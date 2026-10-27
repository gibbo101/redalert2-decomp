// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/ShadowVoxelWorld.hpp"
#include <stdexcept>
using namespace ra2;
int main(){
    RasterData data;RenderData light;VoxelModel model;Animation animation;
    VoxelSnapshotIndex index;VoxelSnapshotPool pool{Bytes(1024,0xa5)};
    ShadowVoxelWorldInputs in;in.clip={0,0,4,4};PixelRect dirty{1,2,3,4};
    std::vector<std::uint16_t> colors(16,0xabcd),depth(16,65535);
    bool called=false;CachedVoxelPartServices services;services.kind=[&]{called=true;};
    auto unchanged=[&]{if(called||pool.cursor||index.size()||colors!=std::vector<std::uint16_t>(16,0xabcd)||
        dirty.x!=1||dirty.y!=2||dirty.width!=3||dirty.height!=4)throw std::runtime_error("Shadow domain check changed state");};
    int width=4;
    auto draw=[&](const VoxelModel* m,const Animation* a){return drawOrdinaryShadowVoxelToWorld(data,light,m,a,in,&index,pool,services,width,4,colors,depth,dirty);};
    auto refused=[&]{bool caught=false;try{draw(&model,&animation);}catch(const std::invalid_argument&){caught=true;}
        if(!caught)throw std::runtime_error("Unsupported shadow domain accepted");unchanged();};
    width=0;refused();width=4;depth.pop_back();refused();depth.push_back(65535);
    in.cache.actorSuppressed=true;if(draw(&model,nullptr).kind!=ShadowVoxelDrawKind::Skipped)return 1;
    in.cache.actorSuppressed=false;in.cache.noShadow=true;if(draw(&model,nullptr).kind!=ShadowVoxelDrawKind::Skipped)return 1;
    in.cache.noShadow=false;in.cache.modelUnavailable=true;if(draw(&model,nullptr).kind!=ShadowVoxelDrawKind::Skipped)return 1;
    in.cache.modelUnavailable=false;if(draw(nullptr,nullptr).kind!=ShadowVoxelDrawKind::Skipped)return 1;
    in.cache.key=0;in.cache.cacheAvailable=true;in.cache.allowBuild=false;
    if(draw(&model,nullptr).kind!=ShadowVoxelDrawKind::Skipped)return 1;unchanged();
    in.cache.allowBuild=true;refused();model.sections.resize(1);refused();
    animation.frames=1;animation.names={"fixture"};refused();
}
