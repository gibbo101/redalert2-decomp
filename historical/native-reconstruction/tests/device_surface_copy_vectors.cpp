// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/DeviceSurfaceCopy.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Device copy fixture domain");}
void run(std::istream& in){
 char op;int enabled,secondary,count,status,restore,failed,bpp,width,height,sw,sh,sbpp;FillRect dr,sr;std::uint32_t first,second;
 need(bool(in>>op>>enabled>>secondary>>count>>status>>restore>>failed>>bpp>>width>>height>>sw>>sh>>sbpp)&&op=='C');
 for(auto& n:dr)need(bool(in>>n));for(auto& n:sr)need(bool(in>>n));need(bool(in>>first>>second));std::string tail;need(!(in>>tail));
 need(enabled>=0&&enabled<=255&&secondary>=0&&secondary<=255&&status>=0&&status<=3&&restore>=0&&restore<=1&&failed>=0&&failed<=1&&bpp>=1&&bpp<=3&&sbpp>=1&&sbpp<=3&&width>=0&&width<=16&&height>=0&&height<=16&&sw>=0&&sw<=16&&sh>=0&&sh<=16);
 std::uint8_t e=enabled,se=secondary,video=7;std::uint32_t bytes=bpp,address=0x3906080;std::uintptr_t device=1;
 std::array<std::uint32_t,27> owner;owner.fill(0xa5a5a5a5);owner[4]=width*bpp;std::span<std::uint32_t> descriptor=owner;
 DeviceSurfacePixelView view{count,bytes,address,video,device,descriptor};DeviceSurfacePixelServices os{e,se};unsigned calls=0;
 os.lost=[&](auto p){need(p==1);const auto v=status==0?0u:status==1?1u:status==2?0x887601c2u:calls==0?0x887601c2u:0u;++calls;std::cout<<"H "<<v<<' ';return v;};
 os.restore=[&](auto p){need(p==1);std::cout<<"T "<<restore<<' ';return std::uint32_t(restore);};
 os.lock=[&](auto p,auto d,auto flags){need(p==1&&flags==1&&d[0]==108&&std::all_of(d.begin()+1,d.end(),[](auto v){return v==0;}));std::cout<<"K "<<flags<<' '<<failed<<' ';if(!failed){d[4]=width*bpp;d[9]=0x3906080;d[21]=bpp*8;d[26]=0x2040;}return std::uint32_t(failed);};
 os.unlock=[&](auto p,auto at){need(p==1);std::cout<<"N "<<at<<' ';};
 os.objectStore=[](auto off,auto n,auto v){std::cout<<"O "<<off<<' '<<n<<' '<<v<<' ';};os.descriptorStore=[](auto off,auto n,auto v){std::cout<<"B "<<off<<' '<<n<<' '<<v<<' ';};
 std::array<std::uint8_t,2048> pixels[2];for(unsigned j=0;j<2;++j)for(unsigned i=0;i<2048;++i)pixels[j][i]=i%7==0?0:std::uint8_t(i*29+0x34+j*41);
 RefreshSurface geometry[2]{{nullptr,width,height},{nullptr,sw,sh}};std::int32_t softwareCount=0;std::uint32_t sourceOffset=128;
 const auto observe=[](unsigned j,char k,auto x,auto y){std::cout<<"Q "<<j<<' '<<k<<' '<<x<<' '<<y<<' ';};
 auto stores=[](unsigned j,auto at,auto n,auto v){std::cout<<"S "<<j<<' '<<at<<' '<<n<<' '<<v<<' ';};
 CopySurface dest{geometry[0],{geometry[0].width,count,bpp,address,pixels[0],{},true},[&](char k,auto x,auto y){if(k!='K'&&k!='U')observe(0,k,x,y);},[&](auto at,auto n,auto v){stores(0,at,n,v);},{},{}};
 CopySurface source{geometry[1],{geometry[1].width,softwareCount,sbpp,sourceOffset,pixels[1],{},true},[&](char k,auto x,auto y){observe(1,k,x,y);},[&](auto at,auto n,auto v){stores(1,at,n,v);},[](auto v){std::cout<<"L "<<v<<' ';},{}};
 dest.bytes70=[&]{return std::bit_cast<std::int32_t>(bytes);};dest.pitch74=[&]{return descriptor[4];};
 os.bytes70=[&]{return std::uint32_t(copySurfaceBpp(dest));};os.pitch74=[&]{return copySurfacePitch(dest);};
 dest.lock5C=[&](auto x,auto y)->std::optional<std::uint32_t>{auto a=lockDeviceSurfacePixels(view,x,y,os);if(!a)return {};need(a>=0x3906000);return a-0x3906000;};
 dest.unlock60=[&]{unlockDeviceSurfacePixels(view,os);};
 os.lockEntry=[&](auto x,auto y){observe(0,'K',x,y);};os.unlockEntry=[&]{observe(0,'U',0,0);};
 DeviceSurfaceCopyServices services{os,[](auto&){std::cout<<"V 0 ";return std::uint8_t(0);}};
 const auto result=copyDeviceSurface(dest,view,dr,source,sr,first,second,services);
 std::cout<<"R "<<result<<' '<<count<<' '<<bytes<<' '<<address<<' '<<unsigned(video)<<' '<<softwareCount<<" F ";for(auto v:owner)std::cout<<v<<' ';
 std::cout<<"P ";for(const auto& backing:pixels){std::uint64_t h=14695981039346656037ull;for(auto b:backing){h^=b;h*=1099511628211ull;}std::cout<<h<<' ';}std::cout<<'\n';
}
void guards(){
 std::int32_t lock=0,bpp=2;std::uint32_t addr=0,bytes=2;std::uint8_t video=0,enable=0;std::uintptr_t device=1;std::array<std::uint32_t,27> d{};std::span<std::uint32_t> ds=d;std::array<std::uint8_t,32> backing{};RefreshSurface g{nullptr,2,2};
 CopySurface s{g,{g.width,lock,bpp,addr,backing,{},true},{},{},{},{}};DeviceSurfacePixelView v{lock,bytes,addr,video,device,ds};DeviceSurfaceCopyServices p{{enable,enable},[](auto&){return std::uint8_t(0);}};
 FillRect r{0,0,2,2};need(!copyDeviceSurface(s,v,r,s,r,0,0,p));p.sourceDevice84=[](auto&){return std::uint8_t(1);};bool refused=false;try{copyDeviceSurface(s,v,r,s,r,0,0,p);}catch(const std::invalid_argument&){refused=true;}need(refused&&lock==0);
 std::cout<<"device surface copy guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
