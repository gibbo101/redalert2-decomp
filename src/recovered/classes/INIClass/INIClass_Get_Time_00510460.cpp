// INIClass::Get_Time (0x00510460)
// Reads a duration written by Put_Time ("hh:mm:ss") back as 1/60 s ticks;
// defvalue when the entry is missing.
#include "shared/ini_class.hpp"
// @ref ?time_format_007d4ef8@@3QBDB=007d4ef8

// "%d:%d:%d" (0x007D4EF8): the literal lives in an earlier unit's pool
// (CoopCampaignClass::Next_Map 0x0048E360 formats with it too).
extern char const time_format_007d4ef8[];

int INIClass::Get_Time(char const *section, char const *entry, int defvalue) const
{
    if (section == 0 || entry == 0) return defvalue;

    INIEntry *entptr = Find_Entry(section, entry);
    if (entptr != 0 && entptr->Value != 0) {
        int hours = 0;
        int minutes = 0;
        int seconds = 0;
        sscanf(entptr->Value, time_format_007d4ef8, &hours, &minutes, &seconds);
        return ((hours * 60 + minutes) * 60 + seconds) * 60;
    }
    return defvalue;
}
