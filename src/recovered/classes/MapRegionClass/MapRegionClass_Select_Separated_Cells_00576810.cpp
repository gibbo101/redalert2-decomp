// R109-supported original MapRegion receiver and borrowed/owned Cell-vector contracts.
#include "shared/map_region.hpp"
#include "shared/map_seed.hpp"
#include "shared/fast_math.hpp"
// @ref ?MapSeed@@3VMapSeedClass@@A=00a6fd68
// @ref ?unknown_map_cells_a70a24@@3PAUUnknownMapGenerationCell@@A=00a70a24
// @ref ?unknown_map_cell_side_84e804@@3HA=0084e804
extern double const unknown_separation_scale_7a5e18;
// @ref ?unknown_separation_scale_7a5e18@@3NB=007a5e18
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref ??0?$VectorClass@VCell@@@@QAE@IPBVCell@@@Z=0042d4a0
// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
// @ref ??_G?$VectorClass@VCell@@@@UAEPAXI@Z=0042d390
// @ref ??_E?$VectorClass@VCell@@@@UAEPAXI@Z=0042d390
// @ref ??_G?$DynamicVectorClass@VCell@@@@UAEPAXI@Z=0042d3e0
// @ref ??_E?$DynamicVectorClass@VCell@@@@UAEPAXI@Z=0042d3e0
// @ref ??8?$VectorClass@VCell@@@@UBE_NABV0@@Z=0042ce10
// @ref ?Resize@?$VectorClass@VCell@@@@UAE_NHPBVCell@@@Z=0042cee0
// @ref ?Resize@?$DynamicVectorClass@VCell@@@@UAE_NHPBVCell@@@Z=0042d050
// @ref ?Clear@?$VectorClass@VCell@@@@UAEXXZ=0042cfb0
// @ref ?Clear@?$DynamicVectorClass@VCell@@@@UAEXXZ=0042cc10
// @ref ?ID@?$VectorClass@VCell@@@@UAEHABVCell@@@Z=0042cfe0
// @ref ?ID@?$VectorClass@VCell@@@@UAEHPBVCell@@@Z=0042d030
// @ref ?ID@?$DynamicVectorClass@VCell@@@@UAEHABVCell@@@Z=0042d120
// @ref ?ID@?$DynamicVectorClass@VCell@@@@UAEHPBVCell@@@Z=0042cc40
// @ref ?Fetch@?$VectorClass@VCell@@@@UBE?AVCell@@H@Z=0042cc60
DynamicVectorClass<Cell> *MapRegionClass::Select_Separated_Cells_00576810(DynamicVectorClass<Cell> const &candidates)
{
    double scaling=(double)MapSeed.TiberiumLayout;
    int assigned=unknown_20;
    scaling*=0.01;
    double best=-1.0;
    int first=-1;
    scaling*=unknown_separation_scale_7a5e18;
    int wanted=(int)((scaling/(double)MapSeed.NumPlayers+2.0)*assigned);
    if(assigned==0 && candidates.Count()>0)wanted=candidates.Count();
    if(wanted>candidates.Count() || wanted==0) {
        if(assigned==0)return 0;
        wanted=candidates.Count();
    }
    DynamicVectorClass<Cell> *selected=new DynamicVectorClass<Cell>;
    int i;
    for(i=0;i<(int)((unsigned int)candidates.Count()-1u);i++) {
        Cell a=candidates[i];
        int regionA;
            if(!unknown_map_cells_a70a24)regionA=-1;
            else regionA=unknown_map_cells_a70a24[(int)((unsigned int)a.Y*(unsigned int)unknown_map_cell_side_84e804+(unsigned int)a.X)].RegionIndex;
        for(int j=i+1;j<candidates.Count();j++) {
            Cell b=candidates[j];
            int dx=(int)a.X-b.X,dy=(int)a.Y-b.Y;
            int regionB;
            if(!unknown_map_cells_a70a24)regionB=-1;
            else regionB=unknown_map_cells_a70a24[(int)((unsigned int)b.Y*(unsigned int)unknown_map_cell_side_84e804+(unsigned int)b.X)].RegionIndex;
            int square=(int)((unsigned int)dx*(unsigned int)dx+(unsigned int)dy*(unsigned int)dy);
            double distance=(double)Fast_Sqrt((double)square)+(double)(regionB!=regionA ? 20 : 0);
            if(j && distance>best) { best=distance;first=i; }
        }
    }
    if(first!=-1)selected->Add(candidates[first]);
    else if(candidates.Count()!=0) { selected->Add(candidates[0]);return selected; }
    while(selected->Count()<wanted) {
        best=-1.0;
        int next=-1;
        for(i=0;i<candidates.Count();i++) {
            Cell a=candidates[i];
            int regionA;
            if(!unknown_map_cells_a70a24)regionA=-1;
            else regionA=unknown_map_cells_a70a24[(int)((unsigned int)a.Y*(unsigned int)unknown_map_cell_side_84e804+(unsigned int)a.X)].RegionIndex;
            double nearest=9999999.0;
            for(int j=0;j<selected->Count();j++) {
                Cell b=(*selected)[j];
                int dx=(int)a.X-b.X,dy=(int)a.Y-b.Y;
                int regionB;
            if(!unknown_map_cells_a70a24)regionB=-1;
            else regionB=unknown_map_cells_a70a24[(int)((unsigned int)b.Y*(unsigned int)unknown_map_cell_side_84e804+(unsigned int)b.X)].RegionIndex;
                int square=(int)((unsigned int)dx*(unsigned int)dx+(unsigned int)dy*(unsigned int)dy);
                double distance=(double)Fast_Sqrt((double)square)+(double)(regionB!=regionA ? 20 : 0);
                if(distance<nearest)nearest=distance;
            }
            if(nearest>best) { best=nearest;next=i; }
        }
        selected->Add(candidates[next]);
    }
    return selected;
}
