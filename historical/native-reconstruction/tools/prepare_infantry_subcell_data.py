#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Prepare private original infantry order data; never alter the source install."""
import argparse,hashlib
from pathlib import Path
import pefile
from verify_terrain_visibility import PATCHED_EXPECTED
MAGIC=b'RA2ISC1\0'
def extract(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied base infantry executable required')
 p=pefile.PE(data=data)
 if p.OPTIONAL_HEADER.ImageBase!=0x400000 or p.FILE_HEADER.Machine!=0x14c:raise ValueError('Infantry PE differs')
 return MAGIC+bytes.fromhex(PATCHED_EXPECTED)+p.get_data(0x7d2b6c-0x400000,36)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args()
 source=a.exe.resolve();output=a.output.resolve();root=Path(__file__).resolve().parents[1]
 if output.is_relative_to(source.parent) or not any(output.is_relative_to(root/n) for n in ('private','build')):raise ValueError('Infantry prepared data must stay private and outside source installation')
 blob=extract(source.read_bytes())
 if output.exists() and output.read_bytes()!=blob:raise ValueError('Refusing to overwrite different prepared data')
 output.parent.mkdir(parents=True,exist_ok=True)
 if not output.exists():output.write_bytes(blob)
 print(len(blob),'private prepared bytes; SHA256',hashlib.sha256(blob).hexdigest())
if __name__=='__main__':main()
