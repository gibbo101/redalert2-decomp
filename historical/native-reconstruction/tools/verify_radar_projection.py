# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact complete630B70 resampling/build and stock numeric/storage children."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_surface_pixel import verify as pixel_verify,RANGES as PIXEL
from verify_surface_radar_pixel import verify as numeric_verify
RANGES={0x630b70:0x6d2,0x4382c0:0x31,0x77f110:0x3d,0x4112d0:4,**PIXEL}
DATA={0x7a87f8:struct.pack('<f',140),0x7a87f4:struct.pack('<f',108),0x79a708:struct.pack('<d',1),0x79a728:struct.pack('<d',.5),0x79a738:struct.pack('<f',0),0x79b7f8:struct.pack('<f',1)}
def verify(data):
 pixel=pixel_verify(data);numeric=numeric_verify(data);pe=pefile.PE(data=data);ranges={}
 for a,n in RANGES.items():
  raw=pe.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError(('Incomplete radar projection span',hex(a)))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for a,v in DATA.items():
  if pe.get_data(a-0x400000,len(v))!=v:raise ValueError('Projection scalar differs')
 for off,target in ((0x18,0x774e20),(0x80,0x4112d0)):
  if pe.get_data(0x79aef8+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Projection stock virtual differs')
 return dict(pixel=pixel,numeric=numeric,ranges=ranges,scope='Complete630B70 resampling/build under supplied53-bit/toward-zero FP state. Actual4382C0, stock geometry/lock/pitch/unlock and FTOL; allocation,631250 colors and initial clear supplied. No production adoption.')
