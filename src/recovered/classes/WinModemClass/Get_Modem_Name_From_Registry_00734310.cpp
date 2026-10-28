// bool __fastcall Get_Modem_Name_From_Registry(char *buffer, int buffer_len) (0x00734310)
// Copies the FriendlyName of HKEY_LOCAL_MACHINE\Enum\Root\Modem\0000.
#include "shared/win_modem.hpp"
#include "shared/crt_memory.hpp"
// @ref ??_C@_04KFCP@Enum?$AA@=007e2808
// @ref ??_C@_04PNFB@Root?$AA@=007fca3c
// @ref ??_C@_05BJKG@Modem?$AA@=007e299c
// @ref ??_C@_04NILH@0000?$AA@=007fca34
// @ref ??_C@_0N@IOME@FriendlyName?$AA@=007fca24

bool __fastcall Get_Modem_Name_From_Registry(char *buffer, int buffer_len)
{
    char value[256];
    DWORD value_size = sizeof(value);
    HKEY key = Get_Registry_Sub_Key(HKEY_LOCAL_MACHINE, "Enum", false);
    if (key == 0) {
        return false;
    }
    key = Get_Registry_Sub_Key(key, "Root", true);
    if (key == 0) {
        return false;
    }
    key = Get_Registry_Sub_Key(key, "Modem", true);
    if (key == 0) {
        return false;
    }
    key = Get_Registry_Sub_Key(key, "0000", true);
    if (key == 0) {
        return false;
    }
    if (RegQueryValueExA(key, "FriendlyName", 0, 0, (BYTE *)value, &value_size) != 0) {
        RegCloseKey(key);
        return false;
    }
    RegCloseKey(key);
    memcpy(buffer, value, buffer_len < (int)value_size ? buffer_len : value_size);
    return true;
}
