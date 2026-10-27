// bool WINAPI CDControlClass::Lock_Logical_Volume(HANDLE vwin32, char drive, char lock_level, short permissions) (0x0046FA50)
// Windows 95: takes a logical volume lock (IOCTL 440Dh minor 4Ah) on drive
// (1 = A:), trying the FAT32 device category 48h before 08h; after both fail
// it logs the DOS error, waits a second and retries, five rounds in all.
// Assumes: WINAPI member; names from Microsoft's VWIN32 sample.
#include "shared/cd_control.hpp"
// @ref __imp__DeviceIoControl@32=0079a1ac
// @ref __imp__GetLastError@0=0079a1f4
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EK@PBAE@DeviceIoControl?5failed?5to?5perfor@=007d2404
// @ref ??_C@_0BK@OOHG@LOCK?5return?5eax?5error?5?$CFd?6?$AA@=007d26f4
// @ref ??_C@_0CN@JINE@LOCK?5return?5eax?5error?5?8Lock?5coun@=007d2710
// @ref ??_C@_0CO@JKHI@LOCK?5return?5eax?5error?5?8Volume?5no@=007d2740
// @ref ??_C@_0DA@CJFK@LOCK?5return?5eax?5error?5?8Function?5@=007d27a4
// @ref ??_C@_0DE@DPHM@LOCK?5return?5eax?5error?5?8Volume?5no@=007d2770
// @ref __imp__Sleep@4=0079a1e4

#define MAKEWORD(low, high) ((WORD)(((BYTE)(low)) | ((WORD)((BYTE)(high))) << 8))

bool WINAPI CDControlClass::Lock_Logical_Volume(HANDLE vwin32, char drive, char lock_level, short permissions)
{
    DIOC_REGISTERS regs = {0};
    DWORD returned;
    int retries = 5;
    bool result;

    do {
        BYTE category = 0;
        do {
            category = category ? 0x08 : 0x48;
            regs.reg_EAX = 0x440D;
            regs.reg_EBX = MAKEWORD(drive, lock_level);
            regs.reg_ECX = MAKEWORD(0x4A, category);
            regs.reg_EDX = permissions;
            result = DeviceIoControl(vwin32, VWIN32_DIOC_DOS_IOCTL, &regs, sizeof(regs), &regs,
                                          sizeof(regs), &returned, 0);
            if (!result) {
                Debug_Printf("DeviceIoControl failed to perform DOS IO control function. Error %d - %s\n",
                             GetLastError(), 0);
            }
            result = result && !(regs.reg_Flags & CARRY_FLAG);
            if (result) {
                return true;
            }
        } while (category != 0x08);

        retries--;
        switch (regs.reg_EAX) {
        case 0x01:
            Debug_Printf("LOCK return eax error 'Function not supported'\n");
            break;
        case 0xB0:
            Debug_Printf("LOCK return eax error 'Volume not locked in drive'\n");
            break;
        case 0xB2:
            Debug_Printf("LOCK return eax error 'Volume not removable'\n");
            break;
        case 0xB4:
            Debug_Printf("LOCK return eax error 'Lock count exceeded'\n");
            break;
        default:
            Debug_Printf("LOCK return eax error %d\n", regs.reg_EAX);
            break;
        }
        Sleep(1000);
    } while (retries > 0);
    return false;
}
