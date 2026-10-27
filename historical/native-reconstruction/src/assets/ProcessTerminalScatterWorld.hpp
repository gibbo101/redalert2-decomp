// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/AdvanceTerminalScatterWorld.hpp"
#include "sim/GroundDriveIdleTarget.hpp"
#include "sim/CellClosestResident.hpp"

namespace ra2 {
// Ordinary Process profile exclusions. Values/initial associations are supplied;
// actual effects behind these special flags and the wake particle stay unjoined.
struct ProcessDriveFlags { std::uint8_t& shortTrack60;std::uint8_t& flag61;std::uint8_t& curve64; };
struct ProcessOrdinaryProfile {
    std::uint8_t flag325=0,flag32d=0;
    bool wakeType=false,effect238=false;
};
struct ProcessPreparationInputs {
    const int& closeEnough;
    int& counter53c;
    // Named supplied pathfinder result/queue output. The caller consumes the
    // actual queue after this callback; it must not run a second Process.
    std::function<bool()> findRoute;
};
// Separate complete Process composition; no runtime adoption. Every child borrows
// this same explicit actor/Drive/map/floor. Binding makes no world queries.
template<class Admission,class Motion>
inline bool processWithTerminalScatter(int mover,int speed,int timerPadding,int heightDivisor,
    const GroundDriveProcessServices& services,const GroundDriveAdvanceAdmissionServices& admission,
    const std::function<bool(std::int16_t,std::int16_t)>& gate,
    const GroundDriveResidentRetry& retry,const GroundDriveMovingWaitServices& waiting,
    std::uint32_t& scratch,BasicCellUnitScatterView<Admission,Motion> world,const CellUnitScatterInputs& input,
    CellNearbySearchInputs nearby,AdvanceTerminalFlags flags,AdvanceTerminalServices effects,
    ProcessDriveFlags driveFlags,const ProcessOrdinaryProfile& profile,const GroundStateStore& actorStore={},
    const GroundStateStore& rampStore={},const ScatterWorldTrace& trace={},
    const NearbyLocationMapTrace& nearbyTrace={},const AdvanceTerminalTrace& terminalTrace={},
    const ProcessPreparationInputs* preparation=nullptr) {
    if(mover<0||std::size_t(mover)>=world.units.size()||!world.units[mover]||
       world.units[mover]->mover!=mover||heightDivisor<=0||profile.flag325||profile.flag32d||profile.wakeType||profile.effect238)
        throw std::invalid_argument("Process requires explicit ordinary actor/effect profile");
    auto& view=*world.units[mover];auto& v=view.unit;auto& d=v.drive;auto& a=v.actor;
    const auto& gateActor=world.admission.gates.objects.at(mover);
    if(gateActor.animation18||gateActor.animation19||view.profile.disabled1bc||view.profile.disabled1c0||
       view.profile.field5c0!=-1||view.profile.field3fc>0||view.profile.timer58c!=-1||view.profile.timer594)
        throw std::invalid_argument("Process preparation requires ordinary unblocked animation/command profile");
    const std::uint8_t* shortTrack=nullptr;
    if constexpr(requires {world.admission.gates.forwardAssignedFallback;}){
        if(world.liveMotion && world.liveMotion->actors.contains(mover) && world.shortTrack.empty())
            shortTrack=&world.liveMotion->actors.at(mover).shortTrack;
    }else if(std::size_t(mover)<world.shortTrack.size())shortTrack=&world.shortTrack[mover];
    if(&driveFlags.shortTrack60!=shortTrack||driveFlags.shortTrack60)
        throw std::invalid_argument("Process requires actual borrowed ordinary Drive flag owner");
    if constexpr(requires {world.admission.gates.forwardAssignedFallback;}){
        const auto& m=world.liveMotion->actors.at(mover);
        if(world.liveMotion->data!=&input.driveData||!world.eligibility5a0.empty()||
           &m.position!=&d.movement.actor.position||&m.destination!=&d.destination||
           &m.head!=&d.movement.head||&m.body!=&d.movement.body||&m.queueHead!=&d.route[0]||
           &m.track!=&d.movement.track||&m.index!=&d.movement.index||
           &m.eligibility5a0!=&d.movement.reached5a0||
           &world.admission.objects.at(mover).target494!=&a.target494)
            throw std::invalid_argument("Process requires actual prepared Drive and target owners");
    }
    if(&v.mission!=&gateActor.mission)
        throw std::invalid_argument("Process split mission owner");
    const auto event=[&](char group,char kind,std::int64_t x=0,std::int64_t y=0,std::int64_t z=0){if(trace)trace(group,kind,x,y,z);};
    const auto binding=[&](const void* target)->const ScatterWorldCellBinding&{
        for(const auto& b:view.bindings)if(b.cell==target)return b;
        throw std::invalid_argument("Process target is not an actual bound Cell");
    };
    UnitDestinationServices destination;
    destination.trace=[&](char k,int x,int y,std::int64_t z){event('d',k,x,y,z);};
    destination.targetId=[&](const void* target){return binding(target).id+1;};
    destination.coordinates=[&](const void* target){
        const auto p=mapCellCenterHeight(view.floor,view.floorHeight,*binding(target).cell);
        event('d','Q',p.x,p.y,p.z);return p;
    };
    destination.cellFlags=[&](Coord p){
        const auto c=services.cell(p);
        if(!c.identity)throw std::invalid_argument("Process Move_To retained null Cell");
        return binding(c.identity).cell->flags;
    };
    destination.dispose=[](const void*){throw UnsupportedUnitDestination("Process owned vector disposal unjoined");};
    if(std::size_t(mover)>=input.destinationPadding.size())throw std::invalid_argument("Process command padding owner missing");
    const UnitDestinationInputs command{input.tick,input.destinationPadding[mover],input.delay,{},input.stopScale};
    GroundDriveIdleTargetServices idle;idle.destination=destination;
    idle.targetKind=[&](const void* target){(void)binding(target);event('i','K',11);return 11;};
    idle.targetWord=[&](const void* target,int axis){const auto& b=binding(target);const auto n=axis?b.cell->position.y:b.cell->position.x;event('i','W',axis,b.id,n);return n;};
    idle.mission414=effects.mission414;
    auto result=GroundDriveProcessResultServices{flags.onMap7d,flags.flag76,flags.flag7a,view.extra.field5b9,
        driveFlags.shortTrack60,driveFlags.flag61,driveFlags.curve64,
        v.retryTimer(),v.waitTimer(), {},{},{},{},{},{},{},{}};
    // Uninitialized Advance frame bytes are an explicit supplied boundary per
    // invocation; only Advance's own low-word/byte stores are recovered here.
    const auto incomingScratch=scratch;
    result.advance=[&](int caller,bool suppress){
        scratch=incomingScratch;
        event('p','C',caller,suppress,0);
        const bool returned=advanceWithTerminalScatter(mover,speed,d.percentage,suppress,services.advance,
            admission,heightDivisor,scratch,world,input,nearby,flags,effects,
            actorStore,trace,nearbyTrace,terminalTrace);
        event('p','c',caller,returned,flags.onMap7d);return returned;
    };
    result.idleTarget=[&]{
        return processOrdinaryIdleTarget(v,view.profile,command,idle)==GroundDriveIdleTargetResult::returnFalse;
    };
    result.mission=[&]{const int mission=unitDiscoveryMission(v.mission);event('p','M',mission);return mission;};
    result.hasTarget=[&]{return a.target494!=nullptr;};
    result.targetKind=[&]{return idle.targetKind(a.target494);};
    result.moveToTarget=[&]{
        const auto p=destination.coordinates(a.target494);
        unit_destination_detail::moveTo(d,p,view.profile,command,destination);
    };
    result.zeroPercentage=[&]{
        auto bits=std::bit_cast<std::uint64_t>(d.instancePercentage)&0xffffffff00000000ull;
        d.instancePercentage=std::bit_cast<double>(bits);event('p','A',0x468,0,0);
        bits=std::bit_cast<std::uint64_t>(d.instancePercentage)&0xffffffffull;
        d.instancePercentage=std::bit_cast<double>(bits);event('p','A',0x46c,0,0);
    };
    result.finishEmptyPreparation=[&]{
        if(!effects.mission414)throw std::invalid_argument("Process preparation mission effect unbound");
        return effects.mission414(0,1)!=0;
    };
    std::optional<GroundDrivePreparationServices> prepared;
    if(preparation){
        if(!preparation->findRoute||view.profile.isTrain)
            throw std::invalid_argument("Preparation requires an explicit route service and ordinary type");
        prepared.emplace(GroundDrivePreparationServices{preparation->closeEnough,heightDivisor,
            preparation->findRoute,{},{},{},{},{},{},{},{}});
        auto& p=*prepared;
        const auto fallback=[&](MapInputPosition q){
            if constexpr(requires {world.admission.gates.forwardAssignedFallback;})
                world.admission.gates.forwardAssignedFallback({q.x,q.y});
            else{
                const auto id=binding(&view.fallback).id;
                world.admission.gates.cells.at(id).point={q.x,q.y};
            }
            event('w','W',std::uint32_t(std::uint16_t(q.x))|(std::uint32_t(std::uint16_t(q.y))<<16));
        };
        // Own the callbacks in the optional service; do not capture temporary
        // local closures by reference after leaving this binding block.
        p.permission=[&,fallback](std::int16_t x,std::int16_t y){
            event('w','N',x,y);MapAttributeLookup map{view.slots,&view.fallback,{},fallback};
            const bool permitted=mapCellPermitted({x,y},true,view.permission,map);
            event('w','n',permitted);return permitted;
        };
        p.resident=[&](const GroundDriveCell& cell,bool elevated){
            const int id=binding(cell.identity).id;event('r','R',id,elevated,-1);
            CellClosestResidentServices s;
            s.head=[&](bool upper){return upper?world.admission.cells.at(id).elevatedHead:world.admission.gates.cells.at(id).head;};
            s.flags=[&](int actor){return std::uint8_t(world.admission.objects.at(actor).flags);};
            s.next=[&](int actor){return int(world.admission.gates.objects.at(actor).next);};
            s.coordinates=[&](int actor){
                if(actor<0||std::size_t(actor)>=world.units.size()||!world.units[actor])
                    throw std::invalid_argument("Preparation resident lacks an actual coordinate owner");
                const auto at=world.units[actor]->unit.drive.movement.actor.position;
                event('r','P',actor,at.x,at.y);event('r','p',actor,at.z);return at;
            };
            s.squareRoot=services.squareRoot;s.memberLimit=world.admission.gates.objects.size();
            const int found=closestCellResident(0,0,elevated,-1,s);event('r','r',found);return found;
        };
        p.allied=[&](int actor){return movement_gate_policy::movementGateAllied(gateActor.owner,actor,world.admission.gates);};
        p.passengers=[&]{return view.profile.passengerCount>0&&view.profile.passenger0;};
        p.flags=[&](const GroundDriveCell& c){return binding(c.identity).cell->flags;};
        p.scatter=[&](const GroundDriveCell& c,std::uint8_t elevated){
            const int id=binding(c.identity).id;event('r','S',id,elevated);
            scatterCellUnitsWithNearbyOnMap(id,{},1,1,elevated,world,input,nearby,trace,nearbyTrace);
        };
        p.setCounter=[&]{preparation->counter53c=10;if(actorStore)actorStore(0x53c,10);};
        p.closeTarget=[&]{
            if(a.vectorCount==0){setOrdinaryUnitDestination(v,nullptr,1,view.profile,command,destination);return false;}
            a.field490=0;event('d','a',0x490,4,0);a.target494=nullptr;event('d','a',0x494,4,0);
            if(v.targetStore)v.targetStore(nullptr);
            if(!effects.mission414)throw std::invalid_argument("Preparation mission effect unbound");
            return effects.mission414(0,1)!=0;
        };
        result.preparation=&p;
    }
    auto joined=services;
    joined.noRoute=[&]{services.noRoute();setOrdinaryUnitDestination(v,nullptr,1,view.profile,command,destination);};
    auto joinedWaiting=waiting;
    joinedWaiting.failedRoute=[&](int option){waiting.failedRoute(option);setOrdinaryUnitDestination(v,nullptr,1,view.profile,command,destination);};
    const GroundDriveAdmissionServices checked{admission.check,services.advance.driveStore};
    return processResultOrdinaryGroundDrive(d,input.driveData,speed,input.tick,timerPadding,
        joined,gate,checked,retry,joinedWaiting,result,actorStore,rampStore);
}
}
