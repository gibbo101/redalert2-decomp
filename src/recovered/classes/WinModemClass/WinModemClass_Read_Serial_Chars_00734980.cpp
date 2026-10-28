// bool WinModemClass::Read_Serial_Chars() (0x00734980)
// Collects a finished overlapped read, then reads what the port holds (at
// most the buffer, at least one byte) into the circular buffer until a read
// stays pending. True when anything was stored.
#include "shared/win_modem.hpp"
#include "shared/debug_printf.hpp"
// @ref ??_C@_0EL@LGAL@GetOverlappedResult?5in?5WinModemC@=007fccc0
// @ref ??_C@_0CP@PNAC@Reading?5from?5port?5handle?5failed?5@=007fcc90
// @ref ?Process_Errors@WinModemClass@@QAEXKUCOMSTAT@@@Z=007354d0

bool WinModemClass::Read_Serial_Chars()
{
    DWORD bytes_read;
    int total = 0;
    if (WaitingForSerialCharRead) {
        bytes_read = 0;
        if (GetOverlappedResult(PortHandle, &ReadOverlap, &bytes_read, false)) {
            WaitingForSerialCharRead = false;
            if (bytes_read) {
                for (unsigned index = 0; index < bytes_read; index++) {
                    SerialBuffer[SerialBufferWritePtr] = TempSerialBuffer[index];
                    SerialBufferWritePtr = (SerialBufferWritePtr + 1) & (SIZE_OF_WINDOWS_SERIAL_BUFFER - 1);
                }
                total = bytes_read;
            }
        } else {
            if (GetLastError() == ERROR_IO_INCOMPLETE) {
                return false;
            }
            Debug_Printf("GetOverlappedResult in WinModemClass::Read_Serial_Chars returned error %s\n", 0);
        }
    }
    ResetEvent(ReadOverlap.hEvent);
    DWORD errors;
    COMSTAT status;
    int bytes_to_read = 1;
    if (ClearCommError(PortHandle, &errors, &status)) {
        InQueue = status.cbInQue;
        OutQueue = status.cbOutQue;
        if (errors) {
            Process_Errors(errors, status);
        }
        bytes_to_read = status.cbInQue;
        if (bytes_to_read >= SIZE_OF_WINDOWS_SERIAL_BUFFER) {
            bytes_to_read = SIZE_OF_WINDOWS_SERIAL_BUFFER;
        } else if (bytes_to_read == 0) {
            bytes_to_read = 1;
        }
    }
    bool read_result;
    while (true) {
        bytes_read = 0;
        read_result = ReadFile(PortHandle, TempSerialBuffer, bytes_to_read, &bytes_read, &ReadOverlap) != 0;
        if (!read_result) {
            if (GetLastError() == ERROR_IO_PENDING) {
                WaitingForSerialCharRead = true;
                return total != 0;
            }
            Debug_Printf("Reading from port handle failed with error %s\n", 0);
            break;
        }
        if (bytes_read) {
            for (unsigned index = 0; index < bytes_read; index++) {
                SerialBuffer[SerialBufferWritePtr] = TempSerialBuffer[index];
                SerialBufferWritePtr = (SerialBufferWritePtr + 1) & (SIZE_OF_WINDOWS_SERIAL_BUFFER - 1);
            }
            total += bytes_read;
        }
        bytes_to_read = 1;
        if (read_result != true) {
            break;
        }
    }
    return total != 0;
}
