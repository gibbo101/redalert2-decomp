// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionTag.hpp"
#include <array>

namespace ra2 {
// A live dispatch view for one entry in the global deferred-delete vector.
// Records and the vector backing remain owned by the caller.
struct MissionDeferredCleanupRecord {
    const void* identity;
    std::function<bool()> inactive;
    std::function<std::uint32_t()> release;
    std::array<std::function<bool()>,4> specialType;
    std::function<void()> markSpecial;
    std::function<void(std::uint32_t)> destroy;
};
struct MissionDeferredCleanupServices {
    MissionDeferredDelete& deferred;
    std::function<MissionDeferredCleanupRecord&(const void*)> resolve;
    MissionTagStore store;
};
inline const void* missionDeferredSlot(const MissionDeferredDelete& q,std::int32_t index) {
    if(index<0||std::size_t(index)>=q.slots.size())
        throw std::invalid_argument("Mission deferred cleanup backing outside native domain");
    return q.slots[std::size_t(index)];
}
inline std::int32_t findMissionDeferred(const MissionDeferredDelete& q,const void* value) {
    const auto count=q.count;
    for(std::int32_t i=0;i<count;++i)if(missionDeferredSlot(q,i)==value)return i;
    return -1;
}
// Remove one occurrence, retaining the unused tail. The original stores the
// count before each ordered shift and reloads live count/backing while shifting.
inline void eraseMissionDeferred(MissionDeferredDelete& q,std::int32_t index,const MissionTagStore& store={}) {
    if(index==-1||index>=q.count)return;
    if(index<0)throw std::invalid_argument("Mission deferred cleanup invalid negative index");
    auto count=missionTagWrapped(q.count,0xffffffffu);
    q.count=count;if(store)store(&q,0x10,std::uint32_t(count),nullptr);
    for(auto cursor=index;cursor<count;cursor=missionTagWrapped(cursor,1)) {
        const auto next=missionTagWrapped(cursor,1);
        const auto value=missionDeferredSlot(q,next);
        if(std::size_t(cursor)>=q.slots.size())
            throw std::invalid_argument("Mission deferred cleanup shift outside backing");
        q.slots[std::size_t(cursor)]=value;
        if(store)store(&q,0x100+std::int64_t(cursor)*4,0,value);
        count=q.count;
    }
}
// Complete6ECF10 control flow. Inactive records are removed everywhere before
// Release, RTTI marking and deleting-dtor dispatch. Newly appended entries and
// live count/backing changes are consumed by the same loop.
inline void drainMissionDeferredCleanup(const MissionDeferredCleanupServices& s) {
    if(!s.resolve)throw std::invalid_argument("Mission deferred cleanup resolver required");
    for(std::int32_t i=0;i<s.deferred.count;) {
        const auto identity=missionDeferredSlot(s.deferred,i);
        if(!identity)throw std::invalid_argument("Mission deferred cleanup null record");
        auto& record=s.resolve(identity);
        if(record.identity!=identity||!record.inactive)
            throw std::invalid_argument("Mission deferred cleanup association differs");
        if(!record.inactive()){++i;continue;}
        for(;;) {
            const auto found=findMissionDeferred(s.deferred,identity);
            if(found==-1)break;
            eraseMissionDeferred(s.deferred,found,s.store);
        }
        if(!record.release)throw std::invalid_argument("Mission deferred cleanup Release required");
        if(!record.release())continue;
        bool special=false;
        for(auto& query:record.specialType) {
            if(!query)throw std::invalid_argument("Mission deferred cleanup RTTI query required");
            if(query()){special=true;break;}
        }
        if(special) {
            if(!record.markSpecial)throw std::invalid_argument("Mission deferred cleanup mark service required");
            record.markSpecial();
        }
        if(!record.destroy)throw std::invalid_argument("Mission deferred cleanup destructor required");
        record.destroy(1);
    }
}
}
