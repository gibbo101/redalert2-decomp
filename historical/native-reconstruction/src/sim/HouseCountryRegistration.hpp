// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <bit>
#include <cstdint>
#include <functional>
#include <span>
#include <stdexcept>
#include <string>
namespace ra2 {
// Selected native fields on one persistent country Type, not its original ABI.
// Name, country114 and INI/list startup are supplied separately from registration.
struct HouseCountryType {
    std::string name;
    std::int32_t indexB4=-1,countryB8=-1;
    float costInfantry114=1.f;
};
struct HouseCountryRegistration {
    const void* identity;
    std::int32_t& count;
    std::int32_t& capacity;
    std::uint8_t& allocated;
    std::int32_t& increment;
    std::span<HouseCountryType*>& slots;
    std::function<std::uint32_t(std::int32_t,std::uint32_t)> resize;
    // Ordered observation: owner, offset, raw value, optional slot identity.
    std::function<void(const void*,std::int64_t,std::uint32_t,const void*)> store;
};
// Registration suffix4F9298..4F9345 of the complete country constructor.
// Constructor prefix/base, defaults, INI loading and list order are not recovered
// by this kernel. It does not equate House30 with countryB8.
inline void registerHouseCountryType(HouseCountryType& type,HouseCountryRegistration& r){
    const auto put=[&](const void* p,std::int64_t off,std::uint32_t v,const void* q=nullptr){if(r.store)r.store(p,off,v,q);};
    const auto check=[&](std::int32_t count){if(count<0||std::size_t(count)>r.slots.size())throw std::invalid_argument("Country registry count outside owned backing");};
    auto count=r.count;check(count);bool append=count<r.capacity;
    if(!append&&(r.allocated||!r.capacity)&&r.increment>0){
        if(!r.resize)throw std::invalid_argument("Country registry growth unbound");
        const auto size=std::bit_cast<std::int32_t>(std::uint32_t(r.capacity)+std::uint32_t(r.increment));
        const auto result=r.resize(size,0);count=r.count;check(count);
        append=std::uint8_t(result)!=0;
    }
    if(append){
        if(std::size_t(count)>=r.slots.size())throw std::invalid_argument("Country append outside owned backing");
        const auto index=count;r.count=std::bit_cast<std::int32_t>(std::uint32_t(count)+1u);
        put(r.identity,16,std::uint32_t(r.count));
        r.slots[std::size_t(index)]=&type;put(r.identity,0x1000+4ll*index,0,&type);
        count=r.count;
    }
    check(count);const auto slots=r.slots;
    std::int32_t first=-1;
    for(std::int32_t i=0;i<count;++i)if(slots[std::size_t(i)]==&type){first=i;break;}
    type.countryB8=first;put(&type,0xb8,std::uint32_t(first));
    // The original independently reloads count/backing for its second scan.
    count=r.count;check(count);const auto secondSlots=r.slots;first=-1;
    for(std::int32_t i=0;i<count;++i)if(secondSlots[std::size_t(i)]==&type){first=i;break;}
    type.indexB4=first;put(&type,0xb4,std::uint32_t(first));
}
}
