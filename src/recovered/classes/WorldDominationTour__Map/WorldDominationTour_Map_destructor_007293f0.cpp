// WorldDominationTour::Map::~Map() (0x007293F0): deletes the index surface, both drawers and
// the palettes, clears the two work surfaces and copies the cleared one to the screen.
// @ref ??_7?$VectorClass@PAVAnimationPalette@Map@WorldDominationTour@@@@6B@=007af25c
// @ref ??_7?$VectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@6B@=007af23c
// @ref ??1ReferenceCounted@@UAE@XZ=00639710
// @ref ??1Wstring@@QAE@XZ=0076d9e0
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?unknown_surface_839954@@3PAVSurface@@A=00839954
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
#include "shared/wdt_map.hpp"

namespace WorldDominationTour {

Map::~Map()
{
    delete unknown_24;
    delete unknown_14;
    for (int i = 0; i < Palettes.Count(); i++) {
        delete Palettes[i];
    }
    unknown_surface_839958->Fill(0);
    unknown_surface_839954->Fill(0);
    unknown_surface_839950->Copy_From(*unknown_surface_839954, false, true);
    delete unknown_78;
}

}
