// Remove both directions of a zone connection and its two bridge-side pairs, original00566C30.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/cell_subzone.hpp"
#include "shared/tileset_index.hpp"
extern int unknown_bridge_side_facings_7e0454[];
// @ref ?unknown_bridge_side_facings_7e0454@@3PAHA=007e0454
// @ref ?Delete@?$DynamicVectorClass@USubzoneConnectionStruct@@@@QAE_NH@Z=0056b070

void MapClass::Unknown_00566C30(ZoneConnectionClass *connection)
{
    short to_id;
    Cell from = connection->From;
    Cell to = connection->To;
    CellClass *from_cell = &Map[from];
    Cell none = unknown_cell_a6f238;
    Cell from_side1 = none;
    Cell from_side2 = none;
    Cell to_side1 = none;
    Cell to_side2 = none;
    if (from_cell->unknown_47b960() || from_cell->unknown_47b980()) {
        bool is_bridge = from_cell->unknown_47b960();
        int tile_set = unknown_tileset_a52c74;
        int tile;
        if (!is_bridge) { tile = from_cell->IsoTileIndex; tile_set = unknown_tileset_a6cb68; }
        else tile = from_cell->IsoTileIndex;
        int facing = unknown_bridge_side_facings_7e0454[tile - tile_set];
        from_side1 = Adjacent_Cell(from, facing);
        from_side2 = Adjacent_Cell(from, (facing - 4) & 7);
        to_side1 = Adjacent_Cell(to, facing);
        to_side2 = Adjacent_Cell(to, (facing - 4) & 7);
    }
    for (int layer = 0; layer < 3; ++layer) {
        {
            int from_id = ((CellSubzoneStruct *)&Fine_Subzone(from))->SubzoneID[layer];
            to_id = ((CellSubzoneStruct *)&Fine_Subzone(to))->SubzoneID[layer];
            SubzoneTracking[layer][from_id].Connections.Delete(SubzoneConnectionStruct(to_id, false));
            SubzoneTracking[layer][to_id].Connections.Delete(SubzoneConnectionStruct(from_id, false));
        }
        {
            int from_id = ((CellSubzoneStruct *)&Fine_Subzone(from_side1))->SubzoneID[layer];
            to_id = ((CellSubzoneStruct *)&Fine_Subzone(to_side1))->SubzoneID[layer];
            SubzoneTracking[layer][from_id].Connections.Delete(SubzoneConnectionStruct(to_id, false));
            SubzoneTracking[layer][to_id].Connections.Delete(SubzoneConnectionStruct(from_id, false));
        }
        {
            int from_id = ((CellSubzoneStruct *)&Fine_Subzone(from_side2))->SubzoneID[layer];
            to_id = ((CellSubzoneStruct *)&Fine_Subzone(to_side2))->SubzoneID[layer];
            SubzoneTracking[layer][from_id].Connections.Delete(SubzoneConnectionStruct(to_id, false));
            SubzoneTracking[layer][to_id].Connections.Delete(SubzoneConnectionStruct(from_id, false));
        }
    }
}
