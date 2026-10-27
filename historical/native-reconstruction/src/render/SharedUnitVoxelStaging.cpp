// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/SharedUnitVoxelStaging.hpp"
#include <algorithm>
#include <stdexcept>
namespace ra2 {
void drawSharedUnitVoxelIntoStaging(const RasterData& data,const RenderData& light,
    const std::array<const VoxelModel*,3>& models,const std::array<const Animation*,3>& animations,
    const VoxelPalette& vpl,const UnitVoxelDrawInputs& input,bool disableCache,
    SharedUnitVoxelStage& stage,UnitVoxelTypeIndexes& type,UnitVoxelActorStage& actor,
    const UnitVoxelStagingServices& s,const IndexRemap& remap,const SharedUnitVoxelObservers& observers){
    if(input.bodyFrames!=1||!animations[0]||animations[0]->frames!=1||stage.image.pixels.size()!=65536)
        throw std::invalid_argument("Shared Unit staging requires stock one-frame HVA and a 256 by 256 byte surface");
    for(int v:{input.emptyDirty.x,input.emptyDirty.y,input.emptyDirty.width,input.emptyDirty.height})
        if(v<-1048576||v>1048576)throw std::invalid_argument("Shared staging template outside bounded profile");
    UnitVoxelDrawState draw{stage.stagingSurface,actor.staging,stage.image.dirty};
    auto in=input;in.turretCacheHasEntries=type.parts[1].size()!=0;in.barrelModel=models[2]!=nullptr;
    UnitVoxelDrawServices bound;
    bound.originalTypeVisible=s.originalTypeVisible;bound.bodyPose=s.bodyPose;
    bound.multipleTurretQuery=s.multipleTurretQuery;bound.shadowPose=s.shadowPose;
    bound.finalBrightness=s.finalBrightness;bound.status=s.status;bound.finalDraw=s.finalDraw;
    bound.height=s.height;bound.cell=s.cell;bound.predicate=s.predicate;bound.shadow=s.shadow;
    bound.stagingBounds=[]{return PixelRect{0,0,256,256};};bound.drawOffset=driveLitDrawOffset;
    bound.cachedImage=[&](UnitVoxelPart p,int key){return type.parts[std::size_t(p)].find(key).has_value();};
    bound.lit=[&](const FootLitRequest& r){
        if(observers.part)observers.part(r);
        const auto p=std::size_t(r.model);if(p>=3)throw std::invalid_argument("Unknown shared Unit part");
        stage.image.dirty=draw.dirty;
        drawOrdinaryTechnoVoxelPart(data,light,models[p],animations[p],vpl,r,disableCache,
            &type.parts[p],stage.pool,s.part,remap,stage.image);
        draw.dirty=stage.image.dirty;
    };
    bound.clearStaging=[&](PixelRect r){
        const int left=std::max(0,r.x),top=std::max(0,r.y);
        const int right=std::min(256,r.x+r.width),bottom=std::min(256,r.y+r.height);
        if(r.width<=0||r.height<=0||right<=left||bottom<=top)return;
        for(int y=top;y<bottom;++y)std::fill(stage.image.pixels.begin()+y*256+left,stage.image.pixels.begin()+y*256+right,0);
    };
    drawHealthyUnitVoxel(data,in,draw,bound,[&](char k,int value){
        // Forward the recovered writes at their boundary, including a diagnostic
        // observer throwing after a write. No transactional rollback is added.
        if(k=='s')stage.stagingSurface=value!=0;
        else if(k=='f')actor.staging=value!=0;
        else if(k>='0'&&k<='3')stage.image.dirty=draw.dirty;
        if(observers.store)observers.store(k,value);
    });
}
}
