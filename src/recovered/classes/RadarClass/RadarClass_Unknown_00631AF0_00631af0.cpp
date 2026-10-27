// void RadarClass::Unknown_00631AF0(TechnoClass *techno, Point2D point) (0x00631AF0)
// Stops tracking an object at a radar point: removes it from its bucket of
// the tracking table and, when it was there, redraws the point (0x00632620)
// and notes pending work (+0x14D5).
#include "shared/radar.hpp"
// @ref ?Unknown_00632620@RadarClass@@QAEXABUPoint2D@@@Z=00632620

void RadarClass::Unknown_00631AF0(TechnoClass *techno, Point2D point)
{
    DynamicVectorClass<HashObject<RadarTrackingStruct, TechnoClass *> > &bucket = unknown_1254->Buckets[Unknown_00631C40(point) % 256];
    HashObject<RadarTrackingStruct, TechnoClass *> object;
    object.Key.unknown_04 = point;
    object.Key.unknown_00 = techno;
    object.Value = techno;
    if (bucket.Delete(object)) {
        Unknown_00632620(point);
        unknown_14d5 = true;
    }
}
