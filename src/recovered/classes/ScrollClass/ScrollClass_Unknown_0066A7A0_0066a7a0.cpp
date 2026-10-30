// void ScrollClass::Unknown_0066A7A0(Point2D const &xy) (0x0066A7A0)
#include "shared/scroll.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/options.hpp"
#include "shared/particle.hpp"
#include "shared/crt_memory.hpp"
// @ref ?unknown_flag_a40380@@3_NA=00a40380
// @ref ?unknown_a40d13@@3_NA=00a40d13
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref ?unknown_8523e0@@3HA=008523e0
// @ref ?unknown_8523e4@@3HA=008523e4
// @ref __imp__GetSystemMetrics@4=0079a3dc
// @ref __imp__ClientToScreen@8=0079a4ac
// @ref __imp__SetCursorPos@8=0079a444
// @ref ?Get_Scroll_Method@OptionsClass@@QBEHXZ=005da3e0
// @ref ?Unknown_00721DB0@@YIHABUPoint2D@@0@Z=00721db0
// @ref ?unknown_slot41@DisplayClass@@UAE_NHPAH_N@Z=00499b60
// @ref __ftol=0077f110
// @ref __real@8@4002c000000000000000=007a5e18
// @ref __real@8@3fff8000000000000000=0079a708
// @ref _?_direction@?1??Unknown_0066A7A0@ScrollClass@@QAEXABUPoint2D@@@Z@4HA=007f2c0c
// @ref _?unknown_7f2c10@?1??Unknown_0066A7A0@ScrollClass@@QAEXABUPoint2D@@@Z@4PAHA=007f2c10
// @ref _?_mouse@?1??Unknown_0066A7A0@ScrollClass@@QAEXABUPoint2D@@@Z@4PAHA=007f2c30

void ScrollClass::Unknown_0066A7A0(Point2D const &xy)
{
    static int _direction = -1;
    // Unreferenced by the code (0x007F2C10, between the two statics the code uses).
    static int unknown_7f2c10[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    static int _mouse[16] = {
        0x3D, 0x3E, 0x40, 0x3F, 0x42, 0x3D, 0x41, 0x3D, 0x44, 0x45, 0x3D, 0x3D, 0x43, 0x3D, 0x3D, 0x3D
    };

    if (!unknown_flag_a40958) {
        return;
    }
    if (!unknown_flag_a40380 && !unknown_a40d13) {
        return;
    }
    if (!unknown_4f28) {
        if (abs(xy.X - unknown_4f20.X) > GetSystemMetrics(0x44) * 2
                || abs(xy.Y - unknown_4f20.Y) > GetSystemMetrics(0x45) * 2) {
            unknown_4f28 = true;
        }
    }
    if (!unknown_4f28) {
        return;
    }
    if (!unknown_4f1c) {
        if (unknown_11cb) {
            unknown_slot49(Point2D(-1, -1));
        } else {
            unknown_4f1c = true;
        }
    }
    if (unknown_4f1c) {
        int dx = xy.X - unknown_4f20.X;
        int dy = xy.Y - unknown_4f20.Y;
        int direction = Unknown_00721DB0(unknown_4f20, xy);
        if (direction != _direction) {
            _direction = direction;
        }
        if (dx == 0) {
            if (unknown_4f20.X == 0) {
                dx = -1;
            } else if (unknown_4f20.X >= unknown_8523e0 - 1) {
                dx = 1;
            }
        }
        if (dy == 0) {
            if (unknown_4f20.Y == 0) {
                dy = -1;
            } else if (unknown_4f20.Y >= unknown_8523e4) {
                dy = 1;
            }
        }
        if ((unknown_4f20.X < 10 && dx < 0) || (unknown_4f20.X > unknown_8523e0 - 10 && dx > 0)) {
            if (dx < 0 && dx > -5) {
                dx = -5;
            }
            if (dx > 0 && dx < 5) {
                dx = 5;
            }
            dx *= 4;
        }
        if ((unknown_4f20.Y < 10 && dy < 0) || (unknown_4f20.Y > unknown_8523e4 - 10 && dy > 0)) {
            if (dy < 0 && dy > -5) {
                dy = -5;
            }
            if (dy > 0 && dy < 5) {
                dy = 5;
            }
            dy *= 4;
        }

        int distance_x;
        int distance_y;
        switch (Options.Get_Scroll_Method()) {
        case 0: {
            double rate = 1.0 / (Options.ScrollRate + 1);
            distance_x = abs((int)(dx * rate));
            distance_y = abs((int)(dy * rate));
            break;
        }
        case 1: {
            double rate = 12.0 / (Options.ScrollRate + 1);
            distance_x = abs((int)(dx * rate));
            distance_y = abs((int)(dy * rate));
            if (distance_x + distance_y > 0) {
                POINT point;
                point.x = 0;
                point.y = 0;
                ClientToScreen(MainWindow, &point);
                SetCursorPos(point.x + unknown_rect_839630.X + unknown_4f20.X, point.y + unknown_rect_839630.Y + unknown_4f20.Y);
            }
            break;
        }
        case 2: {
            dx = -dx;
            dy = -dy;
            double rate = 12.0 / (Options.ScrollRate + 1);
            distance_x = abs((int)(dx * rate));
            distance_y = abs((int)(dy * rate));
            if (distance_x + distance_y > 0) {
                POINT point;
                point.x = 0;
                point.y = 0;
                ClientToScreen(MainWindow, &point);
                SetCursorPos(point.x + unknown_rect_839630.X + unknown_4f20.X, point.y + unknown_rect_839630.Y + unknown_4f20.Y);
            }
            break;
        }
        }

        int blocked = 0;
        for (int facing = 0; facing < 8; facing += 2) {
            int one = 1;
            if (!Map.unknown_slot41(facing, &one, false)) {
                blocked |= 1 << (facing / 2);
            }
        }
        if (dx > 0) {
            Map.unknown_slot41(2, &distance_x, true);
        } else if (dx < 0) {
            Map.unknown_slot41(6, &distance_x, true);
        }
        if (dy > 0) {
            Map.unknown_slot41(4, &distance_y, true);
        } else if (dy < 0) {
            Map.unknown_slot41(0, &distance_y, true);
        }
        Set_Default_Mouse(_mouse[blocked], true);
    }
}
