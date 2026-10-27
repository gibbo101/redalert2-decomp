#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Research-only export of hash-checked private radar dimensions; no runtime EXE read."""
import argparse,hashlib,json,struct
from pathlib import Path
from presentation_evidence import private_path
from verify_radar_shape_buckets import dimensions

def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args()
 out=private_path(a.output,a.exe);meta=out.with_suffix(out.suffix+'.json')
 if out.exists() or meta.exists():raise ValueError('Use a new private dimension export path')
 source=a.exe.read_bytes();payload=struct.pack('<44i',*dimensions(source));out.parent.mkdir(parents=True,exist_ok=True);out.write_bytes(payload)
 record=dict(executable_sha256=hashlib.sha256(source).hexdigest(),bytes=len(payload),sha256=hashlib.sha256(payload).hexdigest(),scope='Private dimension data for explicit tests/caller-supplied shapes; no game runtime executable read')
 meta.write_text(json.dumps(record,indent=2)+'\n');print(json.dumps(record))
if __name__=='__main__':main()
