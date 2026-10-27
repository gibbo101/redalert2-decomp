// void RadarClass::Unknown_00631910(TechnoClass *techno, Point2D point) (0x00631910)
// Starts tracking an object at a radar point: a point off the radar surface
// is clamped into it (and kept as the object's +0x1A0) unless the object is
// a building (kind 6), which is not tracked there at all. A new key goes to
// the front of its bucket for the player's objects and to the back for the
// others; then the point is queued for redraw (0x00632620).
#include "shared/radar.hpp"
#include "shared/techno.hpp"
// @ref ?Unknown_00632620@RadarClass@@QAEXABUPoint2D@@@Z=00632620
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4

void RadarClass::Unknown_00631910(TechnoClass *techno, Point2D point)
{
    Rect area = unknown_1218->Get_Rect();
    if (!area.Is_Point_Within(point)) {
        if (techno->Kind_Of() == 6) {
            return;
        }
        if (point.X < area.X) {
            point.X = area.X;
        }
        if (point.X >= area.X + area.Width) {
            point.X = area.X + area.Width - 1;
        }
        if (point.Y < area.Y) {
            point.Y = area.Y;
        }
        if (point.Y >= area.Y + area.Height) {
            point.Y = area.Y + area.Height - 1;
        }
        techno->unknown_1a0 = point;
    }
    DynamicVectorClass<HashObject<RadarTrackingStruct, TechnoClass *> > &bucket = unknown_1254->Buckets[Unknown_00631C40(point) % 256];
    HashObject<RadarTrackingStruct, TechnoClass *> object;
    object.Key.unknown_04 = point;
    object.Key.unknown_00 = techno;
    object.Value = techno;
    int count = bucket.Count();
    HashObject<RadarTrackingStruct, TechnoClass *> *objects = &bucket[0];
    for (int index = 0; index < count; index++) {
        if (objects[index] == object) {
            return;
        }
    }
    if (techno->House == unknown_player_a35db4) {
        bucket.Add_Head(object);
    } else {
        bucket.Add(object);
    }
    Unknown_00632620(point);
    unknown_14d5 = true;
}
