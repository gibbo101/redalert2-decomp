# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete resource classification below the shared radar-color parents."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_radar_demand_color import verify as parent_verify
from verify_terrain_visibility import PATCHED_EXPECTED
RANGE=(0x5dc0b0,0xbe)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied radar resource target required')
 a,n=RANGE;raw=pefile.PE(data=data).get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a));digest=hashlib.sha256(raw).hexdigest()
 if sum(i.size for i in ins)!=n or digest!='9246fdd038c45698671579cf0ea9362ab445b1c65d4e2fbd3b895c95477ae476':raise ValueError('Resource classifier range differs')
 return dict(parent=parent_verify(data),classifier=dict(address=hex(a),bytes=n,instructions=len(ins),sha256=digest),scope='Complete5DC0B0 below Cell colors/resident/overlay/demand/terrain/projection; shared supplied type/resource registries and logging; no startup, economy or SDL fidelity claim')
