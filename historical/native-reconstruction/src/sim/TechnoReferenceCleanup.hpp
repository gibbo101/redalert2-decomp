// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <bit>
#include <cstdint>
#include <functional>
#include <stdexcept>
namespace ra2 {
struct TechnoReferenceTeam {
    const void* identity;
    const void*& target3C;
    const void*& target40;
};
struct TechnoReferenceAircraft {
    std::uint32_t& wordA8;
    std::uint8_t& byte5BA;
};
struct TechnoReferenceCleanupServices {
    const std::int32_t& footCount;
    const std::int32_t& teamCount;
    // Each slot callback rereads the live backing; initial order is separate.
    std::function<const void*(std::int32_t)> footSlot;
    std::function<const void*(const void*)> target228;
    std::function<void(const void*)> action1E0;
    std::function<std::int32_t(const void*)> kind2C,mission98;
    std::function<TechnoReferenceAircraft(const void*)> aircraft;
    std::function<void(const void*,const void*)> target370;
    std::function<TechnoReferenceTeam(std::int32_t)> teamSlot;
    std::function<void(const void*,std::int64_t,std::uint32_t,const void*)> store;
};
template<class F> inline const F& requireReferenceCleanup(const F& f){
    if(!f)throw std::invalid_argument("Reference cleanup entered child unbound");return f;
}
// Complete6D7C80. Fixed reverse bounds, live backing per iteration and saved Foot
// identity across children. Children/construction are explicit separate evidence.
inline void clearTechnoReferences(const void* subject,const TechnoReferenceCleanupServices& s){
    const auto last=[](std::int32_t count){return std::bit_cast<std::int32_t>(std::uint32_t(count)-1u);};
    const auto put=[&](const void* p,std::int64_t off){if(s.store)s.store(p,off,0,nullptr);};
    for(auto i=last(s.footCount);i>=0;--i){
        const auto foot=requireReferenceCleanup(s.footSlot)(i);
        if(!foot)throw std::invalid_argument("Reference cleanup null Foot slot");
        if(requireReferenceCleanup(s.target228)(foot)!=subject)continue;
        requireReferenceCleanup(s.action1E0)(foot);
        if(requireReferenceCleanup(s.kind2C)(foot)==2&&requireReferenceCleanup(s.mission98)(foot)==25){
            auto fields=requireReferenceCleanup(s.aircraft)(foot);
            fields.wordA8=0;put(foot,0xa8);
            fields.byte5BA=0;put(foot,0x5ba);
        }
        if(s.target228(foot)==subject)requireReferenceCleanup(s.target370)(foot,nullptr);
    }
    for(auto i=last(s.teamCount);i>=0;--i){
        auto team=requireReferenceCleanup(s.teamSlot)(i);
        if(!team.identity)throw std::invalid_argument("Reference cleanup null Team slot");
        if(team.target3C==subject){team.target3C=nullptr;put(team.identity,0x3c);}
        if(team.target40==subject){team.target40=nullptr;put(team.identity,0x40);}
    }
}
}
