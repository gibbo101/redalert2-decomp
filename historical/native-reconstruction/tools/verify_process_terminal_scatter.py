# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact complete Process and shared ordinary terminal/Scatter child tree."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_advance_terminal_scatter import verify as advance_verify,RANGES as ADVANCE,TABLES as AT
from verify_ground_drive_process import verify as process_verify,RANGES as PROCESS
from verify_ground_drive_idle_target import verify as idle_verify,RANGES as IDLE,TABLES as IT
from verify_unit_next_cell import verify as next_verify,RANGES as NEXT
from verify_movement_gate import verify as gate_verify,RANGES as GATE
EXTRA={0x4c2df0:0x67,0x707950:0x30,0x496a90:0x14,0x476cc0:0x28,0x478646:0xb}
RANGES={a:max(d.get(a,0) for d in (ADVANCE,PROCESS,IDLE,NEXT,GATE,EXTRA)) for a in ADVANCE.keys()|PROCESS.keys()|IDLE.keys()|NEXT.keys()|GATE.keys()|EXTRA.keys()}
TABLES={a:max(AT.get(a,0),IT.get(a,0)) for a in AT.keys()|IT.keys()}
def verify(data):
 advance=advance_verify(data);process=process_verify(data);idle=idle_verify(data);nxt=next_verify(data);gate=gate_verify(data)
 TABLES.update({a:max(TABLES.get(a,0),n) for a,n in AT.items()})
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 for a,n in EXTRA.items():
  ins=list(cs.disasm(p.get_data(a-0x400000,n),a))
  if sum(i.size for i in ins)!=n or (a!=0x476cc0 and ins[-1].mnemonic!='ret'):raise ValueError('Incomplete Process child '+hex(a))
 for off,target in ((0x27c,0x707950),(0x4c8,0x4c2df0),(0x4b8,0x705160),(0x16c,0x594770)):
  if p.get_data(0x7addf8+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Process dispatch differs')
 return dict(advance=advance,process=process,idle=idle,next_cell=nxt,gate=gate,root='0x4a05f0',extra={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in EXTRA.items()},scope='Complete ordinary Process/preparation with actual shared Advance0/2/6/7, Cell/Unit/nearby, terminal/idle/null destination/Move_To and timer words. Supplied initial records, Mark/occupation/notification/mission/pathfinder/accessibility/heap/padding. Special flags325/32D and wake type zero; production world/previews/drawing/runtime remain excluded.')
