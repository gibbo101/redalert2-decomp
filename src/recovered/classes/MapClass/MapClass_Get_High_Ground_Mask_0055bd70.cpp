// unsigned int MapClass::Unknown_0055BD70(CellClass *cellptr) (0x0055BD70)
// The pattern of high ground around a cell (TibSun Get_High_Ground_Mask): for a cell inside
// the map whose generator record is in the fill area (+0x4A), the mask bit of every
// neighbour inside the map one level (4) above the cell (+0x11B) and not a cliff tile
// (0x0047B5E0); zero otherwise.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_region.hpp"
// @ref ?Get_Cell_Data_0056dba0@@YIAAUUnknownMapGenerationCell@@ABVCell@@@Z=0056dba0
// @ref ?unknown_47b5e0@CellClass@@QBE_NXZ=0047b5e0
// @ref ?Unknown_0054AAB0@MapClass@@QAE_NABVCell@@@Z=0054aab0

// The generator record of a cell (TibSun MapRegionClass::Get_Cell_Data; __fastcall).
UnknownMapGenerationCell &__fastcall Get_Cell_Data_0056dba0(Cell const &cell);

unsigned int MapClass::Unknown_0055BD70(CellClass *cellptr)
{
    int mask = 0;
    int height = cellptr->unknown_11b;
    Cell origin = cellptr->Fetch_CellID();

    if (!Map.Unknown_0054AAB0(origin) || !Get_Cell_Data_0056dba0(origin).unknown_45[5]) {
        return 0;
    }

    CellClass *cptr_ne = &Map[(Cell)(origin + Cell(1, -1))];
    CellClass *cptr_e = &Map[(Cell)(origin + Cell(1, 0))];
    CellClass *cptr_se = &Map[(Cell)(origin + Cell(1, 1))];
    CellClass *cptr_s = &Map[(Cell)(origin + Cell(0, 1))];
    CellClass *cptr_sw = &Map[(Cell)(origin + Cell(-1, 1))];
    CellClass *cptr_w = &Map[(Cell)(origin + Cell(-1, 0))];
    CellClass *cptr_nw = &Map[(Cell)(origin + Cell(-1, -1))];
    CellClass *cptr_n = &Map[(Cell)(origin + Cell(0, -1))];

    if (Map.Unknown_0054AAB0(origin + Cell(-1, -1)) && cptr_nw->unknown_11b == height + 4 && !cptr_nw->unknown_47b5e0()) {
        mask |= 0x40;
    }
    if (Map.Unknown_0054AAB0(origin + Cell(0, -1)) && cptr_n->unknown_11b == height + 4 && !cptr_n->unknown_47b5e0()) {
        mask |= 0x80;
    }
    if (Map.Unknown_0054AAB0(origin + Cell(1, -1)) && cptr_ne->unknown_11b == height + 4 && !cptr_ne->unknown_47b5e0()) {
        mask |= 0x01;
    }
    if (Map.Unknown_0054AAB0(origin + Cell(-1, 0)) && cptr_w->unknown_11b == height + 4 && !cptr_w->unknown_47b5e0()) {
        mask |= 0x20;
    }
    if (Map.Unknown_0054AAB0(origin + Cell(1, 0)) && cptr_e->unknown_11b == height + 4 && !cptr_e->unknown_47b5e0()) {
        mask |= 0x02;
    }
    if (Map.Unknown_0054AAB0(origin + Cell(-1, 1)) && cptr_sw->unknown_11b == height + 4 && !cptr_sw->unknown_47b5e0()) {
        mask |= 0x10;
    }
    if (Map.Unknown_0054AAB0(origin + Cell(0, 1)) && cptr_s->unknown_11b == height + 4 && !cptr_s->unknown_47b5e0()) {
        mask |= 0x08;
    }
    if (Map.Unknown_0054AAB0(origin + Cell(1, 1)) && cptr_se->unknown_11b == height + 4 && !cptr_se->unknown_47b5e0()) {
        mask |= 0x04;
    }
    return mask;
}
