// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/RenderData.hpp"
#include <span>
namespace ra2 {
double tableSqrt(const RenderData&,double value);
// Recovered routine inputs are model-space float32 vectors. Camera/model transforms
// are a separate host adapter; this kernel does not certify them. See PRESENTATION.md.
std::array<std::uint8_t,256> voxelShades(const RenderData&,int normalType,Vec3 light,Vec3 view,float intensity=3,bool single=false);
using Palette16=std::array<std::uint16_t,256>;
std::vector<Palette16> lightPalette(const RenderData&,const Palette&,std::array<int,3> tint,int shades,const std::array<std::uint8_t,256>& affected);
std::uint32_t expand565(std::uint16_t color);
// Original transparent Xlat ZReadWrite semantics: zero preserves both outputs,
// strict signed candidate < unsigned stored depth, then store low 16 candidate bits.
void depthPixel(std::uint8_t index,int candidate,std::uint16_t color,std::uint16_t& destination,std::uint16_t& depth);
void depthSpan(std::span<const std::uint8_t> source,int candidate,const Palette16& palette,std::span<std::uint16_t> destination,std::span<std::uint16_t> depth,std::size_t start=0);
}
