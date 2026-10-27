// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/UnitScatterWorld.hpp"
#include "sim/CellScatter.hpp"
namespace ra2 {
// The Cell policy borrows actual list heads, Next/kind/owner and per-actor
// Scatter views. Promotion/type/House/rule inputs remain supplied records.
template<class Admission,class Motion> struct BasicCellUnitScatterView {
    Admission& admission;
    std::span<BasicUnitScatterWorldView<Admission,Motion>* const> units;
    std::span<double> veterancy;
    std::span<const int> typeIds;
    std::span<const std::uint8_t> eligibility5a0,shortTrack;
    std::map<int,CellScatterType>& types;
    std::map<int,int>& house194;
    std::uint8_t& rules1431;
    int& rules10b4;
    const Motion* liveMotion=nullptr;
};
using CellUnitScatterView=BasicCellUnitScatterView<UnitAdmissionWorld,UnitAdmissionMotionWorld>;
struct CellUnitScatterInputs {
    const DriveData& driveData;
    std::function<double(double)> squareRoot;
    OriginalRandomState& random;
    std::array<ScatterCellPoint,8> neighbors;
    std::span<const int> destinationPadding;
    int height=104,tick=0,delay=0;
    double stopScale=0.;
    std::function<std::uint8_t(int,int)> missionControl;
    std::function<std::uint32_t(int)> grow;
    std::function<void(int)> release;
};
// Unwired Unit-only Cell dispatch -> complete actual Unit Scatter/world.
// No replacement member callback, movement step, pathfinder or allocator.
template<class Admission,class Motion>
inline void scatterCellUnitsOnMapWithUnitCall(int cell,const Coord& at,std::uint8_t ignoreMission,
    std::uint8_t ignoreDestination,std::uint8_t elevated,BasicCellUnitScatterView<Admission,Motion> v,
    const CellUnitScatterInputs& input,const ScatterWorldTrace& trace,const auto& invokeUnit){
    const auto event=[&](char k,std::int64_t a=0,std::int64_t b=0,std::int64_t c=0){if(trace)trace('c',k,a,b,c);};
    if(v.units.empty()||v.units.size()!=v.admission.gates.objects.size()||
       v.units.size()!=v.veterancy.size()||v.units.size()!=v.typeIds.size()||
       v.units.size()!=input.destinationPadding.size()||
       !v.admission.cells.contains(cell)||
       !v.admission.gates.cells.contains(cell)||!input.grow||!input.release||!input.squareRoot)
        throw std::invalid_argument("Cell Unit Scatter requires explicit shared owners/services");
    constexpr bool borrowed=requires {v.admission.gates.forwardAssignedFallback;};
    if constexpr(borrowed){
        if(!v.liveMotion||v.liveMotion->actors.size()!=v.units.size()||v.liveMotion->data!=&input.driveData||
           !v.liveMotion->squareRoot||!v.eligibility5a0.empty()||!v.shortTrack.empty())
            throw std::invalid_argument("Borrowed Cell Scatter requires actual motion owners without refresh spans");
    }else if(v.units.size()!=v.eligibility5a0.size()||v.units.size()!=v.shortTrack.size()||v.liveMotion)
        throw std::invalid_argument("Value Cell Scatter requires its existing motion projection");
    struct Member {const int& kind;const int& next;const int& type;const int& owner;double& veterancy;};
    struct Heads {int& primary;int& elevated;};
    struct World {
        std::map<int,Member> members;std::map<int,CellScatterType>& types;
        std::map<int,int>& house194;std::map<int,Heads> cells;
        std::uint8_t& rules1431;int& rules10b4;
        std::function<void(char,int,int)> trace;
    } world{{},v.types,v.house194,{},v.rules1431,v.rules10b4,{}};
    for(std::size_t i=0;i<v.units.size();++i){
        const auto* unit=v.units[i];
        if(!v.admission.gates.objects.contains(int(i))||!v.admission.objects.contains(int(i)))
            throw std::invalid_argument("Cell Unit Scatter requires every explicit actor record");
        const auto& actor=v.admission.gates.objects.at(int(i));
        if(!unit||unit->mover!=int(i)||&unit->admission!=&v.admission||
           &unit->unit.mission!=&actor.mission||actor.kind!=1||!v.types.contains(v.typeIds[i])||
           unit->profile.isTrain!=v.admission.objects.at(int(i)).train)
            throw std::invalid_argument("Cell Unit Scatter excludes non-Unit or mirrored actors");
        if constexpr(borrowed){
            const auto& m=v.liveMotion->actors.at(int(i));const auto& d=unit->unit.drive;
            if(&m.position!=&d.movement.actor.position||&m.destination!=&d.destination||&m.head!=&d.movement.head||
               &m.body!=&d.movement.body||&m.queueHead!=&d.route[0]||&m.track!=&d.movement.track||
               &m.index!=&d.movement.index||&m.eligibility5a0!=&d.movement.reached5a0||
               &v.admission.objects.at(int(i)).target494!=&unit->unit.actor.target494)
                throw std::invalid_argument("Borrowed Cell Scatter excludes split motion or target owners");
        }
        if(i){const auto& first=*v.units[0];
            if(unit->slots.data()!=first.slots.data()||unit->slots.size()!=first.slots.size()||
               &unit->fallback!=&first.fallback||&unit->floor!=&first.floor||
               &unit->floorHeight!=&first.floorHeight||&unit->layerHeight!=&first.layerHeight||
               &unit->permission!=&first.permission||unit->bindings.data()!=first.bindings.data()||
               unit->registry.data()!=first.registry.data()||&unit->unit.globalReferences!=&first.unit.globalReferences)
                throw std::invalid_argument("Cell Unit Scatter requires one shared map/numeric/lifetime owner");
            for(std::size_t j=0;j<i;++j)
                if(&unit->unit.actor==&v.units[j]->unit.actor||&unit->unit.drive==&v.units[j]->unit.drive||
                   &unit->unit.references==&v.units[j]->unit.references)
                    throw std::invalid_argument("Cell Unit Scatter excludes mirrored actor/Drive/lifetime records");
        }
        world.members.emplace(int(i),Member{actor.kind,actor.next,v.typeIds[i],actor.owner,v.veterancy[i]});
    }
    world.cells.emplace(cell,Heads{v.admission.gates.cells.at(cell).head,v.admission.cells.at(cell).elevatedHead});
    world.trace=[&](char k,int a,int b){event(k,a,b);};
    // Rebuild only at an actual admission query. Later dispatches must see
    // earlier destinations, queue-head clearing and raw nonnull Cell targets.
    // -2 is an explicit non-actor Cell reference, never a resident actor ID.
    std::optional<Motion> motion;
    if constexpr(!borrowed){motion.emplace();motion->data=&input.driveData;motion->squareRoot=input.squareRoot;}
    const auto refreshMotion=[&]()->const Motion*{
        if constexpr(borrowed)return v.liveMotion;
        else{
        for(std::size_t i=0;i<v.units.size();++i){
            const auto& u=v.units[i]->unit;const auto& d=u.drive;
            motion->actors[int(i)]={d.movement.actor.position,d.destination,d.movement.head,
                d.movement.body,v.eligibility5a0[i],d.route[0],d.movement.track,d.movement.index,v.shortTrack[i]};
            v.admission.objects.at(int(i)).target=u.actor.target494?-2:-1;
        }
        return &*motion;
        }
    };
    CellScatterServices services;
    services.grow=[&](int n){const auto result=input.grow(n);event('G',n,result);return result;};
    services.release=[&](int n){event('F',n);input.release(n);};
    services.scatter=[&](int id,const Coord& point,std::uint8_t im,std::uint8_t dest){
        event('S',id,im,dest);event('P',point.x,point.y,point.z);
        auto unit=*v.units[std::size_t(id)];unit.admissionMotion=refreshMotion;
        // The reused admission profile knows ability17 only for unpromoted
        // actors. Refuse an entered promoted query before its supplied false
        // result can be consumed; Cell's separate ability3 stays supported.
        const ScatterWorldTrace checkedTrace=[&](char group,char k,std::int64_t a,std::int64_t b,std::int64_t c){
            if(group=='a'&&k=='b'&&v.veterancy[std::size_t(a)]>=1.)
                throw UnsupportedUnitScatter("Promoted admission ability17 remains unjoined");
            if(trace)trace(group,k,a,b,c);
        };
        invokeUnit(unit,id,point,im,dest,checkedTrace);
    };
    scatterCellResidents(cell,at,ignoreMission,ignoreDestination,elevated,world,services);
}
// Retained nonzero-point entry; its Unit facade keeps zero-point search refused.
template<class Admission,class Motion>
inline void scatterCellUnitsOnMap(int cell,const Coord& at,std::uint8_t ignoreMission,
    std::uint8_t ignoreDestination,std::uint8_t elevated,BasicCellUnitScatterView<Admission,Motion> v,
    const CellUnitScatterInputs& input,const ScatterWorldTrace& trace={}){
    scatterCellUnitsOnMapWithUnitCall(cell,at,ignoreMission,ignoreDestination,elevated,v,input,trace,
        [&](auto unit,int id,const Coord& point,std::uint8_t im,std::uint8_t dest,const auto& checkedTrace){
            scatterOrdinaryUnitOnMap(unit,point,im,dest,input.driveData.directionsToTargets,
                input.random,input.neighbors,input.height,input.tick,input.destinationPadding[std::size_t(id)],
                input.delay,input.stopScale,input.missionControl,checkedTrace);
        });
}

}
