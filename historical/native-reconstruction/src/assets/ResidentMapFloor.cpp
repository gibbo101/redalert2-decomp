// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/ResidentMapFloor.hpp"
#include <stdexcept>
namespace ra2 {
MapFinalizationResult finalizeResidentMapWithFloor(const MapFinalizationInputs& input,
    std::span<MapFinalizationCell> cells,MapCellAttributes& fallback,
    std::span<std::uint8_t> buffer4,std::span<std::uint8_t> buffer10,
    const MapFinalizationServices& services,const MapFinalizationFloor& floor) {
    if(services.buildingDistance||floor.buildings.size()!=input.buildings.size()||
       !floor.tableSquareRoot)
        throw std::invalid_argument("Resident floor candidate binding differs");
    auto bound=services;
    bound.buildingDistance=[&](int id,std::size_t b){
        if(floor.beforeDistance)floor.beforeDistance(id,b);
        const auto& cell=cells[std::size_t(id)].attributes.input;
        if(floor.beforeFloor)floor.beforeFloor(id,wallOwnerCellCoordinates(cell.position,0));
        const auto target=mapCellCenterHeight(floor.state,floor.levelHeight,cell);
        const auto& building=floor.buildings[b];
        const auto source=wallOwnerBuildingCoordinates(building.position,building.width,building.height);
        const int distance=wallOwnerCellDistance(source,target,floor.tableSquareRoot);
        if(floor.afterDistance)floor.afterDistance(distance);
        return distance;
    };
    return finalizeResidentMap(input,cells,fallback,buffer4,buffer10,bound);
}
}
