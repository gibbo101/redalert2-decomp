// void WorldDominationTour::Voices::Load_List(INIClass &ini, Wstring const &section, int index, Wstring const &key) (0x00731AA0)
// The comma separated line numbers of <faction name><key>.
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

void Voices::Load_List(INIClass &ini, Wstring const &section, int index, Wstring const &key)
{
    Wstring entry = Wstring_Join(Faction_Name(Faction), key);
    Wstring value;
    {
        Wstring empty("");
        ini.Get_String(section, entry, empty, value);
    }
    Parse_List(value, Lists[index]);
}

}
