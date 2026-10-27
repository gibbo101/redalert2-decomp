// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/AlphaAnimation.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace ra2;
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){
  AlphaCombinationTable table;AlphaAnimationServices s;bool refused=false;
  try{drawAlphaAnimations(false,{}, {},table,s);}catch(const std::invalid_argument&){refused=true;}
  if(!refused)throw std::runtime_error("Unbound registry accepted");
  s.count=[]{return 1;};s.backing=[]{return std::span<AlphaAnimationRecord*>{};};refused=false;
  try{drawAlphaAnimations(false,{}, {},table,s);}catch(const std::invalid_argument&){refused=true;}
  if(!refused)throw std::runtime_error("Missing physical slot accepted");
  s.count=[]{return 0;};drawAlphaAnimations(false,{}, {},table,s);
  initializeAlphaCombination(table);if(table.values[127*256+127]!=127||table.values[65535]!=255)throw std::runtime_error("Table domain");
  // Nonfaulting domain refusals: missing cached point image, bad raw payload,
  // ambiguous backing and an original lookup that would leave the64KiB table.
  Bytes image(33,0);image[6]=1;image[12]=image[14]=1;image[28]=32;image[32]=255;
  AlphaAnimationRecord rec{nullptr,{0,0,1,1},{},0};std::array<AlphaAnimationRecord*,1> slots{&rec};
  s.count=[]{return 1;};s.backing=[&]{return std::span<AlphaAnimationRecord*>(slots);};
  s.origin=s.viewport=[]{return PixelPoint{};};std::uint32_t offset=0,begin=0,end=2,extent=2;int stride=1;
  std::array<std::uint16_t,1> words{65535};Bytes bytes(2);std::array<std::uint8_t,1800> mask{};s.tileMask=mask;
  s.alpha=[&]{return FrameDepthView{offset,begin,end,extent,stride,{{},words}};};s.address411230=[](PixelPoint){return 0u;};
  const auto rejects=[&]{try{drawAlphaAnimations(true,{}, {0,0,1,1},table,s);}catch(const std::invalid_argument&){return;}throw std::runtime_error("Unsafe alpha profile accepted");};
  rejects();rec.image38=image;rejects();words[0]=127;image[28]=0;rejects();image[28]=32;
  s.alpha=[&]{return FrameDepthView{offset,begin,end,extent,stride,{bytes,words}};};rejects();
  std::cout<<"Alpha animation guards PASS\n";return 0;
 }
 if(argc!=2)throw std::invalid_argument("Private original tile mask required");
 std::ifstream file(argv[1],std::ios::binary);Bytes mask{std::istreambuf_iterator<char>(file),{}};
 if(mask.size()!=1800)throw std::invalid_argument("Original tile mask length differs");
 std::string line;while(std::getline(std::cin,line)){
  std::array<int,27> f{};std::istringstream in(line);for(auto& n:f)in>>n;if(!in)throw std::invalid_argument("Invalid alpha vector");
  const std::array<int,8> values{0,1,63,126,127,128,254,255};std::array<Bytes,2> images;
  for(int variant=0;variant<2;++variant){auto& image=images[variant];image.resize(32+f[15]*f[16]);
   const auto word=[&](int at,int value){image[at]=std::uint8_t(value);image[at+1]=std::uint8_t(unsigned(value)>>8);};
   word(6,f[4]);for(int k=0;k<4;++k)word(8+2*k,f[13+k]);image[28]=32;
   for(int i=0;i<f[15]*f[16];++i)image[32+i]=std::uint8_t(values[(i+3*variant)%8]);}
  Bytes pixels(8192);std::vector<std::uint16_t> words(4096);
  for(int i=0;i<4096;++i){words[i]=std::uint16_t(values[i%8]);pixels[2*i]=std::uint8_t(words[i]);pixels[2*i+1]=std::uint8_t(words[i]>>8);}
  std::array<int,3> associated{0,1,2};std::array<AlphaAnimationRecord,3> records;
  for(int i=0;i<3;++i){records[i]={&associated[i],{f[5]+4*i,f[6],f[7],f[8]},i||f[2]?std::span<const std::uint8_t>(images[i%2]):std::span<const std::uint8_t>{},std::uint8_t(i?i==2:f[3])};}
  std::array<AlphaAnimationRecord*,3> slots{&records[0],&records[1],&records[2]},slots2{&records[1],&records[2],&records[0]};bool second=false,mutated=false;
  int count=f[25],lock=0,stride=f[24],bpp=2;std::uint32_t offset=f[23],begin=0,end=8192,extent=end,buffer=0;
  PixelPoint origin{f[9],f[10]},viewport{f[11],f[12]},screen{f[21],f[22]};PixelRect clip{f[17],f[18],f[19],f[20]};
  std::ostringstream trace;auto event=[&](int k,std::int64_t a=0,std::int64_t b=0,std::int64_t c=0,std::int64_t d=0){trace<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' ';};
  auto mutate=[&](int where){if(mutated||!f[1]||((where==2)!=(f[1]==6)))return;mutated=true;event(9,f[1]);
   if(f[1]==1)count=3;if(f[1]==2)count=1;if(f[1]==3)second=true;if(f[1]==4)slots[0]=&records[2];
   if(f[1]==5||f[1]==6){origin={17,-23};viewport={1,2};clip={8,9,24,16};}};
  const auto backing=[&]{return SurfacePixelBacking{f[26]?std::span<std::uint8_t>{}:std::span<std::uint8_t>(pixels),f[26]?std::span<std::uint16_t>(words):std::span<std::uint16_t>{}};};
  const auto view=[&]{return FrameDepthView{offset,begin,end,extent,stride,backing()};};
  const auto surface=[&]{auto b=backing();return SurfacePixelView{stride,lock,bpp,buffer,b.storage,b.words,true};};
  FrameDepthServices address;address.lock5c=[&](int x,int y){return lockSurfacePixels(surface(),x,y,{},[&](int v){event(4,v);});};address.unlock60=[&]{unlockSurfacePixels(surface(),[&](int v){event(4,v);});};
  AlphaAnimationServices s;s.count=[&]{return count;};s.backing=[&]{return std::span<AlphaAnimationRecord*>(second?slots2:slots);};
  s.typeImage84=[&](const void* obj){event(1,*static_cast<const int*>(obj));mutate(1);return std::span<const std::uint8_t>(images[0]);};
  s.cacheStore=[&](auto& r){event(2,&r-records.data(),r.image38.data()==images[0].data()?0:1);};
  s.origin=[&]{return origin;};s.viewport=[&]{return viewport;};s.alpha=view;s.tileMask=mask;
  s.address411230=[&](PixelPoint p){event(3,p.x,p.y);mutate(2);return framePlaneAddress(view(),p,address);};
  AlphaCombinationTable table;initializeAlphaCombination(table);table.initialized=128;
  if(f[0]==2)initializeAlphaCombination(table,[&](auto i,auto v){event(6,i,v);});
  else drawAlphaAnimations(f[0]==1,screen,clip,table,s,[&](auto at,auto n,auto value){event(5,at,n,value);});
  if(f[26])for(int i=0;i<8192;++i)pixels[i]=std::uint8_t(words[i/2]>>(8*(i&1)));
  std::cout<<trace.str()<<"F "<<count<<' '<<second<<' '<<mutated<<' '<<lock<<' '<<clip.x<<' '<<clip.y<<' '<<clip.width<<' '<<clip.height<<' '<<origin.x<<' '<<origin.y<<' '<<viewport.x<<' '<<viewport.y<<' ';
  for(auto& r:records)std::cout<<(r.image38.empty()?-1:r.image38.data()==images[0].data()?0:1)<<' ';
  std::cout<<assetSha256(Data(pixels))<<' '<<assetSha256(Data(Bytes(table.values.begin(),table.values.end())))<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
