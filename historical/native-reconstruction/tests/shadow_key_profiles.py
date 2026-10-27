# SPDX-License-Identifier: GPL-3.0-or-later
"""Explicit research-only flat Unit shadow keys and complete Foot dispatch mappings."""
from staging_profiles import PATCHED_ADDRESSES as INHERITED, staging_profile

SHADOW_KEY_ADDRESSES = {
    0x0046C000: 0x0046C400,
    0x00482CC0: 0x00482F20,
    0x00482D00: 0x00482F60,
    0x004C94F0: 0x004C9A40,
    0x0050DCA0: 0x0050E9A0,
    0x0050E710: 0x0050F410,
    0x0053B250: 0x0053D1C0,
    0x0053B570: 0x0053D4E0,
    0x006D03D8: 0x006DAFB8,
    0x006D2524: 0x006DD104,
    0x006D25A6: 0x006DD186,
    0x006F4327: 0x006FF7F7,
    0x006F4346: 0x006FF816,
    0x006F4D03: 0x007001D3,
    0x006F4DC9: 0x00700299,
    0x006F5086: 0x00700556,
    0x006FF65A: 0x0070ABEA,
    0x006FF678: 0x0070AC08,
    0x0076D4B0: 0x00781F20,
    0x00780EC0: 0x00795940,
    0x007B8E5C: 0x007CDECC,
    0x007B9E00: 0x007CEE70,
    0x007BCA80: 0x007D1AE8,
    0x007BCAC0: 0x007D1B28,
    0x007BE9DC: 0x007D38A8,
    0x007BE9FC: 0x007D38C8,
    0x007BEB24: 0x007D39F0,
    0x007BEB30: 0x007D39FC,
    0x007BEB38: 0x007D3A04,
    0x007BEB40: 0x007D3A0C,
    0x007BEB48: 0x007D3A14,
    0x007BEB50: 0x007D3A1C,
    0x007BEB58: 0x007D3A24,
    0x007E0FF4: 0x007F7774,
    0x007E1938: 0x007F80B8,
    0x00824884: 0x0083C55C,
}
PATCHED_ADDRESSES = {**INHERITED, **SHADOW_KEY_ADDRESSES}

def shadow_key_profile(data, *, allow_patched=False):
    return staging_profile(data, allow_patched=allow_patched)

def address(profile, disc_va):
    if profile == "allied-disc":
        return disc_va
    if profile == "supplied-ra2-1006":
        try:
            return PATCHED_ADDRESSES[disc_va]
        except KeyError as error:
            raise ValueError(f"Unmapped 1.006 shadow-key address {disc_va:#x}") from error
    raise ValueError("Unknown shadow-key profile")
