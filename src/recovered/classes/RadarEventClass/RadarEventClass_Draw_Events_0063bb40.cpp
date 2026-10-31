// void RadarEventClass::Draw_Events() -- 0x0063BB40 (TS revent.cpp name)
// Draws every radar event whose visibility timer is still running or that
// is rotating.
#define VECTOR_IMPLEMENT_ALL
#include "shared/radar_event_class.hpp"
// @ref ?unknown_radar_events_ab67e8@@3V?$DynamicVectorClass@PAVRadarEventClass@@@@A=00ab67e8
// @ref ?Draw@RadarEventClass@@QAEXXZ=0063bb90
// @ref ?Frame@@3HA=00a40d2c

void RadarEventClass::Draw_Events()
{
    for (int index = 0; index < unknown_radar_events_ab67e8.Count(); index++) {
        RadarEventClass *event = unknown_radar_events_ab67e8[index];
        if (event->VisibilityTimer > 0 || event->IsRotating) {
            event->Draw();
        }
    }
}
