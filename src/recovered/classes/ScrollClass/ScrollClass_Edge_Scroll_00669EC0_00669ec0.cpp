// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// void ScrollClass::Edge_Scroll_00669EC0(Point2D const &xy) (0x00669EC0): scrolls the view when the mouse
// is at a screen edge (or with inertia), speeding up with the right button. From ra2-decomp
// ScrollClass::Scroll_Edge (YR 0x00692B60), adapted to our names.
#include "shared/scroll.hpp"
#include "shared/display.hpp"
#include "shared/surface.hpp"
#include "shared/fast_math.hpp"
#include "shared/facing.hpp"
#include "shared/keyboard.hpp"
#include "shared/options.hpp"
#include "shared/rules.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_surface_839948@@3PAVSurface@@A=00839948
// @ref ?unknown_surface_839964@@3PAVSurface@@A=00839964
// @ref ?unknown_8523e0@@3HA=008523e0
// @ref ?unknown_8523e4@@3HA=008523e4
// @ref ?unknown_int_839648@@3HA=00839648
// @ref ?unknown_int_83964c@@3HA=0083964c
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Counter@ScrollClass@@2V?$CDTimerClass@VSystemTimerClass@@@@A=00ab7048
// @ref _$E95=0066a280
// @ref _?$S94@?4??Edge_Scroll_00669EC0@ScrollClass@@QAEXABUPoint2D@@@Z@4EA=00ab7054
// @ref _?_rate@?BN@??Edge_Scroll_00669EC0@ScrollClass@@QAEXABUPoint2D@@@Z@4PAHA=007f2be8
// @ref _?dir@?4??Edge_Scroll_00669EC0@ScrollClass@@QAEXABUPoint2D@@@Z@4UUnknownFacingDir@@A=00ab70a0
// @ref _?direction@?4??Edge_Scroll_00669EC0@ScrollClass@@QAEXABUPoint2D@@@Z@4HA=00ab706c
// @ref _?edge_x@?L@??Edge_Scroll_00669EC0@ScrollClass@@QAEXABUPoint2D@@@Z@4NA=007f2bd8
// @ref _?edge_y@?L@??Edge_Scroll_00669EC0@ScrollClass@@QAEXABUPoint2D@@@Z@4NA=007f2be0
// @ref __real@8@3fffc90fdaa22168c000=0079b630
// @ref __real@8@c00ca5f9836e4e441800=0079b628

// Westwood's Bound: original clipped to minval..maxval.
static inline int Scroll_Bound(int original, int minval, int maxval)
{
    if (original < minval) return minval;
    if (original > maxval) return maxval;
    return original;
}

void ScrollClass::Edge_Scroll_00669EC0(Point2D const &xy)
{
    if (unknown_4f2a != true) {
        Point2D p = Point2D(unknown_rect_839630.X, unknown_rect_839630.Y) + xy;
        int x = p.X;
        int y = p.Y;
        int w = (unknown_surface_839964->Get_Width() + unknown_surface_839948->Get_Width()) - 1;
        int h = unknown_surface_839964->Get_Height() - 1;

        bool at_screen_edge = (y <= 0 || x <= 0 || x >= w || y >= h);

        bool player_scrolled = false;

        static UnknownFacingDir dir;
        static int direction;

        if (unknown_4f18 || at_screen_edge) {
            if (at_screen_edge) {
                player_scrolled = true;

                int width = unknown_8523e0;
                int height = unknown_8523e4;

                static double edge_x = 0.16;
                static double edge_y = 0.21;

                int altx = x;
                if (altx < width * edge_x) {
                    altx = 0;
                } else if (altx > width * (1.0 - edge_x)) {
                    altx = width - 1;
                } else {
                    altx = width / 2;
                }

                int alty = y;
                if (alty < height * edge_y) {
                    alty = 0;
                } else if (alty > height * (1.0 - edge_y)) {
                    alty = height - 1;
                } else {
                    alty = height / 2;
                }

                Point2D center(unknown_int_839648 / 2, unknown_int_83964c / 2);
                dir = UnknownFacingDir((unsigned short)((Fast_Atan2((double)center.Y - alty, (double)altx - center.X) - 1.5707963267948966) * -10430.060040584269));
                direction = Dir_To_256(dir);
            }

            int control = Dir_To_8(UnknownFacingDir((unsigned short)(direction << 8)));

            static int _rate[9] = {448, 384, 320, 256, 192, 128, 64, 32, 16};

            int rate = 8 - unknown_4f18;

            if (rate < Options.ScrollRate + 1) {
                rate = Options.ScrollRate + 1;
                unknown_4f18 = 8 - rate;
            }

            if (WWKeyboard->Down((KeyNumType)2)) {
                rate = Scroll_Bound(rate + 1, 4, 8);
            }

            int facing = Dir_To_8(UnknownFacingDir((unsigned short)(direction << 8)));

            int distance = 1;

            if (!unknown_slot41(facing, &distance, false)) {
                Override_Mouse_Shape(control + 9, false);
            } else {
                Override_Mouse_Shape(control + 1, false);

                distance = (int)(_rate[rate] * Rules->ScrollMultiplier);
                unknown_slot41(facing, &distance, true);

                if (Counter == 0 && player_scrolled) {
                    Counter = 1;
                    unknown_4f18++;
                }
            }
        }
        if (!player_scrolled) {
            if (!Counter) {
                unknown_4f18--;
                if (unknown_4f18 < 0) unknown_4f18++;
                Counter = 1;
            }
        }
    }
}
