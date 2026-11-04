// void CellClass::Draw_It(Point2D const &point, Rect const &clip, bool objects) (0x00475680):
// TibSun Draw_It: the cell's tile, then any smudge, unless this is the objects pass.
#include "shared/cell.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/smudge_type.hpp"
#include "shared/light_convert.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/tileset_index.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Init_Drawer@CellClass@@QAEXPAVLightConvertClass@@HHHHH@Z=004790f0
// @ref ?Clear_Icon@CellClass@@QBEHHH@Z=004767a0
// @ref ?Is_Randomized@IsometricTileTypeClass@@QBE_NH@Z=0052b730
// @ref ?unknown_func_52c230@IsometricTileTypeClass@@QAEXPAVLightConvertClass@@HPAVSurface@@HHVRect@@HHHHHHHH@Z=0052c230
// @ref ?unknown_tileset_a52f00@@3HA=00a52f00
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_CellCount_a35f28@@3HA=00a35f28
// @ref ?unknown_level_850c40@@3HA=00850c40
extern int unknown_CellCount_a35f28;     // 0x00A35F28 (TibSun CellCount)
extern int unknown_level_850c40;         // 0x00850C40 (TibSun LEVEL_LEPTON_H)

void CellClass::Draw_It(Point2D const &xpoint, Rect const &clip, bool objects)
{
    if (!objects) {
        if (unknown_34 == 0) {
            Init_Drawer(0, 0x10000, 0, 1000, 1000, 1000);
        }

        IsometricTileTypeClass *ittype = 0;
        int icon = 0;
        int subtile = 0;

        Fetch_Icon(ittype, subtile, &icon, true);

        unknown_CellCount_a35f28++;

        Point2D point;
        point.X = xpoint.X;
        point.Y = xpoint.Y - 15 * unknown_11b;

        if (ittype->unknown_slot39()) {
            ittype->unknown_func_52c230(unknown_34, subtile, unknown_surface_83995c, point.X, point.Y + unknown_int_839634, clip, unknown_11b, unknown_10c, 1, icon, 0, 0, 0, 0);
        }

        if (SmudgeIndex != -1) {
            Point2D p = point + Point2D(30, unknown_int_839634) - Point2D(clip.X, clip.Y);
            SmudgeTypes[SmudgeIndex]->unknown_slot40(&p, &clip, SmudgeData, unknown_level_850c40 * unknown_11b, &MapCoords);
        }
    }
}
