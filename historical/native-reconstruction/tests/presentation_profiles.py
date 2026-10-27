# SPDX-License-Identifier: GPL-3.0-or-later
"""Hash-selected presentation primitive profiles; other boundaries default to disc.

Metadata recovered from the two supplied engines. No general relocation rule,
original code, or implicit runtime/preparation promotion is provided here.
"""
import hashlib
from compare_original import EXPECTED, PATCHED_EXPECTED

PATCHED_ADDRESSES = {
    0x710480: 0x71BA20, 0x710500: 0x71BAA0, 0x710740: 0x71BCE0,
    0x536B30: 0x538AA0, 0x487750: 0x487970,
    0x70F4C9: 0x71AA69, 0x70F4FC: 0x71AA9C,
    0x4B9F30: 0x4BA410, 0x76A6B0: 0x77F110,
    0x536FA0: 0x538F10,
    # Optimized palette targets are inspection metadata, not executed claims.
    0x7829C0: 0x797440, 0x782CFA: 0x79777A,
    0x78303A: 0x797ABA, 0x78337A: 0x797DFA,
    0x785738: 0x79A738, 0x786610: 0x79B610, 0x788578: 0x79D578,
    0x7905D0: 0x7A55E8, 0x7998D8: 0x7AEA40,
    0x7C39F4: 0x7D8964, 0x7CA390: 0x7DF768, 0x7CA490: 0x7DF868,
    0x7E37D0: 0x7F9F80, 0x7E37E4: 0x7F9F94, 0x80011C: 0x817DFC,
    0x821F8C: 0x839C6C,
    0x83B2C8: 0x852FB8, 0x83B2CC: 0x852FBC, 0x83B2D0: 0x852FC0,
    0x83B2D4: 0x852FC4, 0x83B2D8: 0x852FC8, 0x83B2DC: 0x852FCC,
    0xADC068: 0xAF4608, 0xAE0870: 0xAF8E10,
    0xAE096D: 0xAF8F0D, 0xAE096E: 0xAF8F0E, 0xAE096F: 0xAF8F0F,
}

RETAINED_RENDER_SHA256 = '50d2876e6bf8a3b9d535a1843ef93f41109b7021a15e1dbacb47aaa881389c6d'
RETAINED_VPL_SHA256 = '2d75fff8a6872ffe98308c7009858a9e904696e1529bc649181a44993979081c'


def presentation_profile(data, *, allow_patched=False):
    digest = hashlib.sha256(data).hexdigest()
    if digest == EXPECTED:
        return digest, 'allied-disc'
    if allow_patched and digest == PATCHED_EXPECTED:
        return digest, 'supplied-ra2-1006'
    raise ValueError('Unsupported executable hash for this presentation boundary')


def address(profile, disc_va):
    if profile == 'allied-disc':
        return disc_va
    if profile == 'supplied-ra2-1006':
        try:
            return PATCHED_ADDRESSES[disc_va]
        except KeyError as error:
            raise ValueError(f'Unmapped 1.006 presentation address {disc_va:#x}') from error
    raise ValueError('Unknown presentation profile')
