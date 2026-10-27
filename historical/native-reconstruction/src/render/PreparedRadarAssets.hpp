// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/PreparedTerrainMap.hpp"
#include "render/CellRadarColor.hpp"
#include "render/OverlayRadarColor.hpp"

namespace ra2 {
// Synchronous borrowed asset services on the application's prepared owners.
// Caller supplies resident search, brightness and output observation separately.
// Primary-only tiles/variant0 are explicit prepared-map policies, not recovered
// startup. No nonlazy startup loop or animation owner is synthesized here.
inline void bindPreparedRadarAssets(CellRadarColorServices& services,
        PreparedTerrainMap& map,const AssetStore& store,int theater,
        const std::function<void(int)>& missingResource={}){
    const auto overlay=[&map](int id)->OverlayTypeInputs&{
        if(id<0||std::size_t(id)>=map.overlayInputs.size())throw std::invalid_argument("Radar overlay outside prepared registry");
        return map.overlayInputs[std::size_t(id)];
    };
    services.primary=[&map](int id){
        if(id<0||std::size_t(id)>=map.tileImages.size())throw std::invalid_argument("Radar tile outside prepared registry");return id;
    };
    services.type=[&map](int id)->TileSweepType&{
        if(id<0||std::size_t(id)>=map.tileImages.size())throw std::invalid_argument("Radar type outside prepared registry");return map.tileImages[std::size_t(id)];
    };
    services.load52B560=[](int){throw std::invalid_argument("Prepared radar lazy TMP installation unbound");};
    services.variant4767A0=[](const MapCellInput&,int,int variants){
        if(variants!=1)throw std::invalid_argument("Prepared radar alternate startup unbound");return 0;
    };
    services.overlay279=[overlay](int id){return overlay(id).tiberium;};
    services.overlayAlternate26C=[overlay](int id)->const Data*{
        if(overlay(id).cellAnim)throw std::invalid_argument("Prepared radar animation owner unbound");return nullptr;
    };
    services.overlay5DD000=[&map,&store,overlay,theater](int id,std::uint32_t frame){
        auto& type=overlay(id);OverlayRadarColorServices image;
        image.primaryImage=[&map,&store,id,theater]()->const Data*{
            (void)map.demandOverlayImage(store,id,theater);auto& data=map.overlayImages[std::size_t(id)];return data?&*data:nullptr;
        };
        image.animationImage=[](std::uint32_t)->const Data*{throw std::invalid_argument("Prepared radar fallback animation owner unbound");};
        RadarRGB output{};overlayRadarColor(type,frame,output,image);return output;
    };
    services.resource5DC0B0=[&map,overlay,missingResource](int id){
        return classifyOverlayResource(id,id==-1?nullptr:&overlay(id),map.resourceTypes,missingResource);
    };
}
}
