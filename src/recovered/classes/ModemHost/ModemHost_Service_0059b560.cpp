// ModemHost::Service_0059b560 (0x0059B560)
#include "shared/modem_host.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/lobby.hpp"
#include "shared/comm_buffer.hpp"
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?serial_local_player_00a3fb38@@3HA=00a3fb38
// @ref ?TickCount@@3V?$TTimerClass@VSystemTimerClass@@@@A=00839980
// @ref ?Send_Options_0059bc90@ModemHost@@QAEXXZ=0059bc90

void ModemHost::Service_0059b560(bool force)
{
    serial_manager_00a40a28.Service();
    if ((OptionsChanged == true && TickCount.Time() - OptionsTime > 30) || force == true) {
        Send_Options_0059bc90();
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
