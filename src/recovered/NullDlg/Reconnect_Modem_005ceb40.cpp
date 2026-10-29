// bool Reconnect_Modem() (0x005CEB40)
// Restores a lost serial connection by the session's modem role: a null
// modem, or a modem that still has carrier, reconnects; otherwise the dialer
// redials and the answerer answers again.
#include "shared/null_dlg.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?serial_local_player_00a3fb38@@3HA=00a3fb38
// @ref ?DialSettings@@3PAUSerialSettingsType@@A=00a72dc4
// @ref ?Get_Modem_Status@NullModemClass@@QAEHXZ=005d1e50
// @ref ?Reconnect_Null_Modem@@YI_NXZ=005cedd0
// @ref ?Dial_Modem@@YI_NPAUSerialSettingsType@@_N@Z=005cf0b0
// @ref ?Answer_Modem@@YI_NPAUSerialSettingsType@@_N@Z=005cf780

bool Reconnect_Modem()
{
    bool status = false;
    int modemstatus;

    switch (serial_local_player_00a3fb38) {
        case 0:
        case 1:
            status = Reconnect_Null_Modem();
            break;
        case 2:
            modemstatus = serial_manager_00a40a28.Get_Modem_Status();
            if (modemstatus & 0x80) {
                status = Reconnect_Null_Modem();
            } else {
                status = Dial_Modem(DialSettings, true);
            }
            break;
        case 3:
            modemstatus = serial_manager_00a40a28.Get_Modem_Status();
            if (modemstatus & 0x80) {
                status = Reconnect_Null_Modem();
            } else {
                status = Answer_Modem(DialSettings, true);
            }
            break;
    }
    return status;
}
