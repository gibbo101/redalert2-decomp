// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/MapLighting.hpp"
#include "render/Composition.hpp"
#include "assets/Archive.hpp"
#include <openssl/evp.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
std::string wordHash(const std::vector<std::uint16_t>& v) {
    ra2::Bytes b;for(auto x:v){b.push_back(std::uint8_t(x));b.push_back(std::uint8_t(x>>8));}
    unsigned char hash[EVP_MAX_MD_SIZE];unsigned n=0;EVP_Digest(b.data(),b.size(),hash,&n,EVP_sha256(),nullptr);
    std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(hash[i]);return s.str();
}
int main(int argc,char** argv) {
 try {
    if(argc==3&&std::string(argv[1])=="--cells") {
        const auto map=ra2::readMap(ra2::Ini(ra2::readFile(argv[2]).text()));
        for(const auto& c:map.cells)std::cout<<c.x<<' '<<c.y<<' '<<unsigned(c.z)<<'\n';return 0;
    }
    if(argc==4&&std::string(argv[1])=="--export") {
        const auto root=std::filesystem::weakly_canonical(argv[2]);const auto out=std::filesystem::path(argv[3]);
        for(const char* name:{"mp03t4.map","rules.ini","isotem.pal","unittem.pal"}) {
            const auto path=out/name;
            if(std::filesystem::is_symlink(out)||std::filesystem::is_symlink(path))throw std::runtime_error("Symlink research export refused");
            for(auto p=std::filesystem::weakly_canonical(path);!p.empty();) {
                if(p==root)throw std::runtime_error("Use output outside source installation");auto next=p.parent_path();if(p==next)break;p=next;
            }
        }
        ra2::AssetStore store(root);
        for(const char* name:{"mp03t4.map","rules.ini","isotem.pal","unittem.pal"}) {
            const auto data=store.require(name);
            if(std::filesystem::exists(out/name)) {
                const auto current=ra2::readFile(out/name);
                if(data.size!=current.size||!std::equal(data.ptr(),data.ptr()+data.size,current.ptr()))throw std::runtime_error("Different existing research data refused");
            } else {std::filesystem::create_directories(out);std::ofstream f(out/name,std::ios::binary);f.write(reinterpret_cast<const char*>(data.ptr()),std::streamsize(data.size));if(!f)throw std::runtime_error("Research export failed");}
        }
        return 0;
    }
    if(argc!=2)return 2;
    const auto data=ra2::readRenderData(ra2::readFile(argv[1]));std::string op;
    while(std::cin>>op) {
        if(op=="V") {
            int w,h;std::cin>>w>>h;if(w<1||h<1||w>256||h>256)return 4;
            std::cout<<wordHash(std::vector<std::uint16_t>(std::size_t(w)*h,ra2::VisibleAlpha));
        } else if(op=="Q") {
            double ambient,ground,level;std::array<double,3> tint;
            std::cin>>ambient>>tint[0]>>tint[1]>>tint[2]>>ground>>level;
            const auto r=ra2::mapLightSettings(ambient,tint,ground,level);
            std::cout<<r.ambient<<' ';for(int c:r.tint)std::cout<<c<<' ';std::cout<<r.ground<<' '<<r.level;
        } else if(op=="N") {
            int brightness,scale;std::array<int,3> tint;std::cin>>brightness>>tint[0]>>tint[1]>>tint[2];
            ra2::normalizeLight(scale,brightness,tint);std::cout<<scale<<' '<<brightness;for(auto c:tint)std::cout<<' '<<c;
        } else if(op=="C"||op=="B") {
            ra2::MapLightSettings s;int x,y,z,clock,n;
            std::cin>>s.ambient>>s.tint[0]>>s.tint[1]>>s.tint[2]>>s.ground>>s.level>>x>>y>>z>>clock>>n;
            if(n<0||n>256)return 4;std::vector<ra2::LightSource> sources(n);
            for(auto& v:sources)std::cin>>v.x>>v.y>>v.z>>v.radius>>v.intensity>>v.tint[0]>>v.tint[1]>>v.tint[2]>>v.active>>v.minimumDetail;
            const auto r=ra2::cellLight(data,s,x,y,z,sources,clock);
            if(op=="C") {
                std::cout<<r.scale<<' '<<r.sourceIntensity<<' '<<r.ambient<<' '<<r.terrain<<' '<<r.bridge;for(auto c:r.tint)std::cout<<' '<<c;
            } else {
                // Combined kernel -> real palette -> complete flat unit blit.
                int w,h,sw,sh,adjust;ra2::PixelRect box,clip;ra2::PixelPoint at;
                std::cin>>w>>h>>sw>>sh>>box.x>>box.y>>box.width>>box.height>>at.x>>at.y>>clip.x>>clip.y>>clip.width>>clip.height>>adjust;
                if(w<1||h<1||w>256||h>256||sw<1||sh<1||sw>256||sh>256)return 5;
                ra2::Palette p;for(auto& c:p){unsigned red,green,blue;std::cin>>red>>green>>blue;c={std::uint8_t(red),std::uint8_t(green),std::uint8_t(blue)};}
                std::array<std::uint8_t,256> mask;mask.fill(1);const auto palettes=ra2::lightPalette(data,p,r.tint,53,mask);
                ra2::Bytes source(sw*sh);unsigned value;for(auto& v:source){std::cin>>value;v=std::uint8_t(value);}
                std::vector<std::uint16_t> colors(w*h),depth(w*h),alpha(w*h);for(auto* p:{&colors,&depth,&alpha})for(auto& v:*p)std::cin>>v;
                ra2::blitUnit(source,sw,sh,box,at,clip,adjust,r.terrain,palettes,w,h,colors,depth,alpha);
                std::cout<<wordHash(colors)<<' '<<wordHash(depth);
            }
        } else return 3;
        if(!std::cin)return 6;std::cout<<'\n';
    }
 }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
