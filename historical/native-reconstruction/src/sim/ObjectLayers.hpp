// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Drive.hpp"
#include <array>
#include <functional>
#include <map>
namespace ra2 {
struct ObjectLayerEvent {char kind=' ';std::int64_t a=0,b=0,c=0;};
using ObjectLayerTrace=std::function<void(ObjectLayerEvent)>;
struct ObjectLayerActor {Coord position;int lastLayer=-1;};
struct ObjectLayerState {
    std::vector<int> slots; // Active prefix plus original untouched capacity tail.
    int count=0,growBy=10,storageId=-1;
    std::uint8_t valid=1,owned=1;
};
// Ordinary ground Terrain identities. Five original layer records; native IDs
// and allocation storage replace original pointers. No draw/update scheduler.
class ObjectLayers {
    bool ensureCapacity(int,const ObjectLayerTrace&);
    int sortKey(int,const ObjectLayerTrace&) const;
    bool eraseFirst(int,int,const ObjectLayerTrace&);
public:
    std::map<int,ObjectLayerActor> actors;
    std::array<ObjectLayerState,5> layers;
    bool allocationSucceeds=true; // Supplied allocator outcome, not a heap model.
    int nextStorageId=5;
    bool insert(int layer,int actor,bool sorted,const ObjectLayerTrace& trace={});
    void submit(int actor,const ObjectLayerTrace& trace={});
    void remove(int actor,const ObjectLayerTrace& trace={});
};
std::int32_t terrainSortKey(Coord);
}
