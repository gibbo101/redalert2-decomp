#define SHAPE_FILE_EMPTY_RECT Rect(0, 0, 0, 0)
#include "shared/unknown_globals.hpp"
#include "shared/beacon.hpp"
#include "shared/house.hpp"
#include "shared/cd_timer.hpp"
// @ref ?Unknown_0042DE20@UnknownBeacon@@QAEXPAVSurface@@VRect@@_N@Z=0042de20
// @ref ?unknown_beacon_phase_84e948@@3HA=0084e948

void Unknown84E8D0::Unknown_0042EED0(Surface *surface, Rect rect)
{
    if (unknown_60 && Frame % unknown_7c < unknown_beacon_phase_84e948 + 1) {
        for (int house = 0; house < 8; house++) {
            for (int slot = 0; slot < 3; slot++) {
                UnknownBeacon *beacon = unknown_00[house][slot];
                if (beacon && (beacon->unknown_flags & 1) && unknown_player_a35db4->Is_Ally(beacon->unknown_house)
                    && Houses[beacon->unknown_house]->Is_Ally(unknown_player_a35db4)
                    && !Houses[beacon->unknown_house]->unknown_13d) {
                    beacon->Unknown_0042DE20(surface, rect, false);
                }
            }
        }
    }
}
