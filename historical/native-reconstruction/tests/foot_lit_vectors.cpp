// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/FootLitDraw.hpp"
#include "render/VoxelCache.hpp"
#include "render/UnitLighting.hpp"
#include <cstring>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void readPose(std::istream& in,Matrix& pose) {
    std::array<std::uint32_t,12> bits{};for(auto& value:bits)in>>value;
    std::memcpy(pose.data(),bits.data(),sizeof(pose));
}
void print(const FootLitRequest& r) {
    std::cout<<"draw "<<r.model<<' '<<r.frame<<' '<<r.key<<' '<<r.cache<<' '
             <<r.clip.x<<' '<<r.clip.y<<' '<<r.clip.width<<' '<<r.clip.height<<' '
             <<r.point.x<<' '<<r.point.y<<' '<<r.brightness<<' '<<r.flags;
    std::array<std::uint32_t,12> bits{};std::memcpy(bits.data(),r.pose.data(),sizeof(r.pose));
    for(auto value:bits)std::cout<<' '<<value;
}
}
int main() {try {
    VoxelCache cache;int serial=0;std::string line;
    while(std::getline(std::cin,line)) {
        std::istringstream in(line);char op;in>>op;
        if(op=='O') {cache={};serial=0;std::cout<<"reset";}
        else if(op=='Z') {int x,y;in>>x>>y;const auto p=driveLitDrawOffset();std::cout<<p.x<<' '<<p.y;}
        else if(op=='F') {
            int has,mode;PixelPoint offset;FootLitRequest r;
            in>>has>>mode>>r.point.x>>r.point.y>>offset.x>>offset.y
              >>r.model>>r.frame>>r.key>>r.cache>>r.clip.x>>r.clip.y>>r.clip.width>>r.clip.height>>r.brightness>>r.flags;
            readPose(in,r.pose);
            drawFootLit(r,has!=0,[&]{std::cout<<"offset ";return mode==1?driveLitDrawOffset():offset;},print);
        } else if(op=='N') {
            int available,disabled,valid,has,mode;PixelPoint offset;FootLitRequest r;
            in>>r.key>>available>>disabled>>valid>>r.frame>>r.brightness>>has>>mode
              >>r.point.x>>r.point.y>>offset.x>>offset.y;
            readPose(in,r.pose);r.model=1;r.cache=available?1:0;r.clip={0,0,256,256};r.flags=0x2800;
            drawFootLit(r,has!=0,[&]{std::cout<<"offset ";return mode==1?driveLitDrawOffset():offset;},[&](const auto& forwarded){
                print(forwarded);std::cout<<' ';
                const auto result=cache.draw({forwarded.key,available!=0,disabled!=0,valid!=0},[&]{
                    RasterFrame frame;frame.pixels.resize(1);frame.pixels[0]=std::uint8_t(serial+1);return frame;
                });
                if(result.built) {
                    std::cout<<"render "<<forwarded.frame<<" 0 "<<unitBrightnessEffect(forwarded.brightness,0)<<' ';
                    if(!result.bypass)std::cout<<"snapshot "<<++serial<<' ';
                } else if(result.frame)std::cout<<"cached "<<unsigned(result.frame->pixels[0])<<" 0 "<<forwarded.brightness<<' ';
            });
            std::cout<<"state "<<cache.size()<<' '<<cache.capacity()<<' '<<int(cache.sorted())<<' ';
            if(cache.hotKey())std::cout<<*cache.hotKey();else std::cout<<"None";
            for(auto key:cache.keys())std::cout<<' '<<key;
        } else throw std::runtime_error("Unknown Foot lit command");
        if(!in)throw std::runtime_error("Incomplete Foot lit input");
        std::cout<<'\n';
    }
} catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
