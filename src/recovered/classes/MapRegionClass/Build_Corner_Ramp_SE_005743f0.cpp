// Southeast corner ramp (TibSun Build_Corner_Ramp_SE); the only row with no caller in the unit: Connect_Regions_With_Ramp calls NE twice.
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/tileset_index.hpp"
// @ref ?Is_Rectangle_Clear_00575910@MapRegionClass@@=00575910
// @ref ?unknown_tileset_a6e038@@=00a6e038
// @ref ?unknown_tileset_a6e018@@=00a6e018
void __stdcall Assign_Region_To_Rectangle_00575a90(Rect const &area,int region);
void __fastcall Place_Tile_Footprint_005883f0(int tile,Cell const &position,int region,int height);
bool MapRegionClass::unknown_005743f0(Cell const &first,Cell const &second,int lowRegion)
{
    int width=second.X-first.X;
    if(width>=3) {
        int height=first.Y-second.Y;
        if(height>=3) {
            
            int top=second.Y-2;
            Rect area(first.X-2,top,width+10,first.Y-second.Y+10);
            if(Is_Rectangle_Clear_00575910(area,lowRegion)) {
                Assign_Region_To_Rectangle_00575a90(Rect(area.X,first.Y+1,area.Width,7),lowRegion);
                Assign_Region_To_Rectangle_00575a90(Rect(second.X+1,area.Y,7,area.Height),lowRegion);
                Mark_Rectangle_00575bf0(Rect(first.X,first.Y-1,1,2));
                // The second X is intentional: original574672 loads both origins from second.X.
                Mark_Rectangle_00575bf0(Rect(second.X-1,second.X,2,1));
                Mark_Rectangle_00575bf0(Rect(first.X+1,second.Y+1,second.X-first.X-1,first.Y-second.Y-1));
                Place_Tile_Footprint_005883f0(unknown_tileset_a6e038,first,lowRegion,unknown_10);
                Place_Tile_Footprint_005883f0((int)((unsigned)unknown_tileset_a6e038+3u),second,lowRegion,unknown_10);
                for(int step=0;step<4;++step) {
                    CellClass &target=Map[Cell(second.X+step,first.Y+step)];
                    target.unknown_11b=(char)(unknown_10-(char)step-1);
                    target.unknown_11c=7;
                    target.IsoTileIndex=(unsigned)unknown_tileset_a6e018+6u;
                    target.unknown_11a=0;
                }
                for(int row=0;row<4;++row) {
                    for(int column=0;column<second.X-first.X+row-3;++column) {
                        CellClass &target=Map[Cell(first.X+column+3,first.Y+row)];
                        target.unknown_11b=(char)(unknown_10-(char)row-1);
                        target.unknown_11c=4;
                        target.IsoTileIndex=(unsigned)unknown_tileset_a6e018+3u;
                        target.unknown_11a=0;
                    }
                }
                for(int column=0;column<4;++column) {
                    for(int row=0;row<first.Y-second.Y+column-3;++row) {
                        CellClass &target=Map[Cell(second.X+column,second.Y+row+3)];
                        target.unknown_11b=(char)(unknown_10-(char)column-1);
                        target.unknown_11c=3;
                        target.IsoTileIndex=(unsigned)unknown_tileset_a6e018+2u;
                        target.unknown_11a=0;
                    }
                }
                return true;
            }
        }
    }
    return false;
}
