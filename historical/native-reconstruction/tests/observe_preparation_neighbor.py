#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Observe the exact base preparation neighbor block; not a full Process proof.

The interior registers, stack byte, records and registry are supplied. Original
476AC0/548070 children execute unchanged. Native integration is tested separately.
"""
import argparse
import hashlib
import itertools
import json
import struct
import time
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import (UC_X86_REG_EBP, UC_X86_REG_EBX, UC_X86_REG_ESI,
                              UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_ECX)
from original_presentation import PresentationOracle, OBJ, STACK
from compare_original import PATCHED_EXPECTED, write_report
from presentation_evidence import private_path, hash_file

START, END = 0x4a3fa1, 0x4a3fe3
RANGES = {START: END-START, 0x476ac0: 0x56, 0x548070: 0x38, 0x491620: 172}
TABLE, REGISTRY, OVERLAY = 0x1400000, 0x1500000, 0x1501000
TARGET, NEIGHBOR, DRIVE, FALLBACK = OBJ, OBJ+0x1000, OBJ+0x2000, 0xa6f9f8
DIRECTIONS = ((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))
SOURCES = ('tests/observe_preparation_neighbor.py', 'tests/original_presentation.py',
           'tests/presentation_profiles.py', 'tests/compare_original.py',
           'tests/presentation_evidence.py')


def observe(exe):
    import pefile
    data = exe.read_bytes()
    if len(data) != 4485392 or hashlib.sha256(data).hexdigest() != PATCHED_EXPECTED:
        raise ValueError('Exact supplied base executable required')
    pe = pefile.PE(data=data)
    cs = Cs(CS_ARCH_X86, CS_MODE_32)
    inspection = {}
    for address, size in RANGES.items():
        raw = pe.get_data(address-0x400000, size)
        instructions = list(cs.disasm(raw, address))
        if sum(i.size for i in instructions) != size:
            raise ValueError('Incomplete preparation neighbor inspection')
        inspection[hex(address)] = {'bytes': size, 'instructions': len(instructions),
                                   'sha256': hashlib.sha256(raw).hexdigest()}
    oracle = PresentationOracle(exe, allow_patched=True)
    u = oracle.u
    u.mem_map(TABLE, 0x100000)
    u.mem_map(REGISTRY, 0x2000)
    oracle.put(0x8324e0+0x138, TABLE)
    oracle.put(0xa35dec, REGISTRY)
    oracle.put(REGISTRY+27*4, OVERLAY)
    oracle.va = lambda address: address  # Exact base addresses inspected above.
    oracle.checked_call(0x491620, writes=[(0x851a70,32)])
    directions = struct.unpack('<16h', u.mem_read(0x851a70, 32))
    if tuple(zip(directions[::2], directions[1::2])) != DIRECTIONS:
        raise ValueError('Original direction offsets differ')
    query, writes = [], []

    def code(guest, address, size, _):
        if not any(a <= address and address+size <= a+n for a,n in RANGES.items()):
            raise AssertionError(('Uninspected neighbor instruction', hex(address)))
        if address == 0x548070:
            pointer = struct.unpack('<I', guest.mem_read(guest.reg_read(UC_X86_REG_ESP)+4,4))[0]
            query.append(list(struct.unpack('<2h', guest.mem_read(pointer,4))))

    def store(guest, _, address, size, value, __):
        if STACK-64 <= address and address+size <= STACK+4:
            return  # Actual child call/argument scratch, never original code.
        if (address,size) not in ((DRIVE+0x64,1),(FALLBACK+0x24,4)):
            raise AssertionError(('Unexpected neighbor store', hex(address),size))
        writes.append([address,size,value & ((1 << (size*8))-1)])

    u.hook_add(UC_HOOK_CODE, code)
    u.hook_add(UC_HOOK_MEM_WRITE, store)
    immutable = [(a,n) for a,n in RANGES.items()] + [(REGISTRY,0x2000),(0x851a70,32)]
    results = []
    for x,y in ((92,105),(32767,0),(-32768,-1)):
        for first,second,overlay,present in itertools.product(range(8),range(8),(-1,0,1,255),(False,True)):
            u.mem_write(TABLE,bytes(0x100000))
            u.mem_write(TARGET,bytes(0x148));u.mem_write(NEIGHBOR,bytes(0x148));u.mem_write(FALLBACK,bytes(0x148))
            u.mem_write(TARGET+0x24,struct.pack('<2h',x,y))
            for cell in (NEIGHBOR,FALLBACK):oracle.put(cell+0x44,-1 if overlay==-1 else 27)
            u.mem_write(OVERLAY+0x1fd,bytes([max(0,overlay)]))
            dx,dy=DIRECTIONS[second]
            wrap=lambda n:((n+32768)%65536)-32768
            expected_query=[wrap(x+dx),wrap(y+dy)]
            slot=expected_query[1]*512+expected_query[0]
            resident=present and 0<=slot<262144
            if resident:oracle.put(TABLE+slot*4,NEIGHBOR)
            u.mem_write(STACK-64,b'\xa7'*256)
            oracle.put(STACK+0x2c,TARGET)
            u.mem_write(STACK+0x13,b'\0') # Candidate overlay-free scope.
            u.mem_write(DRIVE,b'\xa5'*0x100)
            before=[bytes(u.mem_read(a,n)) for a,n in immutable]
            stack_before=bytes(u.mem_read(STACK+4,188))
            for register,value in ((UC_X86_REG_EBP,DRIVE),(UC_X86_REG_EBX,first),
                                   (UC_X86_REG_ESI,second),(UC_X86_REG_ESP,STACK)):
                u.reg_write(register,value)
            query.clear();writes.clear()
            u.emu_start(START,END,count=256)
            curve=int(overlay>0)
            expected_writes=([[FALLBACK+0x24,4,struct.unpack('<I',struct.pack('<2h',*expected_query))[0]]] if not resident else [])
            expected_writes.append([DRIVE+0x64,1,curve])
            assert u.reg_read(UC_X86_REG_EIP)==END and u.reg_read(UC_X86_REG_ESP)==STACK
            assert u.reg_read(UC_X86_REG_EBP)==DRIVE and u.reg_read(UC_X86_REG_EBX)==first
            assert u.reg_read(UC_X86_REG_ESI)==(first if curve else second)
            assert query==[expected_query] and writes==expected_writes,(query,writes)
            assert bytes(u.mem_read(STACK+4,188))==stack_before
            assert all(bytes(u.mem_read(a,n))==old for (a,n),old in zip(immutable,before))
            results.append([x,y,first,second,overlay,present,query.copy(),writes.copy(),u.reg_read(UC_X86_REG_ESI)])
    return {'cases':len(results),'inspection':inspection,'results':results,
            'scope':'Original interior4A3FA1..4A3FE3 with actual476AC0/548070; supplied registers/stack/records. Candidate overlay-free. Not complete Process, native differential or original gameplay observation. Nonzero Crushable behavior observed but remains natively refused.'}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exe',type=Path,required=True)
    parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args()
    output=private_path(args.output,args.exe)
    if output.exists():raise ValueError('New private output required')
    identities={p:hash_file(Path(p)) for p in SOURCES}
    binary=hash_file(args.exe);start=time.monotonic()
    result=observe(args.exe)
    if hash_file(args.exe)!=binary or {p:hash_file(Path(p)) for p in SOURCES}!=identities:
        raise ValueError('Original observation inputs changed')
    result.update(executable_sha256=binary,sources=identities,elapsed_seconds=time.monotonic()-start,
                  original_instructions_executed=True,original_instructions_modified=False)
    write_report(args.exe,output,result)
    print(f'{result["cases"]} original preparation neighbor interior observations: PASS')


if __name__=='__main__':main()
