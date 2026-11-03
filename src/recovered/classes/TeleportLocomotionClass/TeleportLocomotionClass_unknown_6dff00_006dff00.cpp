// bool TeleportLocomotionClass::unknown_6dff00(CoordStruct coord, bool arrive) (0x006DFF00)
// One warp step (Process). Before arriving (arrive false) the occupants of
// coord's cell (the bridge layer when the cell is a bridge) are dealt with:
// a matching infantry at the very coordinate, a FootClass occupant and,
// for an occupant slot 83 marks, the linked object itself are destroyed
// (C4Warhead); any other occupant or an unfit bridge blocks the cell. A
// blocked cell, or one whose overlay is not passable (+0x279), picks the
// nearest free cell (0x005502E0) and keeps the offset within it in the
// linked object's +0x21C; that returns false. Arriving lifts the object
// from its old place (slot 59), moves the arrival point to +0x21C on the
// ground or bridge, and places it there (slot 58). Otherwise the object
// is placed at the arrival point (or where it stands) and true returned.
// The overlap test passes CellClass::unknown_4788d0 without calling it:
// the original reads the function's address as the bool (always true).
#include "shared/teleport_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/rules.hpp"
#include "shared/techno_type.hpp"
#include "shared/overlay_view.hpp"
// @ref ?unknown_overlay_types_a35de8@@3V?$DynamicVectorClass@PAVUnknownOverlayType@@@@A=00a35de8
// @ref _unknown_geometry_j=00ac02a8
// @ref ?unknown_4788d0@CellClass@@QBEIXZ=004788d0
// @ref ?unknown_coord_ac0280@@3UCoordStruct@@A=00ac0280

// The object as a FootClass, or null (the cast idiom of BuildingTypeClass 0x00458B10).
inline FootClass *Foot_Of_6dff00(ObjectClass *object)
{
    bool foot;
    if (object) foot = object->AbstractFlags.IsFoot;
    if (!object || !foot) return 0;
    return static_cast<FootClass *>(object);
}

bool TeleportLocomotionClass::unknown_6dff00(CoordStruct coord, bool arrive)
{
    if (!arrive) {
        ObjectClass *object;
        if (Map[coord].unknown_140 & 0x100) {
            object = Map[coord].AltOccupierPtr;
        } else {
            object = Map[coord].OccupierPtr;
        }
        int overlay = Map[coord].OverlayIndex;
        bool blocked = false;
        for (; object != 0; object = object->unknown_30) {
            if (!object->unknown_slot83() && object->Kind_Of() == 15 && LinkedTo->Kind_Of() == 15) {
                if (coord == object->Center_Coord()) {
                    int damage = object->unknown_slot32()->MaxStrength;
                    object->unknown_slot86(&damage, 0, Rules->unknown_c74, 0, true, 0);
                }
            } else if (!object->unknown_slot83() && Foot_Of_6dff00(object) != 0) {
                int damage = object->unknown_slot32()->MaxStrength;
                object->unknown_slot86(&damage, 0, Rules->unknown_c74, 0, true, 0);
            } else if (object->unknown_slot83()) {
                int damage = LinkedTo->unknown_slot32()->MaxStrength;
                LinkedTo->unknown_slot86(&damage, 0, Rules->unknown_c74, 0, true, 0);
            } else if (Foot_Of_6dff00(object) == 0) {
                blocked = true;
            }
        }
        if ((Map[coord].unknown_140 & 0x100) && !(Map[coord].unknown_140 & 0x200)) {
            blocked = true;
        }
        CellClass *cell = &Map[Coord_Cell(LinkedTo->Center_Coord())];
        bool alt = cell->unknown_4788d0;
        if ((overlay != -1 && !unknown_overlay_types_a35de8[overlay]->unknown_279 && !alt) || blocked) {
            int zone = LinkedTo->unknown_slot32()->MovementZone;
            if (zone == 9) {
                zone = 0;
            } else if (zone == 2) {
                zone = 0;
            } else if (zone == 3) {
                zone = 5;
            }
            Cell found = Map.Unknown_005502E0(Coord_Cell(coord), 1, Map.Zone(cell->MapCoords, zone, alt), zone,
                Map[Coord_Cell(coord)].IsUnderBridge, Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0);
            CoordStruct offset = coord - Map[coord].Center_Coord();
            CoordStruct target = Map[found].Center_Coord() + offset;
            LinkedTo->unknown_21c = target;
            return false;
        }
    } else {
        if (unknown_28 != unknown_coord_ac0280) {
            LinkedTo->unknown_slot59(unknown_28);
        } else {
            LinkedTo->unknown_slot59(Object_Coord(LinkedTo));
        }
        unknown_28 = LinkedTo->unknown_21c;
        unknown_28.Z = Map.Unknown_0055A280(unknown_28);
        if ((Map[unknown_28].unknown_140 & 0x100) && !LinkedTo->unknown_79) {
            LinkedTo->unknown_79 = true;
            unknown_28.Z += unknown_geometry_j;
        } else {
            LinkedTo->unknown_79 = false;
        }
        LinkedTo->unknown_slot58(unknown_28);
    }
    if (unknown_28 != unknown_coord_ac0280) {
        LinkedTo->unknown_slot58(unknown_28);
    } else {
        LinkedTo->unknown_slot58(Object_Coord(LinkedTo));
    }
    return true;
}
