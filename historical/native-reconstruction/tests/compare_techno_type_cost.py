# SPDX-License-Identifier: GPL-3.0-or-later
"""Techno Type cost with actual E1 kind/base, House multiplier and FTOL: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_techno_type_cost import verify
ORIGINAL=('tests/compare_techno_type_cost.py','tests/original_techno_type_cost.py','tools/verify_techno_type_cost.py')
NATIVE=('src/sim/TechnoTypeCost.hpp','src/sim/TechnoTypeCost.cpp','src/sim/OriginalMath.hpp','tests/techno_type_cost_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_type_cost_and_house_multiplier=True,actual_E1_kind_base_and_ftol=True,other_kind_query_and_startup_supplied=True,live_transfer_unjoined=True)
NAMES=('house','kind','speed','base','f114','f118','f11c','f120','f124')
DEFAULT=(1,16,0,200,0x3fa00000,0x3fc00000,0x3f400000,0x3f000000,0x3fe00000)
def require(v):
 if not v:raise ValueError('Techno Type cost evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(map(str,(kw.get(k,v) for k,v in zip(NAMES,DEFAULT))))
def parse(c):
 f=list(map(int,c.split()));require(len(f)==9 and f[0] in (0,1) and all(-2**31<=v<2**31 for v in f[1:4]) and all(0<=v<2**32 for v in f[4:]))
 return f
def scenarios():
 for house in (0,1):
  for kind in (-2**31,-1,0,2,3,4,7,15,16,39,40,41,2**31-1):
   for speed in (-1,0,5,6):
    for base in (-2**31,-1,0,200,16777217,2**31-1):
     yield 'complete_null_house_and_multiplier_switch',command(house=house,kind=kind,speed=speed,base=base)
 for bits in (0,0x80000000,1,0x80000001,0x007fffff,0x00800000,0x3dcccccd,0x3f666666,0x3f7fffff,0x3f800000,0x3f800001,0xbf800001,0x40000000,0x4f800000,0x5f000000,0x7f7fffff,0xff7fffff,0x7f800000,0xff800000,0x7fc12345,0x7f812345,0xff812345):
  for base in (-2**31,-16777217,-3,-1,0,1,3,16777217,2**31-1):
   yield 'float32_extremes_rounding_64bit_lowword',command(base=base,f114=bits)
 rng=random.Random(0x6dad30)
 for _ in range(128):
  yield 'deterministic_raw_float32_and_signed_base',command(base=rng.randrange(-2**31,2**31),f114=rng.getrandbits(32))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_techno_type_cost.py',{'sources':dict.fromkeys(ORIGINAL)})
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
 i=row.index('F');require(i%2==0 and len(row)-i==5)
 for j in range(0,i,2):require(int(row[j]) in (2,3,4,5,6) and 0<=int(row[j+1])<2**32)
 for v in row[i+1:]:require(0<=int(v)<2**32)
 require(int(row[i+3]) in (0,1) and int(row[i+4])==1)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_techno_type_cost import TechnoTypeCostOracle
  oracle=TechnoTypeCostOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts.get(hex(a),0)>0 for a in (0x6dad30,0x4f5960,0x6dace0,0x50af60,0x77f110)))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Techno Type cost sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
