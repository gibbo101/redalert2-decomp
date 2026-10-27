// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionTag.hpp"
#include <type_traits>

namespace ra2 {
// Live views only. The caller owns every count, backing array and identity;
// callbacks can replace those owners' backing/counts between original reads.
template<class T> struct MissionExpirationVector {
    std::int32_t& count;
    std::span<T>& slots;
    const void* identity;
};
template<class T> inline T missionExpirationSlot(const MissionExpirationVector<T>& v,std::int32_t index) {
    if(index<0||std::size_t(index)>=v.slots.size())
        throw std::invalid_argument("Mission expiration vector outside native backing");
    return v.slots[std::size_t(index)];
}
template<class T> inline std::int32_t findMissionExpiration(const MissionExpirationVector<T>& v,T value) {
    const auto count=v.count;
    for(std::int32_t i=0;i<count;++i)if(missionExpirationSlot(v,i)==value)return i;
    return -1;
}
// Remove one occurrence, retain the unused tail, and store count before shifts.
// Reload live count/backing after every shift rather than compacting a snapshot.
template<class T> inline void eraseMissionExpiration(MissionExpirationVector<T>& v,std::int32_t index,const MissionTagStore& store={}) {
    if(index==-1||index>=v.count)return;
    if(index<0)throw std::invalid_argument("Mission expiration invalid negative index");
    auto count=missionTagWrapped(v.count,0xffffffffu);
    v.count=count;if(store)store(v.identity,0x10,std::uint32_t(count),nullptr);
    for(auto cursor=index;cursor<count;cursor=missionTagWrapped(cursor,1)) {
        const auto next=missionTagWrapped(cursor,1);
        const auto value=missionExpirationSlot(v,next);
        if(std::size_t(cursor)>=v.slots.size())throw std::invalid_argument("Mission expiration shift outside backing");
        v.slots[std::size_t(cursor)]=value;
        if(store) {
            if constexpr(std::is_pointer_v<T>)store(v.identity,0x100+std::int64_t(cursor)*4,0,value);
            else store(v.identity,0x100+std::int64_t(cursor)*4,std::uint32_t(value),nullptr);
        }
        count=v.count;
    }
}
// Borrow either the original packed logical word or the same two Cell words
// used by visibility. No aliasing cast, endian dependency or mirrored coordinate.
class MissionExpirationPointView {
    std::uint32_t* packed_=nullptr;
    std::int16_t* x_=nullptr;
    std::int16_t* y_=nullptr;
public:
    MissionExpirationPointView(std::uint32_t& packed):packed_(&packed){}
    MissionExpirationPointView(std::int16_t& x,std::int16_t& y):x_(&x),y_(&y){}
    operator std::uint32_t()const{
        return packed_?*packed_:std::uint32_t(std::uint16_t(*x_))|(std::uint32_t(std::uint16_t(*y_))<<16);
    }
    MissionExpirationPointView& operator=(std::uint32_t value){
        if(packed_)*packed_=value;
        else{*x_=std::bit_cast<std::int16_t>(std::uint16_t(value));*y_=std::bit_cast<std::int16_t>(std::uint16_t(value>>16));}
        return *this;
    }
};
struct MissionExpirationCell {
    MissionExpirationPointView point;
    MissionTagState*& tag;
    const void*& link2C;
    const void*& link30;
    // Cell+28's vector is queried only for kind61, never for a Tag(kind44).
    const void* const& content;
    const void* identity;
};
struct MissionTagExpirationMap {
    MissionExpirationVector<std::uint32_t>& taggedPoints;
    MissionExpirationVector<const void*>& tags;
    std::span<MissionExpirationCell* const> cells;
    MissionExpirationCell& fallback;
    MissionTagStore store;
};
inline MissionExpirationCell& missionExpirationCell(std::uint32_t packed,const MissionTagExpirationMap& map) {
    const auto x=std::bit_cast<std::int16_t>(std::uint16_t(packed));
    const auto y=std::bit_cast<std::int16_t>(std::uint16_t(packed>>16));
    const auto index=std::int32_t(y)*512+std::int32_t(x);
    if(index>=0&&index<262144) {
        if(std::size_t(index)>=map.cells.size())throw std::invalid_argument("Mission expiration map slot outside native backing");
        if(auto* cell=map.cells[std::size_t(index)])return *cell;
    }
    map.fallback.point=packed;
    if(map.store)map.store(map.fallback.identity,0x24,packed,nullptr);
    return map.fallback;
}
// Complete47A340 in its nonnull Tag(kind44) domain. The independent Cell+2C/
// +30 words are cleared even when its Tag differs. Kind61 is not admitted.
inline void expireMissionCellTag(MissionExpirationCell& cell,MissionTagState& tag,
                                 MissionExpirationVector<std::uint32_t>& points,const MissionTagStore& store={}) {
    if(cell.tag==&tag) {
        clearMissionCellTag(cell.tag,store);
        eraseMissionExpiration(points,findMissionExpiration(points,std::uint32_t(cell.point)),store);
    }
    if(cell.link2C==&tag){cell.link2C=nullptr;if(store)store(cell.identity,0x2c,0,nullptr);}
    if(cell.link30==&tag){cell.link30=nullptr;if(store)store(cell.identity,0x30,0,nullptr);}
}
// Complete559D80 for Tag subjects. The query uses vector points, removal uses
// the selected Cell's stored point. The fallback notification always follows.
inline void expireMissionMapTag(MissionTagState& tag,MissionTagExpirationMap& map) {
    auto& points=map.taggedPoints;
    for(std::int32_t i=0;i<points.count;++i) {
        auto& cell=missionExpirationCell(missionExpirationSlot(points,i),map);
        if(cell.tag==&tag) {
            clearMissionCellTag(cell.tag,map.store);
            eraseMissionExpiration(points,findMissionExpiration(points,std::uint32_t(cell.point)),map.store);
            --i;
        }
    }
    expireMissionCellTag(map.fallback,tag,points,map.store);
    eraseMissionExpiration(map.tags,findMissionExpiration(map.tags,static_cast<const void*>(&tag)),map.store);
}
// Complete53E110 for null/Tag subjects. Every duplicate is removed; map559D80
// deliberately removes only the first occurrence in its distinct Tag registry.
inline void expireMissionLogicTag(MissionTagState* tag,MissionExpirationVector<const void*>& tags,const MissionTagStore& store={}) {
    if(!tag)return;
    for(std::int32_t i=0;i<tags.count;++i)if(missionExpirationSlot(tags,i)==tag) {
        eraseMissionExpiration(tags,i,store);--i;
    }
}
struct MissionTagExpirationRecipient {
    const void* identity;
    std::function<void(MissionTagState&,std::uint32_t)> expired;
};
struct MissionTagExpirationServices {
    const void*& global680;
    const void*& global684;
    MissionExpirationVector<MissionTagExpirationRecipient*>& recipients;
    MissionTagExpirationMap& map;
    MissionExpirationVector<const void*>& logicTags;
    // Named498F10 and CRT dynamic-cast association remain supplied. Only actual
    // non-AbstractType Tag44 is supported; a positive cast refuses explicitly.
    std::function<void()> clearMapSelection;
    std::function<bool(MissionTagState&)> abstractType;
    MissionTagStore store;
};
//6ECB90 Tag44 path. Recipient backing/count are read live after each callback.
// Map receives removed=1 even when the caller passed0; logic ignores the flag.
inline void broadcastMissionTagExpiration(MissionTagState& tag,std::uint32_t removed,const MissionTagExpirationServices& s) {
    if(s.global680==&tag){s.global680=nullptr;if(s.store)s.store(&s.global680,0,0,nullptr);}
    if(s.global684==&tag) {
        s.global684=nullptr;if(s.store)s.store(&s.global684,0,0,nullptr);
        if(!s.clearMapSelection)throw std::invalid_argument("Mission expiration requires map selection service");
        s.clearMapSelection();
    }
    if(!s.abstractType)throw std::invalid_argument("Mission expiration requires Tag RTTI association");
    if(s.abstractType(tag))throw std::invalid_argument("AbstractType expiration requires recovery");
    for(std::int32_t i=0;i<s.recipients.count;++i) {
        auto* recipient=missionExpirationSlot(s.recipients,i);
        if(!recipient||!recipient->expired)throw std::invalid_argument("Mission expiration requires actual recipient dispatch");
        recipient->expired(tag,removed);
    }
    expireMissionMapTag(tag,s.map);
    expireMissionLogicTag(&tag,s.logicTags,s.store);
}
}
