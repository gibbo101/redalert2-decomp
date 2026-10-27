#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Audit initial native registration and effective owned prototype inputs privately.
Original Offset executes on decoded-index fixtures; encryption/OS/lifetime excluded.
"""
import argparse,hashlib,json,shlex,subprocess,sys
from pathlib import Path
from archive_profiles import archive_profile
from presentation_evidence import private_path,hash_file
from compare_archive_sequence import sources as stage_sources
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'tools'))
from verify_archive_sequence_mapping import verify
from verify_archive_startup_order import verify as verify_order
from inspect_patch import write_report
SOURCES=('tests/original_archive_effective.py','tests/compare_archive_effective.py','tools/archive_inspect.cpp')
def sources():return {**stage_sources(),**{p:hash_file(ROOT/p) for p in SOURCES}}

def collect(native,data,map_name):
 p=subprocess.run([str(native),str(data),'--prototype-inputs',map_name],capture_output=True,text=True,check=True)
 archives=[];queries=[]
 for line in p.stdout.splitlines():
  row=shlex.split(line)
  if row[0]=='A':
   ordinal,offset,body,size,count=map(int,[row[1],*row[4:8]])
   if ordinal!=len(archives) or len(row)!=8+count*3:raise ValueError('Malformed archive inspector index')
   archives.append({'name':row[2],'file':row[3],'offset':offset,'body_offset':body,'body_size':size,
                    'entries':[list(map(int,row[i:i+3])) for i in range(8,len(row),3)]})
  elif row[0]=='Q':queries.append({'name':row[1],'archived':bool(int(row[2])),'archive':int(row[3]),'file':row[4],
                                   'offset':int(row[5]),'length':int(row[6]),'sha256':row[7]})
  else:raise ValueError('Missing or malformed prototype input: '+line)
 return archives,queries

def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--data-dir',type=Path,required=True)
 p.add_argument('--map',default='mp03t4.map');p.add_argument('--native',type=Path,default=ROOT/'build/native/archive-inspect')
 p.add_argument('--disc',type=Path,default=ROOT/'private/disc-allied/game.exe');p.add_argument('--patched',type=Path,default=ROOT/'private/official-1006-probe/game.exe')
 p.add_argument('--report',type=Path,required=True);a=p.parse_args();digest,profile=archive_profile(a.exe.read_bytes())
 destination=private_path(a.report,a.exe)
 if destination.is_relative_to(a.data_dir.resolve()):raise ValueError('Evidence must stay outside owned asset inputs')
 if destination.exists():raise ValueError('Effective-input receipt exists')
 verify(a.disc.read_bytes(),a.patched.read_bytes());order=verify_order(a.exe.read_bytes());initial_sources=sources();native_hash=hash_file(a.native)
 # Pin every root file before resolving and recheck all after original comparison.
 initial_files={str(p):hash_file(p) for p in sorted(a.data_dir.iterdir()) if p.is_file()}
 archives,queries=collect(a.native,a.data_dir,a.map)
 from original_archive_effective import EffectiveArchiveOracle
 from original_archive_sequence import ArchiveSequenceOracle
 o=EffectiveArchiveOracle(a.exe);o.setup_decoded(archives);s=ArchiveSequenceOracle(a.exe)
 root_names={Path(path).name.lower() for path in initial_files};bootstrap=s.bootstrap([n for n in range(100) if f'expand{n:02d}.mix' in root_names])
 # Available nested files are resolved from supplied native indexes. Constructor
 # services are recorders; this composes verified requests/lookup, not startup parity.
 names={r['name'] for r in archives};maps=sorted(n for n in root_names if n.startswith('maps') and n.endswith('.mix'))
 movies=sorted(n for n in root_names if n.startswith('movies') and n.endswith('.mix'))
 startup,events=s.startup(1,0,names,maps,movies);theater,theater_events=s.theater(0,-1)
 requested=(['language.mix'] if 'language.mix' in root_names else [])+bootstrap+startup[2:]+theater[1:]
 retained=[name for name in requested if name in names]
 if retained!=[r['name'] for r in archives]:raise AssertionError('Native initial registration differs from original stage requests')
 for q in queries:
  file=Path(q['file']);data=file.read_bytes();selected=data[q['offset']:q['offset']+q['length']]
  if len(selected)!=q['length'] or hashlib.sha256(selected).hexdigest()!=q['sha256']:raise AssertionError('Physical source slice differs')
  if q['archived']:
   result=o.lookup(q['name'])
   if result[0]!=1 or result[2]!=q['archive'] or result[3]!=q['offset'] or result[4]!=q['length']:raise AssertionError('Original Offset source/offset/length differs: '+q['name'])
  else:
   if q['name'].lower() not in root_names or q['offset']!=0:raise AssertionError('Loose file provenance differs')
   result,events,_=o.file_decision(q['name'],loose=True)
   if not result or [e[0] for e in events]!=['close','raw-exists','raw-open']:raise AssertionError('Original loose read decision differs')
 if digest!=hash_file(a.exe) or initial_sources!=sources() or native_hash!=hash_file(a.native):raise ValueError('Effective source/engine/native changed')
 if initial_files!={str(p):hash_file(p) for p in sorted(a.data_dir.iterdir()) if p.is_file()}:raise ValueError('Owned source files changed')
 report={'executable_sha256':digest,'profile':profile,'evidence_mode':'fresh-original-decoded-index-fixtures','original_instructions_executed':True,
  'sources':initial_sources,'native_sha256':native_hash,'owned_root_files':initial_files,'map':a.map,'archives':archives,'queries':queries,
  'query_count':len(queries),'archived_queries':sum(q['archived'] for q in queries),'lookup_roots':o.calls,'lookup_guest_writes':o.audit_writes,
  'stage_roots':s.calls,'stage_guest_writes':s.audit_writes,'startup_order_inspection':order,'runtime_profile_promoted':False,
  'limits':'native-decoded indexes; successful stage constructor recorders; sorted host enumeration; missing movie data omitted; original Offset/loose Open and physical source slices only, no original encrypted parse or full startup/lifetime'}
 write_report(a.exe,destination,report);print(f'{len(queries)} {profile} effective-source queries PASS on decoded-index original fixtures; runtime unpromoted')
if __name__=='__main__':main()
