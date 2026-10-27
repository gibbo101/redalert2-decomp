// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/OwnedUnitProcesses.hpp"
#include "platform/TerrainUnitContext.hpp"
#include "sim/Simulation.hpp"
#include <cmath>

namespace ra2 {
struct OwnedUnitRoute {
    Coord destination;
    std::vector<int> directions;
};
// Supplied bounded host routing, shared by explicit orders and preparation's
// synchronous route callback. No original pathfinding or world queries.
inline std::optional<OwnedUnitRoute> directOwnedUnitRoute(const GroundDriveProcessState& s,
    const std::optional<Coord>& navigationTarget,int x,int y,bool append=false){
    if(x<0||y<0||x>=1024||y>=1024)return {};
    const Coord anchor=s.movement.driving?s.movement.head:s.movement.actor.position;
    const Coord start=append&&navigationTarget?*navigationTarget:anchor;
    OwnedUnitRoute result{{x*256+128,y*256+128,0},{}};
    if(append&&navigationTarget)
        for(int d:s.route){if(d==-1)break;result.directions.push_back(d);}
    auto dx=std::int64_t(x)-start.x/256,dy=std::int64_t(y)-start.y/256;
    const auto distance=std::max(std::abs(dx),std::abs(dy));
    if(!distance||result.directions.size()+std::uint64_t(distance)>23)return {};
    while(dx||dy){
        const int sx=(dx>0)-(dx<0),sy=(dy>0)-(dy<0);
        for(int d=0;d<8;++d)if(directionOffset(d)==std::pair{sx,sy}){result.directions.push_back(d);break;}
        dx-=sx;dy-=sy;
    }
    return result;
}
// Host command records, not original mission/pathfinder state. There is no
// mirrored Drive: Process always consumes the actual membership-bound records.
struct OwnedUnitCommands {
    std::optional<Coord> navigationTarget;
    std::optional<std::uint16_t> pendingBodyTurn;
    bool manualTurret=false, turretTurning=false, stopRequested=false;
    bool operator==(const OwnedUnitCommands&) const=default;
};
struct OwnedUnitWorldActor {
    GroundDriveProcessState& state;
    Facing& turret;
    OwnedUnitCommands& commands;
    GroundDriveMovingWaitState& wait;
};
// A pure numeric service with an explicit shared immutable lifetime. This must
// not close over a live simulation/observer. Clones retain this owner, not the
// context's original supplied callbacks.
struct OwnedUnitWorldNumerics {
    std::shared_ptr<const void> owner;
    std::function<double(double)> squareRoot;
};
struct OwnedUnitWorldCall {
    GroundStateStore actorStore, rampStore, driveStore;
    std::function<void(int)> notify, failedRoute;
    std::function<void()> postCell, noRoute;
    std::function<void(char,int)> decision;
    PreparedUnitMembership::Query query;
    ScatterWorldTrace scatter;
};
enum class OwnedUnitPreviewStatus { accepted, rejected, unsupportedRoute, unsupportedAdmission };
struct OwnedUnitPreviewResult {
    OwnedUnitPreviewStatus status;
    int admission=-1;
};

// SDL-free composition owner. Borrowed actor views stay valid while this owner
// lives. Move the unique_ptr, never the owner. Not yet used by SDL/Simulation.
class OwnedUnitWorld {
    std::unique_ptr<TerrainUnitContext> context_;
    std::shared_ptr<const DriveData> data_;
    OwnedUnitWorldNumerics numerics_;
    OwnedUnitProcessesInputs inputs_;
    Facing turret0_;
    std::array<OwnedUnitCommands,2> commands_;
    std::unique_ptr<OwnedUnitProcesses> processes_;
    const OwnedUnitWorldCall* active_=nullptr;
    int selected_=-1;
    static void checkActor(int id){
        if(id!=0&&id!=1)throw std::invalid_argument("Unknown owned world actor");
    }
    void bind(){
        if(!context_||!context_->map||!context_->unit||!context_->parked||
           !context_->parked->turret||context_->admission||!data_||
           !numerics_.owner||!numerics_.squareRoot)
            throw std::invalid_argument("Owned world requires two explicit actors, turret, data and numeric owners without legacy admission");
        for(auto* service:{&context_->services,&context_->parked->services}){
            // Replace copied external effects. In particular, clone() may have
            // copied the old context's supplied notify/postCell/noRoute closures.
            service->advance.notify=[this](int n){if(active_&&active_->notify)active_->notify(n);};
            service->advance.postCell=[this]{if(active_&&active_->postCell)active_->postCell();};
            service->noRoute=[this]{if(active_&&active_->noRoute)active_->noRoute();};
            service->squareRoot=numerics_.squareRoot;
            service->advance.driveStore={};
        }
        processes_=std::make_unique<OwnedUnitProcesses>(context_->map->input(),*context_->unit,
            std::array<GroundDriveProcessState*,2>{&context_->state,&context_->parked->state},
            std::array<GroundDriveProcessServices,2>{context_->services,context_->parked->services},
            *data_,inputs_,[this](char k,Coord p){if(active_&&active_->query)active_->query(k,p);});
    }
public:
    OwnedUnitWorld(std::unique_ptr<TerrainUnitContext> context,std::shared_ptr<const DriveData> data,
        OwnedUnitWorldNumerics numerics,OwnedUnitProcessesInputs inputs,Facing turret0)
        :context_(std::move(context)),data_(std::move(data)),numerics_(std::move(numerics)),
         inputs_(inputs),turret0_(turret0){bind();}
    OwnedUnitWorld(const OwnedUnitWorld&)=delete;
    OwnedUnitWorld& operator=(const OwnedUnitWorld&)=delete;
    OwnedUnitWorld(OwnedUnitWorld&&)=delete;
    OwnedUnitWorld& operator=(OwnedUnitWorld&&)=delete;
    const TerrainUnitContext& context()const{return *context_;}
    OwnedUnitWorldActor actor(int id){
        checkActor(id);
        return {id?context_->parked->state:context_->state,
            id?*context_->parked->turret:turret0_,commands_[std::size_t(id)],processes_->wait[std::size_t(id)]};
    }
    int selected()const{return selected_;}
    bool hasScatter()const{return processes_->hasScatter();}
    const void* const& movementTargetStorage(int id)const{checkActor(id);return processes_->movementTargetStorage(id);}
    const MapCellInput* movementTarget(int id)const{checkActor(id);return processes_->movementTarget(id);}
    const MapCellInput* pendingScatterRoute(int id)const{checkActor(id);return processes_->pendingScatterRoute(id);}
    void scatterRouted(int id){checkActor(id);processes_->scatterRouted(id);}
    void clearMovementTarget(int id){checkActor(id);processes_->clearTarget(id);}
    bool scatterRouteAllowed(int x,int y)const{return processes_->scatterRouteAllowed(x,y);}
    int preparationCounter(int id)const{checkActor(id);return processes_->preparationCounter(id);}
    // Supplied positive route service, callable inside recursive preparation as
    // well as between Processes. Validate everything before queue/control writes;
    // retain the actual Cell target and destination Z, and never run Process here.
    bool supplyScatterRoute(int id,int x,int y){
        auto a=actor(id);
        if(!hasScatter())throw std::logic_error("Positive preparation route requires explicit Scatter policy");
        const auto route=directOwnedUnitRoute(a.state,{},x,y);
        if(!route)return false;
        Coord at=a.state.movement.driving?a.state.movement.head:a.state.movement.actor.position;
        const auto sample=[&](Coord from,Coord to){
            const auto dx=std::int64_t(to.x)-from.x,dy=std::int64_t(to.y)-from.y;
            const auto count=std::max<std::int64_t>(1,(std::max(std::abs(dx),std::abs(dy))+15)/16);
            if(count>65)throw UnsupportedGroundRoute("Scatter committed segment outside bounded route domain");
            for(std::int64_t n=0;n<=count;++n)for(double ox:{-.25,.25})for(double oy:{-.25,.25}){
                const auto cx=std::floor((from.x+dx*double(n)/double(count))/256.+ox);
                const auto cy=std::floor((from.y+dy*double(n)/double(count))/256.+oy);
                if(cx<0||cy<0||cx>=512||cy>=512||!scatterRouteAllowed(int(cx),int(cy)))
                    throw UnsupportedGroundRoute("Scatter route leaves immutable clearance domain");
                const auto* c=context_->map->table[std::size_t(cy)*512+std::size_t(cx)];
                if(!c||(c->flags&0x100u))throw UnsupportedGroundRoute("Scatter route crosses unsupported Cell");
            }
        };
        sample(a.state.movement.actor.position,at);
        std::array<int,24> queue;queue.fill(-1);
        for(std::size_t i=0;i<route->directions.size();++i){
            const auto [dx,dy]=directionOffset(route->directions[i]);
            const Coord next{at.x+dx*256,at.y+dy*256,at.z};sample(at,next);at=next;queue[i]=route->directions[i];
        }
        a.state.route=queue;
        a.commands.navigationTarget=a.state.destination;a.commands.pendingBodyTurn.reset();
        a.commands.manualTurret=false;a.commands.stopRequested=false;
        return true;
    }
    void select(int id){if(id!=-1)checkActor(id);selected_=id;}
    std::unique_ptr<OwnedUnitWorld> clone()const{
        auto base=context_->clone();
        // TerrainUnitContext is final and its clone preserves its dynamic type.
        std::unique_ptr<TerrainUnitContext> context(static_cast<TerrainUnitContext*>(base.release()));
        auto copy=std::make_unique<OwnedUnitWorld>(std::move(context),data_,numerics_,inputs_,turret0_);
        copy->commands_=commands_;copy->processes_->copyStateFrom(*processes_);copy->selected_=selected_;
        return copy;
    }
    bool process(int id,int speed,int tick,int timerPadding,const OwnedUnitWorldCall& call){
        checkActor(id);
        if(active_)throw std::logic_error("Owned world Process cannot reenter its owner");
        if(!call.failedRoute||!call.notify||!call.postCell||!call.noRoute)
            throw std::invalid_argument("Owned world requires explicit named Process services");
        struct Scope {
            const OwnedUnitWorldCall*& slot;
            explicit Scope(const OwnedUnitWorldCall*& s,const OwnedUnitWorldCall& c):slot(s){slot=&c;}
            ~Scope(){slot=nullptr;}
        } scope(active_,call);
        // The supplied direct router has no detour search. Repeating the same
        // positive route after a recursive rejection would recurse forever.
        // Supply at most one positive answer per Process; later requests fail.
        bool routeAttempted=false;
        return processes_->process(id,speed,tick,timerPadding,call.actorStore,call.rampStore,
            call.driveStore,call.failedRoute,call.decision,call.scatter,[this,id,&routeAttempted]{
                if(std::exchange(routeAttempted,true))return false;
                const auto p=actor(id).state.destination;
                return p!=Coord{}&&supplyScatterRoute(id,p.x/256,p.y/256);
            });
    }
    // The caller supplies command and both-actor scheduling policies on a fresh
    // owner. No preview is committed here; only domain refusals become results.
    OwnedUnitPreviewResult preview(const std::function<bool(OwnedUnitWorld&)>& operation)const{
        if(!operation)throw std::invalid_argument("Owned world preview requires an operation");
        auto copy=clone();
        try{return {operation(*copy)?OwnedUnitPreviewStatus::accepted:OwnedUnitPreviewStatus::rejected};}
        catch(const UnsupportedGroundRoute&){return {OwnedUnitPreviewStatus::unsupportedRoute};}
        catch(const UnsupportedGroundAdmission& e){return {OwnedUnitPreviewStatus::unsupportedAdmission,e.result};}
    }
    void turnTurret(int id,int delta,int tick){
        auto a=actor(id);a.commands.manualTurret=true;
        a.turret.setDesired(std::uint16_t(std::uint32_t(a.turret.desired)+std::uint32_t(delta)),tick);
    }
    void updateTurret(int id,int tick){
        auto a=actor(id);
        if(!a.commands.manualTurret&&!a.turret.rotating(tick)){
            const auto wanted=a.commands.navigationTarget?
                destinationDirection(data_->directionsToTargets,a.state.movement.actor.position,*a.commands.navigationTarget):
                a.state.movement.body.current(tick);
            a.turret.setDesired(wanted,tick);
        }
        a.commands.turretTurning=a.turret.rotating(tick);
    }
};
}
