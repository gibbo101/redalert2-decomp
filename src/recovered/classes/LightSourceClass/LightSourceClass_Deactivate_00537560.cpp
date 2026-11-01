// void LightSourceClass::Deactivate(bool defer) (0x00537560): turns the light off
// and relights its cells.
#include "shared/light_source.hpp"
// @ref ?Unknown_005375D0@LightSourceClass@@QAEX_N@Z=005375d0

void LightSourceClass::Deactivate(bool defer)
{
    if (Activated) {
        Activated = false;
        Unknown_005375D0(defer);
    }
}
