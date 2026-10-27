// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TechnoCoverage.hpp"
#include "sim/MissionBuildingTarget.hpp"
namespace ra2 {
enum class StockCoverageKind : int { Building=6,Infantry=15 };
struct StockTechnoCoverageServices {
    const void* const& type;
    // Pure borrowed type/Owner/Building views; binding makes no queries.
    std::function<const std::int8_t&(const void*)> rangeADE;
    std::function<const void*()> owner1B4;
    std::function<MissionBuildingTarget()> building;
    const MissionBuildingTargetServices& buildingServices;
};
// Actual stock virtual30C/80->84/3C join. Kind is an explicit supplied stock
// vtable association, not an extra gameplay query or inferred type identity.
class StockTechnoCoverageBinding {
    TechnoCoverageServices& target_;
    StockCoverageKind kind_;
    const StockTechnoCoverageServices& services_;
    decltype(TechnoCoverageServices::allowed30C) allowed_;
    decltype(TechnoCoverageServices::typeRangeADE) range_;
    decltype(TechnoCoverageServices::owner3C) owner_;
public:
    StockTechnoCoverageBinding(TechnoCoverageServices& target,StockCoverageKind kind,
            const StockTechnoCoverageServices& services):target_(target),kind_(kind),services_(services){
        if((kind!=StockCoverageKind::Infantry&&kind!=StockCoverageKind::Building)||!services.rangeADE||!services.owner1B4)
            throw std::invalid_argument("Missing stock coverage association/view");
        decltype(allowed_) allowed=[this]()->std::uint8_t{
            if(kind_==StockCoverageKind::Infantry)return 0; // Complete6CD6E0 low byte.
            if(!services_.building)throw std::invalid_argument("Missing coverage Building view");
            return missionBuildingAvailable(services_.building(),services_.buildingServices);
        };
        decltype(range_) range=[this]{return services_.rangeADE(services_.type);};
        decltype(owner_) owner=[this]{return services_.owner1B4();};
        allowed_=std::move(target_.allowed30C);range_=std::move(target_.typeRangeADE);owner_=std::move(target_.owner3C);
        target_.allowed30C=std::move(allowed);target_.typeRangeADE=std::move(range);target_.owner3C=std::move(owner);
    }
    ~StockTechnoCoverageBinding(){target_.allowed30C=std::move(allowed_);target_.typeRangeADE=std::move(range_);target_.owner3C=std::move(owner_);}
    StockTechnoCoverageBinding(const StockTechnoCoverageBinding&)=delete;
    StockTechnoCoverageBinding& operator=(const StockTechnoCoverageBinding&)=delete;
    StockTechnoCoverageBinding(StockTechnoCoverageBinding&&)=delete;
    StockTechnoCoverageBinding& operator=(StockTechnoCoverageBinding&&)=delete;
};
}
