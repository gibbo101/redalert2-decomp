// bool __fastcall WorldDominationTour::Voices::Pick(int faction, DynamicVectorClass<unsigned> const &lines, Wstring &name) (0x00731E60)
// The speech name of a random line of the list (false, name released, for
// an empty list).
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

bool __fastcall Voices::Pick(int faction, DynamicVectorClass<unsigned> const &lines, Wstring &name)
{
    name.Release();
    if (lines.Count() <= 0) {
        return false;
    }
    int index = lines.Count() == 1 ? 0 : unknown_random_839218(0, lines.Count() - 1);
    return Make_Name(faction, lines[index], name);
}

}
