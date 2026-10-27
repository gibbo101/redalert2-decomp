#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Prepare the private base visibility-mask result table without execution."""
import argparse,hashlib
from pathlib import Path
from prepared_data_profiles import readers,PATCHED,default_output

def extract(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED:
        raise ValueError('Exact supplied patched engine required for visibility data')
    digest,_,actual=readers(data)
    return b'RA2VIS1\0'+bytes.fromhex(digest)+actual(0x7ac3bc,256)

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--exe',type=Path,required=True);parser.add_argument('--output',type=Path)
    args=parser.parse_args();source=args.exe.resolve();data=source.read_bytes();destination=(args.output or default_output(hashlib.sha256(data).hexdigest(),'visibility-data.bin')).resolve()
    if destination==source or destination.is_relative_to(source.parent):raise SystemExit('Use a private output outside the source installation')
    blob=extract(data)
    if destination.exists() and destination.read_bytes()!=blob:raise SystemExit('Refusing to overwrite different derived data')
    destination.parent.mkdir(parents=True,exist_ok=True)
    if not destination.exists():destination.write_bytes(blob)
    print(f'Prepared {len(blob)} bytes: {destination}\nSHA-256: '+hashlib.sha256(blob).hexdigest())
if __name__=='__main__':main()
