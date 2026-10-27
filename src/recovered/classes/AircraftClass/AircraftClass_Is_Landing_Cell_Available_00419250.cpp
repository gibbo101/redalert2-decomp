// Aircraft landing-cell predicate00419250. Boolean return spelling is a hypothesis.
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_0055A660@MapClass@@QAE_NABVCell@@_N@Z=0055a660
// @ref ?unknown_471660@CellClass@@QBEPAVObjectClass@@ABUPoint2D@@_NPAV2@@Z=00471660
// @ref ?unknown_FootClass_list_00865f38@@3V?$DynamicVectorClass@PAVFootClass@@@@A=00865f38
bool AircraftClass::Is_Landing_Cell_Available_00419250(Cell const &cell, bool allow_self)
{
    if (!Map.Unknown_0055A660(cell, true)) return true;
    if (Type->Spawned) {
        Point2D offset(0, 0);
        TechnoClass *occupant = (TechnoClass *)Map[cell].unknown_471660(offset, false, 0);
        if (occupant) {
            if (occupant->unknown_238) return true;
            if (occupant->unknown_slot32()->Spawned) return true;
        }
    }
    if (Type->AirportBound) return true;
    bool ignore_contact = Type->Carryall && unknown_494 && unknown_494->Kind_Of() == 1;
    CellClass *where = &Map[cell];
    for (int index = 0; index < unknown_FootClass_list_00865f38.Count(); index++) {
        FootClass *foot = unknown_FootClass_list_00865f38[index];
        if (foot && (!ignore_contact || unknown_494 != foot) &&
            (allow_self || foot != this) && !foot->unknown_76 && foot->unknown_74 &&
            (foot->unknown_slot104() == cell || foot->unknown_494 == where)) return false;
    }
    return true;
}
