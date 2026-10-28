// int AircraftClass::unknown_slot138() (0x004193D0, slot 138): the Enter
// mission (MissionClass slot 138 is mission 7's handler). Status +0xA8 steps
// 6 (wait for radio contact with the destination) -> 7 (closing in: nudge
// the position up to 5 leptons per frame toward the docking coordinate,
// then ask the contact (slot 149, message 21) and, as a carryall, hand the
// passenger over). Body 1248 bytes: the code plus its jump table
// (0x00419890-0x004198AF).
#include "shared/aircraft.hpp"
// @ref ?unknown_416420@AircraftClass@@QAEXXZ=00416420
// @ref ?unknown_4198b0@AircraftClass@@QAEPAVAbstractClass@@XZ=004198b0
// @ref ?Unknown_004717B0@CellClass@@QAEPAVBuildingClass@@XZ=004717b0
// @ref ?unknown_6d8080@TechnoClass@@QAE_NXZ=006d8080
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10
// @ref ?Contact@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e10
// @ref ?unknown_4689f0@UnknownCargo@@QAEPAVObjectClass@@XZ=004689f0
// @ref ?Unknown_00468960@UnknownCargo@@QAEXPAVFootClass@@@Z=00468960
// The destination as a building (it may also be a cell).
static inline BuildingClass *Building_Destination(AbstractClass *target)
{
    if (!target) return 0;
    return target->Kind_Of() == 6 ? (BuildingClass *)target : 0;
}

int AircraftClass::unknown_slot138()
{
    enum { MoveMission = 2, GuardMission = 5 };
    if (unknown_slot108() == 0 && Type->AirportBound && unknown_494) {
        if (unknown_494 != ((CellClass *)unknown_slot105())->Unknown_004717B0()) {
            unknown_5b4 = Building_Destination(unknown_494);
            unknown_slot149(3);
            unknown_slot116(2, true);
            return 1;
        }
    }
    if (unknown_slot108() > 0) {
        AbstractClass *target = unknown_494;
        TechnoClass *previous = unknown_5b4;
        if (previous != target && target && target->Kind_Of() == 6)
            unknown_5b4 = Building_Destination(unknown_494);
    }
    if (!unknown_494 && unknown_slot29() != 2 && unknown_slot149(14) != 1 && !unknown_6d8080()) {
        unknown_slot261(false, true);
        return 1;
    }
    switch (unknown_a8) {
    case 0:
        unknown_a8 = 6;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        unknown_5bc = true;
        return 1;
    case 6:
        if (Type->AirportBound && unknown_slot108() != 0) unknown_slot149(14);
        if (!In_Radio_Contact()) {
            if (!unknown_6d8080()) {
                if (Locomotor.Checked()->Get_Status() == 1) {
                    unknown_a8 = 7;
                    unknown_5bc = true;
                }
                if (MissionQueue == -1) {
                    unknown_slot260(0, 1);
                    unknown_slot261(false, true);
                    unknown_5bc = true;
                    return 1;
                }
                unknown_5bc = true;
            }
            unknown_5bc = true;
            return 1;
        }
        if (Locomotor.Checked()->Get_Status() == 1 || (Type->AirportBound && unknown_slot108() == 0)) {
            unknown_a8 = 7;
            unknown_5bc = false;
        }
        return 3;
    case 7:
        if (Locomotor.Checked()->Get_Status() == 1) {
            AbstractClass *target = unknown_494;
            if (target) {
                CoordStruct destination = target->Kind_Of() == 6
                    ? ((ObjectClass *)target)->unknown_slot41((int)this)
                    : unknown_494->Center_Coord();
                CoordStruct current = Coord;
                int dx = destination.X - current.X;
                int dy = destination.Y - current.Y;
                if (dx > 0) {
                    if (dx > 5) dx = 5;
                } else if (dx < -5) dx = -5;
                if (dy > 0) {
                    if (dy > 5) dy = 5;
                } else if (dy < -5) dy = -5;
                current.X += dx;
                current.Y += dy;
                unknown_slot103(current);
            }
            unknown_5bc = true;
            return 1;
        }
        unknown_5bc = true;
        switch (unknown_slot149(21)) {
        default:
            unknown_slot261(false, true);
            return 1;
        case 5:
            unknown_slot52();
            Contact(0)->Cargo.Unknown_00468960(this);
            return 1;
        case 1:
            break;
        }
        if (Type->Carryall && Cargo.Object) {
            TechnoClass *contact = Contact(0);
            FootClass *passenger = (FootClass *)Cargo.unknown_4689f0();
            unknown_slot149(3);
            if (passenger->unknown_slot150(2, contact) == 1) {
                Cargo.Unknown_00468960(passenger);
                unknown_slot71(0);
                unknown_416420();
                unknown_slot71(1);
            } else {
                unknown_slot260(unknown_4198b0(), 1);
            }
            unknown_slot116(MoveMission, false);
        } else {
            unknown_slot116(GuardMission, false);
        }
        return 1;
    }
    return 1;
}


