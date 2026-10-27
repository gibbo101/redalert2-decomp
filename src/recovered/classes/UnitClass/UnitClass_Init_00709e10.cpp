// void UnitClass::Init() (0x00709E10, slot 9)
// The techno initialisation, then veterancy: units of a type the owner's
// house type lists (+0x168), and trainable land units of a house with
// +0x207, start as veterans; Gunner types select weapon 0.
#include "shared/unit.hpp"
// @ref ?Init@TechnoClass@@UAEXXZ=006c1c50
// @ref ?unknown_713520@UnknownTechnoPair@@QAEX_N@Z=00713520
// @ref ?unknown_6d83f0@TechnoClass@@QAEXH@Z=006d83f0

void UnitClass::Init()
{
    TechnoClass::Init();
    if (Type) {
        if (House) {
            DynamicVectorClass<UnitTypeClass *> &veterans = Unit_House_View(House)->unknown_34->unknown_168;
            for (int index = 0; index < veterans.Count(); index++) {
                if (veterans[index] == Type) {
                    unknown_118.unknown_713520(true);
                    break;
                }
            }
        }
        if (House && Unit_House_View(House)->unknown_207 && !Type->Naval && Type->Trainable) {
            unknown_118.unknown_713520(true);
        }
        if (Type->Gunner) {
            unknown_6d83f0(0);
        }
    }
}
