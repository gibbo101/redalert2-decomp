# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact-base Trigger roots and bounded event persistence dispatch."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_mission_event import verify as verify_event,RANGES as EVENT_RANGES,TABLES as EVENT_TABLES
RANGES={**EVENT_RANGES,0x6ed680:0xbe,0x6ed740:0xe2,0x6ed830:0x66,0x6e6cf0:0x20,0x6e6d50:0x16}
TABLES={**EVENT_TABLES,0x6e6d10:0x3e}
def verify(data):
 child=verify_event(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete mission trigger inspection')
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for a,op in {0x6ed6ae:('lea','eax, [eax + eax*2]'),0x6ed6ba:('mov','dword ptr [edx + 4], ecx'),
  0x6ed6ca:('shl','edx, cl'),0x6ed73d:('ret',''),0x6ed7b3:('call','0x4ed760'),
  0x6ed7c0:('call','0x6e6050'),0x6ed7d9:('call','0x6e6cf0'),0x6ed7e4:('call','0x6e6d50'),
  0x6ed7f0:('mov','edi, dword ptr [edi + 0x28]'),0x6ed80b:('call','0x6ed680'),
  0x6ed818:('ret','0x14'),0x6ed875:('call','0x6adae0'),0x6ed880:('mov','esi, dword ptr [esi + 0x28]'),
  0x6ed893:('ret','8'),0x6e6d65:('ret','')}.items():
  if ops.get(a)!=op:raise ValueError('Mission trigger association differs '+hex(a))
 for kind in (4,13,33,47):
  index=p.get_data(0x6e6d18-0x400000+kind-1,1)[0]
  target=struct.unpack('<I',p.get_data(0x6e6d10-0x400000+4*index,4))[0]
  if target!=(0x6e6d0a if kind in (4,33) else 0x6e6d0d):raise ValueError('Event persistence dispatch differs')
 return dict(ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},event=child,
  scope='Complete ResetTimers/RegisterEvent/FireActions with actual4/13/33/47 events, persistence and House lookup. Random timer51 refused. Action dispatcher, startup, scratch, Tag/discovery/scheduler and runtime excluded.')
