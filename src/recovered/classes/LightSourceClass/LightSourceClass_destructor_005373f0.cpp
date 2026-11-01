// LightSourceClass::~LightSourceClass() (0x005373F0): detaches the light from
// everything, leaves the light list and, when active, turns it off.
#include "shared/light_source.hpp"
#include "shared/radsite.hpp"
// @ref ?Detach_This_From_All@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?Unknown_005375D0@LightSourceClass@@QAEX_N@Z=005375d0

LightSourceClass::~LightSourceClass()
{
    Detach_This_From_All(this, true);
    unknown_LightSourceClass_list_00a6e818.Delete(this);
    if (Activated) {
        Activated = false;
        Unknown_005375D0(0);
    }
}
