# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact grid/stock threat/Object Cell/map child associations."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_house_actor_threat import verify as parent_verify,RANGES as PARENT,TABLES,table_values
from verify_map_coordinate_cell import verify as map_verify,ROOT as MAP_ROOT,SIZE as MAP_SIZE
EXTRA={0x5d51e0:0x57,MAP_ROOT:MAP_SIZE}
RANGES={**PARENT,**EXTRA}
def verify(data):
 parent=parent_verify(data);coordinate=map_verify(data);pe=pefile.PE(data=data);raw=pe.get_data(0x5d51e0-0x400000,0x57);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,0x5d51e0));ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 if sum(i.size for i in ins)!=0x57 or ops.get(0x5d520a)!=('call','0x548000') or ops.get(0x5d522d)!=('call','0x548000') or ops.get(0x5d5236)!=('ret',''):raise ValueError('Object Cell getter differs')
 for vt in (0x7a3540,0x79cbbc):
  if pe.get_data(vt+0x1a4-0x400000,4)!=struct.pack('<I',0x5d51e0):raise ValueError('Stock Object Cell dispatch differs')
 return dict(parent=parent,coordinate=coordinate,currentCell=dict(bytes=len(raw),sha256=hashlib.sha256(raw).hexdigest()),scope='Complete grid/stock threat joined to actual5D51E0 and both548000 lookups on shared map/fallback. Initial records/count/table associations and diagnostic mutations supplied; no production/diplomacy/runtime adoption.')
