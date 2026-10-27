// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/VoxelShadow.hpp"
#include "sim/OriginalMath.hpp"
#include <algorithm>
#include <cmath>
namespace ra2 {
Vec3 voxelShadowOffset(const RasterData& data,float lightAngle) {
    OriginalRounding rounding;const auto light=voxelDefaultLight(data,lightAngle);
    return {float(double(light.x)*-6.0),0,0};
}
RasterFrame rasterVoxelShadow(const VoxelSection& s,const Matrix& model,const Matrix& camera,Vec3 offset,ShadowStencil stencil) {
    OriginalRounding rounding;
    if(s.size[0]<1||s.size[1]<1||s.spans.size()!=std::size_t(s.size[0])*s.size[1])throw std::invalid_argument("Invalid shadow columns");
    for(const auto& m:{model,camera})for(float v:m)if(!std::isfinite(v)||std::abs(v)>1000)throw std::invalid_argument("Shadow matrix outside bounded profile");
    for(float v:{offset.x,offset.y,offset.z})if(!std::isfinite(v)||std::abs(v)>1000)throw std::invalid_argument("Shadow offset outside bounded profile");
    if(!stencil.pixels.empty()&&(stencil.width<1||stencil.height<1||stencil.width>4096||stencil.height>4096||stencil.pixels.size()!=std::size_t(stencil.width)*stencil.height))throw std::invalid_argument("Invalid shadow stencil");
    if(std::abs(std::int64_t(stencil.origin.x))>1048576||std::abs(std::int64_t(stencil.origin.y))>1048576)throw std::invalid_argument("Shadow stencil origin outside bounded profile");
    RasterFrame result;
    const Vec3 corners[4]={{s.max.x,s.max.y,s.min.z},{s.max.x,s.min.y,s.min.z},{s.min.x,s.min.y,s.min.z},{s.min.x,s.max.y,s.min.z}};
    Vec3 low{10000,10000,10000},high{-10000,-10000,-10000};
    for(int i=0;i<4;++i) {
        auto p=voxelTransform(model,corners[i]);p.z=0;p=voxelTransform(camera,p);
        p={float(double(p.x)+offset.x),float(double(p.y)+offset.y),float(double(p.z)+offset.z)};p.y=-p.y;
        result.corners[i]=p;low.x=std::min(low.x,p.x);low.y=std::min(low.y,p.y);high.x=std::max(high.x,p.x);high.y=std::max(high.y,p.y);
    }
    const Vec3 center{float((double(low.x)+high.x)*0.5),float((double(low.y)+high.y)*0.5),0};
    const int w=int(double(high.x)-low.x),h=int(double(high.y)-low.y);
    if(w>240||h>240||w<0||h<0)throw std::invalid_argument("Shadow exceeds bounded scratch buffer");
    result.rectangle={int(center.x)-(w+8)/2,int(center.y)-(h+8)/2,128-w/2-4,128-h/2-4,w+8,h+8};
    // Shadow records use corner 2 as start, 1 for X and 3 for Y. They do not
    // share the lit rasterizer's packed-lane carry or reverse-Z traversal.
    const auto start=result.corners[2],xp=result.corners[1],yp=result.corners[3];
    auto step=[](float a,float b,int count){return std::uint16_t(int(((double(a)-b)/count)*256));};
    const auto dx=step(xp.x,start.x,s.size[0]),dy=step(xp.y,start.y,s.size[0]),yx=step(yp.x,start.x,s.size[1]),yy=step(yp.y,start.y,s.size[1]);
    std::uint16_t rowX=std::uint16_t(int(((double(start.x)+128)-center.x)*256)),rowY=std::uint16_t(int(((double(start.y)+128)-center.y)*256));
    const int stencilX=int(double(stencil.origin.x)+center.x),stencilY=int(double(stencil.origin.y)+center.y);
    auto clear=[&](int x,int y){return stencil.pixels.empty()||x<0||y<0||x>=stencil.width||y>=stencil.height||stencil.pixels[std::size_t(y)*stencil.width+x]==0;};
    for(int y=0;y<s.size[1];++y) {
        auto xloc=rowX,yloc=rowY;
        for(int x=0;x<s.size[0];++x) {
            if(!s.spans[std::size_t(y)*s.size[0]+x].empty()) {
                const unsigned px=xloc>>8,py=yloc>>8;const std::size_t at=py*256+px;
                const int sx=std::uint16_t(stencilX+int(px)),sy=std::uint16_t(stencilY+int(py));
                result.pixels[at]=std::uint8_t(clear(sx,sy));
                if(at+1>=result.pixels.size())throw std::invalid_argument("Shadow write outside scratch buffer");
                result.pixels[at+1]=std::uint8_t(clear(sx+1,sy));
            }
            xloc=std::uint16_t(xloc+dx);yloc=std::uint16_t(yloc+dy);
        }
        rowX=std::uint16_t(rowX+yx);rowY=std::uint16_t(rowY+yy);
    }
    return result;
}
BlitStats blitShadow(const Bytes& source,int sourceWidth,int sourceHeight,PixelRect s,PixelPoint d,PixelRect clip,int zAdjust,
                    int width,int height,std::vector<std::uint16_t>& colors,const std::vector<std::uint16_t>& depth) {
    if(width<1||height<1||width>4096||height>4096||sourceWidth<1||sourceHeight<1||sourceWidth>4096||sourceHeight>4096||source.size()!=std::size_t(sourceWidth)*sourceHeight||colors.size()!=std::size_t(width)*height||depth.size()!=colors.size())throw std::invalid_argument("Invalid shadow blit planes");
    for(int v:{s.x,s.y,s.width,s.height,d.x,d.y,clip.x,clip.y,clip.width,clip.height,zAdjust})if(std::abs(std::int64_t(v))>1048576)throw std::invalid_argument("Shadow blit rectangle outside bounded profile");
    BlitStats stats;if(s.width<=0||s.height<=0||clip.width<=0||clip.height<=0)return stats;
    d.x+=clip.x;d.y+=clip.y;
    const int left=std::max({0,clip.x,d.x,d.x-s.x}),top=std::max({0,clip.y,d.y,d.y-s.y});
    const int right=std::min({width,clip.x+clip.width,d.x+s.width,d.x+sourceWidth-s.x}),bottom=std::min({height,clip.y+clip.height,d.y+s.height,d.y+sourceHeight-s.y});
    if(left>=right||top>=bottom)return stats;
    const int visibleHeight=bottom-top,base=int(std::uint16_t(32768-visibleHeight-top+1))+zAdjust;
    int candidate=(base/3)*3-visibleHeight/3,remainder=3-visibleHeight%3;
    if(remainder==3){remainder=0;++candidate;}
    for(int y=top;y<bottom;++y) {
        for(int x=left;x<right;++x) {
            const auto at=std::size_t(y)*width+x,index=std::size_t(s.y+y-d.y)*sourceWidth+s.x+x-d.x;
            if(source[index]) {
                if(candidate<int(depth[at])){colors[at]=std::uint16_t((colors[at]>>1)&0x7bef);++stats.visible;}
                else ++stats.rejected;
            }
        }
        if(++remainder>=3){++candidate;remainder-=3;}
    }
    return stats;
}
}
