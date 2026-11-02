// WideString WorldDominationTour::RangedGameOption::Describe(rc_ptr<WDTTerritory> const &territory, WideString const &prefix) const (0x00728690)
// The CSF text of Label followed by the territory's range index, after
// prefix and ", " when prefix is not empty.
#include "shared/wdt_game_options.hpp"

namespace WorldDominationTour {

WideString RangedGameOption::Describe(rc_ptr<WDTTerritory> const &territory, WideString const &prefix) const
{
    int range = Get_Range(territory);
    Wstring label = Wstring_Join(Label, Wstring_From_Integer(range));
    if (prefix.Length()) {
        WideString separator(L", ");
        return prefix + separator + StringTable::Load_String(label.Get(), 0, "D:\\Ra2\\WDTGameOptions.cpp", 22);
    }
    return WideString(StringTable::Load_String(label.Get(), 0, "D:\\Ra2\\WDTGameOptions.cpp", 25));
}

}
