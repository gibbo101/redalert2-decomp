# SPDX-License-Identifier: GPL-3.0-or-later
"""Original Offset on supplied decoded-index fixtures, not encrypted-loader parity."""
import struct
from original_archive import ArchiveOracle,NODES,NAME
INDEX_ARENA=0x1300000
class EffectiveArchiveOracle(ArchiveOracle):
 def __init__(self,exe):
  super().__init__(exe);self.u.mem_map(INDEX_ARENA,0x1000000)
 def setup_decoded(self,archives):
  if len(archives)>32:raise ValueError('Effective archive fixture exceeds node domain')
  self.reset_list();self.u.mem_write(NODES,bytes([0x5a])*0x2000);self.archive_inputs=[]
  for i,archive in enumerate(archives):
   entries=archive['entries'];node=NODES+i*0x40;index=INDEX_ARENA+i*0x80000
   if len(entries)>32767:raise ValueError('Negative original index count outside fixture')
   filename=NAME+0x800+i*64;encoded=archive['name'].encode('ascii')+b'\0'
   if len(encoded)>64:raise ValueError('Archive fixture name exceeds bound')
   self.u.mem_write(filename,encoded);self.put(node+0xc,filename);self.put(node+4,0);self.put(node+8,0)
   self.put(node+0x14,len(entries));self.put(node+0x1c,archive['body_offset']);self.put(node+0x20,index);self.put(node+0x24,0)
   if entries:self.u.mem_write(index,b''.join(struct.pack('<3I',*e) for e in entries))
   self.register(node);self.archive_inputs.extend([(node,0x40),(index,len(entries)*12),(filename,len(encoded))])
