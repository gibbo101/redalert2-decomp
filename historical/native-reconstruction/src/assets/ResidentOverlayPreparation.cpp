// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/ResidentOverlayPreparation.hpp"
#include <climits>
#include <stdexcept>

namespace ra2 {
void prepareResidentMapOverlays(int version,int width,int height,bool filterCrates,
    std::span<const OverlayTypeInputs> types,OverlayMapPreparationState& state,
    const OverlayMapPreparationInputs& preparation,OverlayPlacementCell& fallback,
    const ResidentCellInputs& input,std::span<const std::uint8_t> frames,
    std::span<std::uint8_t> buffer4,std::span<std::uint8_t> buffer10,
    const ResidentOverlayServices& services) {
    if(!services.attributes||!services.overlay.placement.cell||input.fallback||
       input.world.cells.size()!=262144||!input.world.fallback||
       input.permission.dimension0!=width||input.directions!=services.overlay.wall.directions||
       buffer4.empty()||buffer4.size()%4||buffer4.size()/4>INT_MAX||
       buffer10.size()/10!=buffer4.size()/4||buffer10.size()%10)
        throw std::invalid_argument("Incomplete resident overlay Cell binding");
    auto child=services.overlay;
    auto resident=input;
    const auto& originalLookup=services.overlay.placement.cell;
    const auto attributes=[&](OverlayPlacementCell& cell)->MapCellAttributes&{
        return services.attributes(cell);
    };
    if(&attributes(fallback).input!=input.world.fallback)
        throw std::invalid_argument("Resident overlay fallback differs");
    if(input.overlays.size()!=types.size())throw std::invalid_argument("Resident overlay registries differ");
    for(std::size_t i=0;i<types.size();++i){
        const auto& t=types[i];const auto& a=input.overlays[i];
        if(a.land!=t.land||a.flag1FD!=t.crushable||a.wall!=t.wall||a.tiberium!=t.tiberium||
           a.noUseTileLandType!=t.noUseTileLandType||a.rubble!=t.rubble||a.rock!=t.rock)
            throw std::invalid_argument("Resident overlay type projections differ");
    }
    const auto check=[&](OverlayPlacementCell& c){
        const auto& a=attributes(c);
        if(c.position!=a.input.position||c.overlay!=a.overlay||c.data!=a.overlayData||
           c.slope!=a.input.slope||c.passability!=a.passability)
            throw std::invalid_argument("Resident overlay records disagree");
    };
    check(fallback);
    const auto fallbackStore=input.world.fallbackStore;
    resident.world.fallbackStore=[&](MapInputPosition p){
        fallback.position=p;
        if(fallbackStore)fallbackStore(p);
    };
    OverlayPlacementCell* selected=nullptr;
    child.placement.cell=[&](MapInputPosition p)->OverlayPlacementCell&{
        auto& c=originalLookup(p);auto& a=attributes(c);
        const int index=int(p.y)*512+int(p.x);
        const auto* expected=index>=0&&index<262144?input.world.cells[std::size_t(index)]:nullptr;
        if(!expected)expected=input.world.fallback;
        if(&a.input!=expected)throw std::invalid_argument("Resident overlay lookup associations differ");
        // The supplied placement lookup performs the original fallback position
        // store. Mirror that store before this record can be read by Cell LAT.
        if(&c==&fallback)a.input.position=c.position;
        check(c);selected=&c;return c;
    };
    const auto mirror=[&](OverlayPlacementCell& c,unsigned off){
        auto& a=attributes(c);
        if(off==0x44)a.overlay=c.overlay;
        else if(off==0x11e)a.overlayData=c.data;
        else if(off==0x4c)a.passability=c.passability;
        else if(off==0x11c)a.input.slope=c.slope;
    };
    const auto placementStore=child.placement.store;
    child.placement.store=[&](unsigned role,unsigned off,unsigned size,std::uint32_t value){
        if(role==1){if(!selected)throw std::invalid_argument("Resident overlay store has no Cell");mirror(*selected,off);}
        if(placementStore)placementStore(role,off,size,value);
    };
    const auto readerStore=child.reader.store;
    child.reader.store=[&](OverlayLoadCell& c,std::uint8_t value){
        mirror(static_cast<OverlayPlacementCell&>(c),0x11e);
        if(readerStore)readerStore(c,value);
    };
    const auto wallStore=child.wall.store;
    child.wall.store=[&](MapWallCell& c,unsigned off,unsigned size,std::uint32_t value){
        mirror(static_cast<OverlayPlacementCell&>(c),off);
        if(wallStore)wallStore(c,off,size,value);
    };
    OverlayMapResourceInputs resource{types,input.resources,frames,input.directions};
    OverlayMapResourceServices resourceServices;
    resourceServices.cell=child.placement.cell;
    resourceServices.classifyQuery=services.classifyQuery;
    resourceServices.missing=services.missingResource;
    resourceServices.store=[&](OverlayPlacementCell& c,std::uint8_t value){
        mirror(c,0x11e);if(readerStore)readerStore(c,value);
    };
    child.placement.resource=[&](OverlayPlacementCell& c){
        check(c);if(services.beforeResource)services.beforeResource(c,0);
        const int value=updateLoadedMapResource(c,resource,resourceServices);
        selected=&c;if(services.afterResource)services.afterResource(c,value);
    };
    child.placement.recalculate=[&](OverlayPlacementCell& c,int level){
        selected=&c;check(c);auto& a=attributes(c);
        if(services.beforeRecalculation)services.beforeRecalculation(c,level);
        ResidentCellServices observer;
        observer.classifyQuery=services.classifyQuery;observer.missingResource=services.missingResource;
        observer.store=[&](MapAttributeField field,std::uint32_t value){
            if(field==MapAttributeField::Overlay)c.overlay=a.overlay;
            else if(field==MapAttributeField::OverlayData)c.data=a.overlayData;
            else if(field==MapAttributeField::Slope)c.slope=a.input.slope;
            if(services.attributeStore)services.attributeStore(c,field,value);
        };
        observer.passabilityStore=[&](int value){
            c.passability=value;if(services.passabilityStore)services.passabilityStore(c,value);
        };
        const int index=mapAttributeBufferIndex(a.input.position,width,height,int(buffer4.size()/4));
        auto cellInput=resident;cellInput.fallback=&c==&fallback;
        recalculateResidentCell(a,level,std::span<std::uint8_t,4>(buffer4.data()+std::size_t(index)*4,4),
            std::span<std::uint8_t,10>(buffer10.data()+std::size_t(index)*10,10),cellInput,observer);
        selected=&c;check(c);
    };
    child.wall.recalculate=[&](MapWallCell& c,int level){child.placement.recalculate(static_cast<OverlayPlacementCell&>(c),level);};
    prepareDecodedMapOverlays(version,width,height,filterCrates,types,state,preparation,child);
}
}
