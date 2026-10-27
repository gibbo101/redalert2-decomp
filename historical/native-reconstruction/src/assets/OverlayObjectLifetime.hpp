// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/OverlayPlacement.hpp"
#include <array>
#include <span>

namespace ra2 {
// Selected base fields. Numeric names retain unknown semantics. These are
// portable projections, never an original Object/Abstract ABI or byte image.
struct OverlayObjectBase {
    std::uint32_t flags14=0,word18=0,word1C=0;
    std::uint8_t byte20=0;
    Coord coord24{};
    std::array<std::uint32_t,3> links30{};
    std::array<std::array<std::uint32_t,3>,2> resources{};
    std::array<std::uint32_t,2> resourceTags{};
    int word64=0,word6C=0,word70=0,lastLayer=0;
    std::uint8_t byte68=0,byte84=0,byte85=0;
    std::array<std::uint8_t,6> bytes77{};
    std::uint32_t word94=0;
};
struct OverlayLifetimeServices {
    // Heap/vector growth result is consumed by its low byte. Successful growth
    // must provide the requested native capacity; allocation/ownership supplied.
    std::function<std::uint32_t(unsigned,int)> grow;
    std::function<void(std::uint32_t)> detachTag;
    std::function<void(unsigned)> expired,baseDestroy,free;
    // Diagnostic observations of the four supplied negative RTTI comparisons.
    std::function<void(unsigned,unsigned)> rttiQuery;
    // role 0 actor offset/size/value; roles 1..6 corresponding registries
    // (count offset 0, slots offset index+1). Handles are caller-owned identities.
    std::function<void(unsigned,unsigned,unsigned,std::uint32_t)> store;
};
void constructOverlayObjectBase(TransientMapOverlay&,OverlayObjectBase&,Coord invalidWorld,
    std::uint32_t resourceTag,std::uint32_t identity,
    const std::array<OverlayTransientRegistry*,4>&,const OverlayLifetimeServices&);
// Already-limbo Overlay only; Object Limbo executes its rejection path. Full
// pointer-expiration broadcasts and eventual base destruction remain services.
void retireLoadedOverlayObject(TransientMapOverlay&,const OverlayObjectBase&,
    std::uint32_t identity,OverlayTransientRegistry& retired,const OverlayLifetimeServices&);
// Overlay actors only, limbo nonzero. Active entries are retained; dead entries
// remove all queued duplicates before the one-entry Overlay registry removal.
void cleanupLoadedOverlayObjects(std::span<TransientMapOverlay* const> actors,
    OverlayTransientRegistry& retired,OverlayTransientRegistry& overlays,
    const OverlayLifetimeServices&);
}
