# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the base executable's ordinary turret root and actual numeric children."""
import hashlib
import struct
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from compare_original import PATCHED_EXPECTED

RANGES = {0x6fb890: 0x220, 0x4b8a30: 0xdf, 0x4b8be0: 0x99,
          0x4b8c90: 0x2d, 0x5d2730: 0x7a, 0x5d4e40: 0x21,
          0x4ba600: 0xb2, 0x77f110: 0x3d}


def verify(data):
    if hashlib.sha256(data).hexdigest() != PATCHED_EXPECTED:
        raise ValueError('Owned turret executable fingerprint differs')
    pe = pefile.PE(data=data)
    cs = Cs(CS_ARCH_X86, CS_MODE_32)
    ranges = {}
    for address, size in RANGES.items():
        raw = pe.get_data(address - 0x400000, size)
        instructions = list(cs.disasm(raw, address))
        if sum(i.size for i in instructions) != size or instructions[-1].mnemonic != 'ret':
            raise ValueError('Incomplete owned turret range ' + hex(address))
        ranges[hex(address)] = {'bytes': size, 'instructions': len(instructions),
                                'sha256': hashlib.sha256(raw).hexdigest()}
    for offset, target in ((0x48, 0x5d4e40), (0x398, 0x6d85a0)):
        if pe.get_data(0x7addf8 + offset - 0x400000, 4) != struct.pack('<I', target):
            raise ValueError('Owned turret Unit dispatch differs')
    return {'ranges': ranges,
            'scope': 'Ordinary nonspinning/no-combat Unit turret root, actual Facing, '
                     'destination/body coordinates and bearing. Initial records, target '
                     'lifetime, weapon services, timer padding and manual override supplied.'}
