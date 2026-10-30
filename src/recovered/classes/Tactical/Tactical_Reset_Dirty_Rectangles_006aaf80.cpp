// void Tactical::Reset_Dirty_Rectangles() (0x006AAF80): deletes the dirty areas
// (TacticalLists::DirtyAreas) one by one from the front (TibSun Tactical::Reset_Dirty_Rectangles).
#include "shared/tactical.hpp"
#include "shared/tactical_lists.hpp"
// @ref ?DirtyAreas@TacticalLists@@2V?$DynamicVectorClass@UDirtyAreaStruct@@@@A=00abe5b0

void Tactical::Reset_Dirty_Rectangles()
{
    while (TacticalLists::DirtyAreas.Count() > 0) {
        TacticalLists::DirtyAreas.Delete(0);
    }
}
