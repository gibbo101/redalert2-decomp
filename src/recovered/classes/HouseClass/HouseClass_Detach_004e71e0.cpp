// void HouseClass::Detach(AbstractClass *target, bool all) (0x004E71E0, slot 10)
// Forgets a destroyed object: the tag and building lists, the waypoint paths, the factories and the +0x5410 slot.
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
#include "shared/tag.hpp"
#include "shared/factory_class.hpp"
#include "shared/waypoint_path.hpp"
// @ref ___RTDynamicCast=00783ce4

void HouseClass::Detach(AbstractClass *target, bool all)
{
    if (unknown_5410 == target) {
        unknown_5410 = 0;
    }
    TagClass *tag = dynamic_cast<TagClass *>(target);
    if (tag != 0) {
        unknown_38.Delete(tag);
    }
    if (target->Kind_Of() == 6 && all) {
        unknown_50.Delete((BuildingClass *)target);
        unknown_80.Delete((BuildingClass *)target);
        unknown_98.Delete((BuildingClass *)target);
        unknown_b0.Delete((BuildingClass *)target);
        Buildings.Delete((BuildingClass *)target);
    }
    for (int index = 0; index < 12; index++) {
        if (WaypointPaths[index] == target) {
            WaypointPaths[index] = 0;
        }
    }
    if (unknown_52d8 == target) {
        unknown_52d8 = 0;
    }
    if (unknown_52dc == target) {
        unknown_52dc = 0;
    }
    if (unknown_52e0 == target) {
        unknown_52e0 = 0;
    }
    if (unknown_52e4 == target) {
        unknown_52e4 = 0;
    }
    if (unknown_52e8 == target) {
        unknown_52e8 = 0;
    }
    if (unknown_52ec == target) {
        unknown_52ec = 0;
    }
    if (unknown_52f0 == target) {
        unknown_52f0 = 0;
    }
    if (unknown_52f4 == target) {
        unknown_52f4 = 0;
    }
    if (unknown_52f8 == target) {
        unknown_52f8 = 0;
    }
}
