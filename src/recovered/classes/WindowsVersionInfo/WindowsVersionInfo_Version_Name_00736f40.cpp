// char *WindowsVersionInfo::Version_Name() (0x00736F40)
// @ref ?unknown_version_name_b25df0@@3PADA=00b25df0
// @ref ??_C@_0M@OMON@Windows?595?5?$AA@=007fd050
// @ref ??_C@_0M@BFLJ@Windows?598?5?$AA@=007fd05c
// @ref ??_C@_0O@NCJI@Windows?5NT?54?5?$AA@=007fd068
// @ref ??_C@_0O@MEDC@Windows?5NT?55?5?$AA@=007fd078
#include "shared/windows_version.hpp"
#include "shared/crt_string.hpp"

char *WindowsVersionInfo::Version_Name()
{
    if (IsWin9x && MajorVersion == 4 && MinorVersion == 0) {
        strcpy(unknown_version_name_b25df0, "Windows 95 ");
    }
    if (IsWin9x && (MajorVersion > 4 || (MajorVersion == 4 && MinorVersion >= 10))) {
        strcpy(unknown_version_name_b25df0, "Windows 98 ");
    }
    if (IsWinNT && MajorVersion >= 5) {
        strcpy(unknown_version_name_b25df0, "Windows NT 5 ");
    }
    if (IsWinNT) {
        strcpy(unknown_version_name_b25df0, "Windows NT 4 ");
    }
    strcat(unknown_version_name_b25df0, AdditionalInfo);
    return unknown_version_name_b25df0;
}
