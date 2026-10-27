// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "platform/OwnedUnitWorld.hpp"
#include "assets/MapCoordinateCell.hpp"
#include <cmath>
#include <span>

namespace ra2 {
// Borrowed, SDL-free command adapter; owns no actor/Drive/map or command state.
// stopScale is the immutable original constant from the caller's DriveData.
// Routing, queue replacement, target lifetime and deferred manual turns are
// supplied prototype policies, separate from original Move_To/Stop/Do_Turn.
class OwnedUnitOrders {
    OwnedUnitWorld& world_;
    double stopScale_;
public:
    OwnedUnitOrders(OwnedUnitWorld& world,double stopScale):world_(world),stopScale_(stopScale){
        if(!std::isfinite(stopScale)||stopScale<0.||stopScale>1.)
            throw std::invalid_argument("Owned orders require a finite original stop scale");
    }
    // Pure bounded route construction. Coordinates are destination Cell words,
    // not a pathfinder result. No queries, floors or live mutations occur here.
    std::optional<OwnedUnitRoute> directRoute(int id,int x,int y,bool append=false){
        auto a=world_.actor(id);
        return directOwnedUnitRoute(a.state,a.commands.navigationTarget,x,y,append);
    }
    // Healthy/nonbridge Move_To projection, then supplied route/control writes.
    // The caller supplies destination Z and checks domain/clearance on a clone
    // before live application. An unsupported bridge can throw after the original
    // destination stores/query; a discarded preview is the refusal boundary.
    void order(int id,Coord destination,std::span<const int> directions){
        auto a=world_.actor(id);
        if(destination==Coord{}||directions.empty()||directions.size()>23)
            throw std::invalid_argument("Owned order requires a nonzero target and 1..23 directions");
        std::array<int,24> queue;queue.fill(-1);
        for(std::size_t i=0;i<directions.size();++i){(void)directionOffset(directions[i]);queue[i]=directions[i];}
        a.state.destination=destination;
        const auto& cell=mapCoordinateCell(destination,world_.context().unit->world(),262144);
        if(cell.flags&0x100u)throw UnsupportedGroundRoute("Owned orders exclude bridge destinations");
        world_.clearMovementTarget(id); // Supplied explicit-command target lifetime.
        a.state.route=queue;
        auto& c=a.commands;c.navigationTarget=destination;c.pendingBodyTurn.reset();
        c.manualTurret=false;c.stopRequested=false;
    }
    void order(int id,const OwnedUnitRoute& route){order(id,route.destination,route.directions);}
    void stop(int id){
        auto a=world_.actor(id);
        // Original ordered percentage store, then null destination. Queue and
        // command records are the supplied explicit-command boundary.
        a.state.percentage=std::min(a.state.percentage,stopScale_);
        a.state.destination={};a.state.route.fill(-1);
        world_.clearMovementTarget(id);
        auto& c=a.commands;c.navigationTarget.reset();c.pendingBodyTurn.reset();c.stopRequested=true;
    }
    void turnBody(int id,int delta,int tick){
        auto a=world_.actor(id);
        const auto wanted=std::uint16_t(std::uint32_t(a.state.movement.body.desired)+std::uint32_t(delta));
        stop(id);
        if(a.state.movement.driving)a.commands.pendingBodyTurn=wanted;
        else a.state.movement.body.setDesired(wanted,tick);
    }
    // Supplied positive routing after a recovered Scatter destination. Run
    // between Process calls so the displaced actor receives its path before
    // empty-queue cleanup. Preserve its actual Cell target and destination Z.
    // This is bounded direct routing, not recovered original pathfinding.
    void followScatter(int id){
        const auto* target=world_.pendingScatterRoute(id);
        if(!target)return;
        auto a=world_.actor(id);
        if(!world_.supplyScatterRoute(id,target->position.x,target->position.y)){
            if(a.state.movement.actor.position.x/256==target->position.x&&
               a.state.movement.actor.position.y/256==target->position.y){world_.scatterRouted(id);return;}
            throw UnsupportedGroundRoute("Scatter destination has no bounded direct route");
        }
        world_.scatterRouted(id);
    }
    // Call explicitly after the supplied both-actor Process schedule. Arrival
    // target cleanup precedes automatic turret update; pending body turn follows.
    // This is host scheduling/mission policy, not an original Unit tick root.
    void finishTick(int id,int tick){
        auto a=world_.actor(id);
        if(!a.state.movement.driving&&a.state.route.front()==-1){
            a.state.destination={};a.commands.navigationTarget.reset();
        }
        world_.updateTurret(id,tick);
        if(!a.state.movement.driving&&a.commands.pendingBodyTurn){
            a.state.movement.body.setDesired(*a.commands.pendingBodyTurn,tick);
            a.commands.pendingBodyTurn.reset();
        }
    }
};
}
