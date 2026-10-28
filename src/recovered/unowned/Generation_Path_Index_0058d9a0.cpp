#include "shared/map_generation_path.hpp"
#include "shared/tileset_index.hpp"
extern int unknown_tileset_a6dd04;
// @ref ?unknown_tileset_a6e014@@=00a6e014
// @ref ?unknown_tileset_a6dd04@@=00a6dd04
// Original names and free fastcall/return-signedness source intent are hypotheses.
int __fastcall Generation_Path_Index_0058d9a0(int tile)
{
    if(tile>=unknown_tileset_a6e014 && tile<(int)((unsigned)unknown_tileset_a6e014+101u))
        return tile-unknown_tileset_a6e014;
    if(tile>=unknown_tileset_a6dd04 && tile<(int)((unsigned)unknown_tileset_a6dd04+8u))
        return tile-unknown_tileset_a6dd04+101;
    return 0;
}
