// ModemHost::Idle_0059c880 (0x0059C880)
#include "shared/modem_host.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/lobby.hpp"
#include "shared/comm_buffer.hpp"
// @ref ?unknown_modem_host_a70de4@@3PAVModemHost@@A=00a70de4
// @ref ?Process_Messages_0059b690@ModemHost@@QAE_N_N@Z=0059b690

bool ModemHost::Idle_0059c880()
{
    if (unknown_modem_host_a70de4) {
        unknown_modem_host_a70de4->Service_0059b560(false);
        unknown_modem_host_a70de4->Process_Messages_0059b690(true);
    }
    Service_Game_IO_00481fb0();
    return false;
}
