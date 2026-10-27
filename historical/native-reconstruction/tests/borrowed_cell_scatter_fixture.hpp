// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/BorrowedCellUnitScatterWorld.hpp"
#include <memory>
namespace ra2::test {
// Initial diagnostic records are supplied once. Only the prepared records are
// consumed during roots. exportObservations is called afterwards to format the
// existing original oracle's five-actor diagnostic output, never for admission.
struct BorrowedCellScatterFixture {
    std::array<MapCellAttributes,10> attributes;
    std::array<MapCellAttributes*,9> cells;
    std::vector<int> slots;
    std::vector<MapCellInput*> table;
    std::array<ScatterWorldCellBinding,10> cellBindings;
    std::array<PreparedAdmissionActor,2> actors;
    std::array<PreparedAdmissionCell,10> admissionCells;
    PreparedAdmissionShared shared;
    UnitMarkState mark1;
    UnitDiscoveryActor mission1;
    std::array<std::uint8_t,4> buffer4{};
    std::array<std::uint8_t,10> buffer10{};
    std::function<double(double)> squareRoot;
    MapFloorHeightState& floor;
    std::unique_ptr<PreparedUnitMembership> member;
    std::unique_ptr<BorrowedPreparedUnitAdmission> admission;
    int queries=0,stores=0,fallbackStores=0;
    PreparedMembershipMap map(){
        ResidentCellInputs resident;resident.world={table,&attributes[9].input,{},{}};
        return {cells,slots,attributes[9],floor,resident,buffer4,buffer10,1,1,104};
    }
    BorrowedCellScatterFixture(UnitAdmissionWorld& source,std::array<UnitDestinationState,5>& state,
        std::array<GroundDriveProcessState,5>& drives,const std::array<std::uint8_t,5>& eligibility,
        const std::array<std::uint8_t,5>& shortTrack,std::array<MapCellInput,10>& inputs,
        const std::array<ScatterWorldCellBinding,10>& bindings,MapFloorHeightState& height,
        const DriveData& data,std::function<double(double)> root)
        :slots(source.gates.slots.begin(),source.gates.slots.end()),table(262144,nullptr),
         squareRoot(std::move(root)),floor(height){
        if(source.gates.fallbackCell!=9||slots.size()!=262144)
            throw std::invalid_argument("Borrowed Cell fixture requires ten original Cell identities");
        for(int i=0;i<10;++i){
            const auto& c=source.cells.at(i);const auto& g=source.gates.cells.at(i);
            if(g.head>1||c.elevatedHead>1)throw std::invalid_argument("Unbound prepared Cell resident");
            attributes[i].input=inputs[i];if(i<9)cells[i]=&attributes[i];
            admissionCells[i]={c.registry,c.owner,c.elevatedOwner};
            cellBindings[i]={&attributes[i].input,i,bindings[i].abstractFlags};
        }
        for(std::size_t i=0;i<slots.size();++i){
            if(slots[i]<-1||slots[i]>8)throw std::invalid_argument("Unbound prepared Cell slot");
            if(slots[i]!=-1)table[i]=&attributes[std::size_t(slots[i])].input;
        }
        member=std::make_unique<PreparedUnitMembership>(map(),
            [this](char k,int i,int off,std::uint32_t){++stores;if(k=='c'&&i==9&&off==0x24)++fallbackStores;},
            [this](char,Coord){++queries;});
        member->houses.loading=1;
        for(int i=0;i<2;++i){
            const auto& g=source.gates.objects.at(i);const auto& o=source.objects.at(i);auto& a=actors[i];
            if(g.kind!=1||g.gate||g.next>1||o.target!=-1||o.destination>1)
                throw std::invalid_argument("Borrowed Cell fixture excludes unbound Unit associations");
            a.flags=o.flags;a.crushable=o.crushable;a.crusher=o.crusher;a.train=o.train;
            a.building1350=o.building1350;a.state1b8=o.state1b8;a.destination1b0=o.destination;
            a.weapon=o.weapon;a.projectile275=o.projectile275;a.shortTrack=shortTrack[i];
            a.destination=state[i];
            if(state[i].target494){
                bool found=false;
                for(int j=0;j<10;++j)if(state[i].target494==&inputs[j]){
                    a.destination.target494=&attributes[j].input;found=true;break;
                }
                if(!found)throw std::invalid_argument("Unbound initial prepared Cell target");
            }
            drives[i].movement.reached5a0=eligibility[i];
        }
        member->discovery=source.gates.objects.at(0).mission;
        member->discovery.owner=source.gates.objects.at(0).owner;
        mission1=source.gates.objects.at(1).mission;mission1.owner=source.gates.objects.at(1).owner;
        member->bind({},drives[0]);member->bindParked({},drives[1],mark1,mission1);
        for(int i=0;i<2;++i)member->membership.actors.at(i).next=source.gates.objects.at(i).next;
        for(int i=0;i<10;++i){
            auto& list=member->membership.cells.at(member->membership.fallbackCell-9+i);
            list.head=source.gates.cells.at(i).head;list.alternateHead=source.cells.at(i).elevatedHead;
            member->occupation[i].ground=source.cells.at(i).occupation;
            member->occupation[i].elevated=source.cells.at(i).elevatedOccupation;
        }
        shared.houses=source.gates.houses;shared.registry=source.registry;shared.speedBits=source.speedBits;
        shared.directions=source.directions;shared.tick=source.gates.tick;
        shared.setPadding=source.gates.setPadding;shared.commencePadding=source.gates.commencePadding;
        admission=std::make_unique<BorrowedPreparedUnitAdmission>(map(),*member,
            std::map<int,PreparedAdmissionActorBinding>{{0,{drives[0],member->discovery,actors[0]}},
                {1,{drives[1],mission1,actors[1]}}},admissionCells,shared,data,squareRoot);
        if(queries||stores)throw std::runtime_error("Borrowed Cell binding made world queries/stores");
    }
    void exportObservations(UnitAdmissionWorld& source,std::array<UnitDestinationState,5>& state,
        std::array<MapCellInput,10>& inputs){
        for(int i=0;i<2;++i){
            state[i]=actors[i].destination;
            if(state[i].target494)for(int j=0;j<10;++j)if(state[i].target494==&attributes[j].input){
                state[i].target494=&inputs[j];break;
            }
            source.gates.objects.at(i).mission=i?mission1:member->discovery;
            source.gates.objects.at(i).next=member->membership.actors.at(i).next;
        }
        for(int i=0;i<10;++i){
            inputs[i]=attributes[i].input;
            const auto& list=member->membership.cells.at(member->membership.fallbackCell-9+i);
            source.gates.cells.at(i).head=list.head;source.cells.at(i).elevatedHead=list.alternateHead;
        }
    }
    BorrowedCellScatterFixture(const BorrowedCellScatterFixture&)=delete;
    BorrowedCellScatterFixture& operator=(const BorrowedCellScatterFixture&)=delete;
};
}
