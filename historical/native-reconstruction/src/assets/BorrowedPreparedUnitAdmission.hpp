// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/PreparedUnitMembership.hpp"
#include "sim/BorrowedUnitAdmission.hpp"
#include "sim/UnitDestination.hpp"
#include "sim/UnitNextCell.hpp"

namespace ra2 {
// Fields absent from the existing prepared membership/map/Drive owners. These
// are explicit supplied records, not construction, a second mission or a Drive.
struct PreparedAdmissionActor {
    int kind=1;
    std::uint8_t gate=0,animation18=0,animation19=0;
    int statusA8=0,lastAC=0,timerStart=0,timerPadding=0,timerRemaining=0;
    std::uint8_t flags=5,crushable=0,crusher=0,train=0,building1350=0,shortTrack=0;
    int state1b8=0,destination1b0=-1;
    bool weapon=false,projectile275=false;
    UnitDestinationState destination;
};
struct PreparedAdmissionCell {
    std::int16_t registry=-1;
    int owner=-1,elevatedOwner=-1;
};
struct PreparedAdmissionShared {
    std::map<int,MovementGateHouse> houses;
    std::vector<std::optional<UnitAdmissionRegistry>> registry;
    std::array<std::uint32_t,12> speedBits{};
    std::array<TerrainCellPoint,8> directions{};
    int tick=0,setPadding=0,commencePadding=0;
};
struct PreparedAdmissionActorBinding {
    GroundDriveProcessState& drive;
    UnitDiscoveryActor& mission;
    PreparedAdmissionActor& extra;
};
// Separate, unwired production binding. Existing owned Process/runtime policy
// is unchanged. Every mutable consumer field borrows the prepared owners.
// Reconstruct this binding over a clone; do not copy its reference maps/callbacks.
class BorrowedPreparedUnitAdmission {
    PreparedUnitMembership& member_;
    std::map<const void*,int> targetIds_;
    std::map<int,PreparedAdmissionActorBinding> actors_;
    BorrowedUnitAdmissionWorld world_;
    BorrowedAdmissionMotionWorld motion_;
public:
    BorrowedPreparedUnitAdmission(PreparedMembershipMap map,PreparedUnitMembership& member,
        std::map<int,PreparedAdmissionActorBinding> actors,
        std::span<PreparedAdmissionCell> cells,PreparedAdmissionShared& shared,
        const DriveData& data,std::function<double(double)>& squareRoot)
        :member_(member),actors_(std::move(actors)),
         world_{{shared.houses,{},{},map.slots,int(map.cells.size()),shared.tick,shared.setPadding,
             shared.commencePadding,{},{},{},{},{},{}},{},{},shared.registry,shared.speedBits,shared.directions,{}},
         motion_{{},&data,squareRoot}{
        // Pure association checks. No floor, permission, coordinate or lazy query.
        const auto prepared=member.world();
        if(map.cells.size()>16384||map.slots.size()!=262144||cells.size()!=map.cells.size()+1||
           member.occupation.size()!=cells.size()||prepared.fallback!=&map.fallback.input||
           prepared.cells.data()!=map.resident.world.cells.data()||
           actors_.empty()||actors_.size()!=member.membership.actors.size()||!squareRoot)
            throw std::invalid_argument("Prepared admission requires exact loaded owner associations");
        const int base=member.membership.fallbackCell-int(map.cells.size());
        std::map<const void*,int> missions;
        for(const auto& [id,a]:actors_){
            if(!member.membership.actors.contains(id)||&member.actorState(id)!=&a.drive||
               &member.actorDiscovery(id)!=&a.mission||a.extra.kind!=1||a.extra.gate)
                throw std::invalid_argument("Prepared admission requires actual Unit/Drive/mission owners");
            if(!targetIds_.emplace(&a.drive,id).second||!missions.emplace(&a.mission,id).second)
                throw std::invalid_argument("Prepared admission actors must have distinct Drive and mission owners");
        }
        for(std::size_t i=0;i<cells.size();++i){
            if(i<map.cells.size()&&!map.cells[i])throw std::invalid_argument("Missing prepared admission Cell");
            auto& input=(i==map.cells.size()?map.fallback:*map.cells[i]).input;
            auto& list=member.membership.cells.at(base+int(i));
            if(&list!=&member.cellMembership(i))throw std::invalid_argument("Split prepared admission Cell heads");
            auto& occupation=member.occupation[i];auto& extra=cells[i];
            world_.gates.cells.emplace(int(i),AdmissionGateCellView{{input.position.x,input.position.y},list.head});
            world_.cells.emplace(int(i),AdmissionCellView{extra.registry,input.level,input.slope,input.flags,
                occupation.ground,occupation.elevated,extra.owner,extra.elevatedOwner,input.land,list.alternateHead});
            if(!targetIds_.emplace(&input,-2).second)
                throw std::invalid_argument("Prepared admission Cells must have distinct identities");
        }
        for(std::size_t slot=0;slot<map.slots.size();++slot){
            const int id=map.slots[slot];const auto actual=member.membership.slots.find(int(slot));
            if(id==-1){
                if(prepared.cells[slot]||actual!=member.membership.slots.end())
                    throw std::invalid_argument("Prepared admission has a split missing-slot association");
            }else if(id<0||std::size_t(id)>=map.cells.size()||
                prepared.cells[slot]!=&map.cells[std::size_t(id)]->input||
                actual==member.membership.slots.end()||actual->second!=base+id)
                throw std::invalid_argument("Prepared admission has a noncanonical slot association");
        }
        for(const auto& [id,a]:actors_){
            auto& list=member.membership.actors.at(id);auto& extra=a.extra;
            auto& drive=a.drive;auto& m=drive.movement;
            world_.gates.objects.emplace(id,AdmissionGateObjectView{extra.kind,list.next,a.mission.owner,
                extra.gate,extra.animation18,extra.animation19,a.mission,extra.statusA8,extra.lastAC,
                extra.timerStart,extra.timerPadding,extra.timerRemaining});
            world_.objects.emplace(id,AdmissionObjectView{extra.flags,extra.crushable,extra.crusher,extra.train,
                extra.building1350,extra.state1b8,extra.destination1b0,extra.weapon,extra.projectile275,
                extra.destination.target494,targetIds_});
            motion_.actors.emplace(id,AdmissionMotionView{m.actor.position,drive.destination,m.head,m.body,
                m.reached5a0,drive.route[0],m.track,m.index,extra.shortTrack});
        }
        world_.gates.forwardFallback=[this](TerrainCellPoint p){member_.world().fallbackStore({p.x,p.y});};
        world_.gates.forwardAssignedFallback=[this](TerrainCellPoint p){member_.forwardAssignedFallback({p.x,p.y});};
    }
    BorrowedPreparedUnitAdmission(const BorrowedPreparedUnitAdmission&)=delete;
    BorrowedPreparedUnitAdmission& operator=(const BorrowedPreparedUnitAdmission&)=delete;
    BorrowedPreparedUnitAdmission(BorrowedPreparedUnitAdmission&&)=delete;
    BorrowedPreparedUnitAdmission& operator=(BorrowedPreparedUnitAdmission&&)=delete;
    BorrowedUnitAdmissionWorld& world(){return world_;}
    const BorrowedAdmissionMotionWorld& motion()const{return motion_;}
    int admit(int mover,int cell,int direction,int level,int previous,std::uint8_t consult){
        return unit_admission_policy::unitAdmission(mover,cell,direction,level,previous,consult,world_,&motion_);
    }
    int terrain(int cell,int direction,int& level,std::uint8_t& elevated,int previous){
        return unit_admission_policy::unitTerrainAdmission(cell,direction,level,elevated,previous,world_);
    }
    bool gates(int mover,TerrainCellPoint p){return movement_gate_policy::checkMovementGates(mover,p,world_.gates);}
    void nextCell(int mover,TerrainCellPoint p,std::uint8_t warning){
        const auto& m=actors_.at(mover).drive.movement;
        unit_next_cell_policy::ordinaryUnitNextCell(mover,{m.actor.position,m.actor.bridge79},p,warning,world_);
    }
};
}
