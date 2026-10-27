// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/BuildingOrdinaryDraw.hpp"
namespace ra2 {
struct TechnoSpriteFields {
    const std::int32_t& field1bc;
    const std::uint8_t& flag5bb;
    const std::uint8_t& flag37c;
};
struct TechnoSpriteCell {
    const void* identity=nullptr;
    const void*& converter34;
    const std::int16_t& terrain10c;
};
struct TechnoSpriteBlit {
    const void* image;
    std::int32_t frame;
    PixelPoint& point;
    PixelRect& clip;
    std::int32_t flags,zero,zAdjust,gradient,brightness;
    std::array<std::int32_t,4> tail{};
    const void* converter;
    const void* surface;
    const void* auxiliaryImage=nullptr;
};
struct TechnoSpriteServices {
    std::function<std::uint8_t()> shadow7d88d5;
    std::function<std::int32_t(std::int32_t,std::int32_t)> mode64;
    std::function<std::uint8_t()> predicate1bc,predicate1c0;
    std::function<std::int32_t()> kind2c;
    std::function<std::uint8_t()> building1386,typeB48,footBB0,footBB1;
    std::function<Coord()> coordinates48;
    std::function<TechnoSpriteCell(std::uint32_t)> cell548070;
    std::function<void(TechnoSpriteCell,std::array<std::int32_t,6>)> initialize4790f0;
    std::function<const void*()> converter1cc,converterAd0608;
    std::function<std::int32_t()> height1b8,depth2c0;
    std::function<bool()> target1b0;
    std::function<std::int32_t(std::int32_t)> project6a2970;
    std::function<const void*()> currentHouseA35db4;
    std::function<std::uint8_t(const void*)> ownerPredicate3d4;
    std::function<const void*(std::int32_t)> objectC8,houseCC;
    std::function<std::int32_t(const void*)> objectKind2c;
    std::function<const void*(const void*)> houseConverter;
    std::function<TechnoSpriteCell()> cell1a4;
    std::function<std::uint8_t()> ownedHousePredicate4f52b0,predicateC0,predicate32c;
    std::function<std::int32_t(std::int32_t)> flags3d0,brightness3f8,status6d86f0;
    std::function<ShpBoundsView(const void*)> image;
    std::function<PixelRect()> emptyFrame;
    std::function<std::int32_t(int)> infantryBoundsRead;
    std::function<void(int,std::int32_t)> infantryBoundsStore;
    std::function<const void*()> surface83995c;
    std::function<void(const TechnoSpriteBlit&)> draw49eea0;
    std::function<void(int,int,int)> read;
};
// Complete4521B0: signed threshold, wrapped32 adjustment, actorD8 bit1.
std::int32_t buildingSpriteBrightness(std::uint32_t flagsD8,std::int32_t light);
// Complete6D1510: explicit named children; no original code runs at runtime.
// This parent emits complete49EEA0 calls. Child services alone do not prove pixels.
void drawTechnoSprite(const TechnoSpriteFields&,const BuildingSpriteRequest&,const TechnoSpriteServices&);
}
