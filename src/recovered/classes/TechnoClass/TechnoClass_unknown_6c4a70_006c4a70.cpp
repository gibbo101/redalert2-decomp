// int TechnoClass::unknown_6c4a70(ObjectClass *other) (0x006C4A70)
// How high this object's cell stands above the other's (levels, never
// negative), divided by the rules' +0x1480, scaled by +0x1488 and limited
// to +0x1490, in leptons (<< 8); 0 unless both are on the map (slot 20).
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_0047CF10@UnknownCellClass@@QBEHXZ=0047cf10
// @ref __ftol=0077f110

int TechnoClass::unknown_6c4a70(ObjectClass *other)
{
    if (unknown_slot20() && other->unknown_slot20()) {
        Cell here = Coord_Cell(Center_Coord());
        Cell there = Coord_Cell(other->Center_Coord());
        UnknownCellClass *source = (UnknownCellClass *)&Map[here];
        UnknownCellClass *target = (UnknownCellClass *)&Map[there];
        int rise;
        if (source->Unknown_0047CF10() - target->Unknown_0047CF10() < 0) {
            rise = 0;
        } else {
            rise = source->Unknown_0047CF10() - target->Unknown_0047CF10();
        }
        double scaled = rise / Rules->unknown_1480 * Rules->unknown_1488;
        double limit = Rules->unknown_1490;
        if (scaled >= limit) {
            scaled = Rules->unknown_1490;
        }
        return (int)scaled << 8;
    }
    return 0;
}
