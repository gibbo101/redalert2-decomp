// void __fastcall Unknown_Remove_Modeless_Dialog_00522b80(HWND dialog) (0x00522B80)
// Clears the dialog's slot in the modeless dialog list at 0x00A522B4 (0x00522B20 adds; the mono window
// 0x0059D900/0x0059DB30 uses both).
#include "shared/audio_file.hpp"
extern "C" int DAT_00a521dc;                    // 0x00A521DC list capacity
// @ref _DAT_00a521dc=00a521dc
// @ref _DAT_00a522b0=00a522b0
// @ref _DAT_00a522b4=00a522b4
// @ref _DAT_00a522b8=00a522b8

void __fastcall Unknown_Remove_Modeless_Dialog_00522b80(HWND__ *dialog)
{
    if (DAT_00a522b0 != 0 && dialog != 0) {
        HWND__ **slot = (HWND__ **)DAT_00a522b4;
        for (int index = 1; index < DAT_00a521dc; index++, slot++) {
            if (*slot == dialog) {
                *slot = 0;
                DAT_00a522b8--;
                return;
            }
        }
    }
}
