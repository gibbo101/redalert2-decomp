// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/UnitLighting.hpp"
#include "render/Composition.hpp"
#include <array>
#include <functional>
namespace ra2 {
struct UnitScreenEntry {int actor=0;PixelPoint point{};};
struct UnitScreenRegistry {
    int count=0;
    std::array<UnitScreenEntry,500> entries{};
};
using UnitDrawTrace=std::function<void(char,int)>;
bool registerUnitScreen(UnitScreenRegistry&,int actor,PixelPoint,PixelPoint origin,
                        int width,int height,const UnitDrawTrace& trace={});
struct UnitDrawResource {std::uint8_t flags=0;std::uint32_t shape=0;};
struct UnitDrawType {std::uint8_t harvester=0,voxel=1;bool voxelModel=true;};
struct OrdinaryUnitDrawInputs {
    int actor=0;Coord coordinates{};
    std::int8_t screenOffset=0,secondaryIndex=-1;
    std::uint8_t addFourteen=0,bridge=0;
    int flagHouse=-1,timerStart=-1,timerDuration=0,extraLight=0,currentFrame=0;
    UnitDrawType type,alternate;
};
struct UnitDrawCell {std::int16_t ambient=0;std::uint32_t flags=0;};
struct OrdinaryUnitDrawServices {
    std::function<std::uint32_t()> loadShape;
    std::function<int()> layer;
    std::function<void(int,PixelPoint)> registerScreen;
    std::function<int(Coord)> groundHeight;
    std::function<UnitDrawCell(Coord)> coordinateCell;
    std::function<UnitDrawCell(UnitLightCell)> lightCell;
    std::function<std::uint8_t()> brightnessPredicate,originalTypeVisible;
    std::function<void()> alternateType;
    std::function<void(bool,PixelPoint,PixelRect,int)> draw; // bool: voxel
    std::function<void(PixelPoint,PixelRect)> footDecoration;
    std::function<void()> timerDecoration;
};
// Complete Unit DrawIt caller in the ordinary nonharvester/nonbridge/no-flag/
// domain. Final draws, visibility/type predicates, ground, timer decoration and
// lighting storage remain explicit services. This is not complete Unit rendering.
void drawOrdinaryUnitCaller(UnitDrawResource&,const OrdinaryUnitDrawInputs&,
                           PixelPoint,PixelRect,const OrdinaryUnitDrawServices&,
                           const UnitDrawTrace& trace={});
}
