// ?Set_Rad_Level@RadSiteClass@@QAEXH@Z (0x006375B0)
// Radiation level; the duration is level times the rules multiple.
#include "shared/radsite.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

void RadSiteClass::Set_Rad_Level(int level)
{
    RadLevel = level;
    RadTimeLeft = RadDuration = Rules->RadDurationMultiple * level;
}
