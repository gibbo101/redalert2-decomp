// bool __fastcall CDFileClass::Find_File(char *filename) (0x004702B0)
// Looks for filename as given, then in each search directory; on success
// replaces filename with the found name (without its directory) and keeps
// the find handle open until the next call.
// Unresolved: the original name; 0x116 = directory | system | hidden | volume
// attribute bits that disqualify a match.
#include "shared/cd_file_class.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_tokens.hpp"
#include "shared/win32_find.hpp"
// @ref ?FindHandle@CDFileClass@@2PAXA=007d27d4

bool __fastcall CDFileClass::Find_File(char *filename)
{
    if (filename == 0) {
        return false;
    }
    if (FindHandle != INVALID_HANDLE_VALUE) {
        FindClose(FindHandle);
        FindHandle = INVALID_HANDLE_VALUE;
    }

    char path[_MAX_PATH];
    WIN32_FIND_DATA finddata;
    strcpy(path, filename);
    HANDLE handle = FindFirstFileA(path, &finddata);
    if (handle != INVALID_HANDLE_VALUE && (finddata.dwFileAttributes & 0x116) == 0) {
        strcpy(filename, finddata.cFileName);
        FindHandle = handle;
        return true;
    }

    for (CDSearchDrive *drive = First; drive != 0; drive = drive->Next) {
        strcpy(path, drive->Path);
        strcat(path, filename);
        handle = FindFirstFileA(path, &finddata);
        if (handle != INVALID_HANDLE_VALUE && (finddata.dwFileAttributes & 0x116) == 0) {
            strcpy(filename, finddata.cFileName);
            FindHandle = handle;
            return true;
        }
    }
    return false;
}
