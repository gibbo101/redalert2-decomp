# SPDX-License-Identifier: GPL-3.0-or-later
"""Check complete base passability and the actual Infantry kind/default branch."""
import hashlib,struct
import pefile
from verify_occupied_cell import verify as occupied,RANGES as BASE,DISPATCH as BASE_DISPATCH
RANGES={**BASE,0x509800:6}
DISPATCH={**BASE_DISPATCH,0x7a3540+0x2c:0x509800}
def verify(data):
 result=occupied(data);p=pefile.PE(data=data)
 raw=p.get_data(0x509800-0x400000,6)
 if raw!=bytes.fromhex('b80f000000c3'):raise ValueError('Infantry kind leaf differs')
 if p.get_data(0x7a356c-0x400000,4)!=struct.pack('<I',0x509800):raise ValueError('Infantry kind slot differs')
 # Neither Building6 nor Terrain36: follow the actual Next pointer.
 if p.get_data(0x479043-0x400000,11)!=bytes.fromhex('3bc5740783f8247453eb3f'):raise ValueError('Passability default branch differs')
 return dict(occupied=result,infantry_kind_sha256=hashlib.sha256(raw).hexdigest(),infantry_dispatch=hex(0x509800),scope='Complete passability with kind15 and mixed primary lists; initial records supplied. No constructors/full movement/frame proof.')
