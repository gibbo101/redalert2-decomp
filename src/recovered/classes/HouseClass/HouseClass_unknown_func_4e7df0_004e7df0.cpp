// void HouseClass::unknown_func_4e7df0() (0x004E7DF0)
// Destroys every techno the house owns (through the rules' warhead at
// +0xC74); a techno taken over by another owner counts for that owner.
#include "shared/techno.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848


// The object a techno keeps at +0x230, and the one at +0x20C (views).
struct UnknownTechno230View {
    char unknown_00[0x28];
    HouseClass *unknown_28;                 // +0x28
};
struct UnknownTechno20cView {
    void unknown_func_6e2680();             // 0x006E2680 (releases its techno)
};

void HouseClass::unknown_func_4e7df0()
{
    int index = 0;
    TechnoClass *last = 0;
    int damage;
    while (index < Technos.Count()) {
        TechnoClass *techno = Technos[index];
        HouseClass *owner = techno->unknown_234 != 0
            ? ((UnknownTechno230View *)((TechnoClass *)techno->unknown_234)->unknown_230)->unknown_28
            : techno->House;
        if (owner == this && techno != last) {
            damage = techno->Strength;
            if (techno->unknown_20c != 0) {
                ((UnknownTechno20cView *)techno->unknown_20c)->unknown_func_6e2680();
            }
            techno->unknown_slot86(&damage, 0, Rules->unknown_c74, 0, true, 1);
            last = techno;
        } else {
            index++;
        }
    }
}
