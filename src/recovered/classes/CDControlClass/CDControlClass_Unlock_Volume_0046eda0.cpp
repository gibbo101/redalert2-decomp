// bool CDControlClass::Unlock_Volume(HANDLE volume) (0x0046EDA0)
// Unlocks the volume (FSCTL), up to 20 attempts 500 ms apart.
#include "shared/cd_control.hpp"
// @ref __imp__DeviceIoControl@32=0079a1ac
// @ref __imp__GetLastError@0=0079a1f4
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref __imp__Sleep@4=0079a1e4
// @ref ??_C@_0DI@JELN@DeviceIoControl?5failed?5to?5unlock@=007d23a4

bool CDControlClass::Unlock_Volume(HANDLE volume)
{
    DWORD returned;
    for (int attempt = 0; attempt < 20; attempt++) {
        if (DeviceIoControl(volume, FSCTL_UNLOCK_VOLUME, 0, 0, 0, 0, &returned, 0)) {
            return true;
        }
        Debug_Printf("DeviceIoControl failed to unlock volume. Error %d - %s\n", GetLastError(), 0);
        Sleep(500);
    }
    return false;
}
