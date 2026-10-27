// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/ShadowVoxelWorld.hpp"
#include "sim/OriginalMath.hpp"
#include <stdexcept>
namespace ra2 {
ShadowVoxelDrawResult drawOrdinaryShadowVoxelToWorld(const RasterData& data,const RenderData& light,
    const VoxelModel* model,const Animation* animation,const ShadowVoxelWorldInputs& in,
    VoxelSnapshotIndex* index,VoxelSnapshotPool& pool,const CachedVoxelPartServices& s,
    int width,int height,std::vector<std::uint16_t>& colors,const std::vector<std::uint16_t>& depth,PixelRect& dirty){
    if(width<1||height<1||width>4096||height>4096||colors.size()!=std::size_t(width)*height||depth.size()!=colors.size())
        throw std::invalid_argument("Invalid shadow world planes");
    ShadowVoxelDrawResult result;const auto& r=in.cache;
    if(r.actorSuppressed||r.noShadow||r.modelUnavailable||!model)return result;
    auto key=r.key;if(!index||!r.cacheAvailable||r.disableCache)key=-1;
    auto cached=[&](std::size_t snapshot){
        drawOrdinaryCachedVoxelShadow(pool.bytes,snapshot,in.point,in.clip,s,width,height,colors,depth,dirty);
    };
    if(key!=-1)if(auto snapshot=index->find(key)){
        cached(*snapshot);result.kind=ShadowVoxelDrawKind::Cached;return result;
    }
    if(key!=-1&&!r.allowBuild)return result;
    if(model->sections.size()!=1||!animation||animation->frames<=0||animation->names.size()!=1||
       animation->transforms.size()!=std::size_t(animation->frames))
        throw std::invalid_argument("Fresh shadow requires a loaded section and supplied positive-frame HVA");
    OriginalRounding rounding;
    // The supplied pose/HVA is the model transform. The original queue applies
    // it before flattening Z, then applies the separate global/half-scale
    // camera transform (both identity in this bounded profile).
    const auto modelMatrix=voxelMultiply(in.pose,animation->transforms[0]);
    const auto camera=voxelMultiply(voxelIdentity(),voxelIdentity());
    auto raster=rasterVoxelShadow(model->sections.front(),modelMatrix,camera,
                                 voxelShadowOffset(data,light.lightAngle),in.stencil);
    if(key==-1){
        const auto gradient=s.value2C4();const auto z=s.value2C0();s.selectBlitter(0x2001);
        if(gradient!=2)throw std::invalid_argument("Alternate fresh shadow gradient requires recovery");
        const auto& b=raster.rectangle;
        const PixelPoint at{signed32(std::uint32_t(in.point.x)+std::uint32_t(b[0])),
                            signed32(std::uint32_t(in.point.y)+std::uint32_t(b[1]))};
        blitShadow(raster.pixels,256,256,{b[2],b[3],b[4],b[5]},at,in.clip,z,width,height,colors,depth);
        result.kind=ShadowVoxelDrawKind::Bypass;
    }else{
        auto padded=raster.pixels;padded.push_back(0);padded.push_back(0);
        const auto snapshot=appendVoxelSnapshot(pool.bytes,pool.cursor,padded,256,256,raster.rectangle);
        if(!snapshot)throw std::runtime_error("Shadow snapshot pool exhaustion requires original eviction recovery");
        index->append(key,*snapshot);
        // The original successful miss recurses with rebuild disabled and no
        // stencil. That second lookup sorts/updates the hot record before copy.
        cached(*index->find(key));result.kind=ShadowVoxelDrawKind::Fresh;
    }
    result.raster=std::move(raster);return result;
}
}
