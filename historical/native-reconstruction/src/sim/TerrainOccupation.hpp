// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Drive.hpp"
#include <compare>
#include <functional>
#include <map>
#include <vector>
namespace ra2 {
struct TerrainCellPoint {
    std::int16_t x=0,y=0;
    auto operator<=>(const TerrainCellPoint&) const = default;
};
struct TerrainOccupationType {std::uint32_t temperate=7,snow=7;};
struct TerrainOccupationChange {
    TerrainCellPoint cell;
    std::uint32_t flags=0;
    std::vector<std::uint8_t> writes; // Original ordered low-byte stores, including ties.
};
TerrainCellPoint terrainCellPoint(Coord);
TerrainOccupationChange terrainOccupation(Coord,int theater,TerrainOccupationType,
                                         std::uint32_t flags,bool mark);
struct TerrainMarkState {std::uint8_t onMap=0,needsRedraw=0,limbo=0;};
enum class TerrainMapAction {None,Insert,Remove};
struct TerrainMarkDecision {
    bool accepted=false,redraw=false,coordinates=false;
    TerrainMapAction action=TerrainMapAction::None;
};
// Ordinary Terrain only, without an attached animation service. Preserves the
// complete base/Object + Terrain decision sequence; external redraw is supplied.
TerrainMarkDecision terrainMark(TerrainMarkState&,std::int32_t mode);

struct TerrainMember {
    Coord position;
    TerrainOccupationType type;
    int next=-1; // Native logical identity; original NextObject +0x30.
    TerrainMarkState state;
};
struct TerrainCellState {
    std::uint32_t flags=0;int head=-1,alternateHead=-1;
    std::uint8_t neighbors=0,overlayFrame=0;
    std::int32_t overlay=-1;
};
struct TerrainOccupationEvent {char kind=' ';int id=0;std::int64_t value=0;};
// Portable ordinary static Terrain cell membership. Map storage, successful
// foundation assignment and redraw/visibility services remain host-owned.
class TerrainOccupationWorld {
public:
    int theater=0;
    std::map<int,TerrainMember> members;
    std::map<TerrainCellPoint,TerrainCellState> cells;
    void cellInsert(int id,TerrainCellPoint cell,bool alternate,
                    const std::function<void(TerrainOccupationEvent)>& trace={});
    void cellRemove(int id,TerrainCellPoint cell,bool alternate,
                    const std::function<void(TerrainOccupationEvent)>& trace={});
    bool mark(int id,std::int32_t mode,
              const std::function<void(TerrainOccupationEvent)>& trace={});
};
}
