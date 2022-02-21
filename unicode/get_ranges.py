#!/usr/bin/env python3

from typing import List, Tuple

def get_ranges(emojis_str: str) -> List[Tuple[int, int]]:
    # assumes ranges never overlap
    ranges: List[Tuple[int, int]] = []
    lines = emojis_str.strip().split('\n')
    for line in lines:
        line = line.split(';')[0].strip()
        if not line:
            continue
        emoji_range = line.split('..')
        start = int(emoji_range[0].strip().lstrip('U+'), 16)
        if len(emoji_range) == 1:
            end = start
        else:
            end = int(emoji_range[1].strip().lstrip('U+'), 16)
        ranges.append((start, end))

    ranges.sort()
    merged_ranges: List[Tuple[int, int]] = []
    for start, end in ranges:
        inserted = False
        for index, (other_start, other_end) in enumerate(merged_ranges):
            if other_end + 1 == start:
                merged_ranges[index] = (other_start, end)
                inserted = True
                break
        if not inserted:
            merged_ranges.append((start, end))
    return merged_ranges

INDENT_WIDTH = 4

def gen_range_expr(start: int, end: int, nesting: int=0) -> None:
    indent = ' ' * (nesting * INDENT_WIDTH)
    if start == end:
        print(indent + 'codepoint == 0x%05X' % start, end='')
    else:
        print(indent + '(codepoint >= 0x%05X && codepoint <= 0x%05X)' % (start, end), end='')

def gen_expr(ranges: List[Tuple[int, int]], nesting: int=0) -> None:
    n = len(ranges)
    
    if n == 0:
        raise ValueError

    if n == 1:
        gen_range_expr(*ranges[0], nesting)
    else:
        mid = n // 2
        left  = ranges[:mid]
        right = ranges[mid:]
        indent = ' ' * (nesting * INDENT_WIDTH)
        print(indent + '(codepoint <= 0x%05X ?' % left[-1][1])
        sub_nesting = nesting + 1
        if len(left) == 1:
            sub_indent = ' ' * (sub_nesting * INDENT_WIDTH)
            print(sub_indent + 'codepoint >= 0x%05X' % left[0][0], end='')
        else:
            gen_expr(left, sub_nesting)
        print(' :')
        gen_expr(right, sub_nesting)
        print(')', end='')

def main() -> None:
    import sys
    with open(sys.argv[1], 'r') as fp:
        emojis_str = fp.read()
    ranges = get_ranges(emojis_str)
    gen_expr(ranges, 3)
    print()
    #for s, e in ranges:
    #    if s == e:
    #        print('            codepoint == 0x%X ||' % s)
    #    else:
    #        print('            (codepoint >= 0x%X && codepoint <= 0x%X) ||' % (s, e))

if __name__ == '__main__':
    main()
