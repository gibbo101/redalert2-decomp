// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MovementData.hpp"
#include "platform/FramePacer.hpp"
#include "sim/Targeting.hpp"
#include <iostream>
#include <sstream>
#include <string>
int main(int argc,char** argv) {
    try {
        if(argc!=3) return 2;
        const auto data=ra2::readDriveData(ra2::readFile(argv[1]),ra2::readFile(argv[2]));
        ra2::Drive drive(data,{2688,2688,0},5,6);
        std::string line;
        while(std::getline(std::cin,line)) {
            std::istringstream in(line);char op;in>>op;
            if(op=='A') {
                ra2::Coord from,target;in>>from.x>>from.y>>target.x>>target.y;
                std::cout<<ra2::destinationDirection(data->directionsToTargets,from,target)<<'\n';
            } else if(op=='R') {
                ra2::FrameTimer timer;std::uint32_t now;in>>timer.start>>timer.duration>>now;
                std::cout<<timer.remaining(now)<<'\n';
            } else if(op=='W') {
                std::uint32_t now,work;int speed;in>>now>>work>>speed;
                const ra2::FrameTimer timer{std::int32_t(ra2::originalClock(now)),ra2::frameDelay(speed)};
                now+=work;std::vector<std::uint32_t> sleeps;
                while(timer.remaining(now)>0 && sleeps.size()<1000) {
                    const auto sleep=std::uint32_t(timer.remaining(now));sleeps.push_back(sleep);now+=std::max(1u,sleep);
                }
                std::cout<<now<<' '<<sleeps.size();for(auto n:sleeps)std::cout<<' '<<n;std::cout<<'\n';
            } else if(op=='B') {
                unsigned body,turret;int rot;in>>body>>turret>>rot;
                drive=ra2::Drive(data,{2688,2688,0},rot,6);
                drive.body.setCurrent(std::uint16_t(body),0);drive.turret.setCurrent(std::uint16_t(turret),0);
            } else if(op=='T') {
                int tick,present;ra2::Coord target;in>>tick>>drive.position.x>>drive.position.y>>present>>target.x>>target.y;
                drive.navigationTarget=present?std::optional{target}:std::nullopt;drive.updateTurret(tick);
                std::cout<<drive.turret.current(tick)<<' '<<drive.turret.desired<<' '<<drive.turret.start<<' '
                  <<drive.turret.timerStart<<' '<<drive.turret.duration<<' '<<drive.turretTurning<<'\n';
            } else return 3;
            if(!in) return 4;
        }
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 1;}
}
