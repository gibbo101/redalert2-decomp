// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/ShadowKeys.hpp"
#include "render/ShadowCache.hpp"
#include "render/VoxelShadow.hpp"
#include "assets/GameAssets.hpp"
#include <openssl/evp.h>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
std::string hash(const ra2::Bytes& bytes) {
    unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;EVP_Digest(bytes.data(),bytes.size(),h,&n,EVP_sha256(),nullptr);
    std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return s.str();
}
int main(int argc,char** argv) {
 try {
    if(argc!=3)return 2;
    const auto raster=ra2::readRasterData(ra2::readFile(argv[1]));const auto render=ra2::readRenderData(ra2::readFile(argv[2]));
    ra2::ShadowCache cache;std::string op;
    while(std::cin>>op) {
        if(op=="K") {
            std::int32_t body;unsigned heading;int y,speed;bool balloon;std::cin>>body>>heading>>y>>speed>>balloon;
            std::cout<<ra2::flatUnitShadowKey(body,std::uint16_t(heading),y,speed,balloon);
            for(float f:ra2::voxelBodyMatrix(raster,std::uint16_t(heading)))std::cout<<' '<<std::bit_cast<std::uint32_t>(f);
        } else if(op=="D") {
            int current;bool crusher;std::cin>>current>>crusher;std::cout<<ra2::unitSpeedTypeDefault(current,crusher);
        } else if(op=="G") {
            ra2::PixelPoint at;std::cin>>at.x>>at.y;
            const auto result=ra2::footShadowPlacement(at,{0,0},true,1);std::cout<<1<<' '<<result->x<<' '<<result->y;
        } else if(op=="F") {
            ra2::PixelPoint at,offset;bool has;unsigned predicate;std::cin>>at.x>>at.y>>offset.x>>offset.y>>has>>predicate;
            const auto result=ra2::footShadowPlacement(at,offset,has,std::uint8_t(predicate));
            std::cout<<int(bool(result));if(result)std::cout<<' '<<result->x<<' '<<result->y;
        } else if(op=="O") {cache={};std::cout<<"reset";}
        else if(op=="R") {
            std::string dir;std::int32_t body;unsigned heading;int style;std::cin>>dir>>body>>heading>>style;
            const auto key=ra2::flatUnitShadowKey(body,std::uint16_t(heading));
            const auto result=cache.draw({key},[&]{
                const auto model=ra2::readVxl(ra2::readFile(dir+"/htnk.vxl"));ra2::Bytes stencil(65536);
                for(int y=0;y<256;++y)for(int x=0;x<256;++x)stencil[y*256+x]=(x*3+y*7+style)%5<2?37:0;
                return ra2::rasterVoxelShadow(model.sections[0],ra2::voxelBodyMatrix(raster,std::uint16_t(heading)),ra2::voxelCameraMatrix(raster),
                    ra2::voxelShadowOffset(raster,render.lightAngle),{stencil,256,256,{0,0}});
            });
            std::cout<<key<<' '<<int(result.built)<<' '<<hash(result.frame->pixels);
            for(int p:result.frame->rectangle)std::cout<<' '<<p;
        } else return 3;
        if(!std::cin)return 4;std::cout<<'\n';
    }
 }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
