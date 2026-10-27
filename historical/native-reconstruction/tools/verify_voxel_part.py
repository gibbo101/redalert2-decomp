#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete staged Techno part root and selected actual actor leaves."""
import argparse,hashlib,struct
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x6d24e0:0x32e,0x6d6df0:7,0x6d6e00:7,0x70a2d0:6,0x717040:6}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data);im=pe.get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    for start,size in RANGES.items():
        b=im[start-0x400000:start-0x400000+size];ins=list(cs.disasm(b,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete part range '+hex(start))
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    for off,target in ((0x1bc,0x6d6df0),(0x1c0,0x6d6e00),(0x2c,0x70a2d0)):
        if struct.unpack_from('<I',im,0x7addf8+off-0x400000)[0]!=target:raise ValueError('Unit part dispatch differs')
    root={i.address:i for i in cs.disasm(im[0x2d24e0:0x2d280e],0x6d24e0)}
    for address,operand in ((0x6d255c,'eax, dword ptr [esp + 0x154]'),(0x6d2565,'dword ptr [edi + 8]'),
                            (0x6d2652,'eax, dword ptr [esp + 0x150]'),(0x6d2659,'edi, dword ptr [esp + 0x14c]'),
                            (0x6d2742,'esi, dword ptr [0xad0608]'),(0x6d280b,'0x20')):
        if root[address].op_str!=operand:raise ValueError('Part frame/point/clip/staging association differs')
    return {'ranges':ranges,'scope':'Complete Techno part root, staged Unit-kind-1/single loaded section/optional supplied HVA/identity global matrix/ordinary light/no flag-bit-8 path. Actual flag/kind leaves, lighting/matrix/raster children execute. House/flag adjustment/value getters/blitter selection/surface draw remain supplied; model loading file/heap and HVA records are research inputs. No nonstaging clip-height, actual staging blit, compressed cache/pool, ownership, firing or whole-frame parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);a=p.parse_args();r=verify(a.exe.read_bytes())
    print(f'{len(r["ranges"])} complete part ranges / {sum(v["instructions"] for v in r["ranges"].values())} instructions: PASS')
