// RadarEventClass::~RadarEventClass() -- 0x0063B840 (TS revent.cpp)
// Takes the event out of the radar event list.
#define VECTOR_IMPLEMENT_ALL
#include "shared/radar_event_class.hpp"
// @ref ?unknown_radar_events_ab67e8@@3V?$DynamicVectorClass@PAVRadarEventClass@@@@A=00ab67e8

RadarEventClass::~RadarEventClass()
{
    RadarEventClass *self = this;
    unknown_radar_events_ab67e8.Delete(self);
}
