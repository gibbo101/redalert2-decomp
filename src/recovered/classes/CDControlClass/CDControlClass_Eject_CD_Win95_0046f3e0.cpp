// void CDControlClass::Eject_CD_Win95(char drive) (0x0046F3E0)
// Windows 95: takes the logical volume lock, removes the media locks and
// ejects the media of drive (0 = A:) through VWIN32.
// The early failure paths leave the VWIN32 handle open, as in the original.
#include "shared/cd_control.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Lock_Logical_Volume@CDControlClass@@QAG_NPAXDDF@Z=0046fa50
// @ref ?Unlock_Logical_Volume@CDControlClass@@QAG_NPAXD@Z=0046fc80
// @ref ?Unlock_Media@CDControlClass@@QAE_NPAXD@Z=0046f750
// @ref ??_C@_0BL@ODLI@Unable?5to?5lock?5volume?5?$CFc?3?6?$AA@=007d2478
// @ref ??_C@_0CG@DPDE@Could?5not?5eject?5media?5from?5drive@=007d23dc
// @ref ??_C@_0CH@DMNE@Could?5not?5unlock?5media?5from?5driv@=007d2450

void CDControlClass::Eject_CD_Win95(char drive)
{
    drive++;
    HANDLE vwin32 = Open_VWin32();
    if (!Lock_Logical_Volume(vwin32, drive, 0, 0)) {
        Debug_Printf("Unable to lock volume %c:\n", drive + 'A' - 1);
        return;
    }
    if (!Unlock_Media(vwin32, drive)) {
        Debug_Printf("Could not unlock media from drive %c:\n", drive + 'A' - 1);
        Unlock_Logical_Volume(vwin32, drive);
        return;
    }
    if (!Eject_Media(vwin32, drive)) {
        Debug_Printf("Could not eject media from drive %c:\n", drive + 'A' - 1);
    }
    Unlock_Logical_Volume(vwin32, drive);
    Close_VWin32(vwin32);
}
