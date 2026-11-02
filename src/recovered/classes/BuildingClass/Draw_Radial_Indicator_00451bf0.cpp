// Draws a building's radius ellipse on the tactical view (0x00451BF0), optionally with four sweeping
// antialiased spokes whose angle follows the game frame. Names and parameter intent are hypotheses.
#include "shared/building.hpp"
#include "shared/rgb_class.hpp"
#include "shared/tactical.hpp"
#include "shared/surface.hpp"
#include "shared/display.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/hicolor.hpp"
#include "shared/cd_timer.hpp"
#include "shared/crt_math.hpp"
double __cdecl unknown_sqrt_4ba410(double value);
double __cdecl unknown_math_4ba520(double value);
extern double unknown_radial_intensity_7cf678[4];
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_radial_intensity_7cf678@@3PANA=007cf678
// @ref __real@8@3ffe8000000000000000=0079a728
// @ref __real@8@3ffca2f9836e4e441800=0079d168
// @ref __real@8@400196cbe3f9990e9000=0079d160
// @ref __real@8@4004f000000000000000=0079a718
void __fastcall Draw_Radial_Indicator_00451BF0(unsigned int radius,unsigned char mode,
    CoordStruct center,RGBClass color,bool filled,bool radius_is_pixels)
{
    int pixels;
    if (radius_is_pixels) {
        pixels = radius;
    } else {
        pixels = (int)(((double)radius + 0.5) / unknown_sqrt_4ba410(2.0) * 60.0);
    }
    Point2D pixel;
    unknown_tactical_83996c->Coord_To_Pixel(center, pixel);
    pixel += Point2D(unknown_rect_839630.X, unknown_rect_839630.Y);
    Rect area = Rect(pixel.X - pixels, pixel.Y - pixels / 2, pixels * 2, pixels);
    Rect visible = Intersect(area, unknown_rect_839630);
    if (visible.Width > 0 && visible.Height > 0) {
        RGBClass black(0, 0, 0);
        RGBClass shade = color;
        if (filled) {
            shade.Adjust(50, black);
        }
        unknown_surface_83995c->Draw_Ellipse(pixel, pixels, (pixels / 2), unknown_rect_839630,
            Build_Hicolor_Pixel(shade.Red, shade.Green, shade.Blue));
        unknown_surface_83995c->Draw_Ellipse(pixel, pixels - 1, (pixels / 2) - 1, unknown_rect_839630,
            Build_Hicolor_Pixel(shade.Red, shade.Green, shade.Blue));
        if (mode) {
            double rx = pixels;
            double ry = (pixels / 2);
            for (int i = 0; i < 4; i++) {
                double angle = (double)(Frame + i) * 0.005;
                angle = angle - (int)(angle * 0.15915494309189535) * 6.283185307179586;
                Point2D end;
                if (fabs(angle - 1.5707963267948966) < 0.001) {
                    end = pixel + Point2D(0, (int)-ry);
                } else if (fabs(angle - 4.71238898038469) < 0.001) {
                    end = pixel + Point2D(0, (int)ry);
                } else {
                    double slope = unknown_math_4ba520(angle);
                    double ry2 = ry * ry;
                    double rx2 = rx * rx;
                    double x = unknown_sqrt_4ba410(1.0 / (slope * slope / ry2 + 1.0 / rx2));
                    double y = unknown_sqrt_4ba410((1.0 - x * x / rx2) * ry2);
                    if (angle > 1.5707963267948966 && angle < 4.71238898038469) {
                        x = -x;
                    }
                    if (angle < 3.141592653589793) {
                        y = -y;
                    }
                    end = pixel + Point2D((int)x, (int)y);
                }

                int top = unknown_rect_839630.Y;
unknown_surface_83995c->Draw_Depth_Antialiased_Line(unknown_rect_839630, pixel - Point2D(unknown_rect_839630.X, top), end - Point2D(unknown_rect_839630.X, top), color,
                    -500, -500, false, true, true, true, (float)unknown_radial_intensity_7cf678[i]);
            }
        }
    }
}
