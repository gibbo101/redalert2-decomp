// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/ResidentMapFinalization.hpp"
#include <stdexcept>
namespace ra2 {
MapFinalizationResult finalizeResidentMap(const MapFinalizationInputs& input,
    std::span<MapFinalizationCell> cells,MapCellAttributes& fallback,
    std::span<std::uint8_t> buffer4,std::span<std::uint8_t> buffer10,
    const MapFinalizationServices& services) {
    if(input.width<2||input.width>255||input.height<1||input.width+input.height>256||
       input.slots.size()!=262144||input.cell.world.cells.size()!=262144||
       input.cell.world.fallback!=&fallback.input||input.cell.fallback||
       input.cell.cliffMode>2||
       input.cell.permission.dimension0!=input.width||!services.initializeLighting)
        throw std::invalid_argument("Unsupported resident map finalization binding");
    const auto side=std::size_t(input.width+input.height+1),capacity=side*side;
    if(buffer4.size()!=capacity*4||buffer10.size()!=capacity*10)
        throw std::invalid_argument("Resident finalization buffer geometry differs");
    for(const auto& cell:cells)if(cell.attachedTag||&cell.attributes==&fallback)
        throw std::invalid_argument("Resident finalization tag/fallback profile differs");
    for(std::size_t i=0;i<input.slots.size();++i) {
        const int id=input.slots[i];const auto* actual=input.cell.world.cells[i];
        if(id==-1){if(actual)throw std::invalid_argument("Finalization null slot differs");continue;}
        if(id<0||std::size_t(id)>=cells.size())throw std::invalid_argument("Missing finalization Cell");
        const auto& cell=cells[std::size_t(id)].attributes.input;
        if(actual!=&cell||int(cell.position.x)!=int(i%512)||int(cell.position.y)!=int(i/512))
            throw std::invalid_argument("Finalization canonical Cell association differs");
    }
    const auto type=[&](int overlay)->const MapOverlayType*{
        if(overlay==-1)return nullptr;
        if(overlay<0||std::size_t(overlay)>=input.cell.overlays.size())
            throw std::invalid_argument("Missing finalization overlay type");
        return &input.cell.overlays[std::size_t(overlay)];
    };
    for(const auto& cell:cells)type(cell.attributes.overlay);
    const auto classify=[&](int overlay){
        if(services.classifyQuery)services.classifyQuery(overlay);
        return classifyMapOverlay(overlay,type(overlay),input.cell.resources,services.missingResource);
    };
    MapFinalizationResult result;result.cursor=resetTileSweepCursor(input.width);
    const auto visit=[&](){const int id=advanceTileSweepCursor(result.cursor,input.width,input.slots);
        if(services.visit)services.visit(id);return id;};
    const auto parentStore=[&](int id,MapPreparationField f,std::uint32_t n){if(services.parentStore)services.parentStore(id,f,n);};
    for(int id;(id=visit())!=-1;){auto& flags=cells[std::size_t(id)].attributes.input.flags;
        flags&=0xFFCFFFFFu;parentStore(id,MapPreparationField::Flags,flags);}
    result.cursor=resetTileSweepCursor(input.width);
    for(int id;(id=visit())!=-1;) {
        auto& cell=cells[std::size_t(id)];auto& a=cell.attributes;
        cell.field30=0;parentStore(id,MapPreparationField::Field30,0);
        services.initializeLighting(id);a.input.flags&=0xFFFDFFFFu;
        parentStore(id,MapPreparationField::Flags,a.input.flags);
        if(services.beforeResource)services.beforeResource(id);
        MapResourceServices resource;resource.types=input.cell.resources;resource.frameTable=input.frames;
        resource.directions=input.cell.directions;resource.classify=classify;
        resource.neighborOverlay=[&](MapInputPosition p){
            const auto& found=mapAttributeCell(p,input.cell.world);
            if(&found==&fallback.input)return fallback.overlay;
            const auto slot=std::size_t(int(p.y)*512+int(p.x));
            return cells[std::size_t(input.slots[slot])].attributes.overlay;
        };
        resource.store=[&](std::uint8_t n){if(services.attributeStore)services.attributeStore(id,MapAttributeField::OverlayData,n);};
        const int value=updateMapResource(a.input.position,a.overlay,a.overlayData,resource);
        if(services.afterResource)services.afterResource(id,value);
        result.resourceTotal+=std::uint32_t(value);
        if(services.beforeRecalculation)services.beforeRecalculation(id);
        ResidentCellServices observer;observer.classifyQuery=services.classifyQuery;observer.missingResource=services.missingResource;
        observer.beforeLAT=[&](const auto& state){if(services.beforeLAT)services.beforeLAT(id,state);};
        observer.beforePassability=[&](const auto& state){if(services.beforePassability)services.beforePassability(id,state);};
        observer.passabilityStore=[&](int n){if(services.passabilityStore)services.passabilityStore(id,n);};
        observer.store=[&](auto f,auto n){if(services.attributeStore)services.attributeStore(id,f,n);};
        const auto index=std::size_t(mapAttributeBufferIndex(a.input.position,input.width,input.height,int(capacity)));
        recalculateResidentCell(a,-1,std::span<std::uint8_t,4>(buffer4.data()+index*4,4),
            std::span<std::uint8_t,10>(buffer10.data()+index*10,10),input.cell,observer);
        // Recalculation can clear the resource/wall overlay. Never use a type
        // pointer saved before that call for the parent's wall-owner decision.
        const auto* overlay=type(a.overlay);
        if(overlay&&overlay->wall) {
            if(services.beforeOwner)services.beforeOwner(id);
            WallOwnerServices owner;
            if(services.buildingDistance)owner.distance=[&](std::size_t b){return services.buildingDistance(id,b);};
            if(services.buildingOwner)owner.owner=[&](std::size_t b){return services.buildingOwner(id,b);};
            owner.store=[&](int n){if(services.ownerStore)services.ownerStore(id,n);};
            assignMapWallOwner(a.overlay,overlay->wall,cell.wallOwner,input.buildings,owner);
        }
    }
    return result;
}
}
