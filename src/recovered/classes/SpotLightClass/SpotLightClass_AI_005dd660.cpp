// void SpotLightClass::AI() (0x005DD660)
#include "shared/spot_light.hpp"

void SpotLightClass::AI()
{
    unknown_0c += 8;
    if (unknown_0c >= 80) {
        delete this;
    }
}
