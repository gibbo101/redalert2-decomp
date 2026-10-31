// void MapClass::Unknown_0055C520(CellClass *cellptr, int region_id, bool set_region) (0x0055C520)
// The map generator's water pruning (TibSun Prune_Water): a water tile (the 12 tiles from
// unknown_tileset_a52580) whose water mask (0x0055D410, control 2) is one of the eight
// lone-corner shapes loses its tile (+0x38 = 0xFFFF, +0x11A = 0); with set_region its
// generator record takes the region; each neighbour inside the generator's diagonal
// bounds has its record's water mask (+0x40) recomputed.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_region.hpp"
#include "shared/tileset_index.hpp"
// @ref ?Get_Cell_Data_0056dba0@@YIAAUUnknownMapGenerationCell@@ABVCell@@@Z=0056dba0
// @ref ?Unknown_0055D410@MapClass@@QAEHPAVCellClass@@H@Z=0055d410

// The generator record of a cell (TibSun MapRegionClass::Get_Cell_Data; __fastcall).
UnknownMapGenerationCell &__fastcall Get_Cell_Data_0056dba0(Cell const &cell);

// Whether a cell is inside the generator's diagonal map bounds (TibSun My_In_Radar).
inline bool My_In_Radar(Cell const &cell)
{
    int x = cell.X;
    int y = cell.Y;
    return (y + x > unknown_map_min_a70a1c &&
            x - y < unknown_map_min_a70a1c &&
            y - x < unknown_map_min_a70a1c &&
            y + x <= unknown_map_max_a70a20) ? true : false;
}

void MapClass::Unknown_0055C520(CellClass *cellptr, int region_id, bool set_region)
{
    int itype = cellptr->IsoTileIndex;
    if (itype >= unknown_tileset_a52580 && itype < unknown_tileset_a52580 + 12) {
        int mask = Unknown_0055D410(cellptr, 2);
        if (mask == 0xC7 || mask == 0x7C || mask == 0xF1 || mask == 0x1F ||
            mask == 0xC6 || mask == 0x6C || mask == 0xB1 || mask == 0x1B) {
            cellptr->IsoTileIndex = 0xFFFF;
            cellptr->unknown_11a = 0;
            if (set_region) {
                Get_Cell_Data_0056dba0(cellptr->MapCoords).RegionIndex = region_id;
            }
            for (int facing = 0; facing < 8; facing++) {
                CellClass *adjptr = &cellptr->Adjacent_Cell(facing);
                if (My_In_Radar(adjptr->Fetch_CellID())) {
                    UnknownMapGenerationCell &data = Get_Cell_Data_0056dba0(adjptr->Fetch_CellID());
                    data.unknown_40 = -1;
                    data.unknown_40 = Unknown_0055D410(adjptr, 2);
                }
            }
        }
    }
}
