// Fear decays, changes prone state and can make a Fraidycat flee (0x00506F30).
#include "shared/infantry.hpp"
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_coord_a410f8@@3UCoordStruct@@A=00a410f8
extern CoordStruct unknown_coord_a410f8;
inline void Infantry_Decay_Fear(int &fear)
{
    --fear;
}
void InfantryClass::unknown_506f30()
{
    if (unknown_5bc > 0) {
        if (!Type->Fearless) {
            Infantry_Decay_Fear(unknown_5bc);
        }
        if (unknown_5bc == 0 && unknown_254 == 0 && unknown_slot163()) {
            unknown_254 = Type->Ammo;
        }
        if (unknown_5c3) {
            if (unknown_5bc < 50 && !unknown_5090d0()) {
                unknown_slot311(7, false, false);
            }
        } else if (unknown_5bc >= 50 && !unknown_5090d0()) {
            if (!(House->Unknown_004F52F0() && (unknown_494 != 0 || Locomotor.Checked()->Is_Moving()))
                && !Type->Fraidycat) {
                unknown_slot311(5, false, false);
            }
        }
    }
    if (Type->Fraidycat && unknown_5bc > 50 && !unknown_5090d0() && !unknown_7a) {
        if (!Locomotor.Checked()->Is_Moving() && unknown_494 == 0) {
            unknown_slot87(unknown_coord_a410f8, true, false);
        }
    }
}
