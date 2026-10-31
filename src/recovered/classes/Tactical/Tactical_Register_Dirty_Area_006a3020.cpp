// void Tactical::Register_Dirty_Area(Rect area, bool refresh_shroud) (0x006A3020): adds a
// screen area to the dirty areas. An area inside a registered one is dropped
// (unless only it refreshes the shroud), registered areas inside it are removed,
// and otherwise the registered area whose union with it is smallest (and smaller
// than both apart) grows to that union (TibSun Tactical::Register_Dirty_Area).
#include "shared/tactical.hpp"
#include "shared/tactical_lists.hpp"
// @ref ?DirtyAreas@TacticalLists@@2V?$DynamicVectorClass@UDirtyAreaStruct@@@@A=00abe5b0
// @ref ??$Union@VRect@@@@YI?AVRect@@ABV0@0@Z=0045efe0

void Tactical::Register_Dirty_Area(Rect area, bool refresh_shroud)
{
    int best_index = -1;
    int best = 0x7FFFFFFF;

    for (int i = 0; i < TacticalLists::DirtyAreas.Count(); i++) {
        Rect rect = TacticalLists::DirtyAreas[i].Area;
        Rect inter = Intersect(rect, area);
        Rect whole = Union(rect, area);

        if (inter.Is_Valid()) {
            if (inter == area) {
                if (!refresh_shroud || TacticalLists::DirtyAreas[i].unknown_10) {
                    return;
                }
            } else if (inter == rect) {
                if (refresh_shroud || !TacticalLists::DirtyAreas[i].unknown_10) {
                    TacticalLists::DirtyAreas.Delete(i);
                    i--;
                }
            } else {
                int size = whole.Size();
                if (size < (rect.Size() + area.Size()) && size < best) {
                    best = size;
                    best_index = i;
                }
            }
        }
    }

    if (best_index == -1) {
        TacticalLists::DirtyAreas.Add(DirtyAreaStruct(area, refresh_shroud));
    } else {
        TacticalLists::DirtyAreas[best_index] = DirtyAreaStruct(Union(area, TacticalLists::DirtyAreas[best_index].Area), refresh_shroud || TacticalLists::DirtyAreas[best_index].unknown_10);
    }
}
