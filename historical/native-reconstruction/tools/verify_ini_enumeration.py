# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original INI count/key/index/cache and existing zero-state CRC."""
import hashlib,struct,pefile,capstone
from verify_team_membership import EXPECTED
RANGES={0x50cb00:193,0x50ce00:205,0x511260:27,0x511280:121,0x511090:149,0x493fc0:457,0x494190:55}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('INI enumeration requires exact supplied executable')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError(('Incomplete INI enumeration span',hex(a)))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 table=[]
 for i in range(256):
  n=i
  for _ in range(8):n=(n>>1)^(0xedb88320 if n&1 else 0)
  table.append(n)
 if p.get_data(0x7d5504-0x400000,1024)!=struct.pack('<256I',*table):raise ValueError('CRC polynomial table differs')
 return dict(ranges=ranges,CRC_polynomial=0xedb88320,complete_count_key_index_cache=True,CRT_qsort_supplied=True,text_and_index_list_construction_unjoined=True)
