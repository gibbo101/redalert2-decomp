// void RadSiteClass::Increase_Radiation(int amount) (0x006375F0)
// Takes the site's current (decayed) level, clears its effect
// (0x00637C10), restarts it at that level plus amount and reapplies it
// (0x00637640). Names are hypotheses.
#include "shared/radsite.hpp"
// @ref ?Unknown_00637C10@RadSiteClass@@QAEXXZ=00637c10
// @ref ?Unknown_00637640@RadSiteClass@@QAEXXZ=00637640
// @ref __ftol=0077f110

void RadSiteClass::Increase_Radiation(int amount)
{
    double level_now = RadLevel;
    double left = RadTimeLeft;
    double duration = RadDuration;
    int level = (int)(level_now * left / duration);
    Unknown_00637C10();
    Set_Rad_Level(level + amount);
    Unknown_00637640();
}
