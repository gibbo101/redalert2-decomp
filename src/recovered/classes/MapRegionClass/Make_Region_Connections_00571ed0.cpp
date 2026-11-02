#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_map_generator.hpp"
#include "shared/random2.hpp"
#include "shared/map_random.hpp"
// @ref __real@8@3fe5ca000000ca000000=007a5df8
MapRegionClass *__fastcall Find_Map_Region_By_Index_00575ce0(int);
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
extern float const unknown_ramp_attempt_scale_7a5df0;
// @ref ?unknown_ramp_attempt_scale_7a5df0@@=007a5df0
// @ref ?Connect_Regions_With_Bridge_00570bc0@MapRegionClass@@=00570bc0
// @ref ?Connect_Regions_With_Ramp_00572270@MapRegionClass@@=00572270
// Original ECX MapRegion receiver; plain RET. Reference name; unknown fields remain explicit.
void MapRegionClass::Make_Region_Connections_00571ed0()
{
    if(unknown_14) {
        for(int index=0;index<NeighborRegionIndices->Count()-1;++index) {
            MapRegionClass *first=Find_Map_Region_By_Index_00575ce0((*NeighborRegionIndices)[index]);
            if(first->NeighborRegionIndices->Count()>1 || first->CellCount>50) {
                for(int next=index+1;next<NeighborRegionIndices->Count();++next) {
                    MapRegionClass *second=Find_Map_Region_By_Index_00575ce0((*NeighborRegionIndices)[next]);
                    if((second->NeighborRegionIndices->Count()>1 || second->CellCount>50) && !second->unknown_14 &&
                       second->unknown_10==first->unknown_10 && first->unknown_10==unknown_10) {
                        Connect_Regions_With_Bridge_00570bc0(first,second);
                    }
                }
            }
        }
    } else {
        for(int neighbor=0;neighbor<NeighborRegionIndices->Count();++neighbor) {
            MapRegionClass *region=Find_Map_Region_By_Index_00575ce0((*NeighborRegionIndices)[neighbor]);
            if(region->Index>Index && region->unknown_10!=unknown_10) {
                int connected=0;
                int target=((int)Map_Random_Range_005797a0(0,100)<unknown_map_generator_a6fd68.SeedOptions.Accessibility?(int)Map_Random_Range_005797a0(1,2):0)+1;
                int tries=0;
                int higher=region->unknown_10>unknown_10?region->Index:Index;
                int lower=region->unknown_10>unknown_10?Index:region->Index;
                MapRegionClass *upper=Find_Map_Region_By_Index_00575ce0(higher);
                DynamicVectorClass<Cell> *border=upper->Collect_Boundary_Cells_0056ed10();
                while(connected<target && tries<100) {
                    unsigned last=(unsigned)(border->Count()-1);
                    struct Range { double Span; } range={(unsigned)(last+1)};
                    unsigned choice;
                    do {
                        choice=(unsigned)((unsigned)unknown_map_random_a705c0()*range.Span*(1.0/4294967295.0));
                    } while(choice>last);
                    Cell position=(*border)[choice];
                    if(Map.Unknown_0055A660(position,true)) {
                        connected+=upper->Connect_Regions_With_Ramp_00572270(position,lower,(float)tries*unknown_ramp_attempt_scale_7a5df0)?1:0;
                    }
                    ++tries;
                }
                if(connected==0)unknown_1b=false;
                delete border;
            }
        }
    }
}
