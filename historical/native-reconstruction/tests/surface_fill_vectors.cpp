// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/SurfaceFill.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Surface fill fixture domain");}
void append(Bytes& b,std::uint32_t v){for(unsigned i=0;i<4;++i)b.push_back(std::uint8_t(v>>(i*8)));}
void run(std::istream& in){
    char op=0;FillSurface s;std::uint32_t color=0;FillRect clip{},rect{};
    require(bool(in>>op>>s.width>>s.height>>s.bytesPerPixel>>s.bufferOffset>>s.lockLevel>>color));
    require((op=='F'||op=='E')&&s.width>=0&&s.width<=32&&s.height>=0&&s.height<=24&&(s.bytesPerPixel==1||s.bytesPerPixel==2)&&s.bufferOffset>=16&&s.bufferOffset<=19);
    for(auto& n:clip)require(bool(in>>n));for(auto& n:rect)require(bool(in>>n));std::string tail;require(!(in>>tail));
    Bytes pixels(2048),trace;for(unsigned i=0;i<pixels.size();++i)pixels[i]=std::uint8_t(i*29+0x34);s.storage=pixels;
    const auto record=[&](auto p,auto n,auto v){append(trace,p);append(trace,n);append(trace,v);};
    auto result=op=='F'?fillSurfaceRect(s,rect,color,record):fillSurfaceRectEx(s,clip,rect,color,record);
    std::cout<<"R "<<result<<" B "<<assetSha256(Data(pixels))<<" T "<<assetSha256(Data(trace))<<" L "<<s.lockLevel<<'\n';
}
void guards(){
    Bytes b(32);FillSurface s{2,2,4,0,b,0};bool refused=false;
    try{fillSurfaceRect(s,{0,0,1,1},0);}catch(const std::invalid_argument&){refused=true;}require(refused);
    s.bytesPerPixel=2;s.width=8;refused=false;try{fillSurfaceRect(s,{0,0,8,8},0);}catch(const std::invalid_argument&){refused=true;} // height still two: backing exactly fits.
    require(!refused);s.height=8;try{fillSurfaceRect(s,{0,0,8,8},0);}catch(const std::invalid_argument&){refused=true;}require(refused);
    require(intersectFillRect({0,0,2,2},{2,0,1,1})==FillRect{});
    std::cout<<"surface fill guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
