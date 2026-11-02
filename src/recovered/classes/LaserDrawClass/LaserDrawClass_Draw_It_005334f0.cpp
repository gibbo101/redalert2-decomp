// void LaserDrawClass::Draw_It() (0x005334F0; TibSun laser.cpp Draw_It)
// Draws the laser as a core line and, with an outer colour, two one-pixel glow lines beside it
// offset by the beam's eight-way facing. RA2: no fog test; house-colour lasers draw through
// Draw_House_Color; at detail level 0 depth-shaded lines, else antialiased (blinking) or
// intensity-scaled (slot 16) lines.
#include "shared/laser_draw.hpp"
#include "shared/surface.hpp"
#include "shared/tactical.hpp"
#include "shared/facing.hpp"
#include "shared/fast_math.hpp"
#include "shared/random2.hpp"
#include "shared/hicolor_pixel.hpp"
#include "shared/unknown_globals.hpp"

extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;
extern Rect unknown_rect_839630;
// @ref ?unknown_facing_scale_79b628@@3NB=0079b628
// @ref ?unknown_facing_origin_79b630@@3NB=0079b630
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?unknown_random_839218@@3VRandom2Class@@A=00839218
// @ref ?unknown_a40b2c@@3HA=00a40b2c
// @ref ?Draw_House_Color@LaserDrawClass@@QAEXXZ=00533c80
// @ref _?$S47@?7??Draw_It@LaserDrawClass@@QAEXXZ@4EA=00a6e539
// @ref _$E48=00533c70
// @ref _?_glow_offsets@?7??Draw_It@LaserDrawClass@@QAEXXZ@4PAULaserGlowOffset@@A=00a6e558

// The direction from one coordinate to another (TibSun inline.h Direction(Coord const &, Coord const &);
// file-local here until another unit shows it).
inline UnknownFacingDir Direction(CoordStruct const &coord1, CoordStruct const &coord2)
{
    int x1 = coord1.X;
    int x2 = coord2.X;

    return UnknownFacingDir((unsigned short)(int)((Fast_Atan2((double)coord1.Y - (double)coord2.Y, (double)x2 - (double)x1)
        - unknown_facing_origin_79b630) * unknown_facing_scale_79b628));
}

// A value in [a, b] from the generator at 0x00839218 (TibSun Sim_Random_Pick; file-local hypothesis).
inline int Sim_Random_Pick(int a, int b)
{
    return unknown_random_839218(a, b);
}

// The glow offset table's element: a screen point with a destructor (the table's atexit
// destructor 0x00533C70 is an empty function; type hypothesis).
struct LaserGlowOffset : Point2D {
    LaserGlowOffset(Point2D const &point) : Point2D(point) {}
    ~LaserGlowOffset() {}
};

void LaserDrawClass::Draw_It()
{
    if (Duration > 0) {
        if (IsHouseColor) {
            Draw_House_Color();
            return;
        }

        static LaserGlowOffset _glow_offsets[16] = {
            Point2D(0, -1),
            Point2D(1, 0),
            Point2D(0, -1),
            Point2D(0, 1),
            Point2D(1, 0),
            Point2D(0, 1),
            Point2D(-1, 0),
            Point2D(1, 0),
            Point2D(-1, 0),
            Point2D(0, 1),
            Point2D(0, -1),
            Point2D(1, 0),
            Point2D(0, -1),
            Point2D(-1, 0),
            Point2D(-1, 0),
            Point2D(1, 0)
        };

        if (!BlinkState) {
            UnknownFacingDir dir = Direction(Source, Target);
            int facing = Dir_To_8(dir);

            Point2D start_pixel;
            unknown_tactical_83996c->Coord_To_Pixel(Source, start_pixel);
            Point2D end_pixel;
            unknown_tactical_83996c->Coord_To_Pixel(Target, end_pixel);

            int start_z = ZAdjust - Unknown_006A2970(Source.Z) - 2;
            int end_z = -Unknown_006A2970(Target.Z) - 2;

            RGBClass outer_color;
            int outer_hicolor = 0;
            bool has_outer_glow = true;

            if (OuterColor == RGBClass(0, 0, 0)) {
                has_outer_glow = false;
            } else {
                int red = Sim_Random_Pick(-OuterSpread.Red, OuterSpread.Red);
                int green = Sim_Random_Pick(-OuterSpread.Green, OuterSpread.Green);
                int blue = Sim_Random_Pick(-OuterSpread.Blue, OuterSpread.Blue);

                red += OuterColor.Red;
                red = red < 0 ? 0 : red;
                red = red > 255 ? 255 : red;

                green += OuterColor.Green;
                green = green < 0 ? 0 : green;
                green = green > 255 ? 255 : green;

                blue += OuterColor.Blue;
                blue = blue < 0 ? 0 : blue;
                blue = blue > 255 ? 255 : blue;

                outer_hicolor = RGB_To_Pixel(red, green, blue);
                outer_color.Red = red;
                outer_color.Green = green;
                outer_color.Blue = blue;
            }

            float current_intensity = 1.0f;

            bool has_r = InnerColor.Red > 0;
            bool has_g = InnerColor.Green > 0;
            bool has_b = InnerColor.Blue > 0;

            if (Fades) {
                current_intensity = (StartIntensity - EndIntensity) * (Duration - Progress.Stage) / Duration + EndIntensity;
            }

            if (unknown_a40b2c != 0) {
                if (Blinks) {
                    unknown_surface_83995c->Draw_Depth_Antialiased_Line(unknown_rect_839630, start_pixel, end_pixel,
                        InnerColor, start_z, end_z, false, true, true, true, current_intensity);
                    if (has_outer_glow) {
                        unknown_surface_83995c->Draw_Depth_Antialiased_Line(unknown_rect_839630,
                            start_pixel + _glow_offsets[2 * facing], end_pixel + _glow_offsets[2 * facing],
                            outer_color, start_z, end_z, false, true, true, true, 1.0f);
                        unknown_surface_83995c->Draw_Depth_Antialiased_Line(unknown_rect_839630,
                            start_pixel + _glow_offsets[2 * facing + 1], end_pixel + _glow_offsets[2 * facing + 1],
                            outer_color, start_z, end_z, false, true, true, true, 1.0f);
                    }
                } else if (has_outer_glow) {
                    unknown_surface_83995c->Unknown_Slot16(unknown_rect_839630,
                        start_pixel + _glow_offsets[2 * facing], end_pixel + _glow_offsets[2 * facing],
                        outer_color, current_intensity, start_z, end_z);
                    unknown_surface_83995c->Unknown_Slot16(unknown_rect_839630,
                        start_pixel + _glow_offsets[2 * facing + 1], end_pixel + _glow_offsets[2 * facing + 1],
                        outer_color, current_intensity, start_z, end_z);
                    unknown_surface_83995c->Unknown_Slot16(unknown_rect_839630, start_pixel, end_pixel,
                        InnerColor, current_intensity, start_z, end_z);
                } else {
                    unknown_surface_83995c->Draw_Depth_Antialiased_Line(unknown_rect_839630, start_pixel, end_pixel,
                        InnerColor, start_z, end_z, false, has_r, has_g, has_b, current_intensity);
                }
            } else {
                unknown_surface_83995c->Draw_Depth_Shaded_Line(unknown_rect_839630, start_pixel, end_pixel,
                    RGB_To_Pixel(InnerColor.Red, InnerColor.Green, InnerColor.Blue), start_z, end_z);
                if (has_outer_glow) {
                    unknown_surface_83995c->Draw_Depth_Shaded_Line(unknown_rect_839630,
                        start_pixel + _glow_offsets[2 * facing], end_pixel + _glow_offsets[2 * facing],
                        outer_hicolor, start_z, end_z);
                    unknown_surface_83995c->Draw_Depth_Shaded_Line(unknown_rect_839630,
                        start_pixel + _glow_offsets[2 * facing + 1], end_pixel + _glow_offsets[2 * facing + 1],
                        outer_hicolor, start_z, end_z);
                }
            }
        }
    }
}
