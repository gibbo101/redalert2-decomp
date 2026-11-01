// void RadarEventClass::Plot() -- 0x0063C080 (TS revent.cpp)
// Marks the radar pixels along the event's square (Plot_Radar_Event_Point for each) and, with the
// radar showing the tactical map and active, adds the square to the radar area to redraw.
#include "shared/radar.hpp"
#include "shared/map_view.hpp"
#include "shared/radar_event_class.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Get_Event_Rect@RadarEventClass@@QBEXAAY03UPoint2D@@@Z=0063c270
// @ref ?Plot_Radar_Event_Point@@YIXABUPoint2D@@@Z=0063b6a0
// @ref ?Clip_Line@@YI_NAAUPoint2D@@0ABVRect@@@Z=00775620
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0

void RadarEventClass::Plot()
{
    Point2D event_rect[4];
    int i;

    Get_Event_Rect(event_rect);
    for (i = 0; i < 4; i++) {
        event_rect[i] += Offset;
    }
    for (i = 0; i < 4; i++) {
        Map.unknown_1218->Plot_Line(Map.unknown_1218->Get_Rect(), event_rect[i], event_rect[(i + 1) % 4], Plot_Radar_Event_Point);
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
