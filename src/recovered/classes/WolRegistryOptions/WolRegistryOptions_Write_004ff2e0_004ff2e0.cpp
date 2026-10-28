// bool WolRegistryOptions::Write_004ff2e0(unsigned int options) (0x004FF2E0)
// Stores the DWORD "Options" under HKLM\SOFTWARE\Westwood\WOLAPI (creating the key
// when it is missing), then reads the value back into Options / HasOptions.
// Returns whether the value was written.
#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
// @ref __imp__RegOpenKeyExA@20=0079a00c
// @ref __imp__RegCreateKeyExA@36=0079a018
// @ref __imp__RegSetValueExA@24=0079a014
// @ref __imp__RegQueryValueExA@24=0079a008
// @ref __imp__RegCloseKey@4=0079a004
// @ref ??_C@_0BK@MEEM@SOFTWARE?2Westwood?2WOLAPI?2?$AA@=007dae9c
// @ref ??_C@_07BFAH@Options?$AA@=007dae94

bool WolRegistryOptions::Write_004ff2e0(unsigned int options)
{
    bool written = false;
    HKEY key;
    DWORD value;
    HKEY readhandle;
    DWORD size;
    DWORD type;
    DWORD disposition;
    char subkey[128];
    strcpy(subkey, "SOFTWARE\\Westwood\\WOLAPI\\");
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, subkey, 0, 0xF003F, &key) != 0) {
        if (RegCreateKeyExA(HKEY_LOCAL_MACHINE, subkey, 0, 0, 0, 0xF003F, 0, &key, &disposition) != 0) {
            return false;
        }
    }
    if (RegSetValueExA(key, "Options", 0, 4, (BYTE *)&options, 4) == 0) {
        written = true;
    }
    RegCloseKey(key);
    HasOptions = false;
    size = 4;
    char readkey[128];
    strcpy(readkey, "SOFTWARE\\Westwood\\WOLAPI\\");
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, readkey, 0, 0xF003F, &readhandle) == 0) {
        value = 0;
        if (RegQueryValueExA(readhandle, "Options", 0, &type, (BYTE *)&value, &size) == 0 && type == 4) {
            HasOptions = true;
            Options = value;
        }
        RegCloseKey(readhandle);
    }
    return written;
}
