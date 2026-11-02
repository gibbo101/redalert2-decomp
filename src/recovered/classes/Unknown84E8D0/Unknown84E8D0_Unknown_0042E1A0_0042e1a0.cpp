#define SHAPE_FILE_EMPTY_RECT Rect(0, 0, 0, 0)
#include "shared/unknown_globals.hpp"
#include "shared/beacon.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/anim_type.hpp"
#include "shared/palette.hpp"
#include "shared/debug_printf.hpp"
// @ref ??_C@_0M@NDGJ@PBEACON?4SHP?$AA@=007cf40c
// @ref ??_C@_0N@JLLI@RDRBEACN?4SHP?$AA@=007cf3e0
// @ref ?unknown_beacon_shape_84e98c@@3PBUShapeFileStruct@@B=0084e98c
// @ref ?unknown_radar_beacon_shape_84e990@@3PBUShapeFileStruct@@B=0084e990
// @ref ??_C@_0BJ@FEKB@Failed?5to?5load?5BeaconArt?$AA@=007cf3f0
// @ref ??_C@_0BO@HJGL@Failed?5to?5load?5RadarBeaconArt?$AA@=007cf3c0


void Unknown84E8D0::Unknown_0042E1A0()
{
    RawFileClass beacon_file("PBEACON.SHP");
    unknown_beacon_shape_84e98c = (ShapeFileStruct const *)Load_Alloc_Data(beacon_file);
    if (unknown_beacon_shape_84e98c == 0) {
        unknown_beacon_shape_84e98c = (ShapeFileStruct const *)MixFileClass::Retrieve("PBEACON.SHP");
    }
    if (unknown_beacon_shape_84e98c != 0) {
        unknown_64 = unknown_beacon_shape_84e98c->Width;
        unknown_68 = unknown_beacon_shape_84e98c->Height;
        unknown_6c = unknown_beacon_shape_84e98c->FrameCount;
    } else {
        Debug_Printf("Failed to load BeaconArt");
    }
    RawFileClass radar_file("RDRBEACN.SHP");
    unknown_radar_beacon_shape_84e990 = (ShapeFileStruct const *)Load_Alloc_Data(radar_file);
    if (unknown_radar_beacon_shape_84e990 == 0) {
        unknown_radar_beacon_shape_84e990 = (ShapeFileStruct const *)MixFileClass::Retrieve("RDRBEACN.SHP");
    }
    if (unknown_radar_beacon_shape_84e990 != 0) {
        unknown_70 = unknown_radar_beacon_shape_84e990->Width;
        unknown_74 = unknown_radar_beacon_shape_84e990->Height;
        short frames = unknown_radar_beacon_shape_84e990->FrameCount;
        unknown_78 = frames;
        unknown_7c = frames << 2;
    } else {
        Debug_Printf("Failed to load RadarBeaconArt");
    }
}
