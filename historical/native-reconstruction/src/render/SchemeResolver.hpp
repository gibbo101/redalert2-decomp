// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceRefreshMarks.hpp"
#include "sim/StringLookup.hpp"
namespace ra2 {
struct SchemeResolverWorld {
    const std::span<const SurfaceMarkScheme*>& registryAB6EFC;
    const std::int32_t& countAB6F08;
    const std::uint32_t& localeB2B098;
    // Pure borrowed fields. Names supply a trailing NUL, as in StringLookup.
    std::function<std::string_view(const SurfaceMarkScheme*)> name304;
    std::function<std::int32_t(const SurfaceMarkScheme*)> category310;
    std::function<void(std::uint32_t,const SurfaceMarkScheme*,int)> afterCompare;
    std::function<void(std::uint32_t,const SurfaceMarkScheme*,std::int32_t)> afterCategory;
};
// Complete663D30, actual781F20 locale-zero comparison reused. Initial registry,
// records and name storage remain supplied. A bound limits host execution only;
// it never substitutes a result for an unsupported original traversal.
inline const SurfaceMarkScheme* resolveSurfaceScheme(std::string_view key,
        std::int32_t category,const SchemeResolverWorld& w){
    if(w.countAB6F08<=0)return nullptr;
    auto slots=w.registryAB6EFC;
    const auto slot=[](std::span<const SurfaceMarkScheme*> s,std::uint32_t i){
        if(i>=s.size()||!s[i])throw std::invalid_argument("Scheme registry slot outside supplied backing");
        return s[i];
    };
    for(std::uint32_t i=0;;){
        if(i>=4096)throw std::invalid_argument("Scheme resolver execution bound");
        const auto before=slot(slots,i);
        if(!w.name304||w.localeB2B098)throw std::invalid_argument("Scheme comparator requires name and locale zero");
        const auto comparison=compareStringLookupKeys(key,w.name304(before));
        if(w.afterCompare)w.afterCompare(i,before,comparison);
        // EAX reload at663D5C happens even when the names differ. This saved
        // registry feeds category, return and the next loop's name load.
        slots=w.registryAB6EFC;
        if(!comparison){
            const auto current=slot(slots,i);
            if(!w.category310)throw std::invalid_argument("Missing scheme category view");
            const auto actual=w.category310(current);
            if(w.afterCategory)w.afterCategory(i,current,actual);
            if(actual==category)return slot(slots,i);
        }
        ++i;
        if(std::int64_t(i)>=w.countAB6F08)return nullptr;
    }
}
// Explicit borrowed fixed-key service; construction makes no registry queries.
class SchemeResolverBinding {
    SurfaceMarkServices& marks_;
    decltype(SurfaceMarkServices::resolve663D30) saved_;
public:
    SchemeResolverBinding(SurfaceMarkServices& marks,const SchemeResolverWorld& world,
            std::string_view key,const std::function<void(const SurfaceMarkScheme*)>& returned):marks_(marks){
        decltype(saved_) replacement=[&world,key,&returned](std::uint32_t category){
            const auto result=resolveSurfaceScheme(key,std::bit_cast<std::int32_t>(category),world);
            if(returned)returned(result);return result;
        };
        saved_=std::move(marks_.resolve663D30);marks_.resolve663D30=std::move(replacement);
    }
    ~SchemeResolverBinding(){marks_.resolve663D30=std::move(saved_);}
    SchemeResolverBinding(const SchemeResolverBinding&)=delete;
    SchemeResolverBinding& operator=(const SchemeResolverBinding&)=delete;
    SchemeResolverBinding(SchemeResolverBinding&&)=delete;
    SchemeResolverBinding& operator=(SchemeResolverBinding&&)=delete;
};
}
