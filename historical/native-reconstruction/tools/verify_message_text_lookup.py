#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete message-color lookup and action11 -> actual string lookup."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import verify as strings,RANGES as STRING_RANGES
from verify_mission_text_action import verify as action,RANGES as ACTION_RANGES,TABLES
RANGES={**STRING_RANGES,**ACTION_RANGES,0x6715d0:0x27}
def verify(data):
 s=strings(data);a=action(data);p=pefile.PE(data=data);raw=p.get_data(0x6715d0-0x400000,0x27)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,0x6715d0));ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 if sum(i.size for i in ins)!=0x27:raise ValueError('Message color inspection incomplete')
 for address,op in {0x6715d4:('cmp','eax, -2'),0x6715d9:('mov','eax, 8'),0x6715de:('movsx','eax, byte ptr [eax + 0x7f3224]'),0x6715e8:('cmp','eax, 9'),0x6715eb:('jae','0x6715f4'),0x6715ed:('movsx','eax, byte ptr [eax + 0x7f3224]'),0x6715f4:('ret','4')}.items():
  if ops.get(address)!=op:raise ValueError('Message color association differs '+hex(address))
 return dict(strings=s,action=a,color_code_sha256=hashlib.sha256(raw).hexdigest(),color_table_sha256=hashlib.sha256(p.get_data(0x7f3224-0x400000,9)).hexdigest(),scope='Complete color root and action11 through actual found-label lookup/CRT comparison; message insertion remains supplied. Fixture color tables/labels/slots, locale0 and startup remain supplied.')
