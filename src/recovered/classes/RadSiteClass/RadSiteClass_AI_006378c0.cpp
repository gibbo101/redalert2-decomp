// void RadSiteClass::AI() (0x006378C0, slot 23)
// Counts the site down; every RadLevelDelay frames updates the cells
// (0x00637DC0), every RadLightDelay frames dims the light, and deletes
// the site when its time is up.
#include "shared/radsite.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_00637DC0@RadSiteClass@@QAEXXZ=00637dc0
// @ref ?Change@LightSourceClass@@QAEXHHHHH@Z=00537580
// @ref ?Frame@@3HA=00a40d2c

void RadSiteClass::AI()
{
    RadTimeLeft--;
    if (unknown_28.Value() == 0) {
        Unknown_00637DC0();
        unknown_28 = CDTimerClass<FrameTimerClass>(Rules->RadLevelDelay);
    }
    if (unknown_34.Value() == 0) {
        Update_Light();
        unknown_34 = CDTimerClass<FrameTimerClass>(Rules->RadLightDelay);
    }
    if (RadTimeLeft <= 0) {
        delete this;
    }
}
