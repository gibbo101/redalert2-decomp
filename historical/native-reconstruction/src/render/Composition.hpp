// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/VoxelRaster.hpp"
#include "render/Lighting.hpp"
#include "sim/Drive.hpp"
namespace ra2 {
struct PixelPoint {int x=0,y=0;bool operator==(const PixelPoint&)const=default;};
struct PixelRect {int x=0,y=0,width=0,height=0;};
double worldHeightScale(const RasterData&,const RenderData&);
int heightPixels(double scale,int height);
int flatUnitDepthAdjust(double scale,int height);
PixelPoint worldPixels(double scale,Coord location);
bool barrelAfterTurret(std::uint16_t heading);
int alphaShadeRow(std::uint16_t alpha,int brightness,int shades);
int terrainDepthBase(int top,int elevation,int originY=0,int maximum=32768);
void terrainPixel(std::uint8_t index,std::uint8_t depthByte,int base,std::uint16_t color,std::uint16_t& destination,std::uint16_t& depth);
// Flat-drive gradient (original descriptor 2); palette/alpha supplied. Reads depth,
// leaves it intact. Unscaled original pixels are composed before host zoom.
struct BlitStats {std::size_t visible=0,rejected=0;};
BlitStats blitUnit(const Bytes& source,int sourceWidth,int sourceHeight,PixelRect sourceRect,PixelPoint destination,PixelRect clip,int zAdjust,int brightness,
              const std::vector<Palette16>& palettes,int width,int height,std::vector<std::uint16_t>& colors,const std::vector<std::uint16_t>& depth,const std::vector<std::uint16_t>& alpha,Bytes* coverage=nullptr);
}
