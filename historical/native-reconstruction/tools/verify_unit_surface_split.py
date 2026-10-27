#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Unit split root, contact getter and top-gradient descriptor."""
import argparse,hashlib,struct
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_unit_surface import verify as parent_verify
from verify_terrain_visibility import write_report
def verify(data):
    parent=parent_verify(data);im=pefile.PE(data=data).get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32)
    b=im[0x636e20-0x400000:0x636e30-0x400000];ins=list(cs.disasm(b,0x636e20))
    if sum(i.size for i in ins)!=16 or ins[-1].mnemonic!='ret':raise ValueError('Incomplete contact getter')
    if [i.op_str for i in ins]!=['eax, dword ptr [ecx + 0xcc]','ecx, dword ptr [esp + 4]','eax, dword ptr [eax + ecx*4]','4']:raise ValueError('Contact getter differs')
    descriptors=im[0x7ce168-0x400000:0x7ce168-0x400000+72]
    if struct.unpack('<18i',descriptors)!=(1,1,1,1,-1,1,2,3,2,3,-1,1,1,3,1,3,1,0):raise ValueError('Gradient descriptors differ')
    return {'parent_inspection':parent,'contact_getter':{'start':'0x636e20','bytes':16,'instructions':4,'sha256':hashlib.sha256(b).hexdigest()},
            'gradient_descriptors_sha256':hashlib.sha256(descriptors).hexdigest(),
            'scope':'Complete Unit final surface root including nonzero TooBigToFitUnderBridge selection and conditional split. Actual first-contact getter on supplied pointer array; contact kind and predicates supplied or separately selected actual cell predicates. Actual initialized ordinary final surface/RGB565 with gradients 0/2. Healthy type/contact/house/planes and depth services are supplied; construction, ownership, bridge gameplay, nonordinary blitter pixels, runtime wiring and whole-frame parity remain open.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path);a=p.parse_args();r=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection exists')
        write_report(a.exe,a.output,r)
    print('Complete Unit split root / four-instruction contact getter / three gradient descriptors: PASS')
