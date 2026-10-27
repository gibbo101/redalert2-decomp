# SPDX-License-Identifier: GPL-3.0-or-later
"""Explicit research-only ordinary map-light and visible-alpha mappings."""
from staging_profiles import PATCHED_ADDRESSES as STAGING, staging_profile

MAP_LIGHT_ADDRESSES = {
    0x410A60: 0x410A60,
    0x41FDF0: 0x41FDF0,
    0x438140: 0x4382C0,
    0x453AB0: 0x453E40,
    0x4702C0: 0x4706C0,
    0x479040: 0x479440,
    0x498A87: 0x498DF7,
    0x4B9F34: 0x4BA414,
    0x51F040: 0x51FC50,
    0x51F050: 0x51FC60,
    0x536450: 0x5383C0,
    0x659071: 0x662211,
    0x65907C: 0x66221C,
    0x659160: 0x662300,
    0x65916B: 0x66230B,
    0x75F930: 0x774390,
    0x75F960: 0x7743C0,
    0x785F8C: 0x79AF8C,
    0x7867F0: 0x79B7F0,
    0x787528: 0x79C528,
    0x7882E0: 0x79D2E0,
    0x7905A8: 0x7A55C0,
    0xA255A0: 0xA3D290,
    0xA2874C: 0xA40B2C,
    0xA39554: 0xA51934,
    0xA3955C: 0xA5193C,
    0xA5642C: 0xA6E81C,
    0xA56438: 0xA6E828,
}
PATCHED_ADDRESSES = {**STAGING, **MAP_LIGHT_ADDRESSES}

def map_light_profile(data, *, allow_patched=False):
    return staging_profile(data, allow_patched=allow_patched)

def address(profile, disc_va):
    if profile == "allied-disc":
        return disc_va
    if profile == "supplied-ra2-1006":
        try:
            return PATCHED_ADDRESSES[disc_va]
        except KeyError as error:
            raise ValueError(f"Unmapped 1.006 map-light address {disc_va:#x}") from error
    raise ValueError("Unknown map-light profile")
