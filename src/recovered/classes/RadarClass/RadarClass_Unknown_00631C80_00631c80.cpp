// void RadarClass::Unknown_00631C80() (0x00631C80)
// Builds a new tracking table (256 buckets, hash 0x00631C60, growth 10).
#include "shared/radar.hpp"
// @ref ?Unknown_00631C60@@YIHABURadarTrackingStruct@@@Z=00631c60
// @ref ??2@YAPAXI@Z=00782017

void RadarClass::Unknown_00631C80()
{
    unknown_1254 = new HashTableClass<RadarTrackingStruct, TechnoClass *>(10, 256, Unknown_00631C60);
}
