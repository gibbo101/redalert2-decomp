#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/tileset_index.hpp"
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &cell);
// @ref ?unknown_tileset_a6dd0c@@=00a6dd0c
// @ref ?unknown_47b940@CellClass@@=0047b940
// @ref ?unknown_47b880@CellClass@@=0047b880
// @ref ?unknown_47b590@CellClass@@=0047b590
// @ref ?unknown_47b860@CellClass@@=0047b860
bool __fastcall Can_Place_Paved_Road_Junction_00588ec0(Rect &area)
{
    if(Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X,area.Y)) &&
       Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X+area.Width-1,area.Y)) &&
       Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X,area.Y+area.Height-1)) &&
       Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X+area.Width-1,area.Y+area.Height-1))) {
        for(int y=area.Y;y<area.Y+3;++y) {
            for(int x=area.X;x<area.X+3;++x) {
                CellClass &cell=Map[Cell(x,y)];
                if((cell.IsoTileIndex<unknown_tileset_a6dd0c || cell.IsoTileIndex>unknown_tileset_a6dd0c+1) && !cell.unknown_47b940()) return false;
            }
        }
        for(int x=area.X;x<area.X+3;++x) {
            int y=area.Y+3;
            CellClass &cell=Map[Cell(x,y)];
            if(!cell.unknown_47b880() && !cell.unknown_47b590() && !cell.unknown_47b860()) return false;
        }
        return true;
    }
    return false;
}
