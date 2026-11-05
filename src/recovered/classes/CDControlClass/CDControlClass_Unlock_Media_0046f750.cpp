// Unlock all pending removable-media locks; original body 0046F750.
#include "shared/cd_control.hpp"
// @ref __imp__DeviceIoControl@32=0079a1ac
// @ref __imp__GetLastError@0=0079a1f4
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EK@PBAE@DeviceIoControl?5failed?5perfor@=007d2404
// @ref ??_C@_0CH@IDOB@Apparent?5number?5of?5locks?5to?5undo@=007d26cc
bool CDControlClass::Unlock_Media(HANDLE vwin32, char drive)
{
    DIOC_REGISTERS regs = {0};
    PARAMBLOCK param = {0};
    DWORD returned;
    param.Operation = 2;
    regs.reg_EAX = 0x440D;
    regs.reg_EBX = drive;
    regs.reg_ECX = 0x848;
    regs.reg_EDX = (DWORD)&param;
    bool result = DeviceIoControl(vwin32, 1, &regs, sizeof(regs), &regs, sizeof(regs), &returned, 0) != 0;
    if (result) {
        if (regs.reg_Flags & 1) {
            result = regs.reg_EAX == 0xB0 || regs.reg_EAX == 1;
        }
    } else {
        Debug_Printf("DeviceIoControl failed to perform DOS IO control function. Error %d - %s\n", GetLastError(), 0);
    }
    if (!result) return false;
    Debug_Printf("Apparent number of locks to undo = %d\n", param.NumLocks);
    if (!param.NumLocks) param.NumLocks = 1;
    for (int count = 0; count < param.NumLocks; ++count) {
        param.Operation = 1;
        regs.reg_EAX = 0x440D;
        regs.reg_EBX = drive;
        regs.reg_ECX = 0x848;
        regs.reg_EDX = (DWORD)&param;
        result = DeviceIoControl(vwin32, 1, &regs, sizeof(regs), &regs, sizeof(regs), &returned, 0) != 0;
        if (!result) {
            Debug_Printf("DeviceIoControl failed to perform DOS IO control function. Error %d - %s\n", GetLastError(), 0);
        }
        result = result && !(regs.reg_Flags & 1);
        if (!result) break;
    }
    return result;
}
