// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/DriveShadowPose.hpp"
#include "sim/OriginalMath.hpp"
#include <cmath>
#include <stdexcept>
namespace ra2 {
Matrix driveShadowPose(const RasterData& raster,const std::array<Matrix,21>& ramps,
    const DriveShadowInputs& in,const DriveShadowServices& services,std::int32_t* key,
    bool wrapper,const DriveShadowKeyStore& store) {
    if(!services.currentRamp||!services.bodyFacing||!std::isfinite(in.rockingX)||!std::isfinite(in.rockingY))
        throw std::invalid_argument("Drive shadow requires map/Facing services and finite rocking");
    OriginalRounding rounding;
    auto write=[&](std::int32_t value){*key=value;if(store)store(value);};
    if(wrapper) {
        double progress=1;
        if(in.slopeDuration!=0) {
            auto remaining=in.slopeRemaining;
            if(in.slopeStart!=-1) {
                const auto elapsed=signed32(std::uint32_t(in.tick)-std::uint32_t(in.slopeStart));
                remaining=elapsed>=remaining?0:signed32(std::uint32_t(remaining)-std::uint32_t(elapsed));
            }
            const auto numerator=signed32(std::uint32_t(in.slopeDuration)-std::uint32_t(remaining));
            progress=double(numerator)/double(in.slopeDuration);
        }
        if((progress!=1||std::abs(double(in.rockingX))>=.005||std::abs(double(in.rockingY))>=.005)&&key)
            write(-1);
    }
    const auto ramp=services.currentRamp(in.position);
    if(ramp>=ramps.size())throw std::invalid_argument("Drive shadow ramp exceeds initialized table");
    auto pose=ramps[ramp];
    for(float v:pose)if(!std::isfinite(v)||std::abs(v)>1000)
        throw std::invalid_argument("Drive shadow matrix outside finite recovered domain");
    const float angle=float((voxelHeading(services.bodyFacing())-8)*raster.headingStep);
    const double c=tableCosine(raster,angle),s=tableSine(raster,angle);
    for(int row=0;row<3;++row) {
        const int a=row*4,b=a+1;const double av=pose[a],bv=pose[b];
        pose[a]=float(bv*s+av*c);pose[b]=float(bv*c-av*s);
    }
    if(key&&*key!=-1) {
        write(signed32(((std::uint32_t(*key)<<6)+ramp)<<5));
        const auto heading=voxelHeading(services.bodyFacing());
        write(signed32(std::uint32_t(*key)|std::uint32_t(heading)));
    }
    return pose;
}
}
