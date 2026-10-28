// GetCDClass::GetCDClass() (0x004D2940)
// Lists the CD-ROM drives: C: to Z: first; when there is none, A: and B:.
#include "shared/get_cd.hpp"
#include "shared/debug_printf.hpp"
#include "shared/cd_control.hpp"
#include "shared/crt_string.hpp"
// @ref __imp__GetDriveTypeA@4=0079a24c
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_03EAMH@a?3?2?$AA@=007d8834
// @ref ??_C@_0BI@BEOA@GetCDClass?5constructor?6?$AA@=007d881c
// @ref ??_C@_0BG@LLIE@CD?5drive?5found?5?9?5?$CFc?3?6?$AA@=007d8804
// @ref ??_C@_0BE@PMAC@No?5CD?5drives?5found?6?$AA@=007d87f0

GetCDClass::GetCDClass()
{
    char root[4] = "a:\\";
    Count = 0;
    Cursor = 0;
    Debug_Printf("GetCDClass constructor\n");
    memset(Drives, 0xFF, 26);
    int upper = 'C';
    for (char letter = 'c'; letter <= 'z'; letter++, upper++) {
        root[0] = letter;
        if (GetDriveTypeA(root) == DRIVE_CDROM) {
            Drives[Count++] = upper - 'A';
            Debug_Printf("CD drive found - %c:\n", upper);
        }
    }
    if (Count == 0) {
        char letter = 'a';
        int index = 0;
        for (; letter <= 'b'; letter++, index++) {
            root[0] = letter;
            if (GetDriveTypeA(root) == DRIVE_CDROM) {
                Drives[Count++] = index;
            }
        }
        if (Count == 0) {
            Debug_Printf("No CD drives found\n");
        }
    }
}
