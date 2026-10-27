// void RadarClass::Unknown_00631ED0() (0x00631ED0)
// Builds the radar after a load: forgets the old surfaces, buffers and
// table (their pointers are stale), makes a new tracking table, refits the
// radar to the map (slot 29) and its surfaces (0x00630A00), clears the
// +0x37B flag of the listed objects, and finishes a pending switch from
// mode 3 (state 5, then the kept mode).
#include "shared/radar.hpp"
#include "shared/object.hpp"
#include "shared/map_view.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_slot29@RadarClass@@UAEXABVRect@@@Z=00630840
// @ref ?Unknown_00630A00@RadarClass@@QAEXXZ=00630a00
// @ref ?unknown_vector_a40c20@@3V?$DynamicVectorClass@PAUUnknownRadarObject37B@@@@A=00a40c20
// @ref ?Unknown_00633000@RadarClass@@QAEXH_N@Z=00633000
// @ref ?unknown_set_frame_rate_0053d820@@YIXH@Z=0053d820

void RadarClass::Unknown_00631ED0()
{
    unknown_1218 = 0;
    unknown_121c = 0;
    unknown_1238.unknown_00 = 0;
    unknown_1254 = 0;
    unknown_1270 = 0;
    unknown_1254 = New_Tracking_Table(256, 10);
    RadarClass *map = &Map;
    map->RadarClass::unknown_slot29(map->MapLocalSize);
    Unknown_00630A00();
    for (int index = 0; index < unknown_vector_a40c20.Count(); index++) {
        unknown_vector_a40c20[index]->unknown_37b = false;
    }
    if (unknown_14ac == 3) {
        unknown_14a8 = 5;
        Unknown_00633000(unknown_14b0, false);
        unknown_set_frame_rate_0053d820(Rules->DetailMinFrameRateNormal);
    }
}
