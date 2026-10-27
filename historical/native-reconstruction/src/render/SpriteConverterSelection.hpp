// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <stdexcept>
namespace ra2 {
// Pure borrowed fields/identities; callbacks do not create owners or perform
// additional game queries. Only the named virtual children may mutate state.
struct SpriteConverterSelectionServices {
    std::function<const void*()> type80,owner1b4,currentHouseA35db4,globalBackingAB6EFC;
    std::function<const void*(const void*)> schemesB8c,typeBacking4,converter30c;
    std::function<std::int32_t(const void*)> index15f40;
    // Original32-bit scaled table offset, not a host-sized element index.
    std::function<const void*(const void*,std::uint32_t)> schemeAtOffset;
    std::function<std::uint8_t(const void*)> ownerPredicate3d4;
    std::function<const void*(std::int32_t)> houseCC;
};
// Complete6D1480. Table backing/domain checks are host safety, not invented
// fallback semantics. In particular CC(1) is called twice on its positive path.
inline const void* selectSpriteConverter(const SpriteConverterSelectionServices& s){
    const auto need=[]<class F>(const F& f)->const F&{if(!f)throw std::invalid_argument("Sprite converter selection field/child missing");return f;};
    const auto type=need(s.type80)();
    const auto owner=need(s.owner1b4)();
    const auto table=need(s.schemesB8c)(type);
    const auto savedIndex=need(s.index15f40)(owner);
    if(table){
        const auto backing=need(s.typeBacking4)(table);
        return need(s.converter30c)(need(s.schemeAtOffset)(backing,std::uint32_t(savedIndex)*4u));
    }
    if(!need(s.ownerPredicate3d4)(need(s.currentHouseA35db4)())&&need(s.houseCC)(1)){
        const auto alternate=need(s.houseCC)(1);
        const auto index=need(s.index15f40)(alternate);
        const auto backing=need(s.globalBackingAB6EFC)();
        return need(s.converter30c)(need(s.schemeAtOffset)(backing,std::uint32_t(index)*4u));
    }
    const auto backing=need(s.globalBackingAB6EFC)();
    return need(s.converter30c)(need(s.schemeAtOffset)(backing,std::uint32_t(savedIndex)*4u));
}
}
