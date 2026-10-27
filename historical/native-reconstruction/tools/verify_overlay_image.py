# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete overlay GetImage, NewTheater and relevant base-loader fields."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x5dd150:0x10f,0x5d7bd0:0x4a,0x4068f0:1}
DIGESTS={0x5dd150:'e6867c875bd0241999c068110a35c5ddf1fb777790653e9212619cedb56d27b1',0x5d7bd0:'dbeb9ffea788b96b65e91c65810bb1fd86027e5ca54d6cdb37ca4eb53d07a249'}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied overlay-image target required')
 pe=pefile.PE(data=data);ranges={}
 for a,n in RANGES.items():
  raw=pe.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a));digest=hashlib.sha256(raw).hexdigest()
  if sum(i.size for i in ins)!=n or a in DIGESTS and digest!=DIGESTS[a]:raise ValueError('Overlay-image range differs')
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=digest)
 for i,(ext,letter) in enumerate(((b'TEM\0',b'T'),(b'SNO\0',b'A'),(b'URB\0',b'U'))):
  if pe.get_data(0x79abac+i*104-0x400000,4)!=ext or pe.get_data(0x79abb4+i*104-0x400000,1)!=letter:raise ValueError('Image theater table differs')
 # Inspect the complete base parent for association evidence, but do not claim
 # execution/recovery of all its independent INI fields/children.
 a,n=0x5d7810,0x3bf;raw=pe.get_data(a-0x400000,n);decoded={i.address:(i.mnemonic,i.op_str) for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a)}
 for a,op in {0x5d7aae:('lea','esi, [ebx + 0x1c8]'),0x5d7b22:('push','esi'),0x5d7b3f:('mov','byte ptr [ebx + 0x1fc], al'),0x5d7b4a:('mov','byte ptr [ebx + 0x207], al')}.items():
  if decoded.get(a)!=op:raise ValueError('Art image field association differs')
 return dict(ranges=ranges,base_parent_inspection_only=dict(address='0x5d7810',bytes=n,sha256=hashlib.sha256(raw).hexdigest()),scope='Complete5DD150 and5D7BD0 with supplied CRT makepath/file construction/read/cleanup services. Resident/zero-demand and base three-theater/NewTheater load/retry branches. Neither-flag uninitialized filename refused. Base loader inspection only; no original IO/heap/animation or production claim.')
