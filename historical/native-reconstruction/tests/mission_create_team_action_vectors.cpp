// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionCreateTeamAction.hpp"
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
namespace {
void require(bool ok){if(!ok)throw std::invalid_argument("Mission Create Team fixture outside domain");}
template<class T>T take(std::istream& in){T value{};require(bool(in>>value));return value;}
void run(std::istream& in){
    require(take<char>(in)=='C');auto depth=take<std::uint32_t>(in);const auto present=take<int>(in),mutate=take<int>(in);const auto childValue=take<std::uint32_t>(in);std::string extra;require(!(in>>extra));require((present==0||present==1)&&(mutate==0||mutate==1));
    int team=1;MissionCreateTeamServices services{depth,{}};
    services.createTeam=[&](const void* identity,std::int32_t argument){
        require(identity==&team);std::cout<<"C 1 "<<argument<<' '<<depth<<' ';
        if(mutate){depth=childValue;std::cout<<"M "<<depth<<' ';}
    };
    const auto result=executeMissionCreateTeamAction(present?&team:nullptr,services);
    std::cout<<"R "<<result<<" D "<<depth<<'\n';
}
void guards(){
    std::uint32_t depth=0xffffffffu;MissionCreateTeamServices none{depth,{}};
    require(executeMissionCreateTeamAction(nullptr,none)&&depth==0xffffffffu);
    depth=7;bool refused=false;try{(void)executeMissionCreateTeamAction(&depth,none);}catch(const std::invalid_argument&){refused=true;}
    require(refused&&depth==8);
    int team=1;depth=0xffffffffu;MissionCreateTeamServices services{depth,{}};std::uint32_t seen=0;
    services.createTeam=[&](const void* identity,std::int32_t argument){require(identity==&team&&argument==0);seen=depth;depth=0;};
    require(executeMissionCreateTeamAction(&team,services)&&seen==0&&depth==0xffffffffu);
    std::cout<<"mission Create Team action guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
