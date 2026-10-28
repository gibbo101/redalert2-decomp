// TubeClass::TubeClass(Cell const &enter, int facing) (0x006EF1D0)
// (the first Tube source: its vector macros are the unit's, the others' come after the first include)
// A tunnel from the entry cell: no directions yet, listed and indexed by the entry cell.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/tube.hpp"
#include "shared/vector_class.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/tube_data.hpp"
// @ref ?unknown_TubeClass_list_008661c8@@3V?$DynamicVectorClass@PAVTubeClass@@@@A=008661c8
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??_7TubeClass@@6BIPersistStream@@@=007adb38
// @ref ??_7TubeClass@@6BIRTTITypeInfo@@@=007adb1c
// @ref ??_7TubeClass@@6BINoticeSink@@@=007adb14
// @ref ??_7TubeClass@@6BINoticeSource@@@=007adb0c

TubeClass::TubeClass(Cell const &enter, int facing) : EnterCell(enter), ExitCell(enter), Facing(facing), unknown_1c0(0)
{
    Create_ID();
    for (int index = 0; index < 100; index++) {
        Directions[index] = -1;
    }
    unknown_TubeClass_list_008661c8.Add(this);
    if (enter.X != 0 || enter.Y != 0) {
        CellClass &cell = Map[enter];
        int index = Tube_Index(this);
        cell.unknown_116 = index;
    }
}
