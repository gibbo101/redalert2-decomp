// bool TeleportLocomotionClass::unknown_6e06b0(CoordStruct const &to) (0x006E06B0)
// Move_To's step: picks the arrival coordinate (+0x28) for a warp to `to`.
// The object is lifted from its old place (slot 59). Toward a bridge cell
// it counts as on the bridge when it stands well above the ground. An
// infantry takes the free sub-cell spot nearest `to` (0x004764B0),
// preferring the occupied spot when its target (+0x494, a unit, aircraft
// or the building there) is at `to` while on missions 8, 9, 7 or 25; a
// refused cell (slot 101) leaves it searching the cells near its target
// (0x005502E0). Other objects take the centre of `to`'s cell or of the
// nearest free one, unless +0x210 holds. The object is placed (slot 58)
// at the arrival point, or back where it stands when there is none
// (false).
#include "shared/teleport_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/techno_type.hpp"
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0
// @ref _unknown_geometry_g=00ac02b8
// @ref _unknown_geometry_k=00ac0260
// @ref ?unknown_coord_ac0280@@3UCoordStruct@@A=00ac0280

bool TeleportLocomotionClass::unknown_6e06b0(CoordStruct const &to)
{
    if (unknown_28 != unknown_coord_ac0280) {
        LinkedTo->unknown_slot59(unknown_28);
    } else {
        LinkedTo->unknown_slot59(Object_Coord(LinkedTo));
    }
    CoordStruct coord = to;
    if (to != unknown_coord_ac0280) {
        bool bridge = (Map[coord].unknown_140 & 0x100) && Object_Coord(LinkedTo).Z > Map.Unknown_0055A280(coord) + unknown_geometry_g * 3;
        if (LinkedTo->Kind_Of() == 15) {
            bool target_here = false;
            if (LinkedTo->unknown_slot91() == 8 || LinkedTo->unknown_slot91() == 9 || LinkedTo->unknown_slot91() == 7 || LinkedTo->unknown_slot91() == 25) {
                {
                    ObjectClass *target = (ObjectClass *)LinkedTo->unknown_494;
                    if (target != 0 && target->Kind_Of() == 1 && target->unknown_slot104() == Coord_Cell(to)) {
                        target_here = true;
                    }
                }
                {
                    ObjectClass *target = (ObjectClass *)LinkedTo->unknown_494;
                    if (target != 0 && target->Kind_Of() == 2 && target->unknown_slot104() == Coord_Cell(to)) {
                        target_here = true;
                    }
                }
                {
                    ObjectClass *target = (ObjectClass *)LinkedTo->unknown_494;
                    if (target != 0 && target->Kind_Of() == 6 && Map[to].unknown_4717b0() == target) {
                        target_here = true;
                    }
                }
            }
            CoordStruct old = unknown_28;
            unknown_28 = Map[coord].Closest_Free_Spot(coord, target_here, bridge);
            if (LinkedTo->unknown_slot101(&Map[Coord_Cell(unknown_28)], -1, -1, 0, true) != 0) {
                unknown_28 = unknown_coord_ac0280;
            }
            Map[old].Center_Coord();    // (the result is unused)
            if (unknown_28 == unknown_coord_ac0280) {
                AbstractClass *target = LinkedTo->unknown_494;
                if (target != 0 && target->AbstractFlags.IsObject) {
                    int zone = LinkedTo->unknown_slot32()->MovementZone;
                    Cell target_cell = Coord_Cell(target->unknown_slot19(0));
                    CellClass *cell = &Map[LinkedTo->unknown_slot19(0)];
                    bool alt = LinkedTo->unknown_slot46(0);
                    Cell found = Map.Unknown_005502E0(target_cell, LinkedTo->unknown_slot32()->SpeedType,
                        Map.Zone(cell->MapCoords, zone, alt), zone, Map[target_cell].IsUnderBridge,
                        Point2D(1, 1), 0, 1, 0, 1, Cell(0, 0), 0);
                    if (found != unknown_geometry_k) {
                        unknown_28 = Map[found].Closest_Free_Spot(Map[found].Center_Coord(), target_here, bridge);
                    }
                }
            }
        } else if (LinkedTo->unknown_210) {
            LinkedTo->unknown_slot58(unknown_28);
        } else {
            int zone = LinkedTo->unknown_slot32()->MovementZone;
            Cell cell = Coord_Cell(to);
            if (cell != unknown_geometry_k && LinkedTo->unknown_slot101(&Map[cell], -1, -1, 0, true) != 0) {
                int index = Map.Zone(cell, zone, bridge);
                cell = Map.Unknown_005502E0(cell, LinkedTo->unknown_slot32()->SpeedType, index, zone, bridge,
                    Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0);
            }
            if (cell != unknown_geometry_k) {
                LinkedTo->unknown_slot59(unknown_28);
                Cell center = Coord_Cell(Map[cell].Center_Coord());
                unknown_28 = CoordStruct(center.X * 256 + 128, center.Y * 256 + 128, 0);
                unknown_28.Z = Map.Unknown_0055A280(unknown_28);
                LinkedTo->unknown_slot58(unknown_28);
            }
        }
    } else {
        unknown_28 = to;
    }
    if (unknown_28 != unknown_coord_ac0280) {
        LinkedTo->unknown_slot58(unknown_28);
        return true;
    }
    LinkedTo->unknown_slot58(Object_Coord(LinkedTo));
    return false;
}
