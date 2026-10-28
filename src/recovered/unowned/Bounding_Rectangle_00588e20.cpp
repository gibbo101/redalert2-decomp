// Inclusive cell-vector bounds; free fastcall/hidden-result spelling is a hypothesis.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/coord.hpp"
#include "shared/rect.hpp"
#include "shared/vector_class.hpp"
Rect __fastcall Bounding_Rectangle_00588e20(DynamicVectorClass<Cell> const &cells)
{
    Cell minimum(999,999),maximum(0,0);
    for(int i=cells.Count()-1;i>=0;i--) {
        Cell point=cells[i];
        if(point.X<minimum.X)minimum.X=point.X;
        if(point.Y<minimum.Y)minimum.Y=point.Y;
        if(point.X>maximum.X)maximum.X=point.X;
        if(point.Y>maximum.Y)maximum.Y=point.Y;
    }
    return Rect(minimum.X,minimum.Y,(int)maximum.X-minimum.X+1,(int)maximum.Y-minimum.Y+1);
}
