// WorldDominationTour::Map::AnimationPalette::~AnimationPalette() (0x0072A600): deletes the drawer.
// Expanded in Map::~Map; this is the unit's out-of-line copy.
// @ref ??1Wstring@@QAE@XZ=0076d9e0
#include "shared/wdt_map.hpp"

namespace WorldDominationTour {

Map::AnimationPalette::~AnimationPalette()
{
    delete Drawer;
}

}
