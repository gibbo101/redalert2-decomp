// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "platform/OwnedUnitSchedule.hpp"

namespace ra2 {
// Immutable copy of the supplied bounds/domain/scenery mask. No renderer,
// callback, mutable Cell, floor, type index or pool is borrowed by this guard.
// Actual gates/admission, including zero Track speed, still decide movement.
class OwnedUnitClearance {
    std::vector<std::uint8_t> allowed_;
public:
    explicit OwnedUnitClearance(std::span<const std::uint8_t> allowed):allowed_(allowed.begin(),allowed.end()){
        if(allowed_.size()!=262144)throw std::invalid_argument("Owned clearance requires the 512 squared Cell mask");
    }
    bool allows(int x,int y)const{
        return x>=0&&y>=0&&x<512&&y<512&&allowed_[std::size_t(y)*512+std::size_t(x)]!=0;
    }
};
enum class OwnedUnitMoveStatus {accepted,invalidRoute,blocked,notArrived,tickLimit,unsupportedRoute,unsupportedAdmission};
struct OwnedUnitMoveResult {
    OwnedUnitMoveStatus status=OwnedUnitMoveStatus::invalidRoute;
    int admission=-1,ticks=0; // Complete scheduled ticks, excluding a faulted tick.
    std::optional<OwnedUnitRoute> route; // Present only on acceptance; never advanced actor state.
};
struct OwnedUnitMovePolicy {
    OwnedUnitStepInputs step;
    int maxTicks=4096;
};
// Bind effects to the supplied clone, not to captured live actors/maps/renderers.
// Binding itself must not query or mutate it. The factory/calls are scoped to
// one preview; only immutable inputs may be captured from outside that owner.
using OwnedUnitPreviewServices=std::function<std::array<OwnedUnitWorldCall,2>(OwnedUnitWorld&)>;

inline OwnedUnitMoveResult previewOwnedUnitMove(const OwnedUnitWorld& source,int id,int x,int y,
    bool append,int tick,double stopScale,const OwnedUnitMovePolicy& policy,
    const OwnedUnitClearance& clearance,const OwnedUnitPreviewServices& bind){
    if(id!=0&&id!=1)throw std::invalid_argument("Unknown owned preview actor");
    if(!bind||policy.maxTicks<1||policy.maxTicks>4096)
        throw std::invalid_argument("Owned preview requires scoped services and 1..4096 scheduled ticks");
    OwnedUnitMoveResult result;
    const auto preview=source.preview([&](OwnedUnitWorld& copy){
        OwnedUnitOrders orders(copy,stopScale);OwnedUnitSchedule schedule(copy,stopScale);
        const auto calls=bind(copy);OwnedUnitSchedule::validate(policy.step,calls);
        auto route=orders.directRoute(id,x,y,append);
        if(!route)return false;
        const auto clear=[&](int cx,int cy){
            return clearance.allows(cx,cy)&&copy.context().map->table[std::size_t(cy)*512+std::size_t(cx)];
        };
        if(!clear(x,y)){result.status=OwnedUnitMoveStatus::blocked;return false;}
        const auto& services=id?copy.context().parked->services:copy.context().services;
        route->destination.z=services.advance.ground.floor(route->destination);
        orders.order(id,*route);
        std::array<Coord,2> previous{copy.actor(0).state.movement.actor.position,copy.actor(1).state.movement.actor.position};
        const auto footprint=[&](Coord a,Coord b){
            if(!clear(int(std::floor(b.x/256.)),int(std::floor(b.y/256.))))return false;
            const auto dx=std::int64_t(b.x)-a.x,dy=std::int64_t(b.y)-a.y;
            const auto samples=std::max<std::int64_t>(1,(std::max(std::abs(dx),std::abs(dy))+15)/16);
            for(std::int64_t sample=0;sample<=samples;++sample){
                const double f=double(sample)/double(samples);
                const double px=(a.x+dx*f)/256.,py=(a.y+dy*f)/256.;
                for(double ox:{-.25,.25})for(double oy:{-.25,.25})
                    if(!clear(int(std::floor(px+ox)),int(std::floor(py+oy))))return false;
            }
            return true;
        };
        for(int actor:{0,1})if(!footprint(previous[actor],previous[actor])){
            result.status=OwnedUnitMoveStatus::blocked;return false;
        }
        for(int step=1;step<=policy.maxTicks;++step){
            const int at=signed32(std::uint32_t(tick)+std::uint32_t(step));
            schedule.step(at,policy.step,calls);++result.ticks;
            for(int actor:{0,1}){
                const auto point=copy.actor(actor).state.movement.actor.position;
                if(!footprint(previous[actor],point)){result.status=OwnedUnitMoveStatus::blocked;return false;}
                previous[actor]=point;
            }
            const auto& state=copy.actor(id).state;
            if(!state.movement.driving&&state.route.front()==-1){
                const auto point=state.movement.actor.position;
                if(point.x!=route->destination.x||point.y!=route->destination.y){
                    result.status=OwnedUnitMoveStatus::notArrived;return false;
                }
                result.status=OwnedUnitMoveStatus::accepted;result.route=std::move(route);return true;
            }
        }
        result.status=OwnedUnitMoveStatus::tickLimit;return false;
    });
    if(preview.status==OwnedUnitPreviewStatus::unsupportedRoute)result.status=OwnedUnitMoveStatus::unsupportedRoute;
    if(preview.status==OwnedUnitPreviewStatus::unsupportedAdmission){
        result.status=OwnedUnitMoveStatus::unsupportedAdmission;result.admission=preview.admission;
    }
    return result;
}
// Single-threaded command entry. Only an accepted command is applied live; the
// advanced preview is discarded. The same floor/Move_To sequence runs on the
// live map after acceptance. Neither preview nor commit invokes a renderer.
inline OwnedUnitMoveResult moveOwnedUnit(OwnedUnitWorld& world,int id,int x,int y,bool append,int tick,
    double stopScale,const OwnedUnitMovePolicy& policy,const OwnedUnitClearance& clearance,
    const OwnedUnitPreviewServices& bind){
    auto result=previewOwnedUnitMove(world,id,x,y,append,tick,stopScale,policy,clearance,bind);
    if(result.status==OwnedUnitMoveStatus::accepted){
        auto route=*result.route;
        const auto& services=id?world.context().parked->services:world.context().services;
        route.destination.z=services.advance.ground.floor(route.destination);
        OwnedUnitOrders(world,stopScale).order(id,route);
    }
    return result;
}
}
