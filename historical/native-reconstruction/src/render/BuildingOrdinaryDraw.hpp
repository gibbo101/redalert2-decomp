// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/BuildingFrame.hpp"
#include "sim/Drive.hpp"
namespace ra2 {
struct BuildingOrdinaryTypeState {
    std::uint8_t flag1385=0;
    std::uint8_t flag1386=0,flagB48=0; // Supplied Type startup;6D1510 reads these live.
    std::int32_t adjust11d4=0;
    PixelPoint offset11e4{};
    std::int16_t offset11fc=0;
    const void* image11a0=nullptr;const void* image11a8=nullptr;
    const void* image11b0=nullptr;const void* image11b8=nullptr;
};
struct BuildingOrdinaryType {
    const BuildingOrdinaryTypeState& fields;
    const BuildingImageState& images;
    const BuildingTypeBoundsState& bounds;
};
struct BuildingSpriteRequest {
    const void* image;
    std::int32_t frame;
    PixelPoint& point;
    PixelRect& clip;
    std::int32_t zero=0,flags=256,adjust=0;
    // The eight pending words across548070/1B8 are final draw arguments8..15.
    // Preserve values without assigning unverified semantic names.
    std::array<std::int32_t,8> tail{};
    // Native binding supplied by the owning composition. The diagnostic global
    // word remains independent; never encode a host pointer into that word.
    const void* auxiliaryImage=nullptr;
};
struct BuildingOrdinaryServices {
    std::function<std::uint32_t()> cell1a0;
    std::function<const void*()> image68;
    std::function<std::int32_t()> kind2c,mission16c;
    std::function<BuildingOrdinaryType()> type;
    std::function<std::int32_t()> stage42c;
    std::function<std::uint8_t*(int)> animation454;
    std::function<const void*(std::int32_t)> partner636e20;
    // Each invocation represents a separate partner virtual80 followed by a
    // raw byte read, even when both resolve to the same Type.
    std::function<std::uint8_t(const void*,int)> partnerFlag80;
    std::function<std::uint8_t(int)> timerPredicate;
    std::function<double()> timerFraction496c70,healthRatio5d4540,threshold1368;
    std::function<std::int32_t()> foundationHeight458940,foundationWidth458930;
    std::function<std::int32_t()> global85029c,frame43be20,height1b8;
    std::function<std::int16_t(const void*)> imageCount;
    std::function<std::int16_t(std::uint32_t)> cellLight548070;
    std::function<std::int32_t(std::int32_t)> projectHeight6a2970;
    std::function<void(const BuildingSpriteRequest&)> draw6d1510;
    std::function<void(int,int,int)> read; // subject0 Type,1 actor,2 image.
    std::function<void(int,const void*)> pointerRead;
    std::function<void(int,std::uint8_t)> animationStore;
};
// Complete41B320 packed-Cell result (signed divide256, narrow words).
std::uint32_t buildingDrawCell(Coord);
// Complete43A5E0 over a nonnull actor. All entered child services are required;
// their mutations and the final15-argument draw identity/order are retained.
void drawBuildingOrdinary(PixelPoint&,PixelRect&,const BuildingOrdinaryServices&);
}
