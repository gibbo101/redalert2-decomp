# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete direct permission55A740 and Foot override4C8CA0 dispatch."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_infantry_admission import verify as verify_parent
from verify_nearby_cell_admission import verify as verify_permission
RANGES={0x55a740:0xaf,0x4c8ca0:0x59,0x506950:7}
def verify(data):
 parent=verify_parent(data);permission=verify_permission(data);p=pefile.PE(data=data);c=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in {0x503190:0x8ad,**RANGES}.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Infantry permission range')
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for a,want in {0x50334d:('push','1'),0x50334f:('push','esi'),0x503355:('call','0x55a740'),0x503363:('call','dword ptr [edx + 0x2f4]'),0x4c8cb5:('call','dword ptr [eax + 0x80]'),0x4c8cd3:('call','dword ptr [edx + 0x16c]'),0x4c8ce8:('call','0x6ba990')}.items():
  if ops.get(a)!=want:raise ValueError('Infantry permission association differs '+hex(a))
 for offset,target in ((0x84,0x506950),(0x80,0x6c12c0),(0x16c,0x594770),(0x2f4,0x4c8ca0)):
  if p.get_data(0x7a3540+offset-0x400000,4)!=struct.pack('<I',target):raise ValueError('Infantry permission dispatch differs')
 return dict(parent=parent,permission=permission,ranges=ranges,scope='Complete ordinary Infantry admission joins actual direct-Cell permission55A740 and complete Foot override4C8CA0 with actual type/mission getters; nonnull Team6BA990 remains supplied. Initial fields/map/associations remain supplied. No runtime sight adoption.')
