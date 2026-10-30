#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &cell);
// ECX rectangle, DL first flag, stack second flag; AL predicate/RET4.
bool __fastcall Can_Place_Paved_Road_00588a30(Rect const &area,bool allowFirst,bool allowSecond)
{
    if(Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X,area.Y)) &&
       Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X+area.Width-1,area.Y)) &&
       Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X,area.Y+area.Height-1)) &&
       Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X+area.Width-1,area.Y+area.Height-1))) {
        for(int y=area.Y;y<area.Y+area.Height;++y) {
            for(int x=area.X;x<area.X+area.Width;++x) {
                CellClass &cell=Map[Cell(x,y)];
                if(cell.unknown_47b8e0()) {
                    if(!allowFirst)return false;
                } else if(cell.unknown_47b900()) {
                    if(!allowSecond)return false;
                } else if(!cell.unknown_47b590() && !cell.unknown_47b860() && !cell.unknown_47b880()) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}
