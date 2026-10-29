// int __fastcall Control_Slot_005c9800(int id) (0x005C9800)
#include "shared/lobby.hpp"

int __fastcall Control_Slot_005c9800(int id)
{
    if (id == 0x411) {
        return 0;
    }
    if (id == 0x412) {
        return 1;
    }
    if (id == 0x413) {
        return 2;
    }
    if (id == 0x414) {
        return 3;
    }
    if (id == 0x415) {
        return 4;
    }
    if (id == 0x416) {
        return 5;
    }
    if (id == 0x417) {
        return 6;
    }
    return id == 0x418 ? 7 : -1;
}
