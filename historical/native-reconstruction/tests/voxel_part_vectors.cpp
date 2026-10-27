// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/VoxelPartDraw.hpp"
#include "assets/Archive.hpp"
#include <openssl/evp.h>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
template<class... T>void event(T... a){((std::cout<<a<<' '),...);}
void rect(PixelRect r){event(r.x,r.y,r.width,r.height);}
std::string digest(const Bytes& b){unsigned char hash[EVP_MAX_MD_SIZE];unsigned n=0;
    EVP_Digest(b.data(),b.size(),hash,&n,EVP_sha256(),nullptr);std::ostringstream out;
    for(unsigned i=0;i<n;++i)out<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(hash[i]);return out.str();}
Animation animation(int mode){Animation a;a.frames=mode==2?3:1;a.names={"fixture"};
    for(int n=0;n<a.frames;++n){auto m=voxelIdentity();if(mode==2){m[0]=0.5f+0.25f*n;m[5]=1.25f;m[3]=0.375f*n;m[7]=-0.625f*n;}a.transforms.push_back(m);}return a;}
}
int main(int argc,char** argv){try {
    if(argc!=4)return 2;
    const auto data=readRasterData(readFile(argv[1]));const auto light=readRenderData(readFile(argv[2]));
    const std::filesystem::path assets=argv[3];const auto vpl=readVpl(readFile(assets/"voxels.vpl"));
    const std::array<VoxelModel,3> models={readVxl(readFile(assets/"htnk.vxl")),readVxl(readFile(assets/"htnktur.vxl")),readVxl(readFile(assets/"htnkbarl.vxl"))};
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream input(line);char op;int part,mode,f204,f205,house,predicate,c4,c0;
        std::uint32_t adjusted;StagedVoxelPartInputs in;
        input>>op>>part>>mode>>in.frame>>in.point.x>>in.point.y>>in.clip.x>>in.clip.y>>in.clip.width>>in.clip.height
             >>in.brightness>>in.flags>>f204>>f205>>house>>predicate>>adjusted>>c4>>c0;
        for(auto& value:in.pose){std::uint32_t bits;input>>bits;value=std::bit_cast<float>(bits);}
        if(!input||op!='P'||part<0||part>2||mode<0||mode>2)throw std::invalid_argument("Invalid staged part command");
        input>>std::ws;if(!input.eof())throw std::invalid_argument("Trailing staged part input");
        auto hva=animation(mode);StagedVoxelPartServices s;
        s.flag204=[&](){event("f204");return std::uint8_t(f204);};s.flag205=[&](){event("f205");return std::uint8_t(f205);};
        s.house=[&](){event("house");return std::uint8_t(house);};s.predicateC0=[&](){event("c0");return std::uint8_t(predicate);};
        s.adjustFlags=[&](auto f){event("adjust",f);return adjusted;};s.kind=[](){event("kind");};
        s.value2C4=[&](){event("v2c4");return c4;};s.value2C0=[&](){event("v2c0");return c0;};
        s.selectBlitter=[](auto f){event("select",f);};
        s.draw=[](const RasterFrame& frame,PixelPoint at,PixelRect clip,int c0,int c4,int brightness){
            event("draw");for(int n=2;n<6;++n)event(frame.rectangle[n]);event(at.x,at.y);rect(clip);event(c0,c4,brightness,0);
        };
        const auto result=drawStagedVoxelPart(data,light,models[std::size_t(part)],mode?&hva:nullptr,vpl,in,s);
        event("result");for(int v:result.rectangle)event(v);event(result.traversal);
        for(auto p:result.corners)for(float v:{p.x,p.y,p.z})event(std::bit_cast<std::uint32_t>(v));
        event(digest(result.pixels));std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
