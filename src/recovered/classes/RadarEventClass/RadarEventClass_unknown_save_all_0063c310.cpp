// bool __fastcall RadarEventClass_unknown_save_all(IStream *stream) -- 0x0063C310
// Purpose: writes the radar events (list 0x00AB67E8): their count, each
// event's 0x40 bytes, then the word at 0x00AB67B8; false when a write
// fails. Called by the save-game writer (0x00656711).
// Assumptions: the events are saved by raw copy (RadarEventClass is 0x40
// bytes); the trailing word's meaning and the names are hypotheses.
#include "shared/com_persist.hpp"
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
// @ref ?unknown_radar_events_ab67e8@@3V?$DynamicVectorClass@PAVRadarEventClass@@@@A=00ab67e8
// @ref ?unknown_radar_event_word_ab67b8@@3HA=00ab67b8

class RadarEventClass;
extern DynamicVectorClass<RadarEventClass *> unknown_radar_events_ab67e8;
extern int unknown_radar_event_word_ab67b8;

bool __fastcall RadarEventClass_unknown_save_all(IStream *stream)
{
    int count = unknown_radar_events_ab67e8.Count();
    if (FAILED(stream->Write(&count, sizeof(count), 0))) {
        return false;
    }
    for (int index = 0; index < count; index++) {
        if (FAILED(stream->Write(unknown_radar_events_ab67e8[index], 0x40, 0))) {
            return false;
        }
    }
    return SUCCEEDED(stream->Write(&unknown_radar_event_word_ab67b8, sizeof(unknown_radar_event_word_ab67b8), 0)) ? true : false;
}
