// void ProgressScreenClass::Draw_Flag(Point2D xy, Surface *flag) (0x0061FAB0)
// Copies a country flag image to xy on the composite surface, magenta
// transparent, in the size of the first country's flag.
#include "shared/progress_screen.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/dsurface.hpp"
#include "shared/hicolor.hpp"
#include "shared/pcx_cache.hpp"
// @ref ?Draw_0068ce80@UnknownBitmapWriter@@QAE_NABVRect@@PAVSurface@@1H@Z=0068ce80
// @ref ?Is_Surface_Lost@DSurface@@QAE_NXZ=004aaee0
// @ref ?unknown_surface_839954@@3PAVSurface@@A=00839954

void ProgressScreenClass::Draw_Flag(Point2D xy, Surface *flag)
{
    int width = 0, height = 0;
    Flag_Size(&width, &height);
    Rect rect(xy.X, xy.Y, width, height);
    int transparent = Build_Hicolor_Pixel(255, 0, 255);
    if (unknown_surface_839954 != 0 && !static_cast<DSurface *>(unknown_surface_839954)->Is_Surface_Lost()) {
        unknown_bitmap_writer_a76378.Draw_0068ce80(rect, unknown_surface_839954, flag, transparent);
    }
}
