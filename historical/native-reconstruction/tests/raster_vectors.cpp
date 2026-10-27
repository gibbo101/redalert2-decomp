// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/VoxelRaster.hpp"
#include "render/Lighting.hpp"
#include "assets/Archive.hpp"
#include <openssl/evp.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
std::string digest(const ra2::Bytes& b) {unsigned char hash[EVP_MAX_MD_SIZE];unsigned n=0;EVP_Digest(b.data(),b.size(),hash,&n,EVP_sha256(),nullptr);std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(hash[i]);return s.str();}
int main(int argc,char** argv) {
 try {
    if(argc==4&&std::string(argv[1])=="--export") {
        if(std::filesystem::is_symlink(argv[3]))throw std::runtime_error("Use output outside the source installation; symlink export refused");
        auto root=std::filesystem::weakly_canonical(argv[2]),output=std::filesystem::weakly_canonical(argv[3]);
        for(auto p=output;!p.empty();) {if(p==root)throw std::runtime_error("Use output outside the source installation");auto next=p.parent_path();if(next==p)break;p=next;}
        for(const char* name:{"htnk.vxl","htnktur.vxl","htnkbarl.vxl","voxels.vpl"}) {
            if(std::filesystem::is_symlink(output/name))throw std::runtime_error("Use output outside the source installation; symlink export refused");
            for(auto p=std::filesystem::weakly_canonical(output/name);!p.empty();) {
                if(p==root)throw std::runtime_error("Use output outside the source installation");
                auto next=p.parent_path();if(next==p)break;p=next;
            }
        }
        ra2::AssetStore store(root);
        for(const char* name:{"htnk.vxl","htnktur.vxl","htnkbarl.vxl","voxels.vpl"}) {
            const auto data=store.require(name);const auto path=output/name;
            if(std::filesystem::exists(path)) {auto old=ra2::readFile(path);if(old.size!=data.size||!std::equal(old.ptr(),old.ptr()+old.size,data.ptr()))throw std::runtime_error("Refusing different existing research data");}
            else {std::filesystem::create_directories(output);std::ofstream f(path,std::ios::binary);f.write(reinterpret_cast<const char*>(data.ptr()),std::streamsize(data.size));if(!f)throw std::runtime_error("Research export failed");}
        }
        return 0;
    }
    if(argc!=2&&argc!=3)return 2;
    const auto data=ra2::readRasterData(ra2::readFile(argv[1]));
    const auto renderPath=argc==3?argv[2]:"private/derived/render-data.bin";
    std::string op;
    while(std::cin>>op) {
        if(op=="L") {
            std::string path;std::cin>>path;
            const auto model=ra2::readVxl(ra2::readFile(path));
            std::cout<<model.sections.size()<<' ';
            for(const auto& s:model.sections) {
                for(int v:s.size)std::cout<<v<<' ';std::cout<<s.normalType<<' ';
                std::cout<<std::bit_cast<std::uint32_t>(s.scale)<<' ';
                for(float v:s.base)std::cout<<std::bit_cast<std::uint32_t>(v)<<' ';
                const ra2::Vec3 corners[]={{s.max.x,s.max.y,s.min.z},{s.max.x,s.min.y,s.min.z},{s.min.x,s.min.y,s.min.z},{s.min.x,s.max.y,s.min.z},
                    {s.max.x,s.max.y,s.max.z},{s.max.x,s.min.y,s.max.z},{s.min.x,s.min.y,s.max.z},{s.min.x,s.max.y,s.max.z}};
                for(auto p:corners)for(float v:{p.x,p.y,p.z})std::cout<<std::bit_cast<std::uint32_t>(v)<<' ';
                ra2::Bytes spans;
                for(const auto& span:s.spans) {
                    auto size=std::uint32_t(span.size());
                    for(unsigned shift=0;shift<32;shift+=8)spans.push_back(std::uint8_t(size>>shift));
                    spans.insert(spans.end(),span.begin(),span.end());
                }
                std::cout<<digest(spans)<<' ';
            }
        } else if(op=="M") {
            unsigned body,turret;std::cin>>body>>turret;
            for(const auto& m:{ra2::voxelBodyMatrix(data,std::uint16_t(body)),ra2::voxelTurretMatrix(data,std::uint16_t(body),std::uint16_t(turret)),ra2::voxelCameraMatrix(data)})
                for(float v:m)std::cout<<std::bit_cast<std::uint32_t>(v)<<' ';
        } else if(op=="P") {
            ra2::Matrix a,b;for(auto& v:a)std::cin>>v;for(auto& v:b)std::cin>>v;
            for(float v:ra2::voxelMultiply(a,b))std::cout<<std::bit_cast<std::uint32_t>(v)<<' ';
        } else if(op=="S") {
            int type;std::cin>>type;ra2::Matrix m;for(auto& v:m)std::cin>>v;
            const auto light=ra2::readRenderData(ra2::readFile(renderPath));
            for(auto v:ra2::voxelSectionShades(data,light,type,m))std::cout<<unsigned(v)<<' ';
        } else if(op=="D") {
            std::string path,vplPath;ra2::Matrix m;std::cin>>path>>vplPath;for(auto& v:m)std::cin>>v;
            std::array<std::uint8_t,256> shades;for(auto& v:shades){unsigned x;std::cin>>x;v=std::uint8_t(x);}
            const auto model=ra2::readVxl(ra2::readFile(path));const auto vpl=ra2::readVpl(ra2::readFile(vplPath));
            if(model.sections.size()!=1)throw std::runtime_error("Oracle expects one section");
            auto frame=ra2::rasterVoxel(data,model.sections[0],m,shades,vpl);
            for(int v:frame.rectangle)std::cout<<v<<' ';std::cout<<frame.traversal<<' ';
            for(auto p:frame.corners)for(float v:{p.x,p.y,p.z})std::cout<<std::bit_cast<std::uint32_t>(v)<<' ';
            std::cout<<digest(frame.pixels);
        } else return 3;
        if(!std::cin)return 4;std::cout<<'\n';
    }
 } catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
