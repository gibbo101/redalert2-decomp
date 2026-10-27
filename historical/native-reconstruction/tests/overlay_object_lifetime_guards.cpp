// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayObjectLifetime.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
namespace {
template<class F> void refuses(F f){try{f();}catch(const std::invalid_argument&){return;}throw std::runtime_error("Unsupported Overlay lifetime accepted");}
}
int main(){try{
    TransientMapOverlay actor;OverlayObjectBase base;OverlayLifetimeServices s;
    OverlayTransientRegistry a,b,c,d,queue,overlays;
    base.flags14=0x12345678;
    refuses([&]{constructOverlayObjectBase(actor,base,{},1,1,{&a,&b,&c,nullptr},s);});
    if(base.flags14!=0x12345678)throw std::runtime_error("Invalid base registry mutated actor");
    a.count=1;refuses([&]{constructOverlayObjectBase(actor,base,{},1,1,{&a,&b,&c,&d},s);});a.count=0;
    actor.limbo=0;refuses([&]{retireLoadedOverlayObject(actor,base,1,queue,s);});actor.limbo=1;
    refuses([&]{retireLoadedOverlayObject(actor,base,1,queue,s);});
    std::vector<TransientMapOverlay*> actors{&actor};
    refuses([&]{cleanupLoadedOverlayObjects(actors,queue,overlays,s);});
    s.expired=[](unsigned){};s.baseDestroy=[](unsigned){};s.free=[](unsigned){};
    queue.slots={2};queue.count=1;
    refuses([&]{cleanupLoadedOverlayObjects(actors,queue,overlays,s);});
    queue.slots={1};actor.limbo=0;
    refuses([&]{cleanupLoadedOverlayObjects(actors,queue,overlays,s);});actor.limbo=1;
    base.links30[2]=1;
    refuses([&]{retireLoadedOverlayObject(actor,base,1,queue,s);});base.links30[2]=0;
    queue.count=0;queue.slots.clear();s.grow=[](unsigned,int){return 1u;};
    refuses([&]{retireLoadedOverlayObject(actor,base,1,queue,s);});
    std::cout<<"Overlay base registry/limbo/destruction/heap boundaries: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
