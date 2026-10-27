// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayPlacement.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
int main(){try{
    OverlayTypeInputs type;type.index=203;type.wall=1;
    TransientMapOverlay actor;actor.type=&type;OverlayTransientRegistry registry;
    LoadedWallPlacementServices s;int flag=7;
    for(unsigned scenario=0;scenario<9;++scenario){
        type.wall=scenario!=0;type.land=scenario==1?9:0;type.cellAnim=scenario==2;
        type.index=scenario>=4?std::array{0x18,0x19,0x7e,0xa7,0xed}[scenario-4]:203;s.loading=scenario==3?0:1;
        bool refused=false;try{constructLoadedMapWall(actor,type,{1,1},{2,2},0,flag,1,registry,1,s);}
        catch(const std::invalid_argument&){refused=true;}
        if(!refused||flag!=7||registry.count||actor.onMap||actor.limbo!=1)throw std::runtime_error("Wall constructor guard mutated state");
    }
    std::cout<<"Loaded wall construction scope guards: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
