// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/FrameDepthRefresh.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){
  std::uint32_t offset=0,begin=0,end=16,extent=16;int stride=2,lock=0,width=2,bpp=2;std::uint32_t buffer=0;
  std::array<std::uint16_t,8> pixels{};FrameDepthView v{offset,begin,end,extent,stride,{{},pixels}};FrameDepthServices s;
  auto refuses=[&](PixelRect r){try{refreshFrameAlpha(v,r,s);}catch(const std::invalid_argument&){return;}throw std::runtime_error("Missing alpha guard");};
  refuses({});s.lock5c=[](int,int){return std::optional<std::uint32_t>(0);};refuses({});
  bool unlocked=false;s.lock5c=[](int,int){return std::optional<std::uint32_t>{};};s.unlock60=[&]{unlocked=true;};refuses({});if(!unlocked)throw std::runtime_error("Null lock must still unlock");
  s.lock5c=[&](int x,int y){return lockSurfacePixels({width,lock,bpp,buffer,{},pixels,true},x,y);};s.unlock60=[&]{unlockSurfacePixels({width,lock,bpp,buffer,{},pixels,true});};
  refreshFrameAlpha(v,{0,0,1,1},s);if(pixels[0]!=0||lock)throw std::runtime_error("Aligned one-word omission changed");
  refreshFrameAlpha(v,{1,0,1,1},s);if(pixels[1]!=127||pixels[0])throw std::runtime_error("Prefixed one-word write missing");
  refuses({0,0,-1,1});refuses({0,0,1048577,1});refuses({0,0,100,1});
  refreshFrameAlpha(v,{0,0,-1,0},s); // Nonpositive height returns after lock/unlock.
  std::cout<<"Frame alpha guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream input(line);std::array<int,16> f;for(auto& n:f)input>>n;if(!input)throw std::invalid_argument("Invalid alpha vector");
  const int mode=f[0];std::array<int,2> width{f[1],fillAdd(f[1],2)},bpp{f[2],f[2]},locks{f[4],f[5]};
  std::array<std::uint32_t,2> offsets{std::uint32_t(f[3]),std::uint32_t(f[3]+4)};int surface=0;
  std::uint32_t delta=f[6],begin=f[7],end=f[8],extent=f[9];int stride=f[10];
  Bytes pixels(2048);std::vector<std::uint16_t> words(1024);for(unsigned i=0;i<pixels.size();++i)pixels[i]=std::uint8_t(i*29+0x34);
  for(unsigned i=0;i<words.size();++i)words[i]=std::uint16_t(pixels[2*i]|std::uint16_t(pixels[2*i+1])<<8);
  std::ostringstream trace;auto event=[&](int k,std::int64_t a=0,std::int64_t b=0,std::int64_t c=0,std::int64_t d=0){trace<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' ';};bool mutated=false;
  auto mutate=[&](int point){
   if(mutated||!mode||point!=((mode==6||mode==7)?2:1))return;mutated=true;event(10,mode);
   if(mode==1||mode==6)surface=1;if(mode==2||mode==7)delta=2;if(mode==3)stride=0;
   if(mode==4){end=std::uint32_t(f[7]+160);extent=160;stride=5;}
   if(mode==5){offsets[0]=std::uint32_t(f[3]+4);width[0]=12;}
  };
  const auto view=[&](int i){return SurfacePixelView{width[i],locks[i],bpp[i],offsets[i],f[15]?std::span<std::uint8_t>{}:std::span<std::uint8_t>(pixels),f[15]?std::span<std::uint16_t>(words):std::span<std::uint16_t>{},true};};
  FrameDepthServices s;
  s.lock5c=[&](int x,int y){const int i=surface;event(1,i);event(2,i,x,y);const auto v=view(i);
   return lockSurfacePixels(v,x,y,{},[&,i](int n){event(3,i,n);},[&,i]{event(4,i,bpp[i]);return bpp[i];},[&,i,v]{event(5,i);return surfacePixelPitch(v,[&,i]{event(6,i,width[i]);mutate(1);return width[i];});});};
  s.unlock60=[&]{const int i=surface;event(1,i);event(7,i);mutate(2);unlockSurfacePixels(view(i),[&,i](int n){event(3,i,n);});};
  refreshFrameAlpha({delta,begin,end,extent,stride,{f[15]?std::span<std::uint8_t>{}:std::span<std::uint8_t>(pixels),f[15]?std::span<std::uint16_t>(words):std::span<std::uint16_t>{}}},
   {f[11],f[12],f[13],f[14]},s,[&](auto at,auto n,auto v){event(9,at,n,v);},[&](int field,std::uint32_t value){event(8,field,std::bit_cast<std::int32_t>(value));});
  if(f[15])for(unsigned i=0;i<pixels.size();++i)pixels[i]=std::uint8_t(words[i/2]>>(8*(i&1)));
  std::cout<<trace.str()<<"F "<<locks[0]<<' '<<locks[1]<<' '<<surface<<' '<<std::bit_cast<std::int32_t>(delta)<<' '<<begin<<' '<<end<<' '<<extent<<' '<<stride<<' '<<width[0]<<' '<<width[1]<<' '<<offsets[0]<<' '<<offsets[1]<<' '<<assetSha256(Data(pixels))<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
