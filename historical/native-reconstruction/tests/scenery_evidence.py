# SPDX-License-Identifier: GPL-3.0-or-later
"""Private per-profile scenery receipts and identity-checked native replay."""
import json
from pathlib import Path
import subprocess
import sys
from compare_original import EXPECTED, PATCHED_EXPECTED, write_report
from scenery_profiles import scenery_profile
from presentation_profiles import RETAINED_RENDER_SHA256
from presentation_evidence import private_path, hash_file, validate_receipt, check_replay_destination

ROOT=Path(__file__).resolve().parents[1]
from unit_light_evidence import SOURCES as INHERITED_SOURCES
SOURCES=tuple(dict.fromkeys(('original_scenery.py','original_props.py','original_terrain_types.py',
                            'scenery_profiles.py','scenery_evidence.py','compare_scenery.py',
                            'compare_props.py','compare_terrain_types.py',*INHERITED_SOURCES)))
ASSETS={
    'art.ini': 'b477f861063a9509e87b7836b78190204c73bea5ea5595a842c456f5920ea223',
    'hdstn01.tem': '6dcc654bf666c8ec9d2e2a13e97c6b35cccbcf8e2a0e3a1cb033f32d69c22c7f',
    'isotem.pal': '5d6e40fcd11a592a31494c635d93c21796cfe86a2743f0258b1f7d0aff850795',
    'lt_eur01.tem': 'dc3295b7f2bf9cef88ffce94e75b5c248f1a8be334a45d8c2035735ad34c1f1e',
    'lt_eur02.tem': 'ca4dcd435918313a1fa82bdb43e7343a1018142cd45efe1b0b76dd84011c7fd5',
    'lt_gen01.tem': '84ff28cbee302987f2798eb3aa4bfebaf993c4530fd86c337cd1533f0acd2597',
    'lt_gen02.tem': '20346c9721f9b530f7a74aacd23877fd56ee1563ea7f163186b6ca2e0a798b1e',
    'lt_gen03.tem': '5d9d2be40744154bb0785853f78bdc33518d5ab1c5a092d3ec590894610962e3',
    'lt_gen04.tem': 'de4d9cefaaa641e1a24c725fb12077dcc7d088366e1d8fbe8f4814147e8a2bb7',
    'lt_sgn01.tem': 'a4c99a1aba5bb744a7c3a197e610e906650152b94fc5d5fa9135d7c74b41560a',
    'lt_sgn02.tem': '1491a5e4f71cf8981086ac07de7cc637906f02a4ffd7c67e4685b5783acca5af',
    'lt_sgn03.tem': '99cb06f1ece13d0a4283aa256d56a72f677ce66ad5b991492b7b520d9c4680d8',
    'lt_sgn04.tem': '38bea47bfb748ed5848f16bd689afdf56259d6f6931b8d71542ec1bb309e926f',
    'mp03t4.map': 'eab7d48cdb16a5317c17323e7b9c19c5e79146dfcf7a1df5a96b359b9fb45315',
    'pole01.tem': 'd2821901b6fdff9a341edfd13f06ccd314af9841154cb7b4068cfafe881f93c1',
    'pole02.tem': 'd52fcedb9d4134dbf05e4e130d3171cc8abfa0a863de0bbd118a22b7de501a6a',
    'rules.ini': 'f34900cbe115a593adc22a91a7b86e7d4e1511eff995b5170af7d89c8a254d0a',
    'sign01.tem': '9c139996faad72af5090173b3b44970e67e355f831cebb9b748b7a30cf53a533',
    'sign02.tem': 'abf795d865a44083c338c59060ec40df005cb2ae24f473ee4721b7f616c00d33',
    'sign03.tem': 'e213bf57c5ecd4caa9c2b0d8df96f9d71f60a3137821a1862b5ee52ca7d28c1b',
    'sign04.tem': 'a7bd8e62a3675d55c9be015c60193ebbca82eb29dff0d0ef3b2d32f1dd64a36d',
    'sign05.tem': '154f766f0b91ebce3d74761f5bfdb80459add380dd7b38b3699b87c5d3f23cda',
    'sign06.tem': '2df65625c800c6ace224b72176ec1e9d800f9b1cbc86d7a4418700000eeed828',
    'temperat.pal': '5903b69868b84f494cfbb4e7100398015ef9775b37726019a0d7b5fb6cb33b55',
    'tree01.tem': '619cb6cba054eaf7c00cb6331eb70a686be25e60fd86573b352df22e22b1956e',
    'tree02.tem': 'bbe0774f6ed95bf604444e25ce71562c276061cf95f9205465eb60ff2d14acaa',
    'tree03.tem': 'd269e5ddfedd96cbb14071c80e4710b7fe301378b788d8562995e41617b781b3',
    'tree04.tem': '77773eccc9849662171ab2bc1f169758f058c090a6150b35346ec5897c1a957c',
    'tree05.tem': '9a8b1a9e668a2eb36a6a705d5d682acae8449e9b05987bbb7fe31bd54c3fa297',
    'tree06.tem': 'b48d5e6d3d2f52293bb8375ae6a6d402879651ed1e63e485d7fbd27fed12bf0f',
    'tree07.tem': 'e177ddaba758b599a5e9035b15806f7e1ff09444c20b209e666ced0da8e2d0a9',
    'tree08.tem': '8b0e49c2a9b65a364492456a1d3e3dd5ed688dde5c2b8ade4202f6b83a013e6b',
    'tree09.tem': '67327f7b71622226e705d2dad9af4feff4ff2e773ac134984e47f47e04141533',
    'tree10.tem': '94134d4f91e2685d47c9e4880c4a61a1d4b48f4d7076d9c6a845a37599d25157',
    'tree11.tem': 'd9a10a7fe1b0e29c47138ef2ca02c3f05d38c2ca444c7c8a9ce4c5a8dec51588',
    'tree12.tem': '9b2b0eb10f78e2df6b5c870a3c5b8ae8322e5f8e3ce35e52285620b8b87ffe27',
    'tree13.tem': '74d20e55c6fe420bc874ab9acd479d7db7544a884322cfdfcda43be93b45feaf',
    'tree14.tem': 'bd59f289d6b7adbc2251222cd68551ef27b802c306e3986f19a7810c0d5ca2b0',
    'tree15.tem': 'c8156189016bd2b079d1dc2ce0fd66b19c675d1bc0be96d0bc85670a048dc5cc',
    'tree16.tem': 'd3a1273b8e6cd3242be3c467323238b339aab080425ca8450d20132d86f912e1',
    'tree17.tem': 'e0e1246cb4460ffd4496bd96c79d56fa20ce2b7cc79ea5ae01d0f2c155a1706b',
    'tree18.tem': 'f739c48c5573fb1e21642896c6a6923d64a9d24fae5a83c7378f6c8130429116',
    'tree19.tem': 'f031ff5d9219451e605f750482a98311ac4ce8ffea9a57399c640446d4dba197',
    'tree20.tem': 'f187951c2d76b07614cc31732592b24c4ac34af94714f39369a6321f124ea981',
    'tree21.tem': '534525f9c62fc7f741b7ae078877aabb89de17c25d9fe7828697d530b75d9fb1',
    'tree22.tem': 'a4f75bf292cdd7644fb1fa76caa4a2afa0aaef8fa6a7d14bda9b52189e3dd995',
    'tree23.tem': '7b2bfa3cda70f9a2211f5e2a6a8bfee8383ad227c70171be33a0c86e2d71ca14',
    'tree24.tem': '41851808e22f7f1242c3f6ca8d1c191a55470d6cbde36c2389ef1b7d15ed08cc',
    'tree25.tem': '35f4127a242fc968dae8440d9838f036627fb2103dc85090dca78b2ff5115f9b',
    'tree26.tem': 'f866ae9bca29aad1e03c8bd3c9d2453228538e2c2c84158279994b3f8fb3c8d5',
    'tree27.tem': '4500d474cd2e52e4fbe7cc1f8333948be9558c42217876a692065fc1f08a9812',
    'tree28.tem': '464a1b2dcf36c8ef49c493298cab4b4e007d387249bb4eaee2e72af5e375a426',
    'trff01.tem': '8f772cda80d0a88e1d830362a4b48c9e7aadc6f7b8b7beee70bcc32a8e0d3249',
    'trff02.tem': '1b60ce92dd0e6280683f1fd7b4fc177dddfe74fd5cb450d0dacfb2f3ab479eb6',
    'trff03.tem': '9ed56d522f2acdc39331117d6b05ae4092784154c4cb9af428672415a9ae122a',
    'trff04.tem': 'e92a304e2ce550a9dea6b5527f2f3c6262b110f89023ec5794e21b7fe96f056e',
}
sys.path.insert(0,str(ROOT/'tools'))
from verify_scenery_mapping import verify
from verify_unit_light_mapping import verify as verify_unit
from verify_staging_mapping import verify as verify_staging
from verify_shadow_color_mapping import verify as verify_shadow
from verify_composition_mapping import verify as verify_composition
from verify_raster_mapping import verify as verify_raster
from verify_presentation_mapping import verify as verify_primitives


def source_identities(args):
    return {'oracle_sources':{name:hash_file(ROOT/'tests'/name) for name in SOURCES},
            'mapping_tools':{name:hash_file(ROOT/'tools'/name) for name in
                             ('verify_scenery_mapping.py','verify_unit_light_mapping.py','verify_staging_mapping.py','verify_shadow_color_mapping.py','verify_raster_mapping.py','verify_presentation_mapping.py',
                              'verify_composition_mapping.py')},
            'render_data_sha256':hash_file(args.render_data),
            'exporter_sha256':hash_file(args.exporter),
            'assets_sha256':{name:hash_file(args.assets/name) for name in ASSETS}}


def prepare(args):
    if args.suite not in ('scenery','terrain-types','props'):raise ValueError('Unknown scenery suite')
    digest,profile=scenery_profile(args.exe.read_bytes(),allow_patched=True)
    native_data=args.native_data_exe or args.exe
    if hash_file(native_data)!=EXPECTED:
        raise ValueError('Retained native scenery inputs require the disc identity; use --native-data-exe explicitly for patched research')
    if digest==PATCHED_EXPECTED:
        verify(native_data.read_bytes(),args.exe.read_bytes())
        verify_staging(native_data.read_bytes(),args.exe.read_bytes())
        verify_unit(native_data.read_bytes(),args.exe.read_bytes())
        verify_shadow(native_data.read_bytes(),args.exe.read_bytes())
        verify_primitives(native_data.read_bytes(),args.exe.read_bytes())
        verify_raster(native_data.read_bytes(),args.exe.read_bytes())
        verify_composition(native_data.read_bytes(),args.exe.read_bytes())
    if hash_file(args.render_data)!=RETAINED_RENDER_SHA256:
        raise ValueError('Prepared raster/render data must retain the verified disc profile')
    output=ROOT/'private'/'migration'/profile/args.suite
    for path in (output/'expected.json',output/'report.json'):
        private_path(path,args.exe)
        if not args.expectations and path.exists():raise ValueError('Fresh scenery evidence already exists; use --expectations for replay')
    if args.report:
        private_path(args.report,args.exe)
        if args.report.resolve()==(output/'expected.json').resolve():raise ValueError('Report cannot replace original expectations')
        if args.report.exists() and not args.expectations:
            prior=json.loads(args.report.read_text())
            if prior.get('evidence_mode')=='fresh-original' or 'commands' in prior:
                raise ValueError('Fresh report cannot replace original evidence')
    args.assets=output/'assets';private_path(args.assets,args.exe)
    if args.assets.resolve().is_relative_to(args.data_dir.resolve()):
        raise ValueError('Research export must be outside the supplied asset installation')
    subprocess.run([str(args.exporter),'--export',str(args.data_dir),str(args.assets)],check=True)
    if {name:hash_file(args.assets/name) for name in ASSETS}!=ASSETS:
        raise ValueError('Assets must match retained supplied inputs; patched precedence is not promoted')
    args.research_identities=source_identities(args)
    args.research_native_sha256=hash_file(args.native)
    return digest,profile,native_data,output


def identities(args,digest,profile,native_data):
    selected=scenery_profile(args.exe.read_bytes(),allow_patched=True)
    if selected!=(digest,profile):raise ValueError('Original engine/profile identity differs')
    current=source_identities(args)
    if current!=args.research_identities:raise ValueError('Oracle sources/prepared inputs changed during this run')
    if hash_file(args.exe)!=digest or hash_file(native_data)!=EXPECTED:raise ValueError('Executable inputs changed during this run')
    if hash_file(args.native)!=args.research_native_sha256:raise ValueError('Native runner changed during this run')
    return {'executable_sha256':digest,'profile':profile,'native_data_executable_sha256':EXPECTED,
            'native_sha256':hash_file(args.native),**current,'suite':args.suite,'runtime_profile_promoted':False}


def run_native(args,commands):
    proc=subprocess.run([str(args.native),str(args.render_data)],
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
                  'mapping_tools','render_data_sha256','exporter_sha256','assets_sha256','fixture_sha256','suite'):
        if evidence['evidence'].get(field)!=current.get(field):raise ValueError('Cached original identity differs: '+field)
    if any(evidence.get(f)!=current[f] for f in ('executable_sha256','profile')):raise ValueError('Cached original envelope identity differs')


def replay(args,digest,profile,native_data,output):
    source=private_path(args.expectations,args.exe)
    evidence=json.loads(source.read_text());receipt=private_path(source.parent/'report.json',args.exe)
    validate_receipt(evidence,json.loads(receipt.read_text()),hash_file(source))
    destination=args.report or output/'replay-report.json'
    check_replay_destination(destination,source,receipt)
    current=identities(args,digest,profile,native_data)
    current['fixture_sha256']={path:hash_file(private_path(Path(path),args.exe)) for path in evidence['evidence']['fixture_sha256']}
    validate_cached(evidence,current)
    import time
    started=time.monotonic()
    actual=run_native(args,evidence['commands'])
    elapsed=time.monotonic()-started
    current=identities(args,digest,profile,native_data)
    current['fixture_sha256']={path:hash_file(private_path(Path(path),args.exe)) for path in evidence['evidence']['fixture_sha256']}
    validate_cached(evidence,current)
    if actual!=evidence['expected']:raise AssertionError('Cached original/native scenery comparison differs')
    report={**evidence['evidence'],**current,'evidence_mode':'cached-original-replay',
            'original_instructions_executed':False,'expectations_sha256':hash_file(source),'cases':len(actual),'native_comparison_seconds':elapsed}
    write_report(args.exe,destination,report)
    print(f'{len(actual)} identity-checked {profile} {args.suite} results: PASS (native replay; no original execution)')
