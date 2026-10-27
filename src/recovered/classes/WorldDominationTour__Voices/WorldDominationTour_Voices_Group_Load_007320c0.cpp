// void WorldDominationTour::Voices::Group::Load(INIClass &ini, Wstring const &section, int faction) (0x007320C0)
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

void Voices::Group::Load(INIClass &ini, Wstring const &section, int faction)
{
    {
        Wstring key("Win");
        Load(ini, section, faction, 0, key);
    }
    {
        Wstring key("Lose");
        Load(ini, section, faction, 1, key);
    }
    {
        Wstring key("Draw");
        Load(ini, section, faction, 2, key);
    }
}

}
