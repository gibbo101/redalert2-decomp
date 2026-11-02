// WideString WorldDominationTour::PlayerCountGameOption::Describe(rc_ptr<WDTTerritory> const &territory, WideString const &prefix) const (0x00728980)
// The CSF text WDT:FourPlayerOnly or WDT:TwoPlayerOnly by the territory's
// PlayerCount, after prefix and ", " when prefix is not empty.
#include "shared/wdt_game_options.hpp"

namespace WorldDominationTour {

WideString PlayerCountGameOption::Describe(rc_ptr<WDTTerritory> const &territory, WideString const &prefix) const
{
    Wstring label(territory->PlayerCount == 4 ? "WDT:FourPlayerOnly" : "WDT:TwoPlayerOnly");
    if (prefix.Length() > 0) {
        WideString separator(L", ");
        return prefix + separator + StringTable::Load_String(label.Get(), 0, "D:\\Ra2\\WDTGameOptions.cpp", 104);
    }
    return WideString(StringTable::Load_String(label.Get(), 0, "D:\\Ra2\\WDTGameOptions.cpp", 107));
}

}
// @ref ??_C@_0BC@IGDO@WDT?3TwoPlayerOnly?$AA@=007fbc4c
// @ref ??_C@_0BD@FFMC@WDT?3FourPlayerOnly?$AA@=007fbc60
