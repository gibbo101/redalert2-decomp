// INIClass::Get_Wide_String (0x0050F1B0)
// As Get_Wide_String 0x0050F010, with a default label: the text of the label
// the entry names, or of defvalue when the entry is missing or empty.
#include "shared/ini_class.hpp"
#include "shared/string_table.hpp"
// @ref ??_C@_0P@BMNN@D?3?2Ra2?2Ini?4CPP?$AA@=007db4bc

int INIClass::Get_Wide_String(char const *section, char const *entry, wchar_t *buffer, char const *defvalue,
                              int size) const
{
    char label[1024];

    Get_String(section, entry, 0, label, sizeof(label));
    if (strlen(label) == 0) {
        wcsncpy(buffer, StringTable::Load_String(defvalue, 0, "D:\\Ra2\\Ini.CPP", 1841), size);
    } else {
        wcsncpy(buffer, StringTable::Load_String(label, 0, "D:\\Ra2\\Ini.CPP", 1843), size);
    }
    buffer[size - 1] = 0;
    return wcslen(buffer);
}
