// void TechnoClass::unknown_slot238() (0x006C2990, slot 238)
// When this object's cell is seen by its house (0x0047C2C0) and slot 160
// holds: every techno targeting it whose house sees the cell under it
// (0x0047C2E0) or shares its house is collected, slot 253 runs quietly, and
// each collected techno gets this object as its target again (slot 220).
// @ref ??_7?$DynamicVectorClass@PAVTechnoClass@@@@6B@=0079a79c
// @ref ??_G?$DynamicVectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bbc0
// @ref ?Clear@?$DynamicVectorClass@PAVTechnoClass@@@@UAEXXZ=0040b5b0
// @ref ?ID@?$DynamicVectorClass@PAVTechnoClass@@@@UAEHABQAVTechnoClass@@@Z=0040baa0
// @ref ?ID@?$DynamicVectorClass@PAVTechnoClass@@@@UAEHPBQAVTechnoClass@@@Z=0040b5e0
// @ref ?Resize@?$DynamicVectorClass@PAVTechnoClass@@@@UAE_NHPBQAVTechnoClass@@@Z=0040b9f0
// @ref ??0?$VectorClass@PAVTechnoClass@@@@QAE@IPBQAVTechnoClass@@@Z=0040bc10
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"

void TechnoClass::unknown_slot238()
{
    Cell cell = Coord_Cell(Center_Coord());
    UnknownCellClass *here = (UnknownCellClass *)&Map[cell];
    if (here->unknown_47c2c0(House->ArrayIndex) && unknown_slot160()) {
        DynamicVectorClass<TechnoClass *> attackers;
        for (int index = Technos.Count() - 1; index >= 0; index--) {
            TechnoClass *techno = Technos[index];
            if (techno->unknown_228 == this) {
                if (((UnknownCellClass *)&Map[Center_Coord()])->unknown_47c2e0(techno->House->ArrayIndex)
                    || techno->House == House) {
                    attackers.Add(techno);
                }
            }
        }
        unknown_slot253(false);
        for (int i = attackers.Count() - 1; i >= 0; i--) {
            attackers[i]->unknown_slot220(this);
        }
    }
}
