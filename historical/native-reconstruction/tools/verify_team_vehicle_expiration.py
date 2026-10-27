# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact base Unit/Aircraft expiration overrides, with inherited Team scope."""
import hashlib,struct,capstone,pefile
from verify_team_foot_expiration import verify as verify_parent
RANGES={0x707e90:56,0x41adb0:56}
def verify(data):
 parent=verify_parent(data);p=pefile.PE(data=data);cs=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);ranges={}
 for address,vt,field in ((0x707e90,0x7addf8,0x5b0),(0x41adb0,0x79b12c,0x5b4)):
  raw=p.get_data(address-0x400000,56);ins=list(cs.disasm(raw,address));ops={i.address-address:(i.mnemonic,i.op_str) for i in ins}
  if sum(i.size for i in ins)!=56 or ops.get(53)!=('ret','8'):raise ValueError('Incomplete vehicle expiration')
  for off,expected in {14:('call','0x4c8460'),19:('mov',f'ecx, dword ptr [esi + {hex(field)}]'),31:('mov',f'dword ptr [esi + {hex(field)}], eax'),37:('cmp','dword ptr [esi + 0x5ac], edi'),45:('mov','dword ptr [esi + 0x5ac], eax')}.items():
   if ops.get(off)!=expected:raise ValueError('Vehicle expiration ordering differs')
  if p.get_data(vt+0x28-0x400000,4)!=struct.pack('<I',address):raise ValueError('Vehicle primary virtual differs')
  ranges[hex(address)]=dict(bytes=56,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest(),vtable=hex(vt))
 return dict(parent=parent,ranges=ranges,scope='Complete Unit/Aircraft with actual inherited Foot/Techno/Radio/Object Team-subject cleanup; named children/startup supplied; no runtime binding')
