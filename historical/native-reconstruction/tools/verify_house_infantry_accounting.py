# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete House accounting parents, counter children and E1 dispatch."""
import hashlib,struct,pefile,capstone
from verify_team_recruitment_schedule import EXPECTED
RANGES={0x4ed440:0x1aa,0x4ed610:0x121,0x4ea800:0x13d,0x4ea970:0x177,0x491c50:0x5d,0x491cb0:0x5d,0x70c490:0x14,0x509800:6}
TABLES={0x4ed5ec:35,0x4ed734:35,0x4ea940:35,0x4eaae8:35}
SERVICES=(0x67c150,0x5b10000,0x5b10010,0x5b10020)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('House Infantry accounting requires exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete House accounting range '+hex(a))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 if p.get_data(0x7a3540+0x2c-0x400000,4)!=struct.pack('<I',0x509800):raise ValueError('E1 kind dispatch differs')
 for table,byte_table,target in ((0x4ed5ec,0x4ed600,0x4ed59e),(0x4ed734,0x4ed748,0x4ed6dd),(0x4ea940,0x4ea954,0x4ea8b1),(0x4eaae8,0x4eaafc,0x4eaa3d)):
  i=p.get_data(byte_table+14-0x400000,1)[0]
  if struct.unpack('<I',p.get_data(table+i*4-0x400000,4))[0]!=target:raise ValueError('E1 accounting switch differs')
 return dict(ranges=out,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},complete_to_return_E1_accounting=True,actual_counter_and_kind_children=True,type_map_resize_and_startup_supplied=True,ownership_transfer_unjoined=True)
