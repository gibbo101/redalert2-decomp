// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MovingUnitAdmission.hpp"
#include "GroundDriveAdmissionVectors.hpp"
// Separate diagnostic M protocol. Initial motion/timer associations are supplied.
struct GroundDriveMovingResidentVectors : GroundDriveAdmissionVectors {
    ra2::UnitAdmissionMotionWorld motion;
    ra2::GroundDriveProcessState* processState=nullptr;
    ra2::GroundDriveMovingWaitState wait;
    ra2::GroundDriveMovingWaitServices waitServices;
    int initial5a1=0,retryStart=-1,retryPadding=7,retryRemaining=0;
    explicit GroundDriveMovingResidentVectors(std::istream& in):GroundDriveAdmissionVectors(in,true){
        for(int i=1;i<5;++i){
            std::array<int,19> row{};for(int& n:row)in>>n;
            if(!in||row[9]<0||row[9]>65535||row[10]<0||row[10]>65535||row[13]<0||row[13]>65535||
               row[14]<0||row[14]>255||row[16]<0||row[16]>63||row[18]<0||row[18]>255)
                throw std::invalid_argument("Invalid moving-resident records");
            auto& a=motion.actors[i];a.position={row[0],row[1],row[2]};a.destination={row[3],row[4],row[5]};a.head={row[6],row[7],row[8]};
            a.body.desired=std::uint16_t(row[9]);a.body.start=std::uint16_t(row[10]);a.body.timerStart=row[11];a.body.duration=row[12];a.body.rate=std::uint16_t(row[13]);
            a.eligibility5a0=std::uint8_t(row[14]);a.queueHead=row[15];a.track=row[16];a.index=row[17];a.shortTrack=std::uint8_t(row[18]);
        }
        in>>initial5a1>>wait.start>>wait.padding>>wait.remaining>>waitServices.duration>>waitServices.temporaryPadding>>retryStart>>retryPadding>>retryRemaining;
        if(!in||initial5a1<0||initial5a1>255)throw std::invalid_argument("Invalid moving-resident wait inputs");
    }
    void bind(const std::vector<ra2::MapCellInput*>& slots,std::array<ra2::MapCellInput,81>& data,ra2::MapCellInput& fb,double speed){
        GroundDriveAdmissionVectors::bind(slots,data,fb,speed);
        for(int i=1;i<5;++i){
            if(world.gates.objects.at(i).kind!=1)throw std::invalid_argument("Moving-resident vectors require Unit identities");
            world.objects.at(i).flags=std::uint8_t(residentFlags);
        }
        motion.actors[0]={};
    }
    int admit(const ra2::GroundDriveCell& c,int d,int level){
        sync();const int id=c.identity==fallback?81:int(static_cast<const ra2::MapCellInput*>(c.identity)-cells->data());
        const auto& s=*processState;const auto& m=s.movement;auto& a=motion.actors.at(0);
        a.position=m.actor.position;a.destination=s.destination;a.head=m.head;a.body=m.body;a.eligibility5a0=m.reached5a0;
        a.queueHead=s.route[0];a.track=m.track;a.index=m.index;
        GroundDriveGateVectors::event('a','U',id,d,level);
        const auto trace=world.gates.trace;world.gates.trace={};
        const int result=ra2::movingUnitAdmission(0,id,d,level,-1,1,world,motion);world.gates.trace=trace;
        GroundDriveGateVectors::event('a','r',result);return result;
    }
    void state(){
        GroundDriveGateVectors::event('w',wait.start,wait.padding,wait.remaining);
        GroundDriveAdmissionVectors::state();
    }
};
