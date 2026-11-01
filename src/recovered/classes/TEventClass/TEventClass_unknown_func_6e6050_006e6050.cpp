// bool TEventClass::unknown_func_6e6050(int event, HouseClass *house, ObjectClass *object,
//     CDTimerClass<FrameTimerClass> *timer, bool *tripped, int source) (0x006E6050)
// TS's TEventClass::operator(): whether this event is satisfied for event (time,
// global/local variable and mission-timer events first, then the events the caller
// reports, then the house and owner tests). Is_Time_Based 0x006E6CF0 inlines here.
#include "shared/object.hpp"
#include "shared/object_type.hpp"
#include "shared/house.hpp"
#include "shared/team.hpp"
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/id_source.hpp"
#include "shared/coord_distance.hpp"
// @ref ?unknown_func_491d10@UnknownHouseCounter@@QAEHH@Z=00491d10

bool TEventClass::unknown_func_6e6050(int event, HouseClass *house, ObjectClass *object,
                                      CDTimerClass<FrameTimerClass> *timer, bool *tripped, int source)
{
    switch (Type) {
    case 0x2D:
        return unknown_id_source_a3d290->unknown_22ac <= Data;
    case 0x2E:
        return unknown_id_source_a3d290->unknown_22ac >= Data;
    case 0x2F:
        if (Data > Frame / 15) {
            return false;
        } else {
            return true;
        }
    case 0x1B: {
        bool value;
        unknown_id_source_a3d290->Get_Global_Variable(Data, &value);
        return value;
    }
    case 0x1C: {
        bool value;
        unknown_id_source_a3d290->Get_Global_Variable(Data, &value);
        return !value;
    }
    case 0x24: {
        bool value;
        unknown_id_source_a3d290->Get_Local_Variable(Data, &value);
        return value;
    }
    case 0x25: {
        bool value;
        unknown_id_source_a3d290->Get_Local_Variable(Data, &value);
        return !value;
    }
    case 0x0E:
        if (!unknown_id_source_a3d290->MissionTimer.Is_Active() || unknown_id_source_a3d290->MissionTimer != 0) return false;
        return true;
    case 0x0D:
    case 0x33:
        if (*timer != 0) return false;
        return true;
    }

    if (Type == 0) {
        return false;
    }

    if (Type != 0x2C &&
        Type != 1 &&
        Type != 0x19 &&
        Type != 0x1A &&
        Type != 0x22 &&
        Type != 0x18 &&
        Type != 0x13 &&
        Type != 0x14 &&
        Type != 0x15 &&
        Type != 0x16 &&
        Type != 0x35 &&
        Type != 0x36 &&
        unknown_func_6e6cf0()) {
        if (event != Type || unknown_flag_a40d13) {
            return false;
        }
    }

    if (Type == 1 || Type == 0x19 || Type == 0x1A || Type == 0x18) {
        if (event != Type) return false;
        if (Data != -1 && HouseClass::As_Pointer(Data) == 0) return false;
        if (!object || (Data != -1 && object->Owner() != HouseClass::As_Pointer(Data)->ArrayIndex)) return false;
        *tripped = true;
        return true;
    } else if (Type == 0x35) {
        if (event != Type) return false;
        if (!object || Data == -1 || HouseClass::As_Pointer(Data) == 0) return false;
        if (!object->unknown_slot51(true)) return false;
        if (object->unknown_slot51(true)->ArrayIndex != HouseClass::As_Pointer(Data)->ArrayIndex) return false;
        *tripped = true;
        return true;
    } else if (Type == 0x36) {
        if (event != Type) return false;
        if (!object) return false;
        ObjectTypeClass *type = object->unknown_slot50(true);
        if (type->Kind_Of() != 0x10 || Data == -1 || type->unknown_slot16() != Data) return false;
        *tripped = true;
        return true;
    } else if (Type == 0x22) {
        if (event != Type) return false;
        CoordStruct waypoint = unknown_id_source_a3d290->Waypoint_Coord(Data);
        if (Coord_Distance(object->Center_Coord(), waypoint) > 0x500) {
            return false;
        }
        return true;
    } else if (Type == 0x2C) {
        if (event != Type) return false;
        // source is the attacking TechnoClass (TS: TechnoClass *source; the int parameter is the old hypothesis).
        if (source == 0 || Data != ((TechnoClass *)source)->House->ArrayIndex) {
            return false;
        }
    }

    int index;
    if (house != 0) {
        switch (Type) {
        case 0x17:
            for (index = 0; index < Teams.Count(); index++) {
                TeamClass *ptr = Teams[index];
                if (ptr->Class == (TeamTypeClass *)unknown_30 && ptr->Member == 0 && ptr->TargetNotAssigned) {
                    *tripped = true;
                    break;
                }
            }
            if (index == Teams.Count()) return false;
            break;
        case 0x0C:
            if (house->Available_Money() < Data) return false;
            break;
        case 0x34:
            if (house->Available_Money() > Data) return false;
            break;
        case 0x11:
            if (house->CurBuildings > 0) {
                for (int index = 0; index < house->Buildings.Count(); index++) {
                    BuildingClass *ptr = house->Buildings[index];
                    if (ptr != 0 && !ptr->unknown_76 && ptr->Type->Factory != 0) {
                        return false;
                    }
                }
            }
            break;
        case 0x12:
            if (!house->unknown_141) return false;
            break;
        case 0x20:
            if (house->unknown_5460.unknown_func_491d10(Data) == 0) return false;
            *tripped = true;
            break;
        case 0x39:
            if (house->unknown_5460.unknown_func_491d10(Data) != 0) return false;
            *tripped = true;
            break;
        case 0x13:
            if (house->unknown_1b4 != Data) return false;
            *tripped = true;
            break;
        case 0x14:
            if (house->unknown_1bc != Data) return false;
            *tripped = true;
            break;
        case 0x15:
            if (house->unknown_1b8 != Data) return false;
            *tripped = true;
            break;
        case 0x16:
            if (house->unknown_1c0 != Data) return false;
            *tripped = true;
            break;
        case 0x0F:
            if (house->unknown_53b4 < Data) return false;
            break;
        case 0x10:
            if (house->unknown_5360 < Data) return false;
            break;
        default:
            break;
        }
    }

    house = HouseClass::As_Pointer(Data);
    if (house != 0) {
        switch (Type) {
        case 0x1E:
            if (house->Power_Fraction() >= 1) return false;
            break;
        case 0x03:
            if (!house->unknown_18b) return false;
            break;
        case 0x05:
            if (!house->unknown_13c) return false;
            break;
        case 0x0A:
            if (house->CurBuildings > 0) return false;
            break;
        case 0x09:
            if (house->unknown_228 > 0 || house->unknown_234 > 0) return false;
            break;
        case 0x37:
            if (house->unknown_22c > 0) return false;
            break;
        case 0x38:
            if (house->unknown_228 - house->unknown_22c > 0) return false;
            if (house->unknown_234 > 0) return false;
            break;
        case 0x0B:
            if (house->CurBuildings > 0 || house->unknown_228 > 0 || house->unknown_234 > 0) return false;
            break;
        default:
            break;
        }
    }
    return true;
}
