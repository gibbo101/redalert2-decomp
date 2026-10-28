// int __fastcall unknown_control_player_4d0f40(int id) (0x004D0F40)
// The player row of a 0x6DA-0x6E1 control id (the inverse of 0x004D0EE0), or -1.
#include "shared/gdlg_supp.hpp"

int __fastcall unknown_control_player_4d0f40(int id)
{
    if (id == 0x6DA) {
        return 0;
    }
    if (id == 0x6DB) {
        return 1;
    }
    if (id == 0x6DC) {
        return 2;
    }
    if (id == 0x6DD) {
        return 3;
    }
    if (id == 0x6DE) {
        return 4;
    }
    if (id == 0x6DF) {
        return 5;
    }
    if (id == 0x6E0) {
        return 6;
    }
    if (id == 0x6E1) {
        return 7;
    }
    return -1;
}
