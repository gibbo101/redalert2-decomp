// bool CDControlClass::Lock_Media(HANDLE vwin32, char drive) (0x0046F8C0)
// Windows 95: clears pending locks, then locks the removable media in drive
// (1 = A:) so the tray cannot be opened.
// Assumes: name from Microsoft's VWIN32 sample vocabulary.
#include "shared/cd_control.hpp"
// @ref __imp__DeviceIoControl@32=0079a1ac
// @ref __imp__GetLastError@0=0079a1f4
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EK@PBAE@DeviceIoControl?5failed?5to?5perfor@=007d2404
// @ref ?Unlock_Media@CDControlClass@@QAE_NPAXD@Z=0046f750

// Not expanded into its callers in the original (they call it); VC6 would
// expand it here without the pragma.
#pragma auto_inline(off)
bool CDControlClass::Lock_Media(HANDLE vwin32, char drive)
{
    DIOC_REGISTERS regs = {0};
    PARAMBLOCK param = {0};
    DWORD returned;

    Unlock_Media(vwin32, drive);
    param.Operation = 0;
    regs.reg_EAX = 0x440D;
    regs.reg_EBX = drive;
    regs.reg_ECX = 0x0848;
    regs.reg_EDX = (DWORD)&param;
    bool result = DeviceIoControl(vwin32, VWIN32_DIOC_DOS_IOCTL, &regs, sizeof(regs), &regs, sizeof(regs),
                                  &returned, 0);
    if (!result) {
        Debug_Printf("DeviceIoControl failed to perform DOS IO control function. Error %d - %s\n",
                     GetLastError(), 0);
    }
    result = result && !(regs.reg_Flags & CARRY_FLAG);
    return result;
}
#pragma auto_inline(on)
