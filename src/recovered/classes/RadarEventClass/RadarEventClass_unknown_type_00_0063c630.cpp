// int RadarEventClass::Unknown_0063C630() const -- 0x0063C630 (TS Get_Suppression_Distance)
// The suppression distance of the event's type (table 0x007A8D58 +0x00).
#include "shared/radar_event_class.hpp"
// @ref ?unknown_radar_event_types_7a8d58@@3PAUUnknownRadarEventType_7a8d58@@A=007a8d58

int RadarEventClass::Unknown_0063C630() const
{
    return unknown_radar_event_types_7a8d58[Type].SuppressionDistance;
}
