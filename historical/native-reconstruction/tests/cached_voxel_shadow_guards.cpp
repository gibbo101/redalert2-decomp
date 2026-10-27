// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/CachedVoxelShadow.hpp"
#include <stdexcept>
using namespace ra2;
int main(){
    Bytes pool(16);PixelPoint point{};PixelRect clip{0,0,4,4},dirty{1,2,3,4};
    std::vector<std::uint16_t> colors(16,0xabcd),depth(16,65535);
    bool called=false;CachedVoxelPartServices s;s.kind=[&]{called=true;};
    int width=4,height=4;std::size_t snapshot=0;
    auto refused=[&]{bool caught=false;try{drawOrdinaryCachedVoxelShadow(pool,snapshot,point,clip,s,width,height,colors,depth,dirty);}catch(const std::invalid_argument&){caught=true;}
        if(!caught||called||colors!=std::vector<std::uint16_t>(16,0xabcd)||dirty.x!=1||dirty.y!=2||dirty.width!=3||dirty.height!=4)throw std::runtime_error("Cached shadow refusal changed state");};
    snapshot=17;refused();snapshot=8;refused();snapshot=0;
    width=0;refused();width=4;depth.pop_back();refused();depth.push_back(65535);
    point.x=2147483647;refused();point.x=0;pool[4]=1;pool[5]=1;refused();
}
