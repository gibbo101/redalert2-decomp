// Changes the type indexed by Data.Value and refreshes the house tech state, native006B27E0.
#include "shared/taction.hpp"
#include "shared/house.hpp"
#include "shared/techno_type.hpp"
bool TActionClass::Set_Type_Tech_Level_006b27e0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    TechnoTypes[Data.Value]->TechLevel = unknown_48;
    if (house != 0) house->unknown_144 = true;
    return true;
}


