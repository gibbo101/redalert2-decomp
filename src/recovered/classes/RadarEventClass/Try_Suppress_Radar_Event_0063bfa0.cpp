// bool __fastcall Try_Suppress_Radar_Event(RadarEventType event, Cell cell) -- 0x0063BFA0 (TS revent.cpp)
// Whether an event of this type at the cell would be suppressed: the type is suppressible and an event
// of the same type is closer than its suppression distance. (TS passes an unused int between the two.)
#include "shared/radar_event_class.hpp"

bool __fastcall Try_Suppress_Radar_Event(RadarEventType event, Cell cell)
{
    if (Can_Suppress_Radar_Event(event)) {
        for (int index = 0; index < unknown_radar_events_ab67e8.Count(); index++) {
            if (unknown_radar_events_ab67e8[index]->Type == event) {
                if (cell.Distance_To(unknown_radar_events_ab67e8[index]->Location) < unknown_radar_events_ab67e8[index]->Unknown_0063C630()) {
                    return true;
                }
            }
        }
    }
    return false;
}
