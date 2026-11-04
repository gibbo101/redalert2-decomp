#define RA2_RADAR_ADD_THREADED
// bool __fastcall Submit_Radar_Event(RadarEventType event, Cell cell) -- 0x0063B5B0 (TS revent.cpp)
// Starts a radar event at a cell unless the type is suppressible and an event of the same type is
// already closer than its suppression distance.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#define RA2_RECT_POINT_INLINE
#include "shared/fast_math.hpp"
#define RA2_POINT_LENGTH
#include "shared/radar_event_class.hpp"
// @ref ?unknown_radar_events_ab67e8@@3V?$DynamicVectorClass@PAVRadarEventClass@@@@A=00ab67e8
// @ref ??0RadarEventClass@@QAE@W4RadarEventType@@VCell@@@Z=0063b6c0
// @ref ?unknown_radar_event_types_7a8d58@@3PAUUnknownRadarEventType_7a8d58@@A=007a8d58

bool __fastcall Submit_Radar_Event(RadarEventType event, Cell cell)
{
    if (Can_Suppress_Radar_Event(event)) {
        for (int index = 0; index < unknown_radar_events_ab67e8.Count(); index++) {
            if (unknown_radar_events_ab67e8[index]->Type == event) {
                if (cell.Distance_To(unknown_radar_events_ab67e8[index]->Location) < unknown_radar_events_ab67e8[index]->Unknown_0063C630()) {
                    return false;
                }
            }
        }
    }
    new RadarEventClass(event, cell);
    return true;
}
