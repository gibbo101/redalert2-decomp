// LAT boundary repair, full original00471D10..00472499.
#define RA2_CELL_LAT_BOOL
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/tileset_index.hpp"
// @ref ?unknown_471d10@CellClass@@QAE_NXZ=00471d10
extern int unknown_tileset_a52f84;
// @ref ?unknown_tileset_a52f84@@3HA=00a52f84
extern int unknown_tileset_a52c70;
// @ref ?unknown_tileset_a52c70@@3HA=00a52c70
extern int unknown_tileset_a52590;
// @ref ?unknown_tileset_a52590@@3HA=00a52590
extern int unknown_tileset_a52ef8;
// @ref ?unknown_tileset_a52ef8@@3HA=00a52ef8
extern int unknown_tileset_a52ee0;
// @ref ?unknown_tileset_a52ee0@@3HA=00a52ee0
extern int unknown_tileset_a6cb74;
// @ref ?unknown_tileset_a6cb74@@3HA=00a6cb74
extern int unknown_tileset_a52ef4;
// @ref ?unknown_tileset_a52ef4@@3HA=00a52ef4
extern int unknown_tileset_a6dd0c;
// @ref ?unknown_tileset_a6dd0c@@3HA=00a6dd0c
extern int unknown_tileset_a52c68;
// @ref ?unknown_tileset_a52c68@@3HA=00a52c68
extern int unknown_tileset_a52ea8;
// @ref ?unknown_tileset_a52ea8@@3HA=00a52ea8
extern int unknown_tileset_a6e018;
// @ref ?unknown_tileset_a6e018@@3HA=00a6e018
extern int unknown_tileset_a6e0e8;
// @ref ?unknown_tileset_a6e0e8@@3HA=00a6e0e8
extern int unknown_tileset_a6cf4c;
// @ref ?unknown_tileset_a6cf4c@@3HA=00a6cf4c
extern int unknown_tileset_a52c60;
// @ref ?unknown_tileset_a52c60@@3HA=00a52c60
extern int unknown_tileset_a6e0e0;
// @ref ?unknown_tileset_a6e0e0@@3HA=00a6e0e0

static Cell Translate_Cell_00471d10(Cell const &origin, Cell delta)
{
    Cell result;
    result.X = delta.X + origin.X;
    result.Y = origin.Y + delta.Y;
    return result;
}

static bool Is_LAT_Family_Tile_00471d10(int tile, int ground, int first, int last)
{
    return tile == ground || (tile >= first && tile <= last);
}

bool CellClass::unknown_471d10()
{
    int road_first = unknown_tileset_a52ee0;
    int road_last = road_first + 1;
    if (road_first == -1) road_last = -1;
    int misc_first = unknown_tileset_a6cb74;
    int misc_last = misc_first + 41;
    if (misc_first == -1) misc_last = -1;
    int rough_first = unknown_tileset_a52f84;
    int rough_last = rough_first + 15;
    if (rough_first == -1) rough_last = -1;
    int sand_first = unknown_tileset_a52c70;
    int sand_last = sand_first + 15;
    if (sand_first == -1) sand_last = -1;
    int green_first = unknown_tileset_a52590;
    int green_last = green_first + 15;
    if (green_first == -1) green_last = -1;
    int pave_first = unknown_tileset_a52ef8;
    int pave_last = pave_first + 15;
    if (pave_first == -1) pave_last = -1;
    int median_last = unknown_tileset_a52ef4;
    int median_first = median_last;
    median_last += 13;
    if (median_first == -1) median_last = -1;
    int pave_extra_last = unknown_tileset_a6dd0c;
    int pave_extra_first = pave_extra_last;
    pave_extra_last += 20;
    if (pave_extra_first == -1) pave_extra_last = -1;
    int pave_alt_last = unknown_tileset_a52c68;
    int pave_alt_first = pave_alt_last;
    pave_alt_last += 13;
    if (pave_alt_first == -1) pave_alt_last = -1;
    int smooth_first = unknown_tileset_a52ea8;
    int smooth_last = smooth_first + 11;
    if (smooth_first == -1) smooth_last = -1;
    int ramp_first = unknown_tileset_a6e018;
    int ramp_last = ramp_first + 19;
    if (ramp_first == -1) ramp_last = -1;
    int offset;
    unsigned facing;
    int index;
    int old_tile = IsoTileIndex;
    if (Is_LAT_Family_Tile_00471d10(IsoTileIndex, unknown_tileset_a6e0e8, rough_first, rough_last)) {
        offset = 0;
        facing = 0;
        for (index = 0; index < 4; index++) {
            CellClass const &neighbor = Adjacent_Cell(facing);
            int tile = neighbor.IsoTileIndex;
            if (!Is_LAT_Family_Tile_00471d10(tile, unknown_tileset_a6e0e8, rough_first, rough_last)) offset |= 1 << index;
            facing = (facing + 2) & 7;
        }
        if (offset != 0) IsoTileIndex = rough_first + offset;
        else IsoTileIndex = unknown_tileset_a6e0e8;
    }
    if (sand_first != -1 && (Is_LAT_Family_Tile_00471d10(IsoTileIndex, unknown_tileset_a6cf4c, sand_first, sand_last))) {
        offset = 0;
        facing = 0;
        for (index = 0; index < 4; index++) {
            CellClass const &neighbor = Adjacent_Cell(facing);
            int tile = neighbor.IsoTileIndex;
            if (!Is_LAT_Family_Tile_00471d10(tile, unknown_tileset_a6cf4c, sand_first, sand_last)) offset |= 1 << index;
            facing = (facing + 2) & 7;
        }
        if (offset != 0) IsoTileIndex = sand_first + offset;
        else IsoTileIndex = unknown_tileset_a6cf4c;
    }
    if (green_first != -1 && (Is_LAT_Family_Tile_00471d10(IsoTileIndex, unknown_tileset_a52c60, green_first, green_last))) {
        offset = 0;
        facing = 0;
        for (index = 0; index < 4; index++) {
            CellClass const &neighbor = Adjacent_Cell(facing);
            int tile = neighbor.IsoTileIndex;
            if (!Is_LAT_Family_Tile_00471d10(tile, unknown_tileset_a52c60, green_first, green_last) &&
                (tile < misc_first || tile > misc_last) &&
                (tile < road_first || tile > road_last)) offset |= 1 << index;
            facing = (facing + 2) & 7;
        }
        if (offset != 0) IsoTileIndex = green_first + offset;
        else IsoTileIndex = unknown_tileset_a52c60;
    }
    if (pave_first != -1 && (Is_LAT_Family_Tile_00471d10(IsoTileIndex, unknown_tileset_a6e0e0, pave_first, pave_last))) {
        offset = 0;
        facing = 0;
        for (index = 0; index < 4; index++) {
            CellClass const &neighbor = Adjacent_Cell(facing);
            int tile = neighbor.IsoTileIndex;
            if (!Is_LAT_Family_Tile_00471d10(tile, unknown_tileset_a6e0e0, pave_first, pave_last) &&
                (tile < median_first || tile > median_last) &&
                (tile < pave_alt_first || tile > pave_alt_last) &&
                (tile < pave_extra_first || tile > pave_extra_last)) offset |= 1 << index;
            facing = (facing + 2) & 7;
        }
        if (offset != 0) IsoTileIndex = pave_first + offset;
        else IsoTileIndex = unknown_tileset_a6e0e0;
    }
    int tile = IsoTileIndex;
    if ((tile >= ramp_first && tile <= ramp_last) ||
        (tile >= smooth_first && tile <= smooth_last)) {
        offset = 0;
        if (unknown_11c == 1) {
            if (Map[::Adjacent_Cell(Fetch_CellID(), 6)].unknown_11c == 0) offset |= 1;
            if (Map[Translate_Cell_00471d10(Fetch_CellID(), AdjacentCell[2])].unknown_11c == 0) offset |= 2;
            if (offset != 0) IsoTileIndex = offset + smooth_first + -1;
        }
        if (unknown_11c == 2) {
            if (Map[Translate_Cell_00471d10(Fetch_CellID(), AdjacentCell[0])].unknown_11c == 0) offset |= 1;
            if (Map[::Adjacent_Cell(Fetch_CellID(), 4)].unknown_11c == 0) offset |= 2;
            if (offset != 0) IsoTileIndex = offset + smooth_first + 2;
        }
        if (unknown_11c == 3) {
            if (Map[Translate_Cell_00471d10(Fetch_CellID(), AdjacentCell[2])].unknown_11c == 0) offset |= 1;
            if (Map[::Adjacent_Cell(Fetch_CellID(), 6)].unknown_11c == 0) offset |= 2;
            if (offset != 0) IsoTileIndex = offset + smooth_first + 5;
        }
        if (unknown_11c == 4) {
            if (Map[::Adjacent_Cell(Fetch_CellID(), 4)].unknown_11c == 0) offset |= 1;
            if (Map[Translate_Cell_00471d10(Fetch_CellID(), AdjacentCell[0])].unknown_11c == 0) offset |= 2;
            if (offset != 0) IsoTileIndex = offset + smooth_first + 8;
        }
        if (offset == 0) IsoTileIndex = unknown_11c + ramp_first - 1;
    }
    if (old_tile != IsoTileIndex) {
        IsometricTileTypeClass *tile_type = IsoTileTypes[IsoTileIndex];
        if (tile_type->unknown_slot39() == 0) tile_type->Load_Tile_Image();
    }
    return old_tile != IsoTileIndex;
}
