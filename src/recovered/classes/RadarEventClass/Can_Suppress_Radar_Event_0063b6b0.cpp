// bool __fastcall Can_Suppress_Radar_Event(RadarEventType event) -- 0x0063B6B0 (TS revent.cpp)
// Whether events of this type are dropped near an event of the same type (table 0x007A8D58 +0x0C).
#include "shared/radar_event_class.hpp"
// @ref ?unknown_radar_event_types_7a8d58@@3PAUUnknownRadarEventType_7a8d58@@A=007a8d58

bool __fastcall Can_Suppress_Radar_Event(RadarEventType event)
{
    return unknown_radar_event_types_7a8d58[event].CanSuppress;
}
