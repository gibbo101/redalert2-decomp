# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the exact Walk selected-head dispatch of Infantry update-position."""
import argparse,hashlib,json,struct
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED

PROCESS_START=0x71e220
PROCESS_SIZE=0x1367
ARRIVAL_START=0x71f0d3
ARRIVAL_END=0x71f2d7
DISPATCH=0x71f196
VTABLE=0x7a3540
UPDATE_POSITION=0x500aa0

def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:
  raise ValueError('Exact supplied Walk schedule engine required')
 pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 if pe.FILE_HEADER.Machine!=0x14c or pe.OPTIONAL_HEADER.ImageBase!=0x400000:
  raise ValueError('Walk schedule PE differs')
 process=list(cs.disasm(pe.get_data(PROCESS_START-0x400000,PROCESS_SIZE),PROCESS_START))
 if sum(i.size for i in process)!=PROCESS_SIZE or process[-1].mnemonic!='ret':
  raise ValueError('Incomplete Walk Movement_AI range')
 ops={i.address:(i.mnemonic,i.op_str) for i in process}
 expected={
  0x71f0d5:('push','0'),0x71f0d7:('call','dword ptr [edx + 0x11c]'),
  0x71f172:('call','0x71f590'),0x71f192:('push','2'),
  0x71f194:('mov','eax, dword ptr [ecx]'),DISPATCH:('call','dword ptr [eax + 0x174]'),
  0x71f19f:('mov','al, byte ptr [ecx + 0x7d]'),
  0x71f1aa:('mov','al, byte ptr [ecx + 0x76]'),
  0x71f1b5:('mov','al, byte ptr [ecx + 0x7a]'),
  0x71f526:('call','0x548000'),0x71f52d:('call','0x47bb30')}
 for address,want in expected.items():
  if ops.get(address)!=want:raise ValueError('Walk update-position schedule differs '+hex(address))
 calls=[i.address for i in process if i.mnemonic=='call' and '+ 0x174]' in i.op_str]
 if calls!=[DISPATCH]:raise ValueError('Walk update-position dispatch inventory differs')
 if pe.get_data(VTABLE+0x174-0x400000,4)!=struct.pack('<I',UPDATE_POSITION):
  raise ValueError('Infantry update-position vtable association differs')
 arrival=pe.get_data(ARRIVAL_START-0x400000,ARRIVAL_END-ARRIVAL_START)
 crossing=pe.get_data(0x71f4ed-0x400000,0x71f535-0x71f4ed)
 return dict(executable_sha256=PATCHED_EXPECTED,
  process=dict(address=hex(PROCESS_START),bytes=PROCESS_SIZE,
   sha256=hashlib.sha256(pe.get_data(PROCESS_START-0x400000,PROCESS_SIZE)).hexdigest()),
  selected_head_arrival=dict(address=hex(ARRIVAL_START),bytes=len(arrival),sha256=hashlib.sha256(arrival).hexdigest(),
   mark0=hex(0x71f0d7),head_transfer=hex(0x71f172),argument=2,dispatch=hex(DISPATCH),vtable_offset=hex(0x174),target=hex(UPDATE_POSITION),
   late_actor_byte_reads=[hex(x) for x in (0x71f19f,0x71f1aa,0x71f1b5)]),
  geometric_cell_crossing=dict(address=hex(0x71f4ed),bytes=len(crossing),sha256=hashlib.sha256(crossing).hexdigest(),
   current_cell=hex(0x71f526),dirty=hex(0x71f52d),update_position_dispatches=0),
  scope='Inspected exact base Walk selected-head arrival schedule: Mark0 and head transfer precede one Infantry vtable+174 call with argument2; raw on-map/76/7A reads follow it. The separate geometric Cell-crossing tail calls current-Cell and dirty only. This does not execute a joined Walk-to-500AA0 original root or enable runtime sight.')

def main():
 parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--exe',type=Path,required=True);parser.add_argument('--output',type=Path,required=True)
 args=parser.parse_args();result=verify(args.exe.read_bytes());result['tool_sha256']=hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
 if args.output.exists():raise ValueError('Refusing to overwrite Walk schedule receipt')
 args.output.parent.mkdir(parents=True,exist_ok=True);args.output.write_text(json.dumps(result,indent=2)+'\n');print('Walk selected-head update-position schedule PASS')
if __name__=='__main__':main()
