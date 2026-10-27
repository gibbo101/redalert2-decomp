// int __fastcall CDFileClass::Is_Disk_Inserted(int drive) (0x0046FDB0)
// Whether the drive (0 = A:) has readable media: looks for any file in its root.
#include "shared/cd_file_class.hpp"
#include "shared/win32_find.hpp"
// @ref ??_C@_06GAEG@?$DP?3?2?$CK?4?$CK?$AA@=007d27d8

int __fastcall CDFileClass::Is_Disk_Inserted(int drive)
{
    char scan[] = "?:\\*.*";
    WIN32_FIND_DATA finddata;
    scan[0] = (char)(drive + 'A');
    HANDLE handle = FindFirstFileA(scan, &finddata);
    if (handle == INVALID_HANDLE_VALUE) {
        return 0;
    }
    FindClose(handle);
    return 1;
}
