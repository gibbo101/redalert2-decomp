// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MutableUnitMap.hpp"
#include "assets/MapCoordinateCell.hpp"
#include "assets/WalkCellView.hpp"
#include <map>
#include <stdexcept>
namespace ra2 {
// Walk borrows the same production map owner as Drive. This binding owns no
// Cells, occupation, fallback, floor cache or actor and performs no query at
// construction. The stable map and any association observer must outlive it.
class PreparedWalkMap {
    MutableUnitMap& map_;
    std::function<void(MapInputPosition)> assignedFallback_;
    std::map<const void*,MapCellAttributes*> owners_;
    MapFloorHeightWorld world() {
        return {map_.table,&map_.fallback.input,assignedFallback_};
    }
public:
    explicit PreparedWalkMap(MutableUnitMap& map,
        std::function<void(MapInputPosition)> assignedFallback={})
        :map_(map),assignedFallback_(std::move(assignedFallback)) {
        owners_.emplace(&map_.fallback.input,&map_.fallback);
        for(auto& c:map_.cells)owners_.emplace(&c.attributes.input,&c.attributes);
    }
    PreparedWalkMap(const PreparedWalkMap&)=delete;
    PreparedWalkMap& operator=(const PreparedWalkMap&)=delete;
    PreparedWalkMap(PreparedWalkMap&&)=delete;
    PreparedWalkMap& operator=(PreparedWalkMap&&)=delete;
    WalkMovementCellView coordinate(Coord p) {
        return borrowWalkCell(mapCoordinateCell(p,world(),262144));
    }
    WalkMovementCellView word(TerrainCellPoint p) {
        return borrowWalkCell(mapAttributeCell({p.x,p.y},
            {map_.table,&map_.fallback.input,{},assignedFallback_}));
    }
    int floor(Coord p) {
        return mapFloorHeight(map_.floor,map_.levelHeight,p,world());
    }
    // Recover the exact owner without another lookup or fallback/cache write.
    // A foreign identity or a view assembled from mixed owners is refused.
    MapCellAttributes& attributes(WalkMovementCellView c) const {
        const auto found=owners_.find(c.identity);
        if(found==owners_.end()||&c.level!=&found->second->input.level||
           &c.flags!=&found->second->input.flags)
            throw std::invalid_argument("Walk Cell view does not borrow this map owner");
        return *found->second;
    }
};
}
