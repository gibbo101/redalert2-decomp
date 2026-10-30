#include "shared/unknown_map_generator.hpp"
#include "shared/tileset_index.hpp"
unsigned int __fastcall Map_Random_Range_005797a0(unsigned int,unsigned int);
// @ref ?unknown_tileset_a52e68@@=00a52e68
// @ref ?Map_Random_Range_005797a0@@=005797a0
int UnknownMapGenerator::Randomize_Ramp_Tile_00582b30(int tile)
{
    tile-=unknown_tileset_a52e68;
    switch(tile) {
    case 4: tile=Map_Random_Range_005797a0(1,2)+4; break;
    case 5: tile=Map_Random_Range_005797a0(0,1)*2+4; break;
    case 6: tile=Map_Random_Range_005797a0(0,1)+4; break;
    case 8: tile=Map_Random_Range_005797a0(1,2)+8; break;
    case 9: tile=Map_Random_Range_005797a0(0,1)*2+8; break;
    case 10: tile=Map_Random_Range_005797a0(0,1)+8; break;
    case 11: tile=Map_Random_Range_005797a0(1,2)+11; break;
    case 12: tile=Map_Random_Range_005797a0(0,1)*2+11; break;
    case 13: tile=Map_Random_Range_005797a0(0,1)+11; break;
    case 14: tile=Map_Random_Range_005797a0(1,2)+14; break;
    case 15: tile=Map_Random_Range_005797a0(0,1)*2+14; break;
    case 16: tile=Map_Random_Range_005797a0(0,1)+14; break;
    case 22: tile=Map_Random_Range_005797a0(1,2)+22; break;
    case 23: tile=Map_Random_Range_005797a0(0,1)*2+22; break;
    case 24: tile=Map_Random_Range_005797a0(0,1)+22; break;
    case 28: tile=29; break;
    case 29: tile=28; break;
    case 34: tile=Map_Random_Range_005797a0(1,2)+34; break;
    case 35: tile=Map_Random_Range_005797a0(0,1)*2+34; break;
    case 36: tile=Map_Random_Range_005797a0(0,1)+34; break;
    }
    return tile+unknown_tileset_a52e68;
}
