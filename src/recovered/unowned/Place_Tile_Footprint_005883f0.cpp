#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/isometric_tile.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?IsoTileTypes@@=00a40cd0
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// ECX tile index, EDX Cell address, RET8 region/height. Names and nominal types are hypotheses.
void __fastcall Place_Tile_Footprint_005883f0(int tile,Cell const &position,int region,int height)
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
                    int index=(int)((unsigned)type->unknown_2b4*(unsigned)y+(unsigned)x);
                    IsoTileCellStruct const *part=(IsoTileCellStruct const *)image->Tiles[index];
                    if(part) {
                        int tileIndex=type->ArrayIndex;
                        cell.unknown_11a=(char)index;
                        cell.IsoTileIndex=tileIndex;
                        if(height!=-1)cell.unknown_11b=(char)(part->unknown_28+height-4);
                        cell.unknown_11c=part->unknown_2a;
                        if(unknown_map_cells_a70a24) {
                            unsigned at=(unsigned)(int)where.Y*(unsigned)unknown_map_cell_side_84e804+(unsigned)(int)where.X;
                            unknown_map_cells_a70a24[at].RegionIndex=region;
                        }
                    }
                }
            }
        }
    }
}
