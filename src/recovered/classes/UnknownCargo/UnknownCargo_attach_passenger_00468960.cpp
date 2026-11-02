// void UnknownCargo::Unknown_00468960(FootClass *passenger) (0x00468960)
// Adds a passenger to the hold (TibSun CargoClass::Attach): the passenger
// leaves the map, any foot objects already chained to it are kept in front of
// the old hold, and the count is recomputed along the foot chain.
#include "shared/foot.hpp"

// TibSun's Is_Foot() test of a link that may be null (VC6_MATCHING_NOTES
// Cell351: the flag byte is spilled once).
inline bool Cargo_Is_Foot(ObjectClass const *object)
{
    bool is_foot;
    if (object != 0) is_foot = object->unknown_14_bit2;
    return object != 0 && is_foot;
}

void UnknownCargo::Unknown_00468960(FootClass *passenger)
{
    if (passenger == 0) return;

    passenger->unknown_slot52();

    ObjectClass *o = 0;
    if (passenger->unknown_30 && Cargo_Is_Foot(passenger->unknown_30)) {
        o = passenger->unknown_30;
        while (o != 0) {
            if (o->unknown_30 == 0) break;
            if (!Cargo_Is_Foot(o->unknown_30)) {
                o = 0;
                break;
            }
            o = o->unknown_30;
            if (o == 0) break;
        }
    }
    if (o != 0) {
        o->unknown_30 = Object;
    } else {
        passenger->unknown_30 = Object;
    }

    Object = passenger;
    Count = 0;
    passenger = (FootClass *)Object;
    while (passenger != 0) {
        Count++;
        if (passenger->unknown_30 == 0) break;
        if (!Cargo_Is_Foot(passenger->unknown_30)) break;
        passenger = (FootClass *)passenger->unknown_30;
    }
}
