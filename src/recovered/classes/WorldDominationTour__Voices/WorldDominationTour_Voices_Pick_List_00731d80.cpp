// bool WorldDominationTour::Voices::Pick_List(int index, Wstring &name) const (0x00731D80)
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

bool Voices::Pick_List(int index, Wstring &name) const
{
    return Pick(Faction, Lists[index], name);
}

}
