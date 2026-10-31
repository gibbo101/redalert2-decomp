// void RadarEventClass::Remove_Finished() -- 0x0063BEF0 (TS revent.cpp name)
// Deletes every radar event whose duration timer has run out and that is not
// rotating, last first; the inlined destructor takes each out of the list.
#define VECTOR_IMPLEMENT_ALL
#include "shared/radar_event_class.hpp"
// @ref ?unknown_radar_events_ab67e8@@3V?$DynamicVectorClass@PAVRadarEventClass@@@@A=00ab67e8
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Frame@@3HA=00a40d2c

void RadarEventClass::Remove_Finished()
{
    for (int index = unknown_radar_events_ab67e8.Count() - 1; index >= 0; index--) {
        if (unknown_radar_events_ab67e8[index]->DurationTimer == 0 && !unknown_radar_events_ab67e8[index]->IsRotating) {
            delete unknown_radar_events_ab67e8[index];
        }
    }
}
