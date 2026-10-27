// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/HouseMakeEnemy.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
struct H {std::int32_t index,enemy,count;const void* type;std::uint8_t a,b,c;std::uint32_t mask,allies;std::array<HouseThreatScore,2> scores;std::span<HouseThreatScore> entries=scores;};
struct T {std::uint8_t passive;std::int32_t color;};
int main(int argc,char** argv){try{
 if(argc>1){if(std::string(argv[1])!="--guards")return 2;
  std::int32_t mode=1,zero=0;std::span<const void*> slots;std::array<std::int32_t,9> table{};std::int16_t word=0;const void* current=nullptr;
  HouseThreatWorld threat{mode,zero,slots,{word,word},table,table};HouseMakeEnemyWorld w{threat,zero,current};
  bool refused=false;try{makeHouseEnemy(nullptr,nullptr,0,w);}catch(const std::invalid_argument&){refused=true;}if(!refused)return 3;
  bool numeric=false;try{missionTextDuration(INFINITY);}catch(const std::invalid_argument&){numeric=true;}if(!numeric)return 4;
  std::cout<<"guards PASS\n";return 0;}
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);char tag;std::array<std::string,53> words;if(!(in>>tag)||tag!='M')return 2;for(auto& x:words)if(!(in>>x))return 2;std::string tail;if(in>>tail)return 2;
  const auto val=[&](int i){return std::stoll(words[i]);};
  int currentID=val(0),targetID=val(1);auto announce=std::uint8_t(val(2));std::int32_t mode=val(3),unrestricted=val(4);int localID=val(5);double delay=std::bit_cast<double>(std::stoull(words[6]));int mutation=val(7);
  std::array<H,3> houses;std::array<T,3> types;
  auto hp=[&](int id)->const void*{if(!id)return nullptr;if(id<1||id>3)throw std::invalid_argument("foreign House");return &houses[id-1];};
  auto hid=[&](const void* p){for(int i=0;i<=3;++i)if(hp(i)==p)return i;throw std::invalid_argument("foreign House");};
  auto tp=[&](int id)->const void*{if(id<1||id>3)throw std::invalid_argument("foreign type");return &types[id-1];};
  auto tid=[&](const void* p){for(int i=1;i<=3;++i)if(tp(i)==p)return i;throw std::invalid_argument("foreign type");};
  auto house=[&](const void* p)->H&{int i=hid(p);if(!i)throw std::invalid_argument("null House");return houses[i-1];};
  for(int i=0;i<3;++i){int j=8+9*i;auto& h=houses[i];h.index=val(j);h.type=tp(val(j+1));h.a=val(j+2);h.allies=val(j+3);h.mask=val(j+4);h.b=val(j+5);h.c=val(j+6);h.enemy=val(j+7);h.count=val(j+8);h.entries=h.scores;}
  for(int i=0;i<3;++i)types[i]={std::uint8_t(val(35+2*i)),std::int32_t(val(36+2*i))};
  for(int i=0;i<3;++i)for(int j=0;j<2;++j)houses[i].scores[j]={hp(val(41+4*i+2*j)),std::int32_t(val(42+4*i+2*j))};
  const void* currentHouse=hp(localID);const auto self=hp(currentID),target=hp(targetID);bool changed=false;
  auto event=[&](int service,int a=0,std::int64_t b=0){auto& h=house(self);std::cout<<"E "<<service<<' '<<a<<' '<<b<<' '<<h.allies<<' '<<h.mask<<' '<<(target?house(target).allies:0)<<' '<<(target?house(target).mask:0)<<' ';};
  auto mutate=[&](int service){
   const int wanted[]={0,1,2,2,4,5,6,8,6,2,1,8,6};
   if(changed||!mutation||service!=wanted[mutation])return;changed=true;auto& s=house(self);auto& o=target?house(target):s;
   if(mutation==1){o.index=-33;s.allies=0xffffffff;}
   if(mutation==2){o.allies=0xffffffff;s.index=-1;unrestricted=1;}
   if(mutation==3){mode=1;unrestricted=0;s.b=255;o.allies=0xffffffff;}
   if(mutation==4){mode=0;s.b=0;s.c=0;o.b=0;o.c=255;}
   if(mutation==5){delay=.6;types[tid(s.type)-1].color=-7;}
   if(mutation==6){mode=0;s.b=0;s.c=0;o.b=0;o.c=255;}
   if(mutation==7){mode=0;s.b=0;s.c=0;o.b=0;o.c=0;}
   if(mutation==8){currentHouse=hp(3);mode=1;}
   if(mutation==9){o.index=31;o.allies=0;}
   if(mutation==10){s.count=2;s.scores[0]={target,INT32_MAX};s.scores[1]={target,7};}
   if(mutation==11){mode=1;currentHouse=target;}
   if(mutation==12){mode=0;s.b=255;}
  };
  std::int32_t count=0;std::span<const void*> slots;std::int16_t zero=0;std::array<std::int32_t,9> table{};
  HouseThreatWorld threat{mode,count,slots,{zero,zero},table,table};
  threat.house=[&](const void* p){auto& h=house(p);return HouseThreatHouse{p,h.index,h.a,h.b,h.c,h.allies,h.enemy,h.count,h.entries,{}};};
  HouseMakeEnemyWorld w{threat,unrestricted,currentHouse};
  w.house=[&](const void* p){auto& h=house(p);return HouseMakeEnemyFields{h.index,h.type,h.b,h.c,h.allies,h.mask};};
  w.passive1A6=[&](const void* p){return types[tid(p)-1].passive;};w.colorC0=[&](const void* p){return types[tid(p)-1].color;};w.delay1128=[&](){return delay;};
  w.mapSight=[&](bool add){int k=add?9:1;event(k);mutate(k);};w.rebuildGrid=[&](const void* p){event(2,hid(p));mutate(2);};
  w.localize=[&]()->const void*{event(4);mutate(4);return &types;};
  w.format=[&](auto text,auto left,auto right)->const void*{if(text!=&types)throw std::invalid_argument("foreign text");event(5,hid(left),hid(right));mutate(5);return &houses;};
  w.display=[&](auto text,auto color,auto duration){if(text!=&houses)throw std::invalid_argument("foreign text");event(6,color,duration);mutate(6);};
  w.redraw0=[&](){event(8);mutate(8);};w.speech=[&](auto key){event(7,key);mutate(7);};
  w.stored=[&](auto p,auto off,auto value){std::cout<<"W "<<hid(p)<<' '<<off<<' '<<value<<' ';};
  makeHouseEnemy(self,target,announce,w);
  std::cout<<"S "<<mode<<' '<<unrestricted<<' '<<hid(currentHouse)<<' '<<std::bit_cast<std::uint64_t>(delay)<<' '<<changed<<' ';
  for(auto& h:houses)std::cout<<h.index<<' '<<tid(h.type)<<' '<<unsigned(h.a)<<' '<<h.allies<<' '<<h.mask<<' '<<unsigned(h.b)<<' '<<unsigned(h.c)<<' '<<h.enemy<<' '<<h.count<<' ';
  for(auto& t:types)std::cout<<unsigned(t.passive)<<' '<<t.color<<' ';
  for(auto& h:houses)for(auto& e:h.scores)std::cout<<hid(e.house)<<' '<<e.value<<' ';std::cout<<'\n';
 }
 return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
