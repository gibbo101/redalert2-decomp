// void LightSourceClass::Deactivate(int arg) (0x00537560): turns the light off
// and relights its cells.
#include "shared/light_source.hpp"
// @ref ?Unknown_005375D0@LightSourceClass@@QAEXH@Z=005375d0

void LightSourceClass::Deactivate(int arg)
{
    if (Activated) {
        Activated = false;
        Unknown_005375D0(arg);
    }
}
