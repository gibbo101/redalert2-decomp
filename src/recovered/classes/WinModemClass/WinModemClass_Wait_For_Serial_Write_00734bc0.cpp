// void WinModemClass::Wait_For_Serial_Write() (0x00734BC0)
// Waits up to 300 ticks for the pending overlapped write to finish. Out of line at
// all six call sites in the unit (Write_To_Serial_Port and its expansions).
#include "shared/win_modem.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430

#pragma auto_inline(off)
void WinModemClass::Wait_For_Serial_Write()
{
    DWORD bytes_written;
    CDTimerClass<SystemTimerClass> timer;
    if (WaitingForSerialCharWrite) {
        timer = 300;
        while (!GetOverlappedResult(PortHandle, &WriteOverlap, &bytes_written, false)
               && GetLastError() == ERROR_IO_INCOMPLETE && timer) {
        }
        WaitingForSerialCharWrite = false;
    }
    ResetEvent(WriteOverlap.hEvent);
}
#pragma auto_inline(on)
