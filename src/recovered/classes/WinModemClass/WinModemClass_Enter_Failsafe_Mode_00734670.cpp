// bool WinModemClass::Enter_Failsafe_Mode() (0x00734670)
// Drops pending I/O and sets the port to 9600 baud, 8 data bits, no parity,
// one stop bit, no flow control; false when the settings are refused.
#include "shared/win_modem.hpp"
#include "shared/debug_printf.hpp"
// @ref ??_C@_0CB@BEPN@GetCommState?5returned?5error?5?$CFs?4?6@=007fcb78
// @ref ??_C@_0CB@JCGN@SetCommState?5returned?5error?5?$CFs?4?6@=007fca98
// @ref ??_C@_0CI@HKEN@WinModemClass?5?9?5Entering?5failsaf@=007fcb9c
// @ref ??_C@_0FN@CMFD@Enter_Failsafe_Mode?5?9?5EscapeComm@=007fcb18
// @ref ?Process_Errors@WinModemClass@@QAEXKUCOMSTAT@@@Z=007354d0

bool WinModemClass::Enter_Failsafe_Mode()
{
    DCB dcb;
    DWORD mask;
    DWORD errors;
    COMSTAT status;
    Debug_Printf("WinModemClass - Entering failsafe mode\n");
    PurgeComm(PortHandle, 0x0F);
    ResetEvent(ReadOverlap.hEvent);
    ResetEvent(WriteOverlap.hEvent);
    WaitingForSerialCharRead = false;
    WaitingForSerialCharWrite = false;
    if (GetCommState(PortHandle, &dcb)) {
        dcb.BaudRate = 9600;
        dcb.Parity = 0;
        dcb.ByteSize = 8;
        dcb.StopBits = 0;
        dcb.fBinary = 1;
        dcb.fParity = 0;
        dcb.fOutxCtsFlow = 0;
        dcb.fOutxDsrFlow = 0;
        dcb.fDtrControl = 1;
        dcb.fOutX = 0;
        dcb.fInX = 0;
        dcb.fErrorChar = 0;
        dcb.fRtsControl = 1;
        dcb.fAbortOnError = 0;
        if (!SetCommState(PortHandle, &dcb)) {
            Debug_Printf("SetCommState returned error %s.\n", 0);
            return false;
        }
    } else {
        Debug_Printf("GetCommState returned error %s.\n", 0);
    }
    GetCommMask(PortHandle, &mask);
    Set_Serial_DTR(true);
    Get_Modem_Status();
    if (!EscapeCommFunction(PortHandle, 3)) {
        Debug_Printf("Enter_Failsafe_Mode - EscapeCommFunction failed to set state of RTS line. Error code %d, %s\n",
                     GetLastError(), 0);
    }
    if (ClearCommError(PortHandle, &errors, &status)) {
        InQueue = status.cbInQue;
        OutQueue = status.cbOutQue;
        if (errors) {
            Process_Errors(errors, status);
        }
    }
    return true;
}
