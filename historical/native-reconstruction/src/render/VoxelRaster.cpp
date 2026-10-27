// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/VoxelRaster.hpp"
#include "render/Lighting.hpp"
#include "sim/OriginalMath.hpp"
#include <algorithm>
#include <cmath>
namespace ra2 {
namespace {
float trig(const RasterData& data,double angle,bool cosine) {
    const int raw=int(double(angle)*(cosine?data.cosineScale:data.sineScale));
    int index=(raw/2)%8192;if(index<0)index+=8192;
    if(cosine)index+=2048;
    if((raw&1)&&index<(cosine?10239:8191))++index;
    return data.sine[std::size_t(index)];
}
void rotate(const RasterData& data,Matrix& m,float angle,bool xAxis) {
    const double c=trig(data,angle,true),s=trig(data,angle,false);
    for(int row=0;row<3;++row) {
        const int a=row*4+(xAxis?1:0),b=a+1;
        const double av=m[a],bv=m[b];
        m[a]=float(xAxis?av*c+bv*s:bv*s+av*c);m[b]=float(bv*c-av*s);
    }
}
std::uint32_t packed(int x,int y){return std::uint16_t(x)|(std::uint32_t(std::uint16_t(y))<<16);}
}
int voxelHeading(std::uint16_t heading){return (((unsigned(heading)>>10)+1)>>1)&31;}
float tableSine(const RasterData& data,double angle){OriginalRounding rounding;return trig(data,angle,false);}
float tableCosine(const RasterData& data,double angle){OriginalRounding rounding;return trig(data,angle,true);}
Matrix voxelIdentity(){return {1,0,0,0,0,1,0,0,0,0,1,0};}
Matrix voxelBodyMatrix(const RasterData& data,std::uint16_t heading) {
    OriginalRounding rounding;auto m=voxelIdentity();rotate(data,m,float((voxelHeading(heading)-8)*data.headingStep),false);return m;
}
Matrix voxelTurretMatrix(const RasterData& data,std::uint16_t body,std::uint16_t turret) {
    OriginalRounding rounding;auto m=voxelBodyMatrix(data,body);
    const double t=(voxelHeading(turret)-8)*data.headingStep,b=(voxelHeading(body)-8)*data.headingStep;
    rotate(data,m,float(t-b),false);return m; // zero HTNK TurretOffset, neutral barrel pitch
}
Matrix voxelCameraMatrix(const RasterData& data) {
    OriginalRounding rounding;auto m=voxelIdentity();rotate(data,m,float(-(data.degrees*60)),true);rotate(data,m,float(-(data.degrees*45)),false);return m;
}
Matrix voxelMultiply(const Matrix& a,const Matrix& b) {
    OriginalRounding rounding;Matrix result;
    for(int r=0;r<3;++r)for(int c=0;c<4;++c) {
        double value=(double(a[r*4+2])*b[8+c]+double(a[r*4+1])*b[4+c])+double(a[r*4])*b[c];
        if(c==3)value+=a[r*4+3];result[r*4+c]=float(value);
    }
    return result;
}
Matrix voxelInverse(const Matrix& m) {
    OriginalRounding rounding;Matrix result;
    for(int r=0;r<3;++r) {
        for(int c=0;c<3;++c)result[r*4+c]=m[c*4+r];
        result[r*4+3]=float(-((double(m[r])*m[3]+double(m[8+r])*m[11])+double(m[4+r])*m[7]));
    }
    return result;
}
Vec3 voxelDefaultLight(const RasterData& data,float angle) {
    OriginalRounding rounding;auto m=voxelIdentity();const double c=trig(data,angle,true),s=trig(data,angle,false);
    for(int row=0;row<3;++row) {double a=m[4*row],b=m[4*row+2];m[4*row]=float(a*c-b*s);m[4*row+2]=float(a*s+b*c);}
    // The initialized light's scalar literal at 0x70CA3E/46, not a generated normal table.
    const float component=std::bit_cast<float>(0xbf3504e6u);
    return voxelTransform(m,{component,component,0});
}
std::array<std::uint8_t,256> voxelSectionShades(const RasterData& data,const RenderData& light,int type,const Matrix& pose) {
    OriginalRounding rounding;const auto m=voxelInverse(pose);const auto v=voxelDefaultLight(data,light.lightAngle);
    // 0x58D980 rotates a direction, ignoring translation and retaining its own
    // operation order. It is distinct from the point transform at 0x58E030.
    const Vec3 transformed{
        float((double(m[1])*v.y+double(m[2])*v.z)+double(m[0])*v.x),
        float((double(m[5])*v.y+double(m[4])*v.x)+double(m[6])*v.z),
        float((double(m[9])*v.y+double(m[8])*v.x)+double(m[10])*v.z)};
    return voxelShades(light,type,transformed,{0,0,1},3);
}
Vec3 voxelTransform(const Matrix& m,Vec3 v) {
    OriginalRounding rounding;return {
        float(((double(m[2])*v.z+double(m[1])*v.y)+double(m[0])*v.x)+m[3]),
        float(((double(m[4])*v.x+double(m[6])*v.z)+double(m[5])*v.y)+m[7]),
        float(((double(m[8])*v.x+double(m[10])*v.z)+double(m[9])*v.y)+m[11])};
}
RasterFrame rasterVoxel(const RasterData& data,const VoxelSection& s,const Matrix& matrix,const std::array<std::uint8_t,256>& shades,const VoxelPalette& vpl) {
    OriginalRounding rounding;
    if(s.size[0]<1||s.size[1]<1||s.size[2]<1||s.spans.size()!=std::size_t(s.size[0])*s.size[1])throw std::runtime_error("Invalid raster section spans");
    for(float v:matrix)if(!std::isfinite(v)||std::abs(v)>1000)throw std::runtime_error("Raster matrix outside bounded domain");
    RasterFrame result;
    // Corner order is established by the original VXL loader, not a cube mesh.
    const Vec3 corners[8]={{s.max.x,s.max.y,s.min.z},{s.max.x,s.min.y,s.min.z},{s.min.x,s.min.y,s.min.z},{s.min.x,s.max.y,s.min.z},
                           {s.max.x,s.max.y,s.max.z},{s.max.x,s.min.y,s.max.z},{s.min.x,s.min.y,s.max.z},{s.min.x,s.max.y,s.max.z}};
    Vec3 low{10000,10000,10000},high{-10000,-10000,-10000};
    for(int i=0;i<8;++i) {
        auto p=voxelTransform(matrix,corners[i]);p.y=-p.y;result.corners[i]=p;
        if(p.z<low.z)result.traversal=i;
        low={std::min(low.x,p.x),std::min(low.y,p.y),std::min(low.z,p.z)};
        high={std::max(high.x,p.x),std::max(high.y,p.y),std::max(high.z,p.z)};
    }
    const Vec3 center{float((double(low.x)+high.x)*0.5),float((double(low.y)+high.y)*0.5),float((double(low.z)+high.z)*0.5)};
    const int width=int(double(high.x)-low.x),height=int(double(high.y)-low.y);
    if(width>240||height>240||width<0||height<0)throw std::runtime_error("Voxel exceeds bounded original scratch buffer");
    result.rectangle={int(center.x)-(width+8)/2,int(center.y)-(height+8)/2,128-width/2-4,128-height/2-4,width+8,height+8};
    const auto& walk=data.traversal[result.traversal];const auto start=result.corners[walk[1]];
    const auto xp=result.corners[walk[2]],yp=result.corners[walk[3]],zp=result.corners[walk[4]];
    auto step=[](float a,float b,int count){return int(((double(a)-b)/count)*256);};
    const int dx=step(xp.x,start.x,s.size[0]),dy=step(xp.y,start.y,s.size[0]);
    const int yx=step(yp.x,start.x,s.size[1]),yy=step(yp.y,start.y,s.size[1]);
    const int zx=step(zp.x,start.x,s.size[2]),zy=step(zp.y,start.y,s.size[2]);
    std::uint32_t row=packed(int(((double(start.x)+128)-center.x)*256),int(((double(start.y)+128)-center.y)*256));
    int column=walk[6]*(s.size[1]-1)*s.size[0]+walk[5]*(s.size[0]-1);
    for(int y=0;y<s.size[1];++y) {
        auto at=row;int cell=column;
        for(int x=0;x<s.size[0];++x) {
            const auto& span=s.spans.at(std::size_t(cell));auto location=at;int z=0;
            auto skip=[&](int n){location+=packed(zx*n,zy*n);z+=n;};
            auto emit=[&](std::uint8_t color,std::uint8_t normal) {
                const auto index=std::size_t((location&0xff00)>>8)|std::size_t((location>>16)&0xff00);
                result.pixels[index]=vpl.lookup(color,shades[normal]);
                location+=packed(zx,zy);++z;
            };
            if(!span.empty()) {
                if(walk[0]==0) {
                    std::size_t p=0;
                    while(z<s.size[2]) {skip(span.at(p++));const int count=span.at(p++);for(int n=0;n<count;++n){emit(span.at(p),span.at(p+1));p+=2;}++p;}
                } else {
                    int p=int(span.size())-1;
                    while(z<s.size[2]) {const int count=span.at(std::size_t(p--));for(int n=0;n<count;++n){emit(span.at(std::size_t(p-1)),span.at(std::size_t(p)));p-=2;}--p;skip(span.at(std::size_t(p--)));}
                }
            }
            at+=packed(dx,dy);cell+=walk[7];
        }
        row+=packed(yx,yy);column+=walk[8]*s.size[0];
    }
    return result;
}
}
