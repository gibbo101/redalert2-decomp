// Decorative pavement operation/name hypothesis; physical ECX rectangle, AL result, plain RET.
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/tileset_index.hpp"
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &cell);
// @ref ?unknown_tileset_a52ef4@@=00a52ef4
bool __fastcall Can_Place_Misc_Pavement_00589320(Rect const &area)
{
    if(Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X,area.Y)) &&
       Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X+area.Width-1,area.Y)) &&
       Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X,area.Y+area.Height-1)) &&
       Generation_Cell_In_Bounds_0058da10(XY_Cell(area.X+area.Width-1,area.Y+area.Height-1))) {
        for(int y=area.Y;y<area.Y+area.Height;++y) {
            for(int x=area.X;x<area.X+area.Width;++x) {
                CellClass &cell=Map[Cell(x,y)];
                int tile=cell.IsoTileIndex;
                if(!cell.unknown_47b880() && (tile<unknown_tileset_a52ef4 || tile>unknown_tileset_a52ef4+7))return false;
                if(cell.OccupierPtr)return false;
            }
        }
        return true;
    }
    return false;
}
