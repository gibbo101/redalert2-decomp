# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the joined viewport and existing point transform, plus frame dispatch leads."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_tactical_viewport import verify as viewport_verify,RANGES as VIEWPORT
RANGES={**VIEWPORT,0x591380:120}
def verify(data):
 result=viewport_verify(data);pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 for a,n in RANGES.items():
  raw=pe.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete joined viewport range')
  result['ranges'][hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 result['scope']='Complete6A9170 with actual591380 and FTOL; supplied matrix/startup; no frame consumer/reset'
 return result
def inspect_dispatch(data):
 # Inspection only. Do not turn call-site facts into an executed frame proof.
 viewport_verify(data);pe=pefile.PE(data=data);raw=pe.get_data(0xe0b30,288)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,0x4e0b30));ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 if len(ins)!=92 or sum(i.size for i in ins)!=288 or ops.get(0x4e0c4f)!=('ret',''):raise ValueError('Frame dispatcher extent differs')
 leads={0x4e0b7b:('push','0'),0x4e0b86:('call','0x6a45a0'),0x4e0b91:('push','1'),0x4e0b9b:('call','0x6a45a0'),0x4e0ba9:('call','dword ptr [edx + 0x40]'),0x4e0bb2:('push','2'),0x4e0bbc:('call','0x6a45a0'),0x4e0c03:('call','0x5b5b30'),0x4e0c40:('call','dword ptr [edx + 0x44]')}
 if any(ops.get(a)!=v for a,v in leads.items()):raise ValueError('Frame phase/callback association differs')
 # One inherited map-interface vtable; construction/receiver startup remains unproved.
 entries={0x7a6520:0x4e0b30,0x7a6524:0x6a12d0,0x7a6528:0x4e0c50}
 if any(struct.unpack('<I',pe.get_data(a-0x400000,4))[0]!=v for a,v in entries.items()):raise ValueError('Frame vtable association differs')
 return dict(entry='0x4e0b30',bytes=288,instructions=92,sha256=hashlib.sha256(raw).hexdigest(),
  scope='Inspection only; phases0/1 -> live Map+40 -> phase2, then optional/UI/message children; no executed dispatcher or complete frame proof',
  leads={hex(a):v for a,v in leads.items()},vtable_entries={hex(a):hex(v) for a,v in entries.items()})
