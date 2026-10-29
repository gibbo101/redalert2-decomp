// bool __fastcall Set_Class_Root_Key(char const *key, char const *subkey, char const *value) (0x0068DBC0)
// Creates HKEY_CLASSES_ROOT\key (\subkey when given) and sets its default
// value to value when one is given; false when a registry call fails.
// The constant-first tests (`0 != subkey`) show in the copies Register_Com_Server
// inlines: `xor reg, reg; cmp reg, offset string`.
#include "shared/com_registration.hpp"
#include "shared/win32_api.hpp"
// @ref ??_C@_01PCFE@?2?$AA@=007cc944

bool __fastcall Set_Class_Root_Key(char const *key, char const *subkey, char const *value)
{
    HKEY handle;
    char path[260];
    bool result = false;

    lstrcpyA(path, key);
    if (0 != subkey) {
        lstrcatA(path, "\\");
        lstrcatA(path, subkey);
    }
    if (RegCreateKeyExA(HKEY_CLASSES_ROOT, path, 0, 0, 0, KEY_ALL_ACCESS, 0, &handle, 0) == 0) {
        if (0 == value || RegSetValueExA(handle, 0, 0, REG_SZ, (BYTE const *)value, lstrlenA(value) + 1) == 0) {
            result = true;
        }
        RegCloseKey(handle);
    }
    return result;
}
