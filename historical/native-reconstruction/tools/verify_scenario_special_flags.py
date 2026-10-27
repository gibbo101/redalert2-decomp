# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete supplied-base scenario flag initializer and SpecialFlags reader."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x68b320:0xca,0x68b5a0:0x237}
KEYS=((0x7efae4,'TiberiumExplosive'),(0x7f4494,'MCVDeploy'),(0x7f4484,'InitialVeteran'),(0x7f4450,'IonStorms'),(0x7f4444,'Meteorites'),(0x7f4438,'Visceroids'),(0x7f158c,'TiberiumGrows'),(0x7f44b4,'TiberiumSpreads'),(0x7f44a0,'DestroyableBridges'),(0x7f4474,'FixedAlliance'),(0x7f1508,'FogOfWar'),(0x7f445c,'Inert'),(0x7f4464,'HarvesterImmune'))
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied scenario executable required')
 p=pefile.PE(data=data);ranges={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a));ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete scenario flag span')
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for a,op in {0x68b33b:('mov','dword ptr [ebp], ecx'),0x68b3cb:('or','ebx, 0x1010'),0x68b3d1:('and','edx, 0xfff88087'),0x68b6a2:('mov','ecx, dword ptr [0xa3d298]'),0x68b6ac:('mov','cl, byte ptr [0xa40d13]'),0x68b76e:('call','0x50f410'),0x68b782:('mov','dword ptr [esi], eax')}.items():
  if ops.get(a)!=op:raise ValueError('Scenario flag association differs')
 for a,key in (*KEYS,(0x7f43f8,'SpecialFlags'),(0x7f4408,'EscapeMovies'),(0x7f4418,'SOFTWARE\\Westwood\\Red Alert 2\\')):
  if p.get_data(a-0x400000,len(key)+1)!=key.encode()+b'\0':raise ValueError('Scenario key differs')
 for a in (0x7f43f0,0x7f43f4):
  if struct.unpack('<I',p.get_data(a-0x400000,4))[0]!=0x7f43f8:raise ValueError('Scenario section differs')
 return dict(ranges=ranges,scope='Complete68B320/68B5A0; registry imports and GetBool supplied probes; no full scenario constructor')
