#!/usr/bin/env python3
"""Audit tracked and unignored source candidates; never package owned game data."""
import subprocess
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
raw=subprocess.check_output(['git','ls-files','--cached','--others','--exclude-standard','-z'],cwd=ROOT)
paths=sorted(set(p.decode() for p in raw.split(b'\0') if p))
blocked_suffixes={'.exe','.dll','.rtp','.mix','.vxl','.vpl','.hva','.pal','.shp','.tem','.sno','.map','.cab','.iso','.bin','.dmg','.cue','.ppm','.png','.bmp','.disasm','.dylib','.a','.o','.pyc'}
errors=[]
for name in paths:
    p=Path(name)
    if any(part in {'private','build','.venv','__pycache__'} or part.endswith('.app') for part in p.parts):
        errors.append(name+': local-only path')
    if p.suffix.lower() in blocked_suffixes:errors.append(name+': binary/asset extension')
    full=ROOT/p
    if full.is_file():
        with full.open('rb') as f:magic=f.read(4)
        if magic[:2]==b'MZ' or magic in (b'\x7fELF',b'\xcf\xfa\xed\xfe',b'\xce\xfa\xed\xfe',b'\xfe\xed\xfa\xcf',b'\xca\xfe\xba\xbe'):
            errors.append(name+': executable magic')
for local in ('private/placement/assets/rules.ini','private/placement/assets/mp03t4.map','private/placement/expected.json','private/lifecycle-report.json','private/lifecycle-sanitize-report.json','private/placement/object-placement.txt','private/occupation/assets/rules.ini','private/occupation/assets/mp03t4.map','private/occupation/expected.json','private/occupation-report.json','private/occupation/terrain-mark.txt','private/props/assets/sign03.tem','private/props/raw-0.shp','private/props/expected.json','private/props-report.json','private/terrain/raw-surface.txt','build/props-props.ppm','build/props-sign03.png','private/terrain-types/assets/tree28.tem','private/terrain-types/expected.json','private/terrain-types-report.json','private/terrain/assets/tree01.tem','private/terrain/expected.json','private/scenery-report.json','private/terrain/terrain-draw.txt','build/scenery-trees.ppm','private/derived/direction-data.bin','private/derived/render-data.bin','private/derived/raster-data.bin','private/raster/assets/htnk.vxl','private/composition/assets/clear01.tem','private/shadow-color/assets/rules.ini','private/shadow-color/expected.json','private/staging/assets/temperat.pal','private/staging/expected.json','private/lighting/assets/mp03t4.map','private/lighting/expected.json','private/shadow-keys/expected.json','private/shadow-key-report.json','private/voxel-cache/next-unit-shadow.txt','private/voxel-cache/expected.json','private/voxel-cache-report.json','private/voxel-cache/type-loaders.txt','private/unit-light/expected.json','private/unit-light/assets/unittem.pal','private/unit-light/constructor.txt','private/unit-light-report.json','private/lighting/cell-light.txt','private/map-light-report.json','private/presentation9/constructor.txt','private/references/redalert2-recomp-eebcf725/docs/voxels.md','private/presentation/voxels.vpl','private/game/ra2.mix','private/disc-allied/game.exe','build/native/redalert2-native','private/references/OpenRA/.git/config'):
    if subprocess.run(['git','check-ignore','--quiet',local],cwd=ROOT).returncode!=0:errors.append(local+': not ignored')
for local in ('private/patches/RA21006EN.EXE','private/patches/YURI-1001-ENGLISH.EXE',
              'private/patch-inspection/ra2-1006.json','private/patch-inspection/yr-1001.json'):
    if subprocess.run(['git','check-ignore','--quiet',local],cwd=ROOT).returncode!=0:errors.append(local+': not ignored')
if errors:raise SystemExit('\n'.join(errors))
print(f'{len(paths)} source candidates audited: PASS; owned data, binaries and research ignored')
