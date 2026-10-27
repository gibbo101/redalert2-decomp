#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare runtime-owned prepared Cells against one isolated original map parent."""
import configparser
import argparse
import hashlib
import json
import subprocess
import time
from pathlib import Path
import compare_resident_map_floor as parent
from presentation_evidence import hash_file, validate_receipt, private_path, check_replay_destination
from compare_original import PATCHED_EXPECTED, write_report
from compare_terrain_visibility import ROOT


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--data-dir',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/terrain-runtime-check')
    p.add_argument('--output',type=Path)
    p.add_argument('--expectations',type=Path)
    p.add_argument('--report',type=Path)
    a=p.parse_args();start=time.monotonic()
    fixture=ROOT/'private/map-depth-1006/resident-floor-v1/expected.json'
    manifest=ROOT/'private/map-depth-1006/resident-fixture-v1/manifest.json'
    old=json.loads(fixture.read_text());validate_receipt(old,json.loads((fixture.parent/'report.json').read_text()),hash_file(fixture))
    if hash_file(a.exe)!=PATCHED_EXPECTED:raise ValueError('Exact supplied base executable required')
    label='owned_all_positions_actual_floor_cliff_2';index=old['labels'].index(label)
    values=list(parent.parse(old['commands'][index]));args=list(values[5:]);args[-1]=[]
    # Keep all fixture map/TMP/type inputs. Only the supplied building registry
    # changes to the demo's empty registry. No final state enters the runtime.
    command=parent.command(*values[:5],args)
    sources=set(parent.SOURCES)|{str(x.relative_to(ROOT)) for x in (ROOT/'src').rglob('*') if x.suffix in ('.cpp','.hpp')}
    sources|={'tests/compare_terrain_runtime.py','tests/terrain_runtime_check.cpp','tools/prepare_map_runtime_data.py','CMakeLists.txt','tests/test_prepare_map_runtime_data.py','test.command'}
    def snapshot():
        return {'engine_sha256':hash_file(a.exe),'fixture_sha256':hash_file(fixture),'manifest_sha256':hash_file(manifest),
                'sources':{s:hash_file(ROOT/s) for s in sorted(sources)},'inspection':parent.verify(a.exe.read_bytes()),
                'prepared_data':{n:hash_file(ROOT/'private/derived/ra2-1006'/n) for n in ('map-runtime-data.bin','ramp-geometry-data.bin','ramp-pose-data.bin')}}
    identities=snapshot();native_hash=hash_file(a.native)
    proc=subprocess.run([str(a.native),str(a.data_dir),'--inputs'],text=True,capture_output=True,check=True)
    inputs=dict(line.split() for line in proc.stdout.splitlines())
    records=json.loads(manifest.read_text())['files']
    ini=configparser.ConfigParser(interpolation=None);ini.read(manifest.parent/'temperat.ini',encoding='latin1')
    names=[]
    for i in range(1024):
        section=f'TileSet{i:04d}'
        if not ini.has_section(section):break
        names.extend((ini.get(section,'FileName')+f'{j:02d}.tem').lower() for j in range(1,ini.getint(section,'TilesInSet')+1))
    required={'mp03t4.map','rules.ini','temperat.ini'}|{names[i] for i,t in enumerate(args[2]) if t[0]}
    if set(inputs)!=required|{'art.ini'}:raise ValueError('Runtime resident file selection differs')
    for name in sorted(required):
        if inputs[name]!=records[name]['sha256']:raise ValueError('Runtime input differs from original fixture: '+name)
    fresh=not bool(a.expectations);generation=0
    if fresh:
        if not a.output or a.report:raise ValueError('Fresh proof requires --output only')
        out=private_path(a.output,a.exe)
        if out.exists():raise ValueError('Use a new private evidence directory')
        from original_resident_map_floor import ResidentMapFloorOracle
        oracle=ResidentMapFloorOracle(a.exe);now=time.monotonic();expected=oracle.run_floor(*parent.parse(command));generation=time.monotonic()-now
        metadata={'audited_roots':oracle.audit_calls,'actual_entries':oracle.entries,'selected_stores':oracle.stores}
        report=out/'report.json'
    else:
        source=private_path(a.expectations,a.exe);old_proof=json.loads(source.read_text());validate_receipt(old_proof,json.loads((source.parent/'report.json').read_text()),hash_file(source))
        if old_proof['identities']!=identities or old_proof['command']!=command or old_proof['inputs']!=inputs:raise ValueError('Runtime proof inputs/sources differ')
        expected=old_proof['expected'];metadata=old_proof['metadata'];report=private_path(a.report or source.parent/'replay.json',a.exe)
        check_replay_destination(report,source,source.parent/'report.json')
    proc=subprocess.run([str(a.native),str(a.data_dir),'--projection'],text=True,capture_output=True,check=True)
    if proc.stdout.strip()!=expected[0]:raise AssertionError('Runtime prepared map differs from exact original: '+proc.stdout.strip()+' != '+expected[0])
    if identities!=snapshot() or native_hash!=hash_file(a.native):raise ValueError('Proof inputs changed during run')
    proof={'identities':identities,'command':command,'expected':expected,'inputs':inputs,'metadata':metadata}
    result={**proof,'native_sha256':native_hash,
        'original_instructions_executed':fresh,'evidence_mode':'fresh-original' if fresh else 'cached-original-replay',
        'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start,'cells':13515,
        'boundary':'Selected map fields only; host parsers, initial records, primary TMP and raw overlay placement supplied. Empty building registry. No full startup/frame parity.'}
    if fresh:
        source=out/'expected.json';write_report(a.exe,source,{**proof,'evidence':result})
    write_report(a.exe,report,{**result,'expectations_sha256':hash_file(source)})
    print(f'13,515 runtime Cells / {len(inputs)} source slices match original projection: PASS; original {generation:.3f}s, total {time.monotonic()-start:.3f}s')
if __name__=='__main__':main()
