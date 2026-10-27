// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MovementData.hpp"
#include "sim/Drive.hpp"
#include <iostream>
#include <sstream>
#include <string>
int main(int argc,char** argv) {
    try {
        if(argc!=2) return 2;
        const auto data=ra2::readDriveData(ra2::readFile(argv[1]));
        std::unique_ptr<ra2::Drive> drive;
        std::string line;
        while(std::getline(std::cin,line)) {
            std::istringstream in(line);std::string op;in>>op;
            if(op=="BEGIN") {
                int x,y,heading,rot,speed;double terrain;
                in>>x>>y>>heading>>rot>>speed>>terrain;
                drive=std::make_unique<ra2::Drive>(data,ra2::Coord{x,y,0},rot,speed);
                drive->body.setCurrent(std::uint16_t(heading),0);
                drive->turret.setCurrent(std::uint16_t(heading),0);drive->terrainScale=terrain;
            } else if(op=="ORDER") {
                int dir,count;in>>dir>>count;const auto [dx,dy]=ra2::directionOffset(dir);
                const auto start=drive->driving?drive->head:drive->position;
                drive->order({start.x+dx*count*256,start.y+dy*count*256,0},std::vector<int>(count,dir));
            } else if(op=="PATH") {
                int count;in>>count;if(count<0||count>23)return 5;
                std::vector<int> route;auto target=drive->driving?drive->head:drive->position;
                for(int i=0;i<count;++i) {int d;in>>d;route.push_back(d);const auto [dx,dy]=ra2::directionOffset(d);target.x+=dx*256;target.y+=dy*256;}
                drive->order(target,route);
            } else if(op=="PASSIVE") {int value;in>>value;drive->passive=value!=0;
            } else if(op=="STOP") drive->stop();
            else if(op=="TURN") {int heading,tick;in>>heading>>tick;drive->body.setDesired(std::uint16_t(heading),tick);}
            else if(op=="STEP"||op=="DETAIL") {
                int tick;in>>tick;drive->process(tick);
                std::cout<<drive->position.x<<' '<<drive->position.y<<' '<<drive->position.z<<' '
                  <<drive->track<<' '<<drive->index<<' '<<drive->accumulator<<' '
                  <<drive->driving<<' '<<drive->body.current(tick)<<' '<<drive->turret.current(tick)<<' '
                  <<drive->wasRotating<<' '<<drive->turretTurning;
                if(op=="DETAIL") {
                    std::cout<<' '<<drive->head.x<<' '<<drive->head.y;
                    for(std::size_t i=0;i<4;++i)std::cout<<' '<<(i<drive->route.size()?drive->route[i]:-1);
                }
                std::cout<<'\n';
            } else if(op=="SPEED") {
                int value,previous;double scale;in>>value>>previous>>scale;
                const int speed=ra2::internalSpeed(value,previous);
                std::cout<<speed<<' '<<ra2::currentSpeed(speed,scale)<<'\n';
            } else return 3;
            if(!in) return 4;
        }
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 1;}
}
