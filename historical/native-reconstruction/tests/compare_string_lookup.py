#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Original found/no-label localization and real CRT lookup comparison."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_string_lookup import verify
NATIVE=('src/sim/StringLookup.hpp','tests/string_lookup_vectors.cpp')
ORIGINAL=('tests/original_string_lookup.py','tools/verify_string_lookup.py','tests/compare_string_lookup.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(original_found_and_no_label_roots=True,complete_CRT_binary_search=True,actual_locale_zero_comparator=True,output_index_aliasing=True,missing_label_fallback_recovered=False,original_CSF_loader_recovered=False,production_UI_enabled=False)
def require(v):
 if not v:raise ValueError('String lookup input/evidence differs')
def encoded(b):return b.hex() if b else '-'
def decode(t):
 if t=='-':return b''
 try:return bytes.fromhex(t)
 except ValueError:raise ValueError('String lookup hex differs')
def command(op,present,outKind,alias,key,rows):
 return ' '.join([op,str(present),str(len(rows)),str(outKind),str(alias),encoded(key),*[str(v) for row in rows for v in (encoded(row[0]),*row[1:])]])
def parse(cmd):
 p=cmd.split();require(len(p)>=6 and p[0] in ('L','B'));present,n,kind,alias=map(int,p[1:5]);key=decode(p[5]);require(present in (0,1) and 0<=n<=32 and 0<=kind<=4 and alias>=0 and (kind<2 or alias<n) and len(p)==6+n*4 and len(key)<=31 and b'\0' not in key)
 rows=[]
 for i in range(n):
  label=decode(p[6+i*4]);index,text,extra=map(int,p[7+i*4:10+i*4]);require(len(label)<=31 and b'\0' not in label and 0<=index<max(n,1) and 0<=text<=0xffffffff and 0<=extra<max(n,1));rows.append((label,index,text,extra))
 return dict(op=p[0],present=present,outKind=kind,alias=alias,key=key,rows=rows)
def scenarios():
 for n in range(17):
  for duplicate in (False,True):
   keys=[('K%02d'%(i//2 if duplicate else i)).encode() for i in range(n)]
   rows=[(key,(i*3)%n,0x100000+i,(i+1)%n) for i,key in enumerate(keys)]
   for key in [b'',b'A',b'ZZ',*sorted(set(keys))]:yield 'complete_binary_search_lower_middle_and_misses',command('B',1,0,0,key,rows)
   for i,key in enumerate(keys):
    for query in (key,key.lower()):
     for kind in range(5):yield 'found_lookup_repeated_index_and_output_alias',command('L',1,kind,i,query,rows)
   for kind in range(5 if n else 2):yield 'no_label_early_return_output_clear',command('L',0,kind,0,b'unused',rows)
 for key in (b'@',b'A',b'Z',b'[',bytes([128]),bytes([255])):
  rows=[(key,0,0xffffffff,0)]
  for query in (b'',b'a',b'z',key,bytes([254])):yield 'actual_locale_zero_unsigned_byte_comparison',command('B',1,0,0,query,rows)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_string_lookup.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):require(parse(cmd) and isinstance(row,list) and 'R' in row and 'F' in row)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_string_lookup import StringLookupOracle
  oracle=StringLookupOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['0x6f9ec0']>0 and oracle.counts['0x782025']>0 and oracle.counts['0x781f20']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'String lookup sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
