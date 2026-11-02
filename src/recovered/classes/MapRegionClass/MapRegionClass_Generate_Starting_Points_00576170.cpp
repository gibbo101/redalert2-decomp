// @ref __real@8@3fe0c0000000c0000000=007a5e00
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/id_source.hpp"
#include "shared/map_random.hpp"
bool __fastcall Can_Place_Paved_Road_00588a30(Rect const &area,bool allowFirst,bool allowSecond);
// @ref ??0?$VectorClass@VCell@@@@=0042d4a0
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
void MapRegionClass::Generate_Starting_Points_00576170(int firstWaypoint)
{
    Rect bounds=Map.MapLocalSize;
    bounds.X+=4;
    bounds.Y+=4;
    bounds.Width-=8;
    bounds.Height-=8;
    DynamicVectorClass<Cell> candidates;
    unsigned int extra;
    do {extra=(unsigned int)((unsigned int)unknown_map_random_a705c0()*(3.0/4294967295.0));} while(extra>2);
    int wanted=unknown_20*15+extra;
    for(int attempt=0;candidates.Count()<wanted && attempt<300;++attempt) {
        unsigned int maximum=Cells.Count()-1;
        struct Range {double Span;};
        Range range={(unsigned int)(maximum+1)};
        unsigned int selected;
        do {selected=(unsigned int)((unsigned int)unknown_map_random_a705c0()*range.Span*(1.0/4294967295.0));} while(selected>maximum);
        Cell position=Cells[selected];
        Rect area(position.X-3,position.Y-3,6,6);
        if(Can_Place_Paved_Road_00588a30(area,false,false) && Map.Unknown_0055A840(bounds,position,true))candidates.Add(position);
    }
    DynamicVectorClass<Cell> *layout=Select_Separated_Cells_00576810(candidates);
    if(!layout)return;
    {
        for(int index=0;index<unknown_20;++index) {
            unknown_id_source_a3d290->Set_Waypoint_Location(firstWaypoint+index,(*layout)[index]);
            Map[unknown_id_source_a3d290->Get_Waypoint_Location(firstWaypoint+index)].unknown_140|=4;
        }
        for(index=0;index<unknown_20;++index)layout->Delete(0);
        delete (DynamicVectorClass<Cell> *)unknown_00;
        unknown_00=layout;
    }
}
