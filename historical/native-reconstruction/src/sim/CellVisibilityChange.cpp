// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/CellVisibilityChange.hpp"
#include "sim/Facing.hpp"
#include <stdexcept>

namespace ra2 {
namespace {
CellVisibilityChangeCell& lookup(TerrainCellPoint point,
        const CellVisibilityChangeWorld& world) {
    if(world.cells.size()!=262144||!world.fallback)
        throw std::invalid_argument("Cell visibility change requires complete map");
    const auto index=signed32(std::uint32_t(std::int32_t(point.y))*512u+
        std::uint32_t(std::int32_t(point.x)));
    CellVisibilityChangeCell* cell=nullptr;
    if(index>=0&&index<262144)cell=world.cells[std::size_t(index)];
    if(!cell){world.fallback->point=point;if(world.fallbackStore)world.fallbackStore(point);cell=world.fallback;}
    if(world.query)world.query(point,cell->identity);
    return *cell;
}
void decrementVisibility(CellVisibilityChangeCell& cell,
        const CellVisibilityChangeServices& services) {
    const auto event=[&](char kind,std::int32_t a=0,std::int32_t b=0,std::int32_t c=0){
        if(services.trace)services.trace(kind,a,b,c);
    };
    if(cell.counter130==1){cell.counter130=0;event('C',cell.identity,0);}
    cell.counter130=signed32(std::uint32_t(cell.counter130)-1u);
    event('C',cell.identity,cell.counter130);
    if(!(cell.flags12c&8u)||!(cell.flags12c&0x10u)) {
        if(cell.counter130<=0) {
            cell.flags12c=(cell.flags12c&0xffffff00u)|
                std::uint8_t(cell.flags12c|0x18u);
            event('F',cell.identity,signed32(cell.flags12c));
        }
    } else if(cell.counter130<=0&&(cell.flags140&0x20u)) {
        cell.flags140=(cell.flags140&0xffffff00u)|
            std::uint8_t(cell.flags140&0xdfu);
        event('G',cell.identity,signed32(cell.flags140));
    }
}
void incrementVisibility(CellVisibilityChangeCell& cell,
        const CellVisibilityChangeServices& services) {
    const auto event=[&](char kind,std::int32_t a=0,std::int32_t b=0,std::int32_t c=0){if(services.trace)services.trace(kind,a,b,c);};
    const auto old=cell.counter130;
    if(old==-1){cell.counter130=0;event('C',cell.identity,0);}
    cell.counter130=signed32(std::uint32_t(cell.counter130)+1u);event('C',cell.identity,cell.counter130);
    if(cell.counter130>cell.maximum134){cell.counter130=cell.maximum134;event('C',cell.identity,cell.counter130);}
    if(old<=0&&cell.counter130>0){cell.flags140=(cell.flags140&0xffffff00u)|std::uint8_t(cell.flags140|0x20u);event('G',cell.identity,signed32(cell.flags140));}
}
}
bool changeCellVisibilityWithLiveRefreshFlags(TerrainCellPoint point,int house,
        std::uint32_t finalArgument,const CellVisibilityChangeWorld& world,
        const std::function<std::uint32_t()>& scenarioFlags,
        const CellVisibilityChangeServices& services) {
    if(!services.visibilityValue||!services.redraw||!services.discover)
        throw std::invalid_argument("Cell visibility change services are incomplete");
    const auto event=[&](char kind,std::int32_t a=0,std::int32_t b=0,std::int32_t c=0){
        if(services.trace)services.trace(kind,a,b,c);
    };
    auto& cell=lookup(point,world);
    const auto oldFlags140=cell.flags140;
    const bool oldBit1Clear=(oldFlags140&2u)==0;
    const bool notify=oldBit1Clear||(cell.flags12c&8u)==0;
    cell.flags140=(oldFlags140&0xffffff00u)|
        std::uint8_t((oldFlags140&0xffu&0xbfu)|2u);
    event('G',cell.identity,signed32(cell.flags140));
    if(std::uint8_t(finalArgument))incrementVisibility(cell,services);else decrementVisibility(cell,services);
    bool changed=notify;
    const auto primary=services.visibilityValue(point,false);event('V',0,primary);
    if(primary!=cell.primary120){cell.primary120=primary;changed=true;event('P',cell.identity,primary);}
    if(cell.primary120==0xffu){
        cell.flags12c=(cell.flags12c&0xffffff00u)|std::uint8_t(cell.flags12c|0x10u);
        event('F',cell.identity,signed32(cell.flags12c));
    }
    const auto secondary=services.visibilityValue(point,true);event('V',1,secondary);
    if(secondary!=cell.secondary121){cell.secondary121=secondary;changed=true;event('S',cell.identity,secondary);}
    if(cell.secondary121==0xffu){
        cell.flags140=(cell.flags140&0xffffff00u)|std::uint8_t(cell.flags140|1u);
        event('G',cell.identity,signed32(cell.flags140));
    }
    if(changed){services.redraw(cell.identity);services.discover(cell.identity,house,notify);}
    if((cell.flags140&2u)&&oldBit1Clear) {
        if(!scenarioFlags)throw std::invalid_argument("Cell visibility change live scenario flags required");
        if(scenarioFlags()&0x1000u) {
            if(!services.refresh)throw std::invalid_argument("Cell visibility change refresh service required");
            services.refresh(cell.identity);
        }
    }
    return changed;
}
bool changeCellVisibility(TerrainCellPoint point,int house,
        std::uint32_t finalArgument,const CellVisibilityChangeWorld& world,
        std::uint32_t refreshRules,const CellVisibilityChangeServices& services) {
    return changeCellVisibilityWithLiveRefreshFlags(point,house,finalArgument,world,
        [refreshRules]{return refreshRules;},services);
}
bool revealCellForOrdinarySight(TerrainCellPoint point,int house,
        std::uint32_t finalArgument,const CellVisibilityChangeWorld& world,
        std::uint32_t refreshRules,const CellVisibilityChangeServices& services) {
    if(finalArgument!=0)throw std::invalid_argument("Ordinary sight reveal requires final argument zero");
    return changeCellVisibility(point,house,finalArgument,world,refreshRules,services);
}
}
