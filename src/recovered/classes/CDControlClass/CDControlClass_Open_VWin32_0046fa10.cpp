// HANDLE WINAPI CDControlClass::Open_VWin32() (0x0046FA10)
// Opens the VWIN32 device driver that carries DOS IOCTL calls on Windows 95.
// Assumes: WINAPI member (this on the stack, ret 4), as in Microsoft's
// VWIN32 sample OpenVWin32.
#include "shared/cd_control.hpp"
// @ref __imp__CreateFileA@28=0079a1b0
// @ref ??_C@_0L@GCFB@?2?2?4?2vwin32?$AA@=007d2494

HANDLE WINAPI CDControlClass::Open_VWin32()
{
    return CreateFileA("\\\\.\\vwin32", 0, 0, 0, 0, FILE_FLAG_DELETE_ON_CLOSE, 0);
}
