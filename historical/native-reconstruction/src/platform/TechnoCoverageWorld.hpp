// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TechnoCoverage.hpp"
#include "sim/RevealArea.hpp"
#include "render/UnitTypeVisibility.hpp"
namespace ra2 {
struct TechnoCoverageHouseView {
    const std::int32_t& index30;const std::uint8_t& flag134;const std::uint8_t& flag135;
    const std::uint32_t& alliance5674;
};
struct TechnoCoverageWorld {
    const std::int32_t& mode;
    const double& heightScale;
    const RevealAreaWorld& map;
    // Pure borrowed views. They must not query map/gameplay or mirror values.
    std::function<TechnoCoverageHouseView(const void*)> house;
    std::function<TechnoCoverageCell(RevealAreaCell&)> cell;
    // Optional entry/return observations for original differential diagnostics.
    std::function<void(char,std::int32_t,std::int32_t)> query;
    std::function<void(char,std::int32_t)> result;
};
// Composition belongs to the platform boundary because existing scalar House
// decisions are also used by rendering. Simulation remains SDL-free. Bindings
// borrow one map/fallback and actual field references; construction makes no query.
class TechnoCoverageWorldBinding {
    TechnoCoverageServices& target_;
    const TechnoCoverageWorld& world_;
    decltype(TechnoCoverageServices::localHouse) local_;
    decltype(TechnoCoverageServices::allied) allied_;
    decltype(TechnoCoverageServices::projectedHeight) height_;
    decltype(TechnoCoverageServices::cell) cell_;
public:
    TechnoCoverageWorldBinding(TechnoCoverageServices& target,const TechnoCoverageWorld& world)
        :target_(target),world_(world){
        if(!world_.house||!world_.cell)throw std::invalid_argument("Coverage world needs borrowed House/Cell views");
        auto local=[this](const void* p){
            if(world_.query)world_.query('L',0,0);
            bool result=false;
            if(world_.mode)result=p==target_.currentHouse;
            else {const auto h=world_.house(p);result=unitOwnerTypeVisible(0,h.flag134,h.flag135,p==target_.currentHouse);}
            if(world_.result)world_.result('L',result);return std::uint8_t(result);
        };
        auto allied=[this](const void* p,const void* q){
            if(world_.query)world_.query('B',0,0);
            // The original null-current and pointer-equality bypasses must not
            // enter unnecessary borrowed views (which can reject foreign handles).
            bool result=false;
            if(q){if(p==q)result=true;else {const auto a=world_.house(p),b=world_.house(q);
                result=unitOwnerAlliedToCurrent(true,false,a.index30,b.index30,a.alliance5674);}}
            if(world_.result)world_.result('B',result);return std::uint8_t(result);
        };
        auto height=[this](std::int32_t z){if(world_.query)world_.query('Z',z,0);
            const auto result=projectVisibilityHeight(z,world_.heightScale);if(world_.result)world_.result('Z',result);return result;};
        auto cell=[this](std::int16_t x,std::int16_t y){if(world_.query)world_.query('C',x,y);
            auto& c=revealAreaMapCell({x,y},world_.map);if(world_.result)world_.result('C',c.identity);return world_.cell(c);};
        // Allocate every replacement before changing any caller callback.
        decltype(local_) l=local;decltype(allied_) a=allied;decltype(height_) h=height;decltype(cell_) c=cell;
        local_=std::move(target_.localHouse);allied_=std::move(target_.allied);height_=std::move(target_.projectedHeight);cell_=std::move(target_.cell);
        target_.localHouse=std::move(l);target_.allied=std::move(a);target_.projectedHeight=std::move(h);target_.cell=std::move(c);
    }
    ~TechnoCoverageWorldBinding(){target_.localHouse=std::move(local_);target_.allied=std::move(allied_);target_.projectedHeight=std::move(height_);target_.cell=std::move(cell_);}
    TechnoCoverageWorldBinding(const TechnoCoverageWorldBinding&)=delete;
    TechnoCoverageWorldBinding& operator=(const TechnoCoverageWorldBinding&)=delete;
    TechnoCoverageWorldBinding(TechnoCoverageWorldBinding&&)=delete;
    TechnoCoverageWorldBinding& operator=(TechnoCoverageWorldBinding&&)=delete;
};
}
