#include "shared/owner_draw_dialog_control.hpp"
namespace OwnerDraw {
// Enables the owner-draw flags for the original ordered dialog-kind set, 005E9FA0.
bool __fastcall unknown_5e9fa0(HWND dialog)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find((unsigned int)dialog);
    if (!record) return false;
    int kind = record->unknown_6c;
    bool special = kind == 0x10c ||
        kind == 0x94 ||
        kind == 0xb6 ||
        kind == 0xa3 ||
        kind == 0x73 ||
        kind == 0xd8 ||
        kind == 0xbbb ||
        kind == 0xf5 ||
        kind == 0x105 ||
        kind == 0xd5 ||
        kind == 0xe2 ||
        kind == 0x2b5 ||
        kind == 0xb7 ||
        kind == 0x2b4 ||
        kind == 0x101 ||
        kind == 0x129 ||
        kind == 0xbc6 ||
        kind == 0xbc7 ||
        kind == 0x10b ||
        kind == 0xd7 ||
        kind == 0x108 ||
        kind == 0xbc ||
        kind == 0xbd ||
        kind == 0xbb ||
        kind == 0xb5 ||
        kind == 0xbba ||
        kind == 0xff ||
        kind == 0xea ||
        kind == 0x6b ||
        kind == 0x100 ||
        kind == 0x102 ||
        kind == 0xb8 ||
        kind == 0xd6 ||
        kind == 0x103 ||
        kind == 0xd4 ||
        kind == 0x125 ||
        kind == 0x122 ||
        kind == 0x112 ||
        kind == 0xe7 ||
        kind == 0x116 ||
        kind == 0xc2 ||
        kind == 0xc9 ||
        kind == 0x113 ||
        kind == 0xfe ||
        kind == 0x10f ||
        kind == 0x11d ||
        kind == 0x11c ||
        kind == 0x117 ||
        kind == 0x114 ||
        kind == 0xe6 ||
        kind == 0xf3 ||
        kind == 0xf4 ||
        kind == 0x2bc ||
        kind == 0x10e ||
        kind == 0xfb;
    if (special) {
        record->unknown_b0 = 1;
        record->unknown_bd = true;
    }
    return special;
}
}
