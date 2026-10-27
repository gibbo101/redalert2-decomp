// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <limits>
#include <span>
#include <stdexcept>
#include <vector>
#include <array>
#include <utility>
namespace ra2 {
using HouseInfantryStore=std::function<void(const void*,std::int64_t,std::uint32_t)>;
// Borrow the original vector's live capacity/backing. Allocation is a named
// service, not an assumption about the original allocator or vector layout.
struct HouseInfantryCounter {
    const void* identity;
    std::int32_t& capacity8;
    std::span<std::uint32_t>& values;
    std::function<std::uint32_t(std::int32_t,std::uint32_t)> resize8;
};
inline std::uint32_t& houseInfantryCounterSlot(HouseInfantryCounter& c,std::int32_t i){
    if(i<0||std::size_t(i)>=c.values.size())throw std::invalid_argument("House Infantry counter outside live backing");
    return c.values[std::size_t(i)];
}
// Complete491C50/491CB0 for nonnegative, nonoverflowing indexes and owned backing.
// Resize failure tests AL, and skips all zeroing/increment/decrement stores.
inline std::uint32_t changeHouseInfantryCounter(HouseInfantryCounter& c,std::int32_t index,bool add,const HouseInfantryStore& store={}){
    if(index<0||index>std::numeric_limits<std::int32_t>::max()-10)
        throw std::invalid_argument("House Infantry counter index outside owned domain");
    const auto old=c.capacity8;
    if(index>=old){
        if(old<0||!c.resize8)throw std::invalid_argument("House Infantry counter resize unbound");
        if(!std::uint8_t(c.resize8(index+10,0)))return 0;
        for(auto i=old;i<c.capacity8;++i){auto& slot=houseInfantryCounterSlot(c,i);slot=0;if(store)store(c.identity,std::int64_t(i)*4,0);}
    }
    auto& slot=houseInfantryCounterSlot(c,index);slot+=add?1u:std::uint32_t(-1);
    if(store)store(c.identity,std::int64_t(index)*4,slot);
    return houseInfantryCounterSlot(c,index);
}
struct HouseInfantryType {
    const std::uint8_t& flag202;
    std::function<std::int32_t()> index40;
};
struct HouseInfantryActor {
    const void* identity;
    std::uint8_t& flag324;
    const std::uint8_t& flag5C1;
    std::function<HouseInfantryType()> type80;
    std::function<std::uint32_t()> kind2C;
};
struct HouseInfantryOwner {
    const void* identity;
    std::uint32_t& count234;
    HouseInfantryCounter active5440,registered5480;
    const std::int32_t& historyCount1270;
    std::span<std::uint32_t> historyA70;
};
inline HouseInfantryType houseInfantryType(const HouseInfantryActor& a){
    if(!a.type80)throw std::invalid_argument("House Infantry Type query unbound");return a.type80();
}
inline std::int32_t houseInfantryIndex(const HouseInfantryActor& a){
    auto t=houseInfantryType(a);if(!t.index40)throw std::invalid_argument("House Infantry Type index unbound");return t.index40();
}
inline void requireHouseInfantryKind(const HouseInfantryActor& a){
    if(!a.kind2C||a.kind2C()!=15)throw std::invalid_argument("House accounting requires original Infantry kind15");
}
// Complete-to-return4ED440 E1 path. Map67C150 precedes even the kind query.
inline void removeRegisteredHouseInfantry(HouseInfantryOwner& h,const HouseInfantryActor& a,const std::function<void()>& map67C150,const HouseInfantryStore& store={}){
    if(!map67C150)throw std::invalid_argument("House removal requires map67C150");map67C150();
    requireHouseInfantryKind(a);const auto index=houseInfantryIndex(a);
    (void)changeHouseInfantryCounter(h.registered5480,index,false,store);
}
// Complete-to-return4ED610 E1 path; flag5C1 suppresses the registration child.
inline void addRegisteredHouseInfantry(HouseInfantryOwner& h,const HouseInfantryActor& a,const HouseInfantryStore& store={}){
    requireHouseInfantryKind(a);if(a.flag5C1)return;
    const auto index=houseInfantryIndex(a);(void)changeHouseInfantryCounter(h.registered5480,index,true,store);
}
// Complete-to-return4EA800 E1 path. The total decrement precedes the second
// Type query, unlike the add path below. Neither path changes actor ownership.
inline void removeActiveHouseInfantry(HouseInfantryOwner& h,const HouseInfantryActor& a,const HouseInfantryStore& store={}){
    a.flag324=0;if(store)store(a.identity,0x324,0);
    if(houseInfantryType(a).flag202)return;requireHouseInfantryKind(a);
    --h.count234;if(store)store(h.identity,0x234,h.count234);
    const auto index=houseInfantryIndex(a);(void)changeHouseInfantryCounter(h.active5440,index,false,store);
}
// Complete-to-return4EA970 E1 path with actual70C490 history child. A failed
// active vector resize does not suppress the independent history increment.
inline void addActiveHouseInfantry(HouseInfantryOwner& h,const HouseInfantryActor& a,const HouseInfantryStore& store={}){
    a.flag324=1;if(store)store(a.identity,0x324,1);
    if(houseInfantryType(a).flag202)return;requireHouseInfantryKind(a);
    const auto index=houseInfantryIndex(a);++h.count234;if(store)store(h.identity,0x234,h.count234);
    (void)changeHouseInfantryCounter(h.active5440,index,true,store);
    if(index<h.historyCount1270){
        if(index<0||std::size_t(index)>=h.historyA70.size())throw std::invalid_argument("House Infantry history outside owned backing");
        auto& value=h.historyA70[std::size_t(index)];++value;if(store)store(h.identity,0xa70+index*4,value);
    }
}
// Authored storage on each actual mission House. Initialization/allocation are
// supplied; these are not recovered constructors. Views are rebuilt after clones.
struct HouseInfantryAccountingState {
    std::uint32_t count234=0;
    std::vector<std::uint32_t> active5440,registered5480;
    std::array<std::uint32_t,512> historyA70{};
    std::int32_t activeCapacity=0,registeredCapacity=0,historyCount1270=512;
};
// Synchronous borrowed views: no span or callback survives the invocation.
// Host vector allocation is an explicitly supplied service. Kernels still own
// the recovered zeroing and arithmetic after it returns.
template<class F> decltype(auto) withHouseInfantryAccounting(HouseInfantryAccountingState& state,const void* identity,F&& body){
    std::span<std::uint32_t> active=state.active5440,registered=state.registered5480;
    HouseInfantryCounter a{&state.active5440,state.activeCapacity,active,{}},r{&state.registered5480,state.registeredCapacity,registered,{}};
    a.resize8=[&](std::int32_t size,std::uint32_t zero){
        if(zero||size<0||size>512)throw std::invalid_argument("Unsupported owned House Infantry allocation");
        state.active5440.resize(std::size_t(size));state.activeCapacity=size;active=state.active5440;return 1u;
    };
    r.resize8=[&](std::int32_t size,std::uint32_t zero){
        if(zero||size<0||size>512)throw std::invalid_argument("Unsupported owned House Infantry allocation");
        state.registered5480.resize(std::size_t(size));state.registeredCapacity=size;registered=state.registered5480;return 1u;
    };
    HouseInfantryOwner owner{identity,state.count234,a,r,state.historyCount1270,state.historyA70};
    return std::forward<F>(body)(owner);
}

}
