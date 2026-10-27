// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitSurfaceSplit.hpp"
#include "foot_depth_fixture.hpp"
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>
using namespace ra2;
namespace {
struct BridgeFixture {
    int flag,p100,p0,field494,present,kind,typeflag;
    void read(std::istream& in){in>>flag>>p100>>p0>>field494>>present>>kind>>typeflag;}
    UnitSurfaceBridgeServices services(bool log,DepthFixture* actual=nullptr) {
        UnitSurfaceBridgeServices b;
        b.flag100=[this,log,actual]{if(actual)return std::uint8_t(footDepthFlag(actual->world()));if(log)std::cout<<"p3 ";return std::uint8_t(p100);};
        b.predicate0=[this,log,actual]{if(actual)return footDepthPredicate0(actual->world());if(log)std::cout<<"p0 ";return p0;};
        b.firstContact=[this,log]{if(log)std::cout<<"contact ";return present!=0;};
        b.contactKind=[this,log]{if(log)std::cout<<"kind ";return kind;};
        b.contactType1357=[this,log]{if(log)std::cout<<"ctype ";return std::uint8_t(typeflag);};return b;
    }
};
void rect(PixelRect r){std::cout<<r.x<<' '<<r.y<<' '<<r.width<<' '<<r.height<<' ';}
std::string digest(const std::vector<std::uint16_t>& plane) {
    Bytes bytes;for(auto v:plane){bytes.push_back(v&255);bytes.push_back(v>>8);}
    unsigned char h[EVP_MAX_MD_SIZE];unsigned size=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),h,&size,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream out;for(unsigned i=0;i<size;++i)out<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return out.str();
}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)) {
        std::istringstream input(line);char op;input>>op;DepthFixture world;
        if(op=='N'){input>>world.seed>>world.x>>world.y>>world.bridge>>world.tileBase>>world.invalidX>>world.invalidY>>world.count;world.prepare();}
        BridgeFixture b;b.read(input);const auto bs=b.services(op!='P',op=='N'?&world:nullptr);UnitSurfaceInputs in;in.typeBAE=std::uint8_t(b.flag);
        if(op=='S'||op=='N') {
            int layer,first,second,extra,z,z2,gradient,index=0;
            input>>layer>>first>>second>>extra>>in.layerFourValue>>z>>z2>>gradient
                >>in.point.x>>in.point.y>>in.dirty.x>>in.dirty.y>>in.dirty.width>>in.dirty.height
                >>in.clip.x>>in.clip.y>>in.clip.width>>in.clip.height>>in.brightness;
            UnitSurfaceServices s;
            s.layer=[&]{std::cout<<"layer 0 0 ";return layer;};s.layerFourExtra=[&]{std::cout<<"extra ";return extra;};
            s.flag204=[&]{std::cout<<"flag204 ";return std::uint8_t(first);};s.flag205=[&]{std::cout<<"flag205 ";return std::uint8_t(second);};
            s.ownerVisible=[]{std::cout<<"owner ";return false;};
            s.houseBlitter=[](auto flags){std::cout<<"select 0 "<<flags<<' ';return std::uint32_t(1000+unitSurfaceBlitterSlot(flags));};
            s.gradient=[&]{std::cout<<"gradient ";return gradient;};s.depth=[&]{std::cout<<"depth ";return index++?z2:z;};
            s.sourceBounds=[]{std::cout<<"bounds ";return PixelRect{0,0,256,256};};
            s.draw=[](const UnitSurfaceRequest& r){std::cout<<"draw ";rect(r.destination);rect(r.sourceBounds);rect(r.source);rect(r.clip);
                std::cout<<r.blitter<<' '<<r.depth<<' '<<r.gradient<<' '<<r.brightness<<' '<<r.extra<<' ';};
            drawBridgeUnitSurface(in,std::uint32_t(b.field494),bs,s);
        } else if(op=='P') {
            int n,w,h,sw,sh,z,scheme;
            input>>n>>w>>h>>sw>>sh>>in.dirty.x>>in.dirty.y>>in.dirty.width>>in.dirty.height
                >>in.point.x>>in.point.y>>in.clip.x>>in.clip.y>>in.clip.width>>in.clip.height>>z>>in.brightness>>scheme;
            if(w<1||h<1||w>128||h>128||sw<1||sh<1||sw>256||sh>256||n<0||n>100000||scheme<0||scheme>7)throw std::runtime_error("Bad split pixel fixture");
            Bytes source(sw*sh);std::vector<std::uint16_t> colors(w*h),depth(w*h),alpha(w*h);std::vector<Palette16> palettes(53);
            constexpr unsigned depths[]={0,32720,32740,32760,32768,32780,65535};
            for(std::size_t i=0;i<source.size();++i)source[i]=i%7?std::uint8_t(i*13+unsigned(n)):0;
            for(std::size_t i=0;i<colors.size();++i){colors[i]=std::uint16_t(i*37+unsigned(n)*91);depth[i]=std::uint16_t(depths[(i+unsigned(n))%7]);alpha[i]=std::uint16_t((i*17+unsigned(n)*11)&255);}
            for(unsigned row=0;row<53;++row)for(unsigned i=0;i<256;++i)palettes[row][i]=std::uint16_t(unsigned(scheme)*257+row*599+i*131);
            UnitSurfaceServices s;s.layer=[]{return 0;};s.flag204=s.flag205=s.disguised=[]{return std::uint8_t(0);};s.ownerVisible=[]{return false;};
            s.houseBlitter=[](auto flags){return unitSurfaceBlitterSlot(flags);};s.gradient=[]{return 2;};s.depth=[&]{return z;};
            s.sourceBounds=[&]{return PixelRect{0,0,sw,sh};};s.draw=[&](const UnitSurfaceRequest& r){
                if(r.blitter!=0x98||r.extra)throw std::runtime_error("Unexpected split blitter");
                if(r.gradient==0)blitUnitTopGradient(source,sw,sh,r.source,{r.destination.x,r.destination.y},r.clip,r.depth,r.brightness,palettes,w,h,colors,depth,alpha);
                else if(r.gradient==2)blitUnit(source,sw,sh,r.source,{r.destination.x,r.destination.y},r.clip,r.depth,r.brightness,palettes,w,h,colors,depth,alpha);
                else throw std::runtime_error("Unexpected split gradient");
            };
            drawBridgeUnitSurface(in,std::uint32_t(b.field494),bs,s);std::cout<<"pixels "<<digest(colors)<<' '<<digest(depth);
        } else throw std::runtime_error("Unknown split command");
        if(!input)throw std::runtime_error("Incomplete split input");input>>std::ws;if(!input.eof())throw std::runtime_error("Trailing split input");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
