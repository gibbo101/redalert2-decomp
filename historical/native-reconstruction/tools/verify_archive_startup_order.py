#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact-engine language-before-bootstrap-before-later-startup control flow.
Calls other than selected bridges are opaque. This is not original execution.
"""
import argparse,hashlib,struct,sys
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from capstone.x86_const import X86_OP_IMM
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tests'))
from archive_profiles import archive_profile
from inspect_patch import write_report
PROFILES={
 'allied-disc':(0x683820,0x5109a0,0x481e20,0x591fa0,0x5150e0,0x5152c0,0x7de820),
 'supplied-ra2-1006':(0x68e280,0x5116a0,0x481bf0,0x5952f0,0x515c90,0x515e70,0x7f4f98)}

def verify(data):
 digest,profile=archive_profile(data);main,init,wrapper,mix,bootstrap,later,filename=PROFILES[profile]
 pe=pefile.PE(data=data);c=Cs(CS_ARCH_X86,CS_MODE_32);c.detail=True
 if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('Unexpected startup architecture')
 def read(va,n):return pe.get_data(va-0x400000,n)
 def graph(start):
  todo=[start];rows={};edges={}
  while todo:
   va=todo.pop()
   if va in rows:continue
   if not start<=va<start+0x4000:raise ValueError('Startup graph leaves inspected domain')
   i=next(c.disasm(read(va,15),va,count=1));rows[va]=i;targets=[]
   if i.mnemonic=='ret':pass
   elif i.mnemonic=='jmp':
    if i.operands[0].type!=X86_OP_IMM:raise ValueError('Unresolved startup jump')
    v=i.operands[0].imm
    if start<=v<start+0x4000:targets=[v]
   elif i.mnemonic.startswith('j'):
    if i.operands[0].type!=X86_OP_IMM:raise ValueError('Unresolved startup branch')
    targets=[i.operands[0].imm,i.address+i.size]
   else:targets=[i.address+i.size]
   edges[va]=targets;todo+=targets
  # Reject decoding a branch into the middle of another instruction.
  occupied=set()
  for va,i in sorted(rows.items()):
   points=set(range(va,va+i.size))
   if occupied&points:raise ValueError('Overlapping startup instruction boundaries')
   occupied|=points
  return rows,edges
 def dominates(start,edges,a,b):
  if a not in edges or b not in edges:raise ValueError('Missing startup boundary')
  seen={a};todo=[start]
  while todo:
   va=todo.pop()
   if va in seen:continue
   if va==b:return False
   seen.add(va);todo+=edges.get(va,[])
  return True
 def calls(rows,target):return sorted(i.address for i in rows.values() if i.mnemonic=='call' and i.operands[0].type==X86_OP_IMM and i.operands[0].imm==target)
 main_rows,main_edges=graph(main);init_rows,init_edges=graph(init)
 language_calls=calls(main_rows,mix);wrapper_calls=calls(main_rows,wrapper)
 if len(language_calls)!=1 or len(wrapper_calls)!=2:raise ValueError('Startup bridge cardinality differs')
 language=language_calls[0]
 # Allocation may skip construction. Allocation and merge-after-construction
 # dominate both init calls; the optional constructor call itself does not.
 for call in wrapper_calls:
  if not dominates(main,main_edges,language-26,call) or not dominates(main,main_edges,language+22,call):raise ValueError('Language phase no longer precedes initialization')
 pushes=list(c.disasm(read(language-12,12),language-12))
 if not any(i.mnemonic=='push' and i.operands[0].type==X86_OP_IMM and i.operands[0].imm==filename for i in pushes):raise ValueError('Language filename association differs')
 if read(filename,13).lower()!=b'language.mix\0':raise ValueError('Language filename differs')
 bridge=list(c.disasm(read(wrapper,20),wrapper))
 if bridge[0].mnemonic!='push' or bridge[1].mnemonic!='mov' or bridge[-1].mnemonic!='call' or bridge[-1].operands[0].imm!=init:raise ValueError('Startup wrapper bridge differs')
 a,b=calls(init_rows,bootstrap),calls(init_rows,later)
 if len(a)!=1 or len(b)!=1 or not dominates(init,init_edges,a[0],b[0]):raise ValueError('Bootstrap no longer dominates later initialization')
 def fingerprint(rows):return hashlib.sha256(b''.join(bytes(i.bytes) for _,i in sorted(rows.items()))).hexdigest()
 return {'executable_sha256':digest,'profile':profile,'main_entry':hex(main),'init_entry':hex(init),'wrapper_entry':hex(wrapper),
  'language_constructor_call':hex(language),'init_wrapper_calls':list(map(hex,wrapper_calls)),
  'bootstrap_call':hex(a[0]),'later_startup_call':hex(b[0]),'main_reachable_instructions':len(main_rows),
  'init_reachable_instructions':len(init_rows),'main_graph_sha256':fingerprint(main_rows),'init_graph_sha256':fingerprint(init_rows),
  'evidence':'static control flow only; other calls opaque, external tail jumps terminal, no original instructions executed'}

def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
 a=p.parse_args();r=verify(a.exe.read_bytes())
 if a.output:write_report(a.exe,a.output,r)
 print(f"Inspected {r['profile']} language/bootstrap/later startup order: PASS")
if __name__=='__main__':main()
