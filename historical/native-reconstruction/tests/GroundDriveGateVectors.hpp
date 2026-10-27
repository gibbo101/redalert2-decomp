// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MovementGate.hpp"
#include <memory>

// Diagnostic gate records for the result-bearing complete Process comparison.
// Terrain/House/animation inputs are supplied; this is not game initialization.
struct GroundDriveGateVectors {
    std::array<int,9> header{};
    std::array<std::pair<int,std::uint32_t>,3> houses{};
    std::array<std::array<int,14>,4> objects{};
    std::vector<std::array<int,4>> updates;
    ra2::MovementGateWorld world;
    std::vector<int> slots;
    template<class... T> static void event(T... args){((std::cout<<args<<' '),...);}
    explicit GroundDriveGateVectors(std::istream& in,bool stationaryUnits=false){
        for(auto& n:header)in>>n;
        for(auto& [index,mask]:houses){std::uint64_t n=0;in>>index>>n;if(n>0xffffffffu)throw std::invalid_argument("Gate House mask outside domain");mask=std::uint32_t(n);}
        for(auto& row:objects)for(auto& n:row)in>>n;
        int count=0;in>>count;
        if(!in||count<0||count>128)throw std::invalid_argument("Gate transition count outside domain");
        updates.resize(std::size_t(count));for(auto& row:updates)for(auto& n:row)in>>n;
        const auto id=[](int n){return n>=-1&&n<5;};
        const auto byte=[](int n){return n>=0&&n<=255;};
        if(header[2]<-1||header[2]>=262144||header[3]<-1||header[3]>=262144||
           (header[2]!=-1&&header[2]==header[3])||!id(header[4])||!id(header[5])||!id(header[6])||
           header[7]<0||header[7]>2||!id(header[8]))throw std::invalid_argument("Gate header outside domain");
        world.objects[0].kind=1;world.objects[0].owner=header[7];world.objects[0].next=header[8];
        world.objects[0].mission.mission98=2;
        for(int i=1;i<5;++i){
            const auto& r=objects[std::size_t(i-1)];
            if((r[0]!=6&&r[0]!=36&&!(stationaryUnits&&r[0]==1))||!id(r[1])||r[2]<-1||r[2]>2||
               !byte(r[3])||!byte(r[6])||!byte(r[7])||!byte(r[8])||
               (r[0]==6&&r[3]&&r[2]==-1))throw std::invalid_argument("Gate object outside domain");
            auto& a=world.objects[i];a.kind=r[0];a.next=r[1];a.owner=r[2];a.gate=std::uint8_t(r[3]);
            a.mission.mission98=r[4];a.mission.queuedA0=r[5];a.mission.queuedA4=std::uint8_t(r[6]);
            a.animation18=std::uint8_t(r[7]);a.animation19=std::uint8_t(r[8]);a.statusA8=r[9];a.lastAC=r[10];
            a.timerStart=r[11];a.timerPadding=r[12];a.timerRemaining=r[13];
        }
        for(int i=0;i<5;++i){int p=i;std::size_t visits=0;while(p!=-1){if(++visits>5)throw std::invalid_argument("Cyclic gate list");p=world.objects.at(p).next;}}
        for(const auto& r:updates)if(r[0]<0||r[0]>=256||r[1]<1||r[1]>=5||!byte(r[2])||!byte(r[3]))
            throw std::invalid_argument("Gate transition outside domain");
    }
    void bind(const std::vector<ra2::MapCellInput*>& mapSlots,std::array<ra2::MapCellInput,81>& cells,ra2::MapCellInput& fallback){
        slots.assign(262144,-1);world.fallbackCell=81;world.setPadding=header[0];world.commencePadding=header[1];
        for(int i=0;i<3;++i)world.houses[i]={houses[std::size_t(i)].first,houses[std::size_t(i)].second};
        for(int i=0;i<81;++i)world.cells[i]={{cells[std::size_t(i)].position.x,cells[std::size_t(i)].position.y},-1};
        world.cells[81]={{fallback.position.x,fallback.position.y},header[6]};
        for(std::size_t i=0;i<mapSlots.size();++i)if(mapSlots[i]){
            const int id=int(mapSlots[i]-cells.data());slots[i]=id;
            if(int(i)==header[2])world.cells.at(id).head=header[4];
            if(int(i)==header[3])world.cells.at(id).head=header[5];
        }
        world.slots=slots;
        world.trace=[](char k,int id){event('g',k,id);};
        world.kindResult=[](int id,int kind){event('g','V',id,kind);};
        world.store=[](int id,int off,int size,std::uint32_t value){event('g','W',id,off,size,value);};
        world.fallbackStore=[&fallback](ra2::TerrainCellPoint p){fallback.position={p.x,p.y};event('g','F',p.x,p.y);};
    }
    void beforeTick(int j,int tick){
        world.tick=tick;
        for(const auto& r:updates)if(r[0]==j){auto& a=world.objects.at(r[1]);a.animation18=std::uint8_t(r[2]);a.animation19=std::uint8_t(r[3]);event('g','U',r[1],r[2],r[3]);}
    }
    bool check(std::int16_t x,std::int16_t y){
        event('g','C',x,y);const bool result=ra2::checkMovementGates(0,{x,y},world);event('g','r',result);return result;
    }
    void state(){
        event('g','R');for(int i=1;i<5;++i){const auto& a=world.objects.at(i);const auto& m=a.mission;
            event(m.mission98,m.queuedA0,unsigned(m.queuedA4),a.statusA8,a.lastAC,a.timerStart,a.timerPadding,a.timerRemaining,unsigned(a.animation18),unsigned(a.animation19));}
    }
};
