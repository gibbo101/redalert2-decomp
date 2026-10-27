# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact supplied-base Building discovery wrapper and radio predicate."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_unit_discovery import verify as verify_common,RANGES as COMMON
RANGES={**COMMON,0x448fe0:0xce,0x636f10:0x25}
DISPATCH={0x180:0x448fe0,0x16c:0x594770,0x1d0:0x594cb0,0x468:0x4426d0}
def verify(data):
 if hashlib.sha256(data).hexdigest()!='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f':raise ValueError('Wrong supplied Building executable')
 common=verify_common(data);p=pefile.PE(data=data);ranges={};ops={}
 for a,n in ((0x448fe0,0xce),(0x636f10,0x25)):
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Building range')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for off,target in DISPATCH.items():
  if p.get_data(0x79cbbc+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Building dispatch differs')
 for a,op in {0x448fe9:('call','0x6c2440'),0x44900b:('mov','edx, dword ptr [eax + 0xb90]'),0x449011:('mov','dword ptr [ecx + 0x1b4], edx'),0x44901d:('mov','byte ptr [eax + 0x18d], 1'),0x44902a:('mov','byte ptr [ecx + 0x144], 1'),0x449033:('call','0x636f10'),0x449065:('call','0x636f10'),0x44909a:('call','dword ptr [eax + 0x468]'),0x636f10:('mov','edx, dword ptr [ecx + 0xd0]'),0x636f1c:('mov','ecx, dword ptr [ecx + 0xcc]')}.items():
  if ops.get(a)!=op:raise ValueError('Building field association differs '+hex(a))
 return dict(common=common,ranges=ranges,dispatch={hex(k):hex(v) for k,v in DISPATCH.items()},scope='Complete448FE0/common/radio636F10; activation4426D0 and Tag effects supplied; initial records and typeB90 supplied; no production scheduling.')
