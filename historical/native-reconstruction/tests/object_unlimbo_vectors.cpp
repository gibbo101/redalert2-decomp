// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/ObjectUnlimbo.hpp"
#include "render/ObjectAlphaPlacement.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){
  std::uint8_t enabled=1,marked=0,redraw=1,limbo=1,active=1;int loading=1,mode=0;int identity;
  ObjectUnlimboType type;type.radial20a=1;
  ObjectUnlimboServices s{enabled,loading,mode};s.type84=[&]{return &type;};s.adjust6c=[](auto&,Coord p){return p;};s.setLocation19c=[](auto){};s.mark11c=[](int){return 1;};s.layer74=[]{return -1;};
  bool refused=false;try{objectUnlimbo({&identity,marked,redraw,limbo,active},{},0,s);}catch(const std::invalid_argument&){refused=true;}
  if(!refused)throw std::runtime_error("Radial path accepted");
  ObjectAlphaPlacementServices a{loading};refused=false;try{placeObjectAlpha(&identity,a);}catch(const std::invalid_argument&){refused=true;}
  if(!refused)throw std::runtime_error("Unbound alpha producer accepted");
  refused=false;try{alphaCanvasDimension({},2);}catch(const std::invalid_argument&){refused=true;}
  if(!refused)throw std::runtime_error("Missing canvas accepted");
  std::cout<<"Object Unlimbo guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::array<std::int64_t,25> f{};std::istringstream in(line);for(auto& n:f)in>>n;if(!in)throw std::invalid_argument("Invalid Object Unlimbo input");
  std::uint8_t enabled=f[0],limbo=f[1],marked=f[2],redraw=f[3],active=f[4];std::int32_t loading=int(f[5]),mode=int(f[14]);
  int identity,cell;ObjectUnlimboType first,late;first.logic204=f[10];first.terrain281=f[11];
  Bytes image(8);auto dimensions=[&](int w,int h){for(int i=0;i<2;++i){image[2+i]=std::uint8_t(std::uint16_t(w)>>(8*i));image[4+i]=std::uint8_t(std::uint16_t(h)>>(8*i));}};dimensions(int(f[19]),int(f[20]));
  first.alphaAC=f[16]?image.data():nullptr;late.alphaAC=image.data();
  PixelPoint origin{int(f[23]),int(f[24])};AlphaAnimationRecord record;
  std::ostringstream trace;auto event=[&](int k,std::int64_t a=0,std::int64_t b=0,std::int64_t c=0,std::int64_t d=0,std::int64_t e=0){trace<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<e<<' ';};
  bool mutated=false;int types=0,kinds=0;
  auto mutate=[&](int at){if(mutated||f[18]!=at)return;mutated=true;event(18,at);
   if(at==1)loading=1;if(at==2)active=0;if(at==3){first.logic204=128;first.alphaAC=image.data();}
   if(at==4)origin={100,-100};
   if(at==5||at==6){origin={-123,77};dimensions(-7,11);loading=loading?0:1;}
  };
  auto type=[&]()->const ObjectUnlimboType*{++types;event(3,types);return types==1?(f[9]?&first:nullptr):&late;};
  ObjectUnlimboServices s{enabled,loading,mode};
  s.mapCell548000=[&](Coord p)->const void*{event(1,p.x,p.y,p.z);return &cell;};
  s.permission194=[&](const void* p,int a,int b,int c,int d){if(p!=&cell)throw std::runtime_error("Permission Cell identity differs");event(2,a,b,c,d);mutate(1);return int(f[6]);};
  s.type84=type;s.adjust6c=[&](const auto& t,Coord p){if(&t!=&first)throw std::runtime_error("Saved Type differs");event(4,p.x,p.y,p.z);return Coord{fillAdd(p.x,7),fillSub(p.y,9),fillAdd(p.z,3)};};
  s.setLocation19c=[&](Coord p){event(5,p.x,p.y,p.z);mutate(2);};
  s.mark11c=[&](int mode){event(6,mode);return std::uint32_t(f[7]);};s.layer74=[&]{event(7);return int(f[8]);};
  s.submit499a40=[&]{event(8);mutate(3);};s.kind2c=[&]{event(9,++kinds);return int(f[kinds==1?12:13]);};
  s.auxiliary10=[&]{event(10);return int(f[15]);};s.logic53e330=[&](auto zero){event(11,zero);};
  ObjectAlphaPlacementServices a{loading};
  a.coordinates48=[&](const void* p){if(p!=&identity)throw std::runtime_error("Coordinates identity differs");event(12);return Coord{int(f[21]),int(f[22]),31};};
  a.project6a29d0=[&](Coord p){event(13,p.x,p.y,p.z);mutate(4);return PixelPoint{int(f[21]),int(f[22])};};a.tacticalOrigin=[&]{return origin;};
  a.image84=[&](const void* p){if(p!=&identity)throw std::runtime_error("Image identity differs");type();return std::span<const std::uint8_t>(image);};
  a.allocate=[&](auto size)->AlphaAnimationRecord*{event(14,size);mutate(5);return f[17]?&record:nullptr;};
  a.construct=[&](auto& r,const void* p,int x,int y){if(&r!=&record||p!=&identity)throw std::runtime_error("Constructor identities differ");event(15,x,y);mutate(6);};
  a.register6a3020=[&](PixelRect r,auto flag){event(16,r.x,r.y,r.width,r.height,flag);};
  s.alphaPlacement=[&](const void* p){placeObjectAlpha(p,a);};s.store=[&](int off,auto value){event(17,off,value);};
  const bool result=objectUnlimbo({&identity,marked,redraw,limbo,active},{int(f[21]),int(f[22]),31},0xdeadbeef,s);
  std::cout<<trace.str()<<"F "<<result<<' '<<unsigned(limbo)<<' '<<unsigned(redraw)<<' '<<unsigned(marked)<<' '<<unsigned(active)<<' '<<loading<<' '<<types<<' '<<kinds<<' '<<mutated<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
