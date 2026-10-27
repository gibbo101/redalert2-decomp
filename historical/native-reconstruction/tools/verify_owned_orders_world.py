# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact base-binary ordinary Move_To, Stop_Moving and Do_Turn boundaries."""
import hashlib
import struct
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from compare_original import PATCHED_EXPECTED

RANGES = {0x49fe30: 181, 0x49fef0: 200, 0x4a0fd0: 34,
          0x6d6df0: 7, 0x6d6e00: 7, 0x6c12c0: 8, 0x705020: 7}


def verify(data):
    if hashlib.sha256(data).hexdigest() != PATCHED_EXPECTED:
        raise ValueError('Owned orders executable fingerprint differs')
    pe = pefile.PE(data=data)
    cs = Cs(CS_ARCH_X86, CS_MODE_32)
    ranges = {}
    for address, size in RANGES.items():
        raw = pe.get_data(address - 0x400000, size)
        instructions = list(cs.disasm(raw, address))
        if sum(i.size for i in instructions) != size or instructions[-1].mnemonic != ('jmp' if address == 0x6c12c0 else 'ret'):
            raise ValueError('Incomplete owned orders range ' + hex(address))
        ranges[hex(address)] = {'bytes': size, 'instructions': len(instructions),
                                'sha256': hashlib.sha256(raw).hexdigest()}
    for offset, target in ((0x80, 0x6c12c0), (0x84, 0x705020),
                           (0x1bc, 0x6d6df0), (0x1c0, 0x6d6e00)):
        if pe.get_data(0x7addf8 + offset - 0x400000, 4) != struct.pack('<I', target):
            raise ValueError('Owned orders Unit dispatch differs')
    cap = pe.get_data(0x79ea48 - 0x400000, 8)
    if struct.unpack('<d', cap)[0] != 0.30000001192092896:
        raise ValueError('Original stop cap differs')
    return {'ranges': ranges, 'stop_cap_sha256': hashlib.sha256(cap).hexdigest(),
            'scope': 'Healthy nonbridge Move_To, IsTrain0 Stop_Moving, Do_Turn/Facing. '
                     'Disabled predicates, queues, direct routing, deferred turns and scheduling supplied.'}
