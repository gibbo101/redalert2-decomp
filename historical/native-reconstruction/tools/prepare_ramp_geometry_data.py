#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Prepare the supplied base engine's tangent table privately; no code execution."""
import argparse,hashlib
from pathlib import Path
from prepared_data_profiles import readers,PATCHED,default_output

def extract(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED:
        raise ValueError('Exact supplied patched engine required for ramp geometry data')
    digest,_mapped,actual=readers(data)
    return b'RA2GEO1\0'+bytes.fromhex(digest)+actual(0x80fde4,4096*4)+actual(0x7a0f80,8)

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();source=a.exe.resolve();data=source.read_bytes()
    output=(a.output or default_output(hashlib.sha256(data).hexdigest(),'ramp-geometry-data.bin')).resolve()
    if output==source or output.is_relative_to(source.parent):
        raise SystemExit('Use a private output outside the source installation')
    blob=extract(data)
    if output.exists() and output.read_bytes()!=blob:
        raise SystemExit('Refusing to overwrite different derived data')
    output.parent.mkdir(parents=True,exist_ok=True)
    if not output.exists():output.write_bytes(blob)
    print(f'Prepared {len(blob)} bytes: {output}\nSHA-256: '+hashlib.sha256(blob).hexdigest())
if __name__=='__main__':main()
