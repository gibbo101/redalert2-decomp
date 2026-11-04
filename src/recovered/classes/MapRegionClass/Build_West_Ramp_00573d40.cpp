// West-facing straight ramp (TibSun Build_West_Ramp): no named height, `tail+=` and `bias+=` in place (RA2_POINT_ADD_IN_PLACE in the unit's first source).
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/tileset_index.hpp"
// @ref ?Is_Rectangle_Clear_00575910@MapRegionClass@@=00575910
// @ref ?unknown_tileset_a6e038@@=00a6e038
// @ref ?unknown_tileset_a6e018@@=00a6e018
// @ref ?unknown_ramp_heights_7e0aa0@@=007e0aa0
// @ref ?unknown_ramp_shapes_7e0ab4@@=007e0ab4
extern int unknown_ramp_heights_7e0aa0[5];
extern int unknown_ramp_shapes_7e0ab4[10];
void __stdcall Assign_Region_To_Rectangle_00575a90(Rect const &,int);
void __fastcall Place_Tile_Footprint_005883f0(int,Cell const &,int,int);
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
bool MapRegionClass::unknown_00573d40(Cell const &first,Cell const &second,int lowRegion)
{
    Rect area((first.X<second.X?first.X:second.X)-7,first.Y-4,(first.X>second.X?first.X:second.X)-(first.X<second.X?first.X:second.X)+11,second.Y-first.Y+9);
    if(!Is_Rectangle_Clear_00575910(area,lowRegion)) {
        return false;
    }
    int drift=second.X-first.X;
    int span=abs(drift);
    if(span>second.Y-first.Y-5) {
        return false;
    }
    int half=(second.Y-first.Y+1)/2+2;
    Assign_Region_To_Rectangle_00575a90(Rect(area.X,area.Y,first.X-area.X,half+2),lowRegion);
    Assign_Region_To_Rectangle_00575a90(Rect(area.X,second.Y-half+3,second.X-area.X,half+2),lowRegion);
    Mark_Rectangle_00575bf0(Rect(first.X,first.Y,area.X+area.Width-first.X-1,half-1));
    Mark_Rectangle_00575bf0(Rect(second.X,second.Y-half+3,area.X+area.Width-second.X-1,half-2));
    Place_Tile_Footprint_005883f0(unknown_tileset_a6e038+7,first-Cell(3,0),lowRegion,unknown_10);
    Place_Tile_Footprint_005883f0(unknown_tileset_a6e038+8,second-Cell(3,2),lowRegion,unknown_10);
    Place_Tile_Footprint_005883f0(unknown_tileset_a6e038+9,second-Cell(1,1),lowRegion,unknown_10);
    Cell tail(0,0);
    if(drift!=0) {
        int pick=Map_Random_Range_005797a0(0,1);
        int down=drift>0;
        Cell bias(drift>0,0);
        if(pick==1) {
            tail+=Cell(drift,span);
        } else {
            bias+=Cell(0,second.Y-(short)span-first.Y-5);
        }
        for(int forward=0;forward<span;forward++) {
            for(int row=0;row<5;row++) {
                short offset=down?forward:-forward;
                Cell position=Cell(first.X,first.Y+3)+Cell(-row,forward)+bias;
                position=Cell(position.X+offset,position.Y);
                CellClass &target=Map[position];
                target.unknown_11b=(char)(unknown_10+unknown_ramp_heights_7e0aa0[row]-4);
                target.unknown_11c=(unsigned char)unknown_ramp_shapes_7e0ab4[5*down+row];
                target.IsoTileIndex=(unsigned)unknown_tileset_a6e018+target.unknown_11c-1;
                target.unknown_11a=0;
            }
        }
    }
    for(int column=0;column<second.Y-first.Y-span-5;column++) {
        for(int row=0;row<4;row++) {
            Cell position=Cell(first.X,first.Y+3)+Cell(-row,column)+tail;
            Set_Cell_Region_Index_0056e970(position,lowRegion);
            CellClass &target=Map[position];
            target.unknown_11b=(char)(unknown_10-(char)row-1);
            target.unknown_11c=1;
            target.IsoTileIndex=(unsigned)unknown_tileset_a6e018;
            target.unknown_11a=0;
        }
    }
    return true;
}
