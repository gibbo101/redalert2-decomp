// bool NullModemClass::Hangup_Modem() (0x005D1B70)
// Hangs the modem up: drops DTR, sends the escape code, then ATH and ATZ.
// Modem servicing (bit 0 of serial_session_flags_00a3fac0) is off meanwhile.
#include "shared/serial_progress.hpp"
#include "shared/crt_string.hpp"
// @ref ?SerialPort@@3PAVWinModemClass@@A=00b25bb0
// @ref ?serial_session_flags_00a3fac0@@3IA=00a3fac0
// @ref ?Wait_Timer_00496A20@@YIXJ@Z=00496a20
// @ref ?Write_To_Serial_Port@WinModemClass@@QAEXPAEH@Z=00734c70
// @ref _strncmp=00783810
// @ref ??_C@_02BKOD@AT?$AA@=007e7ca8
// @ref ??_C@_03LMGC@ATH?$AA@=007e8034
// @ref ??_C@_03EADM@ATZ?$AA@=007e8030
// @ref ??_C@_02HAGF@OK?$AA@=007d5a40

bool NullModemClass::Hangup_Modem()
{
    int status;
    int delay;
    char buffer[81];
    char escape[4];

    if (PortHandle == -1 || !SerialPort) {
        return false;
    }

    serial_session_flags_00a3fac0 &= ~1;

    status = SerialPort->Send_Command_To_Modem("AT", '\r', buffer, 81, 90, 1, -1);
    if (status == 2) {
        serial_session_flags_00a3fac0 |= 1;
        return true;
    }

    SerialPort->Set_Serial_DTR(false);
    Wait_Timer_00496A20(3200 / 60);
    SerialPort->Set_Serial_DTR(true);

    status = SerialPort->Send_Command_To_Modem("AT", '\r', buffer, 81, 90, 1, -1);
    if (status == 2) {
        serial_session_flags_00a3fac0 |= 1;
        return true;
    }

    delay = unknown_2c;
    while (delay > 0) {
        delay = SerialPort->Get_Modem_Result(delay, buffer, 81, -1);
    }

    escape[0] = unknown_30;
    escape[1] = unknown_30;
    escape[2] = unknown_30;
    escape[3] = 0;
    SerialPort->Write_To_Serial_Port((unsigned char *)escape, 3);

    delay = unknown_2c;
    while (delay > 0) {
        delay = SerialPort->Get_Modem_Result(delay, buffer, 81, -1);
        if (strncmp(buffer, "OK", 2) == 0) {
            break;
        }
    }

    status = SerialPort->Send_Command_To_Modem("ATH", '\r', buffer, 81, unknown_28, 1, -1);
    if (status == 2) {
    } else {
        serial_session_flags_00a3fac0 |= 1;
        return false;
    }

    status = SerialPort->Send_Command_To_Modem("ATZ", '\r', buffer, 81, 60, 1, -1);
    if (status != 2) {
        serial_session_flags_00a3fac0 |= 1;
        return false;
    }

    serial_session_flags_00a3fac0 |= 1;
    return true;
}
