#include "shared/map_select.hpp"
// @ref ??9Wstring@@QBE_NPBD@Z=0076dae0
// @ref ??BSystemTimerClass@@=0069a430
// RA2's idle slot retains the queued-voice clock query but no playback action.
// The value is discarded; querying the real system time remains observable.
void MapSelect::Unknown_Slot2()
{
    if(VoiceName!=(char const *)0) {
        (void)VoiceTimer.Value();
    }
}
