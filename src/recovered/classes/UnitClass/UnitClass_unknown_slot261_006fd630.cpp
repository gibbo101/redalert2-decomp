// bool UnitClass::unknown_slot261(bool arg1, bool arg2) (0x006FD630, slot 261)
// Choosing the idle mission (hypothesis: Westwood's Enter_Idle_Mode; arg1
// initial). After the foot step: a unit with a destination moves (2);
// harvesters and weeders harvest (10) unless in radio contact, already
// harvesting, or, for a computer house, off their land type (5); armed
// units guard (5), or hunt/area-guard (11) when their house is below the
// rules' +0x10A8 and they lack ability 16 and DefaultToGuardArea; units
// with passengers to drop unload (16). The mission is queued unless the
// unit is in mission 25, 11 or 16.
#include "shared/unit.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_slot261@FootClass@@UAE_N_N0@Z=004c6f10
// @ref ?unknown_4c8b00@FootClass@@QAEXXZ=004c8b00
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_6d7910@TechnoClass@@QAE_NH@Z=006d7910
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0

// The center of a cell (an inline helper taking a reference; hypothesis).
static inline CoordStruct Cell_Center_Of(Cell const &cell)
{
    return CoordStruct(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
}

bool UnitClass::unknown_slot261(bool arg1, bool arg2)
{
    bool result = FootClass::unknown_slot261(arg1, arg2);
    if (unknown_slot270() || unknown_slot91() == 28) {
        return result;
    }
    if (unknown_slot91() == 2 && !unknown_494) {
        CoordStruct center = Cell_Center_Of(unknown_slot104());
        CoordStruct coord = Coord;
        if (coord.X == center.X && coord.Y == center.Y && coord.Z == center.Z) {
            unknown_slot149(3);
        }
    }
    unknown_4c8b00();
    int mission;
    if (unknown_494) {
        mission = 2;
        goto queue;
    }
    if (!Type->Harvester && !Type->Weeder) {
        if (!unknown_slot163()) {
            if (unknown_32c && Type->Passengers > 0 && Cargo.Object && !Team) {
                mission = 16;
                goto queue;
            }
            if (unknown_57c) {
                goto done;
            }
            if (Mission == 16 && Type->DeploysInto) {
                goto done;
            }
            if (Mission == 11) {
                goto done;
            }
            goto guard;
        }
        if (unknown_slot91() == 5 || unknown_slot91() == 11) {
            return result;
        }
        if (unknown_slot91() != -1 && (Control()->unknown_07 || Control()->unknown_05)) {
            return result;
        }
        if (!(House->unknown_194 >= Rules->unknown_10a8 || unknown_6d7910(16) || Type->DefaultToGuardArea)
            || Team) {
            mission = 5;
        } else {
            mission = 11;
        }
        goto queue;
    }
    if (In_Radio_Contact()) {
        return result;
    }
    if (unknown_slot91() == 10 || MissionQueue == 10) {
        return result;
    }
    mission = 10;
    if (arg1 || !House->Unknown_004F52F0()) {
        goto stop;
    }
    {
        CoordStruct coord = Coord;
        int land = Map[coord].unknown_ec;
        if (land == (Type->Harvester ? 5 : 11)) {
            goto stop;
        }
    }
guard:
    mission = 5;
stop:
    unknown_slot220(0);
    unknown_slot260(0, 1);
queue:
    if (Mission != 25 && Mission != 11 && Mission != 16) {
        unknown_slot116(mission, false);
    }
done:
    return result;
}
