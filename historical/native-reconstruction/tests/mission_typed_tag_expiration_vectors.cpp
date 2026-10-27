// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionTypedTagExpiration.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include "sim/RevealArea.hpp"
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Techno Tag fixture outside domain");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
constexpr std::array<int,15> offsets{0xfc,0x108,0x1b0,0x1b4,0x208,0x20c,0x228,0x22c,0x230,0x238,0x23c,0x27c,0x384,0x3f8,0x30};
void run(std::istream& in){
 require(take<char>(in)=='T');const int root=take<int>(in),subjectId=take<int>(in),flags=take<int>(in);require(root>=0&&root<7&&subjectId>=1&&subjectId<=2&&flags>=0&&flags<=255&&!(flags&1));
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
 const auto operations=take<unsigned>(in);require(operations>0&&operations<=32);std::vector<std::uint32_t> removed(operations);for(auto& n:removed)n=take<std::uint32_t>(in);require(take<char>(in)=='|');
 std::array<int,17> typedIds{};for(auto& n:typedIds){n=take<int>(in);require(n>=0&&n<=16);}
 std::array<std::int32_t,3> recordHealth{};for(auto& n:recordHealth)n=take<std::int32_t>(in);
 std::array<unsigned,3> recordByte7D{};for(auto& n:recordByte7D){n=take<unsigned>(in);require(n<=255);}
 std::array<int,3> recordNext4C8{};for(auto& n:recordNext4C8){n=take<int>(in);require(n>=0&&n<=16);}
 std::array<unsigned,5> typeBytes{};for(auto& n:typeBytes){n=take<unsigned>(in);require(n<=255);}
 std::int32_t queuedA0=take<std::int32_t>(in),actorHealth=take<std::int32_t>(in);const auto globalByte=take<unsigned>(in);require(globalByte<=255);
 Coord subjectPoint{take<std::int32_t>(in),take<std::int32_t>(in),take<std::int32_t>(in)};
 std::array<int,3> extraCounts{};for(auto& n:extraCounts){n=take<int>(in);require(n>=-2&&n<=8);}
 std::array<std::array<int,8>,3> extraInput{};for(auto& b:extraInput)for(auto& n:b){n=take<int>(in);require(n>=0&&n<=16);}
 std::array<std::int32_t,5> strengths{};for(auto& n:strengths)n=take<std::int32_t>(in);
 std::array<std::array<unsigned,2>,5> animationBytes{};for(auto& b:animationBytes)for(auto& n:b){n=take<unsigned>(in);require(n<=255);}
 const auto thresholdBits=take<std::uint64_t>(in);double threshold=std::bit_cast<double>(thresholdBits);
 const int strengthType=take<int>(in),childMode=take<int>(in),mapMode=take<int>(in);require(childMode>=0&&childMode<=3&&mapMode>=0&&mapMode<=2);
#ifdef RA2_VEHICLE_EXPIRATION_FIXTURE
 require(take<char>(in)=='V');const auto vehicle=take<int>(in),derivedId=take<int>(in),linkId=take<int>(in),mutation=take<int>(in);
 require(root==4&&(vehicle==0||vehicle==1)&&derivedId>=0&&derivedId<=16&&linkId>=0&&linkId<=16&&mutation>=0&&mutation<=2);
#endif
 std::string extra;require(!(in>>extra));
 std::int32_t persistence=0;MissionTagType type{persistence};auto* typePointer=&type;MissionTagTrigger* first=nullptr;std::uint8_t executing=0;
 std::array<MissionTagState,2> tags{{{typePointer,first,instances[0],executing},{typePointer,first,instances[1],executing}}};
 std::array<RevealAreaCell,5> cells{};std::array<int,14> identityStorage{};std::array<const void*,17> identities{nullptr,&tags[0],&tags[1],&identityStorage[0],&identityStorage[1],&identityStorage[2],&identityStorage[3],&identityStorage[4],&identityStorage[5],&identityStorage[6],&cells[0],&cells[1],&cells[2],&cells[3],&cells[4],&identityStorage[12],&identityStorage[13]};
#ifdef RA2_TEAM_EXPIRATION_FIXTURE
 int teamIdentity=0;identities[1]=&teamIdentity;
 require(subjectId==1&&tagId!=1&&(root==4||root==5)&&!(flags&3));
#endif
 const auto pointer=[&](int id){return identities.at(std::size_t(id));};const auto id=[&](const void* p){for(int i=0;i<17;++i)if(pointer(i)==p)return i;throw std::invalid_argument("Unknown Techno pointer");};
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
 constexpr std::array<int,17> typedOffsets{0x418,0x41c,0x438,0x440,0x474,0x490,0x494,0x498,0x4b8,0x4bc,0x4c0,0x4c4,0x4c8,0x4d4,0x4e8,0x580,0x5a8};
 std::array<const void*,17> typed{};for(int i=0;i<17;++i)typed[std::size_t(i)]=pointer(typedIds[std::size_t(i)]);
 std::array<std::array<const void*,8>,3> extraBuffers{};std::array<std::span<const void*>,3> extraSlots;std::array<int,3> extraIdentities{};
 for(int v=0;v<3;++v){for(int i=0;i<8;++i)extraBuffers[std::size_t(v)][std::size_t(i)]=pointer(extraInput[std::size_t(v)][std::size_t(i)]);extraSlots[std::size_t(v)]=extraBuffers[std::size_t(v)];}
 std::array<MissionExpirationVector<const void*>,3> extraVectors{{{extraCounts[0],extraSlots[0],&extraIdentities[0]},{extraCounts[1],extraSlots[1],&extraIdentities[1]},{extraCounts[2],extraSlots[2],&extraIdentities[2]}}};
 const auto inheritedObserver=observer;observer=[&](const void* p,std::int64_t off,std::uint32_t value,const void* link){for(int i=0;i<3;++i)if(p==&extraIdentities[std::size_t(i)]){std::cout<<" W "<<30+i<<' '<<off<<' '<<(link?std::uint32_t(id(link)):value);return;}inheritedObserver(p,off,value,link);};
 // One actual map/Cell owner; the Cell identities are distinct from all actors.
 for(int i=0;i<5;++i)cells[std::size_t(i)].identity=10+i;
 cells[4].point={-91,123};std::vector<RevealAreaCell*> map(262144);
 if(mapMode!=2)for(int i=0;i<4;++i)if(mapMode!=1||(i&1))map[std::size_t((19+(i>>1))*512+19+(i&1))]=&cells[std::size_t(i)];
 RevealAreaWorld mapWorld{0,0,map,map,&cells[4]};mapWorld.fallbackStore=[&](char,TerrainCellPoint p){std::cout<<" MAPF "<<p.x<<' '<<p.y;};mapWorld.query=[&](char,TerrainCellPoint p,int identity){std::cout<<" MAP "<<p.x<<' '<<p.y<<' '<<identity;};
 const std::array<int,5> typeIds{1,2,9,15,16};const auto typeIndex=[&](const void* p){const int identity=id(p);for(int i=0;i<5;++i)if(typeIds[std::size_t(i)]==identity)return i;throw std::invalid_argument("Unknown typed expiration type");};
 std::array<std::uint8_t,3> recordFlags{std::uint8_t(flags),std::uint8_t(flags),0};std::array<std::uint8_t,3> bytes7D{};std::array<std::uint8_t,5> bytesC08{};
 std::array<const void*,3> recordNext{},recipients{};for(int i=0;i<3;++i){bytes7D[std::size_t(i)]=std::uint8_t(recordByte7D[std::size_t(i)]);recordNext[std::size_t(i)]=pointer(recordNext4C8[std::size_t(i)]);recipients[std::size_t(i)]=pointer(9);}for(int i=0;i<5;++i)bytesC08[std::size_t(i)]=std::uint8_t(typeBytes[std::size_t(i)]);
 std::uint8_t zeroByte=0;std::int32_t zeroHealth=0;const void* zeroPointer=nullptr;
#ifdef RA2_VEHICLE_EXPIRATION_FIXTURE
 const void* derived=pointer(derivedId);const void* link5AC=pointer(linkId);
 const auto predicateBefore=services.predicateC0;
 services.predicateC0=[&]{const auto result=predicateBefore();if(mutation){derived=pointer(mutation==1?subjectId:9);link5AC=pointer(mutation==1?subjectId:9);}return result;};
#endif
 MissionFootTagExpiration foot{techno,typed[11],typed[15],typed[12],typed[7],typed[5],typed[6],typed[9],typed[8],typed[16],queuedA0,extraVectors[0],extraVectors[1]};
 auto global=std::uint8_t(globalByte);MissionFootTagExpirationServices footServices{global};
 footServices.record=[&](const void* p)->MissionExpirationRecord{const int identity=id(p);if(identity>=1&&identity<=3){const int i=identity-1;return {recordHealth[std::size_t(i)],recordFlags[std::size_t(i)],bytes7D[std::size_t(i)],identity<=2?bytesC08[std::size_t(i)]:zeroByte,recordNext[std::size_t(i)],recipients[std::size_t(i)]};}const int i=typeIndex(p);return {zeroHealth,zeroByte,zeroByte,bytesC08[std::size_t(i)],zeroPointer,zeroPointer};};
 footServices.nestedExpiration28=[&](const void* receiver,const void* expired,std::uint32_t raw){require(receiver==pointer(9)&&expired==pointer(subjectId)&&raw==1);std::cout<<" S nested 9 "<<subjectId<<" 1";if(childMode==3){typed[16]=pointer(subjectId);typed[9]=pointer(subjectId);}};
 footServices.clear1B0=[&](const void* p){require(!p);std::cout<<" S clear1B0 0";if(childMode==1)typed[7]=pointer(subjectId);};
 footServices.coordinates48=[&](const void* p){require(p==pointer(subjectId));return subjectPoint;};
 footServices.cell548070=[&](TerrainCellPoint point)->const void*{return pointer(revealAreaMapCell(point,mapWorld).identity);};
 MissionBuildingTagExpiration building{techno,typed[2],typed[3],typed[1],typed[13],typed[14],typed[4],typed[0],std::span(typed).subspan(10,3),actorHealth,extraVectors[2]};
 MissionBuildingTagExpirationServices buildingServices{threshold};
 buildingServices.strength84=[&]()->const std::int32_t&{std::cout<<" S strength "<<strengthType;if(childMode==1)actorHealth=99;if(childMode==2){typed[0]=pointer(16);threshold=-1.;}return strengths[std::size_t(typeIndex(pointer(strengthType)))];};
 buildingServices.animationFirstByte=[&](const void* p,int off){require(off==0x1158||off==0x1168);return std::uint8_t(animationBytes[std::size_t(typeIndex(p))][off==0x1168?1:0]);};
 buildingServices.animation44CA60=[&](const void* p,int off,int damaged){std::cout<<" S animation "<<id(p)<<' '<<off<<' '<<damaged;if(childMode==3)typed[0]=pointer(subjectId);};
 const auto effectiveKind=root==5?15:root==6?6:kind;services.kind2C=[&]{std::cout<<" S kind "<<effectiveKind;return effectiveKind;};
#ifdef RA2_TEAM_EXPIRATION_FIXTURE
 MissionTeamExpiredAbstract subject{pointer(subjectId),next[std::size_t(subjectId-1)]};
 for(auto removal:removed){std::cout<<" O "<<root;
#ifdef RA2_VEHICLE_EXPIRATION_FIXTURE
 if(vehicle==0)expireMissionUnitTag({foot,derived,link5AC},subject,std::uint8_t(flags),removal,services,footServices,observer);
 else expireMissionAircraftTag({foot,derived,link5AC},subject,std::uint8_t(flags),removal,services,footServices,observer);
#else
 if(root==4)expireMissionFootTag(foot,subject,std::uint8_t(flags),removal,services,footServices,observer);else expireMissionInfantryTag(foot,subject,std::uint8_t(flags),removal,services,footServices,observer);
#endif
 std::cout<<" R";}
#else
 MissionTagExpiredAbstract subject{tags[std::size_t(subjectId-1)],pointer(subjectId),next[std::size_t(subjectId-1)]};
 for(auto removal:removed){std::cout<<" O "<<root;if(root==0)expireMissionRadioTag(radio,subject,removal,observer);else if(root==1)expireMissionTechnoTag(techno,subject,std::uint8_t(flags),removal,services,observer);else if(root==2)unlinkMissionExpirationChain(chain,subject.identity,observer);else if(root==3){const auto result=expireMissionControlTag(control,subject.identity,observer);std::cout<<" V "<<unsigned(result);}else if(root==4)expireMissionFootTag(foot,subject,std::uint8_t(flags),removal,services,footServices,observer);else if(root==5)expireMissionInfantryTag(foot,subject,std::uint8_t(flags),removal,services,footServices,observer);else expireMissionBuildingTag(building,subject,std::uint8_t(flags),removal,services,buildingServices,observer);std::cout<<" R";}
 #endif
 std::cout<<" state "<<instances[0]<<' '<<instances[1]<<' '<<id(objectTag);for(auto p:next)std::cout<<' '<<id(p);for(auto p:links)std::cout<<' '<<id(p);for(auto p:weapons)std::cout<<' '<<id(p);
 std::cout<<' '<<timerStart<<' '<<timerPadding<<' '<<timerDuration<<' '<<mission<<' '<<wordA8<<' '<<unsigned(byte372)<<' '<<unsigned(byte5BA)<<' '<<frame;for(auto p:controlFields)std::cout<<' '<<id(p);for(auto c:counts)std::cout<<' '<<c;for(auto& b:buffers)for(auto p:b)std::cout<<' '<<id(p);for(auto p:alternate)std::cout<<' '<<id(p);
 std::cout<<" TYPED";for(auto p:typed)std::cout<<' '<<id(p);std::cout<<' '<<actorHealth<<' '<<std::bit_cast<std::uint64_t>(threshold);for(auto c:extraCounts)std::cout<<' '<<c;for(auto& b:extraBuffers)for(auto p:b)std::cout<<' '<<id(p);std::cout<<' '<<cells[4].point.x<<' '<<cells[4].point.y;
#ifdef RA2_VEHICLE_EXPIRATION_FIXTURE
 std::cout<<" VEHICLE "<<id(derived)<<' '<<id(link5AC);
#endif
 std::cout<<'\n';
}
void guards(){
 const void* head=nullptr;MissionExpirationChain chain{head,nullptr,{},0};unlinkMissionExpirationChain(chain,nullptr);
 int a=1,b=2;head=&a;bool refused=false;try{unlinkMissionExpirationChain(chain,&b);}catch(const std::invalid_argument&){refused=true;}require(refused&&head==&a);
 chain.next=[&](const void*)->const void*&{return head;};chain.traversalLimit=2;refused=false;try{unlinkMissionExpirationChain(chain,&b);}catch(const std::invalid_argument&){refused=true;}require(refused&&head==&a);
 const void* left=&a;const void* right=&b;expireMissionControlTag({left,right,&a},&b);require(left==&a&&right==&b);expireMissionControlTag({left,right,&a},&a);require(!left&&!right);
 const int previous=std::fegetround();std::int32_t health=1,denominator=10;
 const auto ratio=missionExpirationHealthRatio(health,[&]()->const std::int32_t&{health=2;return denominator;});require(ratio<.1&&std::fegetround()==previous);
 bool propagated=false;try{(void)missionExpirationHealthRatio(health,[]()->const std::int32_t&{throw std::runtime_error("diagnostic");});}catch(const std::runtime_error&){propagated=true;}require(propagated&&std::fegetround()==previous);
 std::cout<<"Typed Tag guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
