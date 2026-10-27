#!/usr/bin/env python3
"""Map code to original source files through embedded source-path strings.

Assertion and debug macros embedded the original file names
("D:\\Ra2\\House.CPP"). Every instruction that pushes or loads such a
string's address anchors its containing function to that file. VC6 keeps
each object file's functions together in .text, so each file's anchors span
an address range; ranges are reported with their anchors, never extended
beyond them.

Writes byte-free manifests/original_source_files.json (file -> anchor
functions and spanned range) and prints a summary.
"""
import argparse
from bisect import bisect_right
import json
from pathlib import Path
import re
import struct
import sys

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))

PATH = re.compile(rb'[A-Za-z]:\\[A-Za-z0-9_\\. -]{2,80}\.(?:cpp|CPP|Cpp|c|C|h|H|hpp|asm|ASM)\0')


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--config', type=Path, default=REPOSITORY / 'private/original-target.local.json')
    args = parser.parse_args()
    import capstone
    from inventory import Inventory
    from verify_manifest import Audit
    audit = Audit(REPOSITORY, json.loads(args.config.read_bytes())['executable'])
    pe = audit.pe; base = audit.base
    raw = pe.__data__
    strings = {}
    for match in PATH.finditer(raw):
        rva = pe.get_rva_from_offset(match.start())
        if rva is not None:
            strings[base + rva] = match.group(0).rstrip(b'\0').decode('latin1')
    functions = Inventory().all_functions()
    spans = sorted((int(r['start'], 16), int(r['end_inclusive'], 16), entry)
                   for entry, row in functions.items() for r in row['ranges'])
    starts = [s[0] for s in spans]
    text = next(s for s in pe.sections if s.Characteristics & 0x20)
    code = text.get_data()[:text.Misc_VirtualSize]; code_base = base + text.VirtualAddress
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    files = {}
    for address, name in strings.items():
        needle = struct.pack('<I', address)
        position = code.find(needle)
        while position >= 0:
            for back in range(1, 8):
                start = position - back
                insn = next(decoder.disasm(code[start:position + 4], code_base + start, 1), None) if start >= 0 else None
                if insn and insn.size == back + 4:
                    index = bisect_right(starts, code_base + start) - 1
                    if index >= 0 and spans[index][0] <= code_base + start <= spans[index][1]:
                        files.setdefault(name, set()).add(spans[index][2])
                    break
            position = code.find(needle, position + 1)
    result = []
    for name, anchors in sorted(files.items(), key=lambda kv: min(kv[1])):
        stem = name.split('\\')[-1]
        result.append(dict(path=name, file=stem, anchors=['%08x' % a for a in sorted(anchors)],
                           first_anchor='%08x' % min(anchors), last_anchor='%08x' % max(anchors)))
    (REPOSITORY / 'manifests/original_source_files.json').write_text(json.dumps(dict(
        source='source-path strings in the supplied executable and the functions that reference them',
        rule='anchors only; a file\'s functions lie around its anchors (VC6 keeps an object file\'s code together)',
        files=result), indent=1) + '\n')
    for item in result:
        print('%-26s %s..%s  %d anchors' % (item['file'], item['first_anchor'], item['last_anchor'], len(item['anchors'])))
    print(len(result), 'files with code anchors;', len(strings), 'path strings')


if __name__ == '__main__':
    main()
