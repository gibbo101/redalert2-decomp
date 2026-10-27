#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Check explicit exact-engine archive ranges; execution parity is separate."""
import argparse, hashlib, json, struct, sys
from pathlib import Path
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86_const import X86_OP_IMM, X86_OP_MEM
sys.path.insert(0, str(Path(__file__).resolve().parents[1]/'tests'))
from archive_profiles import EXPECTED, PATCHED_EXPECTED, PATCHED_ADDRESSES, RANGES
from inspect_patch import write_report

def verify(disc_data, patched_data):
    for data, digest in ((disc_data, EXPECTED), (patched_data, PATCHED_EXPECTED)):
        if hashlib.sha256(data).hexdigest() != digest:
            raise ValueError('Unsupported executable SHA-256')
    disc, patched = (pefile.PE(data=data) for data in (disc_data, patched_data))
    for pe in (disc, patched):
        if pe.FILE_HEADER.Machine != 0x14C or pe.OPTIONAL_HEADER.ImageBase != 0x400000:
            raise ValueError('Unexpected PE architecture/base')
    def read(pe, va, size):
        result = pe.get_data(va-0x400000, size)
        if len(result) != size:
            raise ValueError('Incomplete mapped range')
        return result
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    records = []
    for old_va, size in RANGES.items():
        new_va = PATCHED_ADDRESSES[old_va]
        old, new = read(disc, old_va, size), read(patched, new_va, size)
        before, after = list(decoder.disasm(old, old_va)), list(decoder.disasm(new, new_va))
        if (sum(i.size for i in before) != size or sum(i.size for i in after) != size
                or len(before) != len(after)):
            raise ValueError(f'Incomplete instruction range {old_va:#x}')
        differences = []
        for a, b in zip(before, after):
            if (a.address-old_va != b.address-new_va or a.mnemonic != b.mnemonic
                    or a.size != b.size or len(a.operands) != len(b.operands)):
                raise ValueError(f'Instruction shape changed {a.address:#x}')
            masked_a, masked_b = bytearray(a.bytes), bytearray(b.bytes)
            for x, y in zip(a.operands, b.operands):
                if x.type != y.type:
                    raise ValueError('Operand type changed')
                if x.type == X86_OP_IMM:
                    v, w, offset, length = x.imm, y.imm, a.imm_offset, a.imm_size
                elif x.type == X86_OP_MEM:
                    if (x.mem.base, x.mem.index, x.mem.scale) != (y.mem.base, y.mem.index, y.mem.scale):
                        raise ValueError('Memory operand changed')
                    v, w, offset, length = x.mem.disp, y.mem.disp, a.disp_offset, a.disp_size
                else:
                    if x.reg != y.reg:
                        raise ValueError('Register operand changed')
                    continue
                if v != w:
                    if a.mnemonic.startswith('j') and old_va <= v < old_va+size:
                        if w-new_va != v-old_va:
                            raise ValueError('Internal branch changed')
                        kind = 'same relative branch'
                    elif PATCHED_ADDRESSES.get(v) == w:
                        kind = 'explicit address operand'
                    else:
                        raise ValueError(f'Unverified operand {a.address:#x}: {v:#x} -> {w:#x}')
                    differences.append({'offset': a.address-old_va, 'kind': kind})
                elif not (x.type == X86_OP_IMM and (a.mnemonic == 'call' or a.mnemonic.startswith('j'))):
                    continue
                if not length:
                    raise ValueError('Missing encoded operand')
                masked_a[offset:offset+length] = bytes(length)
                masked_b[offset:offset+length] = bytes(length)
            if masked_a != masked_b:
                raise ValueError(f'Unaccounted instruction bytes {a.address:#x}')
        records.append({'disc_va': hex(old_va), 'patched_va': hex(new_va), 'bytes': size,
                        'instructions': len(before), 'differences': differences,
                        'disc_sha256': hashlib.sha256(old).hexdigest(),
                        'patched_sha256': hashlib.sha256(new).hexdigest()})
    crc_before = read(disc, 0x7C0624, 1024)
    if crc_before != read(patched, PATCHED_ADDRESSES[0x7C0624], 1024):
        raise ValueError('CRC data changed')
    # Dependencies actually dispatched by the constructor, independently read
    # from its referenced FileStraw and prerequisite vtables on each image.
    for old_table, slot, old_target in ((0x788868,0,0x46E0F0),(0x7889AC,8,0x75EE40)):
        for pe, table, target in ((disc,old_table,old_target),
                (patched,PATCHED_ADDRESSES[old_table],PATCHED_ADDRESSES[old_target])):
            if struct.unpack('<I',read(pe,table+slot,4))[0]!=target:
                raise ValueError('Actual archive dependency dispatch changed')
    for old, name in ((0x7C6FC0, b'expand%02d.mix'), (0x7C6FB4, b'ra2.mix'),
                      (0x7C6F9C, b'CACHE.MIX'), (0x7C6F90, b'LOCAL.MIX')):
        for pe, va in ((disc,old), (patched,PATCHED_ADDRESSES[old])):
            if read(pe,va,len(name)+1).lower() != name.lower()+b'\0':
                raise ValueError('Actual bootstrap filename changed')
    return {'disc_sha256': EXPECTED, 'patched_sha256': PATCHED_EXPECTED,
            'ranges': records, 'instructions': sum(r['instructions'] for r in records),
            'crc_table_sha256': hashlib.sha256(crc_before).hexdigest(),
            'evidence': 'inspection only; no original instructions executed'}


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--disc',type=Path,required=True)
    p.add_argument('--patched',type=Path,required=True)
    p.add_argument('--output',type=Path)
    a=p.parse_args();result=verify(a.disc.read_bytes(),a.patched.read_bytes())
    if a.output: write_report(a.patched,a.output,result)
    print(f"Verified {len(result['ranges'])} archive ranges / {result['instructions']} instructions")


if __name__=='__main__': main()
