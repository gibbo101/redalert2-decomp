// INIClass::Get_Wide_String (0x0050F010)
// Reads the entry as a string table label (TXT_...) and copies its localized
// text into buffer, at most size characters, null terminated; returns the
// length. Name from CampaignClass::Read_INI's view (shared/campaign.hpp).
#include "shared/ini_class.hpp"
#include "shared/string_table.hpp"
// @ref ??_C@_0P@BMNN@D?3?2Ra2?2Ini?4CPP?$AA@=007db4bc

int INIClass::Get_Wide_String(char const *section, char const *entry, wchar_t *buffer, int size) const
{
    char label[1024];

    Get_String(section, entry, 0, label, sizeof(label));
    wcsncpy(buffer, StringTable::Load_String(label, 0, "D:\\Ra2\\Ini.CPP", 1827), size);
    buffer[size - 1] = 0;
    return wcslen(buffer);
}
