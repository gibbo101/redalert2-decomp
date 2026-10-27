// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MapVisibility.hpp"
#include <bit>
#include <limits>
#include <stdexcept>
namespace ra2 {
namespace {
enum class Predicate { primary, secondary, count };
std::int16_t word(std::uint32_t v){return std::bit_cast<std::int16_t>(std::uint16_t(v));}
MapVisibilityCell& lookup(TerrainCellPoint p,const MapVisibilityWorld& w,char kind,MapVisibilityCell& scratch){
    if(w.borrowedCell){if(w.query)w.query(kind,p);scratch=w.borrowedCell(p);return scratch;}
    if(w.cells.size()!=262144||!w.fallback)throw std::invalid_argument("Visibility requires complete table and shared fallback");
    if(w.query)w.query(kind,p);
    const int index=int(p.y)*512+int(p.x);
    if(index>=0&&index<262144)if(auto* cell=w.cells[std::size_t(index)])return *cell;
    w.fallback->point=p;if(w.fallbackStore)w.fallbackStore(p);return *w.fallback;
}
bool query(Coord p,const MapVisibilityState& s,const MapVisibilityWorld& w,Predicate predicate){
    // The secondary global shortcut precedes division and all map queries.
    if(predicate==Predicate::secondary&&s.mode&&s.currentHouse13d&&s.overrideValue)return false;
    if(!s.heightDivisor||(p.z==std::numeric_limits<int>::min()&&s.heightDivisor==-1))
        throw std::invalid_argument("Visibility signed division outside native domain");
    const int q=p.z/s.heightDivisor;const bool odd=(std::uint32_t(q)&1)!=0;
    // Original sign correction, SAR and odd-path increment. Negative odd q is
    // NOT mathematical ceil(q/2): -1 produces a shift of +1.
    const int shift=q/2+int(odd);
    const TerrainCellPoint point{word(std::uint32_t(p.x/256)-std::uint32_t(shift)),
                                 word(std::uint32_t(p.y/256)-std::uint32_t(shift))};
    MapVisibilityCell scratch;
    auto* cell=&lookup(point,w,'i',scratch);
    const auto blocked=[&](const MapVisibilityCell& c){if(predicate==Predicate::count){if(w.countRead)w.countRead(c);return c.count13c<=0;}
        return predicate==Predicate::secondary?(c.flags140&2)!=0:(c.flags12c&8)!=0;};
    if(odd){
        if(blocked(*cell))return false;
        if(w.neighbor)w.neighbor(*cell,3);
        const TerrainCellPoint next{word(std::uint32_t(int(cell->point.x))+std::uint32_t(int(w.direction3.x))),
                                    word(std::uint32_t(int(cell->point.y))+std::uint32_t(int(w.direction3.y)))};
        cell=&lookup(next,w,'w',scratch);
    }
    return !blocked(*cell);
}
}
bool mapPrimaryVisibility(Coord p,const MapVisibilityState& s,const MapVisibilityWorld& w){return query(p,s,w,Predicate::primary);}
bool mapSecondaryVisibility(Coord p,const MapVisibilityState& s,const MapVisibilityWorld& w){return query(p,s,w,Predicate::secondary);}
bool mapCountVisibility(Coord p,const MapVisibilityState& s,const MapVisibilityWorld& w){return query(p,s,w,Predicate::count);}
}
