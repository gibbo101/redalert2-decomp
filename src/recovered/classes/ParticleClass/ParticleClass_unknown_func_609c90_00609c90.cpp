// void ParticleClass::unknown_func_609c90() (0x00609C90)
// Runs the behaviour routine of the type's BehavesLike value, then counts
// the lifetime down and flags the particle done at zero.
#include "shared/particle.hpp"
// @ref ?unknown_func_608bb0@ParticleClass@@QAEXXZ=00608bb0
// @ref ?unknown_func_609200@ParticleClass@@QAEXXZ=00609200
// @ref ?unknown_func_6093a0@ParticleClass@@QAEXXZ=006093a0
// @ref ?unknown_func_609540@ParticleClass@@QAEXXZ=00609540
// @ref ?unknown_func_609970@ParticleClass@@QAEXXZ=00609970

void ParticleClass::unknown_func_609c90()
{
    switch (Class->BehavesLike) {
    case 0:
        unknown_func_608bb0();
        break;
    case 1:
        unknown_func_6093a0();
        break;
    case 2:
        unknown_func_609970();
        break;
    case 3:
        unknown_func_609540();
        break;
    case 4:
        unknown_func_609200();
        break;
    }
    Lifetime--;
    if (Lifetime == 0) {
        unknown_121 = true;
    }
}
