// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/FootLitDraw.hpp"
namespace ra2 {
enum class UnitVoxelPart {Body,Turret,Barrel};
struct UnitVoxelDrawInputs {
    PixelPoint point{};
    PixelRect clip{};
    PixelRect emptyDirty{}; // Supplied initialized staging template.
    int brightness=0,animationFrame=0,bodyFrames=1;
    std::uint16_t bodyHeading=0,turretHeading=0,barrelHeading=16384;
    // Raw global +0x839A58 gate: zero seeds -1; nonzero seeds zero.
    std::uint8_t keyGate=1;
    bool barrelModel=true,turretCacheHasEntries=false;
    Matrix camera=voxelIdentity();
};
struct UnitVoxelDrawState {
    bool stagingSurface=false,staging=false;
    PixelRect dirty{};
};
struct UnitVoxelShadowRequest {
    int key=0;
    PixelPoint point{};
    PixelRect clip{};
    Matrix pose{};
    bool useStagingStencil=true;
};
struct UnitVoxelDrawServices {
    std::function<void()> originalTypeVisible,bodyPose,multipleTurretQuery,shadowPose;
    std::function<PixelRect()> stagingBounds;
    std::function<bool(UnitVoxelPart,int)> cachedImage;
    std::function<PixelPoint()> drawOffset;
    std::function<void(const FootLitRequest&)> lit;
    std::function<int(int)> finalBrightness;
    std::function<void()> status;
    std::function<void(PixelPoint,PixelRect,int)> finalDraw;
    // Healthy ground height zero; immutable cell association and neutral Drive
    // shadow point are domain inputs. Callbacks expose original query ordering.
    std::function<void()> height,cell;
    std::function<std::uint8_t()> predicate;
    std::function<void(const UnitVoxelShadowRequest&)> shadow;
    std::function<void(PixelRect)> clearStaging;
};
using UnitVoxelStore=std::function<void(char,int)>;
// Complete Unit voxel root's healthy flat Track/single-turret/zero-offset path.
// Supplied barrel facing, original type visible, height zero, no status/alternate
// body/add-14/bridge/clip-height branches. Services do not imply actor ownership,
// original surfaces, compressed pool, startup globals or raster pixel parity.
void drawHealthyUnitVoxel(const RasterData&,const UnitVoxelDrawInputs&,
                          UnitVoxelDrawState&,const UnitVoxelDrawServices&,
                          const UnitVoxelStore& store={});
}
