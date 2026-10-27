# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact base copy8/clip/stock lock/blitters and CRT data-movement spans."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_surface_pixel import RANGES as PIXEL_RANGES,VT
from verify_surface_clip import RANGES as CLIP_RANGES
from verify_string_lookup import EXPECTED
# CRT code spans exclude embedded branch tables and unreachable padding bytes.
RANGES={**{a:n for a,n in PIXEL_RANGES.items() if a!=0x774220},**CLIP_RANGES,
 0x774f00:0x153,0x434ae0:0x59,0x434b40:0x517,0x7753b0:0x1a8,
 0x411290:0x24,0x435540:0x20,0x435560:0x11,
 0x775980:0x2d,0x775a30:0x2d,0x775a60:0x21,0x775a90:0x1a,0x775ab0:0x24,0x775ae0:0x1d,0x775b00:0x2b,0x775b30:0x2d,
 0x783290:0x63,0x783300:0x6c,0x78338c:0x4c,0x7833e8:0x93,
 0x783488:0x7c,0x783524:0x4c,0x783580:0x45}
DATA_RANGES={0x7ce1b0:24}
TABLES={0x7afcb4:(0x7759f0,0x775980,0x775a30),0x7afca4:(0x775a10,0x775b00,0x775b30),0x7afc94:(0x7759b0,0x775a60,0x775a90),0x7afc84:(0x7759d0,0x775ab0,0x775ae0),
 0x7832f4:(0x783300,0x78332c,0x783350),0x78336c:(0x7833cf,0x7833bc,0x7833b4,0x7833ac,0x7833a4,0x78339c,0x783394,0x78338c),0x7833d8:(0x7833e8,0x7833f0,0x7833fc,0x783410),
 0x78347c:(0x783488,0x7834a8,0x7834d0),0x783504:(0x783524,0x78352c,0x783534,0x78353c,0x783544,0x78354c,0x783554,0x783567),0x783570:(0x783580,0x783588,0x783598,0x7835ac)}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Copy requires exact supplied base')
 p=pefile.PE(data=data);ranges={};ops={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,a))
  if sum(i.size for i in ins)!=n:raise ValueError(('Incomplete copy instruction span',hex(a),n,sum(i.size for i in ins)))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(b).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,values in TABLES.items():
  if p.get_data(a-0x400000,len(values)*4)!=struct.pack('<'+'I'*len(values),*values):raise ValueError('Copy blitter/CRT/gradient table differs')
 for off,a in {8:0x774f00,0x5c:0x411370,0x60:0x4112f0,0x70:0x4113b0,0x74:0x4113c0,0x78:0x411290,0x7c:0x4112c0}.items():
  if p.get_data(VT+off-0x400000,4)!=struct.pack('<I',a):raise ValueError('Copy stock virtual differs')
 for a,op in {0x774f70:('call','0x775190'),0x434bed:('call','0x7753b0'),0x77553d:('call','dword ptr [edx + 0x60]'),0x775a9f:('call','0x783290')}.items():
  if ops.get(a)!=op:raise ValueError('Copy control differs')
 return dict(executable_sha256=EXPECTED,ranges=ranges,tables={hex(a):list(v) for a,v in TABLES.items()},data_ranges={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in DATA_RANGES.items()},scope='Complete774F00 stock-surface copy,434AE0/434B40 zero-alpha/depth profile, actual7753B0/clip/lock/blitters/CRT. Supplied geometry/allocation/stock association; no production/SDL adoption.')
