// bool WorldDominationTour::Voices::Pick(int group, int kind, Wstring &name) const (0x00731BC0)
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

bool Voices::Pick(int group, int kind, Wstring &name) const
{
    return Groups[group].Pick(Faction, kind, name);
}

}
