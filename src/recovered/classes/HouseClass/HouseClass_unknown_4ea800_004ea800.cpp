// void HouseClass::unknown_4ea800(TechnoClass *techno) (0x004EA800)
// A techno leaves the house's counts (AircraftClass/InfantryClass destructors):
// clears its +0x324 flag and, unless its type is flagged (+0x202), lowers the
// count of its kind (+0x228 units/infantry, +0x238, +0x230, +0x234; an
// unoccupied naval vehicle also lowers +0x22C) and the per-type counter
// (+0x5420..+0x5450) of its type's array index.
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"

void HouseClass::unknown_4ea800(TechnoClass *techno)
{
    techno->unknown_324 = false;
    if (!techno->unknown_slot32()->unknown_202) {
        switch (techno->Kind_Of()) {
        case 6:
            if (techno->unknown_slot31()) {
                unknown_228--;
            } else {
                CurBuildings--;
            }
            unknown_5420.Decrement(techno->unknown_slot32()->unknown_slot16());
            break;
        case 2:
            unknown_238--;
            unknown_5450.Decrement(techno->unknown_slot32()->unknown_slot16());
            break;
        case 15:
            unknown_234--;
            unknown_5440.Decrement(techno->unknown_slot32()->unknown_slot16());
            break;
        case 1:
            unknown_228--;
            unknown_5430.Decrement(techno->unknown_slot32()->unknown_slot16());
            if (techno->unknown_slot32()->Naval && techno->unknown_slot32()->Passengers == 0) {
                unknown_22c--;
            }
            break;
        }
    }
}
