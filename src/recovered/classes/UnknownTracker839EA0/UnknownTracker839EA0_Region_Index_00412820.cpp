#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"
// Map a cell to one of the tracker's twenty by twenty spatial bins.
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
int UnknownTracker839EA0::Region_Index_00412820(Cell cell)
{
    int x=cell.X<0 ? 0 : cell.X;
    int y=cell.Y<0 ? 0 : cell.Y;
    int column=19<x/(Map.unknown_128/20) ? 19 : x/(Map.unknown_128/20);
    y/=Map.unknown_12c/20;
    y=y>19 ? 19 : y;
    return column+y*20;
}
