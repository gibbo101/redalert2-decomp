// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/RadarProjection.hpp"
#include "render/SurfacePixel.hpp"
#include <iostream>
#include <sstream>
#include <vector>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Radar projection domain");}
void run(std::istream& in){
 char op;int w,h,rx,ry,rw,rh,existing,colorsPresent,bitmapPresent,update,seed,format;
 need(bool(in>>op>>w>>h>>rx>>ry>>rw>>rh>>existing>>colorsPresent>>bitmapPresent>>update>>seed>>format)&&op=='P'&&w>0&&w<=32&&h>0&&h<=32&&rx>=0&&ry>=0&&rw>=0&&rh>=0&&rx+rw<=w&&ry+rh<=h&&existing>=0&&existing<=1&&colorsPresent>=0&&colorsPresent<=1&&bitmapPresent>=0&&bitmapPresent<=1&&update>=0&&update<=255&&seed>=0&&seed<=255&&format>=0&&format<=1);std::string tail;need(!(in>>tail));
 RefreshSurfaceVirtuals table;table.width7C=[](auto& s){std::cout<<"W "<<s.width<<' ';return s.width;};table.height80=[](auto& s){std::cout<<"H "<<s.height<<' ';return s.height;};RefreshSurface surface{&table,7,5};auto* second=existing?&surface:nullptr;
 std::vector<std::uint8_t> rgb(3072,0xa5),pixels(32768,0xa5),bits(4096,0xa5);
 std::span<std::uint8_t> colors=colorsPresent?std::span<std::uint8_t>(rgb):std::span<std::uint8_t>{};std::span<std::uint8_t> bitmap=bitmapPresent?std::span<std::uint8_t>(bits):std::span<std::uint8_t>{};
 for(int i=0;i<w*h*3;++i)rgb[i]=std::uint8_t(i*29+seed);
 int cw=w,ch=h,lock=0,bpp=2;std::uint32_t offset=0;float scale=0.5f;std::array<std::int32_t,6> shifts=format?std::array<std::int32_t,6>{10,3,0,3,5,3}:std::array<std::int32_t,6>{11,3,0,3,5,2};
 const auto buffer=[](char k,auto at,auto n,auto v){std::cout<<k<<' '<<at<<' '<<n<<' '<<v<<' ';};
 RadarProjectionServices services;
 services.allocate=[&](auto n){std::cout<<"A "<<n<<' ';if(colors.empty())return std::span<std::uint8_t>(rgb).first(n);return std::span<std::uint8_t>(bits).first(n);};
 services.bufferStore=buffer;services.mapStore=[](auto off,auto v){std::cout<<"M "<<off<<' '<<v<<' ';};
 services.colors631250=[&](auto&,auto&){std::cout<<"U ";for(int i=0;i<cw*ch*3;++i)rgb[i]=std::uint8_t(i*29+seed);};
 services.createSecond=[&](auto width,auto height){
  surface.width=width;surface.height=height;
  const auto object=[&](auto off,auto n,auto value){buffer('S',off,n,value);};
  object(8,4,std::uint32_t(height));object(4,4,std::uint32_t(width));object(12,4,0);object(0,4,2);object(16,4,2);
  object(20,4,0);object(24,4,std::uint32_t(width)*std::uint32_t(height)*2);object(28,1,0);
  std::cout<<"A "<<width*height*2<<' ';object(20,4,1);object(28,1,1);object(0,4,3);return &surface;
 };
 services.clear=[&](auto&,auto color){std::cout<<"Z "<<color<<' ';std::fill(pixels.begin(),pixels.begin()+surface.width*surface.height*2,0);};
 auto view=[&]{return SurfacePixelView{surface.width,lock,bpp,offset,pixels,{},true};};
 services.lock=[&](auto&,auto x,auto y){std::cout<<"K "<<x<<' '<<y<<' ';const auto at=lockSurfacePixels(view(),x,y,[&]{return table.width7C(surface);},[&](auto v){buffer('S',12,4,std::uint32_t(v));});need(at&&*at==0);return std::span<std::uint8_t>(pixels);};
 services.unlock=[&](auto&){std::cout<<"N ";unlockSurfacePixels(view(),[&](auto v){buffer('S',12,4,std::uint32_t(v));});};
 RefreshRect source{0,0,w,h},region{rx,ry,rw,rh},out{9,8,7,6};auto* result=buildRadarProjection(out,source,region,std::uint8_t(update),{second,colors,cw,ch,bitmap,scale,shifts},services);need(result==&out);
 std::cout<<"R ";for(auto v:out)std::cout<<v<<' ';for(auto v:region)std::cout<<v<<' ';std::cout<<surface.width<<' '<<surface.height<<' '<<radarProjectionFloatBits(scale)<<' '<<cw<<' '<<ch<<' '<<lock<<' ';
 const auto digest=[](const auto& bytes){std::uint64_t value=14695981039346656037ull;for(auto b:bytes){value^=b;value*=1099511628211ull;}return value;};
 std::cout<<digest(rgb)<<' '<<digest(pixels)<<' '<<digest(bits)<<'\n';
}
void guards(){
 const int before=std::fegetround();
 // Successful real fixture calls must agree under each caller rounding mode,
 // and restore that mode. This also exercises the new-storage path.
 std::string baseline;
 for(const auto mode:{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO}){
  need(std::fesetround(mode)==0);std::ostringstream captured;auto* saved=std::cout.rdbuf(captured.rdbuf());
  try{std::istringstream input("P 8 6 1 1 3 2 0 0 0 1 34 0");run(input);}catch(...){std::cout.rdbuf(saved);std::fesetround(before);throw;}
  std::cout.rdbuf(saved);need(std::fegetround()==mode);
  if(baseline.empty())baseline=captured.str();else need(captured.str()==baseline);
 }
 need(std::fesetround(before)==0);
 for(unsigned failure=0;failure<7;++failure){
  RefreshSurfaceVirtuals table;table.width7C=[](auto& s){return s.width;};table.height80=[](auto& s){return s.height;};
  RefreshSurface surface{&table,1,1};auto* second=&surface;
  std::array<std::uint8_t,3> backing{};std::array<std::uint8_t,2> pixels{};std::array<std::uint8_t,1> bits{};
  std::span<std::uint8_t> rgb=backing,bitmap=bits;int w=1,h=1;float scale=1;std::array<std::int32_t,6> shifts{};RefreshRect source{0,0,1,1},region=source,out{};
  RadarProjectionServices services;
  services.lock=[&](auto&,auto,auto){return std::span<std::uint8_t>(pixels).first(failure==6?1:2);};services.unlock=[](auto&){};
  if(failure==0)rgb={}; // Missing allocator.
  if(failure==1){rgb={};services.allocate=[](auto){return std::span<std::uint8_t>{};};}
  if(failure==2){second=nullptr;services.createSecond=[](auto,auto)->RefreshSurface*{return nullptr;};}
  if(failure==3)scale=0;
  if(failure==4)services.lock={};
  bool refused=false;
  try{buildRadarProjection(out,source,region,failure==5?1:0,{second,rgb,w,h,bitmap,scale,shifts},services);}catch(const std::invalid_argument&){refused=true;}
  need(refused&&std::fegetround()==before);
 }
 need(radarProjectionInteger(-1.9)==-1&&radarProjectionInteger(0x1p32+1)==1&&radarProjectionInteger(0x1p63)==0&&radarProjectionInteger(-0x1p63)==0&&radarProjectionInteger(INFINITY)==0);
 std::cout<<"radar projection guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
