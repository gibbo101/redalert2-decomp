// void IsometricTileTypeClass::Draw_Shadow_Caster(int index, Surface *surface, Point2D point, Rect cliprect,
// int offset) (0x0052B770)
#include "shared/isometric_tile_type.hpp"
#include "shared/tileset_index.hpp"
#include "shared/palette.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?ShadowCasterTiles@IsometricTileTypeClass@@2PAHA=00a52e74
// @ref ?unknown_block_a6e38c@@3PAXA=00a6e38c
// @ref ?unknown_tileset_a52ee8@@3HA=00a52ee8
// @ref ?unknown_tileset_a6e038@@3HA=00a6e038
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0

extern Rect unknown_rect_839630;

void IsometricTileTypeClass::Draw_Shadow_Caster(int index, Surface *surface, Point2D point, Rect cliprect, int offset)
{
    int x;
    int y;
    int frame;
    int caster_index;
    int tiletype = ArrayIndex;
    bool flat = false;
    int pieces;

    if (tiletype >= unknown_tileset_a6e038 && tiletype < unknown_tileset_a6e038 + 10) {
        pieces = unknown_tileset_a6e038;
        flat = true;
    } else {
        if (tiletype >= unknown_tileset_a52ee8 && tiletype < unknown_tileset_a52ee8 + 10) {
            pieces = unknown_tileset_a52ee8;
            flat = true;
        }
    }

    bool can_draw = false;
    if (flat && tiletype - pieces != -1) {
        caster_index = tiletype - pieces;
        if (index == ShadowCasterSlopeInfo[caster_index].Index) {
            frame = ShadowCasterSlopeInfo[caster_index].Frame;
            if (frame != 0) {
                x = 30 + ShadowCasterSlopeInfo[caster_index].XOffset;
                y = 15 + ShadowCasterSlopeInfo[caster_index].YOffset;
                can_draw = true;
            }
        }
    } else if (IsShadowCaster) {
        int i;
        for (i = 0; i < 5; i++) {
            caster_index = tiletype - ShadowCasterTiles[i];
            if (caster_index >= 0 && caster_index < 40) {
                break;
            }
            if (i == 4) {
                return;
            }
        }
        if (index == ShadowCasterCliffInfo[caster_index].Index) {
            frame = ShadowCasterCliffInfo[caster_index].Frame;
            if (frame != 0) {
                x = 30 + ShadowCasterCliffInfo[caster_index].XOffset;
                y = 15 + ShadowCasterCliffInfo[caster_index].YOffset;
                can_draw = true;
            }
        }
    }

    if (can_draw) {
        point.X += x;
        point.Y += y;
        point.X += unknown_rect_839630.X;
        point.Y += unknown_rect_839630.Y;
        point.X -= cliprect.X;
        point.Y -= cliprect.Y;
        CC_Draw_Shape(surface, unknown_LightConvertClass_list_00832398[0], (ShapeFileStruct const *)unknown_block_a6e38c,
            frame - 1, point, cliprect, 0x4601, 0, offset, 0, 1000, 0, 0, Point2D(0, 0));
    }
}
