// void __fastcall Unknown_005cd540(HWND dialog) (0x005CD540)
#include "shared/lobby.hpp"
// @ref ?Unknown_005cd3f0@@YIXPAUHWND__@@@Z=005cd3f0

void __fastcall Unknown_005cd540(HWND dialog)
{
    if (dialog != 0) {
        Unknown_005cd3f0(dialog);
    }
    HWND other = Find_Dialog_00735940(0x116);
    if (other != 0) {
        Unknown_005cd3f0(other);
    }
    other = Find_Dialog_00735940(0x113);
    if (other != 0) {
        Unknown_005cd3f0(other);
    }
    other = Find_Dialog_00735940(0xbb);
    if (other != 0) {
        Unknown_005cd3f0(other);
    }
}
