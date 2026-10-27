// int AircraftClass::unknown_slot129() (0x00419D00)
// The aircraft's guard mission (hypothesis: Mission_Guard); returns the
// delay until the next call. At flight level: a team member with a +0x494
// target attacks (mission 2) and waits the mission rate; without a weapon
// it lands at its cell (slot 260, mission 2); otherwise outside a team it
// returns (slot 261). Below it: a slot-163 aircraft low on ammunition (empty,
// below half or below full by the 0x0083C4D4/0x0083C4D5 settings) not in
// radio contact heads for the nearest dock (mission 7); one reloading at a
// reload building stays. A +0x228 object starts mission 1; idle aircraft
// return 0x2D; a computer house's aircraft picks a target near its
// coordinate (slot 220, mission 1); a player's aircraft not in slot 21
// waits the mission rate; otherwise the foot's guard.
#include "shared/aircraft.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref __real@8@4008e100000000000000=0079b608
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10
// @ref ?Contact@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e10
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?unknown_func_4eb360@HouseClass@@QAEPAVAbstractClass@@ABUCoordStruct@@@Z=004eb360
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_slot129@FootClass@@UAEHXZ=004c4660
// @ref ?unknown_flag_83c4d4@@3_NA=0083c4d4
// @ref ?unknown_flag_83c4d5@@3_NA=0083c4d5

// Rearming settings (0x0083C4D4: rearm only when empty; 0x0083C4D5: rearm
// below half; hypothesis).
extern bool unknown_flag_83c4d4;
extern bool unknown_flag_83c4d5;

// A reload building (a view of BuildingClass).
struct UnknownAircraftDock {
    char unknown_000[0x418];
    BuildingTypeClass *Type;                    // +0x418
};

int AircraftClass::unknown_slot129()
{
    int level = Type->Flight_Level();
    if (unknown_slot108() == level) {
        if (Team != 0) {
            if (unknown_494 != 0) {
                unknown_5bc = true;
                unknown_slot116(2, false);
            }
            return (int)(Control()->unknown_10 * 900.0);
        }
        if (unknown_slot231(0)->WeaponType == 0) {
            CoordStruct coord = Coord;
            unknown_slot260((AbstractClass *)&Map[coord], true);
            unknown_slot116(2, false);
            return 1;
        }
        if (Team == 0) {
            unknown_5bc = true;
            unknown_slot261(0, true);
        }
        return 1;
    }
    if (unknown_flag_83c4d4) {
        if (unknown_254 == 0 && unknown_slot163()) {
            goto rearm;
        }
    } else if (unknown_flag_83c4d5) {
        if (unknown_slot163() && unknown_254 < Type->Ammo / 2) {
            goto rearm;
        }
    } else {
        if (unknown_slot163() && unknown_254 < Type->Ammo) {
            goto rearm;
        }
    }
reloading:
    if (unknown_254 != -1 && unknown_254 < Type->Ammo / 2 && In_Radio_Contact()
        && Contact(0)->Kind_Of() == 6 && ((UnknownAircraftDock *)Contact(0))->Type->unknown_134a) {
        return 1;
    }
    if (unknown_228 != 0) {
        unknown_slot116(1, false);
        return 1;
    }
    if (!unknown_slot163()) {
        return 0x2D;
    }
    if (unknown_slot108() == 0 && !In_Radio_Contact()) {
        return 0x2D;
    }
    if (!House->Unknown_004F52F0()) {
        CoordStruct coord = Coord;
        AbstractClass *target = House->unknown_func_4eb360(coord);
        if (target != 0) {
            unknown_slot220(target);
            unknown_slot116(1, false);
        }
    }
    if (House->Unknown_004F52F0() && !unknown_slot21()) {
        int delay = (int)(Control()->unknown_10 * 900.0);
        return delay + unknown_id_source_a3d290->Random()(0, 2);
    }
    return FootClass::unknown_slot129();
rearm:
    if (!In_Radio_Contact()) {
        TechnoClass *dock = unknown_slot299((DynamicVectorClass<TechnoTypeClass *> const *)&Type->Dock, 0, 0);
        if (dock != 0) {
            unknown_slot116(7, false);
            unknown_slot260(dock, true);
            unknown_slot220(0);
            return 1;
        }
    }
    goto reloading;
}
