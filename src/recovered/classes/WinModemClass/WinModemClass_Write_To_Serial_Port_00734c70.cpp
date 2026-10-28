// void WinModemClass::Write_To_Serial_Port(unsigned char *buffer, int length) (0x00734C70)
// Starts an overlapped write after the previous one finished.
#include "shared/win_modem.hpp"
#include "shared/debug_printf.hpp"
// @ref ?Wait_For_Serial_Write@WinModemClass@@QAEXXZ=00734bc0
// @ref ??_C@_0CN@JKPG@Writing?5to?5port?5handle?5failed?5wi@=007fcd0c

void WinModemClass::Write_To_Serial_Port(unsigned char *buffer, int length)
{
    DWORD bytes_written;
    Wait_For_Serial_Write();
    if (!WriteFile(PortHandle, buffer, length, &bytes_written, &WriteOverlap)) {
        if (GetLastError() == ERROR_IO_PENDING) {
            WaitingForSerialCharWrite = true;
            return;
        }
        Debug_Printf("Writing to port handle failed with error %s\n", 0);
    }
}
