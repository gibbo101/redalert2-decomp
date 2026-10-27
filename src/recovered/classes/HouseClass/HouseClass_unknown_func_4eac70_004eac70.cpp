// void HouseClass::unknown_func_4eac70(TechnoClass *techno) (0x004EAC70)
// Raises the counter of 0x004EAB10 for the kind a building's type names
// at +0xC44.
#include "shared/techno.hpp"
#include "shared/house_views.hpp"

void HouseClass::unknown_func_4eac70(TechnoClass *techno)
{
    if (techno->Kind_Of() == 6) {
        TechnoTypeClass *type = techno->unknown_slot32();
        int *value = unknown_func_4eab10(((UnknownBuildingTypeView *)((UnknownBuildingView *)techno)->Type)->unknown_c44,
                                         type != 0 && type->Naval);
        if (value != 0) {
            (*value)++;
        }
    }
}
