// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/DriveBodyPose.hpp"
#include "render/Lighting.hpp"
#include "sim/OriginalMath.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>
namespace ra2 {
namespace {
double progress(const DriveRampState& s,int tick){
    if(!s.duration)return 1;
    int remaining=s.remaining;
    if(s.start!=-1){const int elapsed=signed32(std::uint32_t(tick)-std::uint32_t(s.start));
        remaining=elapsed>=remaining?0:signed32(std::uint32_t(remaining)-std::uint32_t(elapsed));}
    return double(signed32(std::uint32_t(s.duration)-std::uint32_t(remaining)))/double(s.duration);
}
RampQuaternion fromAxis(const RasterData& raster,const RenderData& render,Vec3 v,float tilt){
    const double length=tableSqrt(render,(double(v.z)*v.z+double(v.y)*v.y)+double(v.x)*v.x);
    if(length!=0)v={float(v.x/length),float(v.y/length),float(v.z/length)};
    const double half=double(tilt)*.5,s=tableSine(raster,half);
    return {float(v.x*s),float(v.y*s),float(v.z*s),tableCosine(raster,half)};
}
double acosTable(const RampPoseData& data,double value){
    const auto raw=std::int32_t((value+1)*double(data.inverseScale));
    if(raw>0||raw<-4096)throw std::invalid_argument("Ramp interpolation inverse trig outside table");
    return data.halfPi-double(data.inverseSine[std::size_t(-raw)]);
}
double interpolationSine(const RasterData& raster,double angle){
    // The shared table helper narrows its scaled index to int. The original
    // FTOL has an indefinite result outside that range; that domain is refused
    // here rather than invoking a C++ floating-to-integer overflow.
    const double index=angle*raster.sineScale;
    if(!std::isfinite(index)||index<std::numeric_limits<int>::min()||index>std::numeric_limits<int>::max())
        throw std::invalid_argument("Ramp interpolation angle exceeds native index domain");
    return tableSine(raster,angle);
}
RampQuaternion interpolate(const RasterData& raster,const RampPoseData& data,
    const RampQuaternion& a,const RampQuaternion& b,float fraction){
    const double dot=((double(a[3])*b[3]+double(a[2])*b[2])+double(a[1])*b[1])+double(a[0])*b[0];
    double first=0,second=0;
    if(dot+1>data.epsilon){
        if(1-dot>data.epsilon){const double angle=acosTable(data,dot),denominator=interpolationSine(raster,angle);
            first=interpolationSine(raster,(1-double(fraction))*angle)/denominator;
            second=interpolationSine(raster,double(fraction)*angle)/denominator;
        }else{first=1-double(fraction);second=fraction;}
    }else{
        first=interpolationSine(raster,(1-double(fraction))*data.oppositeHalfPi);
        second=interpolationSine(raster,double(fraction)*data.oppositeHalfPi);
    }
    RampQuaternion out;for(unsigned i=0;i<4;++i)out[i]=float(double(b[i])*second+double(a[i])*first);return out;
}
Matrix quaternionMatrix(const RampQuaternion& q){
    const double x=q[0],y=q[1],z=q[2],w=q[3];
    const float xx=float(x*x),yy=float(y*y),wy=float(w*y),xz=float(x*z);
    const double zz=z*z,xy=y*x,wz=w*z,yz=y*z,wx=w*x;
    // Original fst stores x*z for m20 but retains the unrounded value for m02.
    // Stock ramp quaternions have z=0; retain the inspected distinction anyway.
    return {float(1-2*(double(yy)+zz)),float(2*(xy-wz)),float(2*(x*z+double(wy))),0,
        float(2*(xy+wz)),float(1-2*(double(xx)+zz)),float(2*(yz-wx)),0,
        float(2*(double(xz)-wy)),float(2*(yz+wx)),float(1-2*(double(xx)+yy)),0};
}
void translate(Matrix& m,int axis,int value){for(int r=0;r<3;++r)m[4*r+3]=float(double(float(value))*m[4*r+axis]+m[4*r+3]);}
void rotateXY(const RasterData& raster,Matrix& m,float angle,bool xAxis){
    const float s=tableSine(raster,angle);const double c=tableCosine(raster,angle);
    for(int r=0;r<3;++r){const int a=r*4+(xAxis?1:0),b=r*4+2;const double av=m[a],bv=m[b];
        m[a]=float(xAxis?av*c+bv*s:av*c-bv*s);m[b]=float(xAxis?bv*c-av*s:av*s+bv*c);}
}
}
std::array<RampQuaternion,21> voxelRampQuaternions(const RasterData& raster,const RenderData& render,
    double axisTilt,double diagonalTilt){
    if(!std::isfinite(axisTilt)||!std::isfinite(diagonalTilt)||std::abs(axisTilt)>3||std::abs(diagonalTilt)>3)
        throw std::invalid_argument("Ramp quaternion tilt outside finite domain");
    OriginalRounding rounding;std::array<RampQuaternion,21> result;result.fill({0,0,0,1});
    const Vec3 axes[]={{0,-1,0},{-1,0,0},{0,1,0},{1,0,0}};
    constexpr float angles[]={3.926875f,2.356125f,.785375f,5.497625f};
    for(unsigned i=0;i<4;++i){
        result[1+i]=fromAxis(raster,render,axes[i],float(axisTilt));
        const Vec3 corner{tableCosine(raster,angles[i]),tableSine(raster,angles[i]),0};
        result[5+i]=fromAxis(raster,render,corner,float(diagonalTilt));
        result[9+i]=result[5+i];result[13+i]=fromAxis(raster,render,corner,float(axisTilt));
    }
    return result;
}
Matrix driveBodyPose(const RasterData& raster,const RampPoseData& data,const std::array<Matrix,21>& ramps,
    const std::array<RampQuaternion,21>& quaternions,const DriveBodyInputs& in,
    const std::function<std::uint16_t()>& facing,std::int32_t* key,const std::function<void()>& typeQuery,
    const DriveShadowKeyStore& store){
    if(!facing||in.ramp.current<0||in.ramp.current>20||in.ramp.previous<0||in.ramp.previous>20||
       !std::isfinite(in.rockingX)||!std::isfinite(in.rockingY)||std::abs(in.rockingX)>1||std::abs(in.rockingY)>1||
       !std::isfinite(in.type330)||!std::isfinite(in.type338)||std::abs(in.type330)>1e6||std::abs(in.type338)>1e6)
        throw std::invalid_argument("Drive body outside bounded ramp/rocking/type domain");
    OriginalRounding rounding;
    const auto write=[&](int v){*key=v;if(store)store(v);};
    const bool transient=progress(in.ramp,in.tick)!=1||std::abs(double(in.rockingX))>=.005||std::abs(double(in.rockingY))>=.005;
    auto lift=voxelIdentity(),rock=voxelIdentity();
    if(transient){
        if(typeQuery)typeQuery();const float dimX=float(in.type330);
        if(typeQuery)typeQuery();const float dimY=float(in.type338);
        const float cy=tableCosine(raster,in.rockingY),sy=tableSine(raster,in.rockingY),cx=tableCosine(raster,in.rockingX);
        const double sx=std::abs(double(tableSine(raster,in.rockingX)));
        const int z=int(sx*dimX+std::abs(double(sy))*dimY);
        int x=int(double(dimY)-int(double(cy)*dimY)),y=int(double(dimX)-int(double(cx)*dimX));
        if(in.rockingY<0)x=-x;if(in.rockingX>0)y=-y;
        translate(lift,2,z);translate(rock,0,x);translate(rock,1,y);
        rotateXY(raster,rock,in.rockingX,true);rotateXY(raster,rock,in.rockingY,false);
        if(key)write(-1);
    }else if(key&&*key!=-1){write(signed32(std::uint32_t(*key)<<6));write(signed32(std::uint32_t(*key)+std::uint32_t(in.ramp.current)));}
    const auto heading=voxelBodyMatrix(raster,facing());
    if(key&&*key!=-1){write(signed32(std::uint32_t(*key)<<5));write(signed32(std::uint32_t(*key)|std::uint32_t(voxelHeading(facing()))));}
    auto slope=voxelIdentity();
    if(in.ramp.duration&&progress(in.ramp,in.tick)<1){
        const double fraction=progress(in.ramp,in.tick);
        slope=in.ramp.previous==in.ramp.current?ramps[std::size_t(in.ramp.current)]:
            quaternionMatrix(interpolate(raster,data,quaternions[std::size_t(in.ramp.previous)],quaternions[std::size_t(in.ramp.current)],float(fraction)));
    }else if(in.ramp.current)slope=ramps[std::size_t(in.ramp.current)];
    if(transient)return voxelMultiply(voxelMultiply(voxelMultiply(lift,slope),heading),rock);
    return voxelMultiply(slope,heading);
}
}
