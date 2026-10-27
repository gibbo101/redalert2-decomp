// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/PreparedInfantryMembership.hpp"
#include "sim/InfantryWalkState.hpp"
#include "sim/InfantryAdmission.hpp"
#include "sim/InfantrySpeed.hpp"
#include "sim/InfantryDestination.hpp"
#include "sim/WalkHead.hpp"
#include "sim/WalkRoute.hpp"
#include "sim/BorrowedUnitAdmission.hpp"
#include "sim/CellResidentKind6.hpp"
#include "sim/FootPermissionOverride.hpp"
#include "assets/NearbyCellAdmission.hpp"
namespace ra2 {
struct InfantryWalkBinding {
    InfantryWalkState& unit;
    const InfantryWalkType& type;
    std::reference_wrapper<const int> houseIndex;
    std::reference_wrapper<const float> countrySpeed;
    std::reference_wrapper<const std::uint8_t> human134;
    std::reference_wrapper<const std::uint8_t> human135;
};
using InfantryWalkStore=std::function<void(char,int,int,int,std::uint64_t)>;
struct InfantryKind6Search {
    const void* resident=nullptr;
    int kindQueries=0,nextReads=0;
};
// Single production composition. Every kernel borrows the same actors, Next,
// Cells, occupation, target, queue, timers, House and map/floor/fallback owners.
// It owns associations/services only; named effects and route finding remain
// supplied. All backing storage must remain stable for this binding's lifetime.
class PreparedInfantryWalk {
    friend struct BootCampWalkWorldInspection; // Borrowed identity regression checks only.
    MutableUnitMap& map_;
    std::span<InfantryMembershipCell> cells_;
    std::map<int,InfantryWalkBinding> actors_;
    InfantryWalkGlobals& globals_;
    const InfantrySubcellData& subcells_;
    OriginalRandomState& random_;
    const WalkMovementNumerics& numbers_;
    const std::array<std::uint32_t,108>& speeds_;
    std::array<std::uint32_t,12> unusedSpeeds_{};
    std::array<TerrainCellPoint,8> directions_;
    PreparedInfantryMembership membership_;
    BorrowedUnitAdmissionWorld admission_;
    std::map<int,const void*> otherResidents_;
    static std::map<int,InfantryMembershipActor> membershipActors(const std::map<int,InfantryWalkBinding>& actors){
        std::map<int,InfantryMembershipActor> result;
        for(const auto& [id,b]:actors){auto& a=b.unit;
            if(a.object.kind!=15)throw std::invalid_argument("Walk requires actual Infantry kind15");
            result.emplace(id,InfantryMembershipActor{a.ground,a.walk,a.object.next,a.eligible5a0,b.type.map205,
                {a.ground.marked74,a.redraw75,a.flag76,a.special370},b.houseIndex,a.object.mission.owner,b.type.image598});
        }return result;
    }
    void write(char kind,int id,int off,int width,std::uint64_t v){if(store)store(kind,id,off,width,v);}
    void fallbackStore(TerrainCellPoint p){
        write('C',int(map_.cells.size()),0x24,4,
            std::uint32_t(std::uint16_t(p.x))|(std::uint32_t(std::uint16_t(p.y))<<16));
    }
    static std::uint32_t link(std::uint32_t v){return v==UINT32_MAX?0:v+1;}
    auto movementTrace(int id){return [this,id](char k,std::int64_t off,std::int64_t v,std::int64_t){
        if(k!='A'&&k!='L')return;
        const bool byte=k=='L'?off>=0x34:(off==0x74||off==0x79||off==0x57a||off==0x57b||off==0x5a1||off==0x5cc);
        write(k,id,int(off),byte?1:4,std::uint32_t(v));
    };}
    WalkCommandServices commands(int id){
        WalkCommandServices s;s.trace=movementTrace(id);
        s.cellFlags=[this](Coord p){return membership_.walkMap().coordinate(p).flags;};
        s.projectionScale=[this]()->const double&{return globals_.projectionScale;};
        s.resetMovement=[this,id]{reset(id);};return s;
    }
    void reset(int id){auto& a=actors_.at(id).unit;
        resetInfantryWalkMovement(a.reset5cc,[this,id](int k,int x,int y){
            if(!animation)throw std::invalid_argument("Unbound Infantry animation4DC");animation(id,k,x,y);
        },movementTrace(id));
    }
    FootDestinationView foot(int id){auto& a=actors_.at(id).unit;
        return {a.field490,a.target494,a.suspended598,a.field5a1,
            {a.retry530[0],a.retry530[1],a.retry530[2]},{a.wait558[0],a.wait558[1],a.wait558[2]},
            {globals_.references,a.references}};
    }
public:
    int admission(int id,const void* c,int d,int l,int previous,int consult){
        auto& b=actors_.at(id);auto& a=b.unit;
        InfantryAdmissionServices s{[this](int c)->const int&{return membership_.attributes(c).overlay;},{},speeds_};
        s.permission=[this](int cell,std::uint8_t elevation){
            return nearbyCellPermitted(membership_.attributes(cell).input,elevation,map_.resident.permission);
        };
        s.permissionOverride=[&a,&b,id](int mover){
            if(mover!=id)throw std::invalid_argument("Foreign Infantry permission actor");
            FootPermissionOverrideServices override;
            override.typeTrainAa0=[&b]{return b.type.trainAa0;};
            override.mission=[&a]{return unitDiscoveryMission(a.object.mission);};
            return footPermissionOverride({a.flag32d,a.flag32c,a.team4c4},override);
        };
        s.resident=[&](int mover,int resident,int& stationary){
            InfantryResidentServices r{a.transport588,b.type.admissionC10,b.type.admissionC11,b.type.admissionC14};
            r.ally4E5580=[this](int left,int right){
                return unit_admission_policy::house(admission_.gates.objects.at(left).owner,
                    admission_.gates.objects.at(right).owner,admission_);
            };
            r.moving10=[this](int resident){return actors_.at(resident).unit.walk.moving34;};
            return ordinaryInfantryResident(mover,resident,stationary,admission_,r);
        };
        return ordinaryInfantryAdmission(id,membership_.cellId(c),d,l,previous,consult,admission_,
            {a.flag32d,a.special370,b.type.speedType5a4,globals_.loading},s);
    }
    InfantryWalkStore store;
    std::function<void(int,int)> arrivalNotification;
    std::function<void(int,int,int,int)> animation;
    std::function<void(int)> dirty;
    std::function<std::uint8_t(int,TerrainCellPoint,int,int)> route;
    std::function<Coord(const void*)> targetCoordinates;
    std::function<int(const void*)> targetIdentity;
    PreparedInfantryWalk(MutableUnitMap& map,std::span<InfantryMembershipCell> cells,
        std::map<int,InfantryWalkBinding> actors,UnitFoundationState& foundation,
        AdmissionHouses houses,
        const std::vector<std::optional<UnitAdmissionRegistry>>& registry,
        InfantryWalkGlobals& globals,const InfantrySubcellData& subcells,OriginalRandomState& random,
        const WalkMovementNumerics& numbers,const std::array<std::uint32_t,108>& speeds)
        :map_(map),cells_(cells),actors_(std::move(actors)),globals_(globals),subcells_(subcells),random_(random),numbers_(numbers),speeds_(speeds),
         membership_(map,cells,membershipActors(actors_),foundation,globals.occupationHeight,numbers.squareRoot,
             [this](MapInputPosition p){fallbackStore({p.x,p.y});}),
         admission_{{houses,{},{},map.slots,int(map.cells.size()),globals.tick,globals.setPadding,globals.commencePadding},
             {},{},registry,unusedSpeeds_,directions_,{}} {
        for(int d=0;d<8;++d){const auto [x,y]=directionOffset(d);directions_[std::size_t(d)]={std::int16_t(x),std::int16_t(y)};}
        for(const auto& [id,b]:actors_){auto& a=b.unit;auto& o=a.object;
            if(!houses.contains(o.mission.owner)||&b.houseIndex.get()!=&houses.at(o.mission.owner).index)
                throw std::invalid_argument("Infantry requires the actual shared House index");
            admission_.gates.objects.emplace(id,AdmissionGateObjectView{o.kind,o.next,o.mission.owner,o.gate,o.animation18,o.animation19,
                o.mission,o.statusA8,o.lastAC,o.timerStart,o.timerPadding,o.timerRemaining});
        }
        for(int id=0;id<=int(map.cells.size());++id){auto& c=membership_.attributes(id).input;auto& e=cells_[std::size_t(id)];
            admission_.gates.cells.emplace(id,AdmissionGateCellView{{c.position.x,c.position.y},e.head});
            admission_.cells.emplace(id,AdmissionCellView{e.registry,c.level,c.slope,c.flags,e.ground,e.elevated,
                e.groundHouse,e.elevatedHouse,c.land,e.alternateHead});
        }
        admission_.gates.forwardFallback=[this](TerrainCellPoint p){map_.fallback.input.position={p.x,p.y};};
        admission_.gates.fallbackStore=[this](TerrainCellPoint p){fallbackStore(p);};
        admission_.gates.store=[this](int id,int off,int width,std::uint32_t value){write('A',id,off,width,value);};
        auto& m=membership_.world();m.store=[this](int subject,int off,std::uint32_t v){
            // Legacy subjects overlap on large maps. These recovered field
            // offsets unambiguously distinguish foundation, Next and Cell.
            if(off<0x24)write('G',0,off,off==0||off==8?1:4,v);
            else if(off==0x30)write('A',subject,off,4,link(v));
            else {const bool pointer=off==0xe4||off==0xe8;write('C',subject-100,off,4,pointer?link(v):v);}
        };
        membership_.occupationStore=[this](InfantryOccupationCell c,int off,int width,std::uint32_t v){
            for(std::size_t i=0;i<cells_.size();++i)if(&c.ground==&cells_[i].ground){write('C',int(i),off,width,v);return;}
            throw std::invalid_argument("Foreign Walk occupation owner");
        };
    }
    PreparedInfantryWalk(const PreparedInfantryWalk&)=delete;
    PreparedInfantryWalk& operator=(const PreparedInfantryWalk&)=delete;
    PreparedInfantryWalk(PreparedInfantryWalk&&)=delete;
    PreparedInfantryWalk& operator=(PreparedInfantryWalk&&)=delete;
    PreparedInfantryMembership& membership(){return membership_;}
    // Only a passive kind6 resident binding, never a Walk/Drive or admission
    // object. Actual membership predecessor traversal borrows its live Next.
    void registerBuildingResident(int id,const void* identity,MembershipActorView view){
        auto& world=membership_.world();
        if(id<0||!identity||view.kind!=6||world.actors.contains(id))
            throw std::invalid_argument("Invalid distinct Building resident binding");
        for(const auto& [key,b]:actors_)if(identity==&b.unit||&view.next==&b.unit.object.next||&view.position==&b.unit.ground.position)
            throw std::invalid_argument("Building resident aliases Infantry");
        for(const auto& [key,p]:otherResidents_)if(p==identity||&world.actors.at(key).next==&view.next||&world.actors.at(key).position==&view.position)
            throw std::invalid_argument("Repeated Building resident identity or Next");
        world.actors.emplace(id,view);otherResidents_.emplace(id,identity);
    }

    std::uintptr_t cellIdentity(Coord point){
        return reinterpret_cast<std::uintptr_t>(membership_.walkMap().coordinate(point).identity);
    }
    MapCellInput& cellInput(TerrainCellPoint point){
        auto view=membership_.walkMap().word(point);
        return membership_.walkMap().attributes(view).input;
    }
    InfantryKind6Search findKind6(std::uintptr_t cellIdentity,const CellResidentKind6State& state){
        InfantryKind6Search result;if(!state.enabled)return result;
        const int cell=membership_.cellId(reinterpret_cast<const void*>(cellIdentity));
        if(cell<0||std::size_t(cell)>=cells_.size())throw std::invalid_argument("Infantry resident Cell outside owner");
        const int head=cells_[std::size_t(cell)].head;
        const auto idOf=[this](const void* identity){
            for(const auto& [id,b]:actors_)if(identity==&b.unit)return id;
            for(const auto& [id,p]:otherResidents_)if(identity==p)return id;
            throw std::invalid_argument("Foreign Infantry resident actor identity");
        };
        const auto identity=[this](int id)->const void*{
            if(id==-1)return nullptr;
            const auto found=actors_.find(id);
            if(found!=actors_.end())return &found->second.unit;
            const auto other=otherResidents_.find(id);
            if(other!=otherResidents_.end())return other->second;
            throw std::invalid_argument("Foreign Infantry resident Next identity");
        };
        CellResidentKind6Services services;
        services.kind=[&](const void* resident){++result.kindQueries;const int id=idOf(resident);
            const auto own=actors_.find(id);return own==actors_.end()?membership_.world().actors.at(id).kind:own->second.unit.object.kind;};
        services.next=[&](const void* resident){++result.nextReads;return identity(membership_.world().actors.at(idOf(resident)).next);};
        result.resident=findCellResidentKind6(state,{identity(head)},services);return result;
    }
    // Rebind borrowed fields at the original owner1B4 store without rebuilding
    // maps, callbacks, actor state or occupation. All validation precedes writes.
    // Speed/control references are supplied by the enclosing canonical House owner.
    void rebindHouse(int id,int owner,const int& index,const float& speed,
            const std::uint8_t& human,const std::uint8_t& control){
        auto& b=actors_.at(id);
        if(!admission_.gates.houses.contains(owner)||&index!=&admission_.gates.houses.at(owner).index||
           &membership_.actor(id).owner!=&b.unit.object.mission.owner)
            throw std::invalid_argument("Infantry rebind requires the actual shared House index/owner");
        membership_.rebindHouseIndex(id,index);
        b.houseIndex=std::cref(index);b.countrySpeed=std::cref(speed);
        b.human134=std::cref(human);b.human135=std::cref(control);
        b.unit.object.mission.owner=owner;
    }
    bool commence(int id){return movement_gate_policy::commence(id,admission_.gates);}
    bool mark(int id,int mode){return membership_.mark(id,mode,[this,id](int off,std::uint8_t v){write('A',id,off,1,v);});}
    void order(int id,const void* target,std::uint8_t flag=1){auto& b=actors_.at(id);auto& a=b.unit;const auto& t=b.type;
        InfantryDestinationServices s;
        s.house=[this,&b]{return InfantryDestinationHouse{globals_.session,b.human134.get(),b.human135.get()};};
        s.animation=[this,id](int k,int x,int y){if(!animation)throw std::invalid_argument("Unbound Infantry animation");animation(id,k,x,y);};
        s.foot.coordinates=[this](const void* p){if(!targetCoordinates)throw std::invalid_argument("Unbound Walk target coordinates");return targetCoordinates(p);};
        s.foot.targetId=[this](const void* p){if(!targetIdentity)throw std::invalid_argument("Unbound Walk target identity");return targetIdentity(p);};
        s.foot.tick=[this]{return globals_.tick;};s.foot.delay=[this]{return globals_.destinationDelay;};
        s.foot.trace=[this,id](char k,int off,int n,std::int64_t v){
            if(k=='a')write('A',id,off,n,std::uint32_t(v));
            else if(k=='C')write('G',1,0,4,std::uint32_t(v));
            else if(k=='I')write('L',id,0x14,4,std::uint32_t(v));
        };
        setOrdinaryInfantryDestination({foot(id),a.route,a.object.mission,a.state5ac,a.flag5c3,t.jumpJetB44,t.c0d,t.c00,a.effect25c},
            a.walk,{a.immobilized3fc,a.disabled204,a.disabled205},target,flag,globals_.orderPadding,s,commands(id));
    }
    std::uint8_t process(int id){auto& b=actors_.at(id);auto& a=b.unit;
        WalkHeadInputs input{subcells_,random_,b.houseIndex.get(),globals_.occupationHeight,globals_.bridgeHeight,globals_.levelHeight};
        WalkHeadServices head;head.squareRoot=numbers_.squareRoot;
        head.cell=[this](const Coord& p){auto v=membership_.walkMap().coordinate(p);
            return WalkHeadCell{membership_.occupation(v),membership_.walkMap().attributes(v).overlay};};
        head.floor=[this](const Coord& p){return membership_.walkMap().floor(p);};
        head.cellStore=membership_.occupationStore;
        head.headStore=[this,id](int off,int v){write('L',id,off,4,std::uint32_t(v));};
        WalkRouteContext refill{{a.retry530[0],a.retry530[1],a.retry530[2]},a.counter53c,a.state5ac,a.target494,b.type.jumpJetB44,
            globals_.routeInterval,globals_.routePadding,[this]{return globals_.tick;},
            [this,id](TerrainCellPoint p,int x,int y){if(!route)throw std::invalid_argument("Unbound Infantry route provider");return route(id,p,x,y);}};
        WalkQueuedContext queued{{a.ground.position,a.object.mission,a.target494},input,head,a.transition57b,
            [this](const Coord& p){return membership_.walkMap().coordinate(p);},
            [this,id,&a,&b](WalkMovementCellView c,int d,int l,int zero,int one){
                if(zero||one!=1)throw std::invalid_argument("Infantry admission argument association");
                return admission(id,c.identity,d,l,-1,one);
            },&refill};
        WalkMovementServices movement;movement.trace=movementTrace(id);
        movement.speed=[this,&a,&b]{
            InfantrySpeedServices s{[&b]{const auto& t=b.type;return InfantrySpeedType{t.speed5a0,t.veteranSpeed26c,t.eliteSpeed27e,t.c0b};},
                [&b]()->const float&{return b.countrySpeed.get();},[this]()->const double&{return globals_.veteranSpeed;},{}};
            return infantrySpeed({a.veterancy118,a.percentage468,a.multiplier470,a.flag5c3},s);
        };
        movement.placement.mark=[this,id](int mode){mark(id,mode);};
        movement.placement.floor=[this](Coord p){return membership_.walkMap().floor(p);};
        movement.lookup=[this](TerrainCellPoint p){return membership_.walkMap().word(p);};
        movement.currentCell=[this](Coord p){return membership_.walkMap().coordinate(p);};
        movement.dirty=[this](WalkMovementCellView c){if(!dirty)throw std::invalid_argument("Unbound Walk dirty Cell effect");dirty(membership_.cellId(c));};
        WalkArrivalContext arrival{{a.route,a.cell450,a.onMap7d,a.flag76,a.flag7a,a.secondary574},{}};
        arrival.services.notify=[this,id](int k){if(!arrivalNotification)throw std::invalid_argument("Unbound Infantry arrival notification");arrivalNotification(id,k);};
        arrival.services.destination=[this,id](int target,int flag){if(target)throw std::invalid_argument("Non-null arrival destination");order(id,nullptr,std::uint8_t(flag));};
        arrival.services.resetMovement=[this,id]{reset(id);};
        return processQueuedWalk(a.walk,{a.ground,a.body,a.immobilized3fc,a.percentage468,a.field5a1,a.field57a},numbers_,movement,arrival,queued,globals_.tick);
    }
};
}
