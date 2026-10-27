# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the queued Walk / actual Infantry admission composition independently."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import verify_walk_queued as queued
import verify_infantry_admission as admission
EXTRA={0x503190:0x8ad,0x4c8730:0x207,0x47a130:0x26,0x476ac0:0x56,0x4e5500:0x32,0x491620:172}
RANGES={**queued.RANGES,**EXTRA}
def verify(data):
 result=dict(queued=queued.verify(data),admission=admission.verify(data));p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 raw=p.get_data(0x491620-0x400000,172);ins=list(cs.disasm(raw,0x491620))
 if sum(i.size for i in ins)!=172 or ins[-1].mnemonic!='ret':raise ValueError('Incomplete word offset initializer')
 if p.get_data(0x7a3540+0x198-0x400000,4)!=struct.pack('<I',0x4c8730):raise ValueError('Foot admission dispatch differs')
 return dict(parent=result,initializer_sha256=hashlib.sha256(raw).hexdigest(),
  scope='Complete queued Walk Process with actual Infantry admission/Foot/registry/neighbor/House; result0 continuation only. Same borrowed actor/Cells/House, actual word offset initializer. Parity map/floor/speed/Mark/notification/destination/reset and initial metadata supplied. No production/SDL walking/objective claim.')
