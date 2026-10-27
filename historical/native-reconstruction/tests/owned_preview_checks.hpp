// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "platform/OwnedUnitMovePreview.hpp"
#include "owned_world_snapshot.hpp"
#include "render/Lighting.hpp"
#include <iostream>
#include <limits>
namespace owned_check {
using namespace ra2;
inline void require(bool value,const char* message){if(!value)throw std::runtime_error(message);}
inline std::vector<std::uintptr_t> associations(const OwnedUnitWorld& world){
    const auto& c=world.context();std::vector<std::uintptr_t> result;
    const auto put=[&](const auto* p){result.push_back(reinterpret_cast<std::uintptr_t>(p));};
    put(&c);put(c.map.get());put(c.unit.get());put(&c.state);put(&c.parked->state);
    for(auto* p:c.map->table)put(p);for(auto* p:c.map->attributes)put(p);
    return result;
}
inline std::array<OwnedUnitWorldCall,2> silentCalls(OwnedUnitWorld&){
    OwnedUnitWorldCall c;c.notify=[](int){};c.postCell=[]{ };c.noRoute=[]{ };c.failedRoute=[](int){};
    return {c,c};
}
// Native policy/isolation checks are deliberately separate from original results.
// The caller retains warm complete renderer state and draws again afterward.
inline void previewChecks(OwnedUnitWorld& world,const DriveData& data,const RenderData& light,
    int tick,int speed,int mode,const std::function<std::string()>& renderer){
    const auto live=snapshot(world),render=renderer();const auto addresses=associations(world);
    int checks=0;
    const auto unchanged=[&]{
        require(snapshot(world)==live&&associations(world)==addresses,"Preview mutated live simulation values or associations");
        require(renderer()==render,"Preview warmed live actor/type/image/pool/world drawing state");++checks;
    };
    Bytes mask(262144,1);OwnedUnitClearance clear(mask);
    const OwnedUnitMovePolicy policy{{{speed,speed},{7,7}},512};
    if(mode==0){
        for(int invalid=0;invalid<4;++invalid){
            auto bad=policy;auto binding=OwnedUnitPreviewServices(silentCalls);int actor=0;double scale=data.stopScale;
            if(invalid==0)bad.maxTicks=0;
            if(invalid==1)actor=2;
            if(invalid==2)binding=[](OwnedUnitWorld& copy){auto c=silentCalls(copy);c[1].notify={};return c;};
            if(invalid==3)scale=std::numeric_limits<double>::infinity();
            bool refused=false;
            try{(void)previewOwnedUnitMove(world,actor,16,12,false,tick,scale,bad,clear,binding);}
            catch(const std::invalid_argument&){refused=true;}
            require(refused,"Invalid preview input accepted");unchanged();
        }
        auto bridge=world.clone();const auto bridgeTarget=bridge->actor(0).state.destination;
        bridge->context().map->cells[std::size_t(bridge->context().map->slots[std::size_t(bridgeTarget.y/256)*512+std::size_t(bridgeTarget.x/256+1)])].attributes.input.flags|=0x100u;
        const auto bridgeBefore=snapshot(*bridge);
        const auto bridgeResult=previewOwnedUnitMove(*bridge,0,bridgeTarget.x/256+1,bridgeTarget.y/256,false,tick,data.stopScale,policy,clear,silentCalls);
        require(bridgeResult.status==OwnedUnitMoveStatus::unsupportedRoute&&snapshot(*bridge)==bridgeBefore,"Unsupported bridge preview escaped source");unchanged();

        for(int id:{0,1})for(bool append:{false,true}){
            const auto target=world.actor(id).state.destination;
            const auto result=previewOwnedUnitMove(world,id,target.x/256+1,target.y/256,append,tick,data.stopScale,policy,clear,silentCalls);
            require(result.status==OwnedUnitMoveStatus::accepted&&result.route&&result.ticks>1,"Direct/append scheduled preview failed");unchanged();
        }
        const auto target=world.actor(0).state.destination;const int x=target.x/256+1,y=target.y/256;
        auto p=policy;p.maxTicks=1;
        auto result=previewOwnedUnitMove(world,0,x,y,false,tick,data.stopScale,p,clear,silentCalls);
        require(result.status==OwnedUnitMoveStatus::tickLimit&&result.ticks==1&&!result.route,"Tick limit accepted or returned preview state");unchanged();
        mask[std::size_t(y)*512+std::size_t(x)]=0;
        result=previewOwnedUnitMove(world,0,x,y,false,tick,data.stopScale,policy,OwnedUnitClearance(mask),silentCalls);
        require(result.status==OwnedUnitMoveStatus::blocked&&result.ticks==0,"Immediate blocked target advanced");unchanged();
        mask.assign(262144,1);
        // A later Cell in the other actor's unchanged route; the selected actor
        // travels in a different row. This catches selected-only clearance.
        const auto other=world.actor(1).state.destination;
        mask[std::size_t(other.y/256)*512+std::size_t(other.x/256)]=0;
        result=previewOwnedUnitMove(world,0,x,y,false,tick,data.stopScale,policy,OwnedUnitClearance(mask),silentCalls);
        require(result.status==OwnedUnitMoveStatus::blocked&&result.ticks>1,"Other actor's late clearance did not refuse after copy advancement");unchanged();
        result=previewOwnedUnitMove(world,0,512,y,false,tick,data.stopScale,policy,clear,silentCalls);
        require(result.status==OwnedUnitMoveStatus::invalidRoute&&!result.route,"Invalid route accepted");unchanged();
        // Fault only after both clone positions have changed; unrelated faults
        // must escape, without an advanced clone or callbacks escaping with them.
        bool threw=false,progressed=false;
        const auto fault=[&](OwnedUnitWorld& copy){
            auto calls=silentCalls(copy);
            const std::array<Coord,2> initial{copy.actor(0).state.movement.actor.position,copy.actor(1).state.movement.actor.position};
            calls[1].driveStore=[&copy,initial,&progressed](int,int){
                if(copy.actor(0).state.movement.actor.position!=initial[0]&&copy.actor(1).state.movement.actor.position!=initial[1]){
                    progressed=true;throw std::runtime_error("late preview fault");
                }
            };return calls;
        };
        try{(void)previewOwnedUnitMove(world,0,x,y,false,tick,data.stopScale,policy,clear,fault);}
        catch(const std::runtime_error& e){threw=std::string_view(e.what())=="late preview fault";}
        require(threw&&progressed,"Late unrelated preview fault was swallowed or never reached");unchanged();
        // The other actor's deferred stop/body request also runs on the clone.
        auto stopped=world.clone();OwnedUnitOrders(*stopped,data.stopScale).turnBody(1,8192,tick);
        bool deferredFinished=false;
        const auto stoppedBefore=snapshot(*stopped);
        const auto observe=[&](OwnedUnitWorld& copy){auto calls=silentCalls(copy);
            calls[0].driveStore=[&copy,&deferredFinished](int,int){
                if(!copy.actor(1).commands.pendingBodyTurn&&!copy.actor(1).state.movement.driving)deferredFinished=true;
            };return calls;};
        result=previewOwnedUnitMove(*stopped,0,x,y,false,tick,data.stopScale,policy,clear,observe);
        require(result.status==OwnedUnitMoveStatus::accepted&&deferredFinished&&snapshot(*stopped)==stoppedBefore,"Other actor's deferred stop/body preview missing or escaped");unchanged();
        // Commit to an isolated source: exact floor/order effects, no simulated
        // tick. Compare an independent logical owner with those effects only.
        auto committed=world.clone(),expected=world.clone();
        auto route=OwnedUnitOrders(*expected,data.stopScale).directRoute(0,x,y);
        route->destination.z=expected->context().services.advance.ground.floor(route->destination);
        OwnedUnitOrders(*expected,data.stopScale).order(0,*route);
        result=moveOwnedUnit(*committed,0,x,y,false,tick,data.stopScale,policy,clear,silentCalls);
        require(result.status==OwnedUnitMoveStatus::accepted&&snapshot(*committed)==snapshot(*expected),"Accepted move committed advanced preview state");unchanged();
        // Refused live entry is still completely atomic.
        const auto committedBefore=snapshot(*committed);mask.assign(262144,0);
        result=moveOwnedUnit(*committed,1,x,y,false,tick,data.stopScale,policy,OwnedUnitClearance(mask),silentCalls);
        require(result.status==OwnedUnitMoveStatus::blocked&&snapshot(*committed)==committedBefore,"Rejected live entry changed source");unchanged();
    }else if(mode==1){
        for(int wanted:{6,7}){
            auto source=world.clone();
            if(wanted==6){
                auto a=source->actor(0);OwnedUnitOrders(*source,data.stopScale).stop(0);
                a.state.movement.driving=false;a.state.movement.head={};
                const auto at=a.state.movement.body.current(tick);
                a.state.movement.body.start=a.state.movement.body.desired=at;a.state.movement.body.duration=0;
            }else{
                // A newly supplied zero-speed type at construction. Mutating a
                // bound services view is not a construction input for reclones.
                auto numeric=std::make_shared<const RenderData>(light);
                GroundDriveProcessServices supplied;supplied.trackSpeed.fill(0);
                supplied.uphill=source->context().services.uphill;supplied.downhill=source->context().services.downhill;
                supplied.squareRoot=[numeric](double n){return tableSqrt(*numeric,n);};
                supplied.advance.notify=[](int){};supplied.advance.postCell=[]{ };supplied.noRoute=[]{ };
                auto context=std::make_unique<TerrainUnitContext>(std::shared_ptr<MutableUnitMap>(source->context().map->clone()),supplied,source->actor(0).state);
                const auto& parked=*source->context().parked;
                context->bindParked(parked.state,parked.marking,parked.discovery,{},parked.turret);
                context->unit->copyStateFrom(*source->context().unit);context->redraw=source->context().redraw;
                const auto inputs=OwnedUnitProcessesInputs{5,1,0,0,8,
                    std::array<OwnedUnitProcessActorInputs,2>{OwnedUnitProcessActorInputs{{19,-23},31},OwnedUnitProcessActorInputs{{-29,37},-41}}};
                auto replacement=std::make_unique<OwnedUnitWorld>(std::move(context),std::make_shared<const DriveData>(data),
                    OwnedUnitWorldNumerics{numeric,[numeric](double n){return tableSqrt(*numeric,n);}},inputs,source->actor(0).turret);
                for(int id:{0,1}){replacement->actor(id).commands=source->actor(id).commands;replacement->actor(id).wait=source->actor(id).wait;}
                replacement->select(source->selected());source=std::move(replacement);
            }
            const auto before=snapshot(*source);const auto target=source->actor(1).state.destination;
            const auto result=previewOwnedUnitMove(*source,1,target.x/256,target.y/256+1,true,tick,data.stopScale,policy,clear,silentCalls);
            if(result.status!=OwnedUnitMoveStatus::unsupportedAdmission||result.admission!=wanted)
                throw std::runtime_error("Actual preview admission "+std::to_string(wanted)+" not reached: "+std::to_string(int(result.status))+"/"+std::to_string(result.admission));
            require(snapshot(*source)==before,"Actual unsupported admission escaped preview source");unchanged();
        }
    }else throw std::invalid_argument("Unknown preview check mode");
    std::cerr<<"Warm scheduled preview mode "<<mode<<": "<<checks<<" isolation checks: PASS\n";
}
}
