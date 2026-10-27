// int FootClass::unknown_slot27(Cell const *cell, bool arg2, bool arg3) (0x004CC650)
// TechnoClass's answer, except that at the centre of the cell (raised to
// the ground and by a bridge's height) passing the map test 0x00568140 a
// nonzero answer becomes 2, or 1 for a MoveToShroud type when the map test
// 0x0055A660 holds and the answer is not 0x33.
#include "shared/foot.hpp"
#include "shared/locomotion.hpp"
#include "shared/techno_type.hpp"
// @ref ?unknown_slot27@TechnoClass@@UAEHPBVCell@@_N1@Z=006ccce0

int FootClass::unknown_slot27(Cell const *cell, bool arg2, bool arg3)
{
    int result = TechnoClass::unknown_slot27(cell, arg2, arg3);
    CoordStruct coord(cell->X * 256 + 128, cell->Y * 256 + 128, 0);
    coord.Z = Map.Unknown_0055A280(coord);
    if (Loco_Cell(coord)->Flags & 0x100) {
        coord.Z += unknown_geometry_j;
    }
    if (Map.Unknown_00568140(coord) && result != 0) {
        if (unknown_slot32()->MoveToShroud && Map.Unknown_0055A660(*cell, true)) {
            if (result != 0x33) {
                return 1;
            }
        } else {
            return 2;
        }
    }
    return result;
}
