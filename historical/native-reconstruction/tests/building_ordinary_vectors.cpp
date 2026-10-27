// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingOrdinaryDraw.hpp"
#include "sim/RevealArea.hpp"
#include <bit>
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::runtime_error("Building ordinary vector domain");}
void event(int k,int a=0,int b=0,int c=0){std::cout<<k<<' '<<a<<' '<<b<<' '<<c<<' ';}
int word(std::uint32_t n){return std::bit_cast<std::int32_t>(n);}
int main(int argc,char**){try{
 if(argc>1){PixelPoint p{};PixelRect r{};bool refused=false;try{drawBuildingOrdinary(p,r,{});}catch(const std::invalid_argument&){refused=true;}need(refused);
  BuildingOrdinaryServices s;s.cell1a0=[]{return 0u;};s.image68=[]{return nullptr;};drawBuildingOrdinary(p,r,s);
  s.image68=[]{return reinterpret_cast<const void*>(1);};refused=false;try{drawBuildingOrdinary(p,r,s);}catch(const std::invalid_argument&){refused=true;}need(refused);
  need(buildingDrawCell({-257,257,0})==0x0001ffff);std::cout<<"Building ordinary guards PASS\n";return 0;}
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);std::array<std::int64_t,39> f{};for(auto& v:f){need(bool(in>>v));need(v>=INT32_MIN&&v<=INT32_MAX);}
  std::array<std::uint64_t,4> fp{};for(auto& v:fp)need(bool(in>>v));std::string extra;need(!(in>>extra));
  std::array<int,8> identities{};const auto ptr=[&](int id)->const void*{need(id>=0&&id<=7);return id?&identities[id]:nullptr;};
  const auto id=[&](const void* p){if(!p)return 0;for(int i=1;i<=7;++i)if(p==ptr(i))return i;throw std::runtime_error("Foreign SHP");};
  BuildingOrdinaryTypeState types[2];BuildingImageState images[2];BuildingTypeBoundsState bounds[2];
  for(int i=0;i<2;++i){auto& t=types[i];t.flag1385=f[6];t.adjust11d4=word(std::uint32_t(f[7])+i*100u);t.offset11e4={word(std::uint32_t(f[8])+i*20u),word(std::uint32_t(f[9])-i*30u)};t.offset11fc=std::bit_cast<std::int16_t>(std::uint16_t(f[10]+i*3));images[i].count137c=word(std::uint32_t(f[11])+i);
   auto image=[&](int v){return ptr(v&&i?v%7+1:v);};t.image11a0=image(f[12]);t.image11a8=image(f[13]);t.image11b0=image(f[14]);t.image11b8=image(f[15]);bounds[i].auxiliary11cc=image(f[16]);}
  int type=0,stage=f[5],z=f[29],cellHeight=f[30],count=f[25],b44=f[18],b1a=f[19];
  double threshold=std::bit_cast<double>(fp[2]);PixelPoint point{int(f[33]),int(f[34])};PixelRect clip{int(f[35]),int(f[36]),int(f[37]),int(f[38])};
  std::array<std::uint8_t,6> animations{};animations.fill(128);bool mutated=false;int imageCalls=0,missionCalls=0,widthCalls=0,frameCalls=0,drawCalls=0;
  const auto mutate=[&](int child){int mode=f[0];if(mutated||!mode||mode!=child)return;mutated=true;event(8,mode);type=1;
   if(mode==1)stage=0;if(mode==2)stage=1;if(mode==3){b44=0;b1a=255;}if(mode==4){count=-3;stage=2;}
   if(mode==5){cellHeight=-32768;z=728;}if(mode==6)z=729;
   if(mode==7){point={71,72};clip={21,22,23,24};stage=2;}
   if(mode==8){images[type].count137c=INT32_MAX;threshold=std::bit_cast<double>(std::uint64_t(0x7ff8000000000000));}
  };
  BuildingOrdinaryServices s;s.read=[](int a,int b,int c){event(1,a,b,c);};s.pointerRead=[&](int off,const void* p){event(2,off,id(p));};
  s.type=[&]{return BuildingOrdinaryType{types[type],images[type],bounds[type]};};s.stage42c=[&]{return stage;};
  s.cell1a0=[&]{event(3,1);return buildingDrawCell({int(f[31]),int(f[32]),z});};
  s.image68=[&]{int i=imageCalls++,which=f[i?4:3];event(3,2,i,which);mutate(1);return ptr(which);};
  s.kind2c=[&]{event(3,3,0,f[2]);return int(f[2]);};
  s.mission16c=[&]{event(3,4,missionCalls,f[1]);if(missionCalls++==1)mutate(2);return int(f[1]);};
  s.animation454=[&](int i)->std::uint8_t*{const int which=i%3==1?-1:i%6;event(5,i,which);return which<0?nullptr:&animations[which];};s.animationStore=[](int i,std::uint8_t v){event(6,i,v);};
  s.partner636e20=[&](int arg)->const void*{event(3,5,arg,f[17]);return f[17]?&stage:nullptr;};
  s.partnerFlag80=[&](const void*,int off){event(3,6,off);mutate(3);const int v=off==0xb44?b44:b1a;event(1,3,off,v);return std::uint8_t(v);};
  s.timerPredicate=[&](int address){event(3,7,address);mutate(9);const int bit=address==0x496a90?0:address==0x496ab0?1:address==0x496b30?2:3;return std::uint8_t((f[20]&(1<<bit))?128:0);};
  s.timerFraction496c70=[&]{event(3,8);return std::bit_cast<double>(fp[0]);};s.healthRatio5d4540=[&]{event(3,9);mutate(8);return std::bit_cast<double>(fp[1]);};s.threshold1368=[&]{return threshold;};
  s.foundationHeight458940=[&]{event(3,10,0,f[22]);return int(f[22]);};
  s.foundationWidth458930=[&]{const int call=widthCalls++;const int v=f[call?23:21];event(3,11,call,v);return v;};
  s.global85029c=[&]{event(1,4,0x85029c,f[24]);return int(f[24]);};
  s.frame43be20=[&]{const int call=frameCalls++;const int value=f[26+std::min(call,2)];event(3,12,call,value);if(call==0)mutate(4);return value;};
  s.imageCount=[&](const void*){return std::int16_t(count);};
  s.cellLight548070=[&](std::uint32_t cell){event(3,13,word(cell));mutate(5);return std::int16_t(cellHeight);};
  s.height1b8=[&]{event(3,14);mutate(6);return z;};s.projectHeight6a2970=[&](int value){return projectVisibilityHeight(value,std::bit_cast<double>(fp[3]));};
  s.draw6d1510=[&](const BuildingSpriteRequest& r){need(&r.point==&point&&&r.clip==&clip);const std::array<int,15> args{id(r.image),r.frame,101,102,r.zero,r.flags,r.adjust,r.tail[0],r.tail[1],r.tail[2],r.tail[3],r.tail[4],r.tail[5],r.tail[6],r.tail[7]};for(int i=0;i<15;++i)event(4,i,args[i]);
   const std::array<int,6> values{point.x,point.y,clip.x,clip.y,clip.width,clip.height};for(int i=0;i<6;++i)event(7,i,values[i]);if(drawCalls++==0)mutate(7);};
  drawBuildingOrdinary(point,clip,s);
  std::cout<<"F "<<type<<' '<<stage<<' '<<z<<' '<<count<<' '<<point.x<<' '<<point.y<<' '<<clip.x<<' '<<clip.y<<' '<<clip.width<<' '<<clip.height<<' ';for(auto v:animations)std::cout<<unsigned(v)<<' ';std::cout<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}}
