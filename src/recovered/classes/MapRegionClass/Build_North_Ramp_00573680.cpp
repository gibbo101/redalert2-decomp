#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/tileset_index.hpp"
// @ref ?Is_Rectangle_Clear_00575910@MapRegionClass@@=00575910
// @ref ?unknown_tileset_a6e038@@=00a6e038
// @ref ?unknown_tileset_a6e018@@=00a6e018
// @ref ?unknown_ramp_heights_7e0a64@@=007e0a64
// @ref ?unknown_ramp_shapes_7e0a78@@=007e0a78
extern int unknown_ramp_heights_7e0a64[5];
extern int unknown_ramp_shapes_7e0a78[10];
void __stdcall Assign_Region_To_Rectangle_00575a90(Rect const &,int);
void __fastcall Place_Tile_Footprint_005883f0(int,Cell const &,int,int);
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
bool MapRegionClass::unknown_00573680(Cell const &first,Cell const &second,int lowRegion)
{
    Rect area(second.X-4,(first.Y<second.Y?first.Y:second.Y)-7,first.X-second.X+8,(first.Y>second.Y?first.Y:second.Y)-(first.Y<second.Y?first.Y:second.Y)+11);
    if(!Is_Rectangle_Clear_00575910(area,lowRegion)) {
        return false;
    }
    int drift=second.Y-first.Y;
    int span=abs(drift);
    int width=first.X-second.X;
    if(span>width-5) {
        return false;
    }
    int half=(width+1)/2+3;
    Assign_Region_To_Rectangle_00575a90(Rect(area.X,area.Y,half+2,second.Y-area.Y),lowRegion);
    Assign_Region_To_Rectangle_00575a90(Rect(first.X-half+2,area.Y,half+3,first.Y-area.Y),lowRegion);
    Mark_Rectangle_00575bf0(Rect(second.X,second.Y,half-2,area.Y+area.Height-second.Y-2));
    Mark_Rectangle_00575bf0(Rect(first.X-half+2,first.Y,half-1,area.Y+area.Height-first.Y-2));
    Place_Tile_Footprint_005883f0(unknown_tileset_a6e038+4,second-Cell(0,3),lowRegion,unknown_10);
    Place_Tile_Footprint_005883f0(unknown_tileset_a6e038+5,first-Cell(2,3),lowRegion,unknown_10);
    Place_Tile_Footprint_005883f0(unknown_tileset_a6e038+6,first-Cell(1,1),lowRegion,unknown_10);
    Cell tail(0,0);
    if(drift!=0) {
        int pick=Map_Random_Range_005797a0(0,1);
        Cell bias;
        bias.X=0;
        int down=drift>0;
        bias.Y=drift<0;
        if(pick==1) {
            tail+=Cell(span,-drift);
        } else {
            bias.X=(first-Cell(span,0)).X-second.X-5;
        }
        for(int forward=0;forward<span;forward++) {
            for(int row=0;row<5;row++) {
                short offset=down?-forward:forward;
                Cell position=Cell(second.X+3,second.Y)+Cell(forward,-row)+bias;
                position=Cell(position.X,position.Y+offset);
                CellClass &target=Map[position];
                target.unknown_11b=(char)(unknown_10+unknown_ramp_heights_7e0a64[row]-4);
                target.unknown_11c=(unsigned char)unknown_ramp_shapes_7e0a78[5*down+row];
                target.IsoTileIndex=(unsigned)unknown_tileset_a6e018+target.unknown_11c-1;
                target.unknown_11a=0;
            }
        }
    }
    for(int column=0;column<first.X-second.X-span-5;column++) {
        for(int row=0;row<4;row++) {
            Cell position=Cell(second.X+3,second.Y)+Cell(column,-row)+tail;
            Set_Cell_Region_Index_0056e970(position,lowRegion);
            CellClass &target=Map[position];
            target.unknown_11b=(char)(unknown_10-(char)row-1);
            target.unknown_11c=2;
            target.IsoTileIndex=(unsigned)unknown_tileset_a6e018+1u;
            target.unknown_11a=0;
        }
    }
    return true;
}
