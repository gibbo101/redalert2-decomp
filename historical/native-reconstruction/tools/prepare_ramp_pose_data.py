#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Prepare private original inverse-trig data for stock ramp interpolation."""
import argparse,hashlib
from pathlib import Path
from prepared_data_profiles import readers,PATCHED,default_output

def extract(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED:raise ValueError('Exact supplied patched engine required for ramp pose data')
 digest,_mapped,actual=readers(data)
 return (b'RA2RPO1\0'+bytes.fromhex(digest)+actual(0x80bdd4,4097*4)+actual(0x7a0f88,4)+
  actual(0x79b630,8)+actual(0x7a8660,8)+actual(0x79c520,8))
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path);a=p.parse_args()
 source=a.exe.resolve();data=source.read_bytes();dest=(a.output or default_output(hashlib.sha256(data).hexdigest(),'ramp-pose-data.bin')).resolve()
 if dest==source or dest.is_relative_to(source.parent):raise SystemExit('Use a private output outside the source installation')
 blob=extract(data)
 if dest.exists() and dest.read_bytes()!=blob:raise SystemExit('Refusing to overwrite different derived data')
 dest.parent.mkdir(parents=True,exist_ok=True)
 if not dest.exists():dest.write_bytes(blob)
 print(f'Prepared {len(blob)} bytes: {dest}\nSHA-256: '+hashlib.sha256(blob).hexdigest())
if __name__=='__main__':main()
