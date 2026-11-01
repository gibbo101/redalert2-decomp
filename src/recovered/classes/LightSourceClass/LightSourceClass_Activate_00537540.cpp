// void LightSourceClass::Activate(bool defer) (0x00537540): turns the light on
// and lights its cells.
#include "shared/light_source.hpp"
// @ref ?Unknown_005375D0@LightSourceClass@@QAEX_N@Z=005375d0

void LightSourceClass::Activate(bool defer)
{
    if (!Activated) {
        Activated = true;
        Unknown_005375D0(defer);
    }
}
