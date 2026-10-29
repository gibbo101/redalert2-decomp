// int NullModemClass::Get_Modem_Status() (0x005D1E50)
// The port's modem status, without carrier detect (0x80) when the modem
// answers "AT" (it is in command mode).
#include "shared/null_modem.hpp"
// @ref ?SerialPort@@3PAVWinModemClass@@A=00b25bb0
// @ref ??_C@_02BKOD@AT?$AA@=007e7ca8

int NullModemClass::Get_Modem_Status()
{
    int modemstatus;
    int status;
    char buffer[81];

    modemstatus = SerialPort->Get_Modem_Status();
    status = SerialPort->Send_Command_To_Modem("AT", '\r', buffer, 81, 90, 1, -1);
    if (status == 2) {
        modemstatus &= ~0x80;
    }
    return modemstatus;
}
