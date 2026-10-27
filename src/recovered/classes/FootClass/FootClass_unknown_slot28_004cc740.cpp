// int FootClass::unknown_slot28(ObjectClass *object, bool arg2) (0x004CC740)
// TechnoClass's answer, except that at a ground-level spot of the object
// (raised by a bridge's height) that passes the map test 0x00568140, in a
// game mode of 0, a nonzero answer becomes 1 for a MoveToShroud type and 2
// otherwise.
#include "shared/foot.hpp"
#include "shared/locomotion.hpp"
#include "shared/techno_type.hpp"
// @ref ?unknown_slot28@TechnoClass@@UAEHPAVObjectClass@@_N@Z=006cc5d0
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298

int FootClass::unknown_slot28(ObjectClass *object, bool arg2)
{
    int result = TechnoClass::unknown_slot28(object, arg2);
    CoordStruct coord = object->Center_Coord();
    coord.Z = Map.Unknown_0055A280(coord);
    if (Loco_Cell(coord)->Flags & 0x100) {
        coord.Z += unknown_geometry_j;
    }
    if (Map.Unknown_00568140(coord) && result != 0 && unknown_game_mode_a3d298 == 0) {
        return unknown_slot32()->MoveToShroud ? 1 : 2;
    }
    return result;
}
