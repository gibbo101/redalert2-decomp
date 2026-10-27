// bool WorldDominationTour::Voices::Pick_Emphasis(int group, int kind, Wstring &name) const (0x00731CA0)
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

bool Voices::Pick_Emphasis(int group, int kind, Wstring &name) const
{
    return Groups[group].Pick_Emphasis(Faction, kind, name);
}

}
