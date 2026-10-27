# SPDX-License-Identifier: GPL-3.0-or-later
"""Private, profile-specific presentation evidence and guarded native replay."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys
from compare_original import EXPECTED, PATCHED_EXPECTED, write_report
from presentation_profiles import presentation_profile, RETAINED_RENDER_SHA256, RETAINED_VPL_SHA256

ROOT=Path(__file__).resolve().parents[1]
SOURCES=('original_presentation.py','presentation_profiles.py','presentation_evidence.py','compare_presentation.py')
sys.path.insert(0,str(ROOT/'tools'))
from verify_presentation_mapping import verify


def hash_file(path):return hashlib.sha256(path.read_bytes()).hexdigest()


def private_path(path,source):
    path=path.absolute()
    if any(p.is_symlink() for p in (path,*path.parents)):
        raise ValueError('Symlink evidence paths are refused')
    path=path.resolve()
    if path.is_relative_to(source.resolve().parent):
        raise ValueError('Evidence must be outside the source installation')
    if not any(path.is_relative_to(ROOT/name) for name in ('private','build')):
        raise ValueError('Evidence must stay under private/ or build/')
    return path


def source_identities(args):
    return {'oracle_sources':{name:hash_file(ROOT/'tests'/name) for name in SOURCES},
            'mapping_tool_sha256':hash_file(ROOT/'tools/verify_presentation_mapping.py'),
            'render_data_sha256':hash_file(args.render_data),'vpl_sha256':hash_file(args.vpl)}


def prepare(args):
    digest,profile=presentation_profile(args.exe.read_bytes(),allow_patched=True)
    native_data=args.native_data_exe or args.exe
    if hash_file(native_data)!=EXPECTED:
        raise ValueError('Retained native render inputs require the disc identity; use --native-data-exe explicitly for patched research')
    if digest==PATCHED_EXPECTED:
        verify(native_data.read_bytes(),args.exe.read_bytes())
    if hash_file(args.render_data)!=RETAINED_RENDER_SHA256:
        raise ValueError('Render data must retain the verified disc profile')
    output=ROOT/'private'/'migration'/profile/'presentation'
    private_path(output/'expected.json',args.exe)
    if args.report:private_path(args.report,args.exe)
    if args.vpl is None:
        args.vpl=output/'voxels.vpl'
        private_path(args.vpl,args.exe)
        if args.vpl.resolve().is_relative_to(args.data_dir.resolve()):
            raise ValueError('VPL research export must be outside the asset installation')
        subprocess.run([str(args.native),'--export-vpl',str(args.data_dir),str(args.vpl)],check=True)
    if hash_file(args.vpl)!=RETAINED_VPL_SHA256:
        raise ValueError('VPL must match the retained supplied input; asset precedence is not promoted')
    args.research_identities=source_identities(args)
    args.research_native_sha256=hash_file(args.native)
    return digest,profile,native_data,output


def identities(args,digest,profile,native_data):
    current=source_identities(args)
    if current!=args.research_identities:
        raise ValueError('Oracle sources/prepared inputs changed during this run')
    if hash_file(args.exe)!=digest or hash_file(native_data)!=EXPECTED:
        raise ValueError('Executable inputs changed during this run')
    if hash_file(args.native)!=args.research_native_sha256:
        raise ValueError('Native runner changed during this run')
    return {'executable_sha256':digest,'profile':profile,
            'native_data_executable_sha256':EXPECTED,'native_sha256':hash_file(args.native),
            **current,'runtime_profile_promoted':False}


def save(args,output,commands,expected,labels,report):
    report['evidence_mode']='fresh-original';report['original_instructions_executed']=True
    destination=output/'expected.json'
    if args.report and args.report.resolve()==destination.resolve():
        raise ValueError('Report cannot replace original expectations')
    evidence={'executable_sha256':report['executable_sha256'],'profile':report['profile'],
              'commands':commands,'expected':expected,'labels':labels,'evidence':report}
    write_report(args.exe,destination,evidence)
    report['expectations_sha256']=hash_file(destination)
    write_report(args.exe,output/'report.json',report)
    if args.report and args.report.resolve()!=(output/'report.json').resolve():
        write_report(args.exe,args.report,report)


def validate_cached(evidence,current):
    fields=('executable_sha256','profile','native_data_executable_sha256','oracle_sources',
            'mapping_tool_sha256','render_data_sha256','vpl_sha256')
    for field in fields:
        if evidence['evidence'].get(field)!=current.get(field):
            raise ValueError('Cached original evidence identity differs: '+field)
    if any(evidence.get(f)!=current[f] for f in ('executable_sha256','profile')):
        raise ValueError('Cached original envelope identity differs')


def validate_receipt(evidence,receipt,fingerprint):
    if receipt.get('evidence_mode')!='fresh-original' or receipt.get('expectations_sha256')!=fingerprint:
        raise ValueError('Cached original expectation fingerprint differs from fresh receipt')
    if {k:v for k,v in receipt.items() if k!='expectations_sha256'}!=evidence['evidence']:
        raise ValueError('Cached original evidence differs from fresh receipt')


def check_replay_destination(destination,expectations,receipt):
    destination=destination.resolve()
    if destination in (expectations.resolve(),receipt.resolve()):
        raise ValueError('Replay report cannot replace original expectations or fresh receipt')
    if destination.exists():
        prior=json.loads(destination.read_text())
        if prior.get('evidence_mode')=='fresh-original' or 'commands' in prior:
            raise ValueError('Replay report cannot replace fresh original evidence')


def replay(args,digest,profile,native_data,output):
    source=private_path(args.expectations,args.exe)
    evidence=json.loads(source.read_text());receipt_path=private_path(source.parent/'report.json',args.exe)
    validate_receipt(evidence,json.loads(receipt_path.read_text()),hash_file(source))
    destination=args.report or output/'replay-report.json'
    check_replay_destination(destination,source,receipt_path)
    current=identities(args,digest,profile,native_data);validate_cached(evidence,current)
    proc=subprocess.run([str(args.native),str(args.render_data),str(args.vpl)],
                        input='\n'.join(evidence['commands'])+'\n',text=True,capture_output=True,check=True)
    current=identities(args,digest,profile,native_data)
    actual=[[int(n) for n in line.split()] for line in proc.stdout.splitlines()]
    if actual!=evidence['expected']:
        mismatch=next((i for i,pair in enumerate(zip(actual,evidence['expected'])) if pair[0]!=pair[1]),min(len(actual),len(evidence['expected'])))
        raise AssertionError(f'Cached original/native comparison differs at result {mismatch}')
    report={**evidence['evidence'],**current,'evidence_mode':'cached-original-replay',
            'original_instructions_executed':False,'expectations_sha256':hash_file(source),
            'cases':len(actual),'matched_values':sum(map(len,actual))}
    write_report(args.exe,destination,report)
    print(f'{len(actual):,} identity-checked {profile} presentation cases / {report["matched_values"]:,} values: PASS (native replay; no original execution)')
