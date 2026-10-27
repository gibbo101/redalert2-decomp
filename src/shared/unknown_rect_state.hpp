// An unidentified object reset by 0x004321B0 (no direct callers: an
// out-of-line copy). Only the fields the reset writes are known.
#ifndef RA2_SHARED_UNKNOWN_RECT_STATE_HPP
#define RA2_SHARED_UNKNOWN_RECT_STATE_HPP

#include "shared/win32_api.hpp"

struct UnknownRectState_004321b0 {
    void unknown_reset_004321b0();  // 0x004321B0

    int unknown_00;                 // +0x00 (not written by the reset)
    int unknown_04;                 // +0x04
    int unknown_08;                 // +0x08
    int unknown_0C;                 // +0x0C
    int unknown_10;                 // +0x10
    int unknown_14;                 // +0x14
    int unknown_18;                 // +0x18
    int unknown_1C;                 // +0x1C
    int unknown_20;                 // +0x20
    short unknown_24;               // +0x24 (reset to 0x7FFF)
    short unknown_26;               // +0x26 (reset to 0x3555)
    int unknown_28;                 // +0x28 (reset to 0x40)
    int unknown_2C;                 // +0x2C
    RECT unknown_30;                // +0x30 (emptied)
    bool unknown_40;                // +0x40
    bool unknown_41;                // +0x41
};

#endif
