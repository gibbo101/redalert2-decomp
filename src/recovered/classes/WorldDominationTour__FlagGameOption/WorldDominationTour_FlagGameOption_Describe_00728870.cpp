// WideString WorldDominationTour::FlagGameOption::Describe(rc_ptr<WDTTerritory> const &territory, WideString const &prefix) const (0x00728870)
// prefix followed by ", " and the CSF text of the label for the flag's
// state (OnLabel or OffLabel); prefix alone when that label is empty.
#include "shared/wdt_game_options.hpp"

namespace WorldDominationTour {

WideString FlagGameOption::Describe(rc_ptr<WDTTerritory> const &territory, WideString const &prefix) const
{
    Wstring label = (territory->OptionFlags & Flag) ? OnLabel : OffLabel;
    if (!label.Length()) {
        return prefix;
    }
    if (prefix.Length() > 0) {
        WideString separator(L", ");
        return prefix + separator + StringTable::Load_String(label.Get(), 0, "D:\\Ra2\\WDTGameOptions.cpp", 78);
    }
    return WideString(StringTable::Load_String(label.Get(), 0, "D:\\Ra2\\WDTGameOptions.cpp", 81));
}

}
