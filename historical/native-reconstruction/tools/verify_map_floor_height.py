#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin actual Cell floor, map floor, relative height and Cell center queries."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x4706c0:0x7bb,0x55a280:0x79,0x5d4810:0x4f,0x47ba50:0x49,0x77f110:0x3d}
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Floor height PE layout differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete floor height range '+hex(a))
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
 constants={0x79a728:0.5,0x79a730:1/256,0x79b610:0,0x79c9b0:-0.5}
 for a,n in constants.items():
  if p.get_data(a-0x400000,8)!=struct.pack('<d',n):raise ValueError('Floor height constant differs')
 if p.get_data(0x7d8964-0x400000,4)!=struct.pack('<I',0xe7f):raise ValueError('FTOL control word differs')
 return {'ranges':ranges,'constants':{hex(a):n for a,n in constants.items()},
  'initial_plane_template_sha256':hashlib.sha256(p.get_data(0x7d27e8-0x400000,800)).hexdigest(),
  'scope':'Complete Cell finite floor query and lazy state initialization, full map floor/relative height/Cell center wrappers. Ramps 0..20; signed level bytes and wrapped products/index/relative subtraction, low coordinate bytes, supplied 53-bit/toward-zero FP mode. Initial static template/global level height, map/Cell/actor/bridge storage supplied. No static startup/level-height initializer, original construction/ownership/concurrency, NaN/qword overflow, other ramp indexes, runtime or frame parity.'}
