// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/RadarSurfaceStartup.hpp"
#include "render/SurfaceStartup.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Radar startup domain");}
// Geometry is borrowed from the exact surface passed to refresh and the caller.
struct BorrowedDevice {
 std::int32_t &width4,&height8;std::int32_t lockC=0;
 std::uint32_t bytes10=0,offset14=0;std::uint8_t flag18=0,video19=0;
 std::uintptr_t surface1C=0;std::span<std::uint32_t> descriptor20;
};
void run(std::istream& in){
 char op;std::int32_t w,h,x,y,sw,sh;unsigned old,requested,forced,allocation,created;std::uint32_t bits,caps;
 need(bool(in>>op>>w>>h>>x>>y>>sw>>sh>>old>>forced>>allocation>>created>>bits>>caps)&&op=='R'&&old<16&&forced<=255&&allocation<=1&&created<=1);std::string tail;need(!(in>>tail));requested=1;
 RefreshSurfaceVirtuals table;table.width7C=[](auto& s){std::cout<<"W "<<s.width<<' ';return s.width;};table.height80=[](auto& s){std::cout<<"H "<<s.height<<' ';return s.height;};
 RefreshSurface firstRecord{&table,0,0},secondRecord{&table,sw,sh},oldFirst{&table,1,2},oldSecond{&table,3,4};
 RefreshSurface* first=(old&1)?&oldFirst:nullptr;RefreshSurface* second=(old&2)?&oldSecond:nullptr;
 int colorsOwner=0,bitmapOwner=0;const void* colors=(old&4)?&colorsOwner:nullptr;const void* bitmap=(old&8)?&bitmapOwner:nullptr;RefreshRect rect{17,19,w,h};
 BorrowedDevice device{firstRecord.width,firstRecord.height};std::array<std::uint32_t,27> descriptor;descriptor.fill(0xa5a5a5a5);
 const auto out=[](char k,unsigned o,unsigned n,std::uint32_t v){std::cout<<k<<' '<<o<<' '<<n<<' '<<v<<' ';};
 SurfaceStartupServices backend;
 backend.objectStore=[&](auto o,auto n,auto v){out('O',o,n,v);};backend.descriptorStore=[&](auto o,auto n,auto v){out('D',o,n,v);};
 backend.allocate=[&](auto n){std::cout<<"A "<<n<<' ';return allocation?std::span<std::uint32_t>(descriptor):std::span<std::uint32_t>{};};
 backend.create=[&](auto d,auto& surface){std::cout<<"C "<<d[0]<<' '<<d[1]<<' '<<d[2]<<' '<<d[3]<<' '<<d[26]<<' ';surface=created;out('O',28,4,created);};
 backend.describe=[&](auto surface,auto){std::cout<<"G "<<surface<<' ';descriptor[21]=bits;out('D',84,4,bits);descriptor[26]=caps;out('D',104,4,caps);};
 RadarSurfaceStartupServices services;
 services.store=[](auto off,auto v){std::cout<<"M "<<off<<' '<<v<<' ';};
 services.destroy=[&](auto* p,auto flag){std::cout<<"X "<<(p==&oldSecond?2:1)<<' '<<flag<<' ';};
 services.release=[&](auto* p){std::cout<<"F "<<(p==&colorsOwner?3:4)<<' ';};
 services.buildSecond=[&](auto&,auto& a,auto& b,auto flag){need(&a==&rect&&&a==&b&&flag==1);std::cout<<"B "<<a[0]<<' '<<a[1]<<' '<<a[2]<<' '<<a[3]<<' '<<unsigned(flag)<<' ';second=&secondRecord;std::cout<<"M 4636 5 ";};
 services.allocateFirst=[&](auto n){std::cout<<"A "<<n<<' ';return &firstRecord;};
 services.initializeFirst=[&](auto* p,auto width,auto height,auto video){need(p==&firstRecord);const std::uint8_t force=std::uint8_t(forced);initializeDeviceSurface(device,width,height,video,force,backend);return p;};
 services.clear=[](auto&,auto color){std::cout<<"L "<<color<<' ';};services.finish632700=[](){std::cout<<"Z ";};
 initializeRadarSurfaces({first,second,colors,bitmap,rect,x,y},services);
 std::cout<<"R ";for(auto v:rect)std::cout<<v<<' ';std::cout<<(first==&firstRecord?1:first?6:0)<<' '<<(second==&secondRecord?5:second?7:0)<<' '<<bool(colors)<<' '<<bool(bitmap)<<' '<<firstRecord.width<<' '<<firstRecord.height<<' '<<device.bytes10<<' '<<unsigned(device.video19)<<' '<<device.surface1C<<'\n';
}
void guards(){
 RefreshSurface* first=nullptr;RefreshSurface* second=nullptr;const void* colors=nullptr;const void* bitmap=nullptr;RefreshRect r{9,8,0,1};std::int32_t x=0,y=0;RadarSurfaceStartupServices services;
 initializeRadarSurfaces({first,second,colors,bitmap,r,x,y},services);need(r[0]==9&&r[1]==8);
 RefreshSurfaceVirtuals table;table.width7C=refreshSurfaceWidth;table.height80=refreshSurfaceHeight;RefreshSurface s{&table,140,108};r[2]=1;
 services.buildSecond=[&](auto&,auto&,auto&,auto){second=&s;};services.allocateFirst=[](auto)->RefreshSurface*{return nullptr;};bool refused=false;
 try{initializeRadarSurfaces({first,second,colors,bitmap,r,x,y},services);}catch(const std::invalid_argument&){refused=true;}need(refused&&first==nullptr&&second==&s&&r[2]==140&&r[3]==108);
 std::cout<<"radar surface startup guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
