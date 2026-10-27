// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/CachedVoxelShadow.hpp"
#include <openssl/evp.h>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
template<class... T>void out(T... v){((std::cout<<v<<' '),...);}
std::string digest(const std::vector<std::uint16_t>& v){
    Bytes b;for(auto n:v){b.push_back(n&255);b.push_back(n>>8);}
    unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;
    if(!EVP_Digest(b.data(),b.size(),h,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return s.str();
}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);int seed,mode,w,h,ox,oy,z;PixelPoint p;PixelRect clip,dirty;
        in>>seed>>mode>>w>>h>>ox>>oy>>p.x>>p.y>>clip.x>>clip.y>>clip.width>>clip.height>>z>>dirty.x>>dirty.y>>dirty.width>>dirty.height;
        if(!in||seed<0||seed>100000||mode<0||mode>3||w<1||w>256||h<1||h>256)throw std::invalid_argument("Invalid cached shadow fixture");
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing cached shadow fixture");
        Bytes source(std::size_t(w)*h+2);
        for(unsigned i=0;i<unsigned(w*h);++i){
            if(mode==0)source[i]=std::uint8_t((i*37+unsigned(seed)*19)%255+1);
            else if(mode==1)source[i]=0;
            else if(mode==2)source[i]=i%unsigned(w)<unsigned(std::min(w,7))||int(i%unsigned(w))>=w-3?0:std::uint8_t((i*13+unsigned(seed))%255+1);
            else source[i]=i%257==256?93:0;
        }
        source[std::size_t(w)*h]=std::uint8_t(seed);source[std::size_t(w)*h+1]=std::uint8_t(seed*3);
        Bytes pool(65536,0xa5);std::size_t cursor=0;
        const auto snapshot=appendVoxelSnapshot(pool,cursor,source,w,h,{ox,oy,0,0,w,h});
        if(!snapshot)throw std::runtime_error("Fixture pool exhausted");
        constexpr int width=160,height=144;std::vector<std::uint16_t> colors(width*height),depth(width*height);
        constexpr unsigned depths[]={0,32720,32740,32760,32768,32780,65535};
        for(unsigned i=0;i<colors.size();++i){colors[i]=std::uint16_t(i*37+unsigned(seed)*91);depth[i]=std::uint16_t(depths[(i+unsigned(seed))%7]);}
        CachedVoxelPartServices s;s.kind=[]{out("kind");};s.selectBlitter=[](auto f){out("select",f);};
        s.value2C4=[]{out("v2c4");return 2;};s.value2C0=[&]{out("v2c0");return z;};
        drawOrdinaryCachedVoxelShadow(pool,*snapshot,p,clip,s,width,height,colors,depth,dirty);
        out("draw",dirty.x,dirty.y,dirty.width,dirty.height,digest(colors),digest(depth));std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
