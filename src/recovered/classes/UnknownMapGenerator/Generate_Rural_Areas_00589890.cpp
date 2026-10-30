#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_generation_path.hpp"
#include "shared/tileset_index.hpp"
extern int unknown_tileset_a6dd04;
// @ref ?unknown_tileset_a6e014@@=00a6e014
// @ref ?unknown_tileset_a6dd04@@=00a6dd04
extern UnknownMapGenerationPath unknown_generation_paths_a700a0[109];
// @ref ?unknown_generation_paths_a700a0@@=00a700a0
// The original109-record array/12-byte stride is evidenced by full initializer/cleanup.
// Its source name and this cdecl/void operation spelling remain hypotheses.
void Set_Generation_Path_Tile_Indices_0058d9d0()
{
    int i;
    for(i=0;i<101;i++)
        unknown_generation_paths_a700a0[i].unknown_08=(int)((unsigned)unknown_tileset_a6e014+(unsigned)i);
    for(i=0;i<8;i++)
        unknown_generation_paths_a700a0[101+i].unknown_08=(int)((unsigned)unknown_tileset_a6dd04+(unsigned)i);
}

bool __fastcall Can_Place_Paved_Road_00588a30(Rect const &area,bool first,bool second);
// @ref ?Generate_Rural_Buildings_00589ac0@UnknownMapGenerator@@=00589ac0
// @ref ?Generate_Rural_Units_00589f00@UnknownMapGenerator@@=00589f00
// @ref ?Generate_Rural_Roads_0058a1b0@UnknownMapGenerator@@=0058a1b0
// @ref __real@8@3ffdf5c28f5c28f5c000=007a6050
// Existing accepted cell-protection predicate, legacy fastcall/short-pointer ABI retained.
namespace seed_0056dac0 {
bool __fastcall FUN_0056dac0(short *position)
{
    unsigned index=(unsigned)(int)position[1]*(unsigned)unknown_map_cell_side_84e804+(unsigned)(int)position[0];
    return unknown_map_cells_a70a24[index].unknown_45[0]==0;
}
}
// @ref ?FUN_0056dac0@=0056dac0
void UnknownMapGenerator::Generate_Rural_Areas_00589890()
{
    Set_Generation_Path_Tile_Indices_0058d9d0();
    int count=(int)((SeedOptions.UrbanPresence+0.49)*2);
    int tries=0;
    int placed=0;
    while(tries<10 && placed<count) {
        Cell position;
        position.X=0;
        position.Y=0;
        int localTries=0;
        for(;;) {
            position=MapRegionClass::Pick_Random_Clear_Map_Cell_0056d7a0();
            ++localTries;
            if(localTries>=20)break;
            if(seed_0056dac0::FUN_0056dac0((short *)&position) && Can_Place_Paved_Road_00588a30(Rect(position.X-4,position.Y-4,8,8),false,false) && Map.Unknown_0055A660(position,true))break;
        }
        if(localTries!=20 && Generate_Rural_Roads_0058a1b0(position)) {
            Generate_Rural_Buildings_00589ac0(position);
            Generate_Rural_Units_00589f00(position);
            ++placed;
        }
        ++tries;
    }
}
