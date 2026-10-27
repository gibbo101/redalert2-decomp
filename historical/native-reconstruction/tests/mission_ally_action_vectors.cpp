// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionAllyAction.hpp"
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
namespace {
void require(bool ok){if(!ok)throw std::invalid_argument("Mission ally fixture outside domain");}
template<class T>T take(std::istream& in){T value{};require(bool(in>>value));return value;}
const void* identity(int mode,const int& current,const int& target){require(mode>=0&&mode<=2);return mode==0?nullptr:mode==1?&current:&target;}
int code(const void* value,const int& current,const int& target){return !value?0:value==&current?1:value==&target?2:throw std::invalid_argument("Foreign Mission ally identity");}
void run(std::istream& in){
    require(take<char>(in)=='A');const auto value=take<std::int32_t>(in);const int currentMode=take<int>(in),resolvedMode=take<int>(in);std::string extra;require(!(in>>extra));
    int currentOwner=1,targetOwner=2;const auto* current=identity(currentMode,currentOwner,targetOwner);const auto* resolved=identity(resolvedMode,currentOwner,targetOwner);
    MissionAllyServices services;
    services.resolveHouse=[&](std::int32_t index){require(index==value);std::cout<<"F "<<index<<' '<<code(resolved,currentOwner,targetOwner)<<' ';return resolved;};
    services.makeAlly=[&](const void* self,const void* other,std::uint8_t announce){std::cout<<"A "<<code(self,currentOwner,targetOwner)<<' '<<code(other,currentOwner,targetOwner)<<' '<<unsigned(announce)<<' ';};
    const auto result=executeMissionAllyAction(value,current,services);std::cout<<"R "<<result<<'\n';
}
void guards(){
    MissionAllyServices none;require(executeMissionAllyAction(-1,nullptr,none));
    bool refused=false;try{(void)executeMissionAllyAction(0,nullptr,none);}catch(const std::invalid_argument&){refused=true;}require(refused);
    int a=1,b=2,calls=0;MissionAllyServices services;services.resolveHouse=[&](auto){return static_cast<const void*>(&b);};
    services.makeAlly=[&](const void* self,const void* other,std::uint8_t announce){
        if(calls++==0)require(self==&a&&other==&b&&!announce);else require(self==&b&&other==&a&&!announce);
    };
    require(executeMissionAllyAction(13,&a,services)&&calls==2);
    std::cout<<"mission ally action guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
