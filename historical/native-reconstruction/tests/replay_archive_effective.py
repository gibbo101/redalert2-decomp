#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Identity-checked native replay of private decoded-index original fixture results."""
import argparse,json
from pathlib import Path
from compare_archive_effective import collect,sources
from archive_profiles import archive_profile
from presentation_evidence import private_path,hash_file
from inspect_patch import write_report

def validate(evidence,digest,profile,source_ids,files):
 if evidence.get('evidence_mode')!='fresh-original-decoded-index-fixtures':raise ValueError('Replay requires fresh original decoded-index evidence')
 for key,value in [('executable_sha256',digest),('profile',profile),('sources',source_ids),('owned_root_files',files)]:
  if evidence.get(key)!=value:raise ValueError('Effective replay identity differs: '+key)

def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--data-dir',type=Path,required=True)
 p.add_argument('--native',type=Path,required=True);p.add_argument('--expectations',type=Path,required=True);p.add_argument('--report',type=Path,required=True)
 a=p.parse_args();digest,profile=archive_profile(a.exe.read_bytes());source=private_path(a.expectations,a.exe);destination=private_path(a.report,a.exe)
 if destination==source or destination.exists() or destination.is_relative_to(a.data_dir.resolve()):raise ValueError('Replay cannot replace evidence or source inputs')
 fingerprint=hash_file(source);evidence=json.loads(source.read_text());source_ids=sources();native_hash=hash_file(a.native)
 def files():return {str(p):hash_file(p) for p in sorted(a.data_dir.iterdir()) if p.is_file()}
 before=files();validate(evidence,digest,profile,source_ids,before)
 archives,queries=collect(a.native,a.data_dir,evidence['map'])
 if archives!=evidence['archives'] or queries!=evidence['queries']:raise AssertionError('Effective native replay differs from original fixture evidence')
 validate(evidence,*archive_profile(a.exe.read_bytes()),sources(),files())
 if native_hash!=hash_file(a.native) or fingerprint!=hash_file(source):raise ValueError('Native/expectation changed during replay')
 report={**evidence,'evidence_mode':'cached-original-decoded-index-replay','original_instructions_executed':False,
         'native_sha256':native_hash,'expectations_sha256':fingerprint,'replay_source_sha256':hash_file(Path(__file__))}
 write_report(a.exe,destination,report);print(f"{len(queries)} {profile} effective-source native replay PASS; no original execution")
if __name__=='__main__':main()
