# SPDX-License-Identifier: GPL-3.0-or-later
"""Explicit research-only lit actor keys and successful voxel-index mappings."""
from unit_light_profiles import PATCHED_ADDRESSES as INHERITED, unit_light_profile

VOXEL_CACHE_ADDRESSES = {
    0x004F4660: 0x004F52B0,
    0x0050CAF0: 0x0050D7F0,
    0x0050E710: 0x0050F410,
    0x006C7120: 0x006D1D00,
    0x006C714A: 0x006D1D2A,
    0x006C7162: 0x006D1D42,
    0x006C7169: 0x006D1D49,
    0x006C727C: 0x006D1E5C,
    0x006C75E2: 0x006D21C2,
    0x006C75EC: 0x006D21CC,
    0x006C7900: 0x006D24E0,
    0x006CDB4D: 0x006D872D,
    0x006CDB59: 0x006D8739,
    0x006CDB63: 0x006D8743,
    0x006CDB8A: 0x006D876A,
    0x006CDB9F: 0x006D877F,
    0x006CDBB4: 0x006D8794,
    0x006CDBBB: 0x006D879B,
    0x006CDBE4: 0x006D87C4,
    0x006CDC1C: 0x006D87FC,
    0x006CEC70: 0x006D9850,
    0x006D2DE1: 0x006DD9C1,
    0x006D2E8A: 0x006DDA6A,
    0x006F42F1: 0x006FF7C1,
    0x006F4327: 0x006FF7F7,
    0x006F445B: 0x006FF92B,
    0x006F44AB: 0x006FF97B,
    0x007E0BC8: 0x007F7348,
    0x007E0C0C: 0x007F738C,
    0x00821B10: 0x008397F0,
}
PATCHED_ADDRESSES = {**INHERITED, **VOXEL_CACHE_ADDRESSES}

def voxel_cache_profile(data, *, allow_patched=False):
    return unit_light_profile(data, allow_patched=allow_patched)

def address(profile, disc_va):
    if profile == "allied-disc":
        return disc_va
    if profile == "supplied-ra2-1006":
        try:
            return PATCHED_ADDRESSES[disc_va]
        except KeyError as error:
            raise ValueError(f"Unmapped 1.006 voxel-cache address {disc_va:#x}") from error
    raise ValueError("Unknown voxel-cache profile")
