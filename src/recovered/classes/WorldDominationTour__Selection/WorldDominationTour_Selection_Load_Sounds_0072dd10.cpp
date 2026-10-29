// void Selection::Load_Sounds(INIClass &ini, Wstring const &section) (0x0072DD10)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Load_Sounds(INIClass &ini, Wstring const &section)
{
    Wstring value;
    int count = ini.Entry_Count(section);
    for (int index = 0; index < count; index++) {
        Wstring entry = ini.Get_Entry(section, index);
        if (entry != 0 && ini.Get_String(section, entry, (char const *)0, value) > 0) {
            if (entry == "Theme") {
                ThemeName = value;
                break;
            }
            MSSfxEntry *sound = new MSSfxEntry(entry, value);
            if (sound->Name == 0) {
                delete sound;
            } else if (sound != 0) {
                Sounds.Add(sound);
            }
        }
    }
}
}
// @ref ??_C@_05PDLI@Theme?$AA@=007d9d6c
