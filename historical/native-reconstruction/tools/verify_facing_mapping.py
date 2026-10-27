#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect bounded Facing mappings; no original instruction execution or editing.

Research-only Capstone/pefile. This evidence covers eight routine ranges, not
whole-engine equivalence or native acceptance of patched tracks/assets.
"""
import argparse
import hashlib
from pathlib import Path
import sys

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86_const import X86_OP_IMM, X86_OP_MEM

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tests'))
from compare_original import EXPECTED, PATCHED_EXPECTED, ADDRESSES, FACING_PROFILES
from inspect_patch import write_report

RANGES = {'set_desired': 224, 'set_current': 208, 'current': 160, 'rotating': 48,
          'clockwise': 64, 'counterclockwise': 64, 'set_rate': 32, 'timer_remaining': 32}


def verify(disc_data, patched_data):
    if hashlib.sha256(disc_data).hexdigest() != EXPECTED:
        raise ValueError('Unsupported disc executable SHA-256')
    if hashlib.sha256(patched_data).hexdigest() != PATCHED_EXPECTED:
        raise ValueError('Unsupported patched executable SHA-256')
    disc = pefile.PE(data=disc_data)
    patched = pefile.PE(data=patched_data)
    for image in (disc, patched):
        if image.FILE_HEADER.Machine != 0x14C or image.OPTIONAL_HEADER.ImageBase != 0x400000:
            raise ValueError('Unexpected PE architecture/base')
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    old_addresses = {**ADDRESSES, 'timer_remaining': 0x453B30}
    new_addresses = {**FACING_PROFILES[PATCHED_EXPECTED][1], 'timer_remaining': 0x453EB0}
    records = []
    for name, size in RANGES.items():
        old_va, new_va = old_addresses[name], new_addresses[name]
        old = disc.get_data(old_va-0x400000, size)
        new = patched.get_data(new_va-0x400000, size)
        old_instructions = list(decoder.disasm(old, old_va))
        new_instructions = list(decoder.disasm(new, new_va))
        if (len(old) != size or len(new) != size or
                sum(i.size for i in old_instructions) != size or
                sum(i.size for i in new_instructions) != size or
                len(old_instructions) != len(new_instructions)):
            raise ValueError('Incomplete instruction range: '+name)
        differences = []
        for before, after in zip(old_instructions, new_instructions):
            if (before.mnemonic != after.mnemonic or before.size != after.size or
                    before.address-old_va != after.address-new_va):
                raise ValueError('Instruction/control-flow mismatch: '+name)
            if before.op_str == after.op_str:
                if before.bytes != after.bytes:
                    raise ValueError('Unexpected encoding change: '+name)
                continue
            kind = None
            old_frame, new_frame = old_addresses['frame_counter'], new_addresses['frame_counter']
            if any(o.type == X86_OP_MEM and o.mem.disp == old_frame for o in before.operands):
                if after.op_str == before.op_str.replace(hex(old_frame), hex(new_frame)):
                    kind = 'frame-counter operand'
            elif before.mnemonic == 'call':
                if (before.operands[0].type == X86_OP_IMM and after.operands[0].type == X86_OP_IMM
                        and before.operands[0].imm == old_addresses['timer_remaining']
                        and after.operands[0].imm == new_addresses['timer_remaining']):
                    kind = 'timer-helper target'
            elif before.mnemonic.startswith('j'):
                if (before.operands[0].type == X86_OP_IMM and after.operands[0].type == X86_OP_IMM
                        and before.operands[0].imm-old_va == after.operands[0].imm-new_va):
                    kind = 'same relative branch'
            if kind is None:
                raise ValueError('Unverified operand change: '+name)
            differences.append({'offset': before.address-old_va, 'kind': kind})
        records.append({'name': name, 'disc_va': hex(old_va), 'patched_va': hex(new_va),
                        'bytes': size, 'disc_sha256': hashlib.sha256(old).hexdigest(),
                        'patched_sha256': hashlib.sha256(new).hexdigest(),
                        'instructions': len(old_instructions), 'operand_differences': differences})
    return {'scope': 'Facing and timer helper only; explicit operand mapping, not whole-engine parity',
            'disc_sha256': EXPECTED, 'patched_sha256': PATCHED_EXPECTED, 'ranges': records,
            'original_bytes_modified': False, 'original_instructions_executed': False}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--disc', required=True, type=Path)
    parser.add_argument('--patched', required=True, type=Path)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    report = verify(args.disc.read_bytes(), args.patched.read_bytes())
    report['tool_sha256'] = hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    if args.output:
        for source in (args.disc.resolve(), args.patched.resolve()):
            if args.output.resolve().is_relative_to(source.parent):
                raise ValueError('Report must be outside either source installation')
        write_report(args.patched, args.output, report)
    print(f"Verified {len(report['ranges'])} bounded Facing/helper mappings, "
          f"{sum(r['instructions'] for r in report['ranges'])} instructions; no original bytes edited.")


if __name__ == '__main__':
    main()
