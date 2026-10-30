#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &cell);
// ECX rectangle, DL overlap flag; AL predicate, plain RET.
// The signed byte at cell+0x11b is the elevation hypothesis.
bool __fastcall Can_Place_Paved_Road_End_00588c20(Rect const &area,bool allowRoad)
{
    if(Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X,area.Y)) &&
       Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X+area.Width-1,area.Y)) &&
       Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X,area.Y+area.Height-1)) &&
       Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X+area.Width-1,area.Y+area.Height-1))) {
        int originX=area.X;
        int originY=area.Y;
        int height=Map[Cell(originX,originY)].unknown_11b;
        for(int y=area.Y;y<area.Y+area.Height;++y) {
            for(int x=area.X;x<area.X+area.Width;++x) {
                CellClass &cell=Map[Cell(x,y)];
                if(cell.unknown_11b!=height)return false;
                if(cell.unknown_47b8e0() || cell.unknown_47b900()) {
                    if(!allowRoad)return false;
                } else if(!cell.unknown_47b590() && !cell.unknown_47b860() && !cell.unknown_47b880()) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}
