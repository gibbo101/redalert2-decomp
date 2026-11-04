// void JumpjetLocomotionClass::Move_To(CoordStruct to) (0x0052F600)
#include "shared/jumpjet_locomotion.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_coord_a6e3e0@@3UCoordStruct@@A=00a6e3e0
// @ref ?Unknown_005502E0@MapClass@@QAE?AVCell@@ABV2@HHH_NUPoint2D@@HHHH0H@Z=005502e0

void __stdcall JumpjetLocomotionClass::Move_To(CoordStruct to)
{
    if (unknown_3c != unknown_coord_a6e3e0 && unknown_4c != 0 && unknown_88) {
        LinkedTo->unknown_slot59(unknown_3c);
        unknown_88 = false;
    }
    unknown_3c = CoordStruct(to.X, to.Y, to.Z);
    if (to != unknown_coord_a6e3e0) {
        Cell cell;
        if (LinkedTo->Kind_Of() == 1 && !((UnitClass *)LinkedTo)->Type->BalloonHover) {
            cell = Map.Unknown_005502E0(Coord_Cell(to), LinkedTo->unknown_slot32()->SpeedType, -1, 9, false, Point2D(1, 1), 0, 0, 0, 0, Cell(0, 0), 0);
        } else {
            cell = Map.Unknown_005502E0(Coord_Cell(to), LinkedTo->unknown_slot32()->SpeedType, -1, 9, (Map[CoordStruct(to)].unknown_140 >> 8) & 1, Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0);
        }
        CoordStruct coord = unknown_5310a0(CoordStruct(cell));
        if (coord != unknown_coord_a6e3e0) {
            if (LinkedTo->Kind_Of() != 1 || (!LinkedTo->unknown_slot32()->BalloonHover && LinkedTo->MissionQueue != 7 && LinkedTo->unknown_slot91() != 7)) {
                unknown_3c = coord;
            }
            if (LinkedTo->MissionQueue != 7 && LinkedTo->unknown_slot91() != 7) {
                LinkedTo->unknown_494 = &Map[unknown_3c];
            }
            unknown_48 = true;
            if (unknown_4c == 4) {
                unknown_4c = 1;
                unknown_78 = Height;
            }
        }
    } else {
        unknown_48 = false;
    }
}

