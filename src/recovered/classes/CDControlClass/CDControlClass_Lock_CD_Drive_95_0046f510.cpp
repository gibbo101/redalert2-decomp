// bool CDControlClass::Lock_CD_Drive_95(char drive) (0x0046F510)
// Windows 95: under the logical volume lock, locks the media of drive
// (0 = A:) so the tray cannot be opened.
// Name from its own debug strings.
#include "shared/cd_control.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Lock_Logical_Volume@CDControlClass@@QAG_NPAXDDF@Z=0046fa50
// @ref ?Unlock_Logical_Volume@CDControlClass@@QAG_NPAXD@Z=0046fc80
// @ref ?Lock_Media@CDControlClass@@QAE_NPAXD@Z=0046f8c0
// @ref ??_C@_04NCCD@true?$AA@=007d24d8
// @ref ??_C@_05NAGO@false?$AA@=007d24d0
// @ref ??_C@_0BC@HCID@Volume?5locked?5OK?6?$AA@=007d254c
// @ref ??_C@_0BL@ODLI@Unable?5to?5lock?5volume?5?$CFc?3?6?$AA@=007d2478
// @ref ??_C@_0BO@GFCK@CD?5tray?5ejection?5disabled?5OK?6?$AA@=007d24e0
// @ref ??_C@_0CC@JIOF@CDControlClass?3?3Lock_CD_Drive_95@=007d25c0
// @ref ??_C@_0CD@FBEC@About?5to?5prevent?5CD?5tray?5ejectio@=007d2528
// @ref ??_C@_0CE@MJIJ@Preventing?5ejection?5on?5CD?5drive?5@=007d259c
// @ref ??_C@_0CF@PPJC@Could?5not?5lock?5CD?5tray?5in?5drive?5@=007d2500
// @ref ??_C@_0CP@FBAI@CDControlClass?3?3Lock_CD_Drive_95@=007d24a0
// @ref ??_C@_0DJ@FFJH@About?5to?5lock?5logical?5volume?5to?5@=007d2560

bool CDControlClass::Lock_CD_Drive_95(char drive)
{
    Debug_Printf("CDControlClass::Lock_CD_Drive_95\n");
    bool result = true;
    Debug_Printf("Preventing ejection on CD drive %c\n", drive + 'A');
    drive++;
    HANDLE vwin32 = Open_VWin32();
    Debug_Printf("About to lock logical volume to enable exclusive access\n");
    if (!Lock_Logical_Volume(vwin32, drive, 0, 0)) {
        Debug_Printf("Unable to lock volume %c:\n", drive + 'A' - 1);
        return false;
    }
    Debug_Printf("Volume locked OK\n");
    Debug_Printf("About to prevent CD tray ejection\n");
    if (!Lock_Media(vwin32, drive)) {
        Debug_Printf("Could not lock CD tray in drive %c:\n", drive + 'A' - 1);
        result = false;
    } else {
        Debug_Printf("CD tray ejection disabled OK\n");
    }
    Unlock_Logical_Volume(vwin32, drive);
    Close_VWin32(vwin32);
    Debug_Printf("CDControlClass::Lock_CD_Drive_95 returning %s\n", result ? "true" : "false");
    return result;
}
