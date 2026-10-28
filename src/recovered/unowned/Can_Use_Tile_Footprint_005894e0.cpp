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
// @ref ?unknown_47b590@CellClass@@QBE_NXZ=0047b590
// @ref ?unknown_47b5b0@CellClass@@QBE_NXZ=0047b5b0
// Operation/freefastcall/constreference/flag signedness/bool source intent are hypotheses.
bool __fastcall Can_Use_Tile_Footprint_005894e0(int tile,Cell const &position,unsigned char check_mark,unsigned char reject_outside)
{
    IsometricTileTypeClass *type=IsoTileTypes[tile];
    IsoTileImageStruct const *image=(IsoTileImageStruct const *)type->unknown_slot39();
    if(!image)return true;
    for(int y=0;y<type->unknown_2b8;y++) {
        for(int x=0;x<type->unknown_2b4;x++) {
            Cell where=position+Cell(x,y);
            if((int)where.Y+(int)where.X>unknown_map_min_a70a1c &&
               (int)where.X-(int)where.Y<unknown_map_min_a70a1c &&
               (int)where.Y-(int)where.X<unknown_map_min_a70a1c &&
               (int)where.Y+(int)where.X<=unknown_map_max_a70a20) {
                CellClass &cell=Map[where];
                unsigned char const *subtile=(unsigned char const *)image->Tiles[(int)((unsigned)type->unknown_2b4*(unsigned)y+(unsigned)x)];
                if(subtile) {
                    if(!cell.unknown_47b590() && !cell.unknown_47b5b0())return false;
                    if((int)cell.unknown_11c!=(int)(signed char)subtile[0x2a])return false;
                    if(check_mark && unknown_map_cells_a70a24[(int)((unsigned)(int)where.Y*(unsigned)unknown_map_cell_side_84e804+(unsigned)(int)where.X)].unknown_45[1])return false;
                }
            } else if(reject_outside)return false;
        }
    }
    return true;
}
