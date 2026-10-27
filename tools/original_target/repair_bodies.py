#!/usr/bin/env python3
"""Merge function bodies Ghidra split after calls to wrongly no-return functions.

Ghidra marked operator new/delete (and two other functions whose bodies
return) as no-return, so every function calling them was cut after the call.
A split body is repaired when, between consecutive ranges, the earlier range
ends with a call to one of those functions and the missing bytes decode
exactly as instructions. Only original bytes and frozen inventory rows are
used. Output: JSON repairs for ghidra/RepairBodies.java (pass export).
"""
import argparse
import json
from pathlib import Path
import sys

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))


def repairs(rows, wrong, original, decoder):
    found = []
    for row in rows:
        if row['contiguous'] or len(row['ranges']) < 2:
            continue
        spans = sorted(row['ranges'], key=lambda s: int(s['start'], 16))
        if int(spans[0]['start'], 16) != int(row['entry'], 16):
            continue
        good = True
        for previous, following in zip(spans, spans[1:]):
            end = int(previous['end_inclusive'], 16) + 1; start = int(following['start'], 16)
            last = list(decoder.disasm(bytes.fromhex(previous['bytes_hex']), int(previous['start'], 16)))[-1:]
            if (not last or last[0].mnemonic != 'call' or not last[0].op_str.startswith('0x') or
                    int(last[0].op_str, 16) not in wrong or start < end):
                good = False; break
            gap = original(end, start - end) if start > end else b''
            if sum(i.size for i in decoder.disasm(gap, end)) != len(gap):
                good = False; break
        if good:
            found.append(dict(entry=row['entry'], start=spans[0]['start'], end_inclusive=spans[-1]['end_inclusive']))
    return found


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--pass-dir', type=Path, required=True)
    parser.add_argument('--wrong-noreturn', type=Path, required=True, help='JSON list of hex entries')
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--config', type=Path, default=REPOSITORY / 'private/original-target.local.json')
    args = parser.parse_args()
    import capstone
    from verify_manifest import Audit
    audit = Audit(REPOSITORY, json.loads(args.config.read_bytes())['executable'])
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    rows = [json.loads(l) for l in (args.pass_dir / 'functions.jsonl').read_text().splitlines()]
    wrong = {int(x, 16) for x in json.loads(args.wrong_noreturn.read_text())}
    found = repairs(rows, wrong, audit.original, decoder)
    args.output.write_text(json.dumps(dict(wrong_noreturn=sorted('%08x' % w for w in wrong), repairs=found), indent=1))
    print(len(found), 'repairs')


if __name__ == '__main__':
    main()
