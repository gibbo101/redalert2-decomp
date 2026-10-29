// bool __fastcall Unknown_005bc430(int count, bool unknown_1, bool unknown_2) (0x005BC430)
#include "shared/lobby.hpp"

bool __fastcall Unknown_005bc430(int count, bool unknown_1, bool unknown_2)
{
    HWND dialog = Find_Dialog_00735940(0xBC);
    return Unknown_005cbdb0(dialog, count, unknown_1, unknown_2);
}
