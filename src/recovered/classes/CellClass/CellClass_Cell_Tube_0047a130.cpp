// Cell tube lookup: typed existing ECX fastcall ABI; member/free spelling remains a hypothesis.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/map_cell.hpp"
#include "shared/vector_class.hpp"
class TubeClass;
extern DynamicVectorClass<TubeClass *> unknown_TubeClass_list_008661c8;
// @ref ?unknown_TubeClass_list_008661c8@@=008661c8
TubeClass *__fastcall Cell_Tube_0047a130(CellClass const *cell)
{
    short index=cell->unknown_116;
    if (index>=0 && index<unknown_TubeClass_list_008661c8.Count()) return unknown_TubeClass_list_008661c8[index];
    return 0;
}
