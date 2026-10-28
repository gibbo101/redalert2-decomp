// void WinModemClass::Leave_Failsafe_Mode() (0x007347C0)
// Drops pending I/O and restores the settings Serial_Port_Open made.
#include "shared/win_modem.hpp"
#include "shared/debug_printf.hpp"
// @ref ??_C@_0CB@JCGN@SetCommState?5returned?5error?5?$CFs?4?6@=007fca98
// @ref ??_C@_0CH@LKKO@WinModemClass?5?9?5Leaving?5failsafe@=007fcc24
// @ref ??_C@_0FN@EINH@Leave_Failsafe_Mode?5?9?5EscapeComm@=007fcbc4
// @ref ?Process_Errors@WinModemClass@@QAEXKUCOMSTAT@@@Z=007354d0

void WinModemClass::Leave_Failsafe_Mode()
{
    DWORD errors;
    COMSTAT status;
    Debug_Printf("WinModemClass - Leaving failsafe mode\n");
    PurgeComm(PortHandle, 0x0F);
    ResetEvent(ReadOverlap.hEvent);
    ResetEvent(WriteOverlap.hEvent);
    WaitingForSerialCharRead = false;
    WaitingForSerialCharWrite = false;
    if (!SetCommState(PortHandle, &SerialSettings)) {
        Debug_Printf("SetCommState returned error %s.\n", 0);
    }
    if (!EscapeCommFunction(PortHandle, 3)) {
        Debug_Printf("Leave_Failsafe_Mode - EscapeCommFunction failed to set state of RTS line. Error code %d, %s\n",
                     GetLastError(), 0);
    }
    if (ClearCommError(PortHandle, &errors, &status)) {
        InQueue = status.cbInQue;
        OutQueue = status.cbOutQue;
        if (errors) {
            Process_Errors(errors, status);
        }
    }
    Set_Serial_DTR(true);
}
