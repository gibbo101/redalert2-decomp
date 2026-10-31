// void __stdcall JumpjetLocomotionClass::Stop_Moving() (0x0052F960, ILocomotion 18)
// While moving (and 0x00A40774 clear): the target claim is released; the
// jumpjet then moves to the nearest free cell (0x005502E0 for its speed
// type and movement zone) at ground (bridge) height. With no free cell a
// living object is destroyed with the rules' C4 warhead and the target
// cleared.
#include "shared/jumpjet_locomotion.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/cell.hpp"
#include "shared/techno_type.hpp"
#include "shared/rules.hpp"
// @ref ?unknown_coord_a6e3e0@@3UCoordStruct@@A=00a6e3e0
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?Unknown_005502E0@MapClass@@QAE?AVCell@@ABV2@HHH_NUPoint2D@@11110H@Z=005502e0

void __stdcall JumpjetLocomotionClass::Stop_Moving()
{
    if (unknown_a40774 == 0 && unknown_48) {
        if (unknown_3c != unknown_coord_a6e3e0 && unknown_4c != 0 && unknown_88) {
            LinkedTo->unknown_slot59(unknown_3c);
            unknown_88 = false;
        }
        Cell here = Coord_Cell(Object_Coord(LinkedTo));
        Cell cell = Map.Unknown_005502E0(here, LinkedTo->unknown_slot32()->SpeedType, -1, LinkedTo->unknown_slot32()->MovementZone, false, Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0);
        if (cell != unknown_geometry_k) {
            CoordStruct coord = Cell_Coord(cell);
            coord.Z = Map.Unknown_0055A280(coord);
            if (Map[cell].unknown_140 & 0x100) {
                coord.Z += unknown_geometry_j;
            }
            Move_To(CoordStruct(coord.X, coord.Y, coord.Z));
            return;
        }
        if (LinkedTo->Strength > 0) {
            LinkedTo->unknown_slot86(&LinkedTo->Strength, 0, Rules->unknown_c74, 0, 1, 1);
            unknown_3c = unknown_coord_a6e3e0;
        }
    }
}
