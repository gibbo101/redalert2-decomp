// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/HouseMapRefresh.hpp"
#include "render/UnitTypeVisibility.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
namespace {
void require(bool b){if(!b)throw std::invalid_argument("House map refresh fixture outside domain");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
std::uint8_t byte(std::istream& in){auto v=take<int>(in);require(v>=0&&v<=255);return std::uint8_t(v);}
struct House{int index=0;std::uint8_t f134=0,f135=0;std::uint32_t allies=0;};
struct Type{std::uint8_t f534=0,fADD=0;};
struct Actor{std::uint8_t f76=0,sight=0;const void* owner=nullptr;int type=1;std::array<int,3> kinds{};int range=0,x=0,y=0,z=0,calls=0;};
void run(std::istream& in){
 require(take<char>(in)=='M');const int addition=take<int>(in);auto skip=byte(in);const int argument=take<int>(in);int count=take<int>(in),mode=take<int>(in),current=take<int>(in);auto rule=byte(in);const int mutation=take<int>(in);
 require(addition>=0&&addition<=1&&count>=-2&&count<=8&&current>=0&&current<=3&&mutation>=0&&mutation<=7);
 std::array<House,3> houses;std::array<Type,3> types;std::array<Actor,3> actors;std::array<const void*,8> slots{},alternate{};
 const auto hp=[&](int id)->const void*{require(id>=0&&id<=3);return id?&houses[std::size_t(id-1)]:nullptr;};
 const auto ap=[&](int id)->const void*{require(id>=0&&id<=3);return id?&actors[std::size_t(id-1)]:nullptr;};
 const auto hid=[&](const void* p){for(int i=0;i<=3;++i)if(hp(i)==p)return i;throw std::invalid_argument("Foreign refresh House");};
 const auto aid=[&](const void* p){for(int i=1;i<=3;++i)if(ap(i)==p)return i;throw std::invalid_argument("Foreign refresh actor");};
 for(auto& p:slots)p=ap(take<int>(in));for(std::size_t i=0;i<8;++i)alternate[i]=ap(3-int(i%3));
 for(auto& h:houses){h.index=take<int>(in);h.f134=byte(in);h.f135=byte(in);h.allies=take<std::uint32_t>(in);}
 for(auto& t:types){t.f534=byte(in);t.fADD=byte(in);}
 for(auto& a:actors){a.f76=byte(in);a.sight=byte(in);a.owner=hp(take<int>(in));require(a.owner);a.type=take<int>(in);require(a.type>=1&&a.type<=3);for(auto& k:a.kinds)k=take<int>(in);a.range=take<int>(in);a.x=take<int>(in);a.y=take<int>(in);a.z=take<int>(in);}
 std::string extra;require(!(in>>extra));std::span<const void*> registry=slots;const void* currentHouse=hp(current);HouseMapRefreshWorld w{count,registry,HouseMapRefreshOwner{std::function<const void*()>([&]{return currentHouse;})},rule};
 bool changed=false;const auto mutate=[&](int id,int service){
  if(changed)return;const bool entered=(mutation==1||mutation==2||mutation==6)?service==44:mutation==3?(service==1048||service==1052):mutation==4?service==128:mutation==5?service==0:mutation==7?(service==940||service==944):false;
  if(!entered)return;changed=true;auto& a=actors[std::size_t(id-1)];
  if(mutation==1){a.f76=1;a.sight=0;}
  if(mutation==2){registry=alternate;count=0;mode=1;currentHouse=hp(3);a.owner=hp(3);}
  if(mutation==3){a.x=-2147483647-1;a.y=2147483647;a.z=-7;a.range=2147483647;a.type=2;currentHouse=hp(2);rule=0;}
  if(mutation==4){auto& t=types[std::size_t(a.type-1)];a.type=3;t.fADD^=255;t.f534^=1;mode=1;currentHouse=a.owner;}
  if(mutation==5){a.x=17;a.y=-19;a.z=23;a.owner=hp(1);rule=255;count=-2;}
  if(mutation==6){a.owner=hp(2);houses[1].allies^=0xffffffffu;houses[1].f134=0;houses[1].f135=1;rule=1;mode=0;currentHouse=hp(1);}
  if(mutation==7){auto& next=actors[std::size_t(id%3)];next.f76=255;next.owner=hp(3);registry=alternate;count=4;}
 };
 w.actor=[&](const void* p){const auto& a=actors[std::size_t(aid(p)-1)];return HouseMapRefreshActor{a.f76,a.sight,HouseMapRefreshOwner{std::function<const void*()>([&a]{return a.owner;})},a.range,a.x,a.y,a.z};};
 w.localHouse=[&](const void* p){const int id=hid(p);std::cout<<" H "<<id;if(mode)return unitOwnerTypeVisible(mode,0,0,p==currentHouse);require(id);const auto& h=houses[std::size_t(id-1)];return unitOwnerTypeVisible(mode,h.f134,h.f135,p==currentHouse);};
 w.allied=[&](const void* p,const void* q){const int id=hid(p),other=hid(q);std::cout<<" A "<<id<<' '<<other;if(!q)return unitOwnerAlliedToCurrent(false,false,0,0,0);require(id);const auto& h=houses[std::size_t(id-1)];return unitOwnerAlliedToCurrent(true,p==q,h.index,houses[std::size_t(other-1)].index,h.allies);};
 w.kind2C=[&](const void* p){const int id=aid(p);auto& a=actors[std::size_t(id-1)];const int result=a.kinds[std::size_t(std::min(a.calls++,2))];std::cout<<" K "<<id<<' '<<result;mutate(id,44);return result;};
 w.type80=[&](const void* p){const int id=aid(p),type=actors[std::size_t(id-1)].type;std::cout<<" T "<<id<<' '<<type;mutate(id,128);const auto& t=types[std::size_t(type-1)];return HouseMapRefreshType{t.f534,t.fADD};};
 int lastActor=0;w.sight=[&](const void* p,int slot,int a,int b,int c,const void* h){const int id=aid(p);lastActor=id;std::cout<<" S "<<id<<' '<<slot<<' '<<a<<' '<<b<<' '<<c<<' '<<hid(h);mutate(id,slot);};
 w.image=[&](const void* p,int slot){const int id=aid(p);std::cout<<" I "<<id<<' '<<slot;mutate(id,slot);};
 w.postSight=[&](std::array<int,3> point,int inner,int outer,std::uint32_t disabled){require(lastActor);std::cout<<" P "<<lastActor<<' '<<point[0]<<' '<<point[1]<<' '<<point[2]<<' '<<inner<<' '<<outer<<' '<<disabled;mutate(lastActor,0);};
 refreshHouseMapSight(addition,skip,argument,w);
 std::cout<<" R 0 F "<<count<<' '<<mode<<' '<<hid(currentHouse)<<' '<<unsigned(rule)<<' '<<(registry.data()==alternate.data());
 for(const auto& h:houses)std::cout<<' '<<h.index<<' '<<unsigned(h.f134)<<' '<<unsigned(h.f135)<<' '<<h.allies;
 for(const auto& t:types)std::cout<<' '<<unsigned(t.f534)<<' '<<unsigned(t.fADD);
 for(const auto& a:actors)std::cout<<' '<<unsigned(a.f76)<<' '<<unsigned(a.sight)<<' '<<hid(a.owner)<<' '<<a.type<<' '<<a.kinds[0]<<' '<<a.kinds[1]<<' '<<a.kinds[2]<<' '<<a.range<<' '<<a.x<<' '<<a.y<<' '<<a.z;
 std::cout<<'\n';
}
void guards(){
 int count=-1;std::uint8_t rule=0;const void* current=nullptr;std::span<const void*> slots;HouseMapRefreshWorld w{count,slots,current,rule};refreshHouseMapSight(true,0,0,w);
 std::array<const void*,1> one{nullptr};slots=one;count=1;refreshHouseMapSight(false,255,0,w);
 int scalar=0;std::uint8_t flag=1,sight=1;const void* owner=&scalar;one[0]=&scalar;w.actor=[&](const void*){return HouseMapRefreshActor{flag,sight,owner,scalar,scalar,scalar,scalar};};refreshHouseMapSight(true,0,0,w);
 flag=0;int calls=0;w.kind2C=[&](const void*){++calls;return 6;};refreshHouseMapSight(false,255,0,w);require(calls==1);
 bool caught=false;try{refreshHouseMapSight(false,0,0,w);}catch(const std::invalid_argument&){caught=true;}require(caught);
 one[0]=nullptr;count=2;caught=false;try{refreshHouseMapSight(false,0,0,w);}catch(const std::invalid_argument&){caught=true;}require(caught);
 std::cout<<"House map refresh guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
