// TibSun Plan_Paved_Road: how far a road can run along dir inside rect. Member: ECX is the generator.
#include "shared/coord.hpp"
#include "shared/rect.hpp"
#include "shared/adjacent_cell.hpp"
#include "shared/map_random.hpp"
bool __fastcall Can_Place_Paved_Road_00588a30(Rect const &area,bool overlap,bool end);
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
Cell UnknownMapGenerator::Plan_Paved_Road_00588850(Cell const &cell,Rect const &rect,int dir)
{
    bool south=dir==4;
    Cell wcell=cell;
    int margin_x=0;
    int margin_y=0;
    int margin_width=0;
    int margin_height=0;
    Rect tile_size(0,0,0,0);
    if(dir==2) {
        tile_size=Rect(0,0,1,3);
        margin_y=-3;
        margin_height=6;
    } else {
        tile_size=Rect(0,0,3,1);
        margin_x=-3;
        margin_width=6;
    }
    while(true) {
        Rect const &area=rect;
        if(!(wcell.X<area.X+area.Width+1 && wcell.Y<area.Y+area.Height+1)) {
            break;
        }
        if(!Can_Place_Paved_Road_00588a30(Rect(margin_x+wcell.X,margin_y+wcell.Y,margin_width+tile_size.Width,margin_height+tile_size.Height),south,south)) {
            break;
        }
        wcell=Adjacent_Road_Cell(wcell,dir);
    }
    wcell=Adjacent_Road_Cell(wcell,dir-4);
    int length=wcell.X-cell.X>wcell.Y-cell.Y?wcell.X-cell.X:wcell.Y-cell.Y;
    if(length>6) {
        int shorten=Map_Random_Range_005797a0(0,3);
        while(shorten>0) {
            Cell back=Adjacent_Road_Cell(wcell,dir-4);
            shorten--;
            wcell=back;
        }
    }
    return wcell;
}
