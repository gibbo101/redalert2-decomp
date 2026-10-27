#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare bounded original MIX behavior; private receipts protect native replay."""
import argparse, hashlib, json, random, struct, subprocess, sys, time, zlib
from pathlib import Path
from archive_profiles import archive_profile
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'tools'))
from verify_archive_mapping import verify
from inspect_patch import write_report

SOURCES=('tests/archive_profiles.py','tests/original_archive.py','tests/compare_archive.py',
 'tests/compare_original.py','tests/presentation_evidence.py','tools/verify_archive_mapping.py','tools/inspect_patch.py',
 'src/assets/Archive.hpp','src/assets/Archive.cpp','tests/archive_vectors.cpp')
def source_identities():return {name:hash_file(ROOT/name) for name in SOURCES}
def validate_cached(evidence,current):
 for key in ('executable_sha256','profile','sources','fixtures'):
  if evidence['evidence'].get(key)!=current.get(key):raise ValueError('Archive cached identity differs: '+key)
 if evidence['profile']!=current['profile'] or evidence['executable_sha256']!=current['executable_sha256']:
  raise ValueError('Archive cached envelope identity differs')
def run_native(native,commands):
 p=subprocess.run([str(native)],input='\n'.join(commands)+'\n',text=True,capture_output=True,check=True)
 return [line.split() for line in p.stdout.splitlines()]
def independent_id(name):
 data=name.upper().encode('ascii');r=len(data)%4
 if r:data+=bytes([r])+bytes([data[-r]])*(3-r)
 return zlib.crc32(data)
def make_mix(entries,flags=0):
 # Small authored fixtures only, never copied asset content.
 body=bytes(range(64));header=struct.pack('<HI',len(entries),len(body))+b''.join(struct.pack('<3I',*e) for e in entries)
 return (b'' if flags is None else struct.pack('<I',flags))+header+body

def main():
 p=argparse.ArgumentParser(description=__doc__)
 p.add_argument('--exe',type=Path,required=True);p.add_argument('--disc',type=Path,default=ROOT/'private/disc-allied/game.exe')
 p.add_argument('--patched',type=Path,default=ROOT/'private/official-1006-probe/game.exe')
 p.add_argument('--native',type=Path,default=ROOT/'build/native/archive-vectors')
 p.add_argument('--output-dir',type=Path);p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
 a=p.parse_args();digest,profile=archive_profile(a.exe.read_bytes());verify(a.disc.read_bytes(),a.patched.read_bytes())
 work=private_path(a.output_dir or ROOT/'private/migration'/profile/'archive',a.exe)
 sources=source_identities();native_hash=hash_file(a.native)
 def identities(fixtures):
  if archive_profile(a.exe.read_bytes())!=(digest,profile) or source_identities()!=sources or hash_file(a.native)!=native_hash:
   raise ValueError('Archive source/engine/native changed during run')
  if any(hash_file(Path(path))!=h for path,h in fixtures.items()):raise ValueError('Archive fixture changed during run')
  return {'executable_sha256':digest,'profile':profile,'sources':sources,'fixtures':fixtures,'native_sha256':native_hash,
          'runtime_profile_promoted':False}
 if a.expectations:
  source=private_path(a.expectations,a.exe);e=json.loads(source.read_text());receipt=source.parent/'report.json'
  validate_receipt(e,json.loads(receipt.read_text()),hash_file(source))
  fixtures=e['evidence']['fixtures'];current=identities(fixtures);validate_cached(e,current)
  destination=private_path(a.report or work/'replay-report.json',a.exe);check_replay_destination(destination,source,receipt)
  started=time.monotonic();actual=run_native(a.native,e['commands']);elapsed=time.monotonic()-started
  validate_cached(e,identities(fixtures))
  if actual!=e['expected']:raise AssertionError('Archive cached original/native mismatch')
  result={**e['evidence'],**current,'evidence_mode':'cached-original-replay','original_instructions_executed':False,
          'expectations_sha256':hash_file(source),'native_comparison_seconds':elapsed}
  write_report(a.exe,destination,result)
  print(f'{len(actual):,} {profile} archive results PASS (native replay; no original execution)');return
 for name in ('expected.json','report.json'):
  if (work/name).exists():raise ValueError('Fresh archive receipts exist; use --expectations')
 if a.report and a.report.exists():raise ValueError('Fresh output already exists')
 work.mkdir(parents=True,exist_ok=True)
 from original_archive import ArchiveOracle
 o=ArchiveOracle(a.exe);rng=random.Random(0x52413241);commands=[];expected=[];groups={};fixtures={};observations=[]
 def add(group,command,result):
  commands.append(command);expected.append(list(map(str,result)));groups[group]=groups.get(group,0)+1
 def lookup(archives,name,mask,group):
  o.setup(archives)
  data=' '.join(str(x) for origin,cached,entries in archives for x in [origin,cached,len(entries),*[v for e in entries for v in e]])
  add(group,f'L {mask} {int(name is None)} {json.dumps(name or "")} {len(archives)} '+data,o.lookup(name,mask))
 started=time.monotonic()
 names=['','htnk.vxl','RULES.INI','a','ab','abc','abcd','abcde','duplicate.id','mp03t4.map']
 names+=[ ''.join(rng.choice('aBcDeF0123456789._ -') for _ in range(i%95+1)) for i in range(502)]
 for name in names:add('filename_crc',f'H {json.dumps(name)}',o.hash(name))
 for i in range(96):
  ids=[0x80000000,0xffffffff,0,0x7fffffff]+[rng.getrandbits(32) for _ in range(i%17)]
  if i%3==0:ids += [ids[-1]]*3
  ids.sort(key=lambda n:n if n<0x80000000 else n-0x100000000)
  entries=[(id,j%31,(j*3)%16) for j,id in enumerate(ids)]
  flags=[None,0,0x10000][i%3];blob=make_mix(entries,flags);origin=rng.getrandbits(32)
  path=work/f'plaintext-{i:03d}.mix'
  with path.open('xb') as out:out.write(blob)
  fixtures[str(path)]=hash_file(path);result,events=o.constructor(blob,origin)
  add('plaintext_constructor',f'M {json.dumps(str(path))} {origin}',result)
 # Full parser failure behavior has original-only assertions; native refuses
 # malformed/negative counts rather than simulating huge allocation requests.
 for available,allocate in [(False,True),(True,False)]:
  blob=make_mix([(independent_id('a'),0,1)])
  result,events=o.constructor(blob,available=available,allocate=allocate)
  assert result[0]==0 and result[3]==0
  observations.append({'kind':'constructor-unregistered','available':available,'allocate':allocate,'result':result,'events':events})
 for count in (0x8000,0xffff):
  blob=struct.pack('<IHI',0,count,64)
  result,events=o.constructor(blob,allocate=False)
  assert result[0]==0 and result[1]==count-65536 & 0xffffffff
  observations.append({'kind':'signed-count-refused-allocation','count':count,'result':result,'events':events})
 for i in range(128):
  expansions=[] if i==0 else list(range(100)) if i==1 else rng.sample(range(100),i%40)
  add('complete_bootstrap','B '+str(len(expansions))+' '+' '.join(map(str,expansions)),o.bootstrap(expansions))
 target=independent_id('duplicate.id')
 for i in range(256):
  archives=[]
  for j in range(i%5):
   ids=[rng.getrandbits(32) for _ in range(i%29)]
   if (i+j)%3!=0:ids+=[target]*(j%3+1)
   ids.sort(key=lambda n:n if n<0x80000000 else n-0x100000000)
   entries=[(id,rng.getrandbits(32),rng.getrandbits(32)) for id in ids]
   archives.append((rng.getrandbits(32),rng.choice([0,1,0xfffffff0,0x1200000]),entries))
  for mask in range(16):lookup(archives,'DuPlicate.id',mask,'lookup_optional_outputs')
  lookup(archives,None,i%16,'null_filename')
  lookup(archives,'missing'+str(i),15,'missing_filename')
 # Read/Open and Exists are deliberately separate original-only observations.
 # Supplied raw/memory/file methods record operations; actual lookup executes.
 for cached in [0,0x1200000]:
  o.setup([(1000,cached,[(independent_id('rules.ini'),23,71)])])
  for loose in [False,True]:
   for handle in [False,True]:
    for name in ['rules.ini','absent.ini']:
     for mode in [0,1,2,3]:
      result,events,position=o.file_decision(name,loose,handle,mode)
      kinds=[e[0] for e in events];assert kinds[0]=='close'
      if mode&2:assert kinds==['close','raw-open']
      elif loose:assert kinds==['close','raw-exists','raw-open']
      elif name=='rules.ini':assert ('memory' if cached else 'archive-open') in kinds and 'raw-open' not in kinds
      else:assert kinds==['close','raw-exists','name','raw-open']
      observations.append({'kind':'open','cached':cached,'loose':loose,'handle':handle,'name':name,'mode':mode,'result':result,'events':events,'position':position})
     result,events,_=o.file_decision(name,loose,handle,1,exists=True)
     kinds=[e[0] for e in events]
     assert kinds==(['handle'] if handle else ['handle','name'] if name=='rules.ini' else ['handle','name','raw-exists'])
     assert result==int(handle or loose or name=='rules.ini')
     observations.append({'kind':'exists','cached':cached,'loose':loose,'handle':handle,'name':name,'result':result,'events':events})
 original_seconds=time.monotonic()-started
 started=time.monotonic();actual=run_native(a.native,commands);native_seconds=time.monotonic()-started
 if actual!=expected:
  for i,(before,after) in enumerate(zip(expected,actual)):
   if before!=after:raise AssertionError(f'Archive mismatch {i}: {commands[i]}\noriginal {before}\nnative {after}')
  raise AssertionError('Archive output count differs')
 report={**identities(fixtures),'evidence_mode':'fresh-original','original_instructions_executed':True,
  'cases':len(commands),'groups':groups,'original_only_assertions':len(observations),'observations':observations,
  'callable_roots':o.calls,'audited_guest_writes':o.audit_writes,
  'original_generation_seconds':original_seconds,'native_comparison_seconds':native_seconds,
  'limits':'plaintext stream/heap services; bootstrap constructor recorder; ASCII CRT; caller/write/input audits; full startup and encrypted parser excluded'}
 evidence={'executable_sha256':digest,'profile':profile,'commands':commands,'expected':expected,'evidence':report}
 write_report(a.exe,work/'expected.json',evidence);report={**report,'expectations_sha256':hash_file(work/'expected.json')}
 write_report(a.exe,work/'report.json',report)
 if a.report:write_report(a.exe,a.report,report)
 print(f'{len(commands):,} {profile} original/native archive results PASS; {len(observations)} separate original-only assertions')
 print(f'Original {original_seconds:.2f}s; native {native_seconds:.2f}s')

if __name__=='__main__':main()
