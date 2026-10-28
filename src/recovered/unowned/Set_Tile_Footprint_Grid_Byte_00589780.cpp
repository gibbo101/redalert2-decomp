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
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &position);
// Original field semantics unknown: byte46 is existing grid unknown_45[1], not a new layout.
void __fastcall Set_Tile_Footprint_Grid_Byte_00589780(int tile,Cell const &position,unsigned char value)
{
    IsometricTileTypeClass *type=IsoTileTypes[tile];
    IsoTileImageStruct const *image=(IsoTileImageStruct const *)type->unknown_slot39();
    if(image) {
        for(int y=0;y<type->unknown_2b8;y++) {
            for(int x=0;x<type->unknown_2b4;x++) {
                Cell where;
                where.X=(short)((unsigned)(int)position.X+(unsigned)x);
                where.Y=(short)((unsigned)(int)position.Y+(unsigned)y);
                if(Generation_Cell_In_Bounds_0058da10(where) && image->Tiles[(int)((unsigned)type->unknown_2b4*(unsigned)y+(unsigned)x)]!=0)
                    unknown_map_cells_a70a24[(int)((unsigned)(int)where.Y*(unsigned)unknown_map_cell_side_84e804+(unsigned)(int)where.X)].unknown_45[1]=value;
            }
        }
    }
}
