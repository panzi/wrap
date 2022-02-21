#ifndef WRAP_H
#define WRAP_H
#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// only can handle valid UTF-8
#define DECODE_UTF8(STR, SIZE, ...) \
    for (size_t index = 0; index < (SIZE);) { \
        uint8_t byte1 = (STR)[index ++]; \
        if (byte1 < 0x80) { \
            uint32_t codepoint = byte1; \
            (void)codepoint; \
            __VA_ARGS__; \
        } else if (byte1 < 0xE0) { \
            if (index < (SIZE)) { \
                uint8_t byte2 = (STR)[index ++]; \
                uint32_t codepoint = (uint32_t)(byte1 & 0x1F) << 6 | \
                                     (uint32_t)(byte2 & 0x3F); \
                (void)codepoint; \
                __VA_ARGS__; \
            } /* else unexpected end of multibyte sequence, ignored */ \
        } else if (byte1 < 0xF0) { \
            if (index + 1 < (SIZE)) { \
                uint8_t byte2 = (STR)[index ++]; \
                uint8_t byte3 = (STR)[index ++]; \
                \
                uint32_t codepoint = (uint32_t)(byte1 & 0x0F) << 12 | \
                                     (uint32_t)(byte2 & 0x3F) <<  6 | \
                                     (uint32_t)(byte3 & 0x3F); \
                (void)codepoint; \
                __VA_ARGS__; \
            } /* else unexpected end of multibyte sequence, ignored */ \
        } else if (byte1 < 0xF8) { \
            if (index + 2 < (SIZE)) { \
                uint8_t byte2 = (STR)[index ++]; \
                uint8_t byte3 = (STR)[index ++]; \
                uint8_t byte4 = (STR)[index ++]; \
                \
                uint32_t codepoint = (uint32_t)(byte1 & 0x07) << 18 | \
                                     (uint32_t)(byte2 & 0x3F) << 12 | \
                                     (uint32_t)(byte3 & 0x3F) <<  6 | \
                                     (uint32_t)(byte4 & 0x3F); \
                (void)codepoint; \
                __VA_ARGS__; \
            } /* else unexpected end of multibyte sequence, ignored */ \
        } /* else illegal byte sequence, ignored */ \
    }

#define DECODE_UTF8Z(STR, ...) \
    size_t index = 0; \
    while ((STR)[index]) { \
        size_t codepoint_index = index; \
        (void)codepoint_index; \
        uint8_t byte1 = (STR)[index ++]; \
        if (byte1 < 0x80) { \
            uint32_t codepoint = byte1; \
            (void)codepoint; \
            __VA_ARGS__; \
        } else if (byte1 < 0xE0) { \
            if ((STR)[index]) { \
                uint8_t byte2 = (STR)[index ++]; \
                uint32_t codepoint = (uint32_t)(byte1 & 0x1F) << 6 | \
                                     (uint32_t)(byte2 & 0x3F); \
                (void)codepoint; \
                __VA_ARGS__; \
            } /* else unexpected end of multibyte sequence, ignored */ \
        } else if (byte1 < 0xF0) { \
            if ((STR)[index] && (STR)[index + 1]) { \
                uint8_t byte2 = (STR)[index ++]; \
                uint8_t byte3 = (STR)[index ++]; \
                \
                uint32_t codepoint = (uint32_t)(byte1 & 0x0F) << 12 | \
                                     (uint32_t)(byte2 & 0x3F) <<  6 | \
                                     (uint32_t)(byte3 & 0x3F); \
                (void)codepoint; \
                __VA_ARGS__; \
            } /* else unexpected end of multibyte sequence, ignored */ \
        } else if (byte1 < 0xF8) { \
            if ((STR)[index] && (STR)[index + 1] && (STR)[index + 2]) { \
                uint8_t byte2 = (STR)[index ++]; \
                uint8_t byte3 = (STR)[index ++]; \
                uint8_t byte4 = (STR)[index ++]; \
                \
                uint32_t codepoint = (uint32_t)(byte1 & 0x07) << 18 | \
                                     (uint32_t)(byte2 & 0x3F) << 12 | \
                                     (uint32_t)(byte3 & 0x3F) <<  6 | \
                                     (uint32_t)(byte4 & 0x3F); \
                (void)codepoint; \
                __VA_ARGS__; \
            } /* else unexpected end of multibyte sequence, ignored */ \
        } /* else illegal byte sequence, ignored */ \
    }

size_t rendered_char_count(const char *text, size_t len, size_t current_linelen, size_t tabwidth);

#ifdef __cplusplus
}
#endif

#endif
