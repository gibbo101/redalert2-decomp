// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayPlacement.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
namespace {
template<class F> void refuses(F f){try{f();}catch(const std::invalid_argument&){return;}throw std::runtime_error("Unsupported wall placement accepted");}
}
int main(){try{
    OverlayTypeInputs type;type.index=203;type.wall=1;TransientMapOverlay actor;actor.type=&type;
    LoadedWallPlacementServices wall;
    for(int index:{0x18,0x19,0xed,0xee,0x7e,0xa7}){type.index=index;refuses([&]{markLoadedMapWall(actor,1,wall);});}
    type.index=203;
    for(int field=0;field<5;++field){
        actor.type=field==0?nullptr:&type;type.wall=field==1?0:1;type.cellAnim=field==2?1:0;type.land=field==3?9:0;wall.loading=field==4?0:1;
        refuses([&]{markLoadedMapWall(actor,1,wall);});
        if(!actor.limbo||actor.onMap||actor.redraw)throw std::runtime_error("Wall type guard mutated actor");
    }
    actor.type=&type;type.wall=1;type.cellAnim=0;type.land=0;wall.loading=1;
    refuses([&]{markLoadedMapWall(actor,1,wall);});
    std::cout<<"Loaded wall type/loading/service boundaries: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
