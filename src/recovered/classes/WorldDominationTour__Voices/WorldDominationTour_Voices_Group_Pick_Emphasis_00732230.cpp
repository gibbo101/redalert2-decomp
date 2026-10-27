// bool WorldDominationTour::Voices::Group::Pick_Emphasis(int faction, int kind, Wstring &name) const (0x00732230)
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

bool Voices::Group::Pick_Emphasis(int faction, int kind, Wstring &name) const
{
    return Voices::Pick(faction, Lines[kind * 2 + 1], name);
}

}
