// void ParticleClass::unknown_slot67(int arg1, int arg2) (0x00609D10, slot 67)
// Draws the particle (TibSun ParticleClass::Draw_It) at the screen point arg1
// within the window arg2, unless the frame rate is too low or it is hidden
// under fog. Shape particles draw their frame lifted by their height, with
// the type's translucency at full detail; sparks and railgun particles put
// one pixel blended along the type's colour list, dimmed by the alpha buffer
// and hidden behind closer depth.
#include "shared/particle.hpp"
#include "shared/logic.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/id_source.hpp"
#include "shared/special.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/palette.hpp"
#include "shared/blit.hpp"
#include "shared/surface.hpp"
#include "shared/hicolor.hpp"
// @ref ?Unknown_0053D840@@YAIXZ=0053d840
// @ref ?unknown_a6eb1c@@3IA=00a6eb1c
// @ref ?Unknown_006A2970@@YIHH@Z=006a2970
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

void ParticleClass::unknown_slot67(int arg1, int arg2)
{
    Point2D const &point = *(Point2D const *)arg1;
    Rect const &cliprect = *(Rect const *)arg2;
    if (unknown_a6eb1c < Unknown_0053D840()) {
        return;
    }
    if (unknown_a40b2c != 0 || Class->BehavesLike != 1 && Class->BehavesLike != 3) {
        if (!unknown_flag_a40d13 && unknown_b263d8 != 0 && unknown_id_source_a3d290->Special().FogOfWar && Map.Unknown_005683C0(Position_Coord_004f3f40())) {
            return;
        }

        if (Class->BehavesLike != 3 && Class->BehavesLike != 4) {
            int height_offset = -15 - Unknown_006A2970(unknown_slot110());
            ShapeFileStruct const *shape = (ShapeFileStruct const *)unknown_slot26();
            if (shape != 0) {
                int flags = 0x2800;
                int shapenum = unknown_slot116();
                if (unknown_a40b2c == 2) {
                    if (unknown_11f == 25) {
                        flags = 0x2802;
                    } else if (unknown_11f == 50) {
                        flags = 0x2804;
                    } else if (unknown_11f >= 75) {
                        flags = 0x2806;
                    }
                }
                CC_Draw_Shape(unknown_surface_83995c, Unit_Draw_Convert_008323C0, shape, shapenum, point, cliprect, flags | 0xE00, 0, height_offset, 2, 1000, 0, 0, Point2D(0, 0));
            }
        } else {
            Point2D pixel;
            unknown_tactical_83996c->Coord_To_Pixel(Position_Coord_004f3f40(), pixel);
            pixel.Y += unknown_int_839634;
            if (cliprect.Is_Point_Within(pixel)) {
                Point2D alpha_point = pixel - Point2D(0, ZBufferPtr->Area.Y);
                unsigned short *alpha_ptr = ZBufferPtr->Get_Buffer_Ptr(alpha_point);
                int alpha = *alpha_ptr;
                if (alpha != 0) {
                    Point2D depth_point = pixel - Point2D(0, ABufferPtr->Area.Y);
                    int zdepth = (unsigned short)(ABufferPtr->Area.Y + ABufferPtr->MaxValue - pixel.Y) - Unknown_006A2970(Position_Coord_004f3f40().Z) - 50;
                    int depth = *ABufferPtr->Get_Buffer_Ptr(depth_point);
                    if (zdepth < depth) {
                        RGBClass color1 = ColorState.ColorIndex == 0 ? Color : Class->ColorList[ColorState.ColorIndex];
                        RGBClass color2 = Class->ColorList[ColorState.ColorIndex + 1];
                        int red = color1.Red * (1.0 - ColorState.Fraction) + color2.Red * ColorState.Fraction;
                        int green = color1.Green * (1.0 - ColorState.Fraction) + color2.Green * ColorState.Fraction;
                        int blue = color1.Blue * (1.0 - ColorState.Fraction) + color2.Blue * ColorState.Fraction;
                        if (alpha < 127) {
                            red = (int)(red * alpha) >> 7;
                            green = (int)(green * alpha) >> 7;
                            blue = (int)(blue * alpha) >> 7;
                        }
                        unknown_surface_83995c->Put_Pixel(pixel, (unsigned short)Build_Hicolor_Pixel(red, green, blue));
                    }
                }
            }
        }
    }
}
