// int AircraftClass::unknown_slot28(ObjectClass *object, bool arg2) (0x004175A0)
// The action against an object (hypothesis: What_Action): the foot's
// answer, adjusted. An airport-bound aircraft does not use action 0x1A. A
// player's carryall picks up (0x11) an allied empty unit when not carrying,
// and otherwise asks slot 27 about the object's cell for action 0; entering
// (4) needs a passenger and firing (5) a primary weapon; a player's
// aircraft docks (3) at an airfield (the rules' +0x778 type) or helipad it
// is in radio contact with when the pad is empty and accepted (message 0xF). A
// carryall does not pick up from a weapons factory's cell; action 2 on a
// slot-48 object that is not owned and whose slot-50 type is 0x15 becomes
// 1; fire on an object whose type has +0x203 becomes 2.
#include "shared/aircraft.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/house.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/map_view.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_slot28@FootClass@@UAEHPAVObjectClass@@_N@Z=004cc740
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580
// @ref ?Unknown_00636ED0@RadioClass@@QBE_NPAVTechnoClass@@@Z=00636ed0
// @ref _unknown_geometry_k=0083c478
// @ref ?Unknown_004717B0@UnknownAircraftCell@@QAEPAUUnknownAircraftBuilding@@XZ=004717b0

// A building as read here (a view of BuildingClass).
struct UnknownAircraftBuilding {
    char unknown_000[0x418];
    BuildingTypeClass *Type;                    // +0x418
};
// A cell as read here (a view of CellClass).
class UnknownAircraftCell {
public:
    UnknownAircraftBuilding *Unknown_004717B0();    // 0x004717B0 (the building in the cell)
};

int AircraftClass::unknown_slot28(ObjectClass *object, bool arg2)
{
    int action = FootClass::unknown_slot28(object, arg2);
    if (action == 8) {
        return action;
    }
    if (action == 0x1A && Type->AirportBound) {
        action = 0;
    }
    if (Type->Carryall && House->Unknown_004F52B0()) {
        if (action == 7 || action == 0) {
            if (House->Is_Ally((TechnoClass *)object)) {
                bool active;
                if (object != 0) {
                    active = object->AbstractFlags.IsTechno;
                }
                if (object == 0 || !active || object->Owning_House()->Is_Ally(this)) {
                    if (Cargo.Object == 0 && object->Kind_Of() == 1) {
                        action = 0x11;
                        goto docking;
                    }
                }
            }
        } else {
            goto checks;
        }
    }
    if (action == 0) {
        Cell cell = Coord_Cell(object->Center_Coord());
        action = unknown_slot27(&cell, action != 0, arg2);
    }
checks:
    if (action == 4) {
        if (Cargo.Count == 0) {
            action = 0;
        }
    } else if (action == 5) {
        if (unknown_slot231(0)->WeaponType == 0) {
            action = 0;
        }
    }
docking:
    if (House->Unknown_004F52B0() && action == 7 && object->Kind_Of() == 6) {
        BuildingTypeClass *type = ((UnknownAircraftBuilding *)object)->Type;
        if ((type == Rules->unknown_778 || type->unknown_1365)
            && ((TechnoClass *)object)->Unknown_00636ED0(this) && ((TechnoClass *)object)->Cargo.Object == 0
            && unknown_slot150(0xF, (TechnoClass *)object) == 1) {
            action = 3;
        }
    }
    if (Type->Carryall && action == 0x11) {
        Cell cell = object->unknown_slot104();
        if (cell.X != unknown_geometry_k.X || cell.Y != unknown_geometry_k.Y) {
            UnknownAircraftBuilding *building = ((UnknownAircraftCell &)((UnknownPlacementCellView &)Map[cell])).Unknown_004717B0();
            if (building != 0 && building->Type->unknown_1357) {
                action = 0;
            }
        }
    } else if (action == 2) {
        if (object->unknown_slot48() && object->unknown_slot51(true) == 0 && object->unknown_slot50(true)->Kind_Of() == 0x15) {
            action = 1;
        }
    } else if (action == 5 && object->Class_Of()->unknown_203) {
        action = 2;
    }
    return action;
}
