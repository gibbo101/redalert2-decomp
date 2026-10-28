// void NullModemClass::Translate_Line_Ends() (0x005D1D50)
// Replaces CR by 1 and LF by 2 in the serial manager's receive buffer.
#include "shared/null_modem.hpp"
#include "shared/serial_progress.hpp"
#include "shared/crt_string.hpp"
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28

extern "C" unsigned int __cdecl strlen(char const *string);
#pragma intrinsic(strlen)

void NullModemClass::Translate_Line_Ends()
{
    for (unsigned i = 0; i < strlen(serial_manager_00a40a28.ReceiveBuf); i++) {
        if (serial_manager_00a40a28.ReceiveBuf[i] == '\r') {
            serial_manager_00a40a28.ReceiveBuf[i] = 1;
        } else if (serial_manager_00a40a28.ReceiveBuf[i] == '\n') {
            serial_manager_00a40a28.ReceiveBuf[i] = 2;
        }
    }
}
