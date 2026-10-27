// SPDX-License-Identifier: GPL-3.0-or-later
// Borrow two exact membership-bound Process records and their shared map/type.
// The enclosing stable owner keeps records, services, map and Drive data alive.
// Initial type/House/timer records and named services are explicit supplied inputs.
// This binding does not construct actors or schedule ticks.
#pragma once
#include "assets/BorrowedPreparedUnitAdmission.hpp"
#include "assets/OwnedUnitScatter.hpp"
#include <array>
#include <memory>
#include <stdexcept>
#include <bit>
#include <utility>
namespace ra2 {
// Opaque retry/wait padding is supplied at its separate child boundaries.
struct OwnedUnitProcessActorInputs {
    GroundDriveResidentRetry retry;
    int waitPadding=0;
};
// Opt-in only after the enclosing world's membership/preview/drawing evidence.
// The default retains the existing live Advance6/7 refusals.
enum class OwnedUnitAdvancePolicy { guarded, ordinaryAdmission, ordinaryScatter };
struct OwnedUnitProcessesInputs {
    std::uint8_t flags=0,crusher=0;
    int houseIndex=0;
    std::uint32_t houseAllies=0;
    int waitDuration=0;
    std::array<OwnedUnitProcessActorInputs,2> actors;
    OwnedUnitAdvancePolicy advancePolicy=OwnedUnitAdvancePolicy::guarded;
    std::shared_ptr<const OwnedUnitScatterInputs> scatter={};
};
// Immovable: shared query callbacks capture this binding. Clone logical records
// into fresh owners, construct/rebind here, then copy the two wait records.
class OwnedUnitProcesses {
    OwnedUnitProcessesInputs inputs_;
    PreparedUnitMembership& member_;
    std::array<GroundDriveProcessState*,2> actors_;
    std::array<GroundDriveProcessServices,2> services_;
    PreparedMembershipMap map_;
    const DriveData& data_;
    std::array<PreparedAdmissionActor,2> admissionActors_;
    std::vector<PreparedAdmissionCell> admissionCells_;
    PreparedAdmissionShared shared_;
    std::unique_ptr<BorrowedPreparedUnitAdmission> admission_;
    std::unique_ptr<OwnedUnitScatter> scatter_;
    PreparedUnitMembership::Query query_;
    GroundDriveProcessState& state(int id){return *actors_.at(std::size_t(id));}
    // Validate the supported profile without refreshing projected gameplay state.
    // Admission reads each actual owner when its recovered consumer enters.
    void validateLive(int tick){
        auto& member=member_;
        if(member.membership.actors.size()!=2||!member.membership.actors.contains(0)||
           !member.membership.actors.contains(1)||member.houses.loading!=1)
            throw std::invalid_argument("Owned Process requires two loaded Unit bindings");
        shared_.tick=tick;
        for(int id:{0,1}){
            const auto& a=member.membership.actors.at(id);
            const auto& d=member.actorDiscovery(id);
            const auto& movement=member.actorState(id).movement;
            if(d.owner!=inputs_.houseIndex||d.hasTag||a.alternate||movement.actor.bridge79||
               (a.next!=-1&&!member.membership.actors.contains(a.next)))
                throw std::invalid_argument("Owned Process requires nonbridge House0 Units");
        }
        for(std::size_t i=0;i<=map_.cells.size();++i){
            const auto& m=member.cellMembership(i);
            const auto valid=[&](int id){return id==-1||member.membership.actors.contains(id);};
            if(!valid(m.head)||!valid(m.alternateHead))
                throw std::invalid_argument("Owned Process Cell has an unbound resident");
        }
    }
    int identity(const GroundDriveCell& c){
        const auto* p=static_cast<const MapCellInput*>(c.identity);
        if(p==&map_.fallback.input)return int(map_.cells.size());
        if(!p)throw std::invalid_argument("Null owned Process Cell");
        const int slot=int(p->position.y)*512+int(p->position.x);
        if(slot<0||slot>=262144)throw std::invalid_argument("Owned Process Cell outside slots");
        const int id=map_.slots[std::size_t(slot)];
        if(id<0||std::size_t(id)>=map_.cells.size()||&map_.cells[std::size_t(id)]->input!=p)
            throw std::invalid_argument("Noncanonical owned Process Cell");
        return id;
    }
public:
    OwnedUnitProcesses(const OwnedUnitProcesses&)=delete;
    OwnedUnitProcesses& operator=(const OwnedUnitProcesses&)=delete;
    OwnedUnitProcesses(OwnedUnitProcesses&&)=delete;
    OwnedUnitProcesses& operator=(OwnedUnitProcesses&&)=delete;
    // Persistent per-actor state. Initial values and clone copies are supplied.
    std::array<GroundDriveMovingWaitState,2> wait;
    OwnedUnitProcesses(PreparedMembershipMap map,PreparedUnitMembership& member,
        std::array<GroundDriveProcessState*,2> actors,std::array<GroundDriveProcessServices,2> services,
        const DriveData& data,OwnedUnitProcessesInputs inputs,PreparedUnitMembership::Query query)
        :inputs_(inputs),member_(member),actors_(actors),services_(std::move(services)),map_(map),data_(data),query_(std::move(query)){
        if(inputs_.flags!=5||inputs_.crusher!=1||inputs_.houseIndex!=0||inputs_.houseAllies!=0)
            throw std::invalid_argument("Owned Process supplied profile outside bounded type/House domain");
        if(inputs_.advancePolicy!=OwnedUnitAdvancePolicy::guarded&&
           inputs_.advancePolicy!=OwnedUnitAdvancePolicy::ordinaryAdmission&&
           inputs_.advancePolicy!=OwnedUnitAdvancePolicy::ordinaryScatter)
            throw std::invalid_argument("Unknown owned Advance admission policy");
        if((inputs_.advancePolicy==OwnedUnitAdvancePolicy::ordinaryScatter)!=bool(inputs_.scatter))
            throw std::invalid_argument("Owned Scatter requires its explicit supplied inputs");
        // Check associations before installing callbacks, without any map/floor query.
        const auto shared=member_.world();
        if(member_.membership.actors.size()!=2||!member_.membership.actors.contains(0)||
           !member_.membership.actors.contains(1)||map_.slots.size()!=262144||
           map_.cells.size()+1!=member_.occupation.size()||!shared.fallbackStore||
           shared.cells.size()!=map_.slots.size()||
           shared.cells.data()!=map_.resident.world.cells.data()||shared.fallback!=&map_.fallback.input)
            throw std::invalid_argument("Owned Processes require canonical shared membership Cells");
        for(std::size_t slot=0;slot<map_.slots.size();++slot){
            const int id=map_.slots[slot];
            if(id<0){
                if(shared.cells[slot])throw std::invalid_argument("Owned Process missing Cell index");
            }else if(std::size_t(id)>=map_.cells.size()||!map_.cells[std::size_t(id)]||
                     shared.cells[slot]!=&map_.cells[std::size_t(id)]->input)
                throw std::invalid_argument("Owned Process map/member identity differs");
        }
        for(int id:{0,1}){
            if(!actors_[id]||&member_.actorState(id)!=actors_[id])
                throw std::invalid_argument("Owned Process requires exact distinct member actor records");
            for(unsigned i=0;i<12;++i)
                if(std::bit_cast<std::uint32_t>(services_[id].trackSpeed[i])!=
                   std::bit_cast<std::uint32_t>(services_[0].trackSpeed[i]))
                    throw std::invalid_argument("Owned Process shared type speeds differ");
        }
        shared_.houses[inputs_.houseIndex]={inputs_.houseIndex,inputs_.houseAllies};
        shared_.directions={TerrainCellPoint{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};
        for(unsigned i=0;i<12;++i)shared_.speedBits[i]=std::bit_cast<std::uint32_t>(services_[0].trackSpeed[i]);
        admissionCells_.resize(map_.cells.size()+1);
        for(auto& a:admissionActors_){a.flags=inputs_.flags;a.crusher=inputs_.crusher;}
        admission_=std::make_unique<BorrowedPreparedUnitAdmission>(map_,member_,
            std::map<int,PreparedAdmissionActorBinding>{{0,{state(0),member_.actorDiscovery(0),admissionActors_[0]}},
                {1,{state(1),member_.actorDiscovery(1),admissionActors_[1]}}},admissionCells_,shared_,data_,services_[0].squareRoot);
        admission_->world().trace=[this](char k,int a,int b,int){
            if(k=='L'&&query_)query_('W',{a,b,0});
        };
        if(inputs_.scatter)scatter_=std::make_unique<OwnedUnitScatter>(map_,member_,*admission_,actors_,
            admissionActors_,wait,*inputs_.scatter);
    }
    bool hasScatter()const{return bool(scatter_);}
    const void* const& movementTargetStorage(int id)const{return admissionActors_.at(std::size_t(id)).destination.target494;}
    const MapCellInput* movementTarget(int id)const{return static_cast<const MapCellInput*>(admissionActors_.at(std::size_t(id)).destination.target494);}
    const MapCellInput* pendingScatterRoute(int id)const{return scatter_?scatter_->pendingRoute(id):nullptr;}
    void scatterRouted(int id){if(scatter_)scatter_->routed(id);}
    void clearTarget(int id){if(scatter_)scatter_->clearTarget(id);}
    bool scatterRouteAllowed(int x,int y)const{return scatter_&&scatter_->routeAllowed(x,y);}
    int preparationCounter(int id)const{return scatter_?scatter_->preparationCounter(id):0;}
    void copyStateFrom(const OwnedUnitProcesses& from){
        if(inputs_.advancePolicy!=from.inputs_.advancePolicy||inputs_.scatter!=from.inputs_.scatter||
           admissionCells_.size()!=from.admissionCells_.size())
            throw std::invalid_argument("Owned Process clone profile differs");
        wait=from.wait;shared_=from.shared_;
        std::copy(from.admissionCells_.begin(),from.admissionCells_.end(),admissionCells_.begin());
        for(int i:{0,1}){
            const auto* target=from.admissionActors_[i].destination.target494;
            admissionActors_[i]=from.admissionActors_[i];
            if(target){
                const void* rebound=nullptr;
                for(std::size_t c=0;c<=map_.cells.size();++c){
                    const auto& src=c==map_.cells.size()?from.map_.fallback:*from.map_.cells[c];
                    if(target==&src.input){rebound=&(c==map_.cells.size()?map_.fallback:*map_.cells[c]).input;break;}
                }
                if(!rebound)throw std::invalid_argument("Owned Process clone target is not an actual Cell");
                admissionActors_[i].destination.target494=rebound;
            }
        }
        if(scatter_)scatter_->copyStateFrom(*from.scatter_);
    }
    bool process(int id,int speed,int tick,int timerPadding,
        const GroundStateStore& actorStore,const GroundStateStore& rampStore,
        const GroundStateStore& driveStore,const std::function<void(int)>& failedRoute,
        const std::function<void(char,int)>& decision={},const ScatterWorldTrace& scatterTrace={},
        const std::function<bool()>& findRoute={}){
        if(id!=0&&id!=1)throw std::invalid_argument("Unknown owned Process actor");
        if(!failedRoute)throw std::invalid_argument("Owned Process requires a named failed-route service");
        // These callbacks are local to this synchronous Process call.
        auto services=services_.at(std::size_t(id));
        services.admit={};services.reserve={};services.advance.driveStore=driveStore;
        services.markNext=[this,id,tick](auto x,auto y){
            validateLive(tick);admission_->nextCell(id,{x,y},1);
        };
        GroundDriveAdmissionServices admission;admission.driveStore=driveStore;
        admission.check=[this,id,tick,&decision](const auto& c,int direction,int level){
            validateLive(tick);
            const int result=admission_->admit(id,identity(c),direction,level,-1,1);
            if(decision)decision('D',result);return result;
        };
        const auto gate=[this,id,tick,&decision](auto x,auto y){validateLive(tick);
            const bool result=admission_->gates(id,{x,y});if(decision)decision('G',result);return result;};
        GroundDriveMovingWaitServices waiting;waiting.duration=inputs_.waitDuration;waiting.temporaryPadding=inputs_.actors.at(id).waitPadding;
        waiting.failedRoute=failedRoute; // Named failed-pathfinder/accessibility/mission services are supplied.
        if(scatter_){
            validateLive(tick);
            return scatter_->process(id,speed,tick,timerPadding,data_,services,admission,gate,
                inputs_.actors.at(id).retry,waiting,actorStore,rampStore,scatterTrace,findRoute);
        }
        const auto entry=inputs_.advancePolicy==OwnedUnitAdvancePolicy::ordinaryAdmission?
            processAdvanceAdmittedOrdinaryGroundDrive:processMovingResidentOrdinaryGroundDrive;
        return entry(state(id),data_,speed,tick,timerPadding,services,gate,admission,
            inputs_.actors.at(id).retry,wait[std::size_t(id)],waiting,actorStore,rampStore);
    }
};
}
