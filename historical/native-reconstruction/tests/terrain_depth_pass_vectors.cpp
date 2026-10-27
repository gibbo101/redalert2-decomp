// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/TerrainDepthPass.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){
  int stride=96;std::uint32_t offset=0,begin=0,end=18432,extent=end;
  std::vector<std::uint16_t> words(end/2);FrameDepthView v{offset,begin,end,extent,stride,{{},words}};
  TerrainDepthServices s;drawTerrainDepth(v,{},{},0,2,false,s);
  auto refuses=[&]{try{drawTerrainDepth(v,{},{0,0,96,96},0,2,true,s);}catch(const std::invalid_argument&){return;}throw std::runtime_error("Missing terrain guard");};refuses();
  bool unlocked=false;FrameDepthServices a;a.lock5c=[](int,int){return std::optional<std::uint32_t>{};};a.unlock60=[&]{unlocked=true;};
  try{(void)framePlaneAddress(v,{},a);throw std::runtime_error("Missing address null refusal");}catch(const std::invalid_argument&){}
  if(!unlocked)throw std::runtime_error("Address null must unlock");
  a.lock5c=[](int,int){return std::optional<std::uint32_t>(18432);};
  if(framePlaneAddress(v,{},a)!=0)throw std::runtime_error("Exact end must single wrap");
  a.lock5c=[](int,int){return std::optional<std::uint32_t>(18432*3);};
  if(framePlaneAddress(v,{},a)!=18432*2)throw std::runtime_error("Address must not use modulo");
  std::cout<<"Terrain depth guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);std::array<int,15> f;for(auto& n:f)in>>n;if(!in)throw std::invalid_argument("Invalid terrain vector");
  constexpr int N=18432;std::array<Bytes,3> backing{Bytes(N),Bytes(N),Bytes(N)};
  for(auto& b:backing)for(int i=0;i<N;++i)b[i]=std::uint8_t(i*29+0x34);
  std::array<int,3> locks{};int refs=f[13];const int width=96,bpp=f[8],two=2;const std::uint32_t buffer=0,offset=f[6],zero=0,end=N,extent=N;int stride=96;
  std::ostringstream trace;auto e=[&](auto... v){((trace<<v<<' '),...);};
  e('C',f[0],f[1],f[2],f[3],f[4],f[5],f[11],f[12],1,0,0,1,0,0);
  auto surface=[&](int i){return SurfacePixelView{width,locks[i],i==0?bpp:two,buffer,backing[i],{},true};};
  auto lock=[&](int i,int x,int y){return lockSurfacePixels(surface(i),x,y,{},[&,i](int n){e('K',i,n);},[&,i]{if(i==0)e('B',bpp);return i==0?bpp:2;},[&,i]{if(i==0)e('P',192);return surfacePixelPitch(surface(i));});};
  auto unlock=[&](int i){unlockSurfacePixels(surface(i),[&,i](int n){e('K',i,n);});};
  FrameDepthView depth{offset,zero,end,extent,stride,{backing[1],{}}},alpha{zero,zero,end,extent,stride,{backing[2],{}}};
  TerrainDepthServices s;s.acquire41e3e0=[&]{e('A',53);retainTerrainDepthAlpha(refs);e('T',refs);};
  s.release41e510=[&]{e('R');releaseTerrainDepthAlpha(refs);e('T',refs);};
  s.bytes70=[&]{e('B',bpp);return bpp;};s.header9c=[&]{e('H');return !f[10];};s.pitch74=[&]{e('P',192);return 192u;};
  s.lock5c=[&](int x,int y){e('L',x,y);return lock(0,x,y);};s.unlock60=[&]{e('U');unlock(0);};
  auto address=[&](int i,PixelPoint p){e(i==1?'Z':'Q',p.x,p.y);FrameDepthServices s;
   s.lock5c=[&](int x,int y){return lock(i,x,y);};s.unlock60=[&]{unlock(i);};return framePlaneAddress(i==1?depth:alpha,p,s);};
  s.depth776340=[&](PixelPoint p){return address(1,p);};s.alpha411230=[&](PixelPoint p){return address(2,p);};
  drawTerrainDepth(depth,{f[0],f[1]},{f[2],f[3],f[4],f[5]},f[7],2,!f[9],s,[&](auto p,auto n,auto v){e('W',p,n,v);});
  std::cout<<trace.str()<<"F "<<locks[0]<<' '<<locks[1]<<' '<<locks[2]<<' '<<refs;
  for(const auto& b:backing)std::cout<<' '<<assetSha256(Data(b));std::cout<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
