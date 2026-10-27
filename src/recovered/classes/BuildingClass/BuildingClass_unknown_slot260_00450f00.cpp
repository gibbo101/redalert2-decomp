// void BuildingClass::unknown_slot260(AbstractClass *target, int arg2) (0x00450F00, slot 260)
// Ignored in mission 19; otherwise records the target (0x006D6E50) when slot 153
// or the type flag +0x1353 holds, then the techno behaviour.
#include "shared/building.hpp"
// @ref ?unknown_6d6e50@TechnoClass@@QAEXPAVAbstractClass@@@Z=006d6e50
// @ref ?unknown_slot260@TechnoClass@@UAEXPAVAbstractClass@@H@Z=006d48e0

void BuildingClass::unknown_slot260(AbstractClass *target, int arg2)
{
    if (Mission != 19) {
        if (unknown_slot153() || Type->ConstructionYard) {
            unknown_6d6e50(target);
        }
        TechnoClass::unknown_slot260(target, arg2);
    }
}
