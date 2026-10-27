// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayMapResources.hpp"
#include <stdexcept>

namespace ra2 {
int updateLoadedMapResource(OverlayPlacementCell& cell,const OverlayMapResourceInputs& input,
    const OverlayMapResourceServices& services) {
    MapResourceServices child;
    child.directions=input.directions;
    child.types=input.resources;
    child.frameTable=input.frames;
    child.classify=[&](int overlay) {
        if(services.classifyQuery)services.classifyQuery(overlay);
        const OverlayTypeInputs* type=nullptr;
        if(overlay!=-1) {
            if(overlay<0||std::size_t(overlay)>=input.overlays.size())
                throw std::invalid_argument("Missing loaded resource overlay binding");
            type=&input.overlays[std::size_t(overlay)];
        }
        MapOverlayType selected;
        if(type)selected.tiberium=type->tiberium;
        return classifyMapOverlay(overlay,type?&selected:nullptr,input.resources,services.missing);
    };
    child.neighborOverlay=[&](MapInputPosition p) {
        if(!services.cell)throw std::invalid_argument("Missing loaded resource Cell lookup");
        return services.cell(p).overlay;
    };
    child.store=[&](std::uint8_t value) {if(services.store)services.store(cell,value);};
    return updateMapResource(cell.position,cell.overlay,cell.data,child);
}
}
