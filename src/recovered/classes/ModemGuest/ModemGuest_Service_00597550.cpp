// ModemGuest::Service_00597550 (0x00597550)
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
// @ref ?Send_Options_00598330@ModemGuest@@QAEXXZ=00598330
// @ref ?serial_local_player_00a3fb38@@3HA=00a3fb38
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
void ModemGuest::Service_00597550(bool force)
{
    serial_manager_00a40a28.Service();
    if ((OptionsChanged == true && TickCount.Time() - OptionsTime > 30) || force == true) {
        Send_Options_00598330();
        OptionsTime = TickCount.Time();
        OptionsChanged = false;
    }
    if (TickCount.Time() - TimingTime > 40) {
        UnknownSerialPacket packet;
        memset(&packet, 0, sizeof(packet));
        packet.Command = 0x69;
        packet.Timing.ResponseTime = serial_manager_00a40a28.Response_Time();
        packet.ID = serial_local_player_00a3fb38;
        serial_manager_00a40a28.Send_Message(&packet, sizeof(packet), 0);
        TimingTime = TickCount.Time();
    }
}
