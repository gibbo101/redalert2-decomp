// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/HouseThreat.hpp"
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
 for(auto& v:offsets)v=take<int>(in);for(auto& v:shifts)v=take<int>(in);std::string extra;require(!(in>>extra));
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
 w.threat2A0=[&](const void* p){const int id=aid(p),result=actors[std::size_t(id-1)].strength;std::cout<<" V "<<id<<" 672 "<<result;mutate(id,672);return result;};
 w.kind2C=[&](const void* p){const int id=aid(p);auto& a=actors[std::size_t(id-1)];const auto result=a.kinds[std::min(a.kindCalls++,2)];std::cout<<" V "<<id<<" 44 "<<result;mutate(id,44);return result;};
 w.objectCell1A4=[&](const void* p){const int id=aid(p);std::cout<<" V "<<id<<" 420 "<<id;mutate(id,420);const auto& a=actors[std::size_t(id-1)];return HouseThreatCell{a.ox,a.oy};};
 int result=0;if(root==0)rebuildHouseThreatGrid(hp(current),w);else if(root==1)updateHouseThreatScore(hp(current),delta,hp(target),w);else result=projectHouseThreatCell({px,py});
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
 std::cout<<"House threat guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
