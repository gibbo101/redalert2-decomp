#!/usr/bin/env python3
"""Record PE identity; optionally disassemble a bounded range to ignored research output."""
import argparse
import hashlib
import json
from pathlib import Path
import pefile
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('exe',type=Path)
parser.add_argument('--range',nargs=2,type=lambda x:int(x,0),metavar=('START','END'))
args=parser.parse_args()
data=args.exe.read_bytes();p=pefile.PE(data=data)
identity={'file':args.exe.name,'sha256':hashlib.sha256(data).hexdigest(),'bytes':len(data),'image_base':hex(p.OPTIONAL_HEADER.ImageBase),'entry_rva':hex(p.OPTIONAL_HEADER.AddressOfEntryPoint),'timestamp':p.FILE_HEADER.TimeDateStamp}
for block in getattr(p,'FileInfo',[]):
    for info in block:
        for table in getattr(info,'StringTable',[]):
            identity['version_strings']={k.decode(errors='replace'):v.decode(errors='replace') for k,v in table.entries.items()}
print(json.dumps(identity,indent=2))
if args.range:
    from capstone import Cs,CS_ARCH_X86,CS_MODE_32
    start,end=args.range
    if end<=start or end-start>0x10000:raise SystemExit('Disassembly limited to 64 KiB')
    raw=p.get_data(start-p.OPTIONAL_HEADER.ImageBase,end-start)
    for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,start):print(f'{i.address:08x} {i.mnemonic:8s} {i.op_str}')
