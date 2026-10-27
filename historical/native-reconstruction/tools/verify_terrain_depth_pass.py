# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base Cell caller, complete TMP body and retained-hit entered children."""
import hashlib,struct,pefile,capstone
from verify_frame_depth_refresh import verify as stock_verify
RANGES={0x4754b0:0x66,0x52c230:6967,0x776340:52,0x411230:52,0x41e3e0:46,0x41e477:32,0x41e510:126,0x411370:49,0x4112f0:10,0x4113b0:4,0x4113c0:14,0x4112c0:4}
def verify(data):
 stock=stock_verify(data);p=pefile.PE(data=data);d=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);ranges={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(d.disasm(b,a))
  if sum(i.size for i in ins)!=n:raise ValueError(('Incomplete terrain depth span',hex(a)))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(b).hexdigest())
 diamond=p.get_data(0x7a4a28-0x400000,1800)
 for y in range(30):
  w=4*(y+1 if y<15 else 29-y);left=(60-w)//2
  if [i for i in range(60) if diamond[y*60+i]!=32]!=list(range(left,left+w)):raise ValueError('Diamond formula differs from original mask')
 return dict(ranges=ranges,diamond_sha256=hashlib.sha256(diamond).hexdigest(),stock_surface=stock['stock_surface_vtable'],scope='Complete4754B0 entered fixed52C230 depth-only profile; actual stock planes/cache retained hit, supplied resident file getter/startup; scratch representation and scheduling excluded')
