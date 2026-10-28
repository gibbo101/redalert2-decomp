// void ParasiteClass::Detach(AbstractClass *target, bool all) (0x00607200)
// Forgets a removed owner or victim object. When the unit attacked goes away
// while 0x00A40D04 is set, the parasite unit either dies (its +0x2C timer still
// running and slot 203 false) or is put back on the map at the coordinate
// 0x00607C30 picks, facing the way the unit attacked faced; if it cannot be
// placed there it is destroyed.
#include "shared/foot.hpp"
#include "shared/house.hpp"
#include "shared/team.hpp"
#include "shared/techno_map.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/parasite.hpp"
// @ref ?Unknown_00607C30@ParasiteClass@@QAE?AUCoordStruct@@XZ=00607c30

void ParasiteClass::Detach(AbstractClass *target, bool all)
{
    if (target == Owner) {
        Owner = 0;
        return;
    }
    if (target == unknown_28) {
        if (!unknown_flag_a40d04) {
            unknown_28 = 0;
            return;
        }
        if (unknown_2c.Value() > 0 && !Owner->unknown_slot203()) {
            unknown_28->unknown_580 = 0;
            unknown_28 = 0;
            Owner->unknown_slot60();
            return;
        }
        CoordStruct coord = Unknown_00607C30();
        unknown_a40774++;
        if (coord != unknown_geometry_l) {
            if (Owner->unknown_slot53(&coord, Dir_To_256(unknown_28->unknown_2e0.Current()))) {
                unknown_a40774--;
                if (Owner->unknown_381 && Owner->House->Unknown_004F52B0()) {
                    Owner->unknown_381 = false;
                    Owner->unknown_slot80();
                }
                if (Owner->unknown_384 != 0) {
                    ((TeamClass *)Owner->unknown_384)->unknown_func_6b8cc0(Owner);
                }
                if (!Owner->unknown_slot270()) {
                    Owner->unknown_6d6e50(0);
                    Owner->unknown_slot220(0);
                    Owner->unknown_slot260(0, 1);
                }
                Owner->unknown_slot261(0, 1);
                Owner->unknown_slot262(0, 0, 0, 0);
                Map.Unknown_0054A550(CoordStruct(Owner->Coord), Owner->unknown_1f4 - 3, Owner->unknown_1f4 + 3, 0);
                unknown_28 = 0;
                return;
            }
        }
        unknown_a40774--;
        Owner->Strength = 0;
        Owner->unknown_slot60();
        unknown_28 = 0;
        return;
    }
    if (target == Victim) {
        Victim = 0;
        unknown_54 = true;
    }
}
