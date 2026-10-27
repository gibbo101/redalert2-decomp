#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin resident map children and inspect complete scenario/map INI ordering."""
import hashlib
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from verify_map_preparation import verify as verify_parent

INSPECTED = {0x65eb40:0xe3a, 0x49cfd0:0x936, 0x52b650:0x34}

def verify(data):
    parent = verify_parent(data)
    pe = pefile.PE(data=data)
    cs = Cs(CS_ARCH_X86, CS_MODE_32)
    inspected = {}
    decoded = {}
    for address, size in INSPECTED.items():
        raw = pe.get_data(address-0x400000, size)
        instructions = list(cs.disasm(raw, address))
        if sum(i.size for i in instructions) != size or instructions[-1].mnemonic != 'ret':
            raise ValueError('Incomplete resident startup inspection '+hex(address))
        inspected[hex(address)] = {'bytes':size, 'instructions':len(instructions),
                                  'sha256':hashlib.sha256(raw).hexdigest()}
        decoded[address] = {i.address:(i.mnemonic,i.op_str) for i in instructions}
    scenario = decoded[0x65eb40]
    for address, target in ((0x65f6c0,0x49cfd0),(0x65f71b,0x472540),(0x65f846,0x54b2e0)):
        if scenario.get(address) != ('call',hex(target)):
            raise ValueError('Scenario map preparation order differs')
    ini = decoded[0x49cfd0]
    for address, target in ((0x49d170,0x52b650),(0x49d818,0x54e1e0),(0x49d875,0x52b2e0)):
        if ini.get(address) != ('call',hex(target)):
            raise ValueError('Map INI sequence differs')
    return {'parent':parent, 'inspected_only':inspected,
        'scope':'Actual ordinary map parent and children on supplied general resident TMP/type/Cell/land/geometry inputs. Complete scenario/map INI/usage reset are inspected only, not executed here. No complete startup, file/parser/heap, overlays/actors/converter lifetime, runtime or whole-frame parity.'}
