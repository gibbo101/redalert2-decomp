// void RadarEventClass::Draw() -- 0x0063BB90 (TS revent.cpp)
// Draws the event's square on the radar surface as gradient lines between its type's two colours
// (nothing for a type whose bright colour is black) and, with the radar showing the tactical map and
// active, adds the square to the radar area to redraw.
#include "shared/radar.hpp"
#include "shared/map_view.hpp"
#include "shared/dsurface.hpp"
#include "shared/rect_intersect.hpp"
#include "shared/radar_event_class.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Get_Event_Rect@RadarEventClass@@QBEXAAY03UPoint2D@@@Z=0063c270
// @ref ?Clip_Line@@YI_NAAUPoint2D@@0ABVRect@@@Z=00775620
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
// @ref __real@8@3ffeb504f333f9de6000=007a8eb0
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

void RadarEventClass::Draw()
{
    RGBClass color1 = Get_Max_Color();
    RGBClass color2 = Get_Min_Color();
    if (color1 == RGBClass(0, 0, 0)) {
        return;
    }

    Point2D event_rect[4];
    int i;

    Get_Event_Rect(event_rect);
    for (i = 0; i < 4; i++) {
        event_rect[i] += Offset;
    }
    float color_factor = ColorFactor;
    int dy = abs(event_rect[0].Y - event_rect[1].Y);
    int dx = abs(event_rect[0].X - event_rect[1].X);
    int maxdist = MAX(dx, dy);
    float rate = (Radius * 2) * 0.7071067811865475 / (float)maxdist * ColorSpeed;
    for (i = 0; i < 4; i++) {
        ((DSurface *)Map.unknown_1218)->Draw_Gradient_Line(Map.unknown_1218->Get_Rect(), event_rect[i], event_rect[(i + 1) % 4], color1, color2, rate, color_factor);
    }
    for (i = 0; i < 4; i++) {
        Clip_Line(event_rect[i], event_rect[(i + 1) % 4], Map.unknown_1218->Get_Rect());
    }
    if (Map.unknown_14ac == 1 && Map.unknown_14a8 == 1) {
        for (i = 0; i < 4; i++) {
            Map.unknown_1208 = Union(Map.unknown_1208, Rect(event_rect[i].X, event_rect[i].Y, 1, 1) + Map.unknown_1498.Top_Left()).Intersect(Map.unknown_1498);
        }
    }
}
