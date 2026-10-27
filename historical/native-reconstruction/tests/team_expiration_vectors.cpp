// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamExpiration.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Team expiration fixture differs");}
void run(std::istream& in){
 std::array<int,7> f{};for(auto& v:f)require(bool(in>>v));std::string extra;require(!(in>>extra));
 int team=0,other=0;std::array<int,4> recipientIds{};const void* next=nullptr;MissionTeamExpiredAbstract subject{&team,next};
 const auto id=[&](const void* p){if(!p)return 0;if(p==&team)return 1;if(p==&other)return 2;for(int i=0;i<4;++i)if(p==&recipientIds[i])return 10+i;throw std::invalid_argument("Foreign Team expiration pointer");};
 std::vector<std::uint64_t> trace;const auto event=[&](int k,std::uint32_t a=0,std::uint32_t b=0,std::uint32_t c=0,std::uint32_t d=0,std::uint32_t e=0){trace.insert(trace.end(),{std::uint64_t(k),a,b,c,d,e});};
 const void* choices[]{nullptr,&team,&other};const void* g0=choices[f[0]];const void* g1=choices[f[1]];std::uint8_t flags=std::uint8_t(f[2]);int count=f[3];
 std::array<TeamExpirationRecipient,4> recipients{};std::array<TeamExpirationRecipient*,4> slots{},alt{};for(int i=0;i<4;++i){recipients[i].identity=&recipientIds[i];slots[i]=&recipients[i];alt[i]=&recipients[3-i];}
 std::span<TeamExpirationRecipient*> backing=slots;MissionExpirationVector<TeamExpirationRecipient*> vector{count,backing,slots.data()};int mutated=0;
 const auto mutate=[&](int where){if(mutated||f[6]!=where)return;mutated=1;event(9,where);if(where==1){g0=&team;g1=&other;count=4;}if(where==2){backing=alt;count=4;flags=255;}if(where==3)count=0;if(where==4){backing=alt;count=4;}if(where==5)slots[1]=&recipients[3];};
 TeamExpirationServices s{g0,g1,vector};s.store=[&](const void* p,std::int64_t off,std::uint32_t value,const void* pointer){require((p==&g0||p==&g1)&&off==0&&!value&&!pointer);event(1,p==&g0?30:31,0,4,0);};
 s.clearMapSelection=[&]{event(2);mutate(1);};s.abstractType=[&](const void* p){require(p==&team);event(3,1);mutate(2);return false;};
 for(int i=0;i<4;++i)recipients[i].expired=[&,i](const auto& expired,std::uint32_t removed){require(expired.identity==&team&&removed==std::uint32_t(f[4]));event(4,10+i,1,removed);mutate(3);mutate(4);mutate(5);};
 for(int i=0;i<f[5];++i)broadcastTeamExpiration(subject,flags,std::uint32_t(f[4]),s);
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<mutated<<' '<<id(g0)<<' '<<id(g1)<<' '<<int(flags)<<' '<<std::uint32_t(count)<<' ';for(const auto& b:{slots,alt})for(auto* p:b)std::cout<<id(p->identity)<<' ';std::cout<<'\n';
}
void guards(){int team=0,count=0;const void* next=nullptr;MissionTeamExpiredAbstract subject{&team,next};const void* g0=&team;const void* g1=nullptr;std::span<TeamExpirationRecipient*> slots;MissionExpirationVector<TeamExpirationRecipient*> vector{count,slots,nullptr};TeamExpirationServices s{g0,g1,vector};
 bool refused=false;try{broadcastTeamExpiration(subject,3,1,s);}catch(const std::invalid_argument&){refused=true;}require(refused&&g0==&team);
 refused=false;try{broadcastTeamExpiration(subject,0,1,s);}catch(const std::invalid_argument&){refused=true;}require(refused&&!g0);
 s.abstractType=[](auto){return true;};refused=false;try{broadcastTeamExpiration(subject,0,1,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
 // Typed Team cleanup preserves a real Tag and borrows the live successor.
 int instances=7;std::int32_t persistence=0;MissionTagType tagType{persistence};auto* type=&tagType;MissionTagTrigger* first=nullptr;std::uint8_t executing=0;MissionTagState tag{type,first,instances,executing};auto* actualTag=&tag;
 const void* link=&team;next=&count;expireMissionTagObjectReferences({actualTag,link,&count},subject,257);require(actualTag==&tag&&instances==7&&link==&count);
 MissionTeamExpiredAbstract invalid{&tag,next};refused=false;try{expireMissionTagObjectReferences({actualTag,link,&count},invalid,1);}catch(const std::invalid_argument&){refused=true;}require(refused&&instances==7&&actualTag==&tag&&link==&count);
 std::cout<<"team expiration guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
