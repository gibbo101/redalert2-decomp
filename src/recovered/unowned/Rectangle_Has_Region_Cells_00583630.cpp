#include "shared/map_region.hpp"
#include "shared/rect.hpp"
// ECX rectangle, EDX region, RET8; first stack DWORD unused, second is required count.
// Bool, const-reference and unused-parameter spelling remain source hypotheses.
// @ref ?unknown_map_cells_a70a24@@=00a70a24
// @ref ?unknown_map_cell_side_84e804@@=0084e804
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &cell);
bool __fastcall Rectangle_Has_Region_Cells_00583630(Rect const &area,int region,int unknown,int required)
{
    Cell origin(area.X,area.Y);
    int count=0;
    for(int y=0;y<area.Height;++y) {
        for(int x=0;x<area.Width;++x) {
            if(Generation_Cell_In_Bounds_0058da10(origin+Cell(x,y))) {
                int index=UnknownMapGenerationCell::Get_Region(origin+Cell(x,y));
                if(index==region && ++count>=required)return true;
            }
        }
    }
    return false;
}
