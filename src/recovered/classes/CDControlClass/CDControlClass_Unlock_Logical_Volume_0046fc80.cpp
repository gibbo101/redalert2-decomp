// bool WINAPI CDControlClass::Unlock_Logical_Volume(HANDLE vwin32, char drive) (0x0046FC80)
// Windows 95: releases a logical volume lock (IOCTL 440Dh minor 6Ah) on
// drive (1 = A:), trying the FAT32 device category 48h before 08h.
// Assumes: WINAPI member; names from Microsoft's VWIN32 sample.
#include "shared/cd_control.hpp"
// @ref __imp__DeviceIoControl@32=0079a1ac
// @ref __imp__GetLastError@0=0079a1f4
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EK@PBAE@DeviceIoControl?5failed?5to?5perfor@=007d2404

#define MAKEWORD(low, high) ((WORD)(((BYTE)(low)) | ((WORD)((BYTE)(high))) << 8))

// Not expanded into its callers in the original (they call it); VC6 would
// expand it here without the pragma.
#pragma auto_inline(off)
bool WINAPI CDControlClass::Unlock_Logical_Volume(HANDLE vwin32, char drive)
{
    DIOC_REGISTERS regs = {0};
    DWORD returned;
    BYTE category = 0;
    bool result;

    do {
        category = category ? 0x08 : 0x48;
        regs.reg_EAX = 0x440D;
        regs.reg_EBX = drive;
        regs.reg_ECX = MAKEWORD(0x6A, category);
        result = DeviceIoControl(vwin32, VWIN32_DIOC_DOS_IOCTL, &regs, sizeof(regs), &regs, sizeof(regs),
                                 &returned, 0);
        if (!result) {
            Debug_Printf("DeviceIoControl failed to perform DOS IO control function. Error %d - %s\n",
                         GetLastError(), 0);
        }
        result = result && !(regs.reg_Flags & CARRY_FLAG);
    } while (!result && category != 0x08);
    return result;
}
#pragma auto_inline(on)
