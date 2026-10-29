// ModemHost::Dialog_00598e10 (0x00598E10)
#include "shared/modem_host.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/debug_printf.hpp"
// @ref ?TickCount@@3V?$TTimerClass@VSystemTimerClass@@@@A=00839980
// @ref ?unknown_modem_host_a70de4@@3PAVModemHost@@A=00a70de4
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__SetWindowLongA@12=0079a488
// @ref __imp__ShowWindow@8=0079a498
// @ref ?Dialog_Proc_00598fa0@ModemHost@@SGHPAUHWND__@@IIJ@Z=00598fa0
// @ref ?Init_Dialog_00599920@ModemHost@@QAEXXZ=00599920
// @ref ?Start_Game_0059c290@ModemHost@@QAE_N_N@Z=0059c290
// @ref ?Service_0059b560@ModemHost@@QAEX_N@Z=0059b560
// @ref ?Process_Messages_0059b690@ModemHost@@QAE_N_N@Z=0059b690
// @ref ?Sign_Off_0059c130@ModemHost@@QAEXXZ=0059c130
// @ref ??_C@_04NCCD@true?$AA@=007d24d8
// @ref ??_C@_05NAGO@false?$AA@=007d24d0
// @ref ??_C@_0BJ@HKPJ@ModemHost?4Dialog?$CIenter?$CJ?6?$AA@=007e2430
// @ref ??_C@_0BL@ENPP@ModemHost?4Dialog?$CIexit?5?$CFs?$CJ?6?$AA@=007e2414

bool ModemHost::Dialog_00598e10()
{
    bool result = false;
    Debug_Printf("ModemHost.Dialog(enter)\n");
    Result = -1;
    Window = unknown_create_dialog_5ff610(0xF1, Dialog_Proc_00598fa0, 0);
    if (Window) {
        SetWindowLongA(Window, 8, (LONG)this);
        Init_Dialog_00599920();
        unknown_dialog_5ff7c0(Window);
        Changed = false;
        OptionsChanged = true;
        OptionsTime = TickCount.Time();
        GuestResponseTime = 10000;
        ReceiveTime = TickCount.Time();
        ReceiveTimeout = 1200;
        TimingTime = 0;
        unknown_20 = false;
        GuestName[0] = 0;
        GuestColor = -1;
        GuestHouse = -1;
        unknown_modem_host_a70de4 = this;
        unknown_54 = Unknown_006525F0();
        Read_Art_INI();
        unknown_58 = unknown_art_ini_unique_id();
        unknown_5c = unknown_ini_8397a0_unique_id();
        for (;;) {
            Result = -1;
            while (Result < 0) {
                if (unknown_6000d0() == true) {
                    break;
                }
                Service_0059b560(false);
                if (Process_Messages_0059b690(false) == true) {
                    break;
                }
                unknown_517370(false);
            }
            if (Result != 1) {
                break;
            }
            ShowWindow(Window, 0);
            if (Start_Game_0059c290(false) == true) {
                result = true;
                break;
            }
            ShowWindow(Window, 5);
        }
        unknown_dialog_5ff6e0(Window);
        unknown_modem_host_a70de4 = 0;
        if (Changed == true) {
            unknown_session_a3d298.Write_MultiPlayer_Settings();
        }
    }
    if (Result == 2) {
        Sign_Off_0059c130();
    }
    Debug_Printf("ModemHost.Dialog(exit %s)\n", result == true ? "true" : "false");
    return result;
}
