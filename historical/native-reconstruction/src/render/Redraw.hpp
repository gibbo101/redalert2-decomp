// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/TerrainVisibility.hpp"
#include <functional>
#include <vector>

namespace ra2 {
struct RedrawState {
    int mapMode=0;
    std::uint8_t counter=0,tactical=0;
    bool tacticalPresent=true;
};
struct RedrawEvent {char kind;int index,field,value;};
using RedrawTrace=std::function<void(RedrawEvent)>;
// Complete4E09A0 argument-zero path, borrowing the existing Tactical+D7D.
// A null Tactical pointer causes no write. No map mode/counter is read here.
void requestMapRedrawZero(std::uint8_t* tactical,const RedrawTrace& trace={});
void requestMapRedraw(RedrawState&,int mode,const RedrawTrace& trace={});
void requestObjectRedraw(std::uint8_t& needsRedraw,RedrawState&,const RedrawTrace& trace={});

struct DirtyRegion {PixelRect bounds;std::uint8_t flag=0;};
struct DirtyRegionQueue {
    // Includes unused capacity-tail entries: original removal shifts live entries
    // without clearing the old tail. Host storage/allocator ownership is supplied.
    std::vector<DirtyRegion> slots;
    int count=0,growth=10;
    bool ownsAllocation=false;
};
// Allocator service must preserve old slots and on success resize to the requested
// capacity. False must leave storage unchanged. Original heap code is not recovered.
using DirtyRegionGrowth=std::function<bool(DirtyRegionQueue&,int)>;
PixelRect unionDirtyBounds(PixelRect first,PixelRect second);
void registerDirtyRegion(DirtyRegionQueue&,DirtyRegion,const DirtyRegionGrowth&,
                         const RedrawTrace& trace={});
}
