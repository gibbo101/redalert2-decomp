// void NullModemClass::Setup_Abort_Modem() (0x005D1E00)
#include "shared/null_modem.hpp"
// @ref ?SerialPort@@3PAVWinModemClass@@A=00b25bb0
// @ref ?unknown_modem_aborted_a72ec4@@3_NA=00a72ec4
// @ref ?Abort_Modem@NullModemClass@@SAHXZ=005d1db0

void NullModemClass::Setup_Abort_Modem()
{
    SerialPort->Set_Abort_Function(Abort_Modem);
    unknown_modem_aborted_a72ec4 = false;
}
