// HouseClass::~HouseClass() (0x004E30C0)
// Deletes the house's waypoint paths, super weapons and tags, releases its
// connection points and removes it from the global lists and Houses.
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
#include "shared/waypoint_path.hpp"
// @ref ??_EWaypointClass@@QAEPAXI@Z=0041b890
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00

extern DynamicVectorClass<ObjectClass *> unknown_objects_ac0c80;   // 0x00AC0C80
extern DynamicVectorClass<ObjectClass *> unknown_objects_ac0c30;   // 0x00AC0C30
extern bool unknown_flag_a40958;            // 0x00A40958
extern HouseClass *unknown_house_84e894;    // 0x0084E894

HouseClass::~HouseClass()
{
    Unknown_006ECB90((ObjectClass *)this, true);
    Type = 0;
    for (int index = 0; index < 12; index++) {
        delete WaypointPaths[index];
        WaypointPaths[index] = 0;
    }
    for (index = 0; index < Supers.Count(); index++) {
        delete Supers[index];
    }
    Supers.Clear();
    if (unknown_56cc != 0 && unknown_flag_a40958) {
        unknown_56cc->Release();
        unknown_56cc = 0;
    }
    while (unknown_38.Count() > 0) {
        delete unknown_38[0];
    }
    for (index = 0; index < ConnectionPoints.Count(); index++) {
        while (ConnectionPoints[index]->Release() > 0) {
        }
        ConnectionPoints[index] = 0;
    }
    ConnectionPoints.Clear();
    unknown_15f60 = 0;
    unknown_objects_ac0cb0.Delete((ObjectClass *)this);
    unknown_objects_ac0c80.Delete((ObjectClass *)this);
    unknown_objects_ac0c30.Delete((ObjectClass *)this);
    unknown_objects_ac0c58.Delete((ObjectClass *)this);
    unknown_objects_ac0d60.Delete((ObjectClass *)this);
    if (unknown_house_84e894 == this) {
        unknown_house_84e894 = 0;
    }
    Houses.Delete(this);
}
