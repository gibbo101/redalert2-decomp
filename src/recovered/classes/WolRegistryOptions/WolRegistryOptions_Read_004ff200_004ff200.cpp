// bool WolRegistryOptions::Read_004ff200() (0x004FF200)
// Reads the DWORD "Options" of HKLM\SOFTWARE\Westwood\WOLAPI; HasOptions tells whether it was there.
#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
// @ref __imp__RegOpenKeyExA@20=0079a00c
// @ref __imp__RegQueryValueExA@24=0079a008
// @ref __imp__RegCloseKey@4=0079a004
// @ref ??_C@_0BK@MEEM@SOFTWARE?2Westwood?2WOLAPI?2?$AA@=007dae9c
// @ref ??_C@_07BFAH@Options?$AA@=007dae94

bool WolRegistryOptions::Read_004ff200()
{
    DWORD size = 4;
    HasOptions = false;
    char subkey[128];
    strcpy(subkey, "SOFTWARE\\Westwood\\WOLAPI\\");
    HKEY key;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, subkey, 0, 0xF003F, &key) == 0) {
        DWORD value = 0;
        DWORD type;
        if (RegQueryValueExA(key, "Options", 0, &type, (BYTE *)&value, &size) == 0 && type == 4) {
            HasOptions = true;
            Options = value;
        }
        RegCloseKey(key);
    }
    return HasOptions;
}
