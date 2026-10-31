// void DisplayClass::Constrained_Look(CoordStruct const &center, int distance) (0x0049E1D0)
// The player's discovered technos of layer 2 within their sight range plus
// distance of center look around (slot 70); with the rules' +0x142B allied
// buildings do too (TibSun DisplayClass::Constrained_Look).
#include "shared/display.hpp"
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/coord_distance.hpp"
#include "shared/foot.hpp"
// @ref ?Layer@DisplayClass@@2PAVLayerClass@@A=00852578
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?As_Techno@AbstractClass@@QAEPAVTechnoClass@@XZ=0040dc20
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __ftol=0077f110

void DisplayClass::Constrained_Look(CoordStruct const &center, int distance)
{
    for (int index = 0; index < Layer[2].Count(); index++) {
        TechnoClass *techno = Layer[2][index]->As_Techno();
        if (techno != 0) {
            if (techno->House->Unknown_004F52B0()) {
                if (techno->unknown_373 && Coord_Length(center - techno->Center_Coord()) <= techno->unknown_slot32()->Sight * 256 + distance) {
                    techno->unknown_slot70(false, false);
                }
            } else {
                if (techno->Kind_Of() == 6 && Rules->unknown_142b && techno->House->Is_Ally(unknown_player_a35db4)
                    && Coord_Distance(techno->Center_Coord(), center) <= techno->unknown_slot32()->Sight * 256 + distance) {
                    techno->unknown_slot70(false, false);
                }
            }
        }
    }
}
