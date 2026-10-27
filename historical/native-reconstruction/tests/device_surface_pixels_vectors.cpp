// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/DeviceSurfacePixels.hpp"
#include "render/SurfacePixel.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Device pixel fixture domain");}
void run(std::istream& in){
 char op;int enabled,secondary,present,count,x,y,status,restore,failed;unsigned bits,caps,pitch,offset,initialBytes;std::string operations;
 need(bool(in>>op>>enabled>>secondary>>present>>count>>x>>y>>status>>restore>>failed>>bits>>caps>>pitch>>offset>>initialBytes>>operations)&&op=='D'&&enabled>=0&&enabled<=255&&secondary>=0&&secondary<=255&&present>=0&&present<=1&&status>=0&&status<=3&&restore>=0&&restore<=1&&failed>=0&&failed<=1&&pitch<=4096&&offset<=4096&&operations.size()>=1&&operations.size()<=8);
 std::string tail;need(!(in>>tail));for(auto c:operations)need(c=='L'||c=='U'||c=='S'||c=='G');
 std::uint32_t bytes=initialBytes,address=0x3902000+offset;std::uint8_t video=7,first=std::uint8_t(enabled),second=std::uint8_t(secondary);std::uintptr_t device=present;
 std::array<std::uint32_t,27> owner;owner.fill(0xa5a5a5a5);owner[4]=pitch;std::span<std::uint32_t> descriptor=owner;
 DeviceSurfacePixelView view{count,bytes,address,video,device,descriptor};DeviceSurfacePixelServices services{first,second};unsigned calls=0;
 services.lost=[&](auto p){need(p==1);const auto value=status==0?0u:status==1?1u:status==2?0x887601c2u:calls==0?0x887601c2u:0u;++calls;std::cout<<"H "<<value<<' ';return value;};
 services.restore=[&](auto p){need(p==1);std::cout<<"T "<<restore<<' ';return std::uint32_t(restore);};
 services.lock=[&](auto p,auto d,auto flags){need(p==1&&flags==1&&d[0]==108&&std::all_of(d.begin()+1,d.end(),[](auto v){return v==0;}));std::cout<<"K "<<flags<<' '<<failed<<' ';if(!failed){d[4]=pitch;d[9]=0x3902000+offset;d[21]=bits;d[26]=caps;}return std::uint32_t(failed);};
 services.unlock=[&](auto p,auto at){need(p==1);std::cout<<"N "<<at<<' ';};
 services.objectStore=[](auto off,auto n,auto v){std::cout<<"O "<<off<<' '<<n<<' '<<v<<' ';};services.descriptorStore=[](auto off,auto n,auto v){std::cout<<"B "<<off<<' '<<n<<' '<<v<<' ';};
 std::array<std::uint8_t,2048> pixels;for(unsigned i=0;i<pixels.size();++i)pixels[i]=std::uint8_t(i*29+0x34);
 for(unsigned i=0;i<4;++i)pixels[i]=std::uint8_t(0x3903000u>>(i*8));
 SurfacePixelServices access;
 access.lock=[&](auto a,auto b)->std::optional<std::uint32_t>{auto at=lockDeviceSurfacePixels(view,a,b,services);if(!at)return {};need(at>=0x3902000);return at-0x3902000;};
 access.bytes70=[&]{return std::bit_cast<std::int32_t>(bytes);};access.unlock=[&]{(void)unlockDeviceSurfacePixels(view,services);};
 for(char c:operations){
  std::cout<<"I "<<(c=='L'?0:c=='U'?1:c=='S'?2:3)<<' ';std::uint32_t result;
  if(c=='L')result=lockDeviceSurfacePixels(view,x,y,services);
  else if(c=='U')result=unlockDeviceSurfacePixels(view,services);
  else if(c=='S')result=setSurfacePixelThrough({pixels,{}},x,y,0xdead1234,access,[](auto at,auto n,auto v){std::cout<<"C "<<at<<' '<<n<<' '<<v<<' ';});
  else result=getSurfacePixelThrough({pixels,{}},x,y,access);
  std::cout<<"R "<<result<<' '<<count<<' '<<bytes<<' '<<address<<' '<<unsigned(video)<<' ';
 }
 std::cout<<"F ";for(auto v:owner)std::cout<<v<<' ';
 if(operations.find_first_of("SG")!=std::string::npos){std::uint64_t digest=14695981039346656037ull;for(auto b:pixels){digest^=b;digest*=1099511628211ull;}std::cout<<"P "<<digest<<' ';}
 std::cout<<'\n';
}
void guards(){
 std::int32_t count=0;std::uint32_t bytes=2,address=0;std::uint8_t video=0,enabled=0;std::uintptr_t device=1;std::array<std::uint32_t,27> owner{};std::span<std::uint32_t> descriptor=owner;
 DeviceSurfacePixelView view{count,bytes,address,video,device,descriptor};DeviceSurfacePixelServices services{enabled,enabled};
 need(!lockDeviceSurfacePixels(view,0,0,services)&&!unlockDeviceSurfacePixels(view,services));enabled=1;bool refused=false;
 try{lockDeviceSurfacePixels(view,0,0,services);}catch(const std::invalid_argument&){refused=true;}need(refused&&count==0);
 services.lost=[](auto){return 0u;};need(lockDeviceSurfacePixels(view,-1,0,services)==0&&count==0);
 count=1;services.unlock=[](auto,auto){};need(unlockDeviceSurfacePixels(view,services)&&count==0&&address==0);
 // Original status recovers, recursive OS Lock fails, then a nonzero pixel
 // offset is returned from a cleared buffer. Refuse the invalid host backing.
 count=2;address=0x3902080;bytes=2;owner[4]=32;unsigned statusCalls=0;
 services.lost=[&](auto){return statusCalls++==0?0x887601c2u:0u;};
 services.restore=[](auto){return 0u;};services.lock=[](auto,auto,auto){return 1u;};
 SurfacePixelServices pixel;
 pixel.lock=[&](auto x,auto y)->std::optional<std::uint32_t>{
  auto at=lockDeviceSurfacePixels(view,x,y,services);if(!at)return {};
  need(at>=0x3902000u);return at-0x3902000u;
 };
 pixel.bytes70=[&]{return std::int32_t(bytes);};pixel.unlock=[&]{unlockDeviceSurfacePixels(view,services);};
 std::array<std::uint8_t,2048> backing{};refused=false;
 try{setSurfacePixelThrough({backing,{}},1,2,0x1234,pixel);}catch(const std::invalid_argument&){refused=true;}
 need(refused&&address==0&&count==3&&std::all_of(backing.begin(),backing.end(),[](auto v){return v==0;}));
 std::cout<<"device surface pixel guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
