// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/ResidentCellPreparation.hpp"
#include <stdexcept>

namespace ra2 {
void recalculateResidentCell(MapCellAttributes& cell,int levelOverride,
    std::span<std::uint8_t,4> buffer4,std::span<std::uint8_t,10> buffer10,
    const ResidentCellInputs& input,const ResidentCellServices& services) {
    MapAttributeServices child;
    child.tiles=input.tiles;child.landMap=input.landMap;child.overlays=input.overlays;
    child.tubeCount=input.tubeCount;child.cliffMode=input.cliffMode;child.fallback=input.fallback;
    child.store=services.store;
    child.neighborLevel=[&](MapInputPosition p){return mapAttributeCell(p,input.world).level;};
    child.setupLAT=[&](const MapCellAttributes& state) {
        if(services.beforeLAT)services.beforeLAT(state);
        setupMapLAT(cell.input,input.lat,input.directions,input.world,int(input.tiles.size()),
            [&](int tile){if(services.store)services.store(MapAttributeField::Tile,std::uint32_t(tile));});
        return cell.input.tile;
    };
    child.classifyResource=[&](int overlay) {
        if(services.classifyQuery)services.classifyQuery(overlay);
        const MapOverlayType* type=nullptr;
        if(overlay!=-1) {
            if(overlay<0||std::size_t(overlay)>=input.overlays.size())
                throw std::invalid_argument("Missing resident Cell overlay binding");
            type=&input.overlays[std::size_t(overlay)];
        }
        return classifyMapOverlay(overlay,type,input.resources,services.missingResource);
    };
    child.updatePassability=[&](const MapCellAttributes& state) {
        if(services.beforePassability)services.beforePassability(state);
        const bool permitted=mapCellPermitted(state.input.position,true,input.permission,input.world);
        const MapOverlayType* type=nullptr;
        if(state.overlay!=-1) {
            if(state.overlay<0||std::size_t(state.overlay)>=input.overlays.size())
                throw std::invalid_argument("Missing resident Cell passability overlay");
            type=&input.overlays[std::size_t(state.overlay)];
        }
        if(services.occupiedPassability)
            return services.occupiedPassability(cell,permitted,type);
        const int result=overlayCellPassability(state.input,permitted,type,input.wheelSpeeds);
        // The original child stores Cell +0x4C before returning to its parent.
        cell.passability=result;
        if(services.passabilityStore)services.passabilityStore(result);
        return result;
    };
    recalculateMapCellAttributes(cell,levelOverride,buffer4,buffer10,child);
}
}
