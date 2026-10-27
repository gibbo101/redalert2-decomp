// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitSurfaceDraw.hpp"
#include <openssl/evp.h>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void rect(PixelRect r){std::cout<<r.x<<' '<<r.y<<' '<<r.width<<' '<<r.height<<' ';}
std::string digest(const std::vector<std::uint16_t>& plane){
    Bytes bytes;for(auto v:plane){bytes.push_back(v&255);bytes.push_back(v>>8);}
    unsigned char h[EVP_MAX_MD_SIZE];unsigned size=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),h,&size,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream out;for(unsigned i=0;i<size;++i)out<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return out.str();
}
}
int main(){try {
    std::string line;
    while(std::getline(std::cin,line)){
        std::istringstream input(line);char op;input>>op;
        if(op=='D'){
            UnitDisguiseState a;int frame,owner;std::uint32_t flags;
            input>>frame>>a.creationFrame>>a.timerStart>>a.timerDuration>>flags>>owner;
            auto value=unitDisguiseDrawFlags(a,frame,flags,[&]{std::cout<<"owner ";return owner!=0;});
            std::cout<<"flags "<<value;
        }else if(op=='S'){
            UnitSurfaceInputs in;UnitDisguiseState a;
            int layer,first,second,mode,f134,f135,current,disguised,frame,scheme,extra,z,gradient,actualLayer;
            input>>layer>>in.layerFourValue>>first>>second>>mode>>f134>>f135>>current>>disguised
                 >>frame>>a.creationFrame>>a.timerStart>>a.timerDuration>>scheme>>extra>>z>>gradient>>actualLayer
                 >>in.point.x>>in.point.y>>in.dirty.x>>in.dirty.y>>in.dirty.width>>in.dirty.height
                 >>in.clip.x>>in.clip.y>>in.clip.width>>in.clip.height>>in.brightness;
            UnitSurfaceServices s;
            s.layer=[&]{std::cout<<"layer 0 0 ";if(actualLayer)std::cout<<"drive_layer type type ";return actualLayer?0:layer;};
            s.layerFourExtra=[&]{std::cout<<"extra ";return extra;};
            s.flag204=[&]{std::cout<<"flag204 ";return std::uint8_t(first);};
            s.flag205=[&]{std::cout<<"flag205 ";return std::uint8_t(second);};
            s.ownerVisible=[&]{std::cout<<"owner ";return unitOwnerTypeVisible(mode,std::uint8_t(f134),std::uint8_t(f135),current!=0);};
            s.disguised=[&]{std::cout<<"disguised ";return std::uint8_t(disguised);};
            s.disguiseFlags=[&](auto flags){std::cout<<"disguise "<<flags<<' ';return unitDisguiseDrawFlags(a,frame,flags,s.ownerVisible);};
            s.houseBlitter=[&](auto flags){std::cout<<"select "<<scheme<<' '<<flags<<' ';return std::uint32_t(1000+scheme*256+unitSurfaceBlitterSlot(flags));};
            s.gradient=[&]{std::cout<<"gradient ";return gradient;};s.depth=[&]{std::cout<<"depth ";return z;};
            s.sourceBounds=[]{std::cout<<"bounds ";return PixelRect{0,0,256,256};};
            s.draw=[](const UnitSurfaceRequest& r){std::cout<<"draw ";rect(r.destination);rect(r.sourceBounds);rect(r.source);rect(r.clip);
                std::cout<<r.blitter<<' '<<r.depth<<' '<<r.gradient<<' '<<r.brightness<<' '<<r.extra;};
            drawOrdinaryUnitSurface(in,s);
        }else if(op=='P'){
            int n,w,h,sw,sh,z,scheme;UnitSurfaceInputs in;
            input>>n>>w>>h>>sw>>sh>>in.dirty.x>>in.dirty.y>>in.dirty.width>>in.dirty.height
                 >>in.point.x>>in.point.y>>in.clip.x>>in.clip.y>>in.clip.width>>in.clip.height>>z>>in.brightness>>scheme;
            if(w<1||h<1||w>128||h>128||sw<1||sh<1||sw>256||sh>256||n<0||n>100000||scheme<0||scheme>7)throw std::runtime_error("Bad surface pixel fixture");
            Bytes source(sw*sh);std::vector<std::uint16_t> colors(w*h),depth(w*h),alpha(w*h);std::vector<Palette16> palettes(53);
            constexpr unsigned depths[]={0,32720,32740,32760,32768,32780,65535};
            for(std::size_t i=0;i<source.size();++i)source[i]=i%7?std::uint8_t(i*13+unsigned(n)):0;
            for(std::size_t i=0;i<colors.size();++i){colors[i]=std::uint16_t(i*37+unsigned(n)*91);depth[i]=std::uint16_t(depths[(i+unsigned(n))%7]);alpha[i]=std::uint16_t((i*17+unsigned(n)*11)&255);}
            for(unsigned row=0;row<53;++row)for(unsigned i=0;i<256;++i)palettes[row][i]=std::uint16_t(unsigned(scheme)*257+row*599+i*131);
            UnitSurfaceServices s;s.layer=[]{return 0;};s.flag204=s.flag205=s.disguised=[]{return std::uint8_t(0);};s.ownerVisible=[]{return false;};
            s.houseBlitter=[](auto flags){return unitSurfaceBlitterSlot(flags);};s.gradient=[]{return 2;};s.depth=[&]{return z;};
            s.sourceBounds=[&]{return PixelRect{0,0,sw,sh};};s.draw=[&](const UnitSurfaceRequest& r){
                if(r.blitter!=0x98||r.gradient!=2||r.extra)throw std::runtime_error("Unexpected ordinary blitter");
                blitUnit(source,sw,sh,r.source,{r.destination.x,r.destination.y},r.clip,r.depth,r.brightness,palettes,w,h,colors,depth,alpha);
            };
            drawOrdinaryUnitSurface(in,s);std::cout<<"pixels "<<digest(colors)<<' '<<digest(depth);
        }else throw std::runtime_error("Unknown Unit surface command");
        if(!input)throw std::runtime_error("Incomplete Unit surface command");
        input>>std::ws;if(!input.eof())throw std::runtime_error("Trailing Unit surface command data");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
