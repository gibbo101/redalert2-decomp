// bool __fastcall Reconnect_Null_Modem() (0x005CEDD0)
// Re-establishes a null-modem link under a "check the cables" dialog: sends
// a connect packet with the local colour every 30 ticks until the other side
// answers with its own (then acknowledges it and services the link for 60
// ticks); the same colour means the other system does not respond. Gives up
// after 900 ticks without a message, or on cancel.
#include "shared/null_dlg.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/string_table.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/crt_string.hpp"
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?Service@NullModemClass@@UAEHXZ=005d0660
// @ref ?Send_Message@NullModemClass@@QAEHPAXHH@Z=005d05f0
// @ref ?Get_Message@NullModemClass@@QAEHPAXPAH@Z=005d0630
// @ref ?TickCount@@3V?$TTimerClass@VSystemTimerClass@@@@A=00839980
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?Process@WWMessageBox@@QAEHPBG000_N@Z=005b46b0
// @ref ?unknown_cancel_dialog_6001e0@@YIPAUHWND__@@PBG0PA_N@Z=006001e0
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?unknown_modem_aborted_a72ec4@@3_NA=00a72ec4
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ??_C@_0L@NPIH@TXT_CANCEL?$AA@=007db8c8
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_0BK@GPBE@TXT_SYSTEM_NOT_RESPONDING?$AA@=007e222c
// @ref ??_C@_0BO@DFHD@TXT_NULL_CONNERR_CHECK_CABLES?$AA@=007e74e4
// @ref ??_C@_0BD@MKPO@D?3?2Ra2?2NullDlg?4CPP?$AA@=007e74bc

bool __fastcall Reconnect_Null_Modem()
{
    bool process = true;
    bool retval = false;
    unsigned long starttime;
    unsigned long lastmsgtime;
    int packetlen;
    UnknownSerialPacket SendPacket;
    UnknownSerialPacket ReceivePacket;

    unknown_modem_aborted_a72ec4 = false;
    HWND dialog = unknown_cancel_dialog_6001e0(
        StringTable::Load_String("TXT_NULL_CONNERR_CHECK_CABLES", 0, "D:\\Ra2\\NullDlg.CPP", 0x1959),
        StringTable::Load_String("TXT_CANCEL", 0, "D:\\Ra2\\NullDlg.CPP", 0x1959), &unknown_modem_aborted_a72ec4);
    if (dialog) {
        unknown_dialog_5ff7c0(dialog);
        starttime = lastmsgtime = TickCount.Time();
        while (process == true) {
            if (unknown_6000d0() == true || unknown_modem_aborted_a72ec4) {
                retval = false;
                break;
            }
            serial_manager_00a40a28.Service();
            if (TickCount.Time() - starttime > 30) {
                starttime = TickCount.Time();
                memset(&SendPacket, 0, sizeof(SendPacket));
                SendPacket.Command = 100;
                SendPacket.ID = unknown_a3d3b4;
                serial_manager_00a40a28.Send_Message(&SendPacket, sizeof(SendPacket), 0);
            }
            if (serial_manager_00a40a28.Get_Message(&ReceivePacket, &packetlen) > 0) {
                lastmsgtime = TickCount.Time();
                if (ReceivePacket.Command == 100) {
                    if (ReceivePacket.ID == unknown_a3d3b4) {
                        WWMessageBox(L" ").Process(StringTable::Load_String("TXT_SYSTEM_NOT_RESPONDING", 0, "D:\\Ra2\\NullDlg.CPP", 0x1982),
                            StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\NullDlg.CPP", 0x1982), 0, 0, false);
                        retval = false;
                        break;
                    }
                    memset(&SendPacket, 0, sizeof(SendPacket));
                    SendPacket.Command = 100;
                    SendPacket.ID = unknown_a3d3b4;
                    serial_manager_00a40a28.Send_Message(&SendPacket, sizeof(SendPacket), 1);
                    starttime = TickCount.Time();
                    while (TickCount.Time() - starttime < 60) {
                        serial_manager_00a40a28.Service();
                    }
                    retval = true;
                    process = false;
                }
            }
            if (TickCount.Time() - lastmsgtime > 900) {
                retval = false;
                process = false;
            }
        }
        unknown_dialog_5ff6e0(dialog);
    }
    return retval;
}
