# SPDX-License-Identifier: GPL-3.0-or-later
"""Explicit research-only healthy Terrain, SHP and type/reload mappings.

The SHP prologue/cleanup differ; their inspected fingerprints are verified
separately. Only the valid-shape ordinary domain receives executed parity.
"""
from unit_light_profiles import PATCHED_ADDRESSES as INHERITED, unit_light_profile

SCENERY_ADDRESSES = {
    0x00434F80: 0x004350C0,
    0x00485B40: 0x00485D60,
    0x004878C0: 0x00487AE0,
    0x00487930: 0x00487B50,
    0x00489000: 0x00489220,
    0x004890F0: 0x00489310,
    0x0048A4A0: 0x0048A6C0,
    0x0048BC60: 0x0048BE80,
    0x0048CA50: 0x0048CC70,
    0x0048CEF0: 0x0048D110,
    0x0048D250: 0x0048D470,
    0x0048D610: 0x0048D830,
    0x0049EA80: 0x0049EEA0,
    0x0049EAB3: 0x0049EEDE,
    0x0049EF53: 0x0049F37E,
    0x0049EF61: 0x0049F38B,
    0x0049F000: 0x0049F430,
    0x00592370: 0x005956C0,
    0x005CACF0: 0x005D27B0,
    0x005CFD50: 0x005D7810,
    0x006D8B00: 0x006E3990,
    0x006DA5D0: 0x006E5460,
    0x006DA7A0: 0x006E5630,
    0x006DA7D9: 0x006E5669,
    0x006DA9A6: 0x006E5836,
    0x0076E780: 0x007831F0,
    0x00774EB0: 0x00789930,
    0x00785BAC: 0x0079ABAC,
    0x0079827C: 0x007AD3CC,
    0x00798490: 0x007AD5E0,
    0x007C3965: 0x007D88D5,
    0x007C396C: 0x007D88DC,
    0x0081A6DC: 0x008323BC,
    0x00821C7C: 0x0083995C,
    0x00836DA0: 0x0084EA78,
    0x0083AC60: 0x00852950,
    0x0083AC64: 0x00852954,
    0x0083AC68: 0x00852958,
    0x0083AC6C: 0x0085295C,
    0x00A27F54: 0x00A40324,
    0x00A27F60: 0x00A40330,
    0x00A28933: 0x00A40D13,
}
PATCHED_ADDRESSES = {**INHERITED, **SCENERY_ADDRESSES}

def scenery_profile(data, *, allow_patched=False):
    return unit_light_profile(data, allow_patched=allow_patched)

def address(profile, disc_va):
    if profile == "allied-disc":
        return disc_va
    if profile == "supplied-ra2-1006":
        try:
            return PATCHED_ADDRESSES[disc_va]
        except KeyError as error:
            raise ValueError(f"Unmapped 1.006 scenery address {disc_va:#x}") from error
    raise ValueError("Unknown scenery profile")
