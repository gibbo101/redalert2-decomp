// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/RasterData.hpp"
#include "assets/RenderData.hpp"
namespace ra2 {
int voxelHeading(std::uint16_t heading);
float tableSine(const RasterData&,double angle);
float tableCosine(const RasterData&,double angle);
Matrix voxelIdentity();
Matrix voxelMultiply(const Matrix&,const Matrix&);
Vec3 voxelTransform(const Matrix&,Vec3);
Matrix voxelBodyMatrix(const RasterData&,std::uint16_t heading);
Matrix voxelTurretMatrix(const RasterData&,std::uint16_t body,std::uint16_t turret);
Matrix voxelCameraMatrix(const RasterData&);
Matrix voxelInverse(const Matrix&);
Vec3 voxelDefaultLight(const RasterData&,float angle);
std::array<std::uint8_t,256> voxelSectionShades(const RasterData&,const RenderData&,int normalType,const Matrix&);
struct RasterFrame {
    Bytes pixels=Bytes(65536);
    std::array<int,6> rectangle{}; // destination offset, scratch-buffer origin, dimensions
    std::array<Vec3,8> corners{};
    int traversal=0;
};
// Exact bounded single-section, lit, no internal Z-buffer branch (dispatch 4/5).
// Input matrix is original row-major affine; no triangles or generated voxel cubes.
RasterFrame rasterVoxel(const RasterData&,const VoxelSection&,const Matrix&,const std::array<std::uint8_t,256>& shades,const VoxelPalette&);
}
