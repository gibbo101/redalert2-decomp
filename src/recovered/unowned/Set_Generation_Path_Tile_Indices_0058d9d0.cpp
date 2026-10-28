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
