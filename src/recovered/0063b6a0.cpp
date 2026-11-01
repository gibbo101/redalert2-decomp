// void __fastcall Plot_Radar_Event_Point(Point2D const &point) -- 0x0063B6A0 (TS revent.cpp)
// The plotter RadarEventClass::Plot passes to Plot_Line: marks one radar pixel (RadarClass 0x00632620,
// TS Radar_Pixel).
#include "shared/radar.hpp"
#include "shared/map_view.hpp"
#include "shared/radar_event_class.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_00632620@RadarClass@@QAEXABUPoint2D@@@Z=00632620

void __fastcall Plot_Radar_Event_Point(Point2D const &point)
{
    Map.Unknown_00632620(point);
}
