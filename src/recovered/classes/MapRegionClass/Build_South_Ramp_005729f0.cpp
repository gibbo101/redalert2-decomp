#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/tileset_index.hpp"
// @ref ?Is_Rectangle_Clear_00575910@MapRegionClass@@=00575910
// @ref ?unknown_tileset_a6e038@@=00a6e038
// @ref ?unknown_tileset_a6e018@@=00a6e018
// @ref ?unknown_ramp_heights_7e09ec@@=007e09ec
// @ref ?unknown_ramp_shapes_7e0a00@@=007e0a00
extern int unknown_ramp_heights_7e09ec[5];
extern int unknown_ramp_shapes_7e0a00[10];
void __stdcall Assign_Region_To_Rectangle_00575a90(Rect const &,int);
void __fastcall Place_Tile_Footprint_005883f0(int,Cell const &,int,int);
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
bool MapRegionClass::unknown_005729f0(Cell const &first,Cell const &second,int lowRegion)
{
    Rect area(first.X-5,(first.Y<second.Y?first.Y:second.Y)-3,second.X-first.X+9,(first.Y>second.Y?first.Y:second.Y)-(first.Y<second.Y?first.Y:second.Y)+11);
    if(!Is_Rectangle_Clear_00575910(area,lowRegion)) {
        return false;
    }
    int drift=second.Y-first.Y;
    int span=abs(drift);
    int width=second.X-first.X;
    if(span>width-5) {
        return false;
    }
    int half=(width+1)/2+3;
    Assign_Region_To_Rectangle_00575a90(Rect(area.X,first.Y+1,half+2,area.Y+area.Height-first.Y+1),lowRegion);
    Assign_Region_To_Rectangle_00575a90(Rect(second.X-half+3,second.Y+1,half+2,area.Y+area.Height-second.Y+1),lowRegion);
    Mark_Rectangle_00575bf0(Rect(area.X+4,area.Y+2,half-2,first.Y-area.Y-1));
    Mark_Rectangle_00575bf0(Rect(second.X-half+2,area.Y+2,half-1,second.Y-area.Y-1));
    Place_Tile_Footprint_005883f0(unknown_tileset_a6e038,first,lowRegion,unknown_10);
    Place_Tile_Footprint_005883f0(unknown_tileset_a6e038+1,second-Cell(2,0),lowRegion,unknown_10);
    Cell tail(0,0);
    if(drift!=0) {
        int pick=Map_Random_Range_005797a0(0,1);
        Cell bias;
        bias.X=0;
        int down=drift>0;
        bias.Y=drift<0?-1:0;
        if(pick==1) {
            tail+=Cell(span,drift);
        } else {
            bias.X=(second-Cell(span,0)).X-first.X-5;
        }
        for(int forward=0;forward<span;forward++) {
            for(int row=0;row<5;row++) {
                short offset=down?forward:-forward;
                Cell position=Cell(first.X+3,first.Y)+Cell(forward,row)+bias;
                position=Cell(position.X,position.Y+offset);
                CellClass &target=Map[position];
                target.unknown_11b=(char)(unknown_10+unknown_ramp_heights_7e09ec[row]-4);
                target.unknown_11c=(unsigned char)unknown_ramp_shapes_7e0a00[5*down+row];
                target.IsoTileIndex=(unsigned)unknown_tileset_a6e018+target.unknown_11c-1;
                target.unknown_11a=0;
            }
        }
    }
    for(int column=0;column<second.X-first.X-span-5;column++) {
        for(int row=0;row<4;row++) {
            Cell position=Cell(first.X+3,first.Y)+Cell(column,row)+tail;
            Set_Cell_Region_Index_0056e970(position,lowRegion);
            CellClass &target=Map[position];
            target.unknown_11b=(char)(unknown_10-(char)row-1);
            target.unknown_11c=4;
            target.IsoTileIndex=(unsigned)unknown_tileset_a6e018+3u;
            target.unknown_11a=0;
        }
    }
    return true;
}
