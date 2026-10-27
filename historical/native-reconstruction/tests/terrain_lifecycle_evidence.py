# SPDX-License-Identifier: GPL-3.0-or-later
"""Private occupation/lifecycle receipts and identity-checked native replay."""
import json
from pathlib import Path
import subprocess
import sys
import time
from compare_original import EXPECTED, PATCHED_EXPECTED, write_report
from terrain_lifecycle_profiles import terrain_lifecycle_profile
from presentation_profiles import RETAINED_RENDER_SHA256
from raster_profiles import RETAINED_RASTER_SHA256
from presentation_evidence import private_path, hash_file, validate_receipt, check_replay_destination
from scenery_evidence import SOURCES as INHERITED_SOURCES, ASSETS as SCENERY_ASSETS

ROOT=Path(__file__).resolve().parents[1]
SOURCES=tuple(dict.fromkeys(('original_occupation.py','original_lifecycle.py',
                            'terrain_lifecycle_profiles.py','terrain_lifecycle_evidence.py',
                            'compare_occupation.py','compare_lifecycle.py',*INHERITED_SOURCES)))
# Contents plus filenames pin the 51-type enumeration used by both suites.
ASSETS=SCENERY_ASSETS
NATIVE_SOURCES=('tests/occupation_vectors.cpp','tests/lifecycle_vectors.cpp',
                'src/sim/ObjectLayers.cpp','src/sim/ObjectLayers.hpp',
                'src/sim/TerrainLifecycle.cpp','src/sim/TerrainLifecycle.hpp',
                'src/sim/TerrainOccupation.cpp','src/sim/TerrainOccupation.hpp')
sys.path.insert(0,str(ROOT/'tools'))
from verify_terrain_lifecycle_mapping import verify
from verify_composition_mapping import verify as verify_composition
from verify_raster_mapping import verify as verify_raster
MAPPING_TOOLS=('verify_terrain_lifecycle_mapping.py','verify_composition_mapping.py','verify_raster_mapping.py')


def source_identities(args):
    return {'oracle_sources':{name:hash_file(ROOT/'tests'/name) for name in SOURCES},
            'native_sources':{name:hash_file(ROOT/name) for name in NATIVE_SOURCES},
            'mapping_tools':{name:hash_file(ROOT/'tools'/name) for name in MAPPING_TOOLS},
            'render_data_sha256':hash_file(args.render_data),'raster_data_sha256':hash_file(args.raster_data),
            'exporter_sha256':hash_file(args.exporter),'cell_exporter_sha256':hash_file(args.cell_exporter),
            'assets_sha256':{name:hash_file(args.assets/name) for name in ASSETS}}


def prepare(args):
    if args.suite not in ('occupation','lifecycle'):raise ValueError('Unknown terrain/lifecycle suite')
    digest,profile=terrain_lifecycle_profile(args.exe.read_bytes(),allow_patched=True)
    native_data=args.native_data_exe or args.exe
    if hash_file(native_data)!=EXPECTED:
        raise ValueError('Retained native terrain/lifecycle inputs require the disc identity; use --native-data-exe explicitly for patched research')
    if digest==PATCHED_EXPECTED:
        disc,patched=native_data.read_bytes(),args.exe.read_bytes()
        verify(disc,patched);verify_composition(disc,patched);verify_raster(disc,patched)
    if hash_file(args.render_data)!=RETAINED_RENDER_SHA256 or hash_file(args.raster_data)!=RETAINED_RASTER_SHA256:
        raise ValueError('Prepared render/raster data must retain the verified disc profile')
    output=ROOT/'private'/'migration'/profile/args.suite
    for path in (output/'expected.json',output/'report.json'):
        private_path(path,args.exe)
        if not args.expectations and path.exists():raise ValueError('Fresh terrain/lifecycle evidence already exists; use --expectations for replay')
    if args.report:
        private_path(args.report,args.exe)
        if args.report.resolve()==(output/'expected.json').resolve():raise ValueError('Report cannot replace original expectations')
        if args.report.exists() and not args.expectations:
            prior=json.loads(args.report.read_text())
            if prior.get('evidence_mode')=='fresh-original' or 'commands' in prior:raise ValueError('Fresh report cannot replace original evidence')
    args.assets=output/'assets';private_path(args.assets,args.exe)
    if args.assets.resolve().is_relative_to(args.data_dir.resolve()):raise ValueError('Research export must be outside the supplied asset installation')
    subprocess.run([str(args.exporter),'--export',str(args.data_dir),str(args.assets)],check=True)
    if {name:hash_file(args.assets/name) for name in ASSETS}!=ASSETS:raise ValueError('Assets must match retained supplied inputs; patched precedence is not promoted')
    args.research_identities=source_identities(args)
    args.research_native_sha256=hash_file(args.native)
    return digest,profile,native_data,output


def identities(args,digest,profile,native_data):
    selected=terrain_lifecycle_profile(args.exe.read_bytes(),allow_patched=True)
    if selected!=(digest,profile):raise ValueError('Original engine/profile identity differs')
    current=source_identities(args)
    if current!=args.research_identities:raise ValueError('Oracle sources/prepared inputs changed during this run')
    if hash_file(args.exe)!=digest or hash_file(native_data)!=EXPECTED:raise ValueError('Executable inputs changed during this run')
    if hash_file(args.native)!=args.research_native_sha256:raise ValueError('Native runner changed during this run')
    return {'executable_sha256':digest,'profile':profile,'native_data_executable_sha256':EXPECTED,
            'native_sha256':hash_file(args.native),**current,'suite':args.suite,'runtime_profile_promoted':False}


def run_native(args,commands):
    argv=[str(args.native)]
    if args.suite=='lifecycle':argv += [str(args.render_data),str(args.raster_data)]
    proc=subprocess.run(argv,input='\n'.join(commands)+'\n',text=True,capture_output=True,check=True)
    return [line.split() for line in proc.stdout.splitlines()]


def save(args,output,commands,expected,report):
    report['evidence_mode']='fresh-original';report['original_instructions_executed']=True
    destination=output/'expected.json'
    evidence={'executable_sha256':report['executable_sha256'],'profile':report['profile'],
              'commands':commands,'expected':expected,'evidence':report}
    write_report(args.exe,destination,evidence)
    report['expectations_sha256']=hash_file(destination)
    write_report(args.exe,output/'report.json',report)
    if args.report and args.report.resolve()!=(output/'report.json').resolve():write_report(args.exe,args.report,report)


IDENTITY_FIELDS=('executable_sha256','profile','native_data_executable_sha256','oracle_sources',
                 'native_sources','mapping_tools','render_data_sha256','raster_data_sha256',
                 'exporter_sha256','cell_exporter_sha256','assets_sha256','suite')
def validate_cached(evidence,current):
    for field in IDENTITY_FIELDS:
        if evidence['evidence'].get(field)!=current.get(field):raise ValueError('Cached original identity differs: '+field)
    if any(evidence.get(f)!=current[f] for f in ('executable_sha256','profile')):raise ValueError('Cached original envelope identity differs')


def replay(args,digest,profile,native_data,output):
    source=private_path(args.expectations,args.exe)
    evidence=json.loads(source.read_text());receipt=private_path(source.parent/'report.json',args.exe)
    validate_receipt(evidence,json.loads(receipt.read_text()),hash_file(source))
    destination=args.report or output/'replay-report.json'
    check_replay_destination(destination,source,receipt)
    current=identities(args,digest,profile,native_data);validate_cached(evidence,current)
    started=time.monotonic();actual=run_native(args,evidence['commands']);elapsed=time.monotonic()-started
    current=identities(args,digest,profile,native_data);validate_cached(evidence,current)
    if actual!=evidence['expected']:raise AssertionError('Cached original/native terrain/lifecycle comparison differs')
    report={**evidence['evidence'],**current,'evidence_mode':'cached-original-replay',
            'original_instructions_executed':False,'expectations_sha256':hash_file(source),
            'cases':len(actual),'native_comparison_seconds':elapsed}
    write_report(args.exe,destination,report)
    print(f'{len(actual):,} identity-checked {profile} {args.suite} results: PASS (native replay; no original execution)')
