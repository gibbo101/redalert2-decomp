#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin base visibility spread constructors and inherited projection setup."""
import argparse,hashlib,struct
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from capstone.x86_const import X86_OP_MEM
from verify_static_redraw import verify as verify_static
from verify_terrain_visibility import PATCHED_EXPECTED,write_report

RANGES={0x5441e0:0x1fa6,0x5461a0:0x178c}
THUNKS={0x5441d0:0x5441e0,0x546190:0x5461a0}
COUNTS=0x7a5908
REGISTRATION=0x7ca81c

def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied visibility-startup engine required')
 p=pefile.PE(data=data);image=p.get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32);cs.detail=True;records={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Visibility-startup PE differs')
 for root,size in RANGES.items():
  raw=image[root-0x400000:root-0x400000+size];ins=list(cs.disasm(raw,root))
  if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete visibility-startup constructor '+hex(root))
  stores=[]
  for i in ins:
   for operand in i.operands:
    if operand.type==X86_OP_MEM and operand.mem.base==0 and operand.mem.index==0 and i.mnemonic.startswith('mov'):
     address=operand.mem.disp&0xffffffff
     if (0xa6f248<=address<=0xa6f808) or (0xa6ed18<=address<=0xa6f1e8):stores.append(address)
  expected_stores=369 if root==0x5441e0 else 309
  expected_calls=81 if root==0x5441e0 else 68
  if len(stores)!=expected_stores or sum(i.mnemonic=='call' and i.op_str=='0x42ad30' for i in ins)!=expected_calls:raise ValueError('Visibility-startup constructor body differs '+hex(root))
  if min(stores)!=(0xa6f248 if root==0x5441e0 else 0xa6ed18) or max(stores)!=(0xa6f808 if root==0x5441e0 else 0xa6f1e8):raise ValueError('Visibility-startup store span differs '+hex(root))
  records[hex(root)]=dict(bytes=size,instructions=len(ins),stores=len(stores),point_constructor_calls=expected_calls,sha256=hashlib.sha256(raw).hexdigest())
 for thunk,target in THUNKS.items():
  instruction=next(cs.disasm(image[thunk-0x400000:thunk-0x400000+5],thunk))
  if instruction.mnemonic!='jmp' or instruction.op_str!=hex(target):raise ValueError('Visibility-startup thunk differs '+hex(thunk))
 if struct.unpack('<2I',image[REGISTRATION-0x400000:REGISTRATION-0x400000+8])!=(0x5441d0,0x546190):raise ValueError('Visibility-startup registration order differs')
 counts=image[COUNTS-0x400000:COUNTS-0x400000+44]
 inherited=verify_static(data)
 projection={key:inherited['ranges'][key] for key in ('0x6a20e0','0x6a2170','0x6a2440')}
 return dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',ranges=records,registration_sha256=hashlib.sha256(image[REGISTRATION-0x400000:REGISTRATION-0x400000+8]).hexdigest(),radius_counts_sha256=hashlib.sha256(counts).hexdigest(),projection_initializers=projection,scope='Complete base5441E0/5461A0 visibility spread/height constructors and registration order. Exact projection result reuses the previously verified 6A20E0/6A2170/6A2440 initializers. Private lookup tables and the visibility-mask result table are not incorporated.')

if __name__=='__main__':
 parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--exe',type=Path,required=True);parser.add_argument('--output',type=Path)
 args=parser.parse_args();result=verify(args.exe.read_bytes())
 if args.output:
  if args.output.exists():raise ValueError('Inspection output already exists')
  write_report(args.exe,args.output,result)
 print(f'{len(result["ranges"])} complete visibility constructors / {sum(v["instructions"] for v in result["ranges"].values())} instructions: PASS')
