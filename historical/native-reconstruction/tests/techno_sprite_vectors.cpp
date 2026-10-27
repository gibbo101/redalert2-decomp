// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/TechnoSpriteDraw.hpp"
#include "sim/RevealArea.hpp"
#include <iostream>
#include <sstream>
#include <bit>
using namespace ra2;
void need(bool b){if(!b)throw std::runtime_error("Techno sprite fixture domain");}
void event(int a,int b=0,int c=0,int d=0){std::cout<<a<<' '<<b<<' '<<c<<' '<<d<<' ';}
int wrap(std::uint32_t v){return std::bit_cast<std::int32_t>(v);}
int main(int argc,char**){try{
 if(argc>1){int field=0;std::uint8_t byte=0;PixelPoint p{};PixelRect c{};BuildingSpriteRequest r{nullptr,0,p,c};drawTechnoSprite({field,byte,byte},r,{});r.image=&field;bool refused=false;try{drawTechnoSprite({field,byte,byte},r,{});}catch(const std::invalid_argument&){refused=true;}need(refused);std::cout<<"Techno sprite guards PASS\n";return 0;}
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);std::array<int,67> f{};for(auto& v:f){std::int64_t n;need(bool(in>>n)&&n>=INT32_MIN&&n<=INT32_MAX);v=int(n);}std::string extra;need(!(in>>extra));
  std::array<int,8> objects{};const auto ptr=[&](int id)->const void*{need(id>=0&&id<8);return id?&objects[id]:nullptr;};const auto id=[&](const void* p){if(!p)return 0;for(int i=1;i<8;++i)if(ptr(i)==p)return i;throw std::invalid_argument("Foreign sprite fixture identity");};
  std::uint8_t flag5bb=f[11],flag37c=f[30];int field1bc=f[3],kind=f[2],height=f[17],count=f[31],shadow=f[13],b48=f[12],currentConverter=f[23];
  std::array<const void*,2> converters{ptr(f[8]),ptr(f[8])};std::array<std::int16_t,2> terrain{std::int16_t(f[10]),std::bit_cast<std::int16_t>(std::uint16_t(f[10]+17))};
  PixelRect infantry{f[38],f[39],f[40],f[41]};PixelPoint point{f[53],f[54]};PixelRect clip{f[55],f[56],f[57],f[58]};
  bool mutated=false;int draws=0,objectCalls=0,heightCalls=0;
  const auto mutate=[&](int mode,PixelPoint* local=nullptr){if(mutated||f[59]!=mode)return;mutated=true;event(8,mode);
   if(mode==1){shadow=0;field1bc=1;}
   if(mode==2){kind=2;b48=128;}
   if(mode==3)converters[0]=nullptr;
   if(mode==4){need(local);*local={71,72};clip={99,98,97,96};count=-3;flag37c=255;shadow=0;b48=255;converters[0]=ptr(4);}
   if(mode==5){currentConverter=4;b48=255;}
   if(mode==6){shadow=0;flag37c=128;}
   if(mode==7)height=wrap(std::uint32_t(height)+104u);
   if(mode==8)terrain[0]=-32768;
  };
  TechnoSpriteServices s;const auto read=[](int subject,int off,int value){event(1,subject,off,value);};s.read=read;
  s.shadow7d88d5=[&]{read(8,0x7d88d5,shadow);return std::uint8_t(shadow);};
  s.mode64=[&](int a,int b){need(a==0&&b==0);event(3,0x64,0,f[1]);mutate(1);return f[1];};
  s.predicate1bc=[&]{event(3,0x1bc,0,f[4]);return std::uint8_t(f[4]);};s.predicate1c0=[&]{event(3,0x1c0,0,f[5]);return std::uint8_t(f[5]);};
  s.kind2c=[&]{event(3,0x2c,0,kind);return kind;};s.building1386=[&]{return std::uint8_t(f[6]);};
  s.coordinates48=[&]{event(3,0x48);mutate(3);return Coord{f[60],f[61],f[62]};};
  const auto cell=[&](int i){return TechnoSpriteCell{ptr(i+5),converters[i],terrain[i]};};
  s.cell548070=[&](std::uint32_t p){event(3,0x548070,wrap(p),0);return cell(0);};
  s.initialize4790f0=[&](TechnoSpriteCell c,std::array<int,6> args){need(args==std::array<int,6>{0,65536,0,1000,1000,1000});const int i=id(c.identity)-5;event(3,0x4790f0,i,f[9]);mutate(8);converters[i]=ptr(f[9]);};
  s.converterAd0608=[&]{read(8,0xad0608,4);return ptr(4);};
  s.converter1cc=[&]{event(3,0x1cc,0,f[7]);mutate(2);return ptr(f[7]);};
  s.height1b8=[&]{const int value=height;event(3,0x1b8,heightCalls++,value);mutate(7);return value;};s.project6a2970=[](int h){event(3,0x6a2970,h);return projectVisibilityHeight(h,.125);};
  s.depth2c0=[&]{event(3,0x2c0,0,f[18]);return f[18];};s.target1b0=[&]{event(3,0x1b0,0,f[16]);return bool(f[16]);};
  s.typeB48=[&]{event(3,0x80);return std::uint8_t(b48);};s.footBB0=[&]{return std::uint8_t(f[14]);};s.footBB1=[&]{return std::uint8_t(f[15]);};
  s.currentHouseA35db4=[&]{read(8,0xa35db4,1);return ptr(1);};
  s.ownerPredicate3d4=[&](const void* p){need(id(p)==1);event(3,0x3d4,1,f[19]);mutate(5);return std::uint8_t(f[19]);};
  s.objectC8=[&](int arg){need(arg==1);const int object=objectCalls++?2:1;event(3,0xc8,1,object);return ptr(object);};
  s.objectKind2c=[&](const void* p){const int object=id(p);need(object==1||object==2);const int k=f[object==1?20:21];event(3,0x2c,object,k);return k;};
  s.houseCC=[&](int arg){need(arg==1);event(3,0xcc,1,2);return ptr(2);};
  s.houseConverter=[&](const void* p){const int h=id(p);need(h==1||h==2);const int converter=h==1?currentConverter:f[22];read(9,h,converter);return ptr(converter);};
  s.cell1a4=[&]{event(3,0x1a4,0,1);return cell(1);};
  s.ownedHousePredicate4f52b0=[&]{event(3,0x4f52b0,2,f[24]);return std::uint8_t(f[24]);};s.predicateC0=[&]{event(3,0xc0,0,f[25]);return std::uint8_t(f[25]);};
  s.flags3d0=[&](int value){int result=wrap(std::uint32_t(value)^std::uint32_t(f[26]));event(3,0x3d0,value,result);return result;};
  s.brightness3f8=[&](int value){int result=buildingSpriteBrightness(std::uint32_t(f[27]),value);event(3,0x3f8,value,result);mutate(6);return result;};
  s.predicate32c=[&]{event(3,0x32c,0,f[28]);return std::uint8_t(f[28]);};s.status6d86f0=[&](int v){int result=wrap(std::uint32_t(v)+std::uint32_t(f[29]));event(3,0x6d86f0,v,result);return result;};
  s.image=[&](const void* p){need(p==ptr(1));return ShpBoundsView{p,[&]{read(4,6,count);return std::int16_t(count);},[&]{read(4,2,f[32]);read(4,4,f[33]);return PixelPoint{f[32],f[33]};},[&](std::uint32_t index,int field){need(index<32);read(5,int(index)*24+field*2,f[34+field]);return std::int16_t(f[34+field]);}};};
  s.emptyFrame=[&]{read(6,12,f[66]);read(6,0,f[63]);read(6,4,f[64]);read(6,8,f[65]);return PixelRect{f[63],f[64],f[65],f[66]};};
  s.infantryBoundsRead=[&](int off){const std::array<int,4> v{infantry.x,infantry.y,infantry.width,infantry.height};read(7,off,v.at(off/4));return v.at(off/4);};
  s.infantryBoundsStore=[&](int off,int value){event(2,7,off,value);if(off==0)infantry.x=value;else if(off==4)infantry.y=value;else if(off==8)infantry.width=value;else infantry.height=value;};
  s.surface83995c=[&]{read(8,0x83995c,1);return ptr(1);};
  s.draw49eea0=[&](const TechnoSpriteBlit& b){need(b.image==ptr(1)&&&b.clip==&clip&&&b.point!=&point&&id(b.surface)==1);const std::array<int,14> args{1,b.frame,101,102,b.flags,b.zero,b.zAdjust,b.gradient,b.brightness,b.tail[0],b.tail[1],b.tail[2],b.tail[3],id(b.converter)};for(int i=0;i<14;++i)event(4,i,args[i]);const std::array<int,6> v{b.point.x,b.point.y,clip.x,clip.y,clip.width,clip.height};for(int i=0;i<6;++i)event(7,i,v[i]);if(draws++==0)mutate(4,&b.point);};
  drawTechnoSprite({field1bc,flag5bb,flag37c},{f[0]?ptr(1):nullptr,f[42],point,clip,0,f[43],f[44],{f[45],f[46],f[47],f[48],f[49],f[50],f[51],f[52]}},s);
  std::cout<<"F ";for(int v:{point.x,point.y,clip.x,clip.y,clip.width,clip.height,infantry.x,infantry.y,infantry.width,infantry.height,draws,field1bc,int(flag5bb),int(flag37c),kind,height,count,shadow,b48,currentConverter,id(converters[0]),id(converters[1]),int(terrain[0]),int(terrain[1])})std::cout<<v<<' ';std::cout<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}}
