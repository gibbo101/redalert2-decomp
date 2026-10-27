#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete compressed voxel row/snapshot/cached-draw routines on exact base."""
import argparse,hashlib,struct,sys
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tests'))
from compare_original import PATCHED_EXPECTED
from verify_voxel_part_staging import verify as staging_verify
RANGES={0x63d150:0x5f,0x63d1b0:0x3e,0x63d260:0x65,0x69a1d0:0x130,
        0x6d29d0:0x2c6,0x485d60:0x2a4,0x4864f0:0x7e,0x4350c0:0x471,
        0x49ed90:0x19,0x4382c0:0x31,0x438410:0x28}
def verify(disc,data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    inherited=staging_verify(disc,data);pe=pefile.PE(data=data);im=pe.get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for a,size in RANGES.items():
        b=im[a-0x400000:a-0x400000+size];ins=list(cs.disasm(b,a))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete snapshot routine '+hex(a))
        ranges[hex(a)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    for a,op in ((0x63d16d,'ecx, edi'),(0x63d16f,'0x63d17a'),(0x63d171,'bl, byte ptr [ecx + edx + 1]'),
                  (0x485e9b,'eax, dword ptr [esi + 0xd0]')):
        i=next(cs.disasm(pe.get_data(a-0x400000,16),a))
        if i.op_str!=op:raise ValueError('Snapshot lookahead/selector association differs '+hex(a))
    if struct.unpack_from('<I',im,0x79e4d4-0x400000)[0]!=0x4864f0:raise ValueError('Cached byte span slot differs')
    return {'inherited':inherited,'ranges':ranges,'scope':'Complete ordinary compressed rows, caller-supplied successful pool and capacity failure, Unit-kind-1 staging cached wrapper/byte selector/surface/span. Original pointers normalized to pool-relative offsets in native storage. Readable source padding and zero depth/alpha globals are fixture inputs. No cache parent, allocation/eviction/ownership/lifecycle/runtime or whole-frame parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--disc',type=Path,default=Path('private/disc-allied/game.exe'));a=p.parse_args()
    r=verify(a.disc.read_bytes(),a.exe.read_bytes());print(f'{len(r["ranges"])} complete snapshot/cached ranges: PASS')
