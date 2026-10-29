// bool __fastcall unknown_dialog_c2_call(int count, bool unknown_1, bool unknown_2) -- 0x0075CA30
// Purpose: answers Unknown_005cbdb0 (0x005CBDB0) for dialog 0xC2 (found by 0x00735940).
#include "shared/lobby.hpp"
// @ref ?Find_Dialog_00735940@@YIPAUHWND__@@H@Z=00735940
// @ref ?Unknown_005cbdb0@@YI_NPAUHWND__@@H_N1@Z=005cbdb0

bool __fastcall unknown_dialog_c2_call(int count, bool unknown_1, bool unknown_2)
{
    HWND dialog = Find_Dialog_00735940(0xC2);
    return Unknown_005cbdb0(dialog, count, unknown_1, unknown_2);
}
