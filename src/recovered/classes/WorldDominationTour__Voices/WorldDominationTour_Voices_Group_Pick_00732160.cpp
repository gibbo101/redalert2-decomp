// bool WorldDominationTour::Voices::Group::Pick(int faction, int kind, Wstring &name) const (0x00732160)
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

bool Voices::Group::Pick(int faction, int kind, Wstring &name) const
{
    return Voices::Pick(faction, Lines[kind * 2], name);
}

}
