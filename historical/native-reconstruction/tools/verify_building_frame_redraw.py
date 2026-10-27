# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete frame predicate and actual base Building+A8/FTOL children."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x6aa180:0x17f,0x453c70:0x2b,0x77f110:0x3d}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Exact supplied Building frame executable required')
 pe=pefile.PE(data=data);records={};ops={}
 for a,n in RANGES.items():
  raw=pe.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a));ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Building frame range')
  records[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 if pe.get_data(0x79cbbc+0xa8-0x400000,4)!=struct.pack('<I',0x453c70):raise ValueError('Building+A8 dispatch differs')
 if struct.unpack('<d',pe.get_data(0x79a728-0x400000,8))[0]!=0.5:raise ValueError('Height half literal differs')
 for a,op in {0x6aa1c0:('mov','ecx, dword ptr [0xa40b08]'),0x6aa1d2:('mov','ecx, dword ptr [0xa40afc]'),0x6aa203:('call','dword ptr [edx + 0xa8]'),0x6aa2b1:('call','0x77f110'),0x6aa2d4:('mov','ecx, dword ptr [0xa40b08]'),0x453c7f:('lea','esi, [eax - 0x80]')}.items():
  if ops.get(a)!=op:raise ValueError('Building frame load/child association differs')
 return dict(executable_sha256=EXPECTED,ranges=records,building_vtable='0x79cbbc',coordinate_child='0x453c70',scope='Complete6AA180/453C70/FTOL; supplied registry/fields/height scale; no complete frame or queue reset')
