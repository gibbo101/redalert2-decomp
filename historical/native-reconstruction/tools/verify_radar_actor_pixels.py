# SPDX-License-Identifier: GPL-3.0-or-later
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_radar_map_pixels import verify as parent_verify
from verify_actor_radar_color import verify as actor_verify,RANGES as ACTOR
from verify_scheme_resolver import verify as resolver_verify,RANGES as RESOLVER
EXTRA={0x4f52b0:0x34,0x4e5580:0x51,0x6c7430:7,0x6c12c0:8,0x506950:7,0x453c60:7}
RANGES={**ACTOR,**RESOLVER,**EXTRA}
def verify(data):
 parent=parent_verify(data);actor=actor_verify(data);resolver=resolver_verify(data);p=pefile.PE(data=data);ranges={};ops={}
 for a,n in EXTRA.items():
  b=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete radar actor child')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(b).hexdigest());ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for a,op in {0x6c12c2:('jmp','dword ptr [eax + 0x84]'),0x506950:('mov','eax, dword ptr [ecx + 0x5a8]'),0x453c60:('mov','eax, dword ptr [ecx + 0x418]'),0x6c7430:('mov','eax, dword ptr [ecx + 0x1b4]'),0x4f52b0:('mov','eax, dword ptr [0xa3d298]'),0x4e558d:('call','dword ptr [eax + 0x3c]')}.items():
  if ops.get(a)!=op:raise ValueError('Radar actor stock association differs')
 for vt,type84 in ((0x7a3540,0x506950),(0x79cbbc,0x453c60)):
  for slot,target in ((0x80,0x6c12c0),(0x84,type84),(0x3c,0x6c7430)):
   if p.get_data(vt+slot-0x400000,4)!=struct.pack('<I',target):raise ValueError('Radar actor stock table differs')
 return dict(parent=parent,actor=actor,resolver=resolver,extra=ranges,scope='Complete nonzero radar/caller with actual floor/discovery/pixels and stock actor/House/type/owner/C0/CC/alliance/scheme/locale-zero CRT children. Initial associations/records supplied; no runtime adoption.')
