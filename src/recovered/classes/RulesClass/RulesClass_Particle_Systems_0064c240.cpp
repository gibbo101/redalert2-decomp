// RulesClass::Particle_Systems (0x0064C240)
// @ref ??_C@_0BA@IINN@ParticleSystems?$AA@=007f168c
// @ref ??_C@_00A@?$AA@=0083c55c
// Makes a ParticleSystemTypeClass for every name listed in [ParticleSystems].
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/particle_system.hpp"

bool RulesClass::Particle_Systems(CCINIClass &ini)
{
    int count = ini.Entry_Count("ParticleSystems");
    for (int index = 0; index < count; index++) {
        char buffer[32];
        if (ini.Get_String("ParticleSystems", ini.Get_Entry("ParticleSystems", index), "", buffer, sizeof(buffer))) {
            ParticleSystemTypeClass::Find_Or_Make(buffer);
        }
    }
    return count > 0;
}
