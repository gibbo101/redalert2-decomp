// bool CDControlClass::Prevent_Removal_Of_Volume(HANDLE volume, bool prevent) (0x0046EE60)
// Allows or prevents ejecting the media (IOCTL_STORAGE_MEDIA_REMOVAL).
#include "shared/cd_control.hpp"
// @ref __imp__DeviceIoControl@32=0079a1ac
// @ref __imp__GetLastError@0=0079a1f4
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@DMGK@DeviceIoControl?5failed?5to?5preven@=007d2278

bool CDControlClass::Prevent_Removal_Of_Volume(HANDLE volume, bool prevent)
{
    DWORD returned;
    PREVENT_MEDIA_REMOVAL removal;
    removal.PreventMediaRemoval = prevent;
    bool result = DeviceIoControl(volume, IOCTL_STORAGE_MEDIA_REMOVAL, &removal, sizeof(removal), 0, 0,
                                  &returned, 0);
    if (!result) {
        Debug_Printf("DeviceIoControl failed to prevent media removal. Error %d - %s\n", GetLastError(), 0);
    }
    return result;
}
