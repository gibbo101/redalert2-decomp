#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the scenario-loop resident-search setter and complete base4717B0."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED

PREFIX=(0x5135f0,0x51362b)
HELPER=(0x4717b0,0x4717df)
LOOP=(0x481bf0,0x481efc)
CALLERS=((0x481cfa,0x481d08),(0x481ed4,0x481edf))
HASHES={
 PREFIX:'c23ccecd4b6e7107d5e9214b0e9e5522b924a812c0f0520d5ad196af73f76bdf',
 HELPER:'931f5f84d2cbea80b0c5ee8b1c7bdba09e3e0c625bef52bdfd1c2abc8be233dc',
 LOOP:'a4a3314d1f9ee2266b80f0447b7e6f3ee5f9779a651a00d67e3d11106b6188ac',
 CALLERS[0]:'50b3582e127e5f60b10b5da0b3da1f3c86469915391c997d7b001a34efb2b32e',
 CALLERS[1]:'d8aebfb8eb32487f28392231c5eaa5178f6e58a681a50b152e4886bbc5bd1897',
}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Cell resident engine required')
 pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 decoded={}
 for bounds,digest in HASHES.items():
  start,end=bounds;raw=pe.get_data(start-0x400000,end-start)
  if len(raw)!=end-start or hashlib.sha256(raw).hexdigest()!=digest:raise ValueError('Cell resident range differs '+hex(start))
  if bounds!=LOOP:
   ins=list(cs.disasm(raw,start))
   if sum(i.size for i in ins)!=len(raw):raise ValueError('Incomplete Cell resident range '+hex(start))
   decoded.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 expected={
  0x5135f0:('sub','esp, 0x110'),0x513604:('call','0x6e8510'),0x51360f:('call','0x6e7eb0'),
  0x513624:('mov','byte ptr [0xa40958], 1'),
  0x481cfa:('mov','cl, byte ptr [0x7d3338]'),0x481d03:('call','0x5135f0'),
  0x481ed4:('mov','cl, byte ptr [0x7d3338]'),0x481eda:('call','0x5135f0'),
  0x4717b0:('mov','al, byte ptr [0xa40958]'),0x4717b8:('je','0x4717d7'),
  0x4717ba:('mov','esi, dword ptr [ecx + 0xe4]'),0x4717c8:('call','dword ptr [eax + 0x2c]'),
  0x4717cb:('cmp','eax, 6'),0x4717d0:('mov','esi, dword ptr [esi + 0x30]'),
  0x4717d7:('xor','eax, eax'),0x4717db:('mov','eax, esi'),0x4717de:('ret',''),
 }
 for address,op in expected.items():
  if decoded.get(address)!=op:raise ValueError('Cell resident association differs '+hex(address))
 calls=[]
 for section in pe.sections:
  raw=section.get_data();start=pe.OPTIONAL_HEADER.ImageBase+section.VirtualAddress
  for i in range(len(raw)-4):
   if raw[i]==0xe8 and start+i+5+struct.unpack_from('<i',raw,i+1)[0]==PREFIX[0]:calls.append(start+i)
 if calls!=[0x481d03,0x481eda]:raise ValueError('Scenario-loop setter callers differ')
 for address in (0x690863,0x690883):
  raw=pe.get_data(address-0x400000,5)
  if raw[0]!=0xe8 or address+5+struct.unpack_from('<i',raw,1)[0]!=LOOP[0]:raise ValueError('Top-level loop caller differs '+hex(address))
 return dict(ranges={hex(a):dict(bytes=b-a,sha256=HASHES[(a,b)]) for a,b in HASHES},
  setter_callers=[hex(x) for x in calls],top_level_loop_callers=['0x690863','0x690883'],
  scope='Selected unconditional scenario-loop prefix store plus complete Cell primary-list kind-6 traversal. Preceding calls, the rest of the loop/startup and resident construction remain separate.')
