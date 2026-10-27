#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the actor/type/global storage operands in the existing complete root."""
import hashlib,sys
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tests'))
from compare_original import PATCHED_EXPECTED
from verify_unit_voxel_staging import verify as parent
OPERANDS={
 0x6ff6b4:('mov','ebx, dword ptr [ebp + 0x5ac]'),
 0x6ff725:('mov','dword ptr [0x83995c], ecx'),
 0x6ff76c:('mov','byte ptr [ebp + 0x5bb], 1'),
 0x6ff837:('mov','dword ptr [0xad0490], eax'),
 0x6ff841:('mov','dword ptr [0xad0494], ecx'),
 0x6ff847:('mov','dword ptr [0xad0498], edx'),
 0x6ff84d:('mov','dword ptr [0xad049c], eax'),
 0x6ff8bf:('lea','eax, [ebx + 0x214]'),
 0x6ffb1c:('lea','edi, [ebx + 0x228]'),
 0x6ffb85:('lea','edi, [ebx + 0x250]'),
 0x70019b:('mov','dword ptr [0x83995c], esi'),
 0x7001b4:('mov','byte ptr [ebp + 0x5bb], 0'),
}
def verify(disc,data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied base executable required')
 inherited=parent(disc,data);pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 instructions={i.address:(i.mnemonic,i.op_str) for i in cs.disasm(pe.get_data(0x6ff690-0x400000,0xf15),0x6ff690)}
 for address,expected in OPERANDS.items():
  if instructions.get(address)!=expected:raise ValueError('Shared staging association differs: '+hex(address))
 return {'inherited':inherited,'selected_operands':{hex(k):list(v) for k,v in OPERANDS.items()},
  'scope':'Two supplied actor/Drive records share one supplied type/index association and global staging/pool; complete healthy flat Unit/cache/raster/staging/cleanup. Visibility/height/final-world/shadow services and initial records supplied. No live movement/prepared-map/two-Unit runtime/frame claim.'}
