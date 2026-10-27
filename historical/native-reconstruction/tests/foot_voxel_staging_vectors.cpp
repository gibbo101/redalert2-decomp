// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/FootVoxelStaging.hpp"
#include "assets/Archive.hpp"
#include <openssl/evp.h>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
template<class... T>void out(T... v){((std::cout<<v<<' '),...);}
std::string digest(const Bytes& b){unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;if(!EVP_Digest(b.data(),b.size(),h,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return s.str();}
}
int main(int argc,char** argv){try{
    if(argc!=5)return 2;
    const auto data=readRasterData(readFile(argv[1]));const auto light=readRenderData(readFile(argv[2]));
    const std::filesystem::path assets=argv[3];const auto vpl=readVpl(readFile(assets/"voxels.vpl"));
    const std::array<VoxelModel,3> models={readVxl(readFile(assets/"htnk.vxl")),readVxl(readFile(assets/"htnktur.vxl")),readVxl(readFile(assets/"htnkbarl.vxl"))};
    const auto palette=readPalette(readFile(argv[4]));const Palette black{};const std::array<IndexRemap,2> maps={stagingRemap(palette,palette),stagingRemap(black,black)};
    Animation hva;hva.frames=1;hva.names={"fixture"};hva.transforms={voxelIdentity()};
    VoxelSnapshotIndex index;VoxelSnapshotPool pool{Bytes(0x80000,0xa5)};
    StagedVoxelPartServices services;services.flag204=services.flag205=services.house=services.predicateC0=[]{return std::uint8_t(0);};services.kind=[]{};
    services.value2C4=[]{return 2;};services.value2C0=[]{return -1;};services.selectBlitter=[](auto){};
    std::string line;while(std::getline(std::cin,line)){std::istringstream input(line);char op=0;input>>op;
        if(op=='O'){index={};pool={Bytes(0x80000,0xa5)};out("reset");}
        else if(op=='D'){
            int pm=0,part=0,available=0,disabled=0,valid=0,has=0;unsigned seed=0;FootLitRequest r;UnitStaging stage;
            input>>pm>>seed>>part>>r.key>>available>>disabled>>valid>>has>>r.frame>>r.brightness>>r.point.x>>r.point.y
                 >>r.clip.x>>r.clip.y>>r.clip.width>>r.clip.height>>stage.dirty.x>>stage.dirty.y>>stage.dirty.width>>stage.dirty.height;
            for(auto& f:r.pose){std::uint32_t b=0;input>>b;f=std::bit_cast<float>(b);}
            if(!input||pm<0||pm>1||part<0||part>2||seed>100000)throw std::invalid_argument("Invalid joined Foot staging input");
            r.flags=0x2800;r.model=1;r.cache=available?1:0;
            for(unsigned i=0;i<stage.pixels.size();++i)stage.pixels[i]=std::uint8_t(i*37+seed*19);
            const auto result=drawOrdinaryFootVoxelPart(data,light,valid?&models[std::size_t(part)]:nullptr,valid?&hva:nullptr,vpl,r,
                has!=0,disabled!=0,available?&index:nullptr,pool,services,maps[std::size_t(pm)],stage);
            out("draw",int(result.kind),stage.dirty.x,stage.dirty.y,stage.dirty.width,stage.dirty.height,
                result.raster?digest(result.raster->pixels):"-",digest(stage.pixels),"pool",pool.cursor,digest(pool.bytes),
                "state",index.size(),index.capacity(),int(index.sorted()));
            if(index.hotKey())out(*index.hotKey());else out("None");for(auto key:index.keys())out(key);
        }else throw std::invalid_argument("Unknown joined Foot staging command");
        if(!input)throw std::invalid_argument("Incomplete joined Foot staging command");input>>std::ws;if(!input.eof())throw std::invalid_argument("Trailing joined Foot staging input");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
