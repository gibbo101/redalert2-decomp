// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TechnoSightRemoval.hpp"
#include <stdexcept>

namespace ra2 {
void removeTechnoSight(TechnoSightRemovalActor actor,std::uint32_t forwarded1,
        std::uint32_t forwarded2,std::uint32_t explicitHouseOnly,
        const void* explicitHouse,const TechnoSightRemovalServices& services) {
    if(!actor.enabled32d||actor.ownerCountryFlag1a6)return;
    const auto event=[&](char kind,std::int32_t value=0){if(services.trace)services.trace(kind,value);};
    const bool explicitOnly=std::uint8_t(explicitHouseOnly)!=0;
    const auto reveal=[&](const void* house){
        if(!services.revealArea)throw std::invalid_argument("Techno sight removal requires reveal-area service");
        services.revealArea({actor.lastSightCoordinates1e8,actor.lastSightRange1f4,
            house,forwarded1,forwarded2,0,1,1});
    };
    if(actor.sightActive1e4){
        actor.sightActive1e4=0;event('A',0);
        if(!actor.lastSightRange1f4)return;
        if(explicitOnly&&explicitHouse)reveal(explicitHouse);
        else reveal(actor.owner);
        return;
    }
    if(explicitOnly&&actor.lastSightRange1f4&&explicitHouse)reveal(explicitHouse);
}
}
