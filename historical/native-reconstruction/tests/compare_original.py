#!/usr/bin/env python3
"""Compare native facing state with isolated routines from the supplied base RA2 EXE.
Research only: the application never links Unicorn or executes this executable.
"""
import argparse
import hashlib
import json
import random
import struct
import subprocess
import tempfile
import os
from pathlib import Path
import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_ESP, UC_X86_REG_EIP
from unicorn.x86_const import UC_X86_REG_EBX, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP
from unicorn import UC_HOOK_MEM_WRITE

EXPECTED = '135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743'
ADDRESSES = {'current': 0x4B8700, 'set_desired': 0x4B8550, 'set_current': 0x4B8630,
             'set_rate': 0x4B89B0, 'rotating': 0x4B87B0, 'clockwise': 0x4B87E0,
             'counterclockwise': 0x4B8820, 'frame_counter': 0xA2894C}

# This profile is limited to Facing. Other oracles importing EXPECTED retain
# their disc-only gate; neither the native data reader nor other suites inherit it.
PATCHED_EXPECTED = 'e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
FACING_PROFILES = {
    EXPECTED: ('allied-disc', ADDRESSES),
    PATCHED_EXPECTED: ('supplied-ra2-1006', {
        'current': 0x4B8BE0, 'set_desired': 0x4B8A30, 'set_current': 0x4B8B10,
        'set_rate': 0x4B8E90, 'rotating': 0x4B8C90, 'clockwise': 0x4B8CC0,
        'counterclockwise': 0x4B8D00, 'frame_counter': 0xA40D2C}),
}

def facing_profile(data):
    digest = hashlib.sha256(data).hexdigest()
    if digest not in FACING_PROFILES:
        raise ValueError('REFUSED: executable SHA-256 differs. Recover addresses for this exact binary first.')
    name, addresses = FACING_PROFILES[digest]
    return digest, name, addresses

def write_report(source, destination, report):
    """Keep profile-specific reports private and preserve another build's evidence."""
    source = source.resolve(strict=True)
    destination = destination.absolute()
    if any(path.is_symlink() for path in (destination, *destination.parents)):
        raise ValueError('Symlink report paths are refused')
    destination = destination.resolve()
    root = Path(__file__).resolve().parents[1]
    if destination.is_relative_to(source.parent):
        raise ValueError('Report must be outside the source installation')
    if not any(destination.is_relative_to(root / folder) for folder in ('private', 'build')):
        raise ValueError('Report must stay under private/ or build/')
    if destination.exists():
        previous = json.loads(destination.read_text())
        if previous.get('executable_sha256') != report['executable_sha256']:
            raise ValueError('Refusing to replace another executable profile report')
    destination.parent.mkdir(parents=True, exist_ok=True)
    temporary = None
    try:
        with tempfile.NamedTemporaryFile(mode='w', encoding='utf-8', dir=destination.parent,
                                         prefix='.facing-report-', delete=False) as output:
            temporary = Path(output.name)
            output.write(json.dumps(report, indent=2)+'\n')
        os.replace(temporary, destination)
    finally:
        if temporary and temporary.exists():
            temporary.unlink()

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exe', type=Path, required=True)
    parser.add_argument('--native-vectors', type=Path, default=Path('build/native/native-vectors'))
    parser.add_argument('--report', type=Path)
    args = parser.parse_args()
    data = args.exe.read_bytes()
    try:
        digest, profile, addresses = facing_profile(data)
    except ValueError as error:
        raise SystemExit(str(error)) from error
    pe = pefile.PE(data=data)
    if pe.OPTIONAL_HEADER.ImageBase != 0x400000 or pe.FILE_HEADER.Machine != 0x14c:
        raise SystemExit('Unexpected PE base or architecture')
    u = Uc(UC_ARCH_X86, UC_MODE_32)
    u.mem_map(0x400000, (pe.OPTIONAL_HEADER.SizeOfImage + 4095) & ~4095)
    for section in pe.sections:
        u.mem_write(0x400000 + section.VirtualAddress, section.get_data())
    u.mem_map(0x1000000, 0x20000)
    obj, arg, result, stack, stop = 0x1001000, 0x1001100, 0x1001200, 0x101F000, 0x1000000
    canaries = [(obj-32, 32), (obj+24, 32), (arg-32, 32), (arg+4, 32),
                (result-32, 32), (result+4, 32)]
    for address, size in canaries:
        u.mem_write(address, bytes([0xA5])*size)
    preserved = {UC_X86_REG_EBX: 0x12345678, UC_X86_REG_ESI: 0x23456789,
                 UC_X86_REG_EDI: 0x3456789A, UC_X86_REG_EBP: 0x456789AB}
    def audit_write(_u, _access, address, size, _value, _context):
        if not any(start <= address and address+size <= end for start, end in
                   ((obj, obj+24), (result, result+4), (stack-256, stack))):
            raise AssertionError(f'Unexpected original write at {address:#x}, size {size}')
    u.hook_add(UC_HOOK_MEM_WRITE, audit_write)
    def put(addr, value):
        u.mem_write(addr, struct.pack('<I', value & 0xffffffff))
    def call(name, arguments=()):
        caller = struct.pack('<'+'I'*(len(arguments)+1), stop, *[v & 0xffffffff for v in arguments]) + bytes([0x5A])*32
        u.mem_write(stack, caller)
        for register, value in preserved.items():
            u.reg_write(register, value)
        u.reg_write(UC_X86_REG_ESP, stack)
        u.reg_write(UC_X86_REG_ECX, obj)
        argument_before = bytes(u.mem_read(arg, 4))
        u.emu_start(addresses[name], stop, count=2000)
        if u.reg_read(UC_X86_REG_EIP) != stop:
            raise RuntimeError('Original routine exceeded instruction budget: '+name)
        if u.reg_read(UC_X86_REG_ESP) != stack+4+4*len(arguments):
            raise AssertionError('Original caller ESP changed: '+name)
        if bytes(u.mem_read(stack, len(caller))) != caller:
            raise AssertionError('Original caller stack changed: '+name)
        if any(u.reg_read(register) != value for register, value in preserved.items()):
            raise AssertionError('Original callee-saved register changed: '+name)
        if bytes(u.mem_read(arg, 4)) != argument_before:
            raise AssertionError('Original input argument changed: '+name)
        for address, size in canaries:
            if bytes(u.mem_read(address, size)) != bytes([0xA5])*size:
                raise AssertionError('Original object/input/result arena changed: '+name)
        return u.reg_read(UC_X86_REG_EAX)
    vectors, expected = [], []
    def case(op, desired, start, began, duration, rate, tick, value=0):
        u.mem_write(obj, struct.pack('<IIiiiI', desired, start, began, 0, duration, rate))
        put(addresses['frame_counter'], tick)
        put(arg, value)
        changed = 0
        if op == 'D': changed = call('set_desired', (arg,)) & 255
        elif op == 'S': changed = call('set_current', (arg,)) & 255
        elif op == 'R': call('set_rate', (value,))
        call('current', (result,))
        current = struct.unpack('<H', u.mem_read(result, 2))[0]
        flags = [call(n) & 255 for n in ('rotating','clockwise','counterclockwise')]
        state = struct.unpack('<IIiiiI', u.mem_read(obj, 24))
        expected.append([current, *flags, state[0]&65535, state[1]&65535, state[2], state[4], state[5]&65535, changed])
        vectors.append(' '.join(map(str, (op, desired, start, began, duration, rate, tick, value))))
    # Semantic boundary states: timer expiry/paused sentinel, short turns, 16-bit tie,
    # zero/signed rates, and the low-16 signed narrowing of the quotient.
    facings = [0,1,255,256,1279,1280,1281,8191,8192,8193,32767,32768,65535]
    for start in facings:
        for desired in facings:
            for rate in [0,1,256,1280,32512,32768,65535]:
                for tick in [0,1,5,6,7,30]:
                    case('C',desired,start,0,6,rate,tick)
    rng = random.Random(0x524132)
    for i in range(2500):
        desired, start, value = (rng.randrange(65536) for _ in range(3))
        rate = rng.choice([0,1,256,1280,1792,32512,32768,65535])
        began = rng.choice([-1,0,20,2147483640])
        tick = rng.choice([0,1,20,25,60,2147483647,-2147483648])
        duration = rng.choice([0,1,6,25,32768])
        op = rng.choice(['C','D','S','R'])
        if op == 'R': value = rng.choice([-257,-129,-128,-1,0,1,5,127,128,256,1000])
        case(op,desired,start,began,duration,rate,tick,value)
    # Live sequences: perform a request, advance, then interrupt without reinitializing
    # the logical state. Compare both state and derived heading after every operation.
    for _ in range(200):
        desired=start=rng.randrange(65536);began=duration=0;rate=rng.choice([256,1280,1792,32512])
        for tick in range(35):
            op = 'D' if tick in (0,4,12,25) else 'C'
            value = rng.randrange(65536) if op == 'D' else 0
            case(op,desired,start,began,duration,rate,tick,value)
            _,_,_,_,desired,start,began,duration,rate,_ = expected[-1]
    proc = subprocess.run([str(args.native_vectors)], input='\n'.join(vectors)+'\n', text=True, capture_output=True, check=True)
    actual = [[int(x) for x in line.split()] for line in proc.stdout.splitlines()]
    if len(actual) != len(expected):
        raise RuntimeError(f'Native result count {len(actual)} differs from {len(expected)}')
    for i,(a,e) in enumerate(zip(actual,expected)):
        if a != e:
            raise AssertionError(f'Case {i}: {vectors[i]}\noriginal={e}\nnative={a}')
    report = {'executable_sha256': digest, 'embedded_file_version': '1.08',
              'native_vectors_sha256': hashlib.sha256(args.native_vectors.read_bytes()).hexdigest(),
              'profile':profile, 'cases':len(expected), 'matched':len(expected), 'addresses':{k:hex(v) for k,v in addresses.items()},
              'oracle_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              'audits':['write ranges', 'object/input/result canaries', 'read-only argument',
                        'caller stack and ESP', 'callee-saved registers'],
              'scope':'Facing state, interpolation, requests, ROT; no locomotion, rendering or full-game timing claim',
              'seed':0x524132, 'original_code_patched':False, 'windows_apis_stubbed':False}
    report_path = args.report or Path('private/recovery-report.json' if digest == EXPECTED
                                    else 'private/facing-1006-report.json')
    write_report(args.exe, report_path, report)
    print(f'{len(expected):,} base RA2 original/native facing comparisons: PASS')
    print('No original instructions patched; no API stubs; executable hash pinned.')
if __name__ == '__main__':
    main()
