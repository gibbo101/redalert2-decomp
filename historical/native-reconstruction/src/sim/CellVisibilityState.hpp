// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TerrainOccupation.hpp"
#include <cstdint>

namespace ra2 {
// One mutable logical Cell record shared by mask calculation, ordinary
// visibility change and resident discovery composition.
struct CellVisibilityState {
private:
    std::uint32_t ownedFlags140_=0;
public:
    TerrainCellPoint point{};
    std::uint8_t primary120=0,secondary121=0;
    std::uint32_t flags12c=0;
    std::int32_t counter130=0,maximum134=0;
    std::int32_t redrawFrame5c=-1; // Supplied startup; complete6AADD0 owns writes.
    std::int32_t count13c=0; // Independent radar coverage counter; supplied zero startup.
    std::uint8_t redraw138=0;
    std::uint32_t& flags140;
    int identity=0;
    std::int8_t level11b=0;
    // Standalone table fixtures only. The Boot Camp composition obtains heads
    // from its actual InfantryMembershipCell owner through resident services.
    int primaryResident=-1,elevatedResident=-1;
    // Standalone recovery fixtures own flags140; the production view borrows
    // the actual terrain Cell word. Copies are value snapshots, never aliases.
    CellVisibilityState(TerrainCellPoint p={},std::uint8_t primary=0,std::uint8_t secondary=0,
        std::uint32_t f12c=0,std::int32_t counter=0,std::int32_t maximum=0,
        std::uint8_t redraw=0,std::uint32_t f140=0,int id=0)
        :ownedFlags140_(f140),point(p),primary120(primary),secondary121(secondary),flags12c(f12c),
         counter130(counter),maximum134(maximum),redraw138(redraw),flags140(ownedFlags140_),identity(id){}
    explicit CellVisibilityState(std::uint32_t& terrainFlags140):flags140(terrainFlags140){}
    CellVisibilityState(const CellVisibilityState& other):CellVisibilityState(){*this=other;}
    CellVisibilityState& operator=(const CellVisibilityState& other){
        if(this==&other)return *this;
        point=other.point;primary120=other.primary120;secondary121=other.secondary121;
        flags12c=other.flags12c;counter130=other.counter130;maximum134=other.maximum134;count13c=other.count13c;
        redrawFrame5c=other.redrawFrame5c;redraw138=other.redraw138;flags140=other.flags140;identity=other.identity;
        level11b=other.level11b;primaryResident=other.primaryResident;elevatedResident=other.elevatedResident;
        return *this;
    }
};
}
