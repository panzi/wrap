#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <getopt.h>
#include <unistd.h>
#include <errno.h>

#include "wrap.h"

#define WS_COL_DEFAULT 80
#define WS_ROW_DEFAULT 80
#define WS_XPIXEL_DEFAULT (80 *  8)
#define WS_YPIXEL_DEFAULT (40 * 14)

bool is_breaking_space(uint32_t codepoint) {
    return codepoint == ' ' ||
           (codepoint >= 0x09 && codepoint <= 0x0D) ||
           codepoint == 0x2028 ||
           codepoint == 0x2029 ||
           (codepoint >= 0x2000 && codepoint <= 0x200A) ||
           codepoint == 0x200C ||
           codepoint == 0x205F ||
           codepoint == 0x3000;
}

size_t find_word_end(const char *text, size_t text_index) {
    const char *str = text + text_index;
    DECODE_UTF8Z(str, {
        if (is_breaking_space(codepoint)) {
            return text_index + codepoint_index;
        }
    });

    return text_index + index;
}

size_t find_word_start(const char *text, size_t text_index) {
    const char *str = text + text_index;
    DECODE_UTF8Z(str, {
        if (!is_breaking_space(codepoint) || codepoint == '\n') {
            return text_index + codepoint_index;
        }
    });

    return text_index + index;
}

bool is_all_dots(const char *text, size_t len) {
    if (len < 3) {
        return false;
    }

    for (size_t index = 0; index < len; ++ index) {
        if (text[index] != '.') {
            return false;
        }
    }

    return true;
}

/**
 * @brief Prints a formatted plain text, wrapping lines in a way to keep some of the formatting.
 * 
 * It indents wrapped lines to:
 * - Existing indentation of non-breaking spaces.
 *   If the existing indentation alone is longer than linelen it is set to zero.
 * - Indentation marks consisting of two spaces '  ' or tab (two U+0020 or U+0009) before non-space.
 * - Definition list items marked by '<term> ... <definition>' or more dots indent
 *   to the start of <definition>.
 * - List items marked by '- <text>' or '* <text>' (a single U+0020 space after '-' or '*')
 *   indent to the start of <text>.
 * 
 * @param fp is the stream to print to
 * @param text is the text to print
 * @param linelen is the maximum length of a line in graphemes
 */
void print_wrapped_text(FILE *fp, const char *text, size_t linelen, size_t tabwidth) {
    size_t index = find_word_start(text, 0);
    size_t indent = rendered_char_count(text, index, 0, tabwidth);
    size_t current_linelen = indent;
    size_t line_start = 0;
    bool wrapped = false;
    bool was_all_dots = false;
    // fprintf(stderr, "new indent width (indent): %zu\n", indent);

    if (indent >= linelen) {
        indent = 0;
    } else {
        fwrite(text, index, 1, fp);
    }

    for (;;) {
        char ch = text[index];
        if (!ch) {
            break;
        }

        if (ch == '\n') {
            fputc('\n', fp);
            indent = 0;
            ++ index;
            line_start = index;
            size_t next_index = find_word_start(text, index);
            indent = rendered_char_count(text + index, next_index - index, 0, tabwidth);
            if (indent >= linelen) {
                indent = 0;
            } else {
                fwrite(text + index, next_index - index, 1, fp);
            }
            // fprintf(stderr, "new indent width (indent): %zu\n", indent);
            current_linelen = indent;
            index = next_index;
            wrapped = false;
            was_all_dots = false;
        } else {
            size_t word_end = find_word_end(text, index);
            size_t word_graphemes = rendered_char_count(text + index, word_end - index, current_linelen, tabwidth);
            if (current_linelen + word_graphemes > linelen && index != line_start) {
                fputc('\n', fp);
                // fprintf(stderr, "do indent by %zu spaces\n", indent);
                for (size_t do_indent = 0; do_indent < indent; ++ do_indent) {
                    fputc(' ', fp);
                }
                current_linelen = indent;
                wrapped = true;
            }

            fwrite(text + index, word_end - index, 1, fp);

            if (!wrapped) {
                char ch;
                if (current_linelen == indent && ((ch = text[index]) == '-' || ch == '*') && (word_end - index) == 1) {
                    indent = current_linelen + 2;
                    // fprintf(stderr, "new indent width (list): %zu\n", indent);
                } else if (
                        (index >= 2 && ((ch = text[index - 2]) == ' ' || ch == '\t') && text[index - 1] == ' ') ||
                        (index >= 1 && text[index - 1] == '\t')
                ) {
                    // indentation mark
                    indent = current_linelen;
                    // fprintf(stderr, "new indent width (mark): %zu\n", indent);
                } else if (was_all_dots) {
                    // definition list item
                    indent = current_linelen;
                    // fprintf(stderr, "new indent width (def): %zu\n", indent);
                }

                was_all_dots = is_all_dots(text + index, word_end - index);
            }
            current_linelen += word_graphemes;

            index = find_word_start(text, word_end);

            size_t space_graphemes = rendered_char_count(text + word_end, index - word_end, current_linelen, tabwidth);
            if (current_linelen + space_graphemes >= linelen) {
                char ch = text[index];
                if (ch != '\n' && ch != 0) {
                    fputc('\n', fp);
                    // fprintf(stderr, "do indent by %zu spaces\n", indent);
                    for (size_t do_indent = 0; do_indent < indent; ++ do_indent) {
                        fputc(' ', fp);
                    }
                    current_linelen = indent;
                    wrapped = true;
                }
            } else {
                fwrite(text + word_end, index - word_end, 1, fp);
                current_linelen += space_graphemes;
            }
        }
    }
}

const struct option options[] = {
    { "help",        no_argument,       0, 'h' },
    { "line-length", required_argument, 0, 'l' },
    { "tab-width",   required_argument, 0, 't' },
    { "file",        required_argument, 0, 'f' },
    { 0, 0, 0, 0 },
};

void usage(int argc, char *argv[]) {
    const char *progname = argc == 0 ? "wrap" : argv[0];
    struct winsize wsize = {
        .ws_col = WS_COL_DEFAULT,
        .ws_row = WS_ROW_DEFAULT,
        .ws_xpixel = WS_XPIXEL_DEFAULT,
        .ws_ypixel = WS_YPIXEL_DEFAULT,
    };
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);

    printf("Usage: %s [options] [--] [lines...]\n", progname);
    printf("       %s [options] --file FILE\n", progname);
    printf("\n");
    print_wrapped_text(stdout,
        "OPTIONS:\n"
        "\n"
        "   -h, --help                          Print this help message.\n"
        "   -l LENGTH, --line-length=LENGTH     Wrap lines to LENGTH characters. default: auto\n"
        "   -t WIDTH, --tab-width=WIDTH         Use WIDTH for tab width. default: 8\n"
        "   -f FILE, --file=FILE                Read text from FILE instead of wrapping arguments. Use - for stdin.\n",
        wsize.ws_col, 8);
}

int main(int argc, char *argv[]) {
    struct winsize wsize = {
        .ws_col = WS_COL_DEFAULT,
        .ws_row = WS_ROW_DEFAULT,
        .ws_xpixel = WS_XPIXEL_DEFAULT,
        .ws_ypixel = WS_YPIXEL_DEFAULT,
    };
    bool linelen_auto = true;
    size_t linelen = WS_COL_DEFAULT;
    size_t tabwidth = 8;
    const char *filename = NULL;

    for (;;) {
        int opt = getopt_long(argc, argv, "hl:f:t:", options, NULL);

        if (opt == -1) {
            break;
        }

        switch (opt) {
            case 'h':
                usage(argc, argv);
                printf(
                    "\n"
                    "(c) 2022 Mathias Panzenböck\n"
                    "GitHub: https://github.com/panzi/wrap\n"
                );
                return 0;

            case 'l':
                if (strcmp(optarg, "auto") == 0) {
                    linelen_auto = true;
                } else {
                    linelen_auto = false;

                    char *endptr = NULL;
                    unsigned long long value = strtoull(optarg, &endptr, 10);
                    if (!*optarg || *endptr || value > SIZE_MAX) {
                        fprintf(stderr, "*** error: illegal value for --line-length: %s\n", optarg);
                        return 1;
                    }
                    linelen = value;
                }
                break;

            case 't':
            {
                    char *endptr = NULL;
                    unsigned long long value = strtoull(optarg, &endptr, 10);
                    if (!*optarg || *endptr || value == 0 || value > SIZE_MAX) {
                        fprintf(stderr, "*** error: illegal value for --tab-width: %s\n", optarg);
                        return 1;
                    }
                    tabwidth = value;
                break;
            }
            case 'f':
                filename = optarg;
                break;

            case '?':
                usage(argc, argv);
                break;
        }
    }

    if (linelen_auto && ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize) != -1) {
        linelen = wsize.ws_col;
    }

    int status = 0;
    if (filename == NULL) {
        for (; optind < argc; ++ optind) {
            print_wrapped_text(stdout, argv[optind], linelen, tabwidth);
            putchar('\n');
        }
    } else if (optind < argc) {
        fprintf(stderr, "*** error: no non-option arguments expected when --file is passed.\n");
        return 1;
    } else {
        bool use_stdin = strcmp(filename, "-") == 0;
        FILE *fp = stdin;
        char *buf = NULL;

        if (!use_stdin) {
            fp = fopen(filename, "r");

            if (fp == NULL) {
                fprintf(stderr, "*** error: %s: %s\n", filename, strerror(errno));
                return 1;
            }
        }

        buf = malloc(BUFSIZ);
        size_t size = BUFSIZ;

        if (buf == NULL) {
            fprintf(stderr, "*** error: error allocating buffer: %s\n", strerror(errno));
            status = 1;
            goto cleanup;
        }

        for (;;) {
            size_t offset = 0;
            buf[0] = 0;

            for (;;) {
                if (fgets(buf + offset, size - offset, fp) == NULL) {
                    if (ferror(fp)) {
                        fprintf(stderr, "*** error: reading input: %s\n", strerror(errno));
                        status = 1;
                        goto cleanup;
                    }
                }

                offset += strlen(buf + offset);
                if (offset == 0) {
                    // end of file
                    goto cleanup;
                }

                if (buf[offset - 1] == '\n' || offset + 1 < size) {
                    // end of line (including last line of file without '\n')
                    break;
                }

                size_t new_size = size * 2;
                if (new_size < size) {
                    errno = ENOMEM;
                    fprintf(stderr, "*** error: error allocating buffer: %s\n", strerror(errno));
                    status = 1;
                    goto cleanup;
                }

                char *new_buf = realloc(buf, new_size);
                if (new_buf == NULL) {
                    fprintf(stderr, "*** error: error allocating buffer: %s\n", strerror(errno));
                    status = 1;
                    goto cleanup;
                }
                buf  = new_buf;
                size = new_size;
            }

            print_wrapped_text(stdout, buf, linelen, tabwidth);
        }

        if (!use_stdin) {
            fclose(fp);
        }

    cleanup:
        free(buf);

        if (!use_stdin) {
            fclose(fp);
        }
    }

    return status;
}
