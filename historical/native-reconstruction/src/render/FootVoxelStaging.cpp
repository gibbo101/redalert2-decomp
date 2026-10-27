// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/FootVoxelStaging.hpp"
#include "render/UnitLighting.hpp"
#include "sim/OriginalMath.hpp"
#include <algorithm>
#include <stdexcept>
namespace ra2 {
std::optional<std::size_t> VoxelSnapshotIndex::find(std::int32_t key){
    if(entries_.empty())return {};
    if(hot_&&entries_[*hot_].key==key)return entries_[*hot_].snapshot;
    if(!sorted_){std::sort(entries_.begin(),entries_.end(),[](auto& a,auto& b){return a.key<b.key;});hot_.reset();sorted_=true;}
    const auto it=std::lower_bound(entries_.begin(),entries_.end(),key,[](auto& e,auto k){return e.key<k;});
    if(it==entries_.end()||it->key!=key)return {};
    hot_=std::size_t(it-entries_.begin());return it->snapshot;
}
void VoxelSnapshotIndex::append(std::int32_t key,std::size_t snapshot){
    if(entries_.size()==capacity_){capacity_+=capacity_?capacity_:10;entries_.reserve(capacity_);hot_.reset();}
    entries_.push_back({key,snapshot});sorted_=false;
}
std::vector<std::int32_t> VoxelSnapshotIndex::keys() const{std::vector<std::int32_t> out;for(const auto& e:entries_)out.push_back(e.key);return out;}
FootVoxelDrawResult drawOrdinaryTechnoVoxelPart(const RasterData& data,const RenderData& light,
    const VoxelModel* model,const Animation* animation,const VoxelPalette& vpl,const FootLitRequest& request,
    bool disableCache,VoxelSnapshotIndex* index,VoxelSnapshotPool& pool,
    const StagedVoxelPartServices& s,const IndexRemap& remap,UnitStaging& stage){
    if(request.flags!=0x2800u)throw std::invalid_argument("Alternate lit cache flags require recovery");
    FootVoxelDrawResult result;
    const auto& r=request;
    if(s.flag204()!=0||s.flag205()!=0||s.house()!=0)throw std::invalid_argument("Alternate lit cache actor state requires recovery");
    const auto flags=0x2800u&~r.flags;
    const auto brightness=unitBrightnessEffect(r.brightness,0);
    auto key=r.key;if(!index||disableCache)key=-1;
    if(key!=-1)if(const auto snapshot=index->find(key)){
        CachedVoxelPartServices cached{s.kind,s.selectBlitter,s.value2C4,s.value2C0};
        drawOrdinaryCachedVoxelPart(pool.bytes,*snapshot,r.point,r.clip,flags,brightness,cached,remap,stage.pixels,stage.dirty);
        result.kind=FootVoxelDrawKind::Cached;return result;
    }
    if(!model||!animation)return result;
    StagedVoxelPartInputs in;in.pose=r.pose;in.frame=r.frame;in.brightness=brightness;in.flags=flags;in.point=r.point;in.clip=r.clip;
    auto frame=drawOrdinaryVoxelPartIntoStaging(data,light,*model,animation,vpl,in,s,remap,stage.pixels);
    s.kind();const auto& b=frame.rectangle;stage.dirty=stagingUnion(stage.dirty,
        {signed32(std::uint32_t(r.point.x)+std::uint32_t(b[0])),signed32(std::uint32_t(r.point.y)+std::uint32_t(b[1])),b[4],b[5]});
    if(key!=-1){
        auto padded=frame.pixels;padded.push_back(0);padded.push_back(0);
        const auto snapshot=appendVoxelSnapshot(pool.bytes,pool.cursor,padded,256,256,b);
        if(!snapshot)throw std::runtime_error("Lit snapshot pool exhaustion requires original eviction recovery");
        index->append(key,*snapshot);
    }
    result.kind=key==-1?FootVoxelDrawKind::Bypass:FootVoxelDrawKind::Fresh;result.raster=std::move(frame);
    return result;
}
FootVoxelDrawResult drawOrdinaryFootVoxelPart(const RasterData& data,const RenderData& light,
    const VoxelModel* model,const Animation* animation,const VoxelPalette& vpl,const FootLitRequest& request,
    bool hasDrive,bool disableCache,VoxelSnapshotIndex* index,VoxelSnapshotPool& pool,
    const StagedVoxelPartServices& s,const IndexRemap& remap,UnitStaging& stage){
    FootVoxelDrawResult result;
    drawFootLit(request,hasDrive,driveLitDrawOffset,[&](const FootLitRequest& r){
        result=drawOrdinaryTechnoVoxelPart(data,light,model,animation,vpl,r,disableCache,index,pool,s,remap,stage);
    });
    return result;
}
}
