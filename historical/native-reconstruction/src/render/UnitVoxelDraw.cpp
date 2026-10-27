// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitVoxelDraw.hpp"
#include "render/VoxelCache.hpp"
#include "render/ShadowKeys.hpp"
#include "sim/OriginalMath.hpp"
#include <stdexcept>
namespace ra2 {
namespace {
void emit(const UnitVoxelStore& s,char event,int value){if(s)s(event,value);}
Matrix applyBarrelPitch(const RasterData& data,Matrix pose,std::uint16_t heading) {
    // The ordinary flat/zero-offset branch pivots around the turret matrix's
    // zero translation. Original 0x590880 rotates columns X/Z, unlike the
    // body/turret rotation of columns X/Y. Keep the float32 angle store.
    const float angle=float(-((voxelHeading(heading)-8)*data.headingStep));
    const double c=tableCosine(data,angle),s=tableSine(data,angle);
    for(int row=0;row<3;++row) {
        const int x=row*4,z=x+2;const double a=pose[x],b=pose[z];
        pose[x]=float(a*c-b*s);pose[z]=float(a*s+b*c);
    }
    return pose;
}
}
void drawHealthyUnitVoxel(const RasterData& data,const UnitVoxelDrawInputs& in,
                          UnitVoxelDrawState& state,const UnitVoxelDrawServices& s,
                          const UnitVoxelStore& store) {
    if(in.bodyFrames<=0)throw std::invalid_argument("Positive body HVA frame count required");
    if(state.staging||state.stagingSurface)throw std::invalid_argument("Unit voxel drawing requires the ordinary world surface");
    OriginalRounding rounding;
    s.originalTypeVisible();
    const int frame=in.animationFrame%in.bodyFrames;
    const bool previousSurface=state.stagingSurface;
    state.stagingSurface=true;emit(store,'s',1);
    const auto bounds=s.stagingBounds();
    state.staging=true;emit(store,'f',1);
    s.bodyPose();
    const auto bodyPose=voxelBodyMatrix(data,in.bodyHeading);
    const auto bodyKey=bodyVoxelKey(in.keyGate?voxelHeading(in.bodyHeading):-1,frame);
    // Four ordered assignments, even when an earlier draw left a dirty region.
    state.dirty.x=in.emptyDirty.x;emit(store,'0',state.dirty.x);
    state.dirty.y=in.emptyDirty.y;emit(store,'1',state.dirty.y);
    state.dirty.width=in.emptyDirty.width;emit(store,'2',state.dirty.width);
    state.dirty.height=in.emptyDirty.height;emit(store,'3',state.dirty.height);
    auto part=[&](UnitVoxelPart which,int key,int partFrame,const Matrix& pose) {
        FootLitRequest call;call.model=std::uint32_t(which);call.cache=call.model;
        call.frame=partFrame;call.key=key;call.clip=bounds;call.point={128,128};
        call.pose=pose;call.brightness=in.brightness;call.flags=0x2800;
        drawFootLit(call,true,s.drawOffset,s.lit);
    };
    part(UnitVoxelPart::Body,bodyKey,frame,voxelMultiply(in.camera,bodyPose));
    const int turretKey=turretVoxelKey(bodyKey,in.turretHeading,0);
    s.multipleTurretQuery();
    const bool turretCached=turretKey!=-1&&in.turretCacheHasEntries&&s.cachedImage(UnitVoxelPart::Turret,turretKey);
    const bool barrelCached=in.barrelModel&&turretKey!=-1&&s.cachedImage(UnitVoxelPart::Barrel,turretKey);
    Matrix turretPose,barrelPose;
    if(turretCached&&(!in.barrelModel||barrelCached)) {
        // These are intentionally the untransformed body matrix. A warm image
        // makes the geometry unused by the child; the caller still forwards it.
        turretPose=bodyPose;barrelPose=bodyPose;
    } else {
        const auto pose=voxelTurretMatrix(data,in.bodyHeading,in.turretHeading);
        turretPose=voxelMultiply(in.camera,pose);
        barrelPose=voxelMultiply(in.camera,applyBarrelPitch(data,pose,in.barrelHeading));
    }
    s.multipleTurretQuery();
    if(!barrelAfterTurret(in.turretHeading)&&in.barrelModel)
        part(UnitVoxelPart::Barrel,turretKey,0,barrelPose);
    part(UnitVoxelPart::Turret,turretKey,frame,turretPose);
    if(barrelAfterTurret(in.turretHeading)&&in.barrelModel)
        part(UnitVoxelPart::Barrel,turretKey,0,barrelPose);
    const int brightness=s.finalBrightness(in.brightness);s.status();
    s.finalDraw(in.point,in.clip,brightness);
    const auto dirty=state.dirty;
    state.stagingSurface=previousSurface;emit(store,'s',int(previousSurface));
    state.staging=false;emit(store,'f',0);
    s.shadowPose();s.cell(); // Actual flat Drive shadow pose queries the cell.
    int shadowKey=flatUnitShadowKey(bodyKey,in.bodyHeading);
    s.height();s.cell();
    const bool predicate=s.predicate()!=0;
    if(!predicate) {
        s.height(); // Track branch tests height before adding the high bit.
        shadowKey=signed32(std::uint32_t(shadowKey)|0x80000000u);
    }
    s.height();
    s.shadow({shadowKey,in.point,in.clip,voxelMultiply(in.camera,bodyPose),!predicate});
    s.clearStaging(dirty);
}
}
