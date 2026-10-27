# SPDX-License-Identifier: GPL-3.0-or-later
"""E1 null-attacker notification with actual Tag/Trigger/event7 mismatch and map children: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_techno_null_notification import verify
ORIGINAL=('tests/compare_techno_null_notification.py','tests/original_techno_null_notification.py','tools/verify_techno_null_notification.py')
NATIVE=('src/sim/TechnoNullNotification.hpp','src/sim/HouseInfantryAccounting.hpp','tests/techno_null_notification_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_to_return_E1_null_attacker=True,actual_tag_trigger_event7_mismatch=True,actual_map_mode_dirty_children=True,type_cost_and_startup_supplied=True,matching_event7_and_live_transfer_unjoined=True)
NAMES=('root','onMap','tag','executing','enabled','destroyed','persistence','stat','modeAC','modeA8','dirty','full','cost','owner')
DEFAULT=(0,1,1,0,1,0,0,7,2,1,0,0,200,0)
def require(v):
 if not v:raise ValueError('Techno null notification evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(map(str,(kw.get(k,v) for k,v in zip(NAMES,DEFAULT))))
def parse(c):
 f=list(map(int,c.split()));require(len(f)==14 and all(-2**31<=v<2**31 for v in f))
 require(0<=f[0]<=3 and f[2] in (0,1) and f[13] in (0,1) and all(0<=f[i]<=255 for i in (1,3,4,5,10,11)) and (f[0]!=2 or f[12]!=7))
 return f
def scenarios():
 for onMap in (0,1,128,255):
  for tag in (0,1):
   for executing in (0,255):
    for enabled in (0,255):
     for destroyed in (0,255):
      for persistence in (0,2):
       yield 'complete_E1_null_attacker_actual_tag_mismatch',command(onMap=onMap,tag=tag,executing=executing,enabled=enabled,destroyed=destroyed,persistence=persistence)
 for stat in (-2**31,-1,0,2**31-1):
  for owner in (0,1):
   for modeAC in (-1,0,2,3):
    for modeA8 in (0,1,2):
     yield 'wrapping_old_house_and_exact_map_mode',command(stat=stat,cost=stat,owner=owner,modeAC=modeAC,modeA8=modeA8)
 for dirty in (0,1,128,255):
  for full in (0,1,128,255):
   for argument in (-2**31,-1,0,1,0x100,0x101):
    yield 'complete_map_dirty_latch_raw_low_bytes',command(root=1,dirty=dirty,full=full,cost=argument)
 for pulse in (-2**31,-1,0,4,29,48,2**31-1):
  for suppress in (0,1,128,255):
   yield 'complete_event7_mismatch_only',command(root=2,cost=pulse,onMap=suppress)
 for ac in (-2**31,-1,0,1,2,3,2**31-1):
  for a8 in (-2**31,-1,0,1,2,2**31-1):
   yield 'complete_exact_map_mode',command(root=3,modeAC=ac,modeA8=a8)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_techno_null_notification.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(isinstance(row,list) and all(isinstance(v,str) for v in row) and row.count('F')==1)
 i=row.index('F');require(i%6==0 and len(row)-i==8)
 for j in range(0,i,6):
  require(int(row[j]) in (1,2,3,4,5,7,8,9,10))
  for v in row[j+1:j+6]:require(0<=int(v)<2**32)
 for v in row[i+1:]:require(0<=int(v)<2**32)
 require(int(row[i+1]) in (0,1) and all(int(row[i+j])<=255 for j in (4,5,6)))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_techno_null_notification import TechnoNullNotificationOracle
  oracle=TechnoNullNotificationOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts.get(hex(a),0)>0 for a in (0x6ced90,0x509800,0x6b3df0,0x6ed740,0x6e6050,0x4ed760,0x6331a0,0x6331e0)))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Techno null notification sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
