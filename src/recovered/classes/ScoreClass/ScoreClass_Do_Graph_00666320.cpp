// void ScoreClass::Do_Graph(int first, int second, int xpos) (0x00666320)
// Draws two translucent bars (gold for first, red for second) 140 pixels
// high at most, then grows them two pixels a tick with their counting
// values on top; the final bars and values also go to the background.
#include "shared/score.hpp"
#include "shared/dsurface.hpp"
#include "shared/rgb_class.hpp"
#include "shared/string_table.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?ScoreDelay@ScoreClass@@QAEXH@Z=00667420
// @ref ??_C@_15KLDP@?$AA?$CF?$AAd?$AA?$AA@=007d1598
// @ref ??_C@_08MELN@BarGraph?$AA@=007f288c

void ScoreClass::Do_Graph(int first, int second, int xpos)
{
    Rect firstrect(0, 0, 0, 0);
    Rect secondrect(0, 0, 0, 0);
    int max;
    xpos = XOffset + xpos;
    int bottom = YOffset + 244;
    int firstheight = first, secondheight = second;
    max = firstheight > secondheight ? firstheight : secondheight;
    if (!max) {
        max = 1;
    }
    firstheight = firstheight * 140 / max;
    secondheight = secondheight * 140 / max;
    if (max < 20) {
        firstheight = first * 5;
        secondheight = second * 5;
    }
    max = firstheight > secondheight ? firstheight : secondheight;
    if (!max) {
        max = 1;
    }
    Rect rect;
    rect.Set(xpos, bottom - firstheight, 4, firstheight);
    ((Surface *)unknown_08)->Fill_Rect_Trans(rect, RGBClass(0xFD, 0xB5, 0x1C), 25);
    rect.Set(xpos + 4, bottom - firstheight, 7, firstheight);
    ((Surface *)unknown_08)->Fill_Rect_Trans(rect, RGBClass(0xFD, 0xB5, 0x1C), 50);
    rect.Set(xpos + 11, bottom - firstheight, 4, firstheight);
    ((Surface *)unknown_08)->Fill_Rect_Trans(rect, RGBClass(0xFD, 0xB5, 0x1C), 25);
    rect.Set(xpos + 132, bottom - secondheight, 4, secondheight);
    ((Surface *)unknown_08)->Fill_Rect_Trans(rect, RGBClass(0xFA, 0x1C, 0x1C), 25);
    rect.Set(xpos + 132 + 4, bottom - secondheight, 7, secondheight);
    ((Surface *)unknown_08)->Fill_Rect_Trans(rect, RGBClass(0xFA, 0x1C, 0x1C), 50);
    rect.Set(xpos + 132 + 11, bottom - secondheight, 4, secondheight);
    ((Surface *)unknown_08)->Fill_Rect_Trans(rect, RGBClass(0xFA, 0x1C, 0x1C), 25);

    int firstheightcount = 1;
    int secondheightcount = 1;
    int secondcount = second;
    int firstcount = first;
    int secondstep = second * 2;
    int firststep = first * 2;
    for (int y = bottom - 1; firstheightcount <= (firstheight > secondheight ? firstheight : secondheight); ) {
        if (firstrect.Is_Valid()) {
            unknown_surface_839954->Copy_From(firstrect, *unknown_surface_839958, firstrect, false, true);
        }
        if (firstheightcount <= firstheight) {
            rect.Set(xpos, y, 15, firstheightcount);
            unknown_surface_839954->Copy_From(rect, *(Surface *)unknown_08, rect, false, true);
            firstrect = Count_Up_Print(unknown_surface_839954, L"%d", firstcount / max, first, xpos, y);
        } else {
            firstrect = Count_Up_Print(unknown_surface_839954, L"%d", first, first, xpos, bottom - firstheight);
        }
        if (secondrect.Is_Valid()) {
            unknown_surface_839954->Copy_From(secondrect, *unknown_surface_839958, secondrect, false, true);
        }
        if (secondheightcount <= secondheight) {
            rect.Set(xpos + 132, y, 15, secondheightcount);
            unknown_surface_839954->Copy_From(rect, *(Surface *)unknown_08, rect, false, true);
            secondrect = Count_Up_Print(unknown_surface_839954, L"%d", secondcount / max, second, xpos + 132, y);
        } else {
            secondrect = Count_Up_Print(unknown_surface_839954, L"%d", second, second, xpos + 132, bottom - secondheight);
        }
        Play_Sound("BarGraph", 96);
        ScoreDelay(1);
        firstheightcount += 2;
        secondheightcount += 2;
        firstcount += firststep;
        y -= 2;
        secondcount += secondstep;
    }

    if (firstrect.Is_Valid()) {
        unknown_surface_839954->Copy_From(firstrect, *unknown_surface_839958, firstrect, false, true);
    }
    rect.Set(xpos, bottom - firstheight, 15, firstheight);
    unknown_surface_839958->Copy_From(rect, *(Surface *)unknown_08, rect, false, true);
    Count_Up_Print(unknown_surface_839954, L"%d", first, first, xpos, bottom - firstheight);
    Count_Up_Print(unknown_surface_839958, L"%d", first, first, xpos, bottom - firstheight);
    if (secondrect.Is_Valid()) {
        unknown_surface_839954->Copy_From(secondrect, *unknown_surface_839958, secondrect, false, true);
    }
    rect.Set(xpos + 132, bottom - secondheight, 15, secondheight);
    unknown_surface_839958->Copy_From(rect, *(Surface *)unknown_08, rect, false, true);
    Count_Up_Print(unknown_surface_839954, L"%d", second, second, xpos + 132, bottom - secondheight);
    Count_Up_Print(unknown_surface_839958, L"%d", second, second, xpos + 132, bottom - secondheight);
    ScoreDelay(20);
}
