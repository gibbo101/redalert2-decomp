// bool AnimClass::unknown_slot52() (0x00422ED0)
// Leaves the map: a vein animation clears its cell's 0x20000 flag (+0x140)
// first; when the ObjectClass slot succeeds the map entry is removed too.
// Needs ObjectClass::unknown_slot52 declared bool (0x005D3700 returns al).
#include "shared/anim.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_slot52@ObjectClass@@UAE_NXZ=005d3700

bool AnimClass::unknown_slot52()
{
    if (Class->IsVeins) {
        CoordStruct coord = Coord;
        unsigned long &flags = ((UnknownAnimCell *)&Map[coord])->Flags;
        flags = flags & ~0x20000;
    }
    if (ObjectClass::unknown_slot52()) {
        Map.Remove(this);
        return true;
    }
    return false;
}
