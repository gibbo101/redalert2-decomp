// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MembershipPolicy.hpp"
namespace ra2 {
struct MembershipPointView {
    std::int16_t& x;std::int16_t& y;
    MembershipPointView& operator=(TerrainCellPoint p){x=p.x;y=p.y;return *this;}
};
struct MembershipActorView {
    const Coord& position;
    int& next;
    const std::uint8_t& alternate;
    const std::uint8_t& eligible;
    const std::uint8_t& typeMapFlag;
    int kind;
};
struct MembershipCellView {MembershipPointView point;int& head;int& alternateHead;};
// References into actual actor/Cell owners. Binding and slotCell are host
// associations, never a second actor/map or a query that warms lazy state.
struct BorrowedMembershipWorld {
    UnitFoundationState& foundation;
    std::map<int,MembershipActorView> actors;
    std::map<int,MembershipCellView> cells;
    std::function<int(int)> slotCell;
    int fallbackCell=-1;
    UnitMembershipServices services;
    UnitMembershipStore store;
    UnitMembershipTrace trace;
    void cellInsert(int a,int c){membership_policy::cellInsert(a,c,*this);}
    void cellRemove(int a,int c){membership_policy::cellRemove(a,c,*this);}
    void mapInsert(int a,TerrainCellPoint p){membership_policy::mapChange(a,p,true,*this);}
    void mapRemove(int a,TerrainCellPoint p){membership_policy::mapChange(a,p,false,*this);}
};
}
