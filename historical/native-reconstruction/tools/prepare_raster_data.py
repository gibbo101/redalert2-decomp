#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Prepare owned raster traversal and trigonometry data; no original code execution."""
import argparse,hashlib,struct
from pathlib import Path
from prepared_data_profiles import readers,default_output
from prepare_direction_data import EXPECTED

def extract(data):
    digest,at,_actual=readers(data)
    return b'RA2RST1\0'+bytes.fromhex(digest)+at(0x7e36b0,8*36)+at(0x7ea0e4,10240*4)+at(0x7c3128,8)+at(0x788090,8)+at(0x7998c0,8)
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path);a=p.parse_args()
    source=a.exe.resolve()
    output=(a.output or default_output(hashlib.sha256(source.read_bytes()).hexdigest(),'raster-data.bin')).resolve()
    if output==source or output.is_relative_to(source.parent):raise SystemExit('Use output outside the source installation')
    blob=extract(source.read_bytes())
    if output.exists() and output.read_bytes()!=blob:raise SystemExit('Refusing to overwrite different derived data')
    output.parent.mkdir(parents=True,exist_ok=True)
    if not output.exists():output.write_bytes(blob)
    print(f'Prepared {len(blob)} bytes: {output}\nSHA-256: '+hashlib.sha256(blob).hexdigest())
if __name__=='__main__':main()
