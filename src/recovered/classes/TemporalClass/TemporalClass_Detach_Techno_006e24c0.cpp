// void TemporalClass::Detach_Techno(TechnoClass *target) (0x006E24C0)
// The owner going away lets go of the target; the target going away just forgets it and the chain.
#include "shared/temporal.hpp"
// @ref ?Let_Go_Of_Target@TemporalClass@@QAEXXZ=006e2500

void TemporalClass::Detach_Techno(TechnoClass *target)
{
    if (target == Owner) {
        if (Target != 0) {
            Let_Go_Of_Target();
            Target = 0;
        }
    } else if (target == Target) {
        Target = 0;
        unknown_44 = 0;
        unknown_40 = 0;
        unknown_3c = 0;
        unknown_38 = 0;
    }
}
