// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/HouseActorThreat.hpp"
#include "sim/ObjectCurrentCell.hpp"
namespace ra2 {
struct HouseActorThreatCellServices {
    // Pure borrowed actor field access; binding/access must make no map query.
    std::function<const Coord&(const void*)> position88;
    // Bind actual coordinate lookup to the same map/fallback/count owners.
    // The returned view borrows the returned Cell's position24 words.
    std::function<HouseThreatCell(Coord)> coordinateCell;
};
// Scoped join for the grid's stock Object virtual1A4. Registry, storage and all
// startup remain caller-owned; there is no production scheduler or map mirror.
class HouseActorThreatCells {
    HouseThreatWorld& grid_;
    const HouseActorThreatCellServices& services_;
    std::function<HouseThreatCell(const void*)> prior_;
public:
    HouseActorThreatCells(HouseThreatWorld& grid,const HouseActorThreatCellServices& services)
        :grid_(grid),services_(services){
        if(!services_.position88||!services_.coordinateCell)
            throw std::invalid_argument("House actor Cell needs borrowed coordinates and map lookup");
        std::function<HouseThreatCell(const void*)> replacement=[this](const void* actor){
            return objectCurrentCell(services_.position88(actor),services_.coordinateCell);
        };
        prior_=std::move(grid_.objectCell1A4);grid_.objectCell1A4=std::move(replacement);
    }
    ~HouseActorThreatCells(){grid_.objectCell1A4=std::move(prior_);}
    HouseActorThreatCells(const HouseActorThreatCells&)=delete;
    HouseActorThreatCells& operator=(const HouseActorThreatCells&)=delete;
    HouseActorThreatCells(HouseActorThreatCells&&)=delete;
    HouseActorThreatCells& operator=(HouseActorThreatCells&&)=delete;
};
}
