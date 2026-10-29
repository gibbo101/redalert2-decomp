// int NullModemClass::Send_Modem_Command(char *command, char terminator, char *buffer, int buflen, int delay, int retries) (0x005D1EA0)
#include "shared/null_modem.hpp"
// @ref ?SerialPort@@3PAVWinModemClass@@A=00b25bb0

int NullModemClass::Send_Modem_Command(char *command, char terminator, char *buffer, int buflen, int delay, int retries)
{
    return SerialPort->Send_Command_To_Modem(command, terminator, buffer, buflen, delay, retries, -1);
}
