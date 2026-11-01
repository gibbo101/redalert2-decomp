// bool __fastcall CDFileClass::Find_Next_File(char *filename) (0x00470400)
// Continues Find_File's search: the next matching name (without its
// directory) replaces filename; when there is no search or no further match
// filename is emptied and the result is false.
#include "shared/cd_file_class.hpp"
#include "shared/crt_string.hpp"
#include "shared/win32_find.hpp"
// @ref ?FindHandle@CDFileClass@@2PAXA=007d27d4

bool __fastcall CDFileClass::Find_Next_File(char *filename)
{
    if (filename == 0) {
        return false;
    }
    if (FindHandle != INVALID_HANDLE_VALUE) {
        WIN32_FIND_DATA finddata;
        if (FindNextFileA(FindHandle, &finddata) == TRUE) {
            strcpy(filename, finddata.cFileName);
            return true;
        }
    }
    filename[0] = '\0';
    return false;
}
