// 0x00495770: function not yet identified
//
// Body: 100 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_00495770(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_00495770 {

extern undefined4  FUN_007820f4(int, int, int);
extern "C" __declspec(dllimport) undefined4 __stdcall MessageBoxA(int, int, int, int);  // @ref __imp__MessageBoxA@16=0079a47c
extern "C" undefined4 DAT_007d59f4;
extern "C" code * DAT_008523ec;
extern "C" undefined4 DAT_00b263d8;
extern "C" char s_DDRAW_DLL_Error_code____08X_007d59a8[];
extern "C" char s_Direct_Draw_operation_processed_w_007d59c4[];
extern "C" char s_Direct_X_007d599c[];

void __fastcall FUN_00495770(int param_1, int param_2)
{
    CHAR local_50 [80];

    if (param_1 == 0) {
        if (param_2 != 0) {
            MessageBoxA((int)(DAT_00b263d8), (int)(s_Direct_Draw_operation_processed_w_007d59c4), (int)(&DAT_007d59f4), (int)(0));
            return;
        }
    }
    else {
        if ((uint)(DAT_008523ec) != (uint)((code *)0x0)) {
            (*DAT_008523ec)();
            return;
        }
        FUN_007820f4((int)(local_50), (int)(s_DDRAW_DLL_Error_code____08X_007d59a8), (int)(param_1));
        MessageBoxA((int)(DAT_00b263d8), (int)(local_50), (int)(s_Direct_X_007d599c), (int)(0x30));
    }
    return;
}

}  // namespace seed_00495770
