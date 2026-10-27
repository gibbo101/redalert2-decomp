// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/UnitNextCell.hpp"
// Shared diagnostic gate/admission/next-Cell records, not game initialization.
struct GroundDriveAdmissionVectors {
    GroundDriveGateVectors gates;
    ra2::UnitAdmissionWorld world;
    int crusher=0;
    ra2::GroundDriveResidentRetry retry;
    int residentFlags=1;
    ra2::MapCellInput* fallback=nullptr;
    std::array<ra2::MapCellInput,81>* cells=nullptr;
    explicit GroundDriveAdmissionVectors(std::istream& in,bool stationaryUnits=false):gates(in,stationaryUnits){
        in>>crusher;if(!in||crusher<0||crusher>255)throw std::invalid_argument("Invalid admission Crusher byte");
        for(const auto& r:gates.objects)if((r[0]!=6&&!(stationaryUnits&&r[0]==1))||r[2]<0)throw std::invalid_argument("Joined admission requires supported residents with owners");
        if(stationaryUnits){
            in>>retry.firstPadding>>retry.secondPadding>>residentFlags;
            if(residentFlags!=1&&residentFlags!=5)throw std::invalid_argument("Resident flags outside stationary profile");
        }
    }
    void bind(const std::vector<ra2::MapCellInput*>& slots,std::array<ra2::MapCellInput,81>& data,ra2::MapCellInput& fb,double landSpeed){
        gates.bind(slots,data,fb);world.gates=std::move(gates.world);fallback=&fb;cells=&data;
        for(int i=0;i<82;++i){const auto& c=i==81?fb:data[std::size_t(i)];auto& a=world.cells[i];
            a.level=c.level;a.ramp=c.slope;a.flags=c.flags;a.land=c.land;a.owner=a.elevatedOwner=0;
            a.elevatedHead=4;
        }
        for(int i=0;i<5;++i){auto& a=world.objects[i];a.flags=i?1:5;}
        for(int i=1;i<5;++i)if(world.gates.objects.at(i).kind==1)world.objects[i].flags=std::uint8_t(residentFlags);
        world.objects[0].crusher=std::uint8_t(crusher);
        world.directions={ra2::TerrainCellPoint{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};
        for(int i=0;i<12;++i)world.speedBits[std::size_t(i)]=std::bit_cast<std::uint32_t>(float(double(landSpeed)*(1.-i/16.)));
        world.trace=[this](char k,int a,int b,int){
            if(k=='L')GroundDriveGateVectors::event('W',a,b);
            if(k=='F'){fallback->position={std::int16_t(a),std::int16_t(b)};GroundDriveGateVectors::event('a','F',a,b);}
        };
    }
    void beforeTick(int j,int tick){
        world.gates.tick=tick;
        for(const auto& r:gates.updates)if(r[0]==j){auto& a=world.gates.objects.at(r[1]);a.animation18=std::uint8_t(r[2]);a.animation19=std::uint8_t(r[3]);GroundDriveGateVectors::event('g','U',r[1],r[2],r[3]);}
    }
    void sync(){world.gates.cells.at(81).point={fallback->position.x,fallback->position.y};}
    bool check(std::int16_t x,std::int16_t y){
        sync();GroundDriveGateVectors::event('g','C',x,y);
        const bool r=ra2::checkMovementGates(0,{x,y},world.gates);GroundDriveGateVectors::event('g','r',r);return r;
    }
    int admit(const ra2::GroundDriveCell& c,int d,int level){
        sync();const int id=c.identity==fallback?81:int(static_cast<const ra2::MapCellInput*>(c.identity)-cells->data());
        GroundDriveGateVectors::event('a','U',id,d,level);
        const auto trace=world.gates.trace;world.gates.trace={};
        const int r=ra2::ordinaryUnitAdmission(0,id,d,level,-1,1,world);world.gates.trace=trace;
        GroundDriveGateVectors::event('a','r',r);return r;
    }
    void next(ra2::Coord location,std::int16_t x,std::int16_t y){
        sync();GroundDriveGateVectors::event('a','N',x,y);
        ra2::ordinaryUnitNextCell(0,{location,0},{x,y},1,world);
    }
    void state(){
        GroundDriveGateVectors::event('g','R');for(int i=1;i<5;++i){const auto& a=world.gates.objects.at(i);const auto& m=a.mission;
            GroundDriveGateVectors::event(m.mission98,m.queuedA0,unsigned(m.queuedA4),a.statusA8,a.lastAC,a.timerStart,a.timerPadding,a.timerRemaining,unsigned(a.animation18),unsigned(a.animation19));}
    }
};
