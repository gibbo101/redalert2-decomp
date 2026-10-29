// HKEY __fastcall Search_Registry_Key(HKEY key, char const *value_name, char const *value) (0x0059CBA0)
#include "shared/win_modem.hpp"
#include "shared/crt_string.hpp"
// @ref ?Search_Registry_Key@@YIPAUHKEY__@@PAU1@PBD1@Z=0059cba0

HKEY __fastcall Search_Registry_Key(HKEY key, char const *value_name, char const *value)
{
    DWORD index = 0;
    char *sub_key_name = new char[256];
    DWORD sub_key_name_size = 256;
    FILETIME last_write_time;
    DWORD value_type;
    unsigned char *key_value = new unsigned char[256];
    DWORD key_value_size = 256;
    LONG result;
    do {
        sub_key_name_size = 256;
        result = RegEnumKeyExA(key, index++, sub_key_name, &sub_key_name_size, 0, 0, 0, &last_write_time);
        if (result == 0) {
            HKEY sub_key = Get_Registry_Sub_Key(key, sub_key_name, false);
            if (sub_key) {
                key_value_size = 256;
                if (RegQueryValueExA(sub_key, value_name, 0, &value_type, key_value, &key_value_size) == 0) {
                    if (value_type == REG_SZ && !strcmp((char *)key_value, value)) {
                        delete[] sub_key_name;
                        delete[] key_value;
                        return sub_key;
                    }
                }
                HKEY found = Search_Registry_Key(sub_key, value_name, value);
                RegCloseKey(sub_key);
                if (found) {
                    delete[] sub_key_name;
                    delete[] key_value;
                    return found;
                }
            }
        }
    } while (result == 0);
    delete[] sub_key_name;
    delete[] key_value;
    return 0;
}
