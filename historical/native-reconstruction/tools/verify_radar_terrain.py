# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact base terrain RGB traversal, stock iterator/intersection and projection."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_radar_projection import verify as projection_verify,RANGES as PROJECTION,DATA
RANGES={0x631250:0x1a4,0x55a490:0xb2,0x55a550:0x33,0x41fdf0:0x121,**PROJECTION}
def verify(data):
 projection=projection_verify(data);pe=pefile.PE(data=data);ranges={}
 for a,n in RANGES.items():
  raw=pe.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete terrain RGB span')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 return dict(projection=projection,ranges=ranges,scope='Complete631250, actual iterator/reset/intersection, optionally under complete630B70 on same Map/RGB. Cell4712C0 colors and initial map/source/storage supplied; no runtime adoption.')
