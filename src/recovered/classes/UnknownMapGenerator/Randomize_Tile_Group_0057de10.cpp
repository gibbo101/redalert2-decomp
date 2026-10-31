#include "shared/unknown_map_generator.hpp"
// @ref __real@8@3fe2a0000000a0000000=007a5f28
// @ref __real@8@3fe6f2000000f2000000=007a5f20
// @ref __real@8@3fe6c9000000c9000000=007a5f18
#include "shared/random.hpp"
extern Random2Class unknown_map_random_a705c0;
// @ref ?unknown_map_random_a705c0@@3VRandom2Class@@A=00a705c0
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref __real@8@3fdf8000000080000000=007a5dd0
unsigned int __fastcall Map_Random_Range_005797a0(unsigned int minimum,unsigned int maximum)
{
    double origin;
    unsigned int result;
    do {
        origin=minimum;
        result=(unsigned int)((unsigned int)unknown_map_random_a705c0()*(double)(unsigned int)(maximum-minimum+1)*(1.0/4294967295.0)+origin);
    } while(result>maximum);
    return result;
}

#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/map_region.hpp"
#include "shared/tileset_index.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?Adjacent_Cell@CellClass@@QAEAAV1@I@Z=00476ac0
// @ref ?unknown_map_cells_a70a24@@=00a70a24
// @ref ?unknown_map_cell_side_84e804@@=0084e804
// @ref ?unknown_tileset_a52580@@=00a52580
// @ref ?Stamp_Tile_005883f0@@=005883f0
// @ref ?Map_Random_Range_005797a0@@=005797a0
void __fastcall Stamp_Tile_005883f0(int tile,Cell const &position,int region,int height);
void UnknownMapGenerator::Randomize_Tile_Group_0057de10()
{
    Map.Unknown_0055A550();
    for(CellClass *cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490()) {
        if(cell->IsoTileIndex==unknown_tileset_a52580 && cell->unknown_11a==0) {
            CellClass &east=cell->Adjacent_Cell(2);
            CellClass &south=cell->Adjacent_Cell(4);
            CellClass &corner=cell->Adjacent_Cell(3);
            if(east.IsoTileIndex==unknown_tileset_a52580 && east.unknown_11a==0 &&
               south.IsoTileIndex==unknown_tileset_a52580 && south.unknown_11a==0 &&
               corner.IsoTileIndex==unknown_tileset_a52580 && corner.unknown_11a==0 &&
               Map_Random_Range_005797a0(1,10)!=1) {
                    int sample=(int)Map_Random_Range_005797a0(0,241);
                    int variant=sample>=240 ?247-sample:sample/40;
                    Cell const &position=cell->MapCoords;
                    int region=!unknown_map_cells_a70a24 ?-1:unknown_map_cells_a70a24[position.Y*unknown_map_cell_side_84e804+position.X].RegionIndex;
                    Stamp_Tile_005883f0(unknown_tileset_a52580+variant,position,region,-1);
            } else {
                unsigned sample=Map_Random_Range_005797a0(0,200);
                cell->IsoTileIndex=unknown_tileset_a52580+sample/40+8;
            }
        }
    }
}
