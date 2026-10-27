// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Drive.hpp"
#include <functional>
#include <stdexcept>
namespace ra2 {
// Borrowed original fields, not a replacement Object owner/layout.
struct ObjectUnlimboView {
    const void* identity;
    std::uint8_t& marked74;
    std::uint8_t& redraw75;
    std::uint8_t& limbo76;
    std::uint8_t& active7d;
};
struct ObjectUnlimboType {
    const void* alphaAC=nullptr;
    std::uint8_t logic204=0,terrain281=0,radial20a=0;
};
struct ObjectUnlimboServices {
    const std::uint8_t& enabled;
    const std::int32_t& loading;
    const std::int32_t& sessionMode;
    std::function<const void*(Coord)> mapCell548000;
    std::function<std::int32_t(const void*,int,int,int,int)> permission194;
    std::function<const ObjectUnlimboType*()> type84;
    std::function<Coord(const ObjectUnlimboType&,Coord)> adjust6c;
    std::function<void(Coord)> setLocation19c;
    std::function<std::uint32_t(int)> mark11c;
    std::function<std::int32_t()> layer74;
    std::function<void()> submit499a40;
    std::function<std::int32_t()> kind2c;
    std::function<std::int32_t()> auxiliary10;
    std::function<void(std::uint32_t)> logic53e330;
    // Original inline alpha block is a renderer service in portable code.
    std::function<void(const void*)> alphaPlacement;
    std::function<void(int,std::uint8_t)> store;
};
// Complete5D3890 parent paths excluding entered radial-indicator creation.
// Child placement/Mark/layer/logic services have their own evidence boundaries.
// The second original argument is unused on these paths.
inline bool objectUnlimbo(ObjectUnlimboView o,Coord input,std::uint32_t,
        const ObjectUnlimboServices& s){
    if(!s.enabled||!o.limbo76||o.marked74)return false;
    if(!s.loading){
        if(!s.mapCell548000||!s.permission194)throw std::invalid_argument("Object Unlimbo permission unbound");
        const auto* cell=s.mapCell548000(input);
        if(s.permission194(cell,-1,-1,0,0)!=0)return false;
    }
    const auto store=[&](int off,std::uint8_t v){if(s.store)s.store(off,v);};
    o.limbo76=0;store(0x76,0);o.redraw75=0;store(0x75,0);
    if(!s.type84||!s.setLocation19c||!s.mark11c)throw std::invalid_argument("Object Unlimbo children unbound");
    const auto* type=s.type84();auto adjusted=input;
    if(type){if(!s.adjust6c)throw std::invalid_argument("Object Unlimbo adjustment unbound");adjusted=s.adjust6c(*type,input);}
    s.setLocation19c(adjusted);
    if(!std::uint8_t(s.mark11c(1))){o.limbo76=1;store(0x76,1);return false;}
    if(!o.active7d)return true;
    if(!s.layer74)throw std::invalid_argument("Object Unlimbo layer unbound");
    if(s.layer74()!=-1){if(!s.submit499a40)throw std::invalid_argument("Object Unlimbo submission unbound");s.submit499a40();}
    if(type){
        if(type->logic204){
            if(!s.kind2c)throw std::invalid_argument("Object Unlimbo kind unbound");
            bool logic=s.kind2c()!=36;
            if(!logic)logic=s.kind2c()==36&&type->terrain281;
            if(logic){
                if(s.sessionMode!=0&&s.sessionMode!=5){
                    if(!s.auxiliary10)throw std::invalid_argument("Object Unlimbo auxiliary query unbound");
                    logic=s.auxiliary10()!=-2;
                }
                if(logic){if(!s.logic53e330)throw std::invalid_argument("Object Unlimbo logic registration unbound");s.logic53e330(0);}
            }
        }
        if(type->alphaAC){if(!s.alphaPlacement)throw std::invalid_argument("Object Unlimbo AlphaImage unbound");s.alphaPlacement(o.identity);}
    }
    const auto* late=s.type84();
    if(!late)throw std::invalid_argument("Object Unlimbo final Type dereference is null");
    if(late->radial20a)throw std::invalid_argument("Object Unlimbo radial indicator creation unrecovered");
    return true;
}
}
