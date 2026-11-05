// int __fastcall Slot_Control_Id_005c97a0(int slot) (0x005C97A0)
#include "shared/lobby.hpp"

int __fastcall Slot_Control_Id_005c97a0(int slot)
{
    if (slot == 0) {
        return 0x411;
    }
    if (slot == 1) {
        return 0x412;
    }
    if (slot == 2) {
        return 0x413;
    }
    if (slot == 3) {
        return 0x414;
    }
    if (slot == 4) {
        return 0x415;
    }
    if (slot == 5) {
        return 0x416;
    }
    if (slot == 6) {
        return 0x417;
    }
    if (slot == 7) { return 0x418; }
    return -1;
}
