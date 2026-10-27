// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/InfantrySightSchedule.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace ra2;
namespace {
void require(bool value){if(!value)throw std::invalid_argument("Infantry sight schedule fixture outside domain");}
template<class T>T take(std::istream& in){T value{};require(bool(in>>value));return value;}
void run(std::istream& in){
    require(take<char>(in)=='S');Coord point{take<std::int32_t>(in),take<std::int32_t>(in),take<std::int32_t>(in)};
    std::int32_t range=take<std::int32_t>(in);std::string extra;require(!(in>>extra));
    InfantrySightScheduleServices services;
    services.missionTransition=[] {std::cout<<"M ";};
    services.removeSight=[](auto a,auto b,auto c,auto d){std::cout<<"R "<<a<<' '<<b<<' '<<c<<' '<<d<<' ';};
    services.addSight=[](auto a,auto b,auto c,auto d){std::cout<<"A "<<a<<' '<<b<<' '<<c<<' '<<d<<' ';};
    services.postSight=[](Coord p,auto a,std::int32_t r,auto b){std::cout<<"P "<<p.x<<' '<<p.y<<' '<<p.z<<' '<<a<<' '<<r<<' '<<b;};
    scheduleInfantryArrivalSight({point,range},services);std::cout<<'\n';
}
void guards(){
    Coord point{};std::int32_t range=0;InfantrySightScheduleServices services;
    bool refused=false;try{scheduleInfantryArrivalSight({point,range},services);}catch(const std::invalid_argument&){refused=true;}
    require(refused);std::cout<<"Infantry sight schedule guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
