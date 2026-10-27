// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "owned_world_snapshot.hpp"
#include "platform/OwnedUnitSchedule.hpp"
#include "render/Lighting.hpp"
#include "sim/OriginalMath.hpp"
namespace owned_advance_check {
using namespace ra2;
inline void require(bool v,const char* why){if(!v)throw std::runtime_error(why);}
inline std::vector<std::uintptr_t> associations(const OwnedUnitWorld& w){
    const auto& c=w.context();std::vector<std::uintptr_t> v;
    const auto put=[&](const auto* p){v.push_back(reinterpret_cast<std::uintptr_t>(p));};
    put(&c);put(c.map.get());put(c.unit.get());put(&c.state);put(&c.parked->state);
    for(const auto* p:c.map->table)put(p);for(const auto* p:c.map->attributes)put(p);return v;
}
// Host isolation checks, separate from original expectations. Source rendering is
// already warm; preview receives neither the renderer nor its mutable storage.
inline int check(OwnedUnitWorld& world,std::shared_ptr<const DriveData> data,
    const RenderData& light,OwnedUnitProcessesInputs inputs,int mover,int tick,
    int speed,const std::function<std::string()>& renderer){
    const auto live=owned_check::snapshot(world),render=renderer();const auto refs=associations(world);
    int checks=0;
    const auto unchanged=[&]{
        require(owned_check::snapshot(world)==live&&associations(world)==refs,"Advance preview changed source values/associations");
        require(renderer()==render,"Advance preview changed warm drawing state");++checks;
    };
    const auto calls=[](int& seven){
        std::array<OwnedUnitWorldCall,2> v;
        for(auto& c:v){c.notify=[](int){};c.postCell=[]{ };c.noRoute=[]{ };c.failedRoute=[](int){};}
        for(auto& c:v)c.decision=[&seven](char k,int n){if(k=='D'&&n==7)++seven;};return v;
    };
    for(bool accept:{true,false}){
        int seven=0;
        const auto result=world.preview([&](OwnedUnitWorld& copy){
            const auto before0=copy.actor(0).state.movement.actor.position,before1=copy.actor(1).state.movement.actor.position;
            auto effects=calls(seven);OwnedUnitSchedule schedule(copy,data->stopScale);
            for(int n=0;n<8;++n)schedule.step(signed32(std::uint32_t(tick)+unsigned(n)),{{speed,speed},{7,7}},effects);
            require(copy.actor(0).state.movement.actor.position!=before0&&copy.actor(1).state.movement.actor.position!=before1,
                "Advance preview did not move both genuine actors");return accept;
        });
        require(result.status==(accept?OwnedUnitPreviewStatus::accepted:OwnedUnitPreviewStatus::rejected)&&seven>0,
            "Advance preview lost policy across clone binding");unchanged();
    }
    bool fault=false;int seven=0;
    try{world.preview([&](OwnedUnitWorld& copy)->bool{
        auto effects=calls(seven);OwnedUnitSchedule(copy,data->stopScale).step(tick,{{speed,speed},{7,7}},effects);
        throw std::runtime_error("Advance preview fault after both Process calls");
    });}catch(const std::runtime_error& e){fault=std::string(e.what())=="Advance preview fault after both Process calls";}
    require(fault&&seven>0,"Advance preview swallowed unrelated fault");unchanged();
    const auto six=world.preview([&](OwnedUnitWorld& copy){
        auto& other=copy.actor(1-mover).state;auto& movement=other.movement;
        movement.body.desired=movement.body.start=movement.body.current(tick);movement.body.duration=0;
        other.destination={};movement.head={};other.route.fill(-1);
        int ignored=0;auto effects=calls(ignored);copy.process(mover,speed,tick,7,effects[std::size_t(mover)]);return true;
    });
    require(six.status==OwnedUnitPreviewStatus::unsupportedAdmission&&six.admission==6,"Advance6 ceased being a typed refusal");unchanged();
    // Reconstruct only an isolated clone with the default policy. Preserve the
    // genuine marked map and records; never mutate the live binding's policy.
    auto base=world.context().clone();
    std::unique_ptr<TerrainUnitContext> context(static_cast<TerrainUnitContext*>(base.release()));
    inputs.advancePolicy=OwnedUnitAdvancePolicy::guarded;auto numeric=std::make_shared<const RenderData>(light);
    OwnedUnitWorld guarded(std::move(context),data,{numeric,[numeric](double n){return tableSqrt(*numeric,n);}},inputs,world.actor(0).turret);
    bool refused=false;seven=0;auto effects=calls(seven);
    try{guarded.process(mover,speed,tick,7,effects[std::size_t(mover)]);}
    catch(const UnsupportedGroundAdmission& e){require(e.result==7,"Guarded policy refused another code");refused=true;}
    require(refused&&seven>0,"Default owned policy no longer refuses actual Advance7");unchanged();
    bool prevalidated=false;
    const auto invalid=world.preview([&](OwnedUnitWorld& copy){
        const auto before=owned_check::snapshot(copy);int ignored=0;auto bad=calls(ignored);bad[1].notify={};
        try{OwnedUnitSchedule(copy,data->stopScale).step(tick,{{speed,speed},{7,7}},bad);}
        catch(const std::invalid_argument&){prevalidated=true;}
        require(prevalidated&&owned_check::snapshot(copy)==before,"Second-actor service check followed Process0 mutation");return false;
    });
    require(invalid.status==OwnedUnitPreviewStatus::rejected&&prevalidated,"Invalid service preview was accepted");unchanged();
    return checks;
}
}
