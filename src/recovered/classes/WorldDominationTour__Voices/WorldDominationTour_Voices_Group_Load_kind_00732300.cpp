// void WorldDominationTour::Voices::Group::Load(INIClass &ini, Wstring const &section, int faction, int kind, Wstring const &key) (0x00732300)
// <faction name><group name><key> and the same + "Emphasis".
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

void Voices::Group::Load(INIClass &ini, Wstring const &section, int faction, int kind, Wstring const &key)
{
    Wstring entry = Wstring_Join(Faction_Name(faction), Name) + key;
    Wstring value;
    {
        Wstring empty("");
        ini.Get_String(section, entry, empty, value);
    }
    Voices::Parse_List(value, Lines[kind * 2]);
    entry += "Emphasis";
    {
        Wstring empty("");
        ini.Get_String(section, entry, empty, value);
    }
    Voices::Parse_List(value, Lines[kind * 2 + 1]);
}

}
