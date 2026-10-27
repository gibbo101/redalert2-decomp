#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact shared insertion/expiry and ordinary list/gadget/node drawing composition."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_message_node import verify as node,RANGES as NODE,TABLES as NODE_TABLES,GLOBALS
from verify_message_expiry import verify as expiry,RANGES as EXPIRY,TABLES as EXPIRY_TABLES
RAW={**EXPIRY,0x4cf260:0x2c,0x5b5b30:0xff}
RANGES={**NODE,**RAW}
TABLES={**NODE_TABLES,**EXPIRY_TABLES,0x7a18b4:0x74}
def verify(data):
 n=node(data);e=expiry(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,size in RANGES.items():
  raw=p.get_data(a-0x400000,size);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=size:raise ValueError('Incomplete pipeline inspection')
  ranges[hex(a)]=dict(bytes=size,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x4cf26c:('and','edi, 0xff'),0x4cf277:('call','dword ptr [eax + 0x6c]'),0x4cf27e:('call','dword ptr [edx + 4]'),0x5b5b49:('je','0x5b5c1d'),0x5b5c26:('push','1'),0x5b5c28:('call','dword ptr [edx + 0x2c]')}.items():
  if ops.get(a)!=op:raise ValueError('Pipeline association differs '+hex(a))
 table=p.get_data(0x7adccc-0x400000,0x74)
 if struct.unpack_from('<I',table,0x2c)[0]!=0x4cf260 or struct.unpack_from('<I',table,4)[0]!=0x4cf190:raise ValueError('Text-node traversal targets differ')
 return dict(node=n,expiry=e,ranges=ranges,base_gadget_table=hashlib.sha256(p.get_data(0x7a18b4-0x400000,0x74)).hexdigest(),scope='Complete4CF260 plus5B5B30 ordinary editor-byte0, actual shared insertion/expiry/node/text pixels. Heap/time/audio/surface/IME/fill/line and initial records supplied. Editor/input, production ownership and SDL remain open.')
