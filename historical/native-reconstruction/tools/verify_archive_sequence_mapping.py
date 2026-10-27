#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Explicit base archive stage inspection, independent of executed comparisons."""
import argparse,hashlib,struct,sys
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from capstone.x86_const import X86_OP_IMM,X86_OP_MEM
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tests'))
from archive_sequence_profiles import RANGES,address
from archive_profiles import EXPECTED,PATCHED_EXPECTED
from verify_archive_mapping import verify as verify_primitives
from inspect_patch import write_report

def verify(disc_data,patched_data):
 primitive=verify_primitives(disc_data,patched_data)
 ps=[pefile.PE(data=data) for data in (disc_data,patched_data)]
 def read(pe,va,n):
  result=pe.get_data(va-0x400000,n)
  if len(result)!=n:raise ValueError('Incomplete archive stage data')
  return result
 c=Cs(CS_ARCH_X86,CS_MODE_32);c.detail=True;records=[]
 for a,n in RANGES.items():
  b=address('supplied-ra2-1006',a);old,new=read(ps[0],a,n),read(ps[1],b,n)
  rows=[list(c.disasm(blob,start)) for blob,start in ((old,a),(new,b))]
  if any(sum(i.size for i in row)!=n for row in rows) or len(rows[0])!=len(rows[1]):raise ValueError('Incomplete stage range')
  changes=[]
  for i,j in zip(*rows):
   if (i.address-a,i.mnemonic,i.size,len(i.operands))!=(j.address-b,j.mnemonic,j.size,len(j.operands)):raise ValueError('Stage instruction shape changed')
   lhs,rhs=bytearray(i.bytes),bytearray(j.bytes)
   for x,y in zip(i.operands,j.operands):
    if x.type!=y.type:raise ValueError('Stage operand type changed')
    if x.type==X86_OP_IMM:v,w,offset,size=x.imm,y.imm,i.imm_offset,i.imm_size
    elif x.type==X86_OP_MEM:
     if (x.mem.base,x.mem.index,x.mem.scale)!=(y.mem.base,y.mem.index,y.mem.scale):raise ValueError('Stage memory operand changed')
     v,w,offset,size=x.mem.disp,y.mem.disp,i.disp_offset,i.disp_size
    else:
     if x.reg!=y.reg:raise ValueError('Stage register operand changed')
     continue
    if v!=w:
     if i.mnemonic.startswith('j') and a<=v<a+n:
      if w-b!=v-a:raise ValueError('Stage branch changed')
     elif address('supplied-ra2-1006',v)!=w:raise ValueError('Unverified stage address')
     changes.append({'offset':i.address-a,'disc_operand':hex(v),'patched_operand':hex(w)})
    elif not(x.type==X86_OP_IMM and (i.mnemonic=='call' or i.mnemonic.startswith('j'))):continue
    if not size:raise ValueError('Missing stage encoding')
    lhs[offset:offset+size]=bytes(size);rhs[offset:offset+size]=bytes(size)
   if lhs!=rhs:raise ValueError('Unaccounted stage instruction bytes')
  records.append({'disc_va':hex(a),'patched_va':hex(b),'bytes':n,'instructions':len(rows[0]),'changes':changes,
                  'disc_sha256':hashlib.sha256(old).hexdigest(),'patched_sha256':hashlib.sha256(new).hexdigest()})
 # Three base theater metadata rows, and actual strings consumed by requests.
 table=read(ps[0],0x785b68,312)
 if table!=read(ps[1],address('supplied-ra2-1006',0x785b68),312):raise ValueError('Theater metadata changed')
 for row,names in enumerate([('TEMPERAT','ISOTEMP','TEM'),('SNOW','ISOSNOW','SNO'),('URBAN','ISOURB','URB')]):
  for offset,name in zip((48,58,68),names):
   if table[row*104+offset:].split(b'\0')[0]!=name.encode():raise ValueError('Theater filename identity differs')
 return {'disc_sha256':EXPECTED,'patched_sha256':PATCHED_EXPECTED,'ranges':records,
         'instructions':sum(r['instructions'] for r in records),'primitive_instructions':primitive['instructions'],
         'theater_metadata_sha256':hashlib.sha256(table).hexdigest(),'evidence':'inspection only; no original instructions executed'}

def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--disc',type=Path,required=True);p.add_argument('--patched',type=Path,required=True);p.add_argument('--output',type=Path)
 a=p.parse_args();r=verify(a.disc.read_bytes(),a.patched.read_bytes())
 if a.output:write_report(a.patched,a.output,r)
 print(f"Verified {len(r['ranges'])} archive stage ranges / {r['instructions']} instructions plus primitives")
if __name__=='__main__':main()
