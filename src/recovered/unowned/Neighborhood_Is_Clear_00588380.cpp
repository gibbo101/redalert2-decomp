// Packed coordinate ECX and AL-only result; freefastcall/constreference/bool/name are source hypotheses.
#include "shared/coord.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
bool __fastcall Unknown_Cell_Predicate_0047b5e0(CellClass *cell);
// @ref ?Unknown_Cell_Predicate_0047b5e0@@=0047b5e0
bool __fastcall Neighborhood_Is_Clear_00588380(Cell const &center)
{
    int centerY=center.Y;
    int top=centerY-7;
    int centerX=center.X;
    int right=centerX+7;
    int bottom=centerY+7;
    for(int x=centerX-7;x<right;++x) {
        for(int y=top;y<bottom;++y) {
            Cell position((short)x,(short)y);
            if(Unknown_Cell_Predicate_0047b5e0(&Map[position]))return false;
        }
    }
    return true;
}
