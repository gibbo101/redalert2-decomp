// void NullModemClass::Setup_Modem_Echo(void (__fastcall *func)(char c)) (0x005D1D20)
#include "shared/null_modem.hpp"
// @ref ?SerialPort@@3PAVWinModemClass@@A=00b25bb0

void NullModemClass::Setup_Modem_Echo(void (__fastcall *func)(char c))
{
    SerialPort->Set_Echo_Function(func);
}
