// AircraftClass Receive_Message (slot 95, 0x00418840): the radio handler. Body 1186 bytes including the two-level switch tables; 14 nop pad bytes follow.

// Aircraft radio handler slot95,0x00418840. Full1186-byte body includes two-level70-byte switch data;14 frozen padding.
#include "shared/aircraft.hpp"
#include "shared/house.hpp"
#include "shared/infantry.hpp"
// @ref ?unknown_4198b0@AircraftClass@@QAEPAVAbstractClass@@XZ=004198b0
// @ref ?As_Techno@AbstractClass@@QAEPAVTechnoClass@@XZ=0040dc20
// Classify from the common RadioClass prefix before accessing Infantry-owned fields.
static inline InfantryClass *Aircraft_Radio_Infantry(RadioClass *radio)
{
    if (!radio) return 0;
    return radio->Kind_Of() == 15 ? (InfantryClass *)radio : 0;
}
static inline bool Aircraft_Accepts_Radio_00418840(int mission) { return mission != 4 && (mission <= 25 || mission > 27); }
static inline bool Aircraft_Radio_Target_Is_Current_Cell_00418840(AircraftClass *aircraft)
{
    AbstractClass *cell = aircraft->unknown_slot105();
    AbstractClass *target = aircraft->unknown_494;
    return target == cell;
}
int AircraftClass::unknown_slot95(RadioClass *radio, int message, long &param)
{
    if (!Aircraft_Accepts_Radio_00418840(Mission)) return 0;
    switch (message) {
    case 31: {
        AircraftTypeClass *type = Type;
        int current_ammo = unknown_254;
        int capacity = type->Ammo;
        if (current_ammo >= capacity / 2 && unknown_228) return 1;
        return FootClass::unknown_slot95(radio, message, param);
    }
    case 29: {
        if (unknown_228) return 10;
        AircraftTypeClass *type = Type;
        int current_ammo = unknown_254;
        int capacity = type->Ammo;
        return current_ammo == capacity ? 1 : 10;
    }
    case 33: {
        AircraftTypeClass *type = Type;
        int current_ammo = unknown_254;
        int capacity = type->Ammo;
        return current_ammo == capacity ? 1 : 10;
    }
    case 23:
        unknown_slot116(2, false);
        unknown_slot260(unknown_4198b0(), 1);
        unknown_slot149(3);
        break;
    case 18: {
        FootClass::unknown_slot95(radio, message, param);
        AbstractClass *destination = (AbstractClass *)param;
        if (destination && destination->Kind_Of() == 6) {
            if (unknown_slot150(15, destination->As_Techno()) != 1) return 10;
            unknown_slot116(7, false);
            unknown_slot260(destination, 1);
        } else {
            unknown_slot116(2, false);
            unknown_slot260(destination, 1);
        }
        unknown_slot117();
        return 1;
    }
    case 19:
        FootClass::unknown_slot95(radio, message, param);
        if (!Locomotor.Checked()->Is_Moving() || !unknown_494) return 1;
        if (Type->AirportBound && unknown_494->Kind_Of() == 11 && Aircraft_Radio_Target_Is_Current_Cell_00418840(this)) return 1;
        return 10;
    case 21: {
        AircraftTypeClass *type = Type;
        int count = Cargo.Count;
        int capacity = type->Passengers;
        if (count == capacity) unknown_2a8.unknown_496bc0(type->DeployTime);
        InfantryClass *infantry = Aircraft_Radio_Infantry(radio);
        if (infantry && infantry->Type->Civilian && !infantry->unknown_5c1) {
            unknown_slot220(0);
            unknown_slot260(0, 1);
            unknown_slot116(4, false);
        }
        return 5;
    }
    case 14: {
        int capacity = Type->Passengers;
        if (capacity > 0 && Cargo.Count < capacity) {
            FootClass::unknown_slot95(radio, message, param);
            if (!Locomotor.Checked()->Is_Moving()) {
                unknown_2a8.unknown_496b70(Type->DeployTime);
                if (unknown_slot150(19, (TechnoClass *)radio) == 1) {
                    param = (long)this;
                    if (unknown_slot151(18, (int *)&param, (TechnoClass *)radio) != 1) {
                        unknown_slot150(3, (TechnoClass *)radio);
                        return 1;
                    }
                    Contact(0)->unknown_slot81();
                }
            }
            return 1;
        }
        break;
    }
    case 15: {
        if (Type->Passengers == 0 || !radio || !House->Is_Ally((TechnoClass *)radio)) return 0;
        AircraftTypeClass *type = Type;
        int count = Cargo.Count;
        int capacity = type->Passengers;
        return count < capacity ? 1 : 10;
    }
    case 8:
        if (Type->Carryall && unknown_slot91() == 2 && unknown_370) {
            if ((Cargo.Object && Cargo.unknown_468a10() == radio) || unknown_494 == radio) return 10;
        }
        break;
    default:
        break;
    }
    return FootClass::unknown_slot95(radio, message, param);
}
