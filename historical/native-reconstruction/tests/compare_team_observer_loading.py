# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete observer definition parser with actual Team/TaskForce/trim/FTOL children."""
import itertools,math
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_observer_loading import verify
ORIGINAL=('tests/compare_team_observer_loading.py','tests/original_team_observer_loading.py','tools/verify_team_observer_loading.py')
NATIVE=('src/assets/TeamObserverInputs.hpp','src/assets/TeamObserverInputs.cpp','src/assets/UnitModelInputs.hpp','src/assets/UnitModelInputs.cpp','src/sim/TeamObserverTypes.hpp','src/sim/TeamObserverConstruction.hpp','src/sim/StringLookup.hpp','tests/team_observer_loading_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_observer_parser=True,Team_lookup_TaskForce_trim_FTOL_actual=True,CRT_locale_zero=True,INI_token_numeric_other_type_services_supplied=True,scenario_startup_supplied=True,production_scheduling=False)
NAMES=('line','session','techProfile','object','country','mutation','alternate','repeats')
TOKENS=[b'Observer',b'alpha',b'USA',b'ignored',b'7',b'Target',b'0123',b'10.9',b'-1.2',b'100',b'1',b'unused',b'2',b'1',b'beta',b'1',b'1',b'0']
DEFAULT=(b','.join(TOKENS),1,0,0,3,0,0,1)
def require(v):
 if not v:raise ValueError('Team observer loading evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));f=[kw.get(k,v) for k,v in zip(NAMES,DEFAULT)];f[0]='~' if f[0] is None else f[0].hex() or '-';return ' '.join(map(str,f))
def line(**tokens):
 result=TOKENS.copy()
 for index,value in tokens.items():result[int(index)]=value
 return b','.join(result)
def changed(index,value):
 result=TOKENS.copy();result[index]=value;return b','.join(result)
def parse(c):
 f=c.split();require(len(f)==8);f[0]=None if f[0]=='~' else b'' if f[0]=='-' else bytes.fromhex(f[0]);f[1:]=map(int,f[1:]);require(all(-2**31<=v<2**31 for v in f[1:]))
 require(0<=f[2]<9 and -1<=f[3]<=3 and 0<=f[5]<=4 and f[6] in range(5) and f[7] in (1,2));return f
def scenarios():
 for n in range(19):yield 'required_and_optional_token_exhaustion',command(line=b','.join(TOKENS[:n]))
 for value in (None,b'',b',,,,',b'  ',b'  '+b','.join(TOKENS)+b'  '):yield 'missing_empty_delimiters_and_decoded_trim',command(line=value)
 for session,tech,name in itertools.product((-2147483648,0,1,2147483647),range(6),(b'alpha',b'first team',b'beta',b'alias',b'unknown',b'<none>')):
  yield 'actual_Team_lookup_names_and_TaskForce_session_order',command(line=changed(1,name),session=session,techProfile=tech)
 for country,name in itertools.product((-2147483648,-1,0,2147483647),(b'<none>',b'<all>',b'USA',b'  A ',b'none')):
  yield 'owner_mode_country_index_and_retained_trim_guard',command(line=changed(2,name),country=country)
 for target,name in itertools.product(range(-1,4),(b'Target',b'<none>',b' x ',b'X'*30)):
  yield 'ordered_four_object_lookup_precedence',command(line=changed(5,name),object=target)
 for token in (b'-1.2',b'-0',b'4294967297',b'-4294967297',b'9223372036854775808',b'-9223372036854775808',b'nan',b'inf',b'-inf',b'1e308',b'1e-300',b'2147483647.9'):
  values=TOKENS.copy();values[7:10]=[token]*3
  yield 'actual_signed64_FTOL_unsigned_low_word_weights',command(line=b','.join(values))
 for data in (b'a',b'f',b' a f ',b'  af 01',b'01   ',b'0x0a',b'xyz',b'+a-f',bytes((128,255)),b'12'*33,b'12 '*33,b' '*20):
  yield 'hex_pair_grouping_whitespace_discarded_33rd_and_tail',command(line=changed(6,data))
 for index,flag in itertools.product((3,4,10,11,12,13,15,16,17),(b'0',b'-1',b'256',b'2147483647')):
  yield 'integer_fields_full_truth_and_discarded_positions',command(line=changed(index,flag))
 for mutation,alternate,repeat,primary in itertools.product(range(1,5),(0,1),(1,2),(b'alpha',b'first team',b'<none>')):
  yield 'live_registry_Team_TaskForce_fields_and_repeated_parse',command(line=changed(1,primary),mutation=mutation,alternate=alternate,repeats=repeat)
 for index in range(18):yield 'empty_tokens_are_skipped_not_retained_columns',command(line=changed(index,b''))
 for name in (b' alpha ',b'  a ',b'ALPHA',b'first team',b'\x01alpha\x20',b'X'*25):
  yield 'bounded_identifier_copy_actual_trim_and_locale_zero_lookup',command(line=changed(1,name))
 for countProfile,tech,session in itertools.product(range(2,5),range(6,9),(0,1)):
  yield 'empty_negative_single_count_registries_and_TaskForces',command(alternate=countProfile,techProfile=tech,session=session)
 for tech,session in itertools.product(range(6,9),(0,1)):
  yield 'positive_registry_with_empty_negative_or_single_TaskForce',command(techProfile=tech,session=session)
 for n in (47,48,49,480,510,511,512,600):yield 'display_copy_and_512_byte_input_boundary',command(line=changed(0,b'Z'*n))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_observer_loading.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k)==v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%4==0 and len(row)==i+88)
 for j in range(0,i,4):
  k,a,b,c=map(int,row[j:j+4]);require(1<=k<=13 and 0<=a<2**64 and 0<=b<2**64 and 0<=c<2**64)
 require(row[i+1] in ('0','1') and row[i+2] in ('0','1'))
 for v in row[i+3:]:require(0<=int(v)<2**64)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_observer_loading import TeamObserverLoadingOracle
  oracle=TeamObserverLoadingOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team observer loading sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
