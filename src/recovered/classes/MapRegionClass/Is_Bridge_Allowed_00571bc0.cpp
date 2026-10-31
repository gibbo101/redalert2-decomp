#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &cell);
bool MapRegionClass::Is_Bridge_Allowed_00571bc0(Rect const &area) const
{
    int height=Map[Cell(area.X,area.Y)].unknown_11b;
    if(Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X,area.Y)) &&
       Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X+area.Width-1,area.Y)) &&
       Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X,area.Y+area.Height-1)) &&
       Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X+area.Width-1,area.Y+area.Height-1))) {
        for(int y=area.Y;y<area.Y+area.Height+1;++y) {
            for(int x=area.X;x<area.X+area.Width+1;++x) {
                CellClass &cell=Map[Cell(x,y)];
                if(cell.OverlayIndex!=-1)return false;
                if(cell.unknown_11b!=height)return false;
                if(!cell.unknown_47b590() && !cell.unknown_47b7e0())return false;
            }
        }
        return true;
    }
    return false;
}
