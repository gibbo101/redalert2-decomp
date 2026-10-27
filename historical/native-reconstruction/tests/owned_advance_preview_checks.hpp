// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "owned_preview_checks.hpp"
namespace owned_advance_preview {
using namespace ra2;
// Native route/clearance policy checks, separate from original routine evidence.
// Neither the clone nor its observers receive source renderer storage.
inline void check(OwnedUnitWorld& world,const DriveData& data,int tick,int speed,int mover,
    const std::function<std::string()>& renderer){
    using owned_check::require;
    const auto references=[&]{
        auto refs=owned_check::associations(world);const auto& c=world.context();
        const auto put=[&](const auto* p){refs.push_back(reinterpret_cast<std::uintptr_t>(p));};
        put(c.map->cells.data());put(c.map->slots.data());put(c.map->table.data());put(c.map->attributes.data());
        put(c.map->buffer4.data());put(c.map->buffer10.data());put(&c.map->floor);
        for(int id:{0,1}){auto a=world.actor(id);put(&a.turret);put(&a.commands);put(&a.wait);}
        return refs;
    };
    const auto live=owned_check::snapshot(world),render=renderer();const auto refs=references();
    int checks=0,seven=0;
    const auto unchanged=[&]{
        require(owned_check::snapshot(world)==live&&references()==refs,"Advance full preview changed live values/associations");
        require(renderer()==render,"Advance full preview changed warm renderer");++checks;
    };
    const OwnedUnitMovePolicy policy{{{speed,speed},{7,7}},512};
    Bytes mask(262144,1);const OwnedUnitClearance clear(mask);
    const auto bind=[&](OwnedUnitWorld& copy){auto calls=owned_check::silentCalls(copy);
        for(auto& c:calls)c.decision=[&](char k,int n){if(k=='D'&&n==7)++seven;};return calls;};
    for(bool append:{false,true}){
        seven=0;
        const auto r=previewOwnedUnitMove(world,mover,append?13:12,append?14:13,append,tick,data.stopScale,policy,clear,bind);
        require(r.status==OwnedUnitMoveStatus::accepted&&r.route&&r.ticks>1&&seven>0,"Complete replacement/append lost actual Advance7/arrival");
        require(r.route->destination.x==cellCenter(append?13:12,append?14:13).x&&r.route->destination.y==cellCenter(append?13:12,append?14:13).y,"Accepted preview returned an advanced target");
        if(append)require(r.route->directions.size()>1&&r.route->directions.front()==4,"Append did not preserve the existing route");
        unchanged();
    }
    seven=0;auto limited=policy;limited.maxTicks=1;
    auto r=previewOwnedUnitMove(world,mover,12,13,false,tick,data.stopScale,limited,clear,bind);
    require(r.status==OwnedUnitMoveStatus::tickLimit&&r.ticks==1&&!r.route&&seven>0,"Advance7 tick limit escaped/failed to run");unchanged();
    mask[13*512+12]=0;seven=0;
    r=previewOwnedUnitMove(world,mover,12,13,false,tick,data.stopScale,policy,OwnedUnitClearance(mask),bind);
    require(r.status==OwnedUnitMoveStatus::blocked&&r.ticks==0&&seven==0,"Immediate clearance advanced");unchanged();
    for(int id:{0,1}){
        mask.assign(262144,1);const auto at=world.actor(id).state.movement.actor.position;
        mask[std::size_t(at.y/256)*512+std::size_t(at.x/256)]=0;
        r=previewOwnedUnitMove(world,mover,14,14,true,tick,data.stopScale,policy,OwnedUnitClearance(mask),bind);
        require(r.status==OwnedUnitMoveStatus::blocked&&r.ticks==0,"Both actors' initial footprints must be checked");unchanged();
    }
    // The other actor's NW route reaches this footprint corner after 23 ticks;
    // the selected curve and its southbound route remain in columns 11..12.
    mask.assign(262144,1);mask[11*512+10]=0;seven=0;
    r=previewOwnedUnitMove(world,mover,12,13,false,tick,data.stopScale,policy,OwnedUnitClearance(mask),bind);
    require(r.status==OwnedUnitMoveStatus::blocked&&r.ticks>1&&seven>0,"Other actor's late clearance did not run after Advance7");unchanged();
    bool fault=false,progressed=false;seven=0;
    const auto failing=[&](OwnedUnitWorld& copy){auto calls=bind(copy);
        const std::array<Coord,2> initial{copy.actor(0).state.movement.actor.position,copy.actor(1).state.movement.actor.position};
        calls[1].driveStore=[&copy,initial,&progressed](int,int){
            if(copy.actor(0).state.movement.actor.position!=initial[0]&&copy.actor(1).state.movement.actor.position!=initial[1]){
                progressed=true;throw std::runtime_error("Advance late preview fault");
            }
        };return calls;};
    try{(void)previewOwnedUnitMove(world,mover,12,13,false,tick,data.stopScale,policy,clear,failing);}
    catch(const std::runtime_error& e){fault=std::string_view(e.what())=="Advance late preview fault";}
    require(fault&&progressed&&seven>0,"Unrelated late fault swallowed or not reached after Advance7");unchanged();
    r=previewOwnedUnitMove(world,mover,512,13,false,tick,data.stopScale,policy,clear,bind);
    require(r.status==OwnedUnitMoveStatus::invalidRoute&&!r.route,"Invalid target accepted");unchanged();
    seven=0;r=previewOwnedUnitMove(world,mover,10,10,true,tick,data.stopScale,policy,clear,bind);
    require(r.status==OwnedUnitMoveStatus::notArrived&&!r.route&&seven>0,"Nonarrival was accepted or lost Advance7");unchanged();
    auto stopped=world.clone();auto& other=stopped->actor(1-mover).state;auto& movement=other.movement;
    movement.body.desired=movement.body.start=movement.body.current(tick);movement.body.duration=0;
    movement.driving=false;movement.head={};other.destination={};other.route.fill(-1);
    const auto stoppedBefore=owned_check::snapshot(*stopped);int six=0;
    const auto observeSix=[&](OwnedUnitWorld& copy){auto calls=owned_check::silentCalls(copy);
        for(auto& c:calls)c.decision=[&](char k,int n){if(k=='D'&&n==6)++six;};return calls;};
    r=previewOwnedUnitMove(*stopped,mover,12,13,false,tick,data.stopScale,policy,clear,observeSix);
    require(r.status==OwnedUnitMoveStatus::unsupportedAdmission&&r.admission==6&&six>0&&owned_check::snapshot(*stopped)==stoppedBefore,"Actual typed Advance6 escaped clone");unchanged();
    for(bool append:{false,true}){
        auto committed=world.clone(),expected=world.clone();const int x=append?13:12,y=append?14:13;
        auto route=OwnedUnitOrders(*expected,data.stopScale).directRoute(mover,x,y,append);
        const auto& services=mover?expected->context().parked->services:expected->context().services;
        route->destination.z=services.advance.ground.floor(route->destination);OwnedUnitOrders(*expected,data.stopScale).order(mover,*route);
        seven=0;r=moveOwnedUnit(*committed,mover,x,y,append,tick,data.stopScale,policy,clear,bind);
        require(r.status==OwnedUnitMoveStatus::accepted&&seven>0&&owned_check::snapshot(*committed)==owned_check::snapshot(*expected),"Accepted move committed preview state/time");unchanged();
        const auto before=owned_check::snapshot(*committed);
        r=moveOwnedUnit(*committed,1-mover,14,14,false,tick,data.stopScale,policy,OwnedUnitClearance(Bytes(262144,0)),bind);
        require(r.status==OwnedUnitMoveStatus::blocked&&owned_check::snapshot(*committed)==before,"Rejected live command mutated source");unchanged();
    }
    for(int invalid=0;invalid<3;++invalid){
        auto bad=policy;if(invalid==0)bad.maxTicks=0;int id=invalid==1?2:mover;
        const auto invalidCalls=[&](OwnedUnitWorld& copy){auto calls=bind(copy);if(invalid==2)calls[1].notify={};return calls;};
        bool refused=false;try{(void)previewOwnedUnitMove(world,id,12,13,false,tick,data.stopScale,bad,clear,invalidCalls);}
        catch(const std::invalid_argument&){refused=true;}
        require(refused,"Invalid Advance preview input/services accepted");unchanged();
    }
    std::cerr<<"Warm full Advance preview actor "<<mover<<": "<<checks<<" isolation checks: PASS\n";
}
}
