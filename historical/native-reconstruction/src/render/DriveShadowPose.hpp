// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/VoxelRaster.hpp"
#include "sim/Drive.hpp"
#include <functional>
namespace ra2 {
struct DriveShadowInputs {
    Coord position{};
    std::int32_t tick=0,slopeStart=-1,slopeRemaining=0,slopeDuration=0;
    float rockingX=0,rockingY=0;
};
struct DriveShadowServices {
    std::function<std::uint8_t(Coord)> currentRamp;
    std::function<std::uint16_t()> bodyFacing;
};
using DriveShadowKeyStore=std::function<void(std::int32_t)>;
// Complete base pose/key query and optional Drive timer/rocking invalidation.
// Initialized tables, actor state and read-only map/Facing services are supplied.
// Null/-1 keys still build the pose; aliasing/actor lifetime remain outside scope.
Matrix driveShadowPose(const RasterData&,const std::array<Matrix,21>&,
    const DriveShadowInputs&,const DriveShadowServices&,std::int32_t* key,
    bool driveWrapper=true,const DriveShadowKeyStore& store={});
}
