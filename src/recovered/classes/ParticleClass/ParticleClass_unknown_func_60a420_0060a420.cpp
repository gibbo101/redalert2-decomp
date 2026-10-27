// void ParticleClass::unknown_func_60a420() (0x0060A420)
// Moves the particle by its type's behaviour (0, 1 or 2; others do not
// move here).
#include "shared/particle.hpp"
// @ref ?unknown_func_60a0e0@ParticleClass@@QAEXXZ=0060a0e0
// @ref ?unknown_func_60a230@ParticleClass@@QAEXXZ=0060a230

void ParticleClass::unknown_func_60a420()
{
    switch (Class->BehavesLike) {
    case 0:
        unknown_func_60a0e0();
        break;
    case 1:
        unknown_func_60a230();
        break;
    case 2:
        unknown_func_60a350();
        break;
    }
}
