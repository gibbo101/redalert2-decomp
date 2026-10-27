// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/VoxelPartStaging.hpp"
#include "assets/Archive.hpp"
#include <openssl/evp.h>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
template<class... T>void output(T... a){((std::cout<<a<<' '),...);}
std::string digest(const Bytes& bytes){unsigned char h[EVP_MAX_MD_SIZE];unsigned size=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),h,&size,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream out;for(unsigned i=0;i<size;++i)out<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return out.str();}
Animation animation(int mode){Animation a;a.frames=mode==2?3:1;a.names={"fixture"};
    for(int n=0;n<a.frames;++n){auto m=voxelIdentity();if(mode==2){m[0]=0.5f+0.25f*n;m[5]=1.25f;m[3]=0.375f*n;m[7]=-0.625f*n;}a.transforms.push_back(m);}return a;}
}
int main(int argc,char** argv){try {
    if(argc!=5)return 2;
    const auto data=readRasterData(readFile(argv[1]));const auto light=readRenderData(readFile(argv[2]));
    const std::filesystem::path assets=argv[3];const auto vpl=readVpl(readFile(assets/"voxels.vpl"));
    const std::array<VoxelModel,3> models={readVxl(readFile(assets/"htnk.vxl")),readVxl(readFile(assets/"htnktur.vxl")),readVxl(readFile(assets/"htnkbarl.vxl"))};
    const auto palette=readPalette(readFile(argv[4]));const auto mapping=stagingRemap(palette,palette);
    const Palette black{};const auto zeroMapping=stagingRemap(black,black);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream input(line);char op;int paletteMode;input>>op>>paletteMode;
        if(paletteMode<0||paletteMode>1)throw std::invalid_argument("Invalid staging palette mode");
        const auto& remap=paletteMode?zeroMapping:mapping;
        if(op=='M'){output("remap");for(auto v:remap)output(unsigned(v));}
        else if(op=='S'){
            unsigned seed;int part,mode;StagedVoxelPartInputs in;in.flags=0;
            input>>seed>>part>>mode>>in.frame>>in.point.x>>in.point.y>>in.clip.x>>in.clip.y>>in.clip.width>>in.clip.height>>in.brightness;
            for(auto& value:in.pose){std::uint32_t bits=0;input>>bits;value=std::bit_cast<float>(bits);}
            if(!input||part<0||part>2||mode<0||mode>2||seed>100000)throw std::invalid_argument("Invalid staging part command");
            Bytes target(65536);for(unsigned i=0;i<target.size();++i)target[i]=std::uint8_t(i*37+seed*19);
            StagedVoxelPartServices s;s.flag204=s.flag205=s.house=s.predicateC0=[]{return std::uint8_t(0);};
            s.kind=[]{};s.value2C0=[]{return -1;};s.value2C4=[]{return 2;};
            auto hva=animation(mode);
            const auto result=drawOrdinaryVoxelPartIntoStaging(data,light,models[std::size_t(part)],mode?&hva:nullptr,vpl,in,s,remap,target);
            output("result");for(auto v:result.rectangle)output(v);output(result.traversal);
            for(auto p:result.corners)for(float v:{p.x,p.y,p.z})output(std::bit_cast<std::uint32_t>(v));
            output(digest(result.pixels),digest(target));
        }else throw std::invalid_argument("Unknown staging part command");
        if(!input)throw std::invalid_argument("Incomplete staging part command");
        input>>std::ws;if(!input.eof())throw std::invalid_argument("Trailing staging part data");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
