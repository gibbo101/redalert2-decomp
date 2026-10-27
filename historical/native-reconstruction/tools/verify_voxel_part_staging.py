#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect staged-part and byte-converter/copy nesting, exact supplied base engine."""
import argparse,sys
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tests'))
from verify_voxel_part import verify as part_verify
from verify_staging_mapping import verify as staging_verify
from verify_composition_mapping import verify as composition_verify
from verify_voxel_cache_mapping import verify as cache_verify
def verify(disc,patched):
    result={'part':part_verify(patched),'staging':staging_verify(disc,patched),
            'composition':composition_verify(disc,patched),'cache':cache_verify(disc,patched)}
    pe=pefile.PE(data=patched);cs=Cs(CS_ARCH_X86,CS_MODE_32)
    for address,mnemonic,operand in ((0x6d1dca,'or','esi, 0x800'),(0x6d1dd0,'not','edi'),
                                    (0x6d1dd4,'and','esi, edi'),(0x485bfc,'mov','eax, dword ptr [esi + 0xc]')):
        ins=next(cs.disasm(pe.get_data(address-0x400000,16),address))
        if (ins.mnemonic,ins.op_str)!=(mnemonic,operand):raise ValueError('Staging flag/selector association differs')
    result['scope']='Actual one-section staged part root, initialized one-shade byte Convert, selector flags zero and full indexed BSurface copy. Ordinary cache parent inspection verifies (0x2000|0x800)&~0x2800 == 0; that parent is not executed by this fixture. Actor/house/value services, HVA records and surface storage remain supplied. No cache/pool/ownership/lifecycle/runtime or whole-frame parity.'
    return result
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--disc',type=Path,default=Path('private/disc-allied/game.exe'));a=p.parse_args()
    verify(a.disc.read_bytes(),a.exe.read_bytes());print('Staged part/byte converter/surface/cache flag inspection: PASS')
