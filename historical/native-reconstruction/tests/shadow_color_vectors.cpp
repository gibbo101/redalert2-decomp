// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/PlayerColor.hpp"
#include "render/VoxelShadow.hpp"
#include "assets/Archive.hpp"
#include <openssl/evp.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
std::string hash(const ra2::Bytes& b) {
    unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;EVP_Digest(b.data(),b.size(),h,&n,EVP_sha256(),nullptr);
    std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return s.str();
}
ra2::Bytes words(const std::vector<std::uint16_t>& v){ra2::Bytes b;for(auto x:v){b.push_back(std::uint8_t(x));b.push_back(std::uint8_t(x>>8));}return b;}
int main(int argc,char** argv) {
 try {
    if(argc==4&&std::string(argv[1])=="--export") {
        const auto root=std::filesystem::weakly_canonical(argv[2]),out=std::filesystem::weakly_canonical(argv[3]);
        for(const char* name:{"unittem.pal","rules.ini"}) {
            const auto path=std::filesystem::path(argv[3])/name;
            if(std::filesystem::is_symlink(argv[3])||std::filesystem::is_symlink(path))throw std::runtime_error("Symlink research export refused");
            for(auto p=std::filesystem::weakly_canonical(path);!p.empty();) {
                if(p==root)throw std::runtime_error("Use output outside source installation");auto next=p.parent_path();if(p==next)break;p=next;
            }
        }
        ra2::AssetStore store(root);
        for(const char* name:{"unittem.pal","rules.ini"}) {
            const auto data=store.require(name),pathData=std::filesystem::exists(out/name)?ra2::readFile(out/name):ra2::Data{};
            if(std::filesystem::exists(out/name)) {
                if(data.size!=pathData.size||!std::equal(data.ptr(),data.ptr()+data.size,pathData.ptr()))throw std::runtime_error("Different existing research data refused");
            } else {std::filesystem::create_directories(out);std::ofstream f(out/name,std::ios::binary);f.write(reinterpret_cast<const char*>(data.ptr()),std::streamsize(data.size));if(!f)throw std::runtime_error("Research export failed");}
        }
        return 0;
    }
    if(argc!=2)return 2;const auto data=ra2::readRasterData(ra2::readFile(argv[1]));std::string op;
    while(std::cin>>op) {
        if(op=="H"||op=="C") {
            unsigned h,s,v;std::cin>>h>>s>>v;ra2::HsvColor hsv{std::uint8_t(h),std::uint8_t(s),std::uint8_t(v)};
            if(op=="H"){const auto c=ra2::originalHsvToRgb(hsv);std::cout<<unsigned(c.r)<<' '<<unsigned(c.g)<<' '<<unsigned(c.b);}
            else {std::string path;std::cin>>path;const auto pal=ra2::playerPalette(data,ra2::readPalette(ra2::readFile(path)),hsv);for(auto c:pal)std::cout<<unsigned(c.r)<<' '<<unsigned(c.g)<<' '<<unsigned(c.b)<<' ';}
        } else if(op=="O") {
            float angle;std::cin>>angle;const auto v=ra2::voxelShadowOffset(data,angle);for(float x:{v.x,v.y,v.z})std::cout<<std::bit_cast<std::uint32_t>(x)<<' ';
        } else if(op=="M") {
            unsigned h;std::cin>>h;for(float x:ra2::voxelBodyMatrix(data,std::uint16_t(h)))std::cout<<std::bit_cast<std::uint32_t>(x)<<' ';std::cout<<ra2::voxelHeading(std::uint16_t(h));
        } else if(op=="R") {
            std::string path;ra2::Matrix model,camera;ra2::Vec3 offset;int style,x,y;
            std::cin>>path;for(float& v:model)std::cin>>v;for(float& v:camera)std::cin>>v;std::cin>>offset.x>>offset.y>>offset.z>>style>>x>>y;
            ra2::Bytes stencil;if(style>=0){stencil.resize(65536);for(int j=0;j<256;++j)for(int i=0;i<256;++i)stencil[j*256+i]=std::uint8_t((i*3+j*7+style)%5<2?37:0);}
            const auto vxl=ra2::readVxl(ra2::readFile(path));if(vxl.sections.size()!=1)throw std::runtime_error("Oracle expects one section");
            const auto frame=ra2::rasterVoxelShadow(vxl.sections[0],model,camera,offset,{stencil,256,256,{x,y}});
            for(int v:frame.rectangle)std::cout<<v<<' ';for(int i=0;i<4;++i)for(float v:{frame.corners[i].x,frame.corners[i].y,frame.corners[i].z})std::cout<<std::bit_cast<std::uint32_t>(v)<<' ';
            std::cout<<hash(frame.pixels);
        } else if(op=="B") {
            int w,h,sw,sh,z;ra2::PixelRect s,c;ra2::PixelPoint d;std::cin>>w>>h>>sw>>sh>>s.x>>s.y>>s.width>>s.height>>d.x>>d.y>>c.x>>c.y>>c.width>>c.height>>z;
            ra2::Bytes source(std::size_t(sw)*sh);std::vector<std::uint16_t> colors(std::size_t(w)*h),depth(colors.size());
            unsigned x;for(auto& v:source){std::cin>>x;v=std::uint8_t(x);}for(auto& v:colors){std::cin>>x;v=std::uint16_t(x);}for(auto& v:depth){std::cin>>x;v=std::uint16_t(x);}
            ra2::blitShadow(source,sw,sh,s,d,c,z,w,h,colors,depth);std::cout<<hash(words(colors))<<' '<<hash(words(depth));
        } else return 3;
        if(!std::cin)return 4;std::cout<<'\n';
    }
 }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
