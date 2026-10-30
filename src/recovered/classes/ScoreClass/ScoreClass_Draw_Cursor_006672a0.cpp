// void ScoreClass::Draw_Cursor(int x, int y) (0x006672A0)
// The name entry's blinking underscore: erases it where it was, draws it
// (11 pixels, 14 below y) or restores the background under it, and flips
// it every 5 ticks. The function-static timer's atexit destructor is
// 0x00667410.
#include "shared/score.hpp"
#include "shared/dsurface.hpp"
#include "shared/unknown_globals.hpp"
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref _atexit=0078298a
// @ref _?$S62@?1??Draw_Cursor@ScoreClass@@QAEXHH@Z@4EA=00ab6f18
// @ref _?timer@?1??Draw_Cursor@ScoreClass@@QAEXHH@Z@4V?$CDTimerClass@VSystemTimerClass@@@@A=00ab6f50
// @ref _?blink@?1??Draw_Cursor@ScoreClass@@QAEXHH@Z@4HA=00ab6f88
// @ref _?lastx@?1??Draw_Cursor@ScoreClass@@QAEXHH@Z@4HA=00ab6fa0

void ScoreClass::Draw_Cursor(int x, int y)
{
    static CDTimerClass<SystemTimerClass> timer;
    static int lastx;
    static int blink;
    Rect rect;
    y += 14;
    if (x != lastx) {
        rect.Set(lastx, y, 11, 1);
        unknown_surface_839954->Copy_From(rect, *unknown_surface_839958, rect, false, true);
        lastx = x;
    }
    if (blink) {
        unknown_surface_839954->Draw_Line(Point2D(x, y), Point2D(x + 10, y), Color);
    } else {
        rect.Set(x, y, 11, 1);
        unknown_surface_839954->Copy_From(rect, *(Surface *)unknown_08, rect, false, true);
    }
    if (!timer) {
        blink ^= 1;
        timer = 5;
    }
}
