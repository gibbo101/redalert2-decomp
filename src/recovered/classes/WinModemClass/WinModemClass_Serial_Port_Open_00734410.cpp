// HANDLE WinModemClass::Serial_Port_Open(char const *port_name, int baud, int parity, int wordlen, int stopbits) (0x00734410)
// Opens \\.\port_name for overlapped I/O with 8 KB queues and RTS/CTS flow
// control, records the settings and raises DTR; INVALID_HANDLE_VALUE on
// failure.
#include "shared/win_modem.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
// @ref ?Process_Errors@WinModemClass@@QAEXKUCOMSTAT@@@Z=007354d0
// @ref ??_C@_04CHPO@?2?2?4?2?$AA@=007fcb10
// @ref ??_C@_0BA@NAJH@Port?5opened?5OK?6?$AA@=007fcabc
// @ref ??_C@_0BF@GLCD@Closing?5serial?5port?6?$AA@=007fca0c
// @ref ??_C@_0BI@OLEM@Opening?5serial?5port?5?$CFs?6?$AA@=007fcaf8
// @ref ??_C@_0CB@JCGN@SetCommState?5returned?5error?5?$CFs?4?6@=007fca98
// @ref ??_C@_0CG@EMOK@GetCommState?5returned?5error?5code@=007fca70
// @ref ??_C@_0CJ@IGCF@SetCommTimeouts?5returned?5error?5c@=007fca44
// @ref ??_C@_0CM@KPPI@Failed?5to?5get?5valid?5port?5handle?4@=007fcacc

HANDLE WinModemClass::Serial_Port_Open(char const *port_name, int baud, int parity, int wordlen, int stopbits)
{
    char device_name[266] = "\\\\.\\";
    strcat(device_name, port_name);
    if (PortHandle != INVALID_HANDLE_VALUE) {
        Debug_Printf("Closing serial port\n");
        CloseHandle(PortHandle);
        PortHandle = INVALID_HANDLE_VALUE;
    }
    Debug_Printf("Opening serial port %s\n", device_name);
    HANDLE com_handle = CreateFileA(device_name, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING,
                                    FILE_FLAG_OVERLAPPED, 0);
    if (com_handle == INVALID_HANDLE_VALUE) {
        Debug_Printf("Failed to get valid port handle. Error: %s\n", 0);
        return INVALID_HANDLE_VALUE;
    }
    Debug_Printf("Port opened OK\n");
    PortHandle = com_handle;
    SetupComm(com_handle, SIZE_OF_WINDOWS_SERIAL_BUFFER, SIZE_OF_WINDOWS_SERIAL_BUFFER);
    PurgeComm(PortHandle, 0x0F);
    ReadOverlap.Internal = 0;
    ReadOverlap.InternalHigh = 0;
    ReadOverlap.Offset = 0;
    ReadOverlap.OffsetHigh = 0;
    ReadOverlap.hEvent = CreateEventA(0, true, true, 0);
    WriteOverlap.Internal = 0;
    WriteOverlap.InternalHigh = 0;
    WriteOverlap.Offset = 0;
    WriteOverlap.OffsetHigh = 0;
    WriteOverlap.hEvent = CreateEventA(0, true, true, 0);
    DCB dcb;
    if (GetCommState(com_handle, &dcb)) {
        dcb.BaudRate = baud;
        dcb.Parity = parity;
        dcb.ByteSize = wordlen;
        dcb.StopBits = stopbits - 1;
        dcb.fBinary = 1;
        dcb.fParity = 0;
        dcb.fOutxCtsFlow = 1;
        dcb.fOutxDsrFlow = 0;
        dcb.fDtrControl = 1;
        dcb.fOutX = 0;
        dcb.fInX = 0;
        dcb.fErrorChar = 0;
        dcb.fRtsControl = 2;
        dcb.fAbortOnError = 0;
        if (!SetCommState(com_handle, &dcb)) {
            Debug_Printf("SetCommState returned error %s.\n", 0);
        } else {
            SerialSettings = dcb;
        }
    } else {
        Debug_Printf("GetCommState returned error code %s.\n", 0);
    }
    COMMTIMEOUTS timeouts;
    timeouts.ReadIntervalTimeout = 1000;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    timeouts.ReadTotalTimeoutConstant = 3000;
    timeouts.WriteTotalTimeoutMultiplier = 500;
    timeouts.WriteTotalTimeoutConstant = 1000;
    if (!SetCommTimeouts(com_handle, &timeouts)) {
        Debug_Printf("SetCommTimeouts returned error code %s.\n", 0);
    }
    Set_Serial_DTR(true);
    DWORD errors;
    COMSTAT status;
    if (ClearCommError(PortHandle, &errors, &status)) {
        InQueue = status.cbInQue;
        OutQueue = status.cbOutQue;
        if (errors) {
            Process_Errors(errors, status);
        }
    }
    return com_handle;
}
