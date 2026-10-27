// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/Composition.hpp"
#include "assets/Archive.hpp"
#include <openssl/evp.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>
std::string digest(const std::vector<std::uint16_t>& plane) {
    ra2::Bytes bytes;bytes.reserve(plane.size()*2);for(auto v:plane){bytes.push_back(v&255);bytes.push_back(v>>8);}
    unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;EVP_Digest(bytes.data(),bytes.size(),h,&n,EVP_sha256(),nullptr);std::ostringstream s;
    for(unsigned i=0;i<n;++i)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return s.str();
}
int main(int argc,char** argv) {
 try {
    if(argc==4&&std::string(argv[1])=="--export") {
        if(std::filesystem::is_symlink(argv[3]))throw std::runtime_error("Use output outside the source installation; symlink refused");
        const auto root=std::filesystem::weakly_canonical(argv[2]),dir=std::filesystem::weakly_canonical(argv[3]);
        for(auto p=dir;!p.empty();){if(p==root)throw std::runtime_error("Use output outside the source installation");auto next=p.parent_path();if(p==next)break;p=next;}
        for(const char* name:{"clear01.tem","cliff01.tem","slope01.tem"})if(std::filesystem::is_symlink(dir/name))throw std::runtime_error("Use output outside the source installation; symlink refused");
        ra2::AssetStore store(root);
        for(const char* name:{"clear01.tem","cliff01.tem","slope01.tem"}) {
            const auto path=dir/name;if(std::filesystem::is_symlink(path))throw std::runtime_error("Use output outside the source installation; symlink refused");
            const auto data=store.require(name);
            if(std::filesystem::exists(path)){auto old=ra2::readFile(path);if(old.size!=data.size||!std::equal(old.ptr(),old.ptr()+old.size,data.ptr()))throw std::runtime_error("Refusing different existing research data");}
            else {std::filesystem::create_directories(dir);std::ofstream f(path,std::ios::binary);f.write(reinterpret_cast<const char*>(data.ptr()),std::streamsize(data.size));if(!f)throw std::runtime_error("Research export failed");}
        }return 0;
    }
    if(argc!=1&&argc!=3)throw std::runtime_error("Usage: composition-vectors [RASTER_DATA RENDER_DATA]");
    const auto raster=ra2::readRasterData(ra2::readFile(argc==3?argv[1]:"private/derived/raster-data.bin"));const auto render=ra2::readRenderData(ra2::readFile(argc==3?argv[2]:"private/derived/render-data.bin"));const auto scale=ra2::worldHeightScale(raster,render);
    std::string op;
    while(std::cin>>op) {
        if(op=="P"){ra2::Coord c;std::cin>>c.x>>c.y>>c.z;auto p=ra2::worldPixels(scale,c);std::cout<<p.x<<' '<<p.y;}
        else if(op=="Z"){int height;std::cin>>height;std::cout<<ra2::flatUnitDepthAdjust(scale,height);}
        else if(op=="O"){unsigned heading;std::cin>>heading;std::cout<<ra2::barrelAfterTurret(std::uint16_t(heading));}
        else if(op=="B") {
            int w,h,sw,sh,z,bri;ra2::PixelRect box,clip;ra2::PixelPoint at;
            std::cin>>w>>h>>sw>>sh>>box.x>>box.y>>box.width>>box.height>>at.x>>at.y>>clip.x>>clip.y>>clip.width>>clip.height>>z>>bri;
            if(w<1||h<1||w>256||h>256||sw<1||sh<1||sw>256||sh>256)return 5;
            ra2::Bytes src(sw*sh);std::vector<std::uint16_t> colors(w*h),depth(w*h),alpha(w*h);std::vector<ra2::Palette16> palettes(53);
            for(auto& v:src){unsigned x;std::cin>>x;v=std::uint8_t(x);}for(auto* p:{&colors,&depth,&alpha})for(auto& v:*p)std::cin>>v;
            for(auto& row:palettes)for(auto& v:row)std::cin>>v;
            ra2::blitUnit(src,sw,sh,box,at,clip,z,bri,palettes,w,h,colors,depth,alpha);std::cout<<digest(colors)<<' '<<digest(depth);
        } else if(op=="T") {
            std::string path;int sub,x,y,level;std::cin>>path>>sub>>x>>y>>level;auto tile=ra2::readTmp(ra2::readFile(path)).at(std::size_t(sub));
            const int w=96,h=96;std::vector<std::uint16_t> colors(w*h),depth(w*h,65535);int base=ra2::terrainDepthBase(y,level);
            for(int yy=0;yy<tile.height;++yy)for(int xx=0;xx<tile.width;++xx) {
                const int px=x+tile.x+xx,py=y+tile.y+yy;if(px<0||py<0||px>=w||py>=h)continue;
                const auto src=std::size_t(yy)*tile.width+xx,dest=std::size_t(py)*w+px;
                if(tile.coverage[src]&1)ra2::terrainPixel(tile.basePixels[src],tile.baseDepth[src],base,std::uint16_t(26*256+tile.basePixels[src]),colors[dest],depth[dest]);
                if((tile.coverage[src]&2)&&tile.extraDepth[src]<32)ra2::terrainPixel(tile.extraPixels[src],tile.extraDepth[src],base,std::uint16_t(26*256+tile.extraPixels[src]),colors[dest],depth[dest]);
            }
            std::cout<<digest(colors)<<' '<<digest(depth);
        } else return 3;
        if(!std::cin)return 4;std::cout<<'\n';
    }
 }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
