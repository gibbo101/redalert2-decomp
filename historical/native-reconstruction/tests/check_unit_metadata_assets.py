#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Native GameAssets metadata integration using private INI overrides only."""
import argparse,subprocess,tempfile
from pathlib import Path
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--data-dir',type=Path,required=True)
    p.add_argument('--asset-dir',type=Path,default=Path('private/migration/supplied-ra2-1006/scenery/assets'))
    p.add_argument('--native',type=Path,default=Path('build/native/ra2-inspect'));a=p.parse_args()
    source=a.data_dir.resolve();build=Path('build').resolve()
    if build==source or source in build.parents:raise ValueError('Fixtures must be outside source installation')
    original={name:(a.asset_dir/name).read_bytes() for name in ('rules.ini','art.ini')}
    with tempfile.TemporaryDirectory(prefix='unit-metadata-',dir=build) as work:
        fixture=Path(work)/'game';fixture.mkdir()
        for path in source.iterdir():
            if path.is_file() and path.name.lower() not in original:(fixture/path.name).symlink_to(path)
        checks=0
        def run(overrides,accepted):
            nonlocal checks
            for name,data in original.items():(fixture/name).write_bytes(data+overrides.get(name,b''))
            r=subprocess.run([str(a.native),str(fixture)],capture_output=True,text=True)
            if accepted:assert r.returncode==0,r.stderr
            else:assert r.returncode and 'Only ordinary nonharvester voxel HTNK' in r.stderr,r.stderr
            checks+=1
        run({},True)
        run({'rules.ini':b'\n[HTNK]\nTurret=Totally\nHarvester=Nonsense\n',
             'art.ini':b'\n[HTNK]\nVoxel=Yarbitrary\n'},True)
        for name,key,value in [('rules.ini','Harvester','yes'),('rules.ini','HunterSeeker','yes'),
                               ('rules.ini','BalloonHover','yes'),('rules.ini','Turret','no'),
                               ('rules.ini','Turret','?'),('art.ini','Voxel','no')]:
            run({name:f'\n[HTNK]\n{key}={value}\n'.encode()},False)
        assert all((a.asset_dir/name).read_bytes()==data for name,data in original.items())
    print(f'{checks} owned-data HTNK metadata guard/prefix checks: PASS (native integration only)')
if __name__=='__main__':main()
