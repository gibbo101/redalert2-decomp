// bool CDControlClass::Dismount_Volume(HANDLE volume) (0x0046EE10)
#include "shared/cd_control.hpp"
// @ref __imp__DeviceIoControl@32=0079a1ac
// @ref __imp__GetLastError@0=0079a1f4
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0DK@IIHK@DeviceIoControl?5failed?5to?5dismou@=007d22b8

bool CDControlClass::Dismount_Volume(HANDLE volume)
{
    DWORD returned;
    bool result = DeviceIoControl(volume, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &returned, 0);
    if (!result) {
        Debug_Printf("DeviceIoControl failed to dismount volume. Error %d - %s\n", GetLastError(), 0);
    }
    return result;
}
