# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete630A00 joined to complete4AA4A0; projection child supplied."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_surface_startup import verify as child_verify
from verify_surface_refresh import verify as getters_verify
RANGES={0x630a00:0x169}
def verify(data):
 child=child_verify(data);getters=getters_verify(data);pe=pefile.PE(data=data);raw=pe.get_data(0x630a00-0x400000,0x169);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,0x630a00));ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 if sum(i.size for i in ins)!=len(raw):raise ValueError('Incomplete radar startup parent')
 for a,op in {0x630a83:('call','0x630b70'),0x630b43:('call','0x4aa4a0'),0x630b5c:('call','0x632700'),0x630b68:('ret','')}.items():
  if ops.get(a)!=op:raise ValueError('Radar startup parent control differs')
 return dict(parent=dict(bytes=len(raw),sha256=hashlib.sha256(raw).hexdigest()),child=child,getters=getters,scope='Complete630A00 and actual4AA4A0 plus actual stock width/height getters. Projection630B70, destruction/release, object/descriptor allocation, device results, clear and finish632700 supplied. No runtime adoption.')
