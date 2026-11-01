// bool WalkLocomotionClass::Mark_Head_To(CoordStruct const &coord) (0x0071F590; TibSun walk.cpp Mark_Head_To)
// Releases the old head-to mark, claims the free spot nearest coord (any spot when the
// navigation target is the unit, aircraft or building at coord; the bridge spot when
// the object is well above the ground of an under-bridge cell) and marks it, or the
// object's own spot. True when a head-to coordinate was taken.
#include "shared/walk_locomotion.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_coord_af9060@@3UCoordStruct@@A=00af9060

bool WalkLocomotionClass::Mark_Head_To(CoordStruct const &coord)
{
    if (unknown_28 != unknown_coord_af9060) {
        LinkedTo->unknown_slot59(unknown_28);
    } else {
        LinkedTo->unknown_slot59(Object_Coord(LinkedTo));
    }

    CoordStruct crd = coord;
    bool any_spot = false;

    if (coord != unknown_coord_af9060) {
        if (LinkedTo->unknown_slot91() == 8 || LinkedTo->unknown_slot91() == 9 || LinkedTo->unknown_slot91() == 7
            || LinkedTo->unknown_slot91() == 11 || LinkedTo->unknown_slot91() == 25) {
            ObjectClass *unit = (ObjectClass *)LinkedTo->unknown_494;
            if (unit != 0 && unit->Kind_Of() == 1 && unit->unknown_slot104() == coord.As_Cell()) {
                any_spot = true;
            }
            ObjectClass *aircraft = (ObjectClass *)LinkedTo->unknown_494;
            if (aircraft != 0 && aircraft->Kind_Of() == 2 && aircraft->unknown_slot104() == coord.As_Cell()) {
                any_spot = true;
            }
            ObjectClass *building = (ObjectClass *)LinkedTo->unknown_494;
            if (building != 0 && building->Kind_Of() == 6 && Map[coord].unknown_4717b0() == building) {
                any_spot = true;
            }
        }

        bool isbridge = Map[crd].IsUnderBridge && Object_Coord(LinkedTo).Z > unknown_geometry_g * 3 + Map.Unknown_0055A280(crd);
        unknown_28 = Map[crd].Closest_Free_Spot(crd, any_spot, isbridge);

        if (!Map[unknown_28].unknown_476cc0(LinkedTo) && !LinkedTo->unknown_76) {
            unknown_28 = unknown_coord_af9060;
            if (!LinkedTo->unknown_7d) {
                return false;
            }
        }
    } else {
        unknown_28 = coord;
    }

    if (unknown_28 != unknown_coord_af9060) {
        LinkedTo->unknown_slot58(unknown_28);
        return true;
    }

    LinkedTo->unknown_slot58(Object_Coord(LinkedTo));
    return false;
}
