// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionTagObjectExpiration.hpp"
#include <array>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void require(bool ok){if(!ok)throw std::invalid_argument("Tag Object expiration fixture outside domain");}
void run(std::istream& in) {
    std::array<std::int32_t,2> instances{};int objectTag,objectLink,subject,next,count;
    require(bool(in>>instances[0]>>instances[1]>>objectTag>>objectLink>>subject>>next>>count));
    require(objectTag>=0&&objectTag<=2&&objectLink>=0&&objectLink<=2&&subject>=1&&subject<=2&&next>=0&&next<=2&&count>0&&count<=32);
    std::array<std::int32_t,2> persistence{};std::array<std::uint8_t,2> executing{};std::array<MissionTagType,2> types{{{persistence[0]},{persistence[1]}}};
    std::array<MissionTagType*,2> type{&types[0],&types[1]};std::array<MissionTagTrigger*,2> first{};
    std::array<MissionTagState,2> tags{{{type[0],first[0],instances[0],executing[0]},{type[1],first[1],instances[1],executing[1]}}};
    auto tag=[&](int id)->MissionTagState*{return id?&tags[std::size_t(id-1)]:nullptr;};
    auto identity=[&](int id)->const void*{return id?static_cast<const void*>(&tags[std::size_t(id-1)]):nullptr;};
    MissionTagState* attached=tag(objectTag);const void* link=identity(objectLink);const void* nextLink=identity(next);int object=0;
    MissionTagObjectReferences references{attached,link,&object};MissionTagExpiredAbstract expired{*tag(subject),identity(subject),nextLink};
    auto id=[&](const void* p){if(!p)return 0;if(p==&object)return 20;if(p==&tags[0])return 10;if(p==&tags[1])return 11;throw std::invalid_argument("Unknown Tag Object identity");};
    MissionTagStore store=[&](const void* p,auto offset,auto value,const void* pointer){std::cout<<"W "<<id(p)<<' '<<offset<<' '<<(pointer?std::uint32_t(id(pointer)):value)<<' ';};
    for(int i=0;i<count;++i){std::uint32_t removed;require(bool(in>>removed));std::cout<<"O ";expireMissionTagObjectReferences(references,expired,removed,store);std::cout<<"R ";}
    std::string extra;require(!(in>>extra));std::cout<<"state "<<instances[0]<<' '<<instances[1]<<' '<<id(attached)<<' '<<id(link)<<'\n';
}
void guards(){
    int persistence=0,instances=0,object=0;std::uint8_t executing=0;MissionTagType type{persistence};auto* typePointer=&type;MissionTagTrigger* first=nullptr;
    MissionTagState tag{typePointer,first,instances,executing};MissionTagState* attached=&tag;const void* link=&tag;const void* next=&object;
    MissionTagObjectReferences refs{attached,link,&object};MissionTagExpiredAbstract expired{tag,&tag,next};
    expireMissionTagObjectReferences(refs,expired,0x100);require(!attached&&link==&tag&&instances==-1);
    attached=&tag;expireMissionTagObjectReferences(refs,expired,1);require(!attached&&link==&object&&instances==-2);
    auto recipient=bindMissionTagObjectExpiration(refs,expired);bool refused=false;MissionTagState other{typePointer,first,instances,executing};
    try{recipient.expired(other,1);}catch(const std::invalid_argument&){refused=true;}require(refused);
    bool fault=false;MissionTagStore store=[&](auto...){fault=true;throw std::runtime_error("observer fault");};attached=&tag;
    try{expireMissionTagObjectReferences(refs,expired,0,store);}catch(const std::runtime_error&){}require(fault&&attached==&tag&&instances==-3);
    std::cout<<"guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);char op;require(bool(in>>op)&&op=='P');run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
