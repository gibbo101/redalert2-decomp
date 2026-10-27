# SPDX-License-Identifier: GPL-3.0-or-later
"""Tagged Infantry discovery with actual Tag/event7 mismatch: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_tagged_infantry_discovery import verify
ORIGINAL=('tests/compare_tagged_infantry_discovery.py','tests/original_tagged_infantry_discovery.py','tools/verify_tagged_infantry_discovery.py')
NATIVE=('src/sim/WaypointTaggedDiscovery.hpp','src/sim/WaypointResidentDiscovery.hpp','src/sim/UnitDiscovery.hpp','src/sim/UnitDiscovery.cpp','src/sim/MissionTag.hpp','src/sim/MissionTrigger.hpp','src/sim/MissionEvent.hpp','tests/tagged_infantry_discovery_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_E1_discovery=True,actual_tag_trigger_event7_mismatch=True,startup_and_country_association_supplied=True,matching_event7_and_live_transfer_unjoined=True)
NAMES=('mode','loading','current','owner','discoverer','field372','current373','other374','mission','queued','queuedA4','tag','executing','enabled','destroyed','persistence','human','control','country')
DEFAULT=(0,0,0,1,0,0,0,0,14,-1,255,1,0,1,0,0,1,0,19)
def require(v):
 if not v:raise ValueError('Tagged Infantry discovery evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(map(str,(kw.get(k,v) for k,v in zip(NAMES,DEFAULT))))
def parse(c):
 f=list(map(int,c.split()));require(len(f)==19 and all(-2**31<=v<2**31 for v in f) and f[2] in (0,1) and f[3] in (0,1) and -1<=f[4]<=1 and f[11] in (0,1) and all(0<=f[i]<=255 for i in (5,6,7,10,12,13,14,16,17)) and f[18] in (-9,13,19));return f
def scenarios():
 for current in (0,1):
  for owner in (0,1):
   for discoverer in (-1,0,1):
    for local in (0,128):
     for loading in (0,1):
      for tag in (0,1):yield 'House_null_loading_local_Tag',command(current=current,owner=owner,discoverer=discoverer,field372=local,loading=loading,tag=tag)
 for executing in (0,128):
  for enabled in (0,255):
   for destroyed in (0,1):
    for persistence in (0,1,2,0x12340002):
     for human in (0,1):
      for control in (0,255):yield 'actual_Tag_Trigger_event7_mismatch',command(executing=executing,enabled=enabled,destroyed=destroyed,persistence=persistence,human=human,control=control)
 for current373 in (0,1,128):
  for other374 in (0,1,255):
   for mode in (0,1,-1):
    for mission in (14,19,-1):
     for queued in (14,-1):yield 'repeat_discovery_QueueMission',command(current373=current373,other374=other374,mode=mode,mission=mission,queued=queued,human=0)
 for country in (-9,13,19):
  for raw in (0,1,128,255):yield 'country_B4_lookup_Type_B8',command(country=country,enabled=raw)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_tagged_infantry_discovery.py',{'sources':dict.fromkeys(ORIGINAL)})
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
 i=row.index('F');require(i%6==0 and len(row)-i==14)
 for j in range(0,i,6):require(int(row[j]) in range(1,11) and all(0<=int(v)<2**32 for v in row[j+1:j+6]))
 for v in row[i+1:]:require(0<=int(v)<2**32)
 require(all(int(row[i+j])<=255 for j in (1,2,4,5,6,7,8,9,10,11)) and int(row[i+12])==4 and int(row[i+13])==0)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_tagged_infantry_discovery import TaggedInfantryDiscoveryOracle
  oracle=TaggedInfantryDiscoveryOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts.get(hex(a),0)>0 for a in (0x6c2440,0x5d4230,0x4f52f0,0x594770,0x594cb0,0x6b3df0,0x6ed740,0x4ed760,0x6e6050)))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Tagged Infantry discovery sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
