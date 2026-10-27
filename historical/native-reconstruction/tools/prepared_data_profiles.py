# SPDX-License-Identifier: GPL-3.0-or-later
"""Hash-pinned numeric preparation only; mappings verified in the 1.006 notes."""
import hashlib,struct
from pathlib import Path
DISC='135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743'
PATCHED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
# Explicit bases/ranges, not a blanket displacement. Pointer values in verified
# normal metadata already refer to the selected source image and use read_actual.
PATCHED_TABLES={
 0x7fc114:0x813df4,0x800118:0x817df8,0x78bf94:0x7a0f8c,0x78bf98:0x7a0f90,
 0x788158:0x79d158,0x786630:0x79b630,0x786628:0x79b628,
 0x7e37e4:0x7f9f94,0x7e37d0:0x7f9f80,0x7905d0:0x7a55e8,0x7998d8:0x7aea40,
 0x785cf0:0x79acf0,0x80011c:0x817dfc,
 0x7e36b0:0x7f9e60,0x7ea0e4:0x801dc4,0x7c3128:0x7d8048,0x788090:0x79d090,0x7998c0:0x7aea28}

def readers(data):
 digest=hashlib.sha256(data).hexdigest()
 if digest not in (DISC,PATCHED):raise ValueError('Unsupported executable hash; recover this exact build before preparation')
 pe=struct.unpack_from('<I',data,0x3c)[0]
 if data[pe:pe+4]!=b'PE\0\0' or struct.unpack_from('<H',data,pe+4)[0]!=0x14c or struct.unpack_from('<I',data,pe+52)[0]!=0x400000:
  raise ValueError('Unexpected PE layout')
 count=struct.unpack_from('<H',data,pe+6)[0];optional=struct.unpack_from('<H',data,pe+20)[0]
 def actual(va,size):
  rva=va-0x400000
  for i in range(count):
   p=pe+24+optional+40*i;start,length,offset=struct.unpack_from('<III',data,p+12)
   if start<=rva and rva-start+size<=length:
    result=data[offset+rva-start:offset+rva-start+size]
    if len(result)!=size:raise ValueError('Truncated PE table range')
    return result
  raise ValueError('Table outside supplied PE sections')
 def mapped(va,size):
  if digest==PATCHED:
   if va not in PATCHED_TABLES:raise ValueError('Unmapped patched preparation table')
   va=PATCHED_TABLES[va]
  return actual(va,size)
 return digest,mapped,actual


def default_output(digest,filename):
 if digest==DISC:return Path('private/derived')/filename
 if digest==PATCHED:return Path('private/derived/ra2-1006')/filename
 raise ValueError('Unknown prepared data source')
