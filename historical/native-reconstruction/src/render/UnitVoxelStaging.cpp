// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitVoxelStaging.hpp"
#include <algorithm>
#include <stdexcept>
namespace ra2 {
void drawHealthyUnitVoxelIntoStaging(const RasterData& data,const RenderData& light,
    const std::array<const VoxelModel*,3>& models,const std::array<const Animation*,3>& animations,
    const VoxelPalette& vpl,const UnitVoxelDrawInputs& input,bool disableCache,
    UnitVoxelStagingState& state,const UnitVoxelStagingServices& s,const IndexRemap& remap){
    if(input.bodyFrames!=1||!animations[0]||animations[0]->frames!=1)
        throw std::invalid_argument("Unit staging requires the stock one-frame body HVA");
    if(state.image.pixels.size()!=65536)throw std::invalid_argument("Unit staging requires a 256 by 256 byte surface");
    for(int v:{input.emptyDirty.x,input.emptyDirty.y,input.emptyDirty.width,input.emptyDirty.height})
        if(v<-1048576||v>1048576)throw std::invalid_argument("Unit staging template outside bounded profile");
    auto in=input;in.turretCacheHasEntries=state.indexes[1].size()!=0;in.barrelModel=models[2]!=nullptr;
    UnitVoxelDrawServices bound;
    bound.originalTypeVisible=s.originalTypeVisible;bound.bodyPose=s.bodyPose;
    bound.multipleTurretQuery=s.multipleTurretQuery;bound.shadowPose=s.shadowPose;
    bound.finalBrightness=s.finalBrightness;bound.status=s.status;
    bound.finalDraw=s.finalDraw;bound.height=s.height;bound.cell=s.cell;
    bound.predicate=s.predicate;bound.shadow=s.shadow;
    bound.stagingBounds=[]{return PixelRect{0,0,256,256};};
    bound.drawOffset=driveLitDrawOffset;
    bound.cachedImage=[&](UnitVoxelPart part,int key){return state.indexes[std::size_t(part)].find(key).has_value();};
    bound.lit=[&](const FootLitRequest& r){
        const auto part=std::size_t(r.model);
        if(part>=3)throw std::invalid_argument("Unknown Unit staging part");
        state.image.dirty=state.draw.dirty;
        drawOrdinaryTechnoVoxelPart(data,light,models[part],animations[part],vpl,r,
            disableCache,&state.indexes[part],state.pool,s.part,remap,state.image);
        state.draw.dirty=state.image.dirty;
    };
    bound.clearStaging=[&](PixelRect r){
        // Original BSurface Fill clips the saved dirty region to its bounds.
        // Bounds above and stagingUnion keep these additions in int range.
        const int left=std::max(0,r.x),top=std::max(0,r.y);
        const int right=std::min(256,r.x+r.width),bottom=std::min(256,r.y+r.height);
        if(r.width<=0||r.height<=0||right<=left||bottom<=top)return;
        for(int y=top;y<bottom;++y)std::fill(state.image.pixels.begin()+y*256+left,state.image.pixels.begin()+y*256+right,0);
    };
    drawHealthyUnitVoxel(data,in,state.draw,bound);
}
}
