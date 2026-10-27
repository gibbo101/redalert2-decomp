// HANDLE CDControlClass::Open_Removable_Volume(char drive) (0x0046EC60)
// Opens "\\.\X:" for a removable or CD-ROM drive (0 = A:), read/write for
// removable media and read-only for CD-ROMs; INVALID_HANDLE_VALUE otherwise.
#include "shared/cd_control.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref __imp__GetDriveTypeA@4=0079a24c
// @ref __imp__CreateFileA@28=0079a1b0
// @ref ??_C@_04POLC@?$CFc?3?2?$AA@=007d239c
// @ref ??_C@_07NGPH@?2?2?4?2?$CFc?3?$AA@=007d2354
// @ref ??_C@_0CH@MJPG@Unable?5to?5open?5drive?5?$CFc?3?5for?5eje@=007d232c
// @ref ??_C@_0DO@BGPA@Attempt?5to?5open?5non?9removable?5vo@=007d235c

HANDLE CDControlClass::Open_Removable_Volume(char drive)
{
    char root[5];
    char volume_name[8];
    DWORD access;

    sprintf(root, "%c:\\", drive + 'A');
    switch (GetDriveTypeA(root)) {
    case DRIVE_REMOVABLE:
        access = GENERIC_READ | GENERIC_WRITE;
        break;
    case DRIVE_CDROM:
        access = GENERIC_READ;
        break;
    default:
        Debug_Printf("Attempt to open non-removable volume for locking or ejection\n");
        return INVALID_HANDLE_VALUE;
    }

    sprintf(volume_name, "\\\\.\\%c:", drive + 'A');
    HANDLE volume = CreateFileA(volume_name, access, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
    if (volume == INVALID_HANDLE_VALUE) {
        Debug_Printf("Unable to open drive %c: for ejection\n", drive + 'A');
    }
    return volume;
}
