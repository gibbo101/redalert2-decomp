#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Prepare owned voxel normal data outside the supplied installation and Git.
The game continues to read only track data directly from GAME.EXE.
"""
import argparse
import hashlib
import struct
from pathlib import Path
from prepared_data_profiles import readers,default_output
from prepare_direction_data import EXPECTED

MAGIC=b'RA2RND1\0'
def extract(data):
    digest,at,actual=readers(data)
    counts=at(0x7e37e4,20)
    if struct.unpack('<5I',counts)!=(0,16,36,64,245):raise ValueError('Unexpected normal table sizes')
    blob=MAGIC+bytes.fromhex(digest)+counts
    for index,n in enumerate(struct.unpack('<5I',counts)):
        if n:blob+=actual(struct.unpack('<I',at(0x7e37d0,20)[4*index:4*index+4])[0],n*12)
    return blob+at(0x7905d0,8)+at(0x7998d8,4)+at(0x785cf0,4)+at(0x80011c,16384*4)

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exe',type=Path,required=True)
    parser.add_argument('--output',type=Path)
    args=parser.parse_args();source=args.exe.resolve()
    output=(args.output or default_output(hashlib.sha256(source.read_bytes()).hexdigest(),'render-data.bin')).resolve()
    if output==source or output.is_relative_to(source.parent):
        raise SystemExit('Use a separate private output directory, outside the source installation')
    blob=extract(source.read_bytes())
    if output.exists() and output.read_bytes()!=blob:
        raise SystemExit('Refusing to overwrite different derived data; choose a fresh private output path')
    output.parent.mkdir(parents=True,exist_ok=True)
    if not output.exists():output.write_bytes(blob)
    print(f'Prepared {len(blob)} bytes: {output}')
    print('Derived data SHA-256: '+hashlib.sha256(blob).hexdigest())
if __name__=='__main__':main()
