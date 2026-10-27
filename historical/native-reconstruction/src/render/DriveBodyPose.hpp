// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/RampPoseData.hpp"
#include "render/DriveShadowPose.hpp"
#include "sim/ActorGroundState.hpp"
namespace ra2 {
using RampQuaternion=std::array<float,4>;
std::array<RampQuaternion,21> voxelRampQuaternions(const RasterData&,const RenderData&,
    double axisTilt,double diagonalTilt);
struct DriveBodyInputs {
    DriveRampState ramp;
    int tick=0;
    float rockingX=0,rockingY=0;
    double type330=0,type338=0; // Original supplied type doubles, narrowed separately.
};
// Complete Drive body pose/key. Stock initialized tables, immutable state and
// read-only type/Facing observers supplied; actor placement/movement is separate.
Matrix driveBodyPose(const RasterData&,const RampPoseData&,const std::array<Matrix,21>&,
    const std::array<RampQuaternion,21>&,const DriveBodyInputs&,
    const std::function<std::uint16_t()>& bodyFacing,std::int32_t* key,
    const std::function<void()>& typeQuery={},const DriveShadowKeyStore& store={});
}
