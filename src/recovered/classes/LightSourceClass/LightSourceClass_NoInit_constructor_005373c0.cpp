// LightSourceClass::LightSourceClass(NoInitClass const &noinit) (0x005373C0): installs the vtables only
// (the load path restores the object in place; Load 0x00537BA0 expands it).
#include "shared/light_source.hpp"
// @ref ??0AbstractClass@@QAE@ABVNoInitClass@@@Z=0040ff60

LightSourceClass::LightSourceClass(NoInitClass const &noinit) :
    AbstractClass(noinit)
{
}
