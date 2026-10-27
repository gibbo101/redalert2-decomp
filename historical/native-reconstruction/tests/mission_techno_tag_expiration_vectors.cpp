// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionTechnoTagExpiration.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Techno Tag fixture outside domain");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
constexpr std::array<int,15> offsets{0xfc,0x108,0x1b0,0x1b4,0x208,0x20c,0x228,0x22c,0x230,0x238,0x23c,0x27c,0x384,0x3f8,0x30};
void run(std::istream& in){
 require(take<char>(in)=='T');const int root=take<int>(in),subjectId=take<int>(in),flags=take<int>(in);require(root>=0&&root<4&&subjectId>=1&&subjectId<=2&&flags>=0&&flags<=255&&!(flags&1));
 std::array<std::int32_t,2> instances{};for(auto& n:instances)n=take<std::int32_t>(in);
 const auto tagId=take<int>(in);require(tagId>=0&&tagId<=2);
 std::array<int,3> nextIds{};for(auto& n:nextIds){n=take<int>(in);require(n>=0&&n<=2);}
 std::array<int,15> fields{};for(auto& n:fields){n=take<int>(in);require(n>=0&&n<=9);}
 std::array<int,8> weaponIds{};for(auto& n:weaponIds){n=take<int>(in);require(n>=0&&n<=9);}
 std::int32_t timerStart=take<std::int32_t>(in),timerPadding=take<std::int32_t>(in),timerDuration=take<std::int32_t>(in),mission=take<std::int32_t>(in),wordA8=take<std::int32_t>(in);
 const auto byte372in=take<unsigned>(in),byte5BAin=take<unsigned>(in);require(byte372in<=255&&byte5BAin<=255);auto byte372=std::uint8_t(byte372in),byte5BA=std::uint8_t(byte5BAin);
 std::int32_t frame=take<std::int32_t>(in),session=take<std::int32_t>(in),scratch=take<std::int32_t>(in),retry=take<std::int32_t>(in);
 const auto ownerResult=take<int>(in);const auto predicate1=take<unsigned>(in);const auto kind=take<int>(in);const auto predicateC=take<unsigned>(in);const auto queryResult=take<int>(in),mode=take<int>(in);
 require(ownerResult>=0&&ownerResult<=9&&queryResult>=0&&queryResult<=9&&predicate1<=0xffffffffu&&predicateC<=0xffffffffu&&mode>=0&&mode<=3);
 std::array<int,2> controlIds{};for(auto& n:controlIds){n=take<int>(in);require(n>=0&&n<=9);}
 std::array<int,4> counts{};for(auto& n:counts){n=take<int>(in);require(n>=-2&&n<=8);}
 std::array<std::array<int,8>,4> inputBuffers{};for(auto& b:inputBuffers)for(auto& n:b){n=take<int>(in);require(n>=0&&n<=9);}
 const auto operations=take<unsigned>(in);require(operations>0&&operations<=32);std::vector<std::uint32_t> removed(operations);for(auto& n:removed)n=take<std::uint32_t>(in);std::string extra;require(!(in>>extra));
 std::int32_t persistence=0;MissionTagType type{persistence};auto* typePointer=&type;MissionTagTrigger* first=nullptr;std::uint8_t executing=0;
 std::array<MissionTagState,2> tags{{{typePointer,first,instances[0],executing},{typePointer,first,instances[1],executing}}};
 std::array<int,7> identityStorage{};std::array<const void*,10> identities{nullptr,&tags[0],&tags[1],&identityStorage[0],&identityStorage[1],&identityStorage[2],&identityStorage[3],&identityStorage[4],&identityStorage[5],&identityStorage[6]};
 const auto pointer=[&](int id){return identities.at(std::size_t(id));};const auto id=[&](const void* p){for(int i=0;i<10;++i)if(pointer(i)==p)return i;throw std::invalid_argument("Unknown Techno pointer");};
 MissionTagState* objectTag=tagId?&tags[std::size_t(tagId-1)]:nullptr;
 std::array<const void*,3> next{};for(int i=0;i<3;++i)next[std::size_t(i)]=pointer(nextIds[std::size_t(i)]);
 std::array<const void*,15> links{};for(int i=0;i<15;++i)links[std::size_t(i)]=pointer(fields[std::size_t(i)]);
 std::array<const void*,8> weapons{};for(int i=0;i<8;++i)weapons[std::size_t(i)]=pointer(weaponIds[std::size_t(i)]);
 std::array<const void*,2> controlFields{pointer(controlIds[0]),pointer(controlIds[1])};
 std::array<std::array<const void*,8>,4> buffers{};std::array<const void*,8> alternate{};std::array<std::span<const void*>,4> slots;std::array<int,4> vectorIdentity{};
 for(int v=0;v<4;++v){for(int i=0;i<8;++i)buffers[std::size_t(v)][std::size_t(i)]=pointer(inputBuffers[std::size_t(v)][std::size_t(i)]);slots[std::size_t(v)]=buffers[std::size_t(v)];}
 alternate.fill(pointer(subjectId));
 std::array<MissionExpirationVector<const void*>,4> vectors{{{counts[0],slots[0],&vectorIdentity[0]},{counts[1],slots[1],&vectorIdentity[1]},{counts[2],slots[2],&vectorIdentity[2]},{counts[3],slots[3],&vectorIdentity[3]}}};
 const auto store=[&](const void* p,std::int64_t offset,std::uint32_t value,const void* link){int identity=id(p);std::cout<<" W "<<identity<<' '<<offset<<' '<<(link?std::uint32_t(id(link)):value);};
 MissionTagStore observer=[&](const void* p,std::int64_t offset,std::uint32_t value,const void* link){
  for(int v=0;v<4;++v)if(p==&vectorIdentity[std::size_t(v)]){std::cout<<" W "<<20+v<<' '<<offset<<' '<<(link?std::uint32_t(id(link)):value);return;}
  if(p==&links[0]){std::cout<<" W 4 252 "<<id(link);return;}store(p,offset,value,link);
 };
 MissionRadioTagExpiration radio{{objectTag,links[14],pointer(4)},vectors[0]};
 MissionExpirationChain chain{links[0],&links[0],[&](const void* p)->const void*&{const auto i=id(p);require(i>=1&&i<=3);return next[std::size_t(i-1)];},8};
 MissionExpirationControl control{controlFields[0],controlFields[1],pointer(6)};
 MissionTechnoTagExpiration techno{radio,chain,links[1],links[2],links[3],links[4],links[5],links[6],links[7],links[8],links[9],links[10],weapons,links[11],links[12],links[13],timerStart,timerPadding,timerDuration,mission,wordA8,byte372,byte5BA,vectors[1],vectors[2],vectors[3]};
 MissionTechnoTagExpirationServices services{frame,session,scratch};
 services.subjectOwner=[&]{std::cout<<" S owner";if(mode==2)links[3]=pointer(5);return pointer(ownerResult);};
 services.retryRange=[&](int lo,int hi){require(lo==4&&hi==8);std::cout<<" S range 4 8";if(mode==2)frame=missionTagWrapped(frame,3);return retry;};
 services.setTarget370=[&](const void* p){require(!p);std::cout<<" S target 0";if(mode){links[6]=nullptr;if(mode==2){links[3]=pointer(subjectId);mission=25;}}};
 services.predicate1E4=[&]{std::cout<<" S predicate1 "<<predicate1;return std::uint8_t(predicate1);};
 services.action1E0=[&]{std::cout<<" S action1";};services.kind2C=[&]{std::cout<<" S kind "<<kind;return kind;};
 services.predicateC0=[&]{std::cout<<" S predicateC "<<predicateC;if(mode==3){slots[2]=alternate;counts[2]=4;counts[1]=2;}return std::uint8_t(predicateC);};
 services.queryCC=[&](int n){require(n==1);std::cout<<" S query 1";return pointer(queryResult);};services.action400=[&]{std::cout<<" S action400";if(mode==2)links[8]=nullptr;};
 services.control=[&](const void* p){require(p==pointer(6));return control;};
 services.service68A560=[&](const void* p,const void* s){require(p==pointer(7)&&s==pointer(subjectId));std::cout<<" S serviceA 7 "<<subjectId;if(mode==2){links[4]=nullptr;links[12]=pointer(subjectId);}};
 services.service6E24C0=[&](const void* p,const void* s){require(p==pointer(8)&&s==pointer(subjectId));std::cout<<" S serviceB 8 "<<subjectId;};
 MissionTagExpiredAbstract subject{tags[std::size_t(subjectId-1)],pointer(subjectId),next[std::size_t(subjectId-1)]};
 for(auto removal:removed){std::cout<<" O "<<root;if(root==0)expireMissionRadioTag(radio,subject,removal,observer);else if(root==1)expireMissionTechnoTag(techno,subject,std::uint8_t(flags),removal,services,observer);else if(root==2)unlinkMissionExpirationChain(chain,subject.identity,observer);else {const auto result=expireMissionControlTag(control,subject.identity,observer);std::cout<<" V "<<unsigned(result);}std::cout<<" R";}
 std::cout<<" state "<<instances[0]<<' '<<instances[1]<<' '<<id(objectTag);for(auto p:next)std::cout<<' '<<id(p);for(auto p:links)std::cout<<' '<<id(p);for(auto p:weapons)std::cout<<' '<<id(p);
 std::cout<<' '<<timerStart<<' '<<timerPadding<<' '<<timerDuration<<' '<<mission<<' '<<wordA8<<' '<<unsigned(byte372)<<' '<<unsigned(byte5BA)<<' '<<frame;for(auto p:controlFields)std::cout<<' '<<id(p);for(auto c:counts)std::cout<<' '<<c;for(auto& b:buffers)for(auto p:b)std::cout<<' '<<id(p);for(auto p:alternate)std::cout<<' '<<id(p);std::cout<<'\n';
}
void guards(){
 const void* head=nullptr;MissionExpirationChain chain{head,nullptr,{},0};unlinkMissionExpirationChain(chain,nullptr);
 int a=1,b=2;head=&a;bool refused=false;try{unlinkMissionExpirationChain(chain,&b);}catch(const std::invalid_argument&){refused=true;}require(refused&&head==&a);
 chain.next=[&](const void*)->const void*&{return head;};chain.traversalLimit=2;refused=false;try{unlinkMissionExpirationChain(chain,&b);}catch(const std::invalid_argument&){refused=true;}require(refused&&head==&a);
 const void* left=&a;const void* right=&b;expireMissionControlTag({left,right,&a},&b);require(left==&a&&right==&b);expireMissionControlTag({left,right,&a},&a);require(!left&&!right);
 // A copied accessor borrows the same logical field. Copy assignment of a
 // view rebinds; explicit pointer conversion is required for a splice store.
 std::array<int,3> ids{1,2,3};int nextA=2,nextB=3,nextC=0;
 const auto resolve=[&](int n)->const void*{return n?&ids.at(std::size_t(n-1)):nullptr;};
 const auto view=[&](int& n){return MissionExpirationPointerView{[&,p=&n]{return resolve(*p);},[&,p=&n](const void* v){*p=0;for(int i=0;i<3;++i)if(v==&ids[i])*p=i+1;}};};
 auto borrowed=view(nextA);auto copied=borrowed;copied=resolve(3);require(nextA==3);nextA=2;
 head=resolve(1);MissionExpirationChain logical{head,&head,[&](const void* p){return view(p==resolve(1)?nextA:p==resolve(2)?nextB:nextC);},4};
 unlinkMissionExpirationChain(logical,resolve(2));require(nextA==3&&nextB==3&&head==resolve(1));
 unlinkMissionExpirationChain(logical,resolve(1));require(head==resolve(3)&&nextA==3);
 std::cout<<"Techno Tag guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
