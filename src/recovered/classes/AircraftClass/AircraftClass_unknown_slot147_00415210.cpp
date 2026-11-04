// int AircraftClass::unknown_slot147() (0x00415210, slot 147; paradrop overfly
// mission hypothesis). Out of range of the target (Rules +0x468): queue mission
// 26 while +0x5BB is positive, else retreat (mission 4). In range: drop over a
// map cell that passes 0x0055A7F0. Without target or cargo: retreat. Always 5.
// The in-range retreat is written out again in the out-of-range branch; VC6
// merges the two identical copies (the registers only rotate as in the original
// with both statements present).
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Planar_Distance@ObjectClass@@QBEHPBVAbstractClass@@@Z=005d4ce0
// @ref ?Unknown_0055A7F0@MapClass@@QAE_NABUCoordStruct@@@Z=0055a7f0
// @ref ?unknown_415510@AircraftClass@@QAEHXZ=00415510

int AircraftClass::unknown_slot147()
{
    enum { RetreatMission = 4, ParadropApproachMission = 26 };
    AbstractClass *target = unknown_228;
    unknown_5ba = true;
    if (target && Cargo.Object) {
        if (Planar_Distance(target) > Rules->unknown_468) {
            signed char queue_state = unknown_5bb;
            unknown_5ba = false;
            if (queue_state > 0) {
                unknown_slot116(ParadropApproachMission, false);
                return 5;
            }
            unknown_slot220(0);
            unknown_slot260(0, 1);
            unknown_slot116(RetreatMission, false);
            return 5;
        } else {
            CoordStruct location = Coord;
            if (Map.Unknown_0055A7F0(location)) unknown_415510();
            return 5;
        }
    } else {
        unknown_5ba = false;
    }
    unknown_slot220(0);
    unknown_slot260(0, 1);
    unknown_slot116(RetreatMission, false);
    return 5;
}
