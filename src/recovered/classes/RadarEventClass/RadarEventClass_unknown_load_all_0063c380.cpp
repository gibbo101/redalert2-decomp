// bool __fastcall RadarEventClass_unknown_load_all(IStream *stream) -- 0x0063C380 (TS RadarEventClass::Load)
// Deletes every radar event, then reads the count and each event's 0x40 bytes into new events, then
// the word at 0x00AB67B8 (see RadarEventClass_unknown_save_all 0x0063C310). A failed event read still
// returns true (TS returns S_OK there).
#include "shared/com_persist.hpp"
#include "shared/radar_event_class.hpp"
// @ref ?unknown_radar_event_word_ab67b8@@3HA=00ab67b8
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??2@YAPAXI@Z=00782017

bool __fastcall RadarEventClass_unknown_load_all(IStream *stream)
{
    for (int i = unknown_radar_events_ab67e8.Count() - 1; i >= 0; i--) {
        delete unknown_radar_events_ab67e8[i];
        unknown_radar_events_ab67e8.Delete(i);
    }
    int count;
    if (FAILED(stream->Read(&count, sizeof(count), 0))) {
        return false;
    }
    for (int index = 0; index < count; index++) {
        RadarEventClass *event = new RadarEventClass(RADAREVENT_NONE, Cell(0, 0));
        HRESULT hr = stream->Read(event, sizeof(*event), 0);
        if (FAILED(hr)) {
            return S_OK;
        }
    }
    if (SUCCEEDED(stream->Read(&unknown_radar_event_word_ab67b8, sizeof(unknown_radar_event_word_ab67b8), 0))) {
        return true;
    }
    return false;
}
