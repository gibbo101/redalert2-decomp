// TubeClass::~TubeClass() (0x006EF2D0)
// Forgets the tube: clears the entry cell's tube index when it is this tube's, leaves the list.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/tube.hpp"
#include "shared/vector_class.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/tube_data.hpp"
// @ref ?unknown_TubeClass_list_008661c8@@3V?$DynamicVectorClass@PAVTubeClass@@@@A=008661c8
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Detach_This_From_All@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ??1AbstractClass@@UAE@XZ=0040ff90
// @ref ??_7TubeClass@@6BIPersistStream@@@=007adb38
// @ref ??_7TubeClass@@6BIRTTITypeInfo@@@=007adb1c
// @ref ??_7TubeClass@@6BINoticeSink@@@=007adb14
// @ref ??_7TubeClass@@6BINoticeSource@@@=007adb0c

TubeClass::~TubeClass()
{
    Detach_This_From_All(this, true);
    CellClass *cell = &Map[EnterCell];
    if (cell != 0) {
        int index = Tube_Index(this);
        if (cell->unknown_116 == index) {
            cell->unknown_116 = -1;
        }
    }
    unknown_TubeClass_list_008661c8.Delete(this);
}
