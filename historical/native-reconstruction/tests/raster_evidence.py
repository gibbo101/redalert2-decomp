# SPDX-License-Identifier: GPL-3.0-or-later
"""Private per-profile raster receipts and identity-checked native replay."""
import json
from pathlib import Path
import subprocess
import sys
from compare_original import EXPECTED, PATCHED_EXPECTED, write_report
from raster_profiles import raster_profile, RETAINED_RASTER_SHA256
from presentation_profiles import RETAINED_RENDER_SHA256, RETAINED_VPL_SHA256
from presentation_evidence import private_path, hash_file, validate_receipt, check_replay_destination

ROOT=Path(__file__).resolve().parents[1]
SOURCES=('original_raster.py','raster_profiles.py','raster_evidence.py','compare_raster.py',
         'original_presentation.py','presentation_profiles.py','presentation_evidence.py')
ASSETS={'htnk.vxl':'0ca8517c29f8bed26c3a3f0138bb36bae01fbb751fc9eaa30bfa1fba352923a2',
        'htnktur.vxl':'4fc6ca0efb803621ae4dc99357f81eb4bc524cc70a90e386831fa0e63a416451',
        'htnkbarl.vxl':'42a3a41fdc52a5491b172bddcd8aac5b9baedec1d7703f95a68a9b96f8531398',
        'voxels.vpl':RETAINED_VPL_SHA256}
sys.path.insert(0,str(ROOT/'tools'))
from verify_raster_mapping import verify
from verify_presentation_mapping import verify as verify_primitives


def source_identities(args):
    return {'oracle_sources':{name:hash_file(ROOT/'tests'/name) for name in SOURCES},
            'mapping_tools':{name:hash_file(ROOT/'tools'/name) for name in
                             ('verify_raster_mapping.py','verify_presentation_mapping.py')},
            'raster_data_sha256':hash_file(args.raster_data),
            'render_data_sha256':hash_file(args.render_data),
            'assets_sha256':{name:hash_file(args.assets/name) for name in ASSETS}}


def prepare(args):
    digest,profile=raster_profile(args.exe.read_bytes(),allow_patched=True)
    native_data=args.native_data_exe or args.exe
    if hash_file(native_data)!=EXPECTED:
        raise ValueError('Retained native raster/render inputs require the disc identity; use --native-data-exe explicitly for patched research')
    if digest==PATCHED_EXPECTED:
        verify(native_data.read_bytes(),args.exe.read_bytes())
        verify_primitives(native_data.read_bytes(),args.exe.read_bytes())
    if hash_file(args.raster_data)!=RETAINED_RASTER_SHA256 or hash_file(args.render_data)!=RETAINED_RENDER_SHA256:
        raise ValueError('Prepared raster/render data must retain the verified disc profile')
    output=ROOT/'private'/'migration'/profile/'raster'
    for path in (output/'expected.json',output/'report.json'):
        private_path(path,args.exe)
        if not args.expectations and path.exists():raise ValueError('Fresh raster evidence already exists; use --expectations for replay')
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
    if actual!=evidence['expected']:raise AssertionError('Cached original/native raster comparison differs')
    report={**evidence['evidence'],**current,'evidence_mode':'cached-original-replay',
            'original_instructions_executed':False,'expectations_sha256':hash_file(source),'cases':len(actual)}
    write_report(args.exe,destination,report)
    print(f'{len(actual)} identity-checked {profile} raster results: PASS (native replay; no original execution)')
