// bool __fastcall unknown_undo_cell_open_6850b0(CellClass *cell) (0x006850B0)
// Whether the cell is inside the map diamond, has no overlay or occupier,
// is not marked in the map-generation grid and its tile type allows it
// (unknown_2b0; true without a valid tile type). flag is unused; every caller
// sets dl. The bounds test is the inline form of 0x0058DA10, which goes out of
// line one level down (0x00685600).
#include "shared/cell.hpp"
#include "shared/map_region.hpp"
#include "shared/isometric_tile.hpp"
#include "shared/isometric_tile_type.hpp"
// @ref ?unknown_map_min_a70a1c@@3HA=00a70a1c
// @ref ?unknown_map_max_a70a20@@3HA=00a70a20
// @ref ?Generation_Cell_In_Bounds_0058da10@@YI_NABVCell@@@Z=0058da10
// @ref ?IsoTileTypes@@3V?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@A=00a40cd0
// @ref ?unknown_generation_cell_56dba0@@YIPAUUnknownMapGenerationCell@@ABVCell@@@Z=0056dba0
UnknownMapGenerationCell *__fastcall unknown_generation_cell_56dba0(Cell const &cell);

inline bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &position)
{
    int x = position.X;
    int y = position.Y;
    if (y + x > unknown_map_min_a70a1c
        && x - y < unknown_map_min_a70a1c
        && y - x < unknown_map_min_a70a1c
        && y + x <= unknown_map_max_a70a20) {
        return true;
    }
    return false;
}

bool __fastcall unknown_undo_cell_open_6850b0(CellClass *cell, bool flag)
{
    if (Generation_Cell_In_Bounds_0058da10(cell->Fetch_CellID())
        && cell->OverlayIndex == -1
        && cell->OccupierPtr == 0) {
        if (!unknown_generation_cell_56dba0(cell->Fetch_CellID())->unknown_45[0]) {
            int tile = cell->IsoTileIndex;
            if (tile < IsoTileTypes.Count() && tile != 0xFFFF) {
                return IsoTileTypes[tile]->unknown_2b0;
            }
            return true;
        }
    }
    return false;
}
