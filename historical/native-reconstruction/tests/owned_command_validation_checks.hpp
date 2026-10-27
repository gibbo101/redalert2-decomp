// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "platform/OwnedUnitMoveCommand.hpp"
#include "owned_preview_checks.hpp"
#include <chrono>
namespace owned_command_check {
using namespace ra2;
inline void check(OwnedUnitWorld& source,double stopScale,int speed){
    using owned_check::require;
    const auto before=owned_check::snapshot(source);const auto refs=owned_check::associations(source);
    int effects=0,bindings=0;
    const auto bind=[&](OwnedUnitWorld& copy){
        require(&copy!=&source,"Command validation bound live owner");++bindings;
        auto calls=owned_check::silentCalls(copy);
        for(auto& call:calls){
            call.driveStore=[&](int,int){++effects;};call.notify=[&](int){++effects;};
            call.decision=[&](char,int){++effects;};call.query=[&](char,Coord){++effects;};
        }
        return calls;
    };
    const OwnedUnitStepInputs step{{speed,speed},{0,0}};
    const OwnedUnitClearance clear(Bytes(262144,1));
    const auto unchanged=[&]{require(owned_check::snapshot(source)==before&&owned_check::associations(source)==refs,
        "Command validation changed live values/associations");};
    for(int id:{0,1}){
        const auto start=source.actor(id).state.movement.actor.position;
        auto expected=source.clone(),committed=source.clone();
        const int x=start.x/256+2,y=start.y/256;
        auto route=OwnedUnitOrders(*expected,stopScale).directRoute(id,x,y);
        const auto& services=id?expected->context().parked->services:expected->context().services;
        route->destination.z=services.advance.ground.floor(route->destination);
        OwnedUnitOrders(*expected,stopScale).order(id,*route);
        auto result=commandOwnedUnitMove(*committed,id,x,y,false,stopScale,step,clear,bind);
        require(result.status==OwnedUnitMoveStatus::accepted&&result.ticks==0&&result.route&&
            owned_check::snapshot(*committed)==owned_check::snapshot(*expected),"Bounded command simulated or committed extra state");
        unchanged();
    }
    // No need to predict arrival: even zero-speed commands validate, and none
    // of the Process observers/effects run. Keep arrival diagnostics separately.
    const auto at=source.actor(0).state.movement.actor.position;
    const int x=at.x/256+2,y=at.y/256;
    const auto start=std::chrono::steady_clock::now();
    auto result=validateOwnedUnitMove(source,0,x,y,false,stopScale,{{0,0},{0,0}},clear,bind);
    const double commandSeconds=std::chrono::duration<double>(std::chrono::steady_clock::now()-start).count();
    require(result.status==OwnedUnitMoveStatus::accepted&&result.ticks==0&&effects==0&&bindings==3,
        "Command admission depends on future simulation/arrival");unchanged();
    auto limited=OwnedUnitMovePolicy{step,1};
    const auto diagnostic=previewOwnedUnitMove(source,0,x,y,false,100,stopScale,limited,clear,owned_check::silentCalls);
    require(diagnostic.status==OwnedUnitMoveStatus::tickLimit&&diagnostic.ticks==1,
        "Full diagnostic preview disappeared or ceased to predict");unchanged();
    Bytes blocked(262144,1);blocked[std::size_t(y)*512+std::size_t(x-1)]=0;
    result=validateOwnedUnitMove(source,0,x,y,false,stopScale,step,OwnedUnitClearance(blocked),bind);
    require(result.status==OwnedUnitMoveStatus::blocked&&!result.route,"Blocked intermediate command accepted");unchanged();
    result=validateOwnedUnitMove(source,0,512,y,false,stopScale,step,clear,bind);
    require(result.status==OwnedUnitMoveStatus::invalidRoute&&!result.route,"Out-of-domain command accepted");unchanged();
    auto bridge=source.clone();bridge->context().map->table[std::size_t(y)*512+std::size_t(x)]->flags|=0x100u;
    const auto bridgeBefore=owned_check::snapshot(*bridge);
    result=commandOwnedUnitMove(*bridge,0,x,y,false,stopScale,step,clear,owned_check::silentCalls);
    require(result.status==OwnedUnitMoveStatus::unsupportedRoute&&owned_check::snapshot(*bridge)==bridgeBefore,
        "Bridge refusal partially changed command owner");unchanged();
    auto invalid=[&](OwnedUnitWorld& copy){auto calls=bind(copy);calls[1].notify={};return calls;};
    bool refused=false;
    try{(void)validateOwnedUnitMove(source,0,x,y,false,stopScale,step,clear,invalid);}
    catch(const std::invalid_argument&){refused=true;}
    require(refused,"Missing actor1 services entered command validation");unchanged();
    bool propagated=false;
    try{(void)validateOwnedUnitMove(source,0,x,y,false,stopScale,step,clear,
        [](OwnedUnitWorld&)->std::array<OwnedUnitWorldCall,2>{throw std::runtime_error("command binding fault");});}
    catch(const std::runtime_error& e){propagated=std::string_view(e.what())=="command binding fault";}
    require(propagated,"Unrelated command fault swallowed");unchanged();
    std::cout<<"Bounded command validation: both actors, zero predicted ticks/no arrival requirement, exact command effects, "
        "mask/bridge/input/fault isolation PASS; measured validation "<<commandSeconds<<"s\n";
}
}
