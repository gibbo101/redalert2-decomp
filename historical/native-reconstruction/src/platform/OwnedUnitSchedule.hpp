// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "platform/OwnedUnitOrders.hpp"

namespace ra2 {
struct OwnedUnitStepInputs {
    std::array<int,2> speed;
    std::array<int,2> timerPadding;
};
// Supplied frame policy, shared by live advancement and discarded previews.
// There is no second actor/Drive state. Named effects must bind this owner;
// observers are read-only and are not retained after the call.
class OwnedUnitSchedule {
    OwnedUnitWorld& world_;
    OwnedUnitOrders orders_;
    bool stepping_=false;
public:
    OwnedUnitSchedule(OwnedUnitWorld& world,double stopScale):world_(world),orders_(world,stopScale){}
    OwnedUnitSchedule(const OwnedUnitSchedule&)=delete;
    OwnedUnitSchedule& operator=(const OwnedUnitSchedule&)=delete;
    static void validate(const OwnedUnitStepInputs& in,const std::array<OwnedUnitWorldCall,2>& calls){
        for(unsigned id=0;id<2;++id){
            if(in.speed[id]<0||in.speed[id]>255)
                throw std::invalid_argument("Owned schedule speed outside the bounded type profile");
            const auto& c=calls[id];
            if(!c.notify||!c.postCell||!c.noRoute||!c.failedRoute)
                throw std::invalid_argument("Owned schedule requires both actors' explicit named services");
        }
    }
    std::array<bool,2> step(int tick,const OwnedUnitStepInputs& in,
        const std::array<OwnedUnitWorldCall,2>& calls,
        const std::function<void(int,bool)>& afterProcess={}){
        if(stepping_)throw std::logic_error("Owned schedule cannot reenter");
        validate(in,calls); // Refuse invalid actor1 services before Process0.
        struct Scope{bool& flag;explicit Scope(bool& f):flag(f){flag=true;}~Scope(){flag=false;}} scope(stepping_);
        std::array<bool,2> result;
        for(unsigned id=0;id<2;++id){
            result[id]=world_.process(int(id),in.speed[id],tick,in.timerPadding[id],calls[id]);
            if(afterProcess)afterProcess(int(id),result[id]);
            for(int displaced:{0,1})orders_.followScatter(displaced);
        }
        for(int id:{0,1})orders_.finishTick(id,tick);
        return result;
    }
};
}
