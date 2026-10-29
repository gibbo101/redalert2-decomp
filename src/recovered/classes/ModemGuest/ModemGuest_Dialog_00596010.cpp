// ModemGuest::Dialog_00596010 (0x00596010)
#include "shared/modem_guest.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/trigger_type.hpp"
#include "shared/lobby.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/null_dlg.hpp"
#include "shared/string_table.hpp"
#include "shared/keyboard.hpp"
#include "shared/map_preview.hpp"
#include "shared/options_dialog.hpp"
#include "shared/session_state.hpp"
// @ref ??_C@_04NCCD@true?$AA@=007d24d8
// @ref ??_C@_05NAGO@false?$AA@=007d24d0
// @ref ??_C@_0BK@KDAM@ModemGuest?4Dialog?$CIenter?$CJ?6?$AA@=007e1e3c
// @ref ??_C@_0BM@EBMH@ModemGuest?4Dialog?$CIexit?5?$CFs?$CJ?6?$AA@=007e1e20
// @ref ?Dialog_Proc_00596170@ModemGuest@@SGHPAUHWND__@@IIJ@Z=00596170
// @ref ?Init_Dialog_00596540@ModemGuest@@QAEXXZ=00596540
// @ref ?Process_Messages_00597680@ModemGuest@@QAE_NXZ=00597680
// @ref ?Service_00597550@ModemGuest@@QAEX_N@Z=00597550
// @ref ?Sign_Off_00598590@ModemGuest@@QAEXXZ=00598590
// @ref ?Unknown_006525F0@@YIHXZ=006525f0
// @ref ?unknown_517370@@YIX_N@Z=00517370
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
bool ModemGuest::Dialog_00596010()
{
    bool result = false;
    Debug_Printf("ModemGuest.Dialog(enter)\n");
    Result = -1;
    Window = unknown_create_dialog_5ff610(0xF2, Dialog_Proc_00596170, 0);
    if (Window) {
        SetWindowLongA(Window, 8, (LONG)this);
        Init_Dialog_00596540();
        unknown_dialog_5ff7c0(Window);
        Changed = false;
        OptionsChanged = true;
        OptionsTime = TickCount.Time();
        HostResponseTime = 10000;
        ReceiveTime = TickCount.Time();
        ReceiveTimeout = 1200;
        TimingTime = 0;
        HostName[0] = 0;
        HostColor = -1;
        HostHouse = -1;
        unknown_50 = Unknown_006525F0();
        Read_Art_INI();
        unknown_54 = unknown_art_ini_unique_id();
        unknown_58 = unknown_ini_8397a0_unique_id();
        while (Result < 0) {
            if (unknown_6000d0() == true) {
                break;
            }
            Service_00597550(false);
            if (Process_Messages_00597680() == true) {
                break;
            }
            unknown_517370(false);
        }
        unknown_dialog_5ff6e0(Window);
        if (Changed == true) {
            unknown_session_a3d298.Write_MultiPlayer_Settings();
        }
        if (Result == 1) {
            result = true;
        } else if (Result == 2) {
            result = false;
            Sign_Off_00598590();
        }
    }
    Debug_Printf("ModemGuest.Dialog(exit %s)\n", result == true ? "true" : "false");
    return result;
}
