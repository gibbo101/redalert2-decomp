// int __fastcall unknown_script_mission_6eafe0(int mission) (0x006EAFE0)
// Maps a script action to a small code (no caller in the decompiled listing;
// the codes' meaning is unknown).
#include "shared/script.hpp"

int __fastcall unknown_script_mission_6eafe0(int mission)
{
    switch (mission) {
    case 0:
    case 0x39:
        return 0xf;
    case 4:
        return 0x13;
    case 0x22:
        return 0x20;
    case 0xc:
    case 0x26:
        return 0x16;
    case 0x27:
    case 0x28:
        return 0x1d;
    case 5:
    case 6:
    case 0xd:
    case 0x20:
    case 0x2a:
    case 0x32:
        return 10;
    case 1:
    case 3:
    case 0xf:
    case 0x10:
        return 9;
    case 0x14:
        return 0xd;
    case 0xb:
        return 0x12;
    case 0x11:
        return 0x14;
    case 0x12:
        return 0xc;
    case 0x18:
        return 4;
    case 0x19:
        return 3;
    case 0x1a:
        return 2;
    case 0x1b:
        return 1;
    case 0x2e:
    case 0x2f:
    case 0x38:
    case 0x3a:
        return 0x24;
    case 8:
        return 0x25;
    case 0x33:
        return 0x29;
    case 0x34:
        return 0x2a;
    }
    return 0;
}
