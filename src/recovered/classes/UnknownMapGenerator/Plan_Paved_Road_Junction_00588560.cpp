// TibSun Plan_Paved_Road_Junction: first paved tile along dir, then the first spot a junction fits, walked back a random distance. Member: ECX is the generator.
#include "shared/coord.hpp"
#include "shared/rect.hpp"
#include "shared/adjacent_cell.hpp"
#include "shared/map_random.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/tileset_index.hpp"
// @ref ?unknown_tileset_a6e0e0@@=00a6e0e0
extern int unknown_tileset_a6e0e0;
bool __fastcall Can_Place_Paved_Road_00588a30(Rect const &area,bool overlap,bool end);
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
inline Cell Adjacent_Road_Cell(Cell const &cell,int facing)
{
    return cell+AdjacentCell[facing&7];
}
Cell UnknownMapGenerator::Plan_Paved_Road_Junction_00588560(Cell const &cell,Rect const &rect,int dir)
{
    Cell wcell=cell;
    Rect const &area=rect;
    int margin_x=0;
    int margin_y=0;
    int margin_width=0;
    int margin_height=0;
    Rect tile_size(0,0,0,0);
    bool south=dir==4;
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
        if(!(wcell.X<area.X+area.Width && wcell.Y<area.Y+area.Height)) {
            return Cell(0,0);
        }
        if(Map[wcell].IsoTileIndex==(unsigned)unknown_tileset_a6e0e0) {
            break;
        }
        wcell=Adjacent_Road_Cell(wcell,dir);
    }
    while(true) {
        if(!(wcell.X<area.X+area.Width && wcell.Y<area.Y+area.Height)) {
            return Cell(0,0);
        }
        if(Can_Place_Paved_Road_00588a30(Rect(margin_x+wcell.X,margin_y+wcell.Y,margin_width+tile_size.Width,margin_height+tile_size.Height),south,south)) {
            break;
        }
        wcell=Adjacent_Road_Cell(wcell,dir);
    }
    int length=wcell.Y-cell.Y>wcell.X-cell.X?wcell.Y-cell.Y:wcell.X-cell.X;
    if(length>0) {
        int shorten=Map_Random_Range_005797a0(0,length);
        while(shorten>0) {
            Cell back=Adjacent_Road_Cell(wcell,dir-4);
            if(!Can_Place_Paved_Road_00588a30(Rect(margin_x+back.X,margin_y+back.Y,margin_width+tile_size.Width,margin_height+tile_size.Height),false,false)) {
                break;
            }
            wcell=back;
            shorten--;
        }
    }
    return wcell;
}
