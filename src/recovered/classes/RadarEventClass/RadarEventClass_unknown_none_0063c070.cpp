// bool RadarEventClass_unknown_none() -- 0x0063C070
// Purpose: whether the radar event list (0x00AB67E8) is empty.
// Assumptions: name hypothesis.
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
// @ref ?unknown_radar_events_ab67e8@@3V?$DynamicVectorClass@PAVRadarEventClass@@@@A=00ab67e8

class RadarEventClass;
extern DynamicVectorClass<RadarEventClass *> unknown_radar_events_ab67e8;

bool RadarEventClass_unknown_none()
{
    return unknown_radar_events_ab67e8.Count() == 0 ? true : false;
}
