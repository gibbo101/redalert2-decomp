// RulesClass::Particles (0x0064C1D0)
// @ref ??_C@_09FDLM@Particles?$AA@=007f1680
// @ref ??_C@_00A@?$AA@=0083c55c
// Makes a ParticleTypeClass for every name listed in [Particles].
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/particle.hpp"

bool RulesClass::Particles(CCINIClass &ini)
{
    int count = ini.Entry_Count("Particles");
    for (int index = 0; index < count; index++) {
        char buffer[32];
        if (ini.Get_String("Particles", ini.Get_Entry("Particles", index), "", buffer, sizeof(buffer))) {
            ParticleTypeClass::Find_Or_Make(buffer);
        }
    }
    return count > 0;
}
