// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/HouseMakeAlly.hpp"
#include "sim/MissionBuildingTarget.hpp"
#ifdef RA2_DIPLOMACY_JOIN
#include "sim/HouseDiplomacy.hpp"
#endif
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
namespace {
void require(bool b){if(!b)throw std::invalid_argument("House MakeAlly fixture outside domain");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
std::uint8_t byte(std::istream& in){int v=take<int>(in);require(v>=0&&v<=255);return std::uint8_t(v);}
struct Type{int country=0,parent=0,comparison=0,color=0;std::uint8_t passive=0;std::string name;};
struct House{int index=0,enemy=0,count=0;const void* type=nullptr;std::uint8_t field=0,f134=0,f135=0;
#ifdef RA2_DIPLOMACY_JOIN
std::uint8_t f191=53;
#endif
std::uint32_t allies=0,mask=0;std::array<HouseThreatScore,4> scores;std::span<HouseThreatScore> entries=scores;};
struct Actor{int kind=0,id=0,country=0,word310=0,weaponIndex=0,permission=0;std::int16_t x=0,y=0;std::uint8_t flag76=0,byte404=0;const void* owner=nullptr;const void* target=nullptr;const void* service=nullptr;const void* attached=nullptr;};
void run(std::istream& in){
#ifdef RA2_DIPLOMACY_JOIN
 const int root=take<int>(in);auto rule111D=byte(in);const int sessionPresent=take<int>(in);auto sessionResult=take<std::uint32_t>(in);
 require(root>=0&&root<=2&&(sessionPresent==0||sessionPresent==1));
#endif
 require(take<char>(in)=='B');const int current=take<int>(in),target=take<int>(in);auto announce=byte(in);int mode=take<int>(in),unrestricted=take<int>(in),houseCount=take<int>(in),typeCount=take<int>(in),actorCount=take<int>(in),actorBacking=take<int>(in),currentID=take<int>(in),quiet=take<int>(in);auto rule=byte(in);auto delay=std::bit_cast<double>(take<std::uint64_t>(in));int mutation=take<int>(in);
 require(current>=1&&current<=5&&target>=1&&target<=5&&houseCount>=-2&&houseCount<=8&&typeCount>=-2&&typeCount<=4&&actorCount>=-2&&actorCount<=8&&actorBacking>=1&&actorBacking<=2&&currentID>=1&&currentID<=5&&mutation>=0&&mutation<=15);
 std::array<Type,4> types;std::array<House,5> houses;std::array<Actor,4> actors;std::array<const void*,8> hs{},as{},alt{};std::array<const void*,4> ts{};std::array<TargetRegistryEntry,32> primary,alternate;
 const auto hp=[&](int id)->const void*{require(id>=0&&id<=5);return id?&houses[std::size_t(id-1)]:nullptr;};
 const auto tp=[&](int id)->const void*{require(id>=1&&id<=4);return &types[std::size_t(id-1)];};
 const auto ap=[&](int id)->const void*{require(id>=0&&id<=4);return id?&actors[std::size_t(id-1)]:nullptr;};
 const auto hid=[&](const void* p){for(int i=0;i<=5;++i)if(hp(i)==p)return i;throw std::invalid_argument("Foreign House");};
 const auto tid=[&](const void* p){for(int i=1;i<=4;++i)if(tp(i)==p)return i;throw std::invalid_argument("Foreign type");};
 const auto aid=[&](const void* p){for(int i=0;i<=4;++i)if(ap(i)==p)return i;throw std::invalid_argument("Foreign actor");};
 const auto house=[&](const void* p)->House&{return houses.at(std::size_t(hid(p)-1));};const auto actor=[&](const void* p)->Actor&{return actors.at(std::size_t(aid(p)-1));};
 for(auto& p:hs)p=hp(take<int>(in));for(auto& p:ts)p=tp(take<int>(in));for(auto& p:as)p=ap(take<int>(in));for(auto& p:alt)p=ap(take<int>(in));
 for(int i=0;i<4;++i){auto& t=types[std::size_t(i)];t.country=take<int>(in);t.parent=take<int>(in);t.passive=byte(in);t.comparison=take<int>(in);t.color=take<int>(in);t.name="Type"+std::to_string(i+1);}
 for(auto& h:houses){h.index=take<int>(in);h.type=tp(take<int>(in));h.field=byte(in);h.allies=take<std::uint32_t>(in);h.mask=take<std::uint32_t>(in);h.f134=byte(in);h.f135=byte(in);h.enemy=take<int>(in);h.count=take<int>(in);require(h.count>=-2&&h.count<=4);}
 for(auto& h:houses)for(auto& e:h.scores){e.house=hp(take<int>(in));e.value=take<int>(in);}
 for(auto& a:actors){a.kind=take<int>(in);a.id=take<int>(in);int x=take<int>(in),y=take<int>(in);require(x>=-32768&&x<=32767&&y>=-32768&&y<=32767);a.x=std::int16_t(x);a.y=std::int16_t(y);a.flag76=byte(in);a.country=take<int>(in);a.owner=hp(take<int>(in));a.target=ap(take<int>(in));a.byte404=byte(in);a.word310=take<int>(in);a.service=take<int>(in)?ap(1):nullptr;a.attached=ap(take<int>(in));a.weaponIndex=take<int>(in);a.permission=take<int>(in);}
 for(auto* entries:{&primary,&alternate})for(auto& e:*entries){e.key=take<int>(in);e.object=ap(take<int>(in));}
 int registryCount=take<int>(in);auto sorted=byte(in);int backing=take<int>(in),cacheBacking=take<int>(in),cacheIndex=take<int>(in);const void* fallback=ap(take<int>(in));require(registryCount>=0&&registryCount<=32&&backing>=1&&backing<=2&&cacheBacking>=0&&cacheBacking<=2&&cacheIndex>=0&&cacheIndex<32);
 TargetReference scratch;scratch.value=take<int>(in);scratch.tag=byte(in);for(auto& p:scratch.padding)p=byte(in);std::string extra;require(!(in>>extra));
 std::span<const void*> housesSpan=hs,typesSpan=ts,actorsSpan=actorBacking==1?std::span(as):std::span(alt);std::span<TargetRegistryEntry> registry=backing==1?std::span(primary):std::span(alternate);TargetRegistryEntry* cached=cacheBacking==0?nullptr:cacheBacking==1?&primary[std::size_t(cacheIndex)]:&alternate[std::size_t(cacheIndex)];const void* currentHouse=hp(currentID);
#ifdef RA2_DIPLOMACY_JOIN
 std::array<const void*,8> alternateHouses{hp(5),hp(4),hp(3),hp(2),hp(1),hp(5),hp(4),hp(3)};
#endif
 bool changed=false;int phase=0;const void* sourceActor=nullptr;auto& self=houses[std::size_t(current-1)];auto& other=houses[std::size_t(target-1)];
 const auto event=[&](int service,int a=0,std::int64_t b=0){std::cout<<" E "<<service<<' '<<a<<' '<<b<<' '<<self.allies<<' '<<self.mask;};
 const auto mutate=[&](int service,int id){
  if(changed||!mutation)return;const int wanted[]={0,1,2,44,56,16,44,60,10,848,240,5,6,3,0x781f20,60};if(service!=wanted[mutation]||(mutation==6&&phase!=1))return;changed=true;
  if(mutation==1){
#ifdef RA2_DIPLOMACY_JOIN
 houseCount=8;housesSpan=alternateHouses;
#endif
 other.index=-33;mode=4;unrestricted=0;actorsSpan=alt;actorCount=8;registry=alternate;registryCount=32;sorted=0;}
  if(mutation==2){
#ifdef RA2_DIPLOMACY_JOIN
 houseCount=3;housesSpan=alternateHouses;
#endif
 self.count=3;self.scores[0]={hp(target),INT32_MIN};self.scores[1]={hp(target),7};self.scores[2]={hp(5),99};}
  if(mutation==3){auto& a=actors.at(std::size_t(id-1));a.kind=0;a.flag76=255;actorsSpan=alt;actorCount=8;}
  if(mutation==4){self.index=houseThreatAdd(actors.at(std::size_t(id-1)).country,1);actors.at(std::size_t(id-1)).target=ap(4);}
  if(mutation==5)scratch.tag=0;
  if(mutation==6){registryCount=0;sorted=1;cached=nullptr;fallback=ap(4);}
  if(mutation==7){const auto p=actors.at(std::size_t(id-1)).owner;if(p)house(p).index=-1;self.allies=0;}
  if(mutation==8)actors.at(std::size_t(id-1)).target=ap(4);
  if(mutation==9)actors.at(std::size_t(id-1)).attached=ap(4);
  if(mutation==10)for(auto& a:actors)a.attached=ap(3);
  if(mutation==11){mode=0;self.f134=0;self.f135=0;other.f135=255;delay=.6;types.at(std::size_t(tid(self.type)-1)).color=-7;}
  if(mutation==12){currentHouse=hp(target);quiet=255;other.allies=0;}
  if(mutation==13){self.f134=0;self.f135=0;actorCount=-1;actorsSpan=alt;types.at(std::size_t(tid(other.type)-1)).passive=255;}
  if(mutation==14){other.type=tp(4);mode=4;unrestricted=1;self.index=-1;}
  if(mutation==15){require(sourceActor);actor(sourceActor).target=nullptr;}
 };
 HouseAllianceWorld alliance{mode,unrestricted,houseCount,housesSpan,typeCount,typesSpan};
 alliance.house=[&](const void* p){auto& h=house(p);return HouseAllianceRecord{p,h.index,h.type,h.field,h.allies};};
 alliance.type=[&](const void* p){auto& t=types.at(std::size_t(tid(p)-1));return HouseAllianceType{t.country,t.parent,t.passive,t.name};};
 alliance.compareNames=[&](std::string_view name,std::string_view wanted){require(wanted=="Civilian");int id=0;for(int i=1;i<=4;++i)if(types[std::size_t(i-1)].name==name)id=i;require(id);int result=types[std::size_t(id-1)].comparison;event(0x781f20,id,result);mutate(0x781f20,id);return result;};
 std::int16_t zero=0;std::array<int,9> table{};HouseThreatWorld threat{mode,actorCount,actorsSpan,{zero,zero},table,table};
 threat.house=[&](const void* p){auto& h=house(p);return HouseThreatHouse{p,h.index,h.field,h.f134,h.f135,h.allies,h.enemy,h.count,h.entries,{}};};
 TargetReferenceWorld targets{registryCount,registry,sorted,cached,fallback};
 targets.kind=[&](const void* p){int id=aid(p),result=actor(p).kind;event(44,id,result);mutate(44,id);return result;};
 targets.uniqueID=[&](const void* p){int id=aid(p),result=actor(p).id;event(16,id,result);phase=1;mutate(16,id);return result;};
 targets.cell24=[&](const void* p){auto& a=actor(p);return TargetReferenceCell{a.x,a.y};};
 targets.compare=[&](auto a,auto b,auto,auto){event(0x41ba10,int(a)+(registry.data()==primary.data()?32:64),std::int64_t(b));};
 HouseMakeAllyWorld w{alliance,threat,targets,actorCount,actorsSpan,currentHouse,quiet};
 w.house=[&](const void* p){auto& h=house(p);return HouseMakeAllyFields{h.mask,h.f134,h.f135,h.allies};};w.actor=[&](const void* p){auto& a=actor(p);return HouseMakeAllyActor{a.flag76,a.target};};w.rules=[&](){return HouseMakeAllyRules{rule,delay};};
 w.mapSight=[&](bool add){int service=add?9:1;event(service);mutate(service,0);};w.rebuildGrid=[&](const void* p){event(2,hid(p));mutate(2,0);};w.allianceNotification=[&](){event(3);mutate(3,0);};
 w.country38=[&](const void* p){sourceActor=p;int result=actor(p).country;event(56,aid(p),result);mutate(56,aid(p));return result;};w.owner3C=[&](const void* p){const auto owner=actor(p).owner;event(60,aid(p),hid(owner));mutate(60,aid(p));return owner;};
 w.clear370=[&](const void* p){auto& a=actor(p);int dummy=0;std::uint8_t b=0;const void* null=nullptr;MissionBuildingTarget fields{p,dummy,dummy,dummy,b,b,dummy,dummy,null,{null},b,a.byte404,a.target,a.service,a.word310,a.attached,null};MissionBuildingTargetServices services;
  services.clear68A490=[&](const void* service,const void* targetArg){require(service==ap(1)&&!targetArg);event(10,aid(p));mutate(10,aid(p));};
  services.weaponIndex2B8=[&](const void* targetArg){require(!targetArg);int result=a.weaponIndex;event(696,aid(p),result);mutate(696,aid(p));return result;};services.weapon350=[&](const void* targetArg,int index){require(!targetArg&&index==a.weaponIndex);int result=a.permission;event(848,aid(p),result);mutate(848,aid(p));return std::uint8_t(result);};
  services.releaseF0=[&](const void* attachment){event(240,aid(attachment));mutate(240,aid(attachment));};
  clearMissionTechnoTarget(fields,services,[&](const void*,std::int64_t offset,std::uint32_t value,const void* ptr){event(int(offset),aid(p),ptr?aid(ptr):value);});
 };
 int localized=0,text=0;w.localizeNotice=[&]()->const void*{event(4);mutate(4,0);return &localized;};w.formatNotice=[&](const void* source,const void* a,const void* b)->const void*{require(source==&localized);event(5,hid(a),hid(b));mutate(5,0);return &text;};
 w.colorC0=[&](const void* p){return types.at(std::size_t(tid(p)-1)).color;};w.displayNotice=[&](const void* p,int color,std::uint32_t duration){require(p==&text);event(6,color,duration);mutate(6,0);};w.speech=[&](std::uint32_t key){event(7,int(key));mutate(7,0);};w.redraw0=[&](){event(8);mutate(8,0);};
#ifdef RA2_DIPLOMACY_JOIN
 const void* session=sessionPresent?&localized:nullptr;
 HouseAllianceNotificationWorld notification{rule111D,session,mode,houseCount,housesSpan};
 notification.house=[&](const void* p){auto& h=house(p);return HouseAllianceNotificationFields{h.field,h.f134,h.f135,h.f191};};
 notification.session4=[&](const void* p){require(p==&localized);event(17,0,sessionResult);return sessionResult;};
 notification.stored191=[&](const void* p,auto value){event(0x191,hid(p),value);};
 HouseMakeEnemyWorld enemy{threat,unrestricted,currentHouse};
 enemy.house=[&](const void* p){auto& h=house(p);return HouseMakeEnemyFields{h.index,h.type,h.f134,h.f135,h.allies,h.mask};};
 enemy.passive1A6=[&](const void* p){return types.at(std::size_t(tid(p)-1)).passive;};
 enemy.colorC0=w.colorC0;enemy.delay1128=[&](){return delay;};enemy.mapSight=w.mapSight;enemy.rebuildGrid=w.rebuildGrid;
 enemy.localize=w.localizeNotice;enemy.format=w.formatNotice;enemy.display=w.displayNotice;enemy.redraw0=w.redraw0;enemy.speech=w.speech;
 HouseDiplomacy diplomacy(notification,w,enemy,[]{return TargetReference{};});
 diplomacy.entered=[&](char kind,const void* a,const void* b){std::cout<<" J "<<kind<<' '<<hid(a)<<' '<<hid(b);};
 if(root==0)diplomacy.notify();else if(root==1)diplomacy.makeAlly(hp(current),hp(target),announce,scratch);else diplomacy.makeEnemy(hp(current),hp(target),announce);
#else
 makeHouseAlly(hp(current),hp(target),announce,scratch,w);
#endif
 int cb=0,ci=0;if(cached){for(int i=0;i<32;++i){if(cached==&primary[std::size_t(i)]){cb=1;ci=i;}if(cached==&alternate[std::size_t(i)]){cb=2;ci=i;}}require(cb);}
 std::cout<<" R 0 F "<<mode<<' '<<unrestricted<<' '<<actorCount<<' '<<(actorsSpan.data()==as.data()?1:2)<<' '<<hid(currentHouse)<<' '<<quiet<<' '<<unsigned(rule)<<' '<<std::bit_cast<std::uint64_t>(delay)<<' '<<changed<<' '<<phase<<' '<<registryCount<<' '<<unsigned(sorted)<<' '<<(registry.data()==primary.data()?1:2)<<' '<<cb<<' '<<ci<<' '<<aid(fallback);
 std::cout<<' '<<scratch.value<<' '<<unsigned(scratch.tag);for(auto p:scratch.padding)std::cout<<' '<<unsigned(p);
 for(auto& h:houses)std::cout<<' '<<h.index<<' '<<tid(h.type)<<' '<<unsigned(h.field)<<' '<<h.allies<<' '<<h.mask<<' '<<unsigned(h.f134)<<' '<<unsigned(h.f135)<<' '<<h.enemy<<' '<<h.count;
 for(auto& t:types)std::cout<<' '<<t.country<<' '<<t.parent<<' '<<unsigned(t.passive)<<' '<<t.comparison<<' '<<t.color;
 for(auto& h:houses)for(auto& e:h.scores)std::cout<<' '<<hid(e.house)<<' '<<e.value;
 for(auto& a:actors)std::cout<<' '<<a.kind<<' '<<a.id<<' '<<a.x<<' '<<a.y<<' '<<unsigned(a.flag76)<<' '<<a.country<<' '<<hid(a.owner)<<' '<<aid(a.target)<<' '<<unsigned(a.byte404)<<' '<<a.word310<<' '<<bool(a.service)<<' '<<aid(a.attached)<<' '<<a.weaponIndex<<' '<<a.permission;
 for(auto* entries:{&primary,&alternate})for(auto& e:*entries)std::cout<<' '<<e.key<<' '<<aid(e.object);
#ifdef RA2_DIPLOMACY_JOIN
 std::cout<<" D "<<unsigned(rule111D)<<' '<<bool(session)<<' '<<sessionResult;
 for(auto& h:houses)std::cout<<' '<<unsigned(h.f191);
 std::cout<<' '<<houseCount<<' '<<(housesSpan.data()==alternateHouses.data());
#endif
 std::cout<<'\n';
}
void guards(){
 bool caught=false;try{requireHouseMakeAllyService(std::function<void()>{});}catch(const std::invalid_argument&){caught=true;}require(caught);
 require(missionTextDuration(.6)==539);
#ifdef RA2_DIPLOMACY_JOIN
 static_assert(!std::is_move_constructible_v<HouseDiplomacy> && !std::is_copy_constructible_v<HouseDiplomacy>);
 int zero=0;std::uint8_t byte0=0;std::int16_t word0=0;const void* null=nullptr;std::span<const void*> slots;
 std::span<TargetRegistryEntry> entries;TargetRegistryEntry* cached=nullptr;std::array<int,9> table{};
 HouseAllianceWorld alliance{zero,zero,zero,slots,zero,slots};HouseThreatWorld threat{zero,zero,slots,{word0,word0},table,table};
 TargetReferenceWorld targets{zero,entries,byte0,cached,null};HouseMakeAllyWorld ally{alliance,threat,targets,zero,slots,null,zero};
 HouseMakeEnemyWorld enemy{threat,zero,null};HouseAllianceNotificationWorld notification{byte0,null,zero,zero,slots};
 int restored=0;ally.allianceNotification=[&]{restored|=1;};notification.makeAlly=[&](auto,auto,auto){restored|=2;};notification.makeEnemy=[&](auto,auto,auto){restored|=4;};
 {HouseDiplomacy scope(notification,ally,enemy,[]{return TargetReference{};});scope.notify();}
 ally.allianceNotification();notification.makeAlly(nullptr,nullptr,0);notification.makeEnemy(nullptr,nullptr,0);require(restored==7);
 caught=false;try{HouseDiplomacy scope(notification,ally,enemy,{});}catch(const std::invalid_argument&){caught=true;}require(caught);
 restored=0;ally.allianceNotification();notification.makeAlly(nullptr,nullptr,0);notification.makeEnemy(nullptr,nullptr,0);require(restored==7);
 caught=false;try{HouseDiplomacy scope(notification,ally,enemy,[]{return TargetReference{};});null=&zero;scope.notify();}catch(const std::invalid_argument&){caught=true;}null=nullptr;require(caught);
 restored=0;ally.allianceNotification();notification.makeAlly(nullptr,nullptr,0);notification.makeEnemy(nullptr,nullptr,0);require(restored==7);
#endif
 std::cout<<"House MakeAlly guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
