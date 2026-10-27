// bool CDControlClass::Auto_Eject_Volume(HANDLE volume) (0x0046EEB0)
// Ejects the media (IOCTL_STORAGE_EJECT_MEDIA).
#include "shared/cd_control.hpp"
// @ref __imp__DeviceIoControl@32=0079a1ac
// @ref __imp__GetLastError@0=0079a1f4
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0DG@EMCF@DeviceIoControl?5failed?5to?5eject?5@=007d2240

bool CDControlClass::Auto_Eject_Volume(HANDLE volume)
{
    DWORD returned;
    bool result = DeviceIoControl(volume, IOCTL_STORAGE_EJECT_MEDIA, 0, 0, 0, 0, &returned, 0);
    if (!result) {
        Debug_Printf("DeviceIoControl failed to eject media. Error %d - %s\n", GetLastError(), 0);
    }
    return result;
}
