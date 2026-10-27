// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/VoxelRampShadow.hpp"
#include "sim/OriginalMath.hpp"
#include <cmath>
#include <stdexcept>
namespace ra2 {
namespace {
void rotate(const RasterData& data,Matrix& m,float angle,bool xAxis) {
    const double c=tableCosine(data,angle),s=tableSine(data,angle);
    for(int row=0;row<3;++row) {
        const int a=row*4+(xAxis?1:0),b=a+1;
        const double av=m[a],bv=m[b];
        m[a]=float(xAxis?av*c+bv*s:bv*s+av*c);
        m[b]=float(bv*c-av*s);
    }
}
Matrix slope(const RasterData& data,float direction,float tilt) {
    auto m=voxelIdentity();
    rotate(data,m,direction,false);rotate(data,m,tilt,true);
    rotate(data,m,-direction,false);return m;
}
}
std::array<Matrix,21> voxelRampShadowMatrices(const RasterData& data,double axisTilt,double diagonalTilt) {
    if(!std::isfinite(axisTilt)||!std::isfinite(diagonalTilt)||std::abs(axisTilt)>3||std::abs(diagonalTilt)>3)
        throw std::invalid_argument("Voxel ramp shadow angles exceed the finite tested domain");
    OriginalRounding rounding;
    const float axis=float(axisTilt),diagonal=float(diagonalTilt);
    std::array<Matrix,21> result;result.fill(voxelIdentity());
    // These are the initializer's decimal angle literals, not multiples of an
    // exact pi constant: recomputing 3/6 quarter-turns changes a float32 bit.
    constexpr std::array<float,4> cardinal={4.71225f,3.1415f,1.57075f,0.f};
    constexpr std::array<float,4> corners={3.926875f,2.356125f,.785375f,5.497625f};
    for(unsigned i=0;i<4;++i) {
        result[1+i]=slope(data,cardinal[i],axis);
        result[5+i]=slope(data,corners[i],diagonal);
        result[9+i]=slope(data,corners[i],diagonal);
        result[13+i]=slope(data,corners[i],axis);
    }
    return result;
}
}
