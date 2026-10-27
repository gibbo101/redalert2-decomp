// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/GroundDriveProcess.hpp"
#include "sim/UnitDiscovery.hpp"
#include "sim/FootDestination.hpp"
#include <algorithm>
#include <bit>
#include <functional>
#include <optional>

namespace ra2 {
// Extra Foot/Unit records only. The movement record below is borrowed, never
// mirrored. A target identity denotes an actual Cell supplied by the binding.
struct UnitDestinationState {
    std::uint8_t forced190=0,suspended598=0;
    std::int32_t field490=0;
    const void* target494=nullptr;
    std::array<std::int32_t,3> timer530{},timer558{};
    const void* vectorBuffer=nullptr;
    std::int32_t vectorCapacity=0,vectorCount=0;
    std::uint8_t vectorOwned=0;
};
struct UnitDestinationProfile {
    std::uint8_t typeB1a=0,typeAf5=0,typeAe0=0,isTrain=0,powered=1;
    std::int32_t type3bc=0,passengerCount=0;
    bool passenger0=false,effect25c=false;
    std::uint8_t field5c8=0,disabled1bc=0,disabled1c0=0;
    std::int32_t field5c0=-1,field3fc=0,timer58c=-1,timer594=0;
};
struct UnitDestinationView {
    UnitDestinationState& actor;
    GroundDriveProcessState& drive;
    const UnitDiscoveryActor& mission;
    std::uint32_t& globalReferences;
    std::uint32_t& references;
    // Production already owns these words in its Process/wait records. Bind
    // those owners directly; legacy fixtures retain their existing arrays.
    std::optional<GroundDriveTimerView> retry530={},wait558={};
    // Optional host command notification at the actual target store. This is
    // metadata only; it must not query or alter the borrowed simulation owners.
    std::function<void(const void*)> targetStore={};
    GroundDriveTimerView retryTimer()const{
        return retry530.value_or(GroundDriveTimerView{actor.timer530[0],actor.timer530[1],actor.timer530[2]});
    }
    GroundDriveTimerView waitTimer()const{
        return wait558.value_or(GroundDriveTimerView{actor.timer558[0],actor.timer558[1],actor.timer558[2]});
    }
};
struct UnitDestinationServices {
    // The joined comparison binds actual Cell center/floor and coordinate-map
    // lookup. The kernel has no copied Cell, renderer or asset ownership.
    std::function<Coord(const void*)> coordinates;
    std::function<std::uint32_t(Coord)> cellFlags;
    // Disposal is a named supplied service, not recovered heap destruction.
    std::function<void(const void*)> dispose;
    std::function<int(const void*)> targetId;
    std::function<void(char,int,int,std::int64_t)> trace;
};
struct UnitDestinationInputs {
    int tick=0,temporaryPadding=0,delay=0;
    Coord empty{};
    double stopScale=0.;
};
using UnsupportedUnitDestination=UnsupportedFootDestination;

namespace unit_destination_detail {
inline void event(const UnitDestinationServices& s,char c,int a,int b,std::int64_t v){
    if(s.trace)s.trace(c,a,b,v);
}
inline void store(const UnitDestinationServices& s,char c,int off,int size,std::int64_t v){event(s,c,off,size,v);}
inline std::uint32_t word(int v){return std::bit_cast<std::uint32_t>(v);}
inline int id(const UnitDestinationServices& s,const void* p){
    if(!p)return 0;
    if(!s.targetId)throw std::invalid_argument("Missing destination target identity binding");
    return s.targetId(p);
}
// Actual ordinary successful QI/GetClassID lifetime. Global count changes before
// the atomic instance count. C++ exception cleanup is native safety only.
class Interface : public foot_destination_detail::Interface {
public:
    Interface(UnitDestinationView& v,const UnitDestinationServices& s):
        foot_destination_detail::Interface({v.globalReferences,v.references},s.trace){}
};
inline void clearVector(UnitDestinationState& a,const UnitDestinationServices& s){
    a.vectorCount=0;store(s,'a',0x488,4,0);
    if(a.vectorBuffer&&a.vectorOwned){
        if(!s.dispose)throw std::invalid_argument("Missing destination vector disposal");
        s.dispose(a.vectorBuffer);a.vectorBuffer=nullptr;store(s,'a',0x47c,4,0);
    }
    a.vectorOwned=0;store(s,'a',0x485,1,0);
    a.vectorCapacity=0;store(s,'a',0x480,4,0);
}
inline void driveDestination(GroundDriveProcessState& d,Coord p,const UnitDestinationServices& s){
    d.destination.x=p.x;store(s,'d',0x34,4,word(p.x));
    d.destination.y=p.y;store(s,'d',0x38,4,word(p.y));
    d.destination.z=p.z;store(s,'d',0x3c,4,word(p.z));
}
// Shared actual ordinary Drive::Move_To guards and stores. Process's idle
// target branch calls this directly; Foot additionally owns target/timer state.
inline void moveTo(GroundDriveProcessState& d,Coord point,
    const UnitDestinationProfile& p,const UnitDestinationInputs& w,const UnitDestinationServices& s){
    event(s,'m',0,0,0x49fe30);
    event(s,'b',0x324,0,p.field5c0!=-1||p.field3fc>0);
    if(p.field5c0==-1&&p.field3fc<=0){
        int remaining=p.timer594;
        if(p.timer58c!=-1){
            const int elapsed=signed32(std::uint32_t(w.tick)-std::uint32_t(p.timer58c));
            remaining=elapsed>=remaining?0:signed32(std::uint32_t(remaining)-std::uint32_t(elapsed));
        }
        event(s,'b',0x328,0,remaining!=0);
        if(!remaining){
            event(s,'b',0x1bc,0,p.disabled1bc);
            if(!p.disabled1bc){
                event(s,'b',0x1c0,0,p.disabled1c0);
                if(!p.disabled1c0){
                    driveDestination(d,point,s);
                    if(point!=w.empty){
                        if(!s.cellFlags)throw std::invalid_argument("Missing destination map lookup");
                        if(s.cellFlags(point)&0x100u)
                            throw UnsupportedUnitDestination("Destination excludes bridge adjustment");
                    }
                }
            }
        }
    }
}

}

// Complete Foot SetDestination in the ordinary Unit/Drive profile, including
// actual command guards. Special classes, attached effects and trains excluded.
// Calls do not install paths or replace queue tails. Unwired; see recovery note.
inline void setOrdinaryFootDestination(UnitDestinationView v,const void* target,
    const UnitDestinationProfile& p,const UnitDestinationInputs& w,const UnitDestinationServices& s){
    using namespace unit_destination_detail;
    auto& a=v.actor;auto& d=v.drive;
    if(p.isTrain||p.effect25c)throw UnsupportedUnitDestination("Destination excludes trains/attached effects");
    FootDestinationServices services;
    services.coordinates=s.coordinates;services.targetId=s.targetId;
    services.targetStore=v.targetStore;services.trace=s.trace;
    services.kind=[](){return 1;};services.tick=[&](){return w.tick;};services.delay=[&](){return w.delay;};
    services.moveTo=[&](Coord point){moveTo(d,point,p,w,s);};
    services.stop=[&](){
        event(s,'m',0,0,0x49fef0);
        if(d.movement.head!=w.empty)event(s,'T',0,0,0);
        d.percentage=d.percentage<w.stopScale?d.percentage:w.stopScale;
        store(s,'d',0x50,8,std::bit_cast<std::int64_t>(d.percentage));
        driveDestination(d,w.empty,s);
    };
    const auto retry=v.retryTimer(),wait=v.waitTimer();
    setOrdinaryFootDestination({a.field490,a.target494,a.suspended598,d.movement.reached5a1,
        {retry.start,retry.padding,retry.remaining},{wait.start,wait.padding,wait.remaining},
        {v.globalReferences,v.references}},target,w.temporaryPadding,services);
}

// Complete Unit root restricted to ordinary powered Cell/null targets and
// missions other than 7/16. Unsupported transport/building/special
// locomotor branches are explicit refusals, not supplied-success callbacks.
inline void setOrdinaryUnitDestination(UnitDestinationView v,const void* target,std::uint8_t flag,
    const UnitDestinationProfile& p,const UnitDestinationInputs& w,const UnitDestinationServices& s){
    using namespace unit_destination_detail;
    auto& a=v.actor;auto& d=v.drive;
    if(p.typeB1a||p.typeAf5||p.typeAe0||p.type3bc||p.passengerCount||p.passenger0||p.field5c8||!p.powered)
        throw UnsupportedUnitDestination("Destination excludes special type/passenger/unpowered policies");
    if(target==a.target494&&!a.forced190)return;
    a.forced190=0;store(s,'a',0x190,1,0);
    if(target)event(s,'k',0,0,11);
    const auto mission=[&](){const int m=unitDiscoveryMission(v.mission);event(s,'M',0,0,m);return m;};
    if(mission()==16||v.mission.queuedA0==16)
        throw UnsupportedUnitDestination("Destination mission16 policy unjoined");
    if(mission()==7||v.mission.queuedA0==7)
        throw UnsupportedUnitDestination("Destination mission7 interaction policy unjoined");
    d.route[0]=-1;store(s,'a',0x4d0,4,0xffffffffu);
    if(!target||flag)clearVector(a,s);
    if(target){
        if(flag)event(s,'r',0,0,0); // ordinary Drive +98 returns AL0
        const auto& head=d.movement.head;const auto& location=d.movement.actor.position;
        const bool moving=d.destination!=w.empty||(head!=w.empty&&(head.x!=location.x||head.y!=location.y));
        event(s,'v',0,0,moving);
        if(!moving){Interface retained(v,s);} // ordinary class differs from switch class
    }
    event(s,'P',0,0,p.powered);
    setOrdinaryFootDestination(v,target,p,w,s);
}
}
