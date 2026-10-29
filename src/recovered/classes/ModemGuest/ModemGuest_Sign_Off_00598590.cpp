// ModemGuest::Sign_Off_00598590 (0x00598590)
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
// @ref ??_C@_0BA@JILO@TXT_SIGNING_OFF?$AA@=007e2294
// @ref ??_C@_0BE@PMHE@D?3?2Ra2?2ModemGst?4cpp?$AA@=007e2014
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0
// @ref ?Unknown_005B5EE0@@YAXXZ=005b5ee0
// @ref ?serial_local_player_00a3fb38@@3HA=00a3fb38
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_cancel_dialog_6001e0@@YIPAUHWND__@@PBG0PA_N@Z=006001e0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
void ModemGuest::Sign_Off_00598590()
{
    UnknownSerialPacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x66;
    packet.ScenarioInfo.Color = unknown_a3d3b4;
    packet.ID = serial_local_player_00a3fb38;
    serial_manager_00a40a28.Send_Message(&packet, sizeof(packet), 1);
    HWND dialog = unknown_cancel_dialog_6001e0(
        StringTable::Load_String("TXT_SIGNING_OFF", 0, "D:\\Ra2\\ModemGst.cpp", 0x693), 0, 0);
    if (dialog) {
        unknown_dialog_5ff7c0(dialog);
    }
    unsigned long start = TickCount.Time();
    while (serial_manager_00a40a28.Num_Send() && TickCount.Time() - start < 300) {
        UnknownSerialPacket reply;
        int length;
        if (serial_manager_00a40a28.Get_Message(&reply, &length) > 0 && reply.Command == 0x66
            && reply.ID == serial_local_player_00a3fb38) {
            break;
        }
        Service_Game_IO_00481fb0();
        Unknown_005B5EE0();
        serial_manager_00a40a28.Service();
    }
    Shutdown_Modem();
    if (dialog) {
        unknown_dialog_5ff6e0(dialog);
    }
}
