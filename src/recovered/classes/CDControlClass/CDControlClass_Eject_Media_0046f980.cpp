// bool CDControlClass::Eject_Media(HANDLE vwin32, char drive) (0x0046F980)
// Windows 95: ejects the removable media in drive (1 = A:), IOCTL 440Dh/0849h.
// Assumes: name from Microsoft's VWIN32 sample vocabulary.
#include "shared/cd_control.hpp"
// @ref __imp__DeviceIoControl@32=0079a1ac
// @ref __imp__GetLastError@0=0079a1f4
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EK@PBAE@DeviceIoControl?5failed?5to?5perfor@=007d2404

bool CDControlClass::Eject_Media(HANDLE vwin32, char drive)
{
    DIOC_REGISTERS regs = {0};
    DWORD returned;

    regs.reg_EAX = 0x440D;
    regs.reg_EBX = drive;
    regs.reg_ECX = 0x0849;
    bool result = DeviceIoControl(vwin32, VWIN32_DIOC_DOS_IOCTL, &regs, sizeof(regs), &regs, sizeof(regs),
                                  &returned, 0);
    if (!result) {
        Debug_Printf("DeviceIoControl failed to perform DOS IO control function. Error %d - %s\n",
                     GetLastError(), 0);
    }
    result = result && !(regs.reg_Flags & CARRY_FLAG);
    return result;
}
