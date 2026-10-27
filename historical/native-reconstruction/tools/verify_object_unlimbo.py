# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete exact-base Object Unlimbo; executed domain excludes radial creation."""
import hashlib,pefile,capstone
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x5d3890:824}
HASH='9e8f4bbebf022c9a4b1dc2fb66ef687116a0c556601f9520f6936ca0f7a96b04'
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Object Unlimbo requires exact supplied base')
 p=pefile.PE(data=data);raw=p.get_data(0x5d3890-0x400000,824);ins=list(capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32).disasm(raw,0x5d3890))
 if hashlib.sha256(raw).hexdigest()!=HASH or len(ins)!=265 or sum(i.size for i in ins)!=824 or ins[-1].mnemonic!='ret':raise ValueError('Object Unlimbo complete body differs')
 return dict(complete_parent=dict(bytes=824,instructions=265,sha256=HASH),radial_creation_excluded=True,children_supplied=True)
