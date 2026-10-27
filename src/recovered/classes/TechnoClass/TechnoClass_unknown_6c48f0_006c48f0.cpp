// int TechnoClass::unknown_6c48f0(ObjectClass *other) (0x006C48F0)
// The distance to the other object when its height is measured like
// 0x006C4A70: the horizontal part (levels above, scaled and limited, in
// leptons) and the vertical part (the same levels times the geometry
// constant 0x00AC01C0) combined; 0 unless both are on the map (slot 20).
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_0047CF10@UnknownCellClass@@QBEHXZ=0047cf10
// @ref _unknown_geometry_g=00ac01c0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __ftol=0077f110

int TechnoClass::unknown_6c48f0(ObjectClass *other)
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
        int vertical = unknown_geometry_g * rise;
        int horizontal = (int)scaled << 8;
        return (int)unknown_sqrt_4ba410((double)(horizontal * horizontal + vertical * vertical));
    }
    return 0;
}
