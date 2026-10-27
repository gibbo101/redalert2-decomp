// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TechnoSight.hpp"
#include "sim/Facing.hpp"
#include "sim/OriginalMath.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace ra2 {
namespace {
std::int32_t originalInteger(double value) {
    constexpr double limit=9223372036854775808.0;
    if(!std::isfinite(value)||value<-limit||value>=limit)return 0;
    return signed32(std::uint32_t(std::uint64_t(std::int64_t(value))));
}
std::int32_t wrappedTimesTen(std::int32_t value) {
    return signed32(std::uint32_t(value)*10u);
}
}
void updateTechnoSight(TechnoSightActor actor,std::uint32_t forwarded1,
        std::uint32_t forwarded2,std::uint32_t explicitHouseOnly,
        const void* explicitHouse,const TechnoSightServices& services) {
    if(!actor.enabled32d||actor.ownerCountryFlag1a6)return;
    if(!services.type||!services.heightDivisor1324)
        throw std::invalid_argument("Techno sight requires type and height-divisor owners");
    const auto event=[&](char kind,std::int32_t value=0){if(services.trace)services.trace(kind,value);};
    const auto divisor=services.heightDivisor1324();
    if(divisor==0||(actor.coordinates88.z==std::numeric_limits<std::int32_t>::min()&&divisor==-1))
        throw std::invalid_argument("Techno sight signed division outside original domain");
    const auto increase=wrappedTimesTen(actor.coordinates88.z/divisor);
    if(increase>actor.heightIncrease378)forwarded1&=0xffffff00u;
    actor.heightIncrease378=std::int8_t(std::uint8_t(increase));event('H',actor.heightIncrease378);
    OriginalRounding rounding;
    const auto type=[&]{event('T');return services.type();};
    const auto integer=[&](double value){const auto result=originalInteger(value);event('F',result);return result;};
    const auto currentType=type();
    volatile double scaledHeight=double(actor.heightIncrease378)*0.01;
    volatile double heightFactor=scaledHeight+1.0;
    std::int32_t range=integer(double(currentType.sight530)*heightFactor);
    const auto veteran=[&]{event('V');return actor.sightTimer118>=1.0&&actor.sightTimer118<2.0;};
    const auto elite=[&]{event('E');return actor.sightTimer118>=2.0;};
    if(veteran()||elite()) {
        const auto promotedType=type();
        bool promoted=false;
        if(veteran()&&promotedType.veteranSight271)promoted=true;
        else if(elite()&&(promotedType.veteranSight271||promotedType.eliteSight283))promoted=true;
        if(promoted) {
            if(!services.veteranSight5a0)
                throw std::invalid_argument("Promoted Techno sight requires VeteranSight owner");
            const auto multiplier=services.veteranSight5a0();event('M');
            if(!std::isnan(multiplier)&&multiplier!=0.0)
                range=integer(double(range)*multiplier);
        }
    }
    const auto reveal=[&](const void* house){
        if(!services.revealArea)throw std::invalid_argument("Techno sight reveal-area service required");
        services.revealArea({actor.coordinates88,range,house,forwarded1,forwarded2,0,1,0});
    };
    if(!actor.sightActive1e4) {
        actor.sightActive1e4=1;event('A',1);
        actor.lastSightCoordinates1e8.x=actor.coordinates88.x;event('X',actor.coordinates88.x);
        actor.lastSightRange1f4=range;event('R',range);
        actor.lastSightCoordinates1e8.y=actor.coordinates88.y;event('Y',actor.coordinates88.y);
        actor.lastSightCoordinates1e8.z=actor.coordinates88.z;event('Z',actor.coordinates88.z);
        if(!range)return;
        if(explicitHouseOnly&&explicitHouse)reveal(explicitHouse);
        else reveal(actor.owner);
        return;
    }
    if(explicitHouseOnly&&range&&explicitHouse)reveal(explicitHouse);
}
}
