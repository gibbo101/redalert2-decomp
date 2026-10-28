#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/isometric_tile.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?IsoTileTypes@@=00a40cd0
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?unknown_map_cells_a70a24@@=00a70a24
// @ref ?unknown_map_cell_side_84e804@@=0084e804
// @ref ?Generation_Cell_In_Bounds_0058da10@@=0058da10
// Unchanged real existing original helper; natural standalone copy receives zero credit.
#include "shared/coord.hpp"
extern int unknown_map_min_a70a1c,unknown_map_max_a70a20;
// @ref ?unknown_map_min_a70a1c@@3HA=00a70a1c
// @ref ?unknown_map_max_a70a20@@3HA=00a70a20
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &cell);

// Name/free fastcall/void intent are hypotheses, original ECX index/EDX Cell address.
void __fastcall Erase_Tile_Footprint_00589670(int tile,Cell const &position)
{
    IsometricTileTypeClass *type=IsoTileTypes[tile];
    IsoTileImageStruct const *image=(IsoTileImageStruct const *)type->unknown_slot39();
    if(image) {
        for(int y=0;y<type->unknown_2b8;y++) {
            for(int x=0;x<type->unknown_2b4;x++) {
                Cell where=position+Cell(x,y);
                if((int)where.Y+(int)where.X>unknown_map_min_a70a1c &&
                   (int)where.X-(int)where.Y<unknown_map_min_a70a1c &&
                   (int)where.Y-(int)where.X<unknown_map_min_a70a1c &&
                   (int)where.Y+(int)where.X<=unknown_map_max_a70a20) {
                    CellClass &cell=Map[where];
                    if(image->Tiles[(int)((unsigned)type->unknown_2b4*(unsigned)y+(unsigned)x)]!=0) {
                        cell.IsoTileIndex=0xffff;
                        cell.unknown_11a=0;
                    }
                }
            }
        }
    }
}
