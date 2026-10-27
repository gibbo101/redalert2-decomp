// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/Redraw.hpp"
#include "render/StaticRedraw.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace ra2;
int main(){try{
    for(int mode=0;mode<4;++mode){
        DirtyRegionQueue q;int events=0,calls=0;
        if(mode==0)q.count=-1;
        if(mode==1)q.count=1;
        if(mode==2){q.slots.push_back({{0,0,1,1},0});q.count=1;q.ownsAllocation=true;q.growth=std::numeric_limits<int>::max();}
        DirtyRegionGrowth grow=mode==3?DirtyRegionGrowth{}:DirtyRegionGrowth([&](auto&,int){++calls;return false;});
        bool refused=false;
        try{registerDirtyRegion(q,{{10,10,1,1},0},grow,[&](auto){++events;});}
        catch(const std::invalid_argument&){refused=true;}
        if(!refused||events||calls)throw std::runtime_error("Native dirty-region domain guard failed");
    }
    for(int mode=0;mode<3;++mode){
        std::vector<TerrainCellPoint> cells(mode==0?801:0);std::vector<DirtyRegion> dirty(mode==1?129:0);
        if(mode==2)cells.push_back({32767,0});
        bool refused=false;int calls=0;
        try{requestStaticTerrainRedraw(cells,dirty,{},{},{},{},1,0.1,[&](auto,const auto&,const auto&){++calls;});}
        catch(const std::invalid_argument&){refused=true;}
        if(!refused||calls)throw std::runtime_error("Static redraw domain guard failed before callbacks");
    }
    std::cout<<"Dirty-region and static request native domain guards: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
