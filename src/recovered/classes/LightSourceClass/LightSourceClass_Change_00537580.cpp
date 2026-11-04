// void LightSourceClass::Change(int intensity, int red, int green, int blue, bool defer) (0x00537580):
// takes the new intensity and colour unless they look unchanged, and relights
// the cells when active. (The test compares the stored red with both red and
// blue and never looks at green: as in the original.)
#include "shared/light_source.hpp"
// @ref ?Unknown_005375D0@LightSourceClass@@QAEX_N@Z=005375d0

void LightSourceClass::Change(int intensity, int red, int green, int blue, bool defer)
{
    if (Intensity != intensity || RedTint != red || RedTint != blue) {
        Intensity = intensity;
        GreenTint = green;
        RedTint = red;
        BlueTint = blue;
        if (Activated) {
            Unknown_005375D0(defer);
        }
    }
}
