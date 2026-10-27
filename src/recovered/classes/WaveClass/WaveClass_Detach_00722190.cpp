// void WaveClass::Detach(AbstractClass *target, bool all) (0x00722190)
#include "shared/wave.hpp"
// @ref ?Detach@ObjectClass@@UAEXPAVAbstractClass@@_N@Z=005d3bd0

void WaveClass::Detach(AbstractClass *target, bool all)
{
    ObjectClass::Detach(target, all);
    if (Owner == target) {
        Owner = 0;
    }
    if (Target == target) {
        Target = 0;
    }
}
