// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamAdmission.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Team admission fixture/domain differs");}
void run(std::istream& in){
    std::array<std::int32_t,27> f{};for(auto& x:f)require(bool(in>>x));std::string extra;require(!(in>>extra));
    int teamId=0,oldId=0,houseId=0,foreignId=0,scriptId=0,typeId=0,otherTypeId=0;
    const void* prior=f[0]?&teamId:f[17]?&oldId:nullptr;const void* script=f[14]?&scriptId:nullptr;
    std::uint8_t on=f[1],limbo=f[4],air=f[8],eligible=f[12],teamFlag=f[13],recruit=f[16];
    std::int32_t health=f[2],loading=f[3],priority=f[19],taskCount=f[22],oldPriority=f[18];
    std::uint32_t target=f[21];
    std::array<TeamAdmissionEntry,6> entries;std::array<std::uint32_t,6> counts;
    for(int i=0;i<6;++i){entries[i]={f[25],i==f[23]?&typeId:&otherTypeId};counts[i]=std::uint32_t(f[24]);}
    TeamAdmissionTaskForce task{taskCount,entries};TeamAdmissionTaskForce* taskPointer=&task;
    TeamAdmissionType type{teamFlag,priority,taskPointer};
    TeamAdmissionTeam team{&teamId,[&]()->auto&{return type;},script,[&]()->const void*{return &houseId;},counts};
    TeamAdmissionFoot foot{&on,prior,on,health,limbo,[&]()->const void*{return f[5]?&houseId:&foreignId;},eligible,recruit,air,target};
    int kindCalls=0,missionCalls=0,mutated=0;std::vector<std::int32_t> trace;
    const auto event=[&](int a,int b){trace.push_back(a);trace.push_back(b);};
    const auto mutate=[&](int where){if(mutated||f[26]!=where)return;mutated=1;event(12,where);
        if(where==1){health=0;teamFlag=128;recruit=1;}
        if(where==2){taskCount=2;entries[0].type=&otherTypeId;entries[1].type=&typeId;}
        if(where==3){prior=&oldId;oldPriority=priority;}
        if(where==4){entries[0].required=std::bit_cast<std::int32_t>(std::uint32_t(f[25])+1);counts[0]=std::uint32_t(f[24])+1;}
    };
    TeamAdmissionServices s{loading};
    s.radio636F10=[&]{event(1,f[6]);mutate(1);return std::uint32_t(f[6]);};
    s.kind2C=[&]{++kindCalls;event(2,f[7]);return std::uint32_t(f[7]);};
    s.mission16C=[&]{const auto value=missionCalls++?f[10]:f[9];event(3,value);return value;};
    s.mission594DB0=[&](int m){event(4,m);event(5,f[11]);return std::uint32_t(f[11]);};
    s.script668870=[&](const void* p){require(p==&scriptId);event(6,f[15]);mutate(3);return f[15];};
    s.teamPriorityB4=[&](const void* p){require(p==&oldId);event(7,oldPriority);return oldPriority;};
    s.aircraft39C=[&](std::uint32_t zero){event(8,int(zero));event(9,f[20]);return f[20];};
    s.type84=[&]()->const void*{event(10,1);mutate(2);mutate(4);return &typeId;};
    s.outputStore=[&](int value){event(11,value);};
    std::int32_t output=0x12345678;const auto result=canAdmitTeamFoot(team,foot,output,s);
    for(auto x:trace)std::cout<<x<<' ';
    std::cout<<"F "<<result<<' '<<output<<' '<<kindCalls<<' '<<missionCalls<<' '<<mutated<<' '<<taskCount<<' '<<int(teamFlag)<<' '<<health<<' '<<int(recruit)<<' '<<oldPriority<<' '<<(prior==&teamId?1:prior==&oldId?2:0)<<' '<<entries[0].required<<' '<<counts[0]<<'\n';
}
void guards(){
    int n=1,p=1,zero=0;std::uint8_t yes=1,no=0;std::uint32_t target=0;int id=0,h=0;const void* null=nullptr;
    TeamAdmissionTaskForce task{n,{}};auto* tp=&task;TeamAdmissionType type{no,p,tp};
    std::array<std::uint32_t,1> counts{};TeamAdmissionTeam team{&id,[&]()->auto&{return type;},null,[&]()->const void*{return &h;},counts};
    TeamAdmissionFoot foot{nullptr,null,yes,p,no,[&]()->const void*{return &h;},yes,yes,no,target};TeamAdmissionServices s{zero};int out=123;
    bool refused=false;try{canAdmitTeamFoot(team,foot,out,s);}catch(const std::invalid_argument&){refused=true;}require(refused&&out==123);
    foot.identity=&h;s.radio636F10=[]{return 0u;};s.kind2C=[]{return 15u;};s.mission16C=[]{return -1;};s.type84=[]()->const void*{return nullptr;};
    refused=false;try{canAdmitTeamFoot(team,foot,out,s);}catch(const std::invalid_argument&){refused=true;}require(refused&&out==0);
    n=0;out=123;require(!canAdmitTeamFoot(team,foot,out,s)&&out==0);
    std::cout<<"team admission guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
