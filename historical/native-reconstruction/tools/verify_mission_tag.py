# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact base Tag caller, trigger retirement and null Cell/Object attachment."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_mission_trigger import verify as verify_trigger,RANGES as TRIGGER_RANGES,TABLES
RANGES={**TRIGGER_RANGES,0x6b3df0:0x192,0x6ed990:0x5c,0x5d4430:0x31,0x47a460:0x7a,0x548070:0x38}
def verify(data):
 parent=verify_trigger(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete mission Tag inspection '+hex(a))
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for a,op in {0x6b3e39:('cmp','edx, 2'),0x6b3e3c:('sete','dl'),0x6b3e45:('call','0x6ed740'),
  0x6b3e88:('call','0x6ed990'),0x6b3eb5:('mov','esi, dword ptr [esi + 0x28]'),
  0x6b3ec4:('mov','byte ptr [ebp + 0x35], 0'),0x6b3ed9:('call','0x5d4430'),
  0x6b3f0d:('call','0x47a460'),0x6b3f20:('call','0x6ecb90'),0x6b3f6b:('mov','dword ptr [0xac0ce8], ecx'),
  0x6ed993:('mov','byte ptr [esi + 0x2c], 1'),0x6ed9ce:('test','al, al'),
  0x5d443b:('mov','dword ptr [eax + 0x2c], edx'),0x47a473:('mov','dword ptr [esi + 0x3c], eax'),
  0x54809f:('mov','dword ptr [0xa6fa1c], edx')}.items():
  if ops.get(a)!=op:raise ValueError('Mission Tag association differs '+hex(a))
 if struct.unpack('<I',p.get_data(0x79e868+8-0x400000,4))[0]!=0x40cd40:raise ValueError('Deferred vector growth dispatch differs')
 return dict(trigger=parent,ranges=ranges,scope='Complete Tag RaiseEvent/Trigger Destroy/Object tag assignment/null Cell tag clear and word lookup. Expiration broadcast, heap growth, action effects/initial records/scratch supplied; no deferred drain/discovery/scheduler/runtime.')
