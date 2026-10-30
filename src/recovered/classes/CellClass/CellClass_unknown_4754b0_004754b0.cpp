// void CellClass::unknown_4754b0(Point2D const &point, Rect const &rect) (0x004754B0)
// Draws the first isometric tile type's image at point, clipped to rect, with the cell's
// +0x11B and +0x10C values (Tactical 0x006A3641).
// @ref ?unknown_func_52c230@IsometricTileTypeClass@@QAEXPAVLightConvertClass@@HPAVSurface@@HHVRect@@HHHHHHHH@Z=0052c230
#include "shared/cell.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/light_convert.hpp"

void CellClass::unknown_4754b0(Point2D const &point, Rect const &rect)
{
    IsoTileTypes[0]->unknown_func_52c230(unknown_LightConvertClass_list_00832398[0], 0, unknown_surface_83995c,
        point.X, point.Y, rect, unknown_11b, unknown_10c, 1, 0, 0, 1, 0, 0);
}
