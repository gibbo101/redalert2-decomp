# SPDX-License-Identifier: GPL-3.0-or-later
"""Private per-profile composition receipts and identity-checked native replay."""
import json
from pathlib import Path
import subprocess
import sys
from compare_original import EXPECTED, PATCHED_EXPECTED, write_report
from composition_profiles import composition_profile
from raster_profiles import RETAINED_RASTER_SHA256
from presentation_profiles import RETAINED_RENDER_SHA256
from presentation_evidence import private_path, hash_file, validate_receipt, check_replay_destination

ROOT=Path(__file__).resolve().parents[1]
SOURCES=('original_composition.py','composition_profiles.py','composition_evidence.py','compare_composition.py',
         'original_raster.py','raster_profiles.py','original_presentation.py','presentation_profiles.py',
         'presentation_evidence.py','original_movement.py','movement_profiles.py','compare_original.py')
ASSETS={'clear01.tem':'d90df76d78fd9a3e23834c5a728cef666dbdf65b212dd3a66c29b456cbd51ed2',
        'cliff01.tem':'035d8580b5118c631055143ce722d1995b50d3b1df495beef8449e01425d21b1',
        'slope01.tem':'9ef7381215649ca65d315e47f8ae4fb611ab7397f779527d8e026fafaf6e3a8d'}
sys.path.insert(0,str(ROOT/'tools'))
from verify_composition_mapping import verify
from verify_raster_mapping import verify as verify_raster
from verify_movement_mapping import verify as verify_movement
from verify_presentation_mapping import verify as verify_primitives


def source_identities(args):
    return {'oracle_sources':{name:hash_file(ROOT/'tests'/name) for name in SOURCES},
            'mapping_tools':{name:hash_file(ROOT/'tools'/name) for name in
                             ('verify_composition_mapping.py','verify_raster_mapping.py','verify_presentation_mapping.py',
                              'verify_movement_mapping.py')},
            'raster_data_sha256':hash_file(args.raster_data),
            'render_data_sha256':hash_file(args.render_data),
            'assets_sha256':{name:hash_file(args.assets/name) for name in ASSETS}}


def prepare(args):
    digest,profile=composition_profile(args.exe.read_bytes(),allow_patched=True)
    native_data=args.native_data_exe or args.exe
    if hash_file(native_data)!=EXPECTED:
        raise ValueError('Retained native composition inputs require the disc identity; use --native-data-exe explicitly for patched research')
    if digest==PATCHED_EXPECTED:
        verify(native_data.read_bytes(),args.exe.read_bytes())
        verify_primitives(native_data.read_bytes(),args.exe.read_bytes())
        verify_raster(native_data.read_bytes(),args.exe.read_bytes())
        verify_movement(native_data.read_bytes(),args.exe.read_bytes())
    if hash_file(args.raster_data)!=RETAINED_RASTER_SHA256 or hash_file(args.render_data)!=RETAINED_RENDER_SHA256:
        raise ValueError('Prepared raster/render data must retain the verified disc profile')
    output=ROOT/'private'/'migration'/profile/'composition'
    for path in (output/'expected.json',output/'report.json'):
        private_path(path,args.exe)
        if not args.expectations and path.exists():raise ValueError('Fresh composition evidence already exists; use --expectations for replay')
    if args.report:private_path(args.report,args.exe)
    args.assets=output/'assets';private_path(args.assets,args.exe)
    if args.assets.resolve().is_relative_to(args.data_dir.resolve()):
        raise ValueError('Research export must be outside the supplied asset installation')
    subprocess.run([str(args.native),'--export',str(args.data_dir),str(args.assets)],check=True)
    if {name:hash_file(args.assets/name) for name in ASSETS}!=ASSETS:
        raise ValueError('Assets must match retained supplied inputs; patched precedence is not promoted')
    args.research_identities=source_identities(args)
    args.research_native_sha256=hash_file(args.native)
    return digest,profile,native_data,output


def identities(args,digest,profile,native_data):
    current=source_identities(args)
    if current!=args.research_identities:raise ValueError('Oracle sources/prepared inputs changed during this run')
    if hash_file(args.exe)!=digest or hash_file(native_data)!=EXPECTED:raise ValueError('Executable inputs changed during this run')
    if hash_file(args.native)!=args.research_native_sha256:raise ValueError('Native runner changed during this run')
    return {'executable_sha256':digest,'profile':profile,'native_data_executable_sha256':EXPECTED,
            'native_sha256':hash_file(args.native),**current,'runtime_profile_promoted':False}


def run_native(args,commands):
    proc=subprocess.run([str(args.native),str(args.raster_data),str(args.render_data)],
                        input='\n'.join(commands)+'\n',text=True,capture_output=True,check=True)
    return [line.split() for line in proc.stdout.splitlines()]


def save(args,output,commands,expected,labels,report):
    destination=output/'expected.json'
    if args.report and args.report.resolve()==destination.resolve():raise ValueError('Report cannot replace original expectations')
    report['evidence_mode']='fresh-original';report['original_instructions_executed']=True
    evidence={'executable_sha256':report['executable_sha256'],'profile':report['profile'],
              'commands':commands,'expected':expected,'labels':labels,'evidence':report}
    write_report(args.exe,destination,evidence)
    report['expectations_sha256']=hash_file(destination)
    write_report(args.exe,output/'report.json',report)
    if args.report and args.report.resolve()!=(output/'report.json').resolve():
        write_report(args.exe,args.report,report)


def validate_cached(evidence,current):
    for field in ('executable_sha256','profile','native_data_executable_sha256','oracle_sources',
                  'mapping_tools','raster_data_sha256','render_data_sha256','assets_sha256'):
        if evidence['evidence'].get(field)!=current.get(field):raise ValueError('Cached original identity differs: '+field)
    if any(evidence.get(f)!=current[f] for f in ('executable_sha256','profile')):raise ValueError('Cached original envelope identity differs')


def replay(args,digest,profile,native_data,output):
    source=private_path(args.expectations,args.exe)
    evidence=json.loads(source.read_text());receipt=private_path(source.parent/'report.json',args.exe)
    validate_receipt(evidence,json.loads(receipt.read_text()),hash_file(source))
    destination=args.report or output/'replay-report.json'
    check_replay_destination(destination,source,receipt)
    current=identities(args,digest,profile,native_data);validate_cached(evidence,current)
    actual=run_native(args,evidence['commands'])
    current=identities(args,digest,profile,native_data)
    if actual!=evidence['expected']:raise AssertionError('Cached original/native composition comparison differs')
    report={**evidence['evidence'],**current,'evidence_mode':'cached-original-replay',
            'original_instructions_executed':False,'expectations_sha256':hash_file(source),'cases':len(actual)}
    write_report(args.exe,destination,report)
    print(f'{len(actual)} identity-checked {profile} composition results: PASS (native replay; no original execution)')
