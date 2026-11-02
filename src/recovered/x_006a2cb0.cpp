// void Tactical::Setup_Trigger_Scroll(CoordStruct const &coord, int speed) (0x006A2CB0): starts a trigger scroll
// to a coordinate: the progress cleared, the step from the speed table (0x007F6914), the target the
// coordinate's absolute pixel (Coord_To_Pixel plus the view position), the start the current view position
// (TibSun Tactical::Setup_Trigger_Scroll; TeamClass script handler 0x006BC4C0).
#include "shared/tactical.hpp"
// @ref ?unknown_scroll_speeds_7f6914@@3PAMA=007f6914

extern float unknown_scroll_speeds_7f6914[5];      // 0x007F6914 (TibSun's static _speeds)

void Tactical::Setup_Trigger_Scroll(CoordStruct const &coord, int speed)
{
    unknown_dc = 0;
    unknown_d8 = unknown_scroll_speeds_7f6914[speed];

    Point2D to;
    Coord_To_Pixel(coord, to);
    to.X += TacPixelX;
    to.Y += TacPixelY;
    unknown_d0 = to;
    unknown_c8 = unknown_d64;
}
