// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/SurfaceCopy.hpp"
#include "assets/PreparedData.hpp"
#ifdef RA2_SURFACE_REFRESH_COPY
#include "render/SurfaceCopyBinding.hpp"
#endif
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void need(bool v){if(!v)throw std::invalid_argument("Surface copy fixture domain");}
void run(std::istream& in){
 char op;int same,words;need(bool(in>>op>>same>>words)&&(same==0||same==1)&&(words==0||words==1));
#ifdef RA2_SURFACE_REFRESH_COPY
 need(op=='J');
#else
 need(op=='C');
#endif
 struct Owner {RefreshSurface geometry{nullptr,0,0};std::int32_t bpp=0,lock=0;std::uint32_t offset=0;int present=1;Bytes bytes;std::vector<std::uint16_t> numeric;};
 std::array<Owner,2> owners;
 for(unsigned j=0;j<2;++j){auto& o=owners[j];need(bool(in>>o.geometry.width>>o.geometry.height>>o.bpp>>o.offset>>o.lock>>o.present));
  need(o.geometry.width>=-4&&o.geometry.width<=96&&o.geometry.height>=-4&&o.geometry.height<=32&&o.bpp>=0&&o.bpp<=4&&o.offset<=259&&(o.present==0||o.present==1));
  o.bytes.resize(8192);for(unsigned i=0;i<o.bytes.size();++i)o.bytes[i]=i%7==0?0:std::uint8_t(i*29+0x34+j*41);
  o.numeric.resize(4096);for(unsigned i=0;i<o.numeric.size();++i)o.numeric[i]=std::uint16_t(o.bytes[2*i]|std::uint16_t(o.bytes[2*i+1])<<8);
 }
 FillRect dr,sr;for(auto& x:dr)need(bool(in>>x));for(auto& x:sr)need(bool(in>>x));std::uint32_t f1,f2;need(bool(in>>f1>>f2));std::string tail;need(!(in>>tail));
 auto view=[&](unsigned j){auto& o=owners[j];return SurfacePixelView{o.geometry.width,o.lock,o.bpp,o.offset,words?std::span<std::uint8_t>{}:std::span<std::uint8_t>{o.bytes},words?std::span<std::uint16_t>{o.numeric}:std::span<std::uint16_t>{},bool(o.present)};};
 auto make=[&](unsigned j){return CopySurface{owners[j].geometry,view(j),[j](char kind,auto x,auto y){std::cout<<"Q "<<j<<' '<<kind<<' '<<x<<' '<<y<<' ';},[j](auto at,auto n,auto v){std::cout<<"S "<<j<<' '<<at<<' '<<n<<' '<<v<<' ';},[j](auto lock){std::cout<<"L "<<j<<' '<<lock<<' ';}};};
 auto d=make(0),s=make(1);
#ifdef RA2_SURFACE_REFRESH_COPY
 RefreshSurfaceVirtuals table;d.geometry.table=&table;s.geometry.table=&table;
 table.rect78=[&](RefreshSurface& receiver,RefreshRect& out){auto& owner=&receiver==&d.geometry?d:s;out=copySurfaceRect(owner);return &out;};
 SurfaceCopyServices services{[&](RefreshSurface& receiver)->CopySurface&{need(&receiver==&d.geometry||&receiver==&s.geometry);return &receiver==&d.geometry?d:s;}};
 SurfaceCopyBinding bind(table,services);RefreshSurface* first=&d.geometry;RefreshSurface* second=same?first:&s.geometry;
 int mode=0;SurfaceRefreshScratch scratch{};SurfaceRefreshServices refresh{mode,first,second,[]{std::cout<<"F ";},{}};
 refreshSurfaces(refresh,scratch);const auto ok=true;
#else
 const auto ok=copySurface(d,dr,same?d:s,sr,f1,f2);
#endif
 std::cout<<"R "<<ok;for(auto& o:owners){if(words)for(unsigned i=0;i<o.bytes.size();++i)o.bytes[i]=std::uint8_t(o.numeric[i/2]>>(8*(i&1)));std::cout<<' '<<o.lock<<' '<<assetSha256(Data(o.bytes));}std::cout<<'\n';
}
void guards(){
 RefreshSurface geometry{nullptr,2,2};FillSurface pixels;pixels.width=2;std::array<std::uint8_t,64> bytes{};pixels.storage=bytes;
 auto pv=surfacePixelView(pixels);CopySurface wrong{geometry,pv,{},{},{}};bool refused=false;
 try{copySurface(wrong,{0,0,1,1},wrong,{0,0,1,1},0,1);}catch(const std::invalid_argument&){refused=true;}need(refused&&pixels.lockLevel==0);
 SurfacePixelView good{geometry.width,pixels.lockLevel,pixels.bytesPerPixel,pixels.bufferOffset,pixels.storage,{},true};CopySurface s{geometry,good,{},{},{}};
 refused=false;try{copySurface(s,{0,0,1,1},s,{0,0,1,1},0,1,true);}catch(const std::invalid_argument&){refused=true;}need(refused&&pixels.lockLevel==2);
 pixels.lockLevel=0;need(copySurface(s,{0,0,1,1},s,{0,0,1,1},0,1)&&pixels.lockLevel==0);
 bool fault=false;s.observe=[](char kind,auto,auto){if(kind=='W')throw std::runtime_error("width fault");};
 try{copySurface(s,{0,0,1,1},s,{0,0,1,1},0,1);}catch(const std::runtime_error&){fault=true;}need(fault&&pixels.lockLevel==1);
#ifdef RA2_SURFACE_REFRESH_COPY
 int resolved=0,oldCalls=0;RefreshSurfaceVirtuals table;
 table.copy8=[&](auto&,auto*,auto*,auto*,auto,auto){++oldCalls;};
 SurfaceCopyServices services{[&](RefreshSurface& receiver)->CopySurface&{++resolved;need(&receiver==&geometry);return s;}};
 s.observe={};FillRect r{0,0,1,1};pixels.lockLevel=0;
 {SurfaceCopyBinding bind(table,services);need(resolved==0);table.copy8(geometry,&r,&geometry,&r,0,1);need(resolved==2);}
 table.copy8(geometry,&r,&geometry,&r,0,1);need(oldCalls==1);
 bool propagated=false;services.surface=[](auto&)->CopySurface&{throw std::runtime_error("owner fault");};
 try{SurfaceCopyBinding bind(table,services);table.copy8(geometry,&r,&geometry,&r,0,1);}catch(const std::runtime_error&){propagated=true;}
 need(propagated);table.copy8(geometry,&r,&geometry,&r,0,1);need(oldCalls==2);
#endif
 std::cout<<"surface copy guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
