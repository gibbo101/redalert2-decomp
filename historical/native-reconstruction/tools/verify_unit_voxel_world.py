#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compose exact Unit/staging, Foot/base depth and stock final-surface inspections."""
import argparse,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tests'))
from verify_unit_voxel_staging import verify as staging_verify
from verify_foot_depth import verify as depth_verify
from verify_unit_surface_split import verify as surface_verify
def verify(disc,data):
    return {'staging':staging_verify(disc,data),'depth':depth_verify(data),'surface':surface_verify(data),
            'scope':'Complete healthy one-frame Track Unit root with actual cache/raster/staging/pool, Foot depth/gradient and actual ramp-zero base depth across headings, stock nonzero bridge-size final surface and RGB565 gradients 0/2, followed by supplied shadow and actual saved-dirty cleanup. Immutable map/tile dimension/contact-kind/house/plane/palette/camera records and services remain supplied. No ownership/ramp/status/eviction/actor timing/shadow pixels/runtime/frame parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--disc',type=Path,default=Path('private/disc-allied/game.exe'));a=p.parse_args()
    verify(a.disc.read_bytes(),a.exe.read_bytes());print('Complete Unit/staging/depth/final-surface inspection: PASS')
