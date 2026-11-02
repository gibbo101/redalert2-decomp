// Resolve the tracked object at a radar pixel, or the underlying terrain cell.
#include "shared/radar.hpp"
#include "shared/techno.hpp"

void RadarClass::Unknown_00632AA0(Point2D const &pixel, Cell &cell, TechnoClass *&found)
{
    Point2D origin = *reinterpret_cast<Point2D const *>(&unknown_1498);
    Point2D point = pixel - origin;
    DynamicVectorClass<HashObject<RadarTrackingStruct, TechnoClass *> > &bucket = unknown_1254->Buckets[(point.X + point.Y * 251) & 255];
    int count = bucket.Count();
    found = 0;
    for (int index = count - 1; index >= 0; --index) {
        RadarTrackingStruct track = bucket[index].Key;
        if (track.unknown_04 == point) {
            found = track.unknown_00;
            break;
        }
    }
    if (found != 0) {
        cell = Cell(found->unknown_slot19(0));
    } else {
        cell = Unknown_00631500(point);
    }
}
