// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/HouseAllianceNotification.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
struct H {std::uint8_t a,b,c,d;};
int main(int argc,char** argv){try{
 if(argc>1){
  if(std::string(argv[1])!="--guards")return 2;
  std::uint8_t enabled=1;const void* session=nullptr;std::int32_t mode=0,count=1;
  std::span<const void*> slots;HouseAllianceNotificationWorld w{enabled,session,mode,count,slots};
  bool refused=false;try{notifyHouseAlliances(w);}catch(const std::invalid_argument&){refused=true;}
  if(!refused)return 3;enabled=0;notifyHouseAlliances(w);
  session=&count;refused=false;try{notifyHouseAlliances(w);}catch(const std::invalid_argument&){refused=true;}
  if(!refused)return 4;session=nullptr;enabled=1;H actor{0,0,0,37};
  std::array<const void*,1> one{&actor};slots=one;
  w.house=[&](const void* p){if(p!=&actor)throw std::invalid_argument("foreign House");return HouseAllianceNotificationFields{actor.a,actor.b,actor.c,actor.d};};
  refused=false;try{notifyHouseAlliances(w);}catch(const std::invalid_argument&){refused=true;}
  if(!refused||actor.d!=1)return 5; // Earlier store is retained on child refusal.
  actor.b=1;actor.d=37;notifyHouseAlliances(w);if(actor.d!=37)return 6;
  actor.b=0;actor.a=255;notifyHouseAlliances(w);if(actor.d!=37)return 7;
  std::cout<<"guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);char tag;std::array<std::int64_t,30> v{};if(!(in>>tag)||tag!='N')return 2;
  for(auto& x:v)if(!(in>>x))return 2;std::string tail;if(in>>tail)return 2;
  std::uint8_t enabled=v[0];const void* session=v[1]?&v:nullptr;std::uint32_t result=v[2];
  std::int32_t mode=v[3],count=v[4];const int mutation=v[5];std::array<H,4> houses;
  for(int i=0;i<4;++i)houses[i]={std::uint8_t(v[14+4*i]),std::uint8_t(v[15+4*i]),std::uint8_t(v[16+4*i]),std::uint8_t(v[17+4*i])};
  auto ptr=[&](int id)->const void*{if(id==0)return nullptr;if(id<1||id>4)throw std::invalid_argument("foreign House");return &houses[id-1];};
  auto id=[&](const void* p){for(int i=0;i<4;++i)if(p==&houses[i])return i+1;throw std::invalid_argument("foreign House");};
  std::array<const void*,8> backing,alternate;
  for(int i=0;i<8;++i){backing[i]=ptr(v[6+i]);alternate[i]=ptr(4-i%4);}
  std::span<const void*> slots=backing;bool changed=false;
  auto mutate=[&](bool query){
   if(changed||!mutation||(query!=(mutation<=2)))return;changed=true;
   if(mutation==1){enabled=0;session=nullptr;mode=1;}
   if(mutation==2){enabled=1;count=3;slots=alternate;}
   if(mutation==3){count=1;slots=alternate;mode=1;}
   if(mutation==4){count=6;slots=alternate;houses[1].b=1;houses[2].a=255;}
   if(mutation==5){mode=mode?0:1;houses[0].b=255;houses[1].c=255;}
   if(mutation==6){count=0;houses[0].d=239;}
  };
  HouseAllianceNotificationWorld w{enabled,session,mode,count,slots};
  w.house=[&](const void* p){auto& h=houses[id(p)-1];return HouseAllianceNotificationFields{h.a,h.b,h.c,h.d};};
  w.session4=[&](const void* p){if(p!=&v)throw std::invalid_argument("foreign session");std::cout<<"Q "<<result<<' ';mutate(true);return result;};
  auto service=[&](char kind,const void* a,const void* b,std::uint8_t announce){std::cout<<kind<<' '<<id(a)<<' '<<id(b)<<' '<<unsigned(announce)<<' ';mutate(false);};
  w.makeAlly=[&](auto a,auto b,auto c){service('A',a,b,c);};w.makeEnemy=[&](auto a,auto b,auto c){service('E',a,b,c);};
  w.stored191=[&](auto p,auto value){std::cout<<"W "<<id(p)<<' '<<unsigned(value)<<' ';};
  notifyHouseAlliances(w);std::cout<<"S "<<unsigned(enabled)<<' '<<bool(session)<<' '<<mode<<' '<<count<<' '<<(slots.data()==alternate.data())<<' ';
  for(const auto& h:houses)std::cout<<unsigned(h.a)<<' '<<unsigned(h.b)<<' '<<unsigned(h.c)<<' '<<unsigned(h.d)<<' ';
  std::cout<<'\n';
 }
 return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
