// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/HouseThreat.hpp"
#include "sim/TechnoThreat.hpp"
#include <utility>
namespace ra2 {
// Borrowed fields/services name the same actors used by HouseThreatWorld.
// The caller owns rule, type and actor lifetimes. Map virtual1A4 remains an
// explicit child; this join does not initialize a registry or schedule a rebuild.
struct HouseActorThreatServices {
    const std::int32_t& rulesBE8;
    std::function<const std::int32_t&(const void*)> field564;
    std::function<TechnoThreatServices(const void*)> actor;
};
class HouseActorThreat {
    HouseThreatWorld& grid_;
    const HouseActorThreatServices& services_;
    std::function<std::int32_t(const void*)> prior_;
public:
    HouseActorThreat(HouseThreatWorld& grid,const HouseActorThreatServices& services)
        :grid_(grid),services_(services){
        if(!services_.field564||!services_.actor)
            throw std::invalid_argument("House actor threat needs borrowed actor fields/services");
        std::function<std::int32_t(const void*)> replacement=[this](const void* p){
            const auto fields=services_.actor(p);
            return technoThreat(services_.field564(p),services_.rulesBE8,fields);
        };
        prior_=std::move(grid_.threat2A0);grid_.threat2A0=std::move(replacement);
    }
    ~HouseActorThreat(){grid_.threat2A0=std::move(prior_);}
    HouseActorThreat(const HouseActorThreat&)=delete;
    HouseActorThreat& operator=(const HouseActorThreat&)=delete;
    HouseActorThreat(HouseActorThreat&&)=delete;
    HouseActorThreat& operator=(HouseActorThreat&&)=delete;
    void rebuild(const void* current){rebuildHouseThreatGrid(current,grid_);}
};
}
