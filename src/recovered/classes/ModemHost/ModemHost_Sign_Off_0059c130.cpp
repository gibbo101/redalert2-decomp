// ModemHost::Sign_Off_0059c130 (0x0059C130)
#include "shared/modem_host.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/null_dlg.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/string_table.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/keyboard.hpp"
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?serial_local_player_00a3fb38@@3HA=00a3fb38
// @ref ?TickCount@@3V?$TTimerClass@VSystemTimerClass@@@@A=00839980
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ??_C@_0BA@JILO@TXT_SIGNING_OFF?$AA@=007e2294
// @ref ??_C@_0BE@EBDB@D?3?2Ra2?2ModemHst?4cpp?$AA@=007e247c

void ModemHost::Sign_Off_0059c130()
{
    UnknownSerialPacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x66;
    packet.ScenarioInfo.Color = unknown_a3d3b4;
    packet.ID = serial_local_player_00a3fb38;
    serial_manager_00a40a28.Send_Message(&packet, sizeof(packet), 1);
    HWND dialog = unknown_cancel_dialog_6001e0(
        StringTable::Load_String("TXT_SIGNING_OFF", 0, "D:\\Ra2\\ModemHst.cpp", 0x95E), 0, 0);
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
