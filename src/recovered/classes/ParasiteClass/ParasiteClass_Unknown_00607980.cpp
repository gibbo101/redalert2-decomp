// void ParasiteClass::Unknown_00607980(FootClass *target) (0x00607980)
// Starts a parasite attachment, or returns the owner to its cell.
#include "shared/foot.hpp"
#include "shared/cell.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
#include "shared/parasite.hpp"
// Small accessors for the host and owner fields.
inline int Unknown_1f4_Of_00607980(FootClass *foot) { return foot->unknown_1f4; }
inline void Set_Parasite_00607980(FootClass *host, FootClass *parasite) { host->unknown_580 = parasite; }
void ParasiteClass::Unknown_00607980(FootClass *target)
{
    Unknown_006064C0();
    if (!Can_Infect_006078F0(target)) {
        if (!Owner->unknown_slot53(&Map[Owner->unknown_454].Center_Coord(), 0)) {
            Owner->unknown_slot60();
            return;
        }
        Owner->unknown_slot263(false, false, false, 0);
        Map.Unknown_0054A550(CoordStruct(Owner->Coord), Unknown_1f4_Of_00607980(Owner) - 3, Unknown_1f4_Of_00607980(Owner) + 2, 0);
        if (!Owner->unknown_slot270()) {
            Owner->unknown_slot220(0);
            Owner->unknown_slot260(0, 1);
        }
        Owner->unknown_slot261(false, true);
        return;
    }
    Owner->Locomotor.Checked()->Force_Track(-1, CoordStruct(target->Coord));
    Set_Parasite_00607980(target, Owner);
    unknown_28 = target;
}
