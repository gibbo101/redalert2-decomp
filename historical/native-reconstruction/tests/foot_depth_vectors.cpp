// SPDX-License-Identifier: GPL-3.0-or-later
#include "foot_depth_fixture.hpp"
#include "render/UnitSurfaceDraw.hpp"
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>
using namespace ra2;
namespace {
void fixture(std::istream& in,DepthFixture& f){in>>f.seed>>f.x>>f.y>>f.bridge>>f.tileBase>>f.invalidX>>f.invalidY>>f.count;f.prepare();}
int predicate(const FootDepthWorld& w,int kind){
    switch(kind){case 0:return footDepthPredicate0(w);case 1:return footDepthPredicate1(w);case 2:return footDepthPredicate2(w);
    case 3:return footDepthFlag(w);case 4:return footDepthFlag(w,true);default:throw std::runtime_error("Unknown depth predicate");}
}
std::string digest(const std::vector<std::uint16_t>& plane){
    Bytes bytes;for(auto v:plane){bytes.push_back(v&255);bytes.push_back(v>>8);}
    unsigned char h[EVP_MAX_MD_SIZE];unsigned size=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),h,&size,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream out;for(unsigned i=0;i<size;++i)out<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return out.str();
}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op;in>>op;
        if(op=='Q'){
            int kind;DepthFixture f;in>>kind;fixture(in,f);const auto w=f.world();const auto result=predicate(w,kind);std::cout<<"value "<<result;
        }else if(op=='F'||op=='N'||op=='K'){
            DepthFixture f;if(op!='F')fixture(in,f);const auto w=f.world();
            int has,mode,ld,lg,base,p0=0,p1=0,p2=0,p3=0;FootDepthType t;
            in>>has>>mode>>ld>>lg>>t.b60>>t.b64>>t.b5c>>t.b68;
            if(op=='F')in>>p0>>p1>>p2>>p3;in>>base;
            FootDepthServices s;
            s.locomotorDepth=[&]{std::cout<<"loco_depth ";return mode?0:ld;};
            s.locomotorGradient=[&]{std::cout<<"loco_gradient ";return mode?2:lg;};
            s.type=[&]{std::cout<<"type ";return t;};
            s.predicate0=[&]{if(op!='F')return footDepthPredicate0(w);std::cout<<"p0 ";return p0;};
            s.predicate1=[&]{if(op!='F')return footDepthPredicate1(w);std::cout<<"p1 ";return p1;};
            s.predicate2=[&]{if(op!='F')return footDepthPredicate2(w);std::cout<<"p2 ";return p2;};
            s.predicate3=[&]{if(op!='F')return std::uint8_t(footDepthFlag(w));std::cout<<"p3 ";return std::uint8_t(p3);};
            s.baseDepth=[&]{std::cout<<"base ";if(op=='K'){
                if(f.seed||f.bridge||base!=-1)throw std::runtime_error("K requires healthy flat fixture");
                return flatUnitDepthAdjust(0.125,0);
            }return base;};
            const auto z=footDepthAdjustment(has!=0,s);std::cout<<"depth "<<z<<" gradient ";const auto g=footDepthGradient(has!=0,s);std::cout<<g;
        }else if(op=='P'){
            int n,w,h,sw,sh,z,scheme;UnitSurfaceInputs input;
            in>>n>>w>>h>>sw>>sh>>input.dirty.x>>input.dirty.y>>input.dirty.width>>input.dirty.height
              >>input.point.x>>input.point.y>>input.clip.x>>input.clip.y>>input.clip.width>>input.clip.height>>z>>input.brightness>>scheme;
            if(w<1||h<1||w>128||h>128||sw<1||sh<1||sw>256||sh>256||n<0||n>100000||scheme<0||scheme>7||z!=-1)throw std::runtime_error("Bad nested depth fixture");
            Bytes source(sw*sh);std::vector<std::uint16_t> colors(w*h),depth(w*h),alpha(w*h);std::vector<Palette16> palettes(53);
            constexpr unsigned depths[]={0,32720,32740,32760,32768,32780,65535};
            for(std::size_t i=0;i<source.size();++i)source[i]=i%7?std::uint8_t(i*13+unsigned(n)):0;
            for(std::size_t i=0;i<colors.size();++i){colors[i]=std::uint16_t(i*37+unsigned(n)*91);depth[i]=std::uint16_t(depths[(i+unsigned(n))%7]);alpha[i]=std::uint16_t((i*17+unsigned(n)*11)&255);}
            for(unsigned row=0;row<53;++row)for(unsigned i=0;i<256;++i)palettes[row][i]=std::uint16_t(unsigned(scheme)*257+row*599+i*131);
            DepthFixture f;f.logging=false;f.prepare();const auto world=f.world();FootDepthServices ds;
            ds.locomotorDepth=[]{return 0;};ds.locomotorGradient=[]{return 2;};ds.type=[]{return FootDepthType{};};
            ds.predicate0=[&]{return footDepthPredicate0(world);};ds.predicate1=[&]{return footDepthPredicate1(world);};
            ds.predicate2=[&]{return footDepthPredicate2(world);};ds.predicate3=[&]{return std::uint8_t(footDepthFlag(world));};ds.baseDepth=[]{return flatUnitDepthAdjust(0.125,0);};
            UnitSurfaceServices s;s.layer=[]{return 0;};s.flag204=s.flag205=s.disguised=[]{return std::uint8_t(0);};s.ownerVisible=[]{return false;};
            s.houseBlitter=[](auto flags){return unitSurfaceBlitterSlot(flags);};s.gradient=[&]{return footDepthGradient(true,ds);};s.depth=[&]{return footDepthAdjustment(true,ds);};
            s.sourceBounds=[&]{return PixelRect{0,0,sw,sh};};s.draw=[&](const UnitSurfaceRequest& r){
                if(r.blitter!=0x98||r.gradient!=2||r.extra)throw std::runtime_error("Unexpected ordinary blitter");
                blitUnit(source,sw,sh,r.source,{r.destination.x,r.destination.y},r.clip,r.depth,r.brightness,palettes,w,h,colors,depth,alpha);
            };
            drawOrdinaryUnitSurface(input,s);std::cout<<"pixels "<<digest(colors)<<' '<<digest(depth);
        }else throw std::runtime_error("Unknown Foot depth command");
        if(!in)throw std::runtime_error("Incomplete Foot depth command");in>>std::ws;
        if(!in.eof())throw std::runtime_error("Trailing Foot depth command data");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
