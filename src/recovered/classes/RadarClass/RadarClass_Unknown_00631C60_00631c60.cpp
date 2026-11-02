// int __fastcall Unknown_00631C60(RadarTrackingStruct const &key) (0x00631C60)
// The hash of a tracking key: its point's hash (the tracking table's hash).
#include "shared/radar.hpp"

int __fastcall Unknown_00631C60(RadarTrackingStruct const &key)
{
    return Unknown_00631C40(key.unknown_04);
}
