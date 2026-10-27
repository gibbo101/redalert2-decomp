// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/VoxelSnapshot.hpp"
#include <stdexcept>
using namespace ra2;
template<class F>void refusal(F f){try{f();}catch(const std::invalid_argument&){return;}throw std::runtime_error("Expected snapshot domain refusal");}
int main(){
    refusal([]{encodeVoxelRow(Bytes(3),3);});
    refusal([]{encodeVoxelRow(Bytes(4099),4097);});
    refusal([]{decodeVoxelRow(Bytes{4,0,0});});
    refusal([]{decodeVoxelRow(Bytes{3,0,0});});
    Bytes pool(100,0xa5),source(66);std::size_t cursor=0;
    refusal([&]{appendVoxelSnapshot(pool,cursor,source,8,8,{0,0,7,0,2,1});});
    if(cursor!=0||pool!=Bytes(100,0xa5))throw std::runtime_error("Refused crop modified pool");
    Bytes stage(65536);PixelRect dirty{};IndexRemap map{};CachedVoxelPartServices services;
    refusal([&]{drawOrdinaryCachedVoxelPart(Bytes(11),0,{}, {},0,0,services,map,stage,dirty);});
    refusal([&]{drawOrdinaryCachedVoxelPart(Bytes(12),0,{}, {},8,0,services,map,stage,dirty);});
}
