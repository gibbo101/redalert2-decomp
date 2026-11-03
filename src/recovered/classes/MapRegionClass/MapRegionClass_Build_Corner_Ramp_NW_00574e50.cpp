#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/tileset_index.hpp"
// @ref ?Is_Rectangle_Clear_00575910@MapRegionClass@@=00575910
// @ref ?unknown_tileset_a6e038@@=00a6e038
// @ref ?unknown_tileset_a6e018@@=00a6e018
void __stdcall Assign_Region_To_Rectangle_00575a90(Rect const &,int);
void __fastcall Place_Tile_Footprint_005883f0(int,Cell const &,int,int);
// First is the eastern endpoint, second the southern endpoint. ECXowner/RET12/AL.
bool MapRegionClass::unknown_00574e50(Cell const &first,Cell const &second,int region)
{
    int dx=first.X-second.X;
    if(dx>=3) {
        int dy=second.Y-first.Y;
        if(dy>=3) {
            Rect area(second.X-7,first.Y-7,dx+10,dy+10);
            if(Is_Rectangle_Clear_00575910(area,region)) {
                Assign_Region_To_Rectangle_00575a90(Rect(area.X,area.Y,area.Width,7),region);
                Assign_Region_To_Rectangle_00575a90(Rect(area.X,area.Y,7,area.Height),region);
                Mark_Rectangle_00575bf0(Rect(first.X,first.Y,1,2));
                Mark_Rectangle_00575bf0(Rect(second.X,second.Y,2,1));
                Mark_Rectangle_00575bf0(Rect(second.X+1,first.Y+1,first.X-second.X-1,second.Y-first.Y-1));
                Place_Tile_Footprint_005883f0(unknown_tileset_a6e038+5,first-Cell(2,3),region,unknown_10);
                Place_Tile_Footprint_005883f0(unknown_tileset_a6e038+6,first-Cell(1,1),region,unknown_10);
                Place_Tile_Footprint_005883f0(unknown_tileset_a6e038+8,second-Cell(3,2),region,unknown_10);
                Place_Tile_Footprint_005883f0(unknown_tileset_a6e038+9,second-Cell(1,1),region,unknown_10);
                for(int corner=0;corner<4;++corner) {
                    CellClass &cell=Map[Cell(second.X-corner,first.Y-corner)];
                    cell.unknown_11b=(char)(unknown_10-(char)corner-1);
                    cell.unknown_11c=5;
                    cell.IsoTileIndex=unknown_tileset_a6e018+4;
                    cell.unknown_11a=0;
                }
                for(int north=0;north<4;++north) {
                    for(int x=0;x<first.X-second.X+north-3;++x) {
                        CellClass &cell=Map[Cell(first.X-x-3,first.Y-north)];
                        cell.unknown_11b=(char)(unknown_10-(char)north-1);
                        cell.unknown_11c=2;
                        cell.IsoTileIndex=unknown_tileset_a6e018+1;
                        cell.unknown_11a=0;
                    }
                }
                for(int west=0;west<4;++west) {
                    for(int y=0;y<second.Y-first.Y+west-3;++y) {
                        CellClass &cell=Map[Cell(second.X-west,second.Y-y-3)];
                        cell.unknown_11b=(char)(unknown_10-(char)west-1);
                        cell.unknown_11c=1;
                        cell.IsoTileIndex=unknown_tileset_a6e018;
                        cell.unknown_11a=0;
                    }
                }
                return true;
            }
        }
    }
    return false;
}
