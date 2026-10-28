// void TubeClass::Update_All_Indexes() (0x006EF400)
// Numbers the tubes whose entry cell can be entered and deletes the rest.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/tube.hpp"
#include "shared/vector_class.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
// @ref ?unknown_TubeClass_list_008661c8@@3V?$DynamicVectorClass@PAVTubeClass@@@@A=008661c8
// @ref ?unknown_479cc0@CellClass@@QBE_NXZ=00479cc0
// @ref ?Map@@3VMouseClass@@A=008324e0

void TubeClass::Update_All_Indexes()
{
    short index = -1;
    int count = unknown_TubeClass_list_008661c8.Count();
    for (int position = 0; position < count; position++) {
        TubeClass *tube = unknown_TubeClass_list_008661c8[position];
        CellClass &cell = Map[tube->EnterCell];
        if (!cell.unknown_479cc0()) {
            delete tube;
            count--;
            cell.unknown_116 = -1;
            position--;
        } else {
            index++;
            cell.unknown_116 = index;
        }
    }
}
