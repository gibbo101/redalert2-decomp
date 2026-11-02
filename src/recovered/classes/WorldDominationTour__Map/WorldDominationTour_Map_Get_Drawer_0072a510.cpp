// ConvertClass *WorldDominationTour::Map::Get_Drawer(Wstring const &name) (0x0072A510): the
// drawer of the palette file name, loaded (0x005AC560) and kept in Palettes on first use.
// @ref ??8Wstring@@QBE_NABV0@@Z=0076da70
// @ref ??0Wstring@@QAE@ABV0@@Z=0076d980
// @ref ?unknown_load_drawer_5ac560@@YIPAVConvertClass@@ABVWstring@@@Z=005ac560
// @ref ??2@YAPAXI@Z=00782017
#include "shared/wdt_map.hpp"

namespace WorldDominationTour {

ConvertClass *Map::Get_Drawer(Wstring const &name)
{
    for (int i = 0; i < Palettes.Count(); i++) {
        if (Palettes[i]->Name == name) {
            return Palettes[i]->Drawer;
        }
    }
    ConvertClass *drawer = unknown_load_drawer_5ac560(name);
    if (drawer) {
        Palettes.Add(new AnimationPalette(name, drawer));
    }
    return drawer;
}

}
