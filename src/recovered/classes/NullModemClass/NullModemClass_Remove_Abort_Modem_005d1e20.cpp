// void NullModemClass::Remove_Abort_Modem() (0x005D1E20)
#include "shared/null_modem.hpp"
// @ref ?SerialPort@@3PAVWinModemClass@@A=00b25bb0
// @ref ?unknown_modem_aborted_a72ec4@@3_NA=00a72ec4

void NullModemClass::Remove_Abort_Modem()
{
    SerialPort->Set_Abort_Function(0);
    unknown_modem_aborted_a72ec4 = false;
}
