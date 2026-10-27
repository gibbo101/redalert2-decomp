// bool CDControlClass::Lock_Volume(HANDLE volume) (0x0046ED30)
// Locks the volume (FSCTL), up to 20 attempts 500 ms apart.
#include "shared/cd_control.hpp"
// @ref __imp__DeviceIoControl@32=0079a1ac
// @ref __imp__GetLastError@0=0079a1f4
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref __imp__Sleep@4=0079a1e4
// @ref ??_C@_0DG@DBKA@DeviceIoControl?5failed?5to?5lock?5v@=007d22f4

bool CDControlClass::Lock_Volume(HANDLE volume)
{
    DWORD returned;
    for (int attempt = 0; attempt < 20; attempt++) {
        if (DeviceIoControl(volume, FSCTL_LOCK_VOLUME, 0, 0, 0, 0, &returned, 0)) {
            return true;
        }
        Debug_Printf("DeviceIoControl failed to lock volume. Error %d - %s\n", GetLastError(), 0);
        Sleep(500);
    }
    return false;
}
