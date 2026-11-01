// void WinModemClass::Set_Serial_DTR(bool state) (0x00734900; slot 4)
// Raises (SETDTR) or drops (CLRDTR) the port's DTR line; reports a failure.
#include "shared/win_modem.hpp"
#include "shared/debug_printf.hpp"
// @ref ??_C@_0ED@NLL@Set_Serial_DTR?5?9?5EscapeCommFunct@=007fcc4c

void WinModemClass::Set_Serial_DTR(bool state)
{
    if (state) {
        if (EscapeCommFunction(PortHandle, 5)) {   // SETDTR
            return;
        }
    } else {
        if (EscapeCommFunction(PortHandle, 6)) {   // CLRDTR
            return;
        }
    }
    Debug_Printf("Set_Serial_DTR - EscapeCommFunction failed with error code %d, %s\n", GetLastError(), 0);
}
