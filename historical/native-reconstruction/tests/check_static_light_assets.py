#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Owned-data integration checks; map copies stay in an ignored temporary fixture."""
import argparse
import subprocess
import struct
import tempfile
from pathlib import Path

p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--data-dir',type=Path,required=True)
p.add_argument('--native',type=Path,default=Path('build/native/redalert2-native'))
a=p.parse_args()
source=a.data_dir.resolve()
build_root=Path('build').resolve()
if build_root==source or source in build_root.parents:
    raise ValueError('Test fixtures must be outside the source installation')
build_root.mkdir(exist_ok=True)
with tempfile.TemporaryDirectory(prefix='static-light-assets-',dir=build_root) as work:
    work=Path(work).resolve();export=work/'export';fixture=work/'game';fixture.mkdir()
    subprocess.run(['build/native/map-light-vectors','--export',str(source),str(export)],check=True)
    for path in source.iterdir():
        if path.is_file() and path.name.lower() not in ('mp03t4.map','rules.ini'):
            (fixture/path.name).symlink_to(path)
    original=(export/'mp03t4.map').read_text()
    rules=(export/'rules.ini').read_text()
    rulesfile=fixture/'rules.ini'
    if rulesfile.is_symlink():rulesfile.unlink()
    mapfile=fixture/'mp03t4.map';checks=0
    def render(suffix,extra='',options=(),error=None,zero=False,rules_extra=''):
        global checks
        mapfile.write_text(original+extra)
        rulesfile.write_text(rules+('\n[INGALITE]\nLightIntensity=0\n' if zero else '')+rules_extra)
        target=work/(suffix+'.ppm')
        result=subprocess.run([str(a.native),'--data-dir',str(fixture),'--render',str(target),*options],text=True,capture_output=True)
        if error:
            assert result.returncode and error in result.stderr,(suffix,result.stderr)
            assert not target.exists(),suffix
        else:
            assert result.returncode==0,(suffix,result.stderr)
        checks+=1
        return target.read_bytes() if not error else None
    def structure(kind='INGALITE',health=256,x=35,y=86,key=99999):
        return f'{key}=Neutral,{kind},{health},{x},{y},0,None,1,0,0,0,0\n'
    one='\n[Structures]\n'+structure()
    baseline=render('baseline')
    placed=render('placed',one)
    inert=render('inert',one,zero=True)
    demo=render('demo',options=('--light-demo',))
    # Placed structures also enter conservative route exclusions and may move
    # the demo spawn. Compare the same map/occupancy with an inert light type.
    assert placed!=inert and demo!=baseline,'Static source did not affect pixels'
    low=render('low-inert',one,('--detail','1'),zero=True)
    assert render('low-placed',one,('--detail','1'))==low,'Low-detail light changed pixels'
    render('two',one+structure(key=99998),error='Only one stock INGALITE')
    render('unsupported','\n[Structures]\n'+structure('GALITE'),error='Only one stock INGALITE')
    render('damaged','\n[Structures]\n'+structure(health=128),error='Only a healthy static INGALITE')
    render('override',one+'\n[INGALITE]\nLightIntensity=0.3\n',error='type overrides require recovery')
    render('custom-emitter','\n[Structures]\n'+structure('NEWLAMP')+'\n[NEWLAMP]\nLightIntensity=0.2\n',error='type overrides require recovery')
    render('bad-cell','\n[Structures]\n'+structure(x=-1),error='valid placement cell')
    render('second-demo',one,('--light-demo',),error='Only one static light')
    assert render('voxel-cache-disabled',rules_extra='\n[HTNK]\nDisableVoxelCache=yes\n')==baseline,'Cache bypass changed cold indexed output'
    render('balloon-type',rules_extra='\n[HTNK]\nBalloonHover=yes\n',error='Only ordinary nonharvester voxel HTNK with a turret')
    render('wheel-type',rules_extra='\n[HTNK]\nSpeedType=Wheel\n',error='Only ordinary Track HTNK')
    render('wheel-default',rules_extra='\n[HTNK]\nCrusher=no\n',error='Only ordinary Track HTNK')
    assert render('explicit-track',rules_extra='\n[HTNK]\nCrusher=no\nSpeedType=Track\n')==baseline,'Explicit Track did not override Wheel default'
    # A valid two-frame identity HVA isolates the unrecovered animation/key gate.
    # Read the section name from a protected export, then write only this fixture.
    subprocess.run(['build/native/raster-vectors','--export',str(source),str(export)],check=True)
    name=(export/'htnk.vxl').read_bytes()[802:818]
    hva=fixture/'htnk.hva'
    if hva.is_symlink():hva.unlink()
    hva.write_bytes(bytes(16)+struct.pack('<2I',2,1)+name+struct.pack('<12f',1,0,0,0,0,1,0,0,0,0,1,0)*2)
    render('animated-body',error='Animated HTNK actor frame/key timing')
    assert mapfile.parent!=source
print(f'{checks} owned-data static-light/cache map/CLI checks: PASS (native integration only)')
