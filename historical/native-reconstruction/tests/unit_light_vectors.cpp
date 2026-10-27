// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitLighting.hpp"
#include "render/MapLighting.hpp"
#include "render/Composition.hpp"
#include <openssl/evp.h>
#include <iomanip>
#include <iostream>
#include <sstream>
std::string wordHash(const std::vector<std::uint16_t>& v) {
    ra2::Bytes bytes;for(auto x:v){bytes.push_back(std::uint8_t(x));bytes.push_back(std::uint8_t(x>>8));}
    unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;EVP_Digest(bytes.data(),bytes.size(),h,&n,EVP_sha256(),nullptr);
    std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return s.str();
}
std::vector<std::uint16_t> flatten(const ra2::UnitLightConverter& c) {
    std::vector<std::uint16_t> out;for(const auto& row:c.shades)out.insert(out.end(),row.begin(),row.end());return out;
}
int main(int argc,char** argv) {
 try {
    if(argc!=3)return 2;
    const auto raster=ra2::readRasterData(ra2::readFile(argv[1]));const auto render=ra2::readRenderData(ra2::readFile(argv[2]));
    std::string op;
    while(std::cin>>op) {
        if(op=="Q") {double v;std::cin>>v;std::cout<<ra2::extraUnitLight(v);}
        else if(op=="X") {int x,y;std::cin>>x>>y;const auto c=ra2::unitLightCell(x,y);std::cout<<c.x<<' '<<c.y;}
        else if(op=="B") {
            int ambient,extra;std::uint32_t flags,effects;bool predicate;std::cin>>ambient>>extra>>flags>>predicate>>effects;
            if(ambient<-32768||ambient>32767)return 4;
            const auto b=ra2::ordinaryUnitBrightness(std::int16_t(ambient),extra,flags,predicate);
            std::cout<<b<<' '<<ra2::unitBrightnessEffect(b,effects);
        } else if(op=="H") {
            std::size_t index,n;std::cin>>index>>n;if(n<1||n>32)return 4;
            std::vector<ra2::UnitLightConverter> registry(n);for(auto& c:registry){std::uint16_t id;std::cin>>id;c.shades.resize(1);c.shades[0][0]=id;}
            std::cout<<ra2::houseUnitConverter(registry,index).shades[0][0];
        } else if(op=="P"||op=="C") {
            std::string path;unsigned h,s,v;std::cin>>path>>h>>s>>v;if(h>255||s>255||v>255)return 4;
            const auto p=ra2::readPalette(ra2::readFile(path));const auto converter=ra2::unitLightConverter(raster,render,p,{std::uint8_t(h),std::uint8_t(s),std::uint8_t(v)});
            if(op=="P")std::cout<<wordHash(flatten(converter));
            else {
                ra2::MapLightSettings settings;int x,y,z,detail,n,extra;std::uint32_t flags,effects;bool predicate;
                std::cin>>settings.ambient>>settings.tint[0]>>settings.tint[1]>>settings.tint[2]>>settings.ground>>settings.level>>x>>y>>z>>detail>>n;
                if(n<0||n>256)return 4;std::vector<ra2::LightSource> sources(n);
                for(auto& c:sources)std::cin>>c.x>>c.y>>c.z>>c.radius>>c.intensity>>c.tint[0]>>c.tint[1]>>c.tint[2]>>c.active>>c.minimumDetail;
                std::cin>>extra>>flags>>predicate>>effects;
                const auto cell=ra2::cellLight(render,settings,x,y,z,sources,detail);
                const int brightness=ra2::unitBrightnessEffect(ra2::ordinaryUnitBrightness(std::int16_t(cell.ambient),extra,flags,predicate),effects);
                int w,ht,sw,sh,adjust;ra2::PixelRect box,clip;ra2::PixelPoint at;
                std::cin>>w>>ht>>sw>>sh>>box.x>>box.y>>box.width>>box.height>>at.x>>at.y>>clip.x>>clip.y>>clip.width>>clip.height>>adjust;
                if(w<1||ht<1||w>256||ht>256||sw<1||sh<1||sw>256||sh>256)return 5;
                ra2::Bytes source(sw*sh);unsigned value;for(auto& c:source){std::cin>>value;c=std::uint8_t(value);}
                std::vector<std::uint16_t> colors(w*ht),depth(w*ht),alpha(w*ht);for(auto* p:{&colors,&depth,&alpha})for(auto& c:*p)std::cin>>c;
                ra2::blitUnit(source,sw,sh,box,at,clip,adjust,brightness,converter.shades,w,ht,colors,depth,alpha);
                std::cout<<cell.ambient<<' '<<brightness<<' '<<wordHash(colors)<<' '<<wordHash(depth);
            }
        } else if(op=="R") {
            int brightness;std::cin>>brightness;std::vector<std::uint16_t> rows;for(int alpha=0;alpha<256;++alpha)rows.push_back(std::uint16_t(ra2::alphaShadeRow(std::uint16_t(alpha),brightness,53)));
            std::cout<<wordHash(rows);
        } else return 3;
        if(!std::cin)return 6;std::cout<<'\n';
    }
 }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
