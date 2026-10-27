// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/FramePlane.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
int main(int argc,char**argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){
  std::uint32_t offset=0,begin=0,end=16,extent=16;int base=32768,w=2,h=4;std::array<std::uint16_t,8> pixels{};
  FramePlaneView v{offset,begin,end,extent,base,w,h,{{},pixels}};
  bool refused=false;try{clearFramePlane(v,0,{});}catch(const std::invalid_argument&){refused=true;}if(!refused)throw std::runtime_error("Missing clear guard");
  w=0;refused=false;try{scrollFramePlane(v,0,0,0,{});}catch(const std::invalid_argument&){refused=true;}if(!refused)throw std::runtime_error("Missing scroll dimension guard");
  w=2;scrollFramePlane(v,0,0,0,{});if(offset||base!=32768)throw std::runtime_error("Zero scroll changed state");
  const auto expected=pixels;offset=4;scrollFramePlane(v,3,0,0xdead1234,[&](auto r,auto c){if(r!=FillRect{0,0,2,4}||c!=0x1234)throw std::runtime_error("Full fallback arguments");});
  if(offset!=4||base!=32768||pixels!=expected)throw std::runtime_error("Fallback must keep offset and delegate fill");
  std::cout<<"Frame plane guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);int op,w,h,initialBase,dx,dy,lock,words;std::uint32_t begin,offset,color;
  in>>op>>w>>h>>begin>>offset>>initialBase>>dx>>dy>>color>>lock>>words;if(!in)throw std::invalid_argument("Invalid frame plane vector");
  int base=initialBase;const std::uint32_t end=begin+std::uint32_t(w*h*2),extent=w*h*2;const int bpp=2;
  Bytes data(2048);std::vector<std::uint16_t> numeric(1024);for(unsigned i=0;i<data.size();++i)data[i]=std::uint8_t(i*29+0x34);
  for(unsigned i=0;i<numeric.size();++i)numeric[i]=std::uint16_t(data[2*i]|std::uint16_t(data[2*i+1])<<8);
  SurfacePixelBacking backing{words?std::span<std::uint8_t>{}:std::span<std::uint8_t>(data),words?std::span<std::uint16_t>(numeric):std::span<std::uint16_t>{}};
  std::ostringstream trace;auto e=[&](int k,std::int64_t a=0,std::int64_t b=0,std::int64_t c=0,std::int64_t d=0,std::int64_t f=0){trace<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<f<<' ';};
  const auto pixels=[&](auto p,auto n,auto v){e(2,p,n,v);};
  const auto fill=[&](FillRect r,std::uint32_t color){e(1,r[0],r[1],r[2],r[3],color);bool locked=false;
   fillSurfaceRectThrough({w,h,bpp,lock,backing.storage,begin,backing.words},r,color,[&](auto p,auto n,auto v){if(!locked){e(4,lock);locked=true;}pixels(p,n,v);});
   if(locked)e(4,lock);
  };
  FramePlaneView v{offset,begin,end,extent,base,w,h,backing};
  if(op<2)scrollFramePlane(v,dx,dy,color,fill,pixels,[&](int field,std::uint32_t value){e(3,field,std::bit_cast<std::int32_t>(value));});else clearFramePlane(v,color,fill);
  if(words)for(unsigned i=0;i<data.size();++i)data[i]=std::uint8_t(numeric[i/2]>>(8*(i&1)));
  std::cout<<trace.str()<<"F "<<std::bit_cast<std::int32_t>(offset)<<' '<<base<<' '<<lock<<' '<<assetSha256(Data(data))<<'\n';
 }
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
