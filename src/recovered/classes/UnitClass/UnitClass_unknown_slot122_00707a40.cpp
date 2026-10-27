// bool UnitClass::unknown_slot122() (0x00707A40, slot 122)
// Whether the unit may start its deploy state (hypothesis): never in
// missions 6/21 or with +0x5B9; while busy (moving, outside missions 5/1,
// or flagged +0xA4) only when queued for mission 7; the +0x2A8 state must
// be idle. A unit docked with a weapons factory may only while that
// factory queues mission 2 or 7; one standing on a weapons factory's cell
// may unless it is the cell just south of the factory's own.
#include "shared/unit.hpp"
#include "shared/building_type.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref __com_issue_error@4=00795940
// @ref ?unknown_496b50@UnknownTimed@@QBE_NXZ=00496b50
// @ref ?Contact_With_Whom@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e20
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0

// A building's type (a view until shared/building.hpp is installed: the
// type pointer follows TechnoClass at +0x418).
struct UnknownUnitBuildingView : TechnoClass {
    BuildingTypeClass *Type;                // +0x418
};

bool UnitClass::unknown_slot122()
{
    if (Mission == 6 || Mission == 21 || unknown_5b9) {
        return false;
    }
    if (MissionQueue != 7 && Locomotor.Checked()->Is_Moving_Now() && unknown_slot108() >= 0
        && unknown_slot91() != 5 && (unknown_slot91() != 1 || unknown_228) && !unknown_a4) {
        return false;
    }
    if (!unknown_2a8.unknown_496b50()) {
        return false;
    }
    TechnoClass *contact = Contact_With_Whom(0);
    if (contact) {
        if (contact->Kind_Of() == 6 && ((UnknownUnitBuildingView *)contact)->Type->WeaponsFactory
            && MissionQueue != 2 && MissionQueue != 7) {
            return false;
        }
    } else {
        CoordStruct coord = Coord;
        ObjectClass *building = ((CellClass *)&Map[coord])->unknown_4717b0();
        if (building && ((UnknownUnitBuildingView *)building)->Type->WeaponsFactory) {
            CoordStruct where = building->Coord;
            Cell factory = Coord_Cell(where);
            CoordStruct here = Coord;
            Cell cell = Coord_Cell(here);
            Cell delta(cell.X - factory.X, cell.Y - factory.Y);
            if (delta.X == 0 && delta.Y == 1) {
                return false;
            }
        }
    }
    return true;
}
