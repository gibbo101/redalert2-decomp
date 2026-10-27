// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/BorrowedPreparedUnitAdmission.hpp"
#include <memory>

namespace ra2::test {
// Supplied diagnostic setup only. No value admission world is consumed once
// binding finishes; decisions run on these actual prepared records thereafter.
struct BorrowedAdmissionFixture {
    BorrowedAdmissionFixture(const BorrowedAdmissionFixture&)=delete;
    BorrowedAdmissionFixture& operator=(const BorrowedAdmissionFixture&)=delete;
    BorrowedAdmissionFixture(BorrowedAdmissionFixture&&)=delete;
    BorrowedAdmissionFixture& operator=(BorrowedAdmissionFixture&&)=delete;
    std::array<MapCellAttributes,3> attributes;
    std::array<MapCellAttributes*,2> cells{&attributes[0],&attributes[1]};
    std::vector<int> slots=std::vector<int>(262144,-1);
    std::vector<MapCellInput*> table=std::vector<MapCellInput*>(262144,nullptr);
    MapFloorHeightState floor;
    std::array<std::uint8_t,4> buffer4{};
    std::array<std::uint8_t,10> buffer10{};
    std::array<GroundDriveProcessState,2> drives;
    UnitMarkState mark1;
    UnitDiscoveryActor mission1;
    std::array<PreparedAdmissionActor,2> actors;
    std::array<PreparedAdmissionCell,3> admissionCells;
    PreparedAdmissionShared shared;
    std::function<double(double)> squareRoot;
    std::unique_ptr<PreparedUnitMembership> member;
    std::unique_ptr<BorrowedPreparedUnitAdmission> admission;
    int queries=0,stores=0,fallbackStores=0;
    PreparedMembershipMap map(){
        ResidentCellInputs resident;resident.world={table,&attributes[2].input,{},{}};
        return {cells,slots,attributes[2],floor,resident,buffer4,buffer10,1,1,104};
    }
    BorrowedAdmissionFixture(UnitAdmissionWorld& input,const UnitAdmissionMotionWorld& motion){
        if(input.gates.fallbackCell!=2||input.gates.slots.size()!=slots.size())
            throw std::invalid_argument("Borrowed fixture requires three distinct Cells");
        std::copy(input.gates.slots.begin(),input.gates.slots.end(),slots.begin());
        for(std::size_t i=0;i<table.size();++i){
            if(slots[i]<-1||slots[i]>1)throw std::invalid_argument("Borrowed fixture slot outside map");
            if(slots[i]!=-1)table[i]=&attributes[std::size_t(slots[i])].input;
        }
        for(int i=0;i<3;++i){
            const auto& c=input.cells.at(i);const auto& g=input.gates.cells.at(i);
            if(g.head>1||c.elevatedHead>1)throw std::invalid_argument("Borrowed fixture has an unbound resident");
            auto& a=attributes[i].input;a.position={g.point.x,g.point.y};a.level=c.level;a.slope=c.ramp;a.flags=c.flags;a.land=c.land;
            admissionCells[i]={c.registry,c.owner,c.elevatedOwner};
        }
        member=std::make_unique<PreparedUnitMembership>(map(),
            [this](char k,int id,int offset,std::uint32_t){++stores;if(k=='c'&&id==2&&offset==0x24)++fallbackStores;},
            [this](char,Coord){++queries;});
        member->houses.loading=1;
        for(int i=0;i<2;++i){
            const auto& g=input.gates.objects.at(i);const auto& o=input.objects.at(i);const auto& m=motion.actors.at(i);
            if(g.kind!=1||g.gate||g.next>1||o.target>1||o.destination>1)
                throw std::invalid_argument("Borrowed fixture requires ordinary two-Unit associations");
            auto& a=actors[i];a.flags=o.flags;a.crushable=o.crushable;a.crusher=o.crusher;a.train=o.train;
            a.building1350=o.building1350;a.state1b8=o.state1b8;a.destination1b0=o.destination;
            a.weapon=o.weapon;a.projectile275=o.projectile275;a.shortTrack=m.shortTrack;
            auto& d=drives[i];auto& move=d.movement;move.actor.position=m.position;d.destination=m.destination;
            move.head=m.head;move.body=m.body;move.reached5a0=m.eligibility5a0;move.track=m.track;move.index=m.index;
            d.route.fill(-1);d.route[0]=m.queueHead;
            if(o.target!=-1)a.destination.target494=&drives[std::size_t(o.target)];
        }
        member->discovery=input.gates.objects.at(0).mission;
        member->discovery.owner=input.gates.objects.at(0).owner;
        mission1=input.gates.objects.at(1).mission;mission1.owner=input.gates.objects.at(1).owner;
        member->bind({},drives[0]);member->bindParked({},drives[1],mark1,mission1);
        for(int i=0;i<2;++i)member->membership.actors.at(i).next=input.gates.objects.at(i).next;
        for(int i=0;i<3;++i){
            auto& list=member->membership.cells.at(member->membership.fallbackCell-2+i);
            list.head=input.gates.cells.at(i).head;list.alternateHead=input.cells.at(i).elevatedHead;
            member->occupation[i].ground=input.cells.at(i).occupation;
            member->occupation[i].elevated=input.cells.at(i).elevatedOccupation;
        }
        shared.houses=input.gates.houses;shared.registry=input.registry;shared.speedBits=input.speedBits;
        shared.directions=input.directions;shared.tick=input.gates.tick;shared.setPadding=input.gates.setPadding;
        shared.commencePadding=input.gates.commencePadding;squareRoot=motion.squareRoot;
        admission=std::make_unique<BorrowedPreparedUnitAdmission>(map(),*member,
            bindings(),admissionCells,shared,*motion.data,squareRoot);
        if(queries||stores)throw std::runtime_error("Borrowed admission binding queried or changed the prepared world");
    }
    std::map<int,PreparedAdmissionActorBinding> bindings(){
        return {{0,{drives[0],member->discovery,actors[0]}},{1,{drives[1],mission1,actors[1]}}};
    }
};
}
