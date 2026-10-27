// int __fastcall CDFileClass::Set_Search_Drives(char *pathlist) (0x0046FE70)
// Appends the ';'-separated directories of pathlist to the search list and
// remembers the list in RawPath. An entry starting "?:" stands for the CD
// drive (its letter replaced) and is added only when a disk is in it. Returns 0 when at least one
// directory was added.
// Unresolved: Get_CD_Index (0x004983E0) and its timeout 120 are hypotheses;
// the RawPath test compares the duplicated copy (always different), as the
// original does.
#include "shared/cd_file_class.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_tokens.hpp"
// @ref _strtok=00782ec2
// @ref ??_C@_01PCFE@?2?$AA@=007cc944
// @ref ??_C@_02JBPM@?$DP?3?$AA@=007d27e0
// @ref __strnicmp=00783810
// @ref ?Get_CD_Index@@YIHHH@Z=004983e0
// @ref ?RawPath@CDFileClass@@2PADA=008508a4
// @ref ?CurrentCDDrive@CDFileClass@@2HA=0085089c

int __fastcall CDFileClass::Set_Search_Drives(char *pathlist)
{
    bool found = false;
    if (pathlist == 0) {
        return 0;
    }

    char *ptr = _strdup(pathlist);
    if (ptr != RawPath) {
        strcat(RawPath, ";");
        strcat(RawPath, ptr);
    }

    char const *path = strtok(ptr, ";");
    while (path != 0) {
        if (strlen(path) != 0) {
            char pathname[_MAX_PATH];
            strcpy(pathname, path);
            char last = pathname[strlen(pathname) - 1];
            if (last != ':' && last != '\\') {
                strcat(pathname, "\\");
            }
            if (_strnicmp(pathname, "?:", 2) == 0) {
                if (CurrentCDDrive != 0) {
                    found = true;
                    if (Get_CD_Index(CurrentCDDrive, 120) > -1) {
                        pathname[0] = (char)(CurrentCDDrive + 'A');
                        Add_Search_Drive(pathname);
                    }
                }
            } else {
                found = true;
                Add_Search_Drive(pathname);
            }
        }
        path = strtok(0, ";");
    }
    free(ptr);
    return !found;
}
