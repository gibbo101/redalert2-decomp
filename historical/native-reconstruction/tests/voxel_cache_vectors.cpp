// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/VoxelCache.hpp"
#include "render/UnitLighting.hpp"
#include <openssl/evp.h>
#include <iomanip>
#include <iostream>
#include <sstream>
std::string hash(const ra2::Bytes& bytes) {
    unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;EVP_Digest(bytes.data(),bytes.size(),h,&n,EVP_sha256(),nullptr);
    std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return s.str();
}
int main(int argc,char** argv) {
 try {
    if(argc!=3)return 2;const auto raster=ra2::readRasterData(ra2::readFile(argv[1]));const auto render=ra2::readRenderData(ra2::readFile(argv[2]));
    ra2::VoxelCache cache;std::array<ra2::VoxelCache,3> parts;int serial=0;std::string op;
    while(std::cin>>op) {
        if(op=="O"){cache={};parts={};serial=0;std::cout<<"reset";}
        else if(op=="K") {
            std::int32_t loco;int frame,offset;unsigned heading;std::cin>>loco>>frame>>heading>>offset;
            const auto body=ra2::bodyVoxelKey(loco,frame);std::cout<<body<<' '<<ra2::turretVoxelKey(body,std::uint16_t(heading),offset);
        } else if(op=="D") {
            std::int32_t key;bool available,disabled,valid;int frame,brightness;std::cin>>key>>available>>disabled>>valid>>frame>>brightness;
            const auto result=cache.draw({key,available,disabled,valid},[&]{ra2::RasterFrame f;f.pixels.resize(1);f.pixels[0]=std::uint8_t(serial+1);return f;});
            if(result.built) {
                std::cout<<"render "<<frame<<" 0 "<<ra2::unitBrightnessEffect(brightness,0)<<' ';
                if(!result.bypass)std::cout<<"snapshot "<<++serial<<' ';
            } else if(result.frame)std::cout<<"cached "<<unsigned(result.frame->pixels[0])<<" 0 "<<brightness<<' ';
            std::cout<<"state "<<cache.size()<<' '<<cache.capacity()<<' '<<int(cache.sorted())<<' ';
            if(cache.hotKey())std::cout<<*cache.hotKey();else std::cout<<"None";
            for(auto k:cache.keys())std::cout<<' '<<k;
        } else if(op=="R") {
            std::string dir;unsigned bh,th;int part;bool disabled;std::cin>>dir>>part>>bh>>th>>disabled;if(part<0||part>2)return 4;
            const auto key=ra2::bodyVoxelKey(ra2::voxelHeading(std::uint16_t(bh)),0);const auto selected=part?ra2::turretVoxelKey(key,std::uint16_t(th),0):key;
            const auto result=parts[part].draw({selected,true,disabled,true},[&]{
                const auto name=std::array<const char*,3>{"htnk","htnktur","htnkbarl"}[part];
                const auto model=ra2::readVxl(ra2::readFile(dir+"/"+name+".vxl"));const auto vpl=ra2::readVpl(ra2::readFile(dir+"/voxels.vpl"));
                const auto pose=ra2::voxelMultiply(ra2::voxelCameraMatrix(raster),part?ra2::voxelTurretMatrix(raster,std::uint16_t(bh),std::uint16_t(th)):ra2::voxelBodyMatrix(raster,std::uint16_t(bh)));
                return ra2::rasterVoxel(raster,model.sections[0],pose,ra2::voxelSectionShades(raster,render,model.sections[0].normalType,pose),vpl);
            });
            std::cout<<selected<<' '<<int(result.built)<<' '<<int(result.bypass)<<' '<<hash(result.frame->pixels);
            for(auto coordinate:result.frame->rectangle)std::cout<<' '<<coordinate;
        } else return 3;
        if(!std::cin)return 5;std::cout<<'\n';
    }
 }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
