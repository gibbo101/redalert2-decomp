// void CellClass::Draw_Shadow_Cast(Point2D const &point, Rect const &clip) (0x004755D0): TibSun
// Draw_Shadow_Cast: the shadow a shadow casting tile throws, offset by the cell's height.
#include "shared/cell.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/smudge_type.hpp"
#include "shared/light_convert.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/tileset_index.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Is_Randomized@IsometricTileTypeClass@@QBE_NH@Z=0052b730
// @ref ?unknown_tileset_a52f00@@3HA=00a52f00
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?Draw_Shadow_Caster@IsometricTileTypeClass@@QAEXHPAVSurface@@UPoint2D@@VRect@@H@Z=0052b770
inline void CellClass::Fetch_Icon(IsometricTileTypeClass *&ittype, int &subtile, int *icon, bool doicon) const
{
    if (IsoTileIndex != 0xFFFF) {
        ittype = IsoTileTypes[IsoTileIndex];
        subtile = (unsigned char)unknown_11a;
        if (ittype->NumTileTypesInSet > 1) {
            if (ittype->Is_Randomized(subtile)) {
                if (doicon) *icon = (unknown_140 >> 13) & 1;
            } else {
                if (doicon) {
                    int count = ittype->NumTileTypesInSet;
                    *icon = Clear_Icon(IsoTileIndex, count);
                }
            }
        }
    } else {
        ittype = IsoTileTypes[unknown_tileset_a52f00];
        subtile = 0;
        if (doicon) {
            int count = ittype->NumTileTypesInSet;
            *icon = Clear_Icon(unknown_tileset_a52f00, count);
        }
    }
}

void CellClass::Draw_Shadow_Cast(Point2D const &point, Rect const &clip)
{
    int subtile;
    IsometricTileTypeClass *isotype;

    Fetch_Icon(isotype, subtile, 0, false);
    if (isotype->IsShadowCaster) {
        Point2D drawpoint;
        drawpoint.X = point.X;
        drawpoint.Y = point.Y - 15 * unknown_11b;
        isotype->Draw_Shadow_Caster(subtile, unknown_surface_83995c, drawpoint, clip, -2 - 15 * (unknown_11b - 4));
    }
}
