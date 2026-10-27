// void HouseClass::Silo_Redraw_Check(int tiberium, int capacity) (0x004E5460)
// Redraws the storage buildings when the fill level (in steps) changed.
#include "shared/techno.hpp"
#include "shared/house_views.hpp"

void HouseClass::Silo_Redraw_Check(int tiberium, int capacity)
{
    int old_level = 0;
    if (capacity != 0) {
        old_level = (int)((double)tiberium / capacity * 4.0 + 0.5);
    }
    int level = 0;
    if (Capacity != 0) {
        level = (int)(Tiberium.Get_Total_Amount() / Capacity * 4.0 + 0.5);
    }
    if (old_level != level) {
        int count = Buildings.Count();
        for (int index = 0; index < count; index++) {
            UnknownBuildingView *building = (UnknownBuildingView *)Buildings[index];
            if (building != 0 && !building->unknown_76 &&
                ((UnknownBuildingTypeView *)building->Type)->unknown_1348) {
                building->unknown_slot71(2);
            }
        }
    }
}
