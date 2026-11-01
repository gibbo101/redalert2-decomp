// bool ParasiteClass::Can_Infect_006078F0(FootClass *target) (0x006078F0)
// A target can take a parasite when it is alive and on the map, has no
// parasite already and its type allows one; a naval parasite also needs the
// target on a water cell (or off the map).
#include "shared/foot.hpp"
#include "shared/cell.hpp"
#include "shared/parasite.hpp"
// @ref ?Is_Tile_Water@CellClass@@QBE_NXZ=0047a270

bool ParasiteClass::Can_Infect_006078F0(FootClass *target)
{
    if (target != 0 && !target->unknown_76 && target->unknown_7d && target->Strength != 0
        && target->unknown_580 == 0 && target->unknown_slot32()->Parasiteable) {
        if (Owner == 0 || !Owner->unknown_slot32()->Naval || target->unknown_slot105() == 0
            || ((CellClass *)target->unknown_slot105())->Is_Tile_Water()) {
            return true;
        }
    }
    return false;
}
