// bool WINAPI CDControlClass::Close_VWin32(HANDLE vwin32) (0x0046FA30)
// Closes the VWIN32 device handle. The inventory splits this function at
// 0x0046FA35 (the CloseHandle call); it is one 19-byte body.
// Assumes: WINAPI member (this on the stack, ret 8).
#include "shared/cd_control.hpp"
// @ref __imp__CloseHandle@4=0079a1d4

bool WINAPI CDControlClass::Close_VWin32(HANDLE vwin32)
{
    return CloseHandle(vwin32) ? true : false;
}
