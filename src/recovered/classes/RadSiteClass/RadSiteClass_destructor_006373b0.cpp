// ??1RadSiteClass@@UAE@XZ (0x006373B0)
// Clears the radiation of the base cell, detaches the site, deletes its light and unlists it.
#include "shared/radsite.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0047CE30@RadSiteCell@@QAEXPAVRadSiteClass@@@Z=0047ce30
// @ref ?Detach_This_From_All@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ??1AbstractClass@@UAE@XZ=0040ff90

RadSiteClass::~RadSiteClass()
{
    RadSiteCell &cell = (RadSiteCell &)Map[BaseCell];
    cell.Unknown_0047CE30(0);
    Detach_This_From_All(this, true);
    if (LightSource != 0) {
        delete LightSource;
        LightSource = 0;
    }
    unknown_RadSiteClass_list_00ab6620.Delete(this);
}
