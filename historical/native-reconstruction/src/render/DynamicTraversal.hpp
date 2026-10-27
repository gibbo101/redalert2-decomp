// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/Composition.hpp"
#include <array>
#include <functional>
#include <span>
namespace ra2 {
enum class TraversalKind { Unit, Terrain };
struct TraversalActor {
    TraversalKind kind=TraversalKind::Unit;
    // Original byte +0x14 is supplied, not synthesized from YR class metadata.
    std::uint8_t flags=7,visible=0,animated=0,crumbling=0;
    Coord location{};
};
struct TraversalVector {float x=0,y=0,z=0;};
struct DynamicTraversalContext {
    PixelPoint origin{};
    int surfaceWidth=0,surfaceHeight=0;
    std::uint32_t scenarioFlags=0;
    bool contextPresent=true;
    std::uint8_t bypass=0;
    int force=0;
    double heightScale=0;
    // Only the empty auxiliary collection is recovered in this bounded profile.
    std::size_t auxiliaryCount=0;
};
struct DynamicTraversalServices {
    std::function<TraversalKind(int)> type;
    // Inverse-camera matrix construction/transform is a supplied boundary.
    std::function<TraversalVector(TraversalVector)> inverse;
    // The Foot +0x4C call's result is discarded by this caller.
    std::function<void(int)> footCoordinates;
    std::function<Coord(int)> coordinates;
    std::function<bool(int,Coord)> mapRejects;
    std::function<void(int,PixelPoint,PixelRect&)> drawBehind,drawExtras;
    // Actual +0xFC implementation is a separate service. The shared rectangle
    // and full force dword are forwarded, not a per-actor copy/low byte.
    std::function<void(int,PixelRect&,int,int)> drawIfVisible;
};
using DynamicTraversalTrace=std::function<void(int,std::uint8_t)>;
// Complete per-frame caller in the explicit Unit/Foot and Terrain domain.
// Layers may repeat actors but must not contain nulls or change during a scan.
// Non-Foot Techno, other object types and auxiliary collections are refused.
void drawDynamicLayers(std::span<TraversalActor>,const std::array<std::span<const int>,5>&,
                       PixelRect& viewport,const DynamicTraversalContext&,
                       const DynamicTraversalServices&,const DynamicTraversalTrace& trace={});
}
