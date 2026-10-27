// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/Composition.hpp"
#include "sim/OriginalMath.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
namespace ra2 {
double worldHeightScale(const RasterData& raster,const RenderData& render) {
    OriginalRounding rounding;
    const double pixelsPerLepton=60.0/tableSqrt(render,131072.0);
    return double(tableSine(raster,raster.degrees*60.0))*pixelsPerLepton;
}
int heightPixels(double scale,int height) {
    if(height<-65536||height>65536||!std::isfinite(scale)||scale<=0||scale>1)throw std::invalid_argument("World height outside bounded profile");
    OriginalRounding rounding;return int((height*scale+(height>=728?1:0))+0.5);
}
PixelPoint worldPixels(double scale,Coord location) {
    // All signed16 Cell centers fit here, including their half-Cell addition.
    // At this bound both original32-bit horizontal products/sums remain exact.
    if(std::abs(std::int64_t(location.x))>8388608||std::abs(std::int64_t(location.y))>8388608)throw std::invalid_argument("World projection outside bounded profile");
    return {(location.x*30-location.y*30)/256,(location.x*15+location.y*15)/256-heightPixels(scale,location.z)};
}
int flatUnitDepthAdjust(double scale,int height){return -heightPixels(scale,height)-1;}
bool barrelAfterTurret(std::uint16_t heading) {const unsigned quadrant=(((unsigned(heading)>>13)+1)>>1)&3;return quadrant==1||quadrant==2;}
int alphaShadeRow(std::uint16_t alpha,int brightness,int shades) {
    if(alpha>255||brightness>65535||shades<1||shades>256)throw std::invalid_argument("Alpha lighting outside bounded profile");
    const int bin=std::min(254,std::max(0,brightness)*261/2048);
    return std::min(shades-1,bin*int(alpha)*(shades-1)/32258);
}
int terrainDepthBase(int top,int elevation,int originY,int maximum) {
    return int(std::uint16_t(maximum+originY-top-30))-15*elevation;
}
void terrainPixel(std::uint8_t index,std::uint8_t byte,int base,std::uint16_t color,std::uint16_t& destination,std::uint16_t& depth) {
    (void)index;const auto candidate=std::uint16_t(base+byte);
    // Original TMP normal pixel accepts ties and opaque palette zero.
    if(candidate<=depth){depth=candidate;destination=color;}
}
BlitStats blitUnit(const Bytes& source,int sourceWidth,int sourceHeight,PixelRect s,PixelPoint d,PixelRect clip,int zAdjust,int brightness,
              const std::vector<Palette16>& palettes,int width,int height,std::vector<std::uint16_t>& colors,const std::vector<std::uint16_t>& depth,const std::vector<std::uint16_t>& alpha,Bytes* coverage) {
    if(width<1||height<1||width>4096||height>4096||sourceWidth<1||sourceHeight<1||sourceWidth>4096||sourceHeight>4096||source.size()!=std::size_t(sourceWidth)*sourceHeight||colors.size()!=std::size_t(width)*height||depth.size()!=colors.size()||alpha.size()!=colors.size())throw std::invalid_argument("Invalid unit blit planes");
    for(int v:{s.x,s.y,s.width,s.height,d.x,d.y,clip.x,clip.y,clip.width,clip.height,zAdjust})if(std::abs(std::int64_t(v))>1048576)throw std::invalid_argument("Blit rectangle outside bounded profile");
    BlitStats stats;
    if(coverage&&coverage->size()!=colors.size())throw std::invalid_argument("Invalid coverage plane");
    if(s.width<=0||s.height<=0||clip.width<=0||clip.height<=0)return stats;
    // Original destination coordinates are relative to the clipping rectangle.
    d.x+=clip.x;d.y+=clip.y;
    // Linked source/destination clipping, as in the original surface helper.
    int left=std::max({0,clip.x,d.x,d.x-s.x}),top=std::max({0,clip.y,d.y,d.y-s.y});
    int right=std::min({width,clip.x+clip.width,d.x+s.width,d.x+sourceWidth-s.x});
    int bottom=std::min({height,clip.y+clip.height,d.y+s.height,d.y+sourceHeight-s.y});
    if(left>=right||top>=bottom)return stats;
    const int visibleHeight=bottom-top;
    const int base=int(std::uint16_t(32768-visibleHeight-top+1))+zAdjust;
    int candidate=(base/3)*3-visibleHeight/3,remainder=3-visibleHeight%3;
    if(remainder==3){remainder=0;++candidate;}
    for(int y=top;y<bottom;++y) {
        for(int x=left;x<right;++x) {
            const auto at=std::size_t(y)*width+x;const auto index=source[std::size_t(s.y+y-d.y)*sourceWidth+s.x+x-d.x];
            if(index&&candidate<int(depth[at])) {
                colors[at]=palettes.at(std::size_t(alphaShadeRow(alpha[at],brightness,int(palettes.size()))))[index];
                if(!coverage||!(*coverage)[at]){++stats.visible;if(coverage)(*coverage)[at]=1;}
            } else if(index)++stats.rejected;
        }
        if(++remainder>=3){++candidate;remainder-=3;}
    }
    return stats;
}
}
