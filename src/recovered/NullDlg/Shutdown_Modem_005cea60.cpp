// void Shutdown_Modem() (0x005CEA60)
// Hangs a modem game's line up unless the game is playing, then closes the port.
#include "shared/serial_progress.hpp"
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?unknown_flags_a3f600@@3EA=00a3f600
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Hangup_Modem@NullModemClass@@QAE_NXZ=005d1b70
// @ref ?Shutdown@NullModemClass@@QAEXXZ=005d0570

void Shutdown_Modem()
{
    if (!(unknown_flags_a3f600 & 2)) {
        if (unknown_game_mode_a3d298 == 1) {
            serial_manager_00a40a28.Hangup_Modem();
        }
    }
    serial_manager_00a40a28.Shutdown();
}
