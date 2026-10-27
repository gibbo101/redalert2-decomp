// void RadarClass::Unknown_00631D40() (0x00631D40)
// Rebuilds the radar: a fresh tracking table, the radar refitted to the
// map's local area (slot 29), 0x00630A00, and the +0x37B flag of every
// object in the list at 0x00A40C20 cleared.
#include "shared/radar.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_00631C60@@YIIABURadarTrackingStruct@@@Z=00631c60
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Unknown_00630A00@RadarClass@@QAEXXZ=00630a00
// @ref ?unknown_slot29@RadarClass@@UAEXABVRect@@@Z=00630840
// @ref ?unknown_vector_a40c20@@3V?$DynamicVectorClass@PAUUnknownRadarObject37B@@@@A=00a40c20


void RadarClass::Unknown_00631D40()
{
    delete unknown_1254;
    unknown_1254 = New_Tracking_Table(256, 10);
    RadarClass *map = &Map;
    map->RadarClass::unknown_slot29(map->MapLocalSize);
    Unknown_00630A00();
    for (int index = 0; index < unknown_vector_a40c20.Count(); index++) {
        unknown_vector_a40c20[index]->unknown_37b = false;
    }
}
