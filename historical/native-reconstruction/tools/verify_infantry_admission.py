# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect complete base Infantry root and its shared actual Foot/map children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import verify_unit_admission as parent
EXTRA={0x503190:0x8ad}
RANGES={**parent.RANGES,**EXTRA}
def verify(data):
 result=parent.verify(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in EXTRA.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Infantry admission root')
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for a,op in {0x50320a:('mov','eax, dword ptr [ecx + 0x24]'),0x5032bf:('cmp','edx, 4'),
  0x5032e6:('call','dword ptr [eax + 0x198]'),0x503435:('mov','ecx, dword ptr [esp + 0x38]'),
  0x503974:('fld','dword ptr [edx*4 + 0x850ea0]'),0x5039dc:('jge','0x503a22')}.items():
  if ops.get(a)!=op:raise ValueError('Infantry admission association differs '+hex(a))
 for off,target in ((0x194,0x503190),(0x198,0x4c8730)):
  if p.get_data(0x7a3540+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Infantry admission dispatch differs')
 return dict(parent=result,ranges=ranges,infantry_dispatch_sha256=hashlib.sha256(p.get_data(0x7a3540+0x194-0x400000,8)).hexdigest(),
  scope='Complete ordinary Infantry503190 roots with actual shared Foot terrain, registry, neighbor/map/fallback and House helpers. Empty/self-only selected lists, absent overlays. Entered permission/other-resident/overlay/hostile-owner weapon children refuse. Initial records, directions, speed bits and associations supplied. No Process/production/SDL join.')
