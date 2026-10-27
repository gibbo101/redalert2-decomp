# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact complete4712C0, resident image/variant helpers and color scaling."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_radar_terrain import verify as terrain_verify,RANGES as TERRAIN,DATA as TERRAIN_DATA
RANGES={0x4712c0:0x39c,0x529520:0x2c,0x52b730:0x36,0x5293a0:0x2b,0x5293d0:0x26,0x4767a0:0x179,0x63cdf0:0x122,0x432d70:0x19,**TERRAIN}
DATA={**TERRAIN_DATA,0x79b0a8:struct.pack('<f',255)}
def verify(data):
 terrain=terrain_verify(data);pe=pefile.PE(data=data);ranges={}
 for a,n in RANGES.items():
  raw=pe.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Cell radar color span '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for a,v in DATA.items():
  if pe.get_data(a-0x400000,len(v))!=v:raise ValueError('Color scalar differs')
 if pe.get_data(0x7a51a8+0x9c-0x400000,4)!=struct.pack('<I',0x5293d0):raise ValueError('Color image slot differs')
 return dict(terrain=terrain,ranges=ranges,scope='Complete4712C0 with actual529520/52B730/GetImage/initialized4767A0/63CDF0/FTOL;471760 resident,5DD000 overlay color,5DC0B0 resource classification and52B560 image installation supplied. Authored Cell/type/TMP/animation/brightness tables. Standalone or shared terrain/projection join; no production/asset provenance claim.')
