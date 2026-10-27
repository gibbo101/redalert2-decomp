// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <span>
#include <stdexcept>
#include <string_view>
namespace ra2 {
// Borrow actual fields. Registry/type association and string comparison remain
// explicit services; binding must only return live field views without queries.
struct HouseAllianceType {
    const std::int32_t& countryB8;
    const std::int32_t& parentBC;
    const std::uint8_t& passive1A6;
    std::string_view name24;
};
struct HouseAllianceRecord {
    const void* identity;
    const std::int32_t& index30;
    const void* const& type34;
    const std::uint8_t& field13D;
    const std::uint32_t& allies5674;
};
struct HouseAllianceWorld {
    const std::int32_t& mode;
    const std::int32_t& unrestricted;
    const std::int32_t& houseCount;
    const std::span<const void*>& houses;
    const std::int32_t& typeCount;
    const std::span<const void*>& types;
    std::function<HouseAllianceRecord(const void*)> house;
    std::function<HouseAllianceType(const void*)> type;
    // Named781F20 child. Locale/CRT behavior is not replaced by ASCII folding.
    std::function<std::int32_t(std::string_view,std::string_view)> compareNames;
};
inline const void* houseAllianceSlot(std::span<const void*> slots,std::int32_t i){
    if(i<0||std::size_t(i)>=slots.size())throw std::invalid_argument("House alliance registry exceeds supplied backing");
    if(!slots[std::size_t(i)])throw std::invalid_argument("House alliance registry contains null record");
    return slots[std::size_t(i)];
}
inline HouseAllianceRecord houseAllianceRecord(const HouseAllianceWorld& w,const void* p){
    if(!p||!w.house)throw std::invalid_argument("House alliance needs a nonnull owned House");
    auto record=w.house(p);
    if(record.identity!=p)throw std::invalid_argument("House alliance identity differs");
    return record;
}
inline HouseAllianceType houseAllianceType(const HouseAllianceWorld& w,const void* p){
    if(!p||!w.type)throw std::invalid_argument("House alliance needs an owned type");
    return w.type(p);
}
// Complete4ED760. Save count and backing once, return the first matching typeB8.
template<class Country>
inline const void* findHouseAllianceCountry(std::int32_t country,const std::int32_t& liveCount,
        const std::span<const void*>& liveSlots,const Country& countryB8){
    const auto count=liveCount;if(count<=0)return nullptr;
    const auto slots=liveSlots;
    for(std::int32_t i=0;i<count;++i){
        const auto p=houseAllianceSlot(slots,i);
        if(countryB8(p)==country)return p;
    }
    return nullptr;
}
inline const void* findHouseAllianceCountry(std::int32_t country,const HouseAllianceWorld& w){
    return findHouseAllianceCountry(country,w.houseCount,w.houses,[&](const void* p){
        return houseAllianceType(w,houseAllianceRecord(w,p).type34).countryB8;
    });
}
// Complete67AF90 around named781F20. Return slot ordinal, not the typeB8 value.
// The comparison may replace the live count/backing before the next iteration.
inline std::int32_t findHouseAllianceType(std::string_view name,const HouseAllianceWorld& w){
    if(w.typeCount<=0)return -1;
    for(std::int32_t i=0;;++i){
        const auto p=houseAllianceSlot(w.types,i);
        if(!w.compareNames)throw std::invalid_argument("House alliance needs named string comparison");
        if(!w.compareNames(houseAllianceType(w,p).name24,name))return i;
        if(i+1>=w.typeCount)return -1;
    }
}
// Complete4EC4E0 for nonnull supplied House/type/registry records. Original null
// target falls through to a dereference; the native domain refuses that input.
inline std::uint8_t canMakeHouseAlliance(const void* current,const void* target,const HouseAllianceWorld& w){
    const auto self=houseAllianceRecord(w,current),other=houseAllianceRecord(w,target);
    if(target==current)return 0;
    const auto index=other.index30;
    if(index==self.index30)return 0;
    if(index!=-1&&(self.allies5674&(std::uint32_t(1)<<unsigned(std::uint32_t(index)&31u))))return 0;
    const auto civilian=findHouseAllianceType("Civilian",w);
    if(houseAllianceType(w,other.type34).parentBC==civilian&&w.mode)return 0;
    if(w.unrestricted)return 1;
    if(self.field13D)return 0;
    std::uint32_t eligible=0,allied=0;
    const auto count=w.houseCount;const auto slots=w.houses;
    for(std::int32_t i=0;i<count;++i){
        const auto p=houseAllianceSlot(slots,i);const auto h=houseAllianceRecord(w,p);
        if(h.field13D||houseAllianceType(w,h.type34).passive1A6)continue;
        ++eligible;
        if(p==current||h.index30==self.index30||
                (h.index30!=-1&&(self.allies5674&(std::uint32_t(1)<<unsigned(std::uint32_t(h.index30)&31u)))))++allied;
    }
    return eligible!=allied+1u;
}
}
