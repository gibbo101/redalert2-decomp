# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin stock device copy and its software-source fallback children."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_device_surface_pixels import verify as device_verify,RANGES as DEVICE_RANGES
from verify_surface_copy import verify as copy_verify,RANGES as COPY_RANGES,VT,TABLES,DATA_RANGES
RANGES={**COPY_RANGES,**DEVICE_RANGES,0x4aaf80:0x4b,0x4aafd0:0x517,0x411310:3}
def verify(data):
 device=device_verify(data);software=copy_verify(data);p=pefile.PE(data=data);ranges={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,a))
  if sum(i.size for i in ins)!=n:raise ValueError(('Incomplete device copy span',hex(a)))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(b).hexdigest())
 for table,off,a in ((0x7a0be4,8,0x4aaf80),(0x7a0be4,12,0x4aafd0),(VT,0x84,0x411310)):
  if p.get_data(table+off-0x400000,4)!=struct.pack('<I',a):raise ValueError('Device copy virtual association differs')
 return dict(device=device,software=software,ranges=ranges,scope='Complete4AAF80 and complete4AAFD0 software-source path with actual774F00/clip/blitters/device destination locks; hardware branch not executed; OS services and initial records supplied')
