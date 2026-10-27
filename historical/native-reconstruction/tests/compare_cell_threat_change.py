# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Cell threat parent/children: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_cell_threat_change import verify
ORIGINAL=('tests/compare_cell_threat_change.py','tests/original_cell_threat_change.py','tools/verify_cell_threat_change.py')
NATIVE=('src/sim/CellThreatChange.hpp','src/sim/HouseThreat.hpp','tests/cell_threat_change_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_parent=True,complete_children=True,stencil_startup_supplied=True,production_transfer_unjoined=True)
def require(v):
 if not v:raise ValueError('Cell threat evidence/domain differs')
def command(root=0,x=64,y=88,owner=13,delta=598,mode=0,count=4,nulls=0,duplicate=0,initial=0,mutation=0,houses=None,tables=None):
 houses=houses or [13,0,0,0,0,1,0,8192,1,0,128,0]
 tables=tables or [0]*18
 return ' '.join(map(str,[root,x,y,owner,delta,mode,count,nulls,duplicate,initial,mutation,*houses,*tables]))
def parse(c):
 f=list(map(int,c.split()));require(len(f)==41 and all(-2**31<=v<2**31 for v in f) and f[0] in range(4) and -32768<=f[2]<=32767 and -2<=f[6]<=4 and 0<=f[7]<16 and f[8] in (0,1) and f[10] in (0,1,2) and all(0<=f[i]<=255 for i in (12,13,16,17,20,21)))
 if f[0]==0:require(-32768<=f[1]<=32767)
 return f
def scenarios():
 # Each command carries its explicit stencil; no native producer supplies original inputs.
 for delta in (-2147483648,-2147483647,-599,-1,0,1,598,2147483647):
  for initial in (-2147483648,-1,0,2147483647):
   for tables in (STOCK,[0]*18,[0]*9+[0,1,31,32,-1,33,2,30,-32]):
    yield 'signed_delta_ordered_stencil',command(root=1,x=3000,delta=delta,initial=initial,tables=tables)
 for mode in (-1,0,1):
  for count in (-2,0,1,3,4):
   for nulls in (0,5,15):
    for duplicate in (0,1):
     for owner in (-33,-1,0,13,32):
      yield 'complete_parent_house_gates',command(mode=mode,count=count,nulls=nulls,duplicate=duplicate,owner=owner,delta=-598,initial=1000,tables=STOCK)
 for mutation in (1,2):
  for delta in (-598,598,-2147483648):
   yield 'diagnostic_live_registry_saved_cell',command(owner=7,count=4,mutation=mutation,delta=delta,tables=STOCK)
 for raw in range(256):
  yield 'raw_controlled_byte',command(root=3,mode=1,houses=[-1,raw,128,0,0,0,0,0,1,0,0,0])
  yield 'zero_mode_controlled',command(root=3,mode=0,houses=[-1,0,raw,0,0,0,0,0,1,0,0,0])
 for index in (-2147483648,-33,-1,0,1,13,31,32,2147483647):
  for own in (-1,0,13):
   for mask in (0,1,8192,-1,-2147483648):
    yield 'index_equality_mask_shift',command(root=2,owner=index,houses=[own,0,0,mask,0,0,0,0,1,0,0,0])
 for x,y in ((-7,3),(-1,-1),(0,0),(64,88),(127,127)):
  yield 'signed_projection',command(x=x,y=y,tables=[0]*18)
STOCK=[]
def identities(a):
 paths=python_closure(ROOT/'tests/compare_cell_threat_change.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(isinstance(row,list) and all(isinstance(v,str) for v in row) and row.count('R')==1 and row.count('G')==3)
 i=row.index('R');require(i%3==0)
 for j in range(0,i,3):require(0<=int(row[j])<3 and 0<=int(row[j+1])<0x4204 and 0<=int(row[j+2])<2**32)
 require(0<=int(row[i+1])<=255);i+=2
 for _ in range(3):
  require(row[i]=='G');n=int(row[i+1]);require(0<=n<=0x4204);i+=2
  slots=[]
  for _ in range(n):
   require(0<=int(row[i])<0x4204 and 0<=int(row[i+1])<2**32);slots.append(int(row[i]));i+=2
  require(slots==sorted(set(slots)))
 require(row[i]=='D' and len(row)==i+5 and all(0<=int(v)<2**32 for v in row[i+1:]) and int(row[i+2]) in (0,1))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();global STOCK;verify(a.exe.read_bytes());pe=pefile.PE(data=a.exe.read_bytes());STOCK=list(struct.unpack('<18i',pe.get_data(0x7d9fa0-0x400000,72)));start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_cell_threat_change import CellThreatChangeOracle
  oracle=CellThreatChangeOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts.get(hex(a),0)>0 for a in (0x476b20,0x4e5dc0,0x4e5500,0x4f52f0,0x54e370)))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Cell threat change sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
