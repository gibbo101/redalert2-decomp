// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayMapPreparation.hpp"
#include <climits>
#include <stdexcept>
namespace ra2 {
void prepareDecodedMapOverlays(int version,int width,int height,bool filterCrates,
    std::span<const OverlayTypeInputs> types,OverlayMapPreparationState& state,
    const OverlayMapPreparationInputs& input,const OverlayMapPreparationServices& services){
    if(!state.objects.empty())throw std::invalid_argument("Overlay map preparation requires empty object storage");
    for(const auto& r:state.registries)if(r.count||r.slots.size()>INT_MAX)
        throw std::invalid_argument("Overlay map preparation requires empty registries");
    if(!services.placement.cell)throw std::invalid_argument("Missing shared overlay Cell storage");
    auto lifetime=services.lifetime;
    const auto expired=lifetime.expired;
    lifetime.expired=[&](unsigned id){
        if(services.currentObject)services.currentObject(id);
        if(!expired)throw std::invalid_argument("Missing overlay expiration service");
        expired(id);
    };
    auto reader=services.reader;
    reader.cell=[&](MapInputPosition p)->OverlayLoadCell&{return services.placement.cell(p);};
    reader.construct=[&](unsigned slot,MapInputPosition p,int flag){
        if(slot>=types.size()||state.objects.size()>=unsigned(INT_MAX))
            throw std::invalid_argument("Overlay map temporary object bound exceeded");
        const unsigned id=unsigned(state.objects.size())+1;
        state.objects.emplace_back();auto& item=state.objects.back();item.base.flags14=input.initialFlags;
        if(services.currentObject)services.currentObject(id);
        auto placement=services.placement;
        placement.base=[&](auto& actor){
            constructOverlayObjectBase(actor,item.base,input.invalidWorld,input.resourceTag,id,
                {&state.registries[0],&state.registries[1],&state.registries[2],&state.registries[3]},lifetime);
        };
        placement.identityCounter=input.identityProvider?&state.identityCounter:nullptr;
        placement.grow=[&](int capacity){return lifetime.grow&&std::uint8_t(lifetime.grow(6,capacity));};
        placement.retire=[&](auto& actor){retireLoadedOverlayObject(actor,item.base,id,state.registries[4],lifetime);};
        const auto& type=types[slot];
        if(type.wall){
            LoadedWallPlacementServices wall;wall.object=placement;wall.currentOwner=input.currentOwner;
            wall.livePlacementFlag=&state.placementFlag;wall.directions=services.wall.directions;
            auto update=services.wall;
            update.cell=[&](MapInputPosition q)->MapWallCell&{return services.placement.cell(q);};
            wall.updateWall=[&](auto& cell,std::uint8_t argument){updateMapWall(cell,argument,update);};
            constructLoadedMapWall(item.actor,type,p,input.invalidCell,flag,state.placementFlag,id,
                state.registries[5],input.enabled,wall);
        }else constructLoadedMapOverlay(item.actor,type,p,input.invalidCell,flag,state.placementFlag,id,
            state.registries[5],input.enabled,placement);
    };
    reader.cleanup=[&]{
        if(services.reader.cleanup)services.reader.cleanup();
        std::vector<TransientMapOverlay*> actors;actors.reserve(state.objects.size());
        for(auto& item:state.objects)actors.push_back(&item.actor);
        cleanupLoadedOverlayObjects(actors,state.registries[4],state.registries[5],lifetime);
    };
    loadDecodedMapOverlays(version,width,height,filterCrates,types,reader);
}
}
