// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/CellVisibilityDraw.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
Bytes synthetic(const std::array<int,24>& f,int variant){
 Bytes b(392+f[15]*f[16]);auto word=[&](int at,int n){b.at(at)=std::uint8_t(n);b.at(at+1)=std::uint8_t(unsigned(n)>>8);};word(6,16);
 for(int i=0;i<16;++i){for(int j=0;j<4;++j)word(8+24*i+2*j,f[13+j]);word(28+24*i,392);}
 const std::array<int,8> source{0,1,63,126,127,128,254,255};for(std::size_t i=392;i<b.size();++i)b[i]=std::uint8_t(source[(i-392+3*variant)%8]);return b;
}
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){
  CellVisibilityState cell;CellVisibilityDrawServices s;bool refused=false;
  try{drawCellVisibility(cell,{},{},s);}catch(const std::invalid_argument&){refused=true;}
  if(!refused)throw std::runtime_error("Missing Cell draw service guard");
  VisibilityRasterCache c;VisibilityRasterServices r;refused=false;
  try{drawVisibilityRaster(false,c,{},{},0,r);}catch(const std::invalid_argument&){refused=true;}
  if(!refused||c.shroudInitialized!=1)throw std::runtime_error("Lazy flag must precede loader refusal");
  std::array<int,24> f{};f[15]=f[16]=1;auto image=synthetic(f,0);c.shroud=c.shroudFog=image;
  r.scenarioFlags=[]{return 0u;};r.alpha=[]()->FrameDepthView{throw std::invalid_argument("Unbound plane");};
  auto rejects=[&]{try{drawVisibilityRaster(false,c,{},{0,0,2,2},0,r);}catch(const std::invalid_argument&){return;}throw std::runtime_error("Missing visibility backing guard");};
  rejects();
  std::uint32_t offset=0,begin=0,end=16,extent=16;int stride=2;std::array<std::uint16_t,8> pixels{};
  r.alpha=[&]{return FrameDepthView{offset,begin,end,extent,stride,{{},pixels}};};rejects();
  r.viewportY=[]{return 0;};r.address411230=[](PixelPoint){return 16u;};rejects();
  r.address411230=[](PixelPoint){return 0u;};image.resize(392);c.shroud=c.shroudFog=image;rejects();
  c.shroud=c.shroudFog={};rejects();
  std::cout<<"Cell visibility draw guards PASS\n";return 0;
 }
 std::array<Bytes,2> owned;
 if(argc==2){for(int i=0;i<2;++i){auto d=readFile(std::filesystem::path(argv[1])/(i?"FOG.SHP":"SHROUD.SHP"));owned[i]=Bytes(d.ptr(),d.ptr()+d.size);}}
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);std::array<int,24> f;for(auto& n:f)in>>n;if(!in)throw std::invalid_argument("Invalid visibility vector");
  auto images=f[22]?owned:std::array<Bytes,2>{synthetic(f,0),synthetic(f,1)};
  Bytes pixels(8192);std::vector<std::uint16_t> words(4096);const std::array<int,7> dest{0,1,63,126,127,128,65535};
  for(std::size_t i=0;i<words.size();++i){words[i]=std::uint16_t(dest[i%7]);pixels[2*i]=std::uint8_t(words[i]);pixels[2*i+1]=std::uint8_t(words[i]>>8);}
  CellVisibilityState cell;cell.point={3,5};cell.primary120=0xab;cell.secondary121=0xcd;
  std::uint32_t scenario=f[1];std::uint8_t house=f[2];std::uint32_t offset=f[17],begin=0,end=8192,extent=end,buffer=0;int stride=f[18],lock=0,bpp=2;
  PixelPoint point{f[7],f[8]};PixelRect clip{f[9],f[10],f[11],f[12]};
  VisibilityRasterCache cache;cache.shroudInitialized=cache.fogInitialized=std::uint8_t(f[21]);cache.shroud=images[0];cache.shroudFog=cache.fog=images[1];
  std::ostringstream trace;auto event=[&](int k,std::int64_t a=0,std::int64_t b=0,std::int64_t c=0,std::int64_t d=0){trace<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' ';};bool mutated=false;
  auto mutate=[&](int where){if(mutated||f[5]!=where)return;mutated=true;event(9,where);scenario^=0x1000;house=std::uint8_t(f[2]^1);cell.point={-7,13};};
  const auto backing=[&]{return SurfacePixelBacking{f[23]?std::span<std::uint8_t>{}:std::span<std::uint8_t>(pixels),f[23]?std::span<std::uint16_t>(words):std::span<std::uint16_t>{}};};
  const auto view=[&]{return FrameDepthView{offset,begin,end,extent,stride,backing()};};
  const auto surface=[&]{auto b=backing();return SurfacePixelView{stride,lock,bpp,buffer,b.storage,b.words,true};};
  VisibilityRasterServices r;r.scenarioFlags=[&]{return scenario;};r.viewportY=[&]{return f[19];};r.alpha=view;r.transparent79dad0=f[20];
  r.load5956c0=[&](std::string_view name){const int i=name=="FOG.SHP";event(3,i,cache.shroudInitialized,cache.fogInitialized);mutate(3);return std::span<const std::uint8_t>(images[i]);};
  FrameDepthServices address;address.lock5c=[&](int x,int y){return lockSurfacePixels(surface(),x,y,{},[&](int v){event(6,v);});};address.unlock60=[&]{unlockSurfacePixels(surface(),[&](int v){event(6,v);});};
  r.address411230=[&](PixelPoint p){event(4,p.x,p.y);mutate(4);return framePlaneAddress(view(),p,address);};
  auto stores=[&](auto at,auto n,auto v){event(5,at,n,v);};
  const auto draw=[&](bool fog,const PixelPoint& p,const PixelRect& c,int frame){
   if(&p!=&point||&c!=&clip)throw std::runtime_error("Child identity differs");event(1,fog,frame);if(!fog)mutate(2);
   drawVisibilityRaster(fog,cache,p,c,frame,r,stores);
  };
  if(f[0])draw(f[0]==2,point,clip,f[6]);
  else{
   CellVisibilityDrawServices s;s.mask6a8d40=[&](const TerrainCellPoint& p,bool mode){event(2,mode,p.x,p.y);if(!mode)mutate(1);return f[3+mode];};
   s.scenarioFlags=[&]{return scenario;};s.house13d=[&]{return house;};
   s.shroud474260=[&](const auto& p,const auto& c,int frame){event(7,0x120,cell.primary120);draw(false,p,c,frame);};
   s.fog474510=[&](const auto& p,const auto& c,int frame){event(7,0x121,cell.secondary121);draw(true,p,c,frame);};
   drawCellVisibility(cell,point,clip,s);
   // The secondary store occurs even when fog is skipped. Move its trace to
   // the point following the secondary mask query, before any fog child.
   auto text=trace.str();const auto marker=std::string("7 289 ")+std::to_string(cell.secondary121)+" 0 0 ";
   if(text.find(marker)==std::string::npos)trace<<marker;
  }
  if(f[23])for(std::size_t i=0;i<pixels.size();++i)pixels[i]=std::uint8_t(words[i/2]>>(8*(i&1)));
  std::cout<<trace.str()<<"F "<<int(cell.primary120)<<' '<<int(cell.secondary121)<<' '<<cell.point.x<<' '<<cell.point.y<<' '<<scenario<<' '<<int(house)<<' '<<int(cache.shroudInitialized)<<' '<<int(cache.fogInitialized)<<' '<<lock<<' '<<assetSha256(Data(pixels))<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
