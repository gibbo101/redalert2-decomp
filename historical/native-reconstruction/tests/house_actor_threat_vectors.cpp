// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/HouseActorThreat.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace ra2;
namespace {
void require(bool value){if(!value)throw std::invalid_argument("House threat fixture outside domain");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
std::uint8_t byte(std::istream& in){const auto v=take<int>(in);require(v>=0&&v<=255);return std::uint8_t(v);}
std::int16_t word(std::istream& in){const auto v=take<int>(in);require(v>=-32768&&v<=32767);return std::int16_t(v);}
struct House{int index=0;std::uint8_t field=0,f134=0,f135=0;std::uint32_t allies=0;int enemy=0;std::vector<int> grid=std::vector<int>(0x4205,0x77777777);};
struct Actor{std::uint8_t f76=0,f7D=0;int strength=0;std::array<int,3> kinds{};const void* owner=nullptr;std::int16_t x=0,y=0,ox=0,oy=0;int kindCalls=0;};
void run(std::istream& in){
 require(take<char>(in)=='T');const int root=take<int>(in),current=take<int>(in),target=take<int>(in),delta=take<int>(in);int count=take<int>(in),registryCount=take<int>(in),mode=take<int>(in);const int mutation=take<int>(in);auto ix=word(in),iy=word(in),px=word(in),py=word(in);
 require(root>=0&&root<=2&&current>=1&&current<=4&&target>=0&&target<=4&&count>=-2&&count<=8&&registryCount>=-2&&registryCount<=8&&mutation>=0&&mutation<=6);
 std::array<House,4> houses;std::array<Actor,3> actors;std::array<const void*,8> slots{},alternate{};std::array<HouseThreatScore,8> scores;std::array<int,9> offsets{},shifts{};
 const auto hp=[&](int id)->const void*{require(id>=0&&id<=4);return id?&houses[std::size_t(id-1)]:nullptr;};
 const auto ap=[&](int id)->const void*{require(id>=1&&id<=3);return &actors[std::size_t(id-1)];};
 const auto hid=[&](const void* p){for(int i=0;i<=4;++i)if(hp(i)==p)return i;throw std::invalid_argument("Foreign threat House");};
 const auto aid=[&](const void* p){for(int i=1;i<=3;++i)if(ap(i)==p)return i;throw std::invalid_argument("Foreign threat actor");};
 for(auto& s:slots)s=ap(take<int>(in));for(std::size_t i=0;i<8;++i)alternate[i]=ap(3-int(i%3));
 for(auto& h:houses){h.index=take<int>(in);h.field=byte(in);h.f134=byte(in);h.f135=byte(in);h.allies=take<std::uint32_t>(in);h.enemy=take<int>(in);}
 for(auto& s:scores){s.house=hp(take<int>(in));s.value=take<int>(in);}
 for(auto& a:actors){a.f76=byte(in);a.f7D=byte(in);a.strength=take<int>(in);for(auto& k:a.kinds)k=take<int>(in);a.owner=hp(take<int>(in));a.x=word(in);a.y=word(in);a.ox=word(in);a.oy=word(in);}
 for(auto& v:offsets)v=take<int>(in);for(auto& v:shifts)v=take<int>(in);const auto rule=take<std::int32_t>(in);std::array<std::int32_t,3> types{};
 for(auto& v:types)v=take<std::int32_t>(in);
 struct Threat{int type=1,present=1;std::int32_t field=0;};std::array<Threat,3> threats;
 for(auto& t:threats){t.type=take<int>(in);t.present=take<int>(in);t.field=take<std::int32_t>(in);require(t.type>=1&&t.type<=3&&(t.present==0||t.present==1));}
 require(root==0&&(mutation==0||mutation==3));for(auto& a:actors)require((a.kinds[0]==6||a.kinds[0]==15)&&a.kinds[1]==a.kinds[0]&&a.kinds[2]==a.kinds[0]);
 std::string extra;require(!(in>>extra));
 std::span<const void*> registry=slots;std::span<HouseThreatScore> entries=scores;HouseThreatWorld w{mode,registryCount,registry,{ix,iy},offsets,shifts};
 w.house=[&](const void* p){auto& h=houses.at(std::size_t(hid(p)-1));return HouseThreatHouse{p,h.index,h.field,h.f134,h.f135,h.allies,h.enemy,count,entries,h.grid};};
 w.actor=[&](const void* p){const auto& a=actors.at(std::size_t(aid(p)-1));return HouseThreatActor{a.f76,a.f7D,a.owner,{a.x,a.y}};};
 bool changed=false;const auto mutate=[&](int id,int service){
  if(changed)return;
  const bool entered=(mutation==1||mutation==4||mutation==6)?service==672:(mutation==2||mutation==5)?service==44:mutation==3?service==420:false;
  if(!entered)return;changed=true;auto& a=actors[std::size_t(id-1)];auto& h=houses[std::size_t(current-1)];
  if(mutation==1){a.f76=1;a.f7D=0;a.owner=hp(current);}
  if(mutation==2){registry=alternate;registryCount=0;mode=1;h.f134=0;h.f135=255;h.allies^=0xffffffffu;}
  if(mutation==3){mode=1;h.f134=255;h.allies=0xffffffffu;a.owner=hp(current);a.x=ix;a.y=iy;}
  if(mutation==4){const auto cell=projectHouseThreatCell({a.x,a.y});for(std::size_t i=0;i<9;++i){const auto k=houseThreatAdd(cell,offsets[i]);require(k>=0&&k<0x4204);h.grid[std::size_t(k)]=i%2?0x7fffffff:-1;}}
  if(mutation==5){ix=a.x;iy=a.y;}
  if(mutation==6)a.strength=7;
 };
 const auto enter=[&](const void* p,int address){std::cout<<" E "<<aid(p)<<' '<<address;};
 w.threat2A0=[](const void*)->int{throw std::logic_error("Unjoined actor threat");};
 w.kind2C=[&](const void* p){const auto& a=actors[std::size_t(aid(p)-1)];enter(p,a.kinds[0]==6?0x453c40:0x509800);return a.kinds[0];};
 HouseActorThreatServices joined{rule};
 joined.field564=[&](const void* p)->const std::int32_t&{return threats[std::size_t(aid(p)-1)].field;};
 joined.actor=[&](const void* p){
  TechnoThreatServices s;enter(p,0x6d3e50);
  s.type80=[&,p]()->const void*{const auto id=std::size_t(aid(p)-1);enter(p,0x6c12c0);enter(p,actors[id].kinds[0]==6?0x453c60:0x506950);const auto& t=threats[id];return t.present?&types[std::size_t(t.type-1)]:nullptr;};
  s.kind2C=[&,p]{return w.kind2C(p);};
  s.value598=[&](const void* p)->const std::int32_t&{for(auto& v:types)if(p==&v)return v;throw std::invalid_argument("Foreign threat type");};
  return s;
 };
 w.objectCell1A4=[&](const void* p){const int id=aid(p);std::cout<<" V "<<id<<" 420 "<<id;mutate(id,420);const auto& a=actors[std::size_t(id-1)];return HouseThreatCell{a.ox,a.oy};};
 // The stock getter is a pure field load; original execution counts audit it.
 int result=0;{HouseActorThreat binding(w,joined);binding.rebuild(hp(current));}
 std::cout<<" R "<<result<<" S "<<count<<' '<<registryCount<<' '<<mode<<' '<<ix<<' '<<iy<<' '<<(registry.data()==alternate.data());
 for(const auto& h:houses)std::cout<<' '<<h.index<<' '<<unsigned(h.field)<<' '<<unsigned(h.f134)<<' '<<unsigned(h.f135)<<' '<<h.allies<<' '<<h.enemy;
 for(const auto& s:scores)std::cout<<' '<<hid(s.house)<<' '<<s.value;
 for(const auto& a:actors)std::cout<<' '<<unsigned(a.f76)<<' '<<unsigned(a.f7D)<<' '<<a.strength<<' '<<a.kinds[0]<<' '<<a.kinds[1]<<' '<<a.kinds[2]<<' '<<hid(a.owner)<<' '<<a.x<<' '<<a.y<<' '<<a.ox<<' '<<a.oy;
 const auto& grid=houses[std::size_t(current-1)].grid;const int base=root==0?0:0x77777777;std::size_t nonzero=0;for(std::size_t i=0;i<0x4204;++i)if(grid[i]!=base)++nonzero;
 std::cout<<" G "<<base<<' '<<nonzero;for(std::size_t i=0;i<0x4204;++i)if(grid[i]!=base)std::cout<<' '<<i<<' '<<grid[i];require(grid.back()==0x77777777);std::cout<<'\n';
}
void guards(){
 std::int16_t x=-7,y=-3;require(projectHouseThreatCell({x,y})==130);require(houseThreatAdd(0x7fffffff,1)==(-2147483647-1));
 bool caught=false;try{houseThreatScoreAt({},0);}catch(const std::invalid_argument&){caught=true;}require(caught);
 int mode=0,count=0;std::span<const void*> registry;std::array<int,9> tables{};
 HouseThreatWorld world{mode,count,registry,{x,y},tables,tables};
 world.threat2A0=[](const void*){return 91;};int field=0,rule=1,calls=0;
 HouseActorThreatServices services{rule};
 services.field564=[&](const void*)->const int&{return field;};
 services.actor=[&](const void*){++calls;TechnoThreatServices fields;fields.type80=[]()->const void*{return nullptr;};return fields;};
 {HouseActorThreat join(world,services);require(calls==0&&world.threat2A0(nullptr)==0);
  {HouseActorThreat nested(world,services);require(world.threat2A0(nullptr)==0);}
  require(world.threat2A0(nullptr)==0);}
 require(world.threat2A0(nullptr)==91);
 try{HouseActorThreat join(world,services);throw std::runtime_error("unwind");}catch(const std::runtime_error&){}
 require(world.threat2A0(nullptr)==91);
 services.actor={};caught=false;try{HouseActorThreat join(world,services);}catch(const std::invalid_argument&){caught=true;}
 require(caught&&world.threat2A0(nullptr)==91);
 std::cout<<"House actor threat guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
