// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/ActorRadarColor.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void need(bool v){if(!v)throw std::invalid_argument("Radar actor fixture domain");}
void run(std::istream& in){
 char op;int kind,flag,owner,current,alternate,mutation;std::array<std::int32_t,3> indices;std::array<std::uint32_t,3> masks;std::uint32_t argument;
 need(bool(in>>op>>kind>>flag>>owner>>current>>alternate)&&op=='A');for(auto& v:indices)need(bool(in>>v));for(auto& v:masks)need(bool(in>>v));need(bool(in>>argument>>mutation));std::string tail;need(!(in>>tail));
 need((kind==0||kind==1)&&flag>=0&&flag<=255&&owner>=0&&owner<3&&current>=-1&&current<3&&alternate>=-1&&alternate<3&&mutation>=0&&mutation<=15);
 std::array<int,3> identities{0,1,2};int actor=0;const std::uint8_t raw=std::uint8_t(flag);const void* ownerPointer=&identities[owner];const void* currentPointer=current<0?nullptr:&identities[current];const void* alternatePointer=alternate<0?nullptr:&identities[alternate];bool changed=false;
 auto id=[&](const void* p){if(!p)return -1;for(int i=0;i<3;++i)if(p==&identities[i])return i;throw std::invalid_argument("Foreign radar House");};
 RadarColorWorld world{currentPointer,[&](const void* p)->RadarColorActor{need(p==&actor);return {kind?RadarColorActorKind::building:RadarColorActorKind::infantry,raw,[&]{return ownerPointer;},[&]{return alternatePointer;}};},[&](const void* p)->RadarColorHouse{const auto i=id(p);need(i>=0);return {indices[i],masks[i]};},[&](const void* p,const void* a,const void* b,bool result){need(p==&actor);std::cout<<"H "<<id(a)<<' '<<id(b)<<' '<<result<<' ';if(changed||!mutation)return;changed=true;if(mutation&1)ownerPointer=&identities[2];if(mutation&2)currentPointer=&identities[2];if(mutation&4)alternatePointer=&identities[2];if(mutation&8){indices[2]=-1;masks[0]^=0xffffffff;}}};
 std::cout<<"A "<<unsigned(actorRadarColorFlag(&actor,world))<<' ';for(int i=0;i<2;++i){const auto result=actorRadarColorHouse(&actor,argument,world);std::cout<<"C "<<id(result)<<' ';}
 std::cout<<"R "<<id(ownerPointer)<<' '<<id(currentPointer)<<' '<<id(alternatePointer)<<' '<<changed;for(auto v:indices)std::cout<<' '<<v;for(auto v:masks)std::cout<<' '<<v;std::cout<<'\n';
}
void guards(){
 int actor=0;std::uint8_t raw=255;const void* current=nullptr;int views=0;
 RadarColorWorld w{current,[&](const void*)->RadarColorActor{++views;return {RadarColorActorKind::building,raw,{},{}};},{},{}};
 need(actorRadarColorFlag(&actor,w)==255&&actorRadarColorHouse(&actor,0xffffffff,w)==nullptr);
 RefreshSurface* surface=nullptr;SurfaceMarkBuckets* buckets=nullptr;SurfaceMarkBitmap* bitmap=nullptr;std::span<const SurfaceMarkScheme*> schemes;
 SurfaceMarkServices marks{surface,buckets,bitmap,schemes,{},{},[](auto){return std::uint8_t(7);},[&](auto,auto){return &actor;},{},{},{}};ActorRadarColorProbes probes;auto before=views;
 {ActorRadarColorBinding bind(marks,w,probes);need(views==before);need(marks.actorC0(&actor)==255&&marks.actorCC(&actor,1)==nullptr);}
 need(marks.actorC0(&actor)==7&&marks.actorCC(&actor,1)==&actor);
 bool propagated=false;w.actor=[](auto)->RadarColorActor{throw std::runtime_error("actor fault");};try{ActorRadarColorBinding bind(marks,w,probes);marks.actorC0(&actor);}catch(const std::runtime_error&){propagated=true;}need(propagated&&marks.actorC0(&actor)==7);
 need(!radarColorAllied(nullptr,nullptr,w));std::cout<<"actor radar color guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
