// void ParticleSystemClass::AI() (0x0060CB70)
// Runs the behaviour routine of the type, ends the system when its lifetime
// runs out, and once ended and empty leaves the map and queues itself in the
// 0x00AC0CD8 list.
#include "shared/particle_system.hpp"
// @ref ?unknown_func_60b4e0@ParticleSystemClass@@QAEXXZ=0060b4e0
// @ref ?unknown_func_60b670@ParticleSystemClass@@QAEXXZ=0060b670
// @ref ?unknown_func_60bb70@ParticleSystemClass@@QAEXXZ=0060bb70
// @ref ?unknown_func_60c050@ParticleSystemClass@@QAEXXZ=0060c050
// @ref ?unknown_func_60c7c0@ParticleSystemClass@@QAEXXZ=0060c7c0

void ParticleSystemClass::AI()
{
    switch (Class->BehavesLike) {
    case 0:
        unknown_func_60bb70();
        break;
    case 1:
        unknown_func_60b4e0();
        break;
    case 2:
        unknown_func_60c7c0();
        break;
    case 3:
        unknown_func_60b670();
        break;
    case 4:
        unknown_func_60c050();
        break;
    }
    if (--Lifetime == 0) {
        unknown_slot60();
    }
    if (unknown_7d && unknown_e4 && Particles.Count() == 0) {
        unknown_slot52();
        unknown_7d = false;
        unknown_objects_ac0cd8.Add(this);
    }
}
