// ?Update_Light@RadSiteClass@@QAEXXZ (0x00637F50)
// Scales the light colour by the remaining time and applies it.
#include "shared/radsite.hpp"
// @ref ?Change@LightSourceClass@@QAEXHHHH_N@Z=00537580

void RadSiteClass::Update_Light()
{
    LightSource->Change(LightSource->Intensity - unknown_68,
                        unknown_58 * RadTimeLeft / RadDuration,
                        unknown_5c * RadTimeLeft / RadDuration,
                        unknown_60 * RadTimeLeft / RadDuration, 0);
}
