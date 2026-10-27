#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Prepare private original message color bytes; source installation is read-only."""
import argparse,hashlib
from pathlib import Path
import pefile
from verify_string_lookup import EXPECTED
MAGIC=b'RA2MCL1\0'
def extract(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Exact supplied base message executable required')
 p=pefile.PE(data=data)
 if p.OPTIONAL_HEADER.ImageBase!=0x400000 or p.FILE_HEADER.Machine!=0x14c:raise ValueError('Message PE differs')
 return MAGIC+bytes.fromhex(EXPECTED)+p.get_data(0x7f3224-0x400000,9)
def destination(source,output):
 source=source.resolve();output=output.resolve();root=Path(__file__).resolve().parents[1]
 if output.is_relative_to(source.parent) or not any(output.is_relative_to(root/n) for n in ('private','build')):raise ValueError('Message prepared data must stay private and outside source installation')
 return output
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args()
 output=destination(a.exe,a.output);blob=extract(a.exe.read_bytes())
 if output.exists() and output.read_bytes()!=blob:raise ValueError('Refusing to overwrite different prepared data')
 output.parent.mkdir(parents=True,exist_ok=True)
 if not output.exists():output.write_bytes(blob)
 print(len(blob),'private prepared bytes; SHA256',hashlib.sha256(blob).hexdigest())
if __name__=='__main__':main()
