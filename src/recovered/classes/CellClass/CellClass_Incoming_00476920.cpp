// void CellClass::unknown_476920(void const *threat, bool forced, bool nokidding, bool alt)
// (0x00476920): Westwood's Incoming. Every occupier (alt: the bridge ones) scatters from the threat
// when one of them is elite, when the call insists, when the rules let everything scatter
// (PlayerScatter) or when it is a techno that may scatter (ability 3) or whose house is smart enough
// (IQScatter). threat is a CoordStruct const * (retyping it renames the callers' binding).
#include "shared/cell.hpp"
#include "shared/techno.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"

void CellClass::unknown_476920(void const *threat, bool forced, bool nokidding, bool alt)
{
    ObjectClass *object = alt ? AltOccupierPtr : OccupierPtr;
    bool elite = false;
    if (!nokidding) {
        while (object != 0) {
            TechnoClass *techno = object->As_Techno();
            if (techno != 0 && techno->unknown_118.unknown_713420()) {
                elite = true;
                break;
            }
            object = object->unknown_30;
        }
    }

    object = alt ? AltOccupierPtr : OccupierPtr;

    DynamicVectorClass<ObjectClass *> objs;
    while (object != 0) {
        objs.Add(object);
        object = object->unknown_30;
    }

    for (int i = 0; i < objs.Count(); i++) {
        TechnoClass *techno = objs[i]->As_Techno();
        if (elite || nokidding || Rules->unknown_1431
            || (techno != 0 && (techno->unknown_6d7910(3) || techno->House->unknown_194 >= Rules->IQScatter))) {
            objs[i]->unknown_slot87(*(CoordStruct const *)threat, forced, nokidding);
        }
    }
}
