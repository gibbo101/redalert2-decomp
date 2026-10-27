// bool CDControlClass::Unlock_CD_Drive_95(char drive) (0x0046F630)
// Windows 95: under the logical volume lock, unlocks the media of drive
// (0 = A:) so the tray can be opened again.
// Name from its own debug strings.
#include "shared/cd_control.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Lock_Logical_Volume@CDControlClass@@QAG_NPAXDDF@Z=0046fa50
// @ref ?Unlock_Logical_Volume@CDControlClass@@QAG_NPAXD@Z=0046fc80
// @ref ?Unlock_Media@CDControlClass@@QAE_NPAXD@Z=0046f750
// @ref ??_C@_04NCCD@true?$AA@=007d24d8
// @ref ??_C@_05NAGO@false?$AA@=007d24d0
// @ref ??_C@_0BC@HCID@Volume?5locked?5OK?6?$AA@=007d254c
// @ref ??_C@_0BL@ODLI@Unable?5to?5lock?5volume?5?$CFc?3?6?$AA@=007d2478
// @ref ??_C@_0BN@PHBM@CD?5tray?5ejection?5enabled?5OK?6?$AA@=007d2618
// @ref ??_C@_0CB@EEFN@About?5to?5allow?5CD?5tray?5ejection?6@=007d2660
// @ref ??_C@_0CC@OBIH@Allowing?5ejection?5on?5CD?5drive?5?$CFc@=007d2684
// @ref ??_C@_0CE@HDOM@CDControlClass?3?3Unlock_CD_Drive_@=007d26a8
// @ref ??_C@_0CH@FJCD@Could?5not?5unlock?5CD?5tray?5in?5driv@=007d2638
// @ref ??_C@_0DB@OLOL@CDControlClass?3?3Unlock_CD_Drive_@=007d25e4
// @ref ??_C@_0DJ@FFJH@About?5to?5lock?5logical?5volume?5to?5@=007d2560

bool CDControlClass::Unlock_CD_Drive_95(char drive)
{
    Debug_Printf("CDControlClass::Unlock_CD_Drive_95\n");
    bool result = true;
    Debug_Printf("Allowing ejection on CD drive %c\n", drive + 'A');
    drive++;
    HANDLE vwin32 = Open_VWin32();
    Debug_Printf("About to lock logical volume to enable exclusive access\n");
    if (!Lock_Logical_Volume(vwin32, drive, 0, 0)) {
        Debug_Printf("Unable to lock volume %c:\n", drive + 'A' - 1);
        return false;
    }
    Debug_Printf("Volume locked OK\n");
    Debug_Printf("About to allow CD tray ejection\n");
    if (!Unlock_Media(vwin32, drive)) {
        Debug_Printf("Could not unlock CD tray in drive %c:\n", drive + 'A' - 1);
        result = false;
    } else {
        Debug_Printf("CD tray ejection enabled OK\n");
    }
    Unlock_Logical_Volume(vwin32, drive);
    Close_VWin32(vwin32);
    Debug_Printf("CDControlClass::Unlock_CD_Drive_95 returning %s\n", result ? "true" : "false");
    return result;
}
