// @ref ??_E?$VectorClass@VRect@@@@UAEPAXI@Z=0058ed40
// @ref ??8?$VectorClass@VRect@@@@UBE_NABV0@@Z=0058e530
// @ref ?Resize@?$VectorClass@VRect@@@@UAE_NHPBVRect@@@Z=0058e5a0
// @ref ?Clear@?$VectorClass@VRect@@@@UAEXXZ=0058e690
// @ref ?ID@?$VectorClass@VRect@@@@UAEHABVRect@@@Z=0058e6c0
// @ref ?ID@?$VectorClass@VRect@@@@UAEHPBVRect@@@Z=0058e720
// @ref ?Fetch@?$VectorClass@VRect@@@@UBE?AVRect@@H@Z=0058dde0
// @ref ??_E?$DynamicVectorClass@VRect@@@@UAEPAXI@Z=0058ed90
// @ref ?Resize@?$DynamicVectorClass@VRect@@@@UAE_NHPBVRect@@@Z=0058e740
// @ref ?Clear@?$DynamicVectorClass@VRect@@@@UAEXXZ=0058dd90
// @ref ?ID@?$DynamicVectorClass@VRect@@@@UAEHABVRect@@@Z=0058e830
// @ref ?ID@?$DynamicVectorClass@VRect@@@@UAEHPBVRect@@@Z=0058ddc0
#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/random2.hpp"
extern Random2Class unknown_map_random_a705c0;

extern double const unknown_random_scale_7a5dd0,unknown_chunk_floor_7a5ed0;
// @ref ?unknown_chunk_scale_7a10f8@@=007a10f8
// @ref ?unknown_chunk_floor_7a5ed0@@=007a5ed0
// @ref ?unknown_0057c0d0@UnknownMapGenerator@@=0057c0d0
// @ref ?unknown_0057d3a0@UnknownMapGenerator@@=0057d3a0
// @ref ??0?$VectorClass@VRect@@@@=0058f260
// @ref ??_7?$VectorClass@VRect@@@@6B@=007a5eb0
// @ref ??_7?$DynamicVectorClass@VRect@@@@6B@=007a5edc
void UnknownMapGenerator::unknown_0057c4f0()
{
    unknown_308=1;
    DynamicVectorClass<Rect> regions;
    unsigned int range=2>SeedOptions.NumPlayers/2?2:SeedOptions.NumPlayers/2;
    double span=(double)range;
    unsigned int selected;
    do {selected=(unsigned int)((unsigned int)unknown_map_random_a705c0()*(1.0/4294967295.0)*span+1.0);} while(selected>range);
    Rect area=Map.MapLocalSize;
    unknown_0057c0d0(&regions,SeedOptions.NumPlayers+selected,area);
    Map.Unknown_0055A550();
    for(CellClass *cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490()) {
        Cell position=cell->MapCoords;
        unknown_map_cells_a70a24[position.Y*unknown_map_cell_side_84e804+position.X].unknown_3c=0;
    }
    while(regions.Count()>0) {
        Rect region=regions[0];
        int count=(int)(((unsigned int)unknown_map_random_a705c0()*unknown_random_scale_7a5dd0*0.05+unknown_chunk_floor_7a5ed0)*(region.Width*region.Height*2));
        Point2D center;
        center.X=region.Width/2+region.Height/2+region.Y+region.X+1;
        center.Y=region.Height/2-region.Width/2-region.X+Map.MapSize.Width+region.Y;
        int attempt=0;
        int result=0;
        while(!result && attempt<10) {
            result=unknown_0057d3a0(count,region,center,true,Cell(center.X,center.Y),0.25,false);
            if(!result)++unknown_308;
            ++attempt;
        }
        regions.Delete(0);
    }
}
