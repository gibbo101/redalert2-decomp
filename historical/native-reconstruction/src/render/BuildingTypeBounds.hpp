// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Shp.hpp"
#include "render/Composition.hpp"
#include <functional>
namespace ra2 {
// Synchronous borrowed view of the signed original SHP metadata. Null identity
// denotes no image. Services expose original late count/field reads; no pixels
// or original image-loader code are required by the bounds kernel.
struct ShpBoundsView {
    const void* identity=nullptr;
    std::function<std::int16_t()> count;
    std::function<PixelPoint()> dimensions;
    std::function<std::int16_t(std::uint32_t,int)> field;
};
ShpBoundsView shpBoundsView(const ShpImage&);
PixelRect shpFrameBounds(const ShpBoundsView&,std::int32_t index,const PixelRect& empty);
struct BuildingTypeBoundsState {
    PixelRect bounds11ec{};
    const void* secondaryB98=nullptr;
    const void* auxiliary11cc=nullptr;
    std::uint8_t release13e2=0,flagB9c=0;
};
struct BuildingTypeBoundsServices {
    std::function<ShpBoundsView()> primary9c,secondaryC0;
    std::function<ShpBoundsView(const void*)> auxiliary;
    std::function<void(const void*)> freeImage;
    // Diagnostic, read-only observer of original stores. Pointer stores use0
    // for null; identities are tested separately without native addresses.
    std::function<void(int,int)> store;
};
// Complete45E920 with a supplied heap child. Nonzero byte truth is preserved.
void releaseBuildingSecondary(BuildingTypeBoundsState&,const BuildingTypeBoundsServices&);
// Complete45E290; image loading, heap and initial cache/sentinel remain supplied.
PixelRect buildingTypeBounds(BuildingTypeBoundsState&,const PixelRect& empty,
    const BuildingTypeBoundsServices&);
}
