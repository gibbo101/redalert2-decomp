// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "platform/OwnedUnitMovePreview.hpp"
#include <set>

namespace ra2 {
// Supplied command-domain guard, not pathfinding or original admission. Bound
// work by the two existing 24-word queues, never by predicted travel time.
// Until runtime Scatter is joined, reserve the other actor's stationary Cell
// and commanded endpoint. Moving crossings use actual tick admission; commands
// do not predict timing or guarantee arrival. This reservation is conservative.
inline OwnedUnitMoveResult validateOwnedUnitMove(const OwnedUnitWorld& source,int id,int x,int y,
    bool append,double stopScale,const OwnedUnitStepInputs& step,
    const OwnedUnitClearance& clearance,const OwnedUnitPreviewServices& bind){
    if(id!=0&&id!=1)throw std::invalid_argument("Unknown owned command actor");
    if(!bind)throw std::invalid_argument("Owned command requires scoped services");
    OwnedUnitMoveResult result;
    const auto validation=source.preview([&](OwnedUnitWorld& copy){
        OwnedUnitSchedule::validate(step,bind(copy));
        OwnedUnitOrders orders(copy,stopScale);
        auto route=orders.directRoute(id,x,y,append);
        if(!route)return false;
        // Inspect immutable mask/current Cell words without warming floor/map
        // services. Command effects below run only on this discarded owner.
        const auto footprint=[&](Coord from,Coord to,std::set<int>& slots){
            const auto dx=std::int64_t(to.x)-from.x,dy=std::int64_t(to.y)-from.y;
            if(std::max(std::abs(dx),std::abs(dy))>1024)
                throw UnsupportedGroundRoute("Owned command has an unsupported committed segment");
            const auto count=std::max<std::int64_t>(1,(std::max(std::abs(dx),std::abs(dy))+15)/16);
            for(std::int64_t n=0;n<=count;++n){
                const double fraction=double(n)/double(count);
                const double px=(from.x+dx*fraction)/256.,py=(from.y+dy*fraction)/256.;
                for(double ox:{-.25,.25})for(double oy:{-.25,.25}){
                    const auto cx=std::floor(px+ox),cy=std::floor(py+oy);
                    if(cx<0||cy<0||cx>=512||cy>=512||!clearance.allows(int(cx),int(cy)))return false;
                    const int slot=int(cy)*512+int(cx);const auto* cell=copy.context().map->table[std::size_t(slot)];
                    if(!cell)return false;
                    if(cell->flags&0x100u)throw UnsupportedGroundRoute("Owned command excludes bridge Cells");
                    slots.insert(slot);
                }
            }
            return true;
        };
        const auto collect=[&](int actor,std::span<const int> directions,std::set<int>& slots){
            const auto& movement=copy.actor(actor).state.movement;
            Coord at=movement.actor.position;
            if(movement.actor.bridge79)throw UnsupportedGroundRoute("Owned command excludes bridge actors");
            if(!footprint(at,at,slots))return false;
            if(movement.driving){
                if(!footprint(at,movement.head,slots))return false;
                at=movement.head;
            }
            int count=0;
            for(int direction:directions){
                if(direction==-1)break;
                if(direction<0||direction>7)throw UnsupportedGroundRoute("Owned command has an unsupported direction");
                if(++count>23)throw UnsupportedGroundRoute("Owned command requires a terminated bounded queue");
                const auto [dx,dy]=directionOffset(direction);
                // All points were bounds-checked before incrementing.
                Coord next{at.x+dx*256,at.y+dy*256,at.z};
                if(!footprint(at,next,slots))return false;
                at=next;
            }
            return true;
        };
        std::set<int> selected,other,current,targetSlots,reservedTarget;
        result.status=OwnedUnitMoveStatus::blocked;
        if(!collect(id,route->directions,selected)||!collect(1-id,{},current))return false;
        auto resident=copy.actor(1-id);
        if(!resident.state.movement.driving&&resident.state.route.front()==-1)other=std::move(current);
        if(resident.commands.navigationTarget&&!footprint(*resident.commands.navigationTarget,*resident.commands.navigationTarget,reservedTarget))return false;
        // Include the requested target independently: supported queues can be
        // exhausted at a different point. Acceptance does not promise arrival.
        if(!footprint(route->destination,route->destination,targetSlots))return false;
        if(!copy.hasScatter()){
            for(int slot:selected)if(other.contains(slot))return false;
            for(int slot:targetSlots)if(other.contains(slot)||reservedTarget.contains(slot))return false;
        }
        const auto& services=id?copy.context().parked->services:copy.context().services;
        route->destination.z=services.advance.ground.floor(route->destination);
        orders.order(id,*route);
        result.status=OwnedUnitMoveStatus::accepted;result.route=std::move(route);return true;
    });
    if(validation.status==OwnedUnitPreviewStatus::unsupportedRoute)result.status=OwnedUnitMoveStatus::unsupportedRoute;
    if(validation.status==OwnedUnitPreviewStatus::unsupportedAdmission){
        result.status=OwnedUnitMoveStatus::unsupportedAdmission;result.admission=validation.admission;
    }
    return result;
}

// Single-threaded bounded transaction: discard failed validation/command effects;
// on success apply only the same live floor/order sequence. No Process, tick,
// observer, turret update or renderer is invoked during command acceptance.
// As with the low-level order API, arbitrary external throwing effects are not
// transactional. Production floor/order bindings are owner-local and synchronous.
inline OwnedUnitMoveResult commandOwnedUnitMove(OwnedUnitWorld& world,int id,int x,int y,bool append,
    double stopScale,const OwnedUnitStepInputs& step,const OwnedUnitClearance& clearance,
    const OwnedUnitPreviewServices& bind){
    auto result=validateOwnedUnitMove(world,id,x,y,append,stopScale,step,clearance,bind);
    if(result.status==OwnedUnitMoveStatus::accepted){
        auto route=*result.route;
        const auto& services=id?world.context().parked->services:world.context().services;
        route.destination.z=services.advance.ground.floor(route.destination);
        OwnedUnitOrders(world,stopScale).order(id,route);
    }
    return result;
}
}
