#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Prepare owned angle data outside Git; never modify the supplied executable/install.
The native runtime continues to read only track data from GAME.EXE.
"""
import argparse
import hashlib
import struct
from pathlib import Path
from prepared_data_profiles import readers,default_output

EXPECTED='135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743'
MAGIC=b'RA2DIR1\0'
def extract(data):
    digest,at,_actual=readers(data)
    return (MAGIC+bytes.fromhex(digest)+at(0x7fc114,4097*4)+
            at(0x800118,4)+at(0x78bf94,4)+at(0x78bf98,4)+
            at(0x788158,8)+at(0x786630,8)+at(0x786628,8))

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exe',type=Path,required=True)
    parser.add_argument('--output',type=Path)
    args=parser.parse_args()
    source=args.exe.resolve()
    output=(args.output or default_output(hashlib.sha256(source.read_bytes()).hexdigest(),'direction-data.bin')).resolve()
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
