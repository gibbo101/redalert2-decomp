// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/UnitDiscovery.hpp"
#include <stdexcept>
namespace ra2 {
std::uint8_t discoveryHouseControlled(const UnitDiscoveryHouse& h,int mode){
    return mode?h.human134:std::uint8_t(h.human134||h.control135);
}
int unitDiscoveryMission(const UnitDiscoveryActor& a){return a.mission98==-1?a.queuedA0:a.mission98;}
void queueUnitDiscoveryMission(UnitDiscoveryActor& a,int requested,const UnitDiscoveryStore& write){
    if((a.mission98==28&&requested==5)||a.mission98==19)return;
    if(requested!=-1&&(a.mission98!=requested||(a.queuedA0!=-1&&a.queuedA0!=requested))){
        a.queuedA0=requested;if(write)write(0,0xa0,std::uint32_t(requested));
        a.queuedA4=0;if(write)write(0,0xa4,0);
    }
}
bool discoverUnit(UnitDiscoveryActor& a,int discoverer,UnitDiscoveryWorld& w){
    const auto event=[&](char k,int v){if(w.trace)w.trace(k,v);};
    const auto store=[&](int subject,int off,std::uint32_t v){if(w.store)w.store(subject,off,v);};
    event('d',discoverer);
    if(discoverer==w.currentHouse){if(a.current373)return false;}
    else {
        if(a.other374)return false;
        a.other374=1;store(0,0x374,1);
    }
    event('b',discoverer);if(discoverer==-1)return false;
    event('h',discoverer);
    if(!discoveryHouseControlled(w.houses.at(discoverer),w.mode)){
        event('g',0);
        if(unitDiscoveryMission(a)==14){event('q',15);queueUnitDiscoveryMission(a,15,w.store);}
    }
    if(discoverer==w.currentHouse){
        a.current373=1;store(0,0x373,1);
        w.houses.at(a.owner).field5668=1;store(a.owner+1,0x5668,1);
        w.houses.at(a.owner).field5669=1;store(a.owner+1,0x5669,1);
        if(!a.field372){
            if(!w.loading&&a.hasTag){
                if(!w.tagEvent)throw std::invalid_argument("Reached missing Unit discovery Tag service");
                w.tagEvent(w.tagContext);
            }
            // The original rereads Owner after the optional Tag event.
            w.houses.at(a.owner).discovered13c=1;store(a.owner+1,0x13c,1);
        }
    }else{a.other374=1;store(0,0x374,1);}
    return true;
}
}
