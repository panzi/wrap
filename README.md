wrap
====

Tiny C tool that wraps lines of UTF-8 plaintext files keeping indentation with
very rudimentary unicode support.

Read and experiment with [example.txt](example.txt).

Usage
-----

```plaintext
Usage: wrap [options] [--] [lines...]
       wrap [options] --file FILE

OPTIONS:

   -h, --help                          Print this help message.
   -l LENGTH, --line-length=LENGTH     Wrap lines to LENGTH characters. default: auto
   -t WIDTH, --tab-width=WIDTH         Use WIDTH for tab width. default: 8
   -f FILE, --file=FILE                Read text from FILE instead of wrapping arguments.
                                       Use - for stdin.
```
