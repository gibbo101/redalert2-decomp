#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/tileset_index.hpp"
// Name follows reference hypothesis; original receiver, AL result and RET12 verified.
// @ref ?Is_Rectangle_Clear_00575910@MapRegionClass@@=00575910
// @ref ?Mark_Rectangle_00575bf0@MapRegionClass@@=00575bf0
// @ref ?unknown_tileset_a6e038@@=00a6e038
// @ref ?unknown_tileset_a6e018@@=00a6e018
void __stdcall Assign_Region_To_Rectangle_00575a90(Rect const &,int);
void __fastcall Place_Tile_Footprint_005883f0(int,Cell const &,int,int);
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &);

bool MapRegionClass::unknown_005753f0(Cell const &first,Cell const &second,int region)
{
    int dx=second.X-first.X;
    if(dx>=3) {
        int dy=second.Y-first.Y;
        if(dy>=3) {
            int top=first.Y-4;
            Rect area(first.X-7,top,dx+10,second.Y-first.Y+10);
            if(Is_Rectangle_Clear_00575910(area,region)) {
                Assign_Region_To_Rectangle_00575a90(Rect(area.X,area.Y,7,area.Height),region);
                Assign_Region_To_Rectangle_00575a90(Rect(area.X,second.Y+1,area.Width,7),region);
                Mark_Rectangle_00575bf0(Rect(first.X,first.Y,2,1));
                Mark_Rectangle_00575bf0(Rect(second.X,second.Y-1,1,2));
                Mark_Rectangle_00575bf0(Rect(first.X+1,first.Y+1,second.X-first.X-1,second.Y-first.Y-1));
                Place_Tile_Footprint_005883f0(unknown_tileset_a6e038+7,first-Cell(3,0),region,unknown_10);
                Place_Tile_Footprint_005883f0(unknown_tileset_a6e038+1,second-Cell(2,0),region,unknown_10);
                for(int corner=0;corner<4;++corner) {
                    CellClass &cell=Map[Cell(first.X-corner,second.Y+corner)];
                    cell.unknown_11b=(char)(unknown_10-(char)corner-1);
                    cell.unknown_11c=8;
                    cell.IsoTileIndex=unknown_tileset_a6e018+7;
                    cell.unknown_11a=0;
                }
                for(int west=0;west<4;++west) {
                    for(int y=0;y<second.Y-first.Y+west-3;++y) {
                        CellClass &cell=Map[Cell(first.X-west,first.Y+y+3)];
                        cell.unknown_11b=(char)(unknown_10-(char)west-1);
                        cell.unknown_11c=1;
                        cell.IsoTileIndex=unknown_tileset_a6e018;
                        cell.unknown_11a=0;
                    }
                }
                for(int south=0;south<4;++south) {
                    for(int x=0;x<second.X-first.X+south-3;++x) {
                        CellClass &cell=Map[Cell(second.X-x-3,second.Y+south)];
                        cell.unknown_11b=(char)(unknown_10-(char)south-1);
                        cell.unknown_11c=4;
                        cell.IsoTileIndex=unknown_tileset_a6e018+3;
                        cell.unknown_11a=0;
                    }
                }
                return true;
            }
        }
    }
    return false;
}

