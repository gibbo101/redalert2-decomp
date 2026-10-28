// HKEY __fastcall Get_Registry_Sub_Key(HKEY base_key, char const *search_key, bool close) (0x007341C0)
#include "shared/win_modem.hpp"
#include "shared/crt_string.hpp"

HKEY __fastcall Get_Registry_Sub_Key(HKEY base_key, char const *search_key, bool close)
{
    char class_buffer[1024];
    DWORD class_buffer_size = sizeof(class_buffer);
    DWORD num_sub_keys;
    DWORD longest_sub_key_name;
    DWORD longest_class_string;
    DWORD num_value_entries;
    DWORD longest_value_name_length;
    DWORD longest_value_data_length;
    DWORD security_descriptor_length;
    FILETIME last_write_time;
    if (RegQueryInfoKeyA(base_key, class_buffer, &class_buffer_size, 0, &num_sub_keys, &longest_sub_key_name,
                         &longest_class_string, &num_value_entries, &longest_value_name_length,
                         &longest_value_data_length, &security_descriptor_length, &last_write_time) != 0) {
        return 0;
    }
    DWORD sub_key_buffer_size = longest_sub_key_name + 16;
    char *sub_key_buffer = new char[sub_key_buffer_size];
    char *sub_key_class = new char[longest_class_string + 1];
    for (DWORD key_num = 0; key_num < num_sub_keys; key_num++) {
        *sub_key_buffer = 0;
        longest_sub_key_name = sub_key_buffer_size;
        RegEnumKeyExA(base_key, key_num, sub_key_buffer, &longest_sub_key_name, 0, sub_key_class, &longest_class_string,
                      &last_write_time);
        if (_stricmp(search_key, sub_key_buffer) == 0) {
            HKEY result_key;
            if (RegOpenKeyExA(base_key, sub_key_buffer, 0, KEY_READ, &result_key) == 0) {
                if (close) {
                    RegCloseKey(base_key);
                }
                delete[] sub_key_buffer;
                delete[] sub_key_class;
                return result_key;
            }
        }
    }
    if (close) {
        RegCloseKey(base_key);
    }
    delete[] sub_key_buffer;
    delete[] sub_key_class;
    return 0;
}
