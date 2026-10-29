// void HouseClass::unknown_4ea970(TechnoClass *techno) (0x004EA970)
// A techno joins the house's counts (AircraftClass::Init; the counterpart of
// 0x004EA800): sets its +0x324 flag and, unless its type is flagged (+0x202),
// raises the count of its kind (+0x228 units, +0x230 buildings, +0x238,
// +0x234; an unoccupied naval vehicle also +0x22C), the per-type counter
// (+0x5420..+0x5450) and the kind's tracker (+0x268..+0x1A80) of its type's
// array index.
// @ref ?Unknown_0070C490@UnknownHouseTracker@@QAEXH@Z=0070c490
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"

void HouseClass::unknown_4ea970(TechnoClass *techno)
{
    techno->unknown_324 = true;
    if (!techno->unknown_slot32()->unknown_202) {
        switch (techno->Kind_Of()) {
        case 6: {
            if (techno->unknown_slot31()) {
                unknown_228++;
            } else {
                CurBuildings++;
            }
            int index = techno->unknown_slot32()->unknown_slot16();
            unknown_5420.Increment(index);
            unknown_1a80.Unknown_0070C490(index);
            break;
        }
        case 2: {
            unknown_238++;
            int index = techno->unknown_slot32()->unknown_slot16();
            unknown_5450.Increment(index);
            unknown_268.Unknown_0070C490(index);
            break;
        }
        case 15: {
            int index = techno->unknown_slot32()->unknown_slot16();
            unknown_234++;
            unknown_5440.Increment(index);
            unknown_a70.Unknown_0070C490(index);
            break;
        }
        case 1: {
            unknown_228++;
            int index = techno->unknown_slot32()->unknown_slot16();
            unknown_5430.Increment(index);
            unknown_1278.Unknown_0070C490(index);
            if (techno->unknown_slot32()->Naval && techno->unknown_slot32()->Passengers == 0) {
                unknown_22c++;
            }
            break;
        }
        }
    }
}
