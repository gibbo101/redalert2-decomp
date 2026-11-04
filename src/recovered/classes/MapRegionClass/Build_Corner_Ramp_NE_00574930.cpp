// @ref ?Mark_Rectangle_00575bf0@MapRegionClass@@=00575bf0
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/tileset_index.hpp"
// @ref ?Is_Rectangle_Clear_00575910@MapRegionClass@@=00575910
// @ref ?unknown_tileset_a6e038@@=00a6e038
// @ref ?unknown_tileset_a6e018@@=00a6e018
void __stdcall Assign_Region_To_Rectangle_00575a90(Rect const &,int);
void __fastcall Place_Tile_Footprint_005883f0(int,Cell const &,int,int);
// Original thiscall/AL/RET12. Reference operation name is a hypothesis.
bool MapRegionClass::unknown_00574930(Cell const &first,Cell const &second,int region)
{
    int dx=first.X-second.X;
    if(dx>=3) {
        int dy=first.Y-second.Y;
        if(dy>=3) {
            int top=second.Y-7;
            Rect area(second.X-2,top,dx+10,first.Y-second.Y+10);
            if(Is_Rectangle_Clear_00575910(area,region)) {
                Assign_Region_To_Rectangle_00575a90(Rect(area.X,area.Y,area.Width,7),region);
                Assign_Region_To_Rectangle_00575a90(Rect(first.X+1,area.Y,7,area.Height),region);
                Mark_Rectangle_00575bf0(Rect(second.X,second.Y,1,2));
                Mark_Rectangle_00575bf0(Rect(first.X-1,first.Y,2,1));
                Mark_Rectangle_00575bf0(Rect(second.X+1,second.Y+1,first.X-second.X-1,first.Y-second.Y-1));
                Place_Tile_Footprint_005883f0(unknown_tileset_a6e038+2,first-Cell(0,2),region,unknown_10);
                Place_Tile_Footprint_005883f0(unknown_tileset_a6e038+4,second-Cell(0,3),region,unknown_10);
                for(int corner=0;corner<4;++corner) {
                    CellClass &cell=Map[Cell(first.X+corner,second.Y-corner)];
                    cell.unknown_11b=(char)(unknown_10-(char)corner-1);
                    cell.unknown_11c=6;
                    cell.IsoTileIndex=unknown_tileset_a6e018+5;
                    cell.unknown_11a=0;
                }
                for(int east=0;east<4;++east) {
                    for(int y=0;y<first.Y-second.Y+east-3;++y) {
                        CellClass &cell=Map[Cell(first.X+east,first.Y-y-3)];
                        cell.unknown_11b=(char)(unknown_10-(char)east-1);
                        cell.unknown_11c=3;
                        cell.IsoTileIndex=unknown_tileset_a6e018+2;
                        cell.unknown_11a=0;
                    }
                }
                for(int north=0;north<4;++north) {
                    for(int x=0;x<first.X-second.X+north-3;++x) {
                        CellClass &cell=Map[Cell(second.X+x+3,second.Y-north)];
                        cell.unknown_11b=(char)(unknown_10-(char)north-1);
                        cell.unknown_11c=2;
                        cell.IsoTileIndex=unknown_tileset_a6e018+1;
                        cell.unknown_11a=0;
                    }
                }
                return true;
            }
        }
    }
    return false;
}
