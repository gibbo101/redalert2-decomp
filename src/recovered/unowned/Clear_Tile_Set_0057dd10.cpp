#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_tileset_a6cb74@@3HA=00a6cb74
// Original set name is unknown; this clears its42 tile indices and Cell+11A.
void __fastcall Clear_Tile_Set_0057dd10()
{
    Map.Unknown_0055A550();
    CellClass *cell=Map.Unknown_0055A490();
    while(cell) {
        if(cell->IsoTileIndex>=unknown_tileset_a6cb74 && cell->IsoTileIndex<unknown_tileset_a6cb74+42) {
            cell->IsoTileIndex=0;
            cell->unknown_11a=0;
        }
        cell=Map.Unknown_0055A490();
    }
}
