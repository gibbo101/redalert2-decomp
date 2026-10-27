// void AircraftClass::unknown_slot70(bool arg1, bool arg2) (0x0041A530, slot 70)
// Reveals the map around the aircraft for its house: with the type's Sight
// (1 on the ground, slot 108 0) passing arg1/arg2, twice (last argument 0
// and 1). Airborne without Sight: in scenarios with flag 0x1000, with the
// rules range (+0xEC), flagging whether it flies below half the rules
// flight level.
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

void AircraftClass::unknown_slot70(bool arg1, bool arg2)
{
    CoordStruct coord;
    int sight = Type->Sight;
    if (unknown_slot108() == 0) {
        sight = 1;
    }
    if (sight != 0) {
        coord = Coord;
        Map.Sight_From(coord, sight, House, arg1, arg2, 0, 1, 0);
        coord = Coord;
        Map.Sight_From(coord, sight, House, arg1, arg2, 0, 1, 1);
    } else if (unknown_id_source_a3d290->unknown_000 & 0x1000) {
        sight = Rules->unknown_ec;
        coord = Coord;
        Map.Sight_From(coord, sight, House, 0, 0, 1, unknown_slot108() < Rules->unknown_6dc / 2, 0);
        coord = Coord;
        Map.Sight_From(coord, sight, House, 0, 0, 1, unknown_slot108() < Rules->unknown_6dc / 2, 1);
    }
}
