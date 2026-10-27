// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayPlacement.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
namespace {
template<class F> void refuses(F f){try{f();}catch(const std::invalid_argument&){return;}throw std::runtime_error("Unsupported placement accepted");}
}
int main(){try{
    OverlayTypeInputs type;type.index=102;
    TransientMapOverlay actor;actor.type=&type;
    OverlayPlacementServices s;OverlayPlacementCell cell;
    s.noAttachedAnimation=[]{};s.redraw=[]{};s.cell=[&](auto)->OverlayPlacementCell&{return cell;};
    s.recalculate=[](auto&,int){};s.retire=[](auto& a){a.active=0;};
    for(int index:{0x18,0x19,0xed,0xee,0x7e,0xa7,0x7a,0x7d,0xe9,0xec}){
        type.index=index;refuses([&]{markLoadedMapOverlay(actor,1,s);});
        if(actor.limbo!=1||actor.onMap)throw std::runtime_error("Guard mutated actor");
    }
    type.index=102;
    for(int field=0;field<3;++field){
        type.wall=field==0;type.land=field==1?9:0;type.cellAnim=field==2;
        refuses([&]{unlimboLoadedMapOverlay(actor,{},1,s);});
    }
    type.wall=0;type.land=0;type.cellAnim=0;actor.type=nullptr;
    refuses([&]{unlimboLoadedMapOverlay(actor,{},1,s);});actor.type=&type;
    OverlayTransientRegistry registry;int flag=7;
    refuses([&]{constructLoadedMapOverlay(actor,type,{1,1},{2,2},-1,flag,1,registry,1,s);});
    s.base=[](auto&){};registry.count=1;
    refuses([&]{constructLoadedMapOverlay(actor,type,{1,1},{2,2},-1,flag,1,registry,1,s);});
    registry.count=0;s.grow=[](int){return true;};
    refuses([&]{constructLoadedMapOverlay(actor,type,{1,1},{2,2},-1,flag,1,registry,1,s);});
    s.retire=[](auto&){};
    refuses([&]{unlimboLoadedMapOverlay(actor,{},1,s);});
    std::cout<<"Ordinary overlay type/storage/retirement boundaries: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
