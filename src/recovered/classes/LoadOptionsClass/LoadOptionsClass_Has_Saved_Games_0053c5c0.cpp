// bool LoadOptionsClass::Has_Saved_Games_0053c5c0() (0x0053C5C0)
// Whether a file with the options' extension other than SAVEGAME.NET exists (and is not a hidden, system or
// directory entry, attribute mask 0x116).
#include "shared/load_dlg.hpp"
#include "shared/crt_string.hpp"
// @ref __imp__FindFirstFileA@8=0079a1fc
// @ref __imp__FindNextFileA@8=0079a200
// @ref __imp__FindClose@4=0079a2f8
// @ref __stricmp=00781f20
// @ref _sprintf=007820f4
// @ref ??_C@_05GHIA@?$CK?4?$CF3s?$AA@=007dfabc
// @ref ??_C@_0N@JPFB@SAVEGAME?4NET?$AA@=007d6a4c

bool LoadOptionsClass::Has_Saved_Games_0053c5c0()
{
    char pattern[64];
    WIN32_FIND_DATA find;
    bool found = false;
    sprintf(pattern, "*.%3s", Extension);
    HANDLE handle = FindFirstFileA(pattern, &find);
    if (handle != INVALID_HANDLE_VALUE) {
        do {
            if (!(find.dwFileAttributes & 0x116) && _stricmp(find.cFileName, "SAVEGAME.NET") != 0) {
                found = true;
                break;
            }
        } while (FindNextFileA(handle, &find));
    }
    FindClose(handle);
    return found;
}
