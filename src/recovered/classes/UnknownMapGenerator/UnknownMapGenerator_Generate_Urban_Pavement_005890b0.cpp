#include "shared/unknown_map_generator.hpp"
#include "shared/rect.hpp"
#include "shared/tileset_index.hpp"
#include "shared/random2.hpp"
extern Random2Class unknown_map_random_a705c0;
// @ref ?Can_Place_Misc_Pavement_00589320@@=00589320
// @ref __real@8@3fe1c0000000c0000000=007a5f80
unsigned __fastcall Map_Random_Range_005797a0(unsigned minimum,unsigned maximum);
bool __fastcall Can_Place_Misc_Pavement_00589320(Rect const &area);
void __fastcall Place_Tile_Footprint_005883f0(int tile,Cell const &position,int region,int height);
// @ref ?unknown_tileset_a52ef4@@=00a52ef4
void UnknownMapGenerator::Generate_Urban_Pavement_005890b0(DynamicVectorClass<Cell> &cells)
{
    Rect sizes[5]={Rect(0,0,6,4),Rect(0,0,4,6),Rect(0,0,4,4),Rect(0,0,4,2),Rect(0,0,2,4)};
    int count=cells.Count()/50;
    int placed=0;
    for(int tries=0;tries<10*count && placed<count;++tries) {
        unsigned index;
        {
        unsigned maximum=(unsigned)cells.Count()-1;
        double span=(unsigned)(maximum+1);
        do { index=(unsigned)((unsigned)unknown_map_random_a705c0()*span*(1.0/4294967295.0)); } while(index>maximum);
        }
        Cell cell=cells[index];
        int size=0;
        bool fits=false;
        Rect area(cell.X,cell.Y,0,0);
        while(!fits) {
            if(size>=5)break;
            area.Width=sizes[size].Width;
            area.Height=sizes[size].Height;
            if(Can_Place_Misc_Pavement_00589320(area))fits=true;
            ++size;
        }
        if(fits) {
            unsigned variant;
            do { variant=(unsigned)((unsigned)unknown_map_random_a705c0()*(6.0/4294967295.0)); } while(variant>5);
            int tile=variant+unknown_tileset_a52ef4+8;
            for(int y=0;y<area.Height/2;++y) {
                for(int x=0;x<area.Width/2;++x) {
                    Place_Tile_Footprint_005883f0(tile,Cell(area.X+2*x,area.Y+2*y),-1,-1);
                }
            }
            ++placed;
        }
    }
}
