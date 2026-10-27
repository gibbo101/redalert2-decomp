// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitStaging.hpp"
#include "render/ShadowCache.hpp"
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
        for(const char* name:{"temperat.pal","isotem.pal"}) {
            const auto path=std::filesystem::path(argv[3])/name;
            if(std::filesystem::is_symlink(argv[3])||std::filesystem::is_symlink(path))throw std::runtime_error("Symlink research export refused");
            for(auto p=std::filesystem::weakly_canonical(path);!p.empty();) {
                if(p==root)throw std::runtime_error("Use output outside source installation");auto next=p.parent_path();if(p==next)break;p=next;
            }
        }
        ra2::AssetStore store(root);
        for(const char* name:{"temperat.pal","isotem.pal"}) {
            const auto data=store.require(name),pathData=std::filesystem::exists(out/name)?ra2::readFile(out/name):ra2::Data{};
            if(std::filesystem::exists(out/name)) {
                if(data.size!=pathData.size||!std::equal(data.ptr(),data.ptr()+data.size,pathData.ptr()))throw std::runtime_error("Different existing research data refused");
            } else {std::filesystem::create_directories(out);std::ofstream f(out/name,std::ios::binary);f.write(reinterpret_cast<const char*>(data.ptr()),std::streamsize(data.size));if(!f)throw std::runtime_error("Research export failed");}
        }
        return 0;
    }
    if(argc!=3)return 2;
    const auto raster=ra2::readRasterData(ra2::readFile(argv[1]));const auto render=ra2::readRenderData(ra2::readFile(argv[2]));
    ra2::ShadowCache cache;int serial=0;std::string op;
    auto palette=[](){ra2::Palette p;for(auto& c:p){unsigned r,g,b;std::cin>>r>>g>>b;c={std::uint8_t(r),std::uint8_t(g),std::uint8_t(b)};}return p;};
    while(std::cin>>op) {
        if(op=="P") {auto a=palette(),b=palette();for(auto v:ra2::stagingRemap(a,b))std::cout<<unsigned(v)<<' ';}
        else if(op=="U") {
            ra2::PixelRect a,b;std::cin>>a.x>>a.y>>a.width>>a.height>>b.x>>b.y>>b.width>>b.height;
            const auto c=ra2::stagingUnion(a,b);std::cout<<c.x<<' '<<c.y<<' '<<c.width<<' '<<c.height;
        } else if(op=="I"||op=="F") {
            int w,h,sw,sh,z=0,bri=1000;ra2::PixelRect s,c;ra2::PixelPoint d;
            std::cin>>w>>h>>sw>>sh>>s.x>>s.y>>s.width>>s.height>>d.x>>d.y>>c.x>>c.y>>c.width>>c.height;
            if(w<1||h<1||w>256||h>256||sw<1||sh<1||sw>256||sh>256)return 5;
            if(op=="F")std::cin>>z>>bri;
            ra2::Bytes source(sw*sh);unsigned x;for(auto& v:source){std::cin>>x;v=std::uint8_t(x);}
            if(op=="I") {
                ra2::Bytes target(w*h);ra2::IndexRemap m;for(auto& v:target){std::cin>>x;v=std::uint8_t(x);}for(auto& v:m){std::cin>>x;v=std::uint8_t(x);}
                ra2::blitIndexed(source,sw,sh,s,d,c,m,w,h,target);std::cout<<hash(target);
            } else {
                std::vector<std::uint16_t> colors(w*h),depth(w*h),alpha(w*h);std::vector<ra2::Palette16> palettes(53);
                for(auto* p:{&colors,&depth,&alpha})for(auto& v:*p)std::cin>>v;for(auto& row:palettes)for(auto& v:row)std::cin>>v;
                ra2::blitUnit(source,sw,sh,s,d,c,z,bri,palettes,w,h,colors,depth,alpha);std::cout<<hash(words(colors))<<' '<<hash(words(depth));
            }
        } else if(op=="A") {
            unsigned bh,th;std::string dir;int profile;std::cin>>dir>>bh>>th>>profile;
            const auto iso=ra2::readPalette(ra2::readFile(dir+"/temperat.pal"));const auto m=ra2::stagingRemap(iso,iso);
            const auto vpl=ra2::readVpl(ra2::readFile(dir+"/voxels.vpl"));ra2::UnitStaging stage;
            const auto body=ra2::voxelBodyMatrix(raster,std::uint16_t(bh)),turret=ra2::voxelTurretMatrix(raster,std::uint16_t(bh),std::uint16_t(th)),cam=ra2::voxelCameraMatrix(raster);
            std::array<ra2::VoxelModel,3> models;std::array<ra2::RasterFrame,3> frames;const std::array<std::string,3> names={"htnk","htnktur","htnkbarl"};
            for(int i=0;i<3;++i) {
                models[i]=ra2::readVxl(ra2::readFile(dir+"/"+names[i]+".vxl"));const auto pose=ra2::voxelMultiply(cam,i?turret:body);
                frames[i]=ra2::rasterVoxel(raster,models[i].sections.at(0),pose,ra2::voxelSectionShades(raster,render,models[i].sections[0].normalType,pose),vpl);
            }
            stage.add(frames[0],m);stage.add(frames[ra2::barrelAfterTurret(std::uint16_t(th))?1:2],m);stage.add(frames[ra2::barrelAfterTurret(std::uint16_t(th))?2:1],m);
            const auto b=stage.dirty;std::cout<<b.x<<' '<<b.y<<' '<<b.width<<' '<<b.height<<' '<<hash(stage.pixels)<<' ';
            const auto sh=ra2::rasterVoxelShadow(models[0].sections[0],body,cam,ra2::voxelShadowOffset(raster,render.lightAngle),{stage.pixels,256,256,{}});
            std::cout<<hash(sh.pixels)<<' ';
            constexpr int w=96,h=80;std::vector<std::uint16_t> colors(w*h),depth(w*h),alpha(w*h);std::vector<ra2::Palette16> palettes(53);
            for(int i=0;i<w*h;++i){colors[i]=std::uint16_t(i*71);depth[i]=profile?std::uint16_t(32700+(i%99)):65535;alpha[i]=std::uint16_t(i%256);}
            for(int i=0;i<53;++i)for(int j=0;j<256;++j)palettes[i][j]=std::uint16_t((i<<8)|j);
            const ra2::PixelRect clip=profile?ra2::PixelRect{3,5,80,64}:ra2::PixelRect{0,0,w,h};
            ra2::blitUnit(stage.pixels,256,256,b,{48+b.x-128,50+b.y-128},clip,-1,1000,palettes,w,h,colors,depth,alpha);
            const auto& sb=sh.rectangle;ra2::blitShadow(sh.pixels,256,256,{sb[2],sb[3],sb[4],sb[5]},{48+sb[0],50+sb[1]},clip,-1,w,h,colors,depth);
            std::cout<<hash(words(colors))<<' '<<hash(words(depth));
        } else if(op=="N") {cache=ra2::ShadowCache{};serial=0;std::cout<<"reset";}
        else if(op=="K") {
            ra2::ShadowRequest r;std::cin>>r.key>>r.actorSuppressed>>r.noShadow>>r.modelUnavailable>>r.cacheAvailable>>r.disableCache>>r.allowBuild;
            bool built=false;int id=0;const auto result=cache.draw(r,[&](){built=true;id=(r.key==-1||!r.cacheAvailable||r.disableCache)?0:++serial;ra2::RasterFrame b;b.traversal=id;return b;});
            if(built){std::cout<<"render "<<!result.bypass<<" 8193 ";if(!result.bypass)std::cout<<"snapshot "<<id<<' ';}
            if(result.frame&&!result.bypass)std::cout<<"cached "<<result.frame->traversal<<" 8193 1000 ";
            std::cout<<"state "<<cache.size()<<' '<<cache.capacity()<<' '<<cache.sorted()<<' ';if(cache.hotKey())std::cout<<*cache.hotKey();else std::cout<<"None";
            for(auto key:cache.keys())std::cout<<' '<<key;
        } else return 3;
        if(!std::cin)return 4;std::cout<<'\n';
    }
 }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
