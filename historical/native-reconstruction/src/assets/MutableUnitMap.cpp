// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MutableUnitMap.hpp"
#include <algorithm>
#include <stdexcept>
namespace ra2 {
MutableUnitMap::MutableUnitMap(UnitMapSeed seed,std::shared_ptr<const void> keepAlive)
    :keepAlive_(std::move(keepAlive)),tiles_(seed.resident.tiles.begin(),seed.resident.tiles.end()),
     overlays_(seed.resident.overlays.begin(),seed.resident.overlays.end()),
     resources_(seed.resident.resources.begin(),seed.resident.resources.end()),
     cells(seed.cells.begin(),seed.cells.end()),table(262144,nullptr),slots(seed.slots.begin(),seed.slots.end()),
     fallback(seed.fallback),floor(seed.floor),resident(seed.resident),
     buffer4(seed.buffer4.begin(),seed.buffer4.end()),buffer10(seed.buffer10.begin(),seed.buffer10.end()),
     width(seed.width),height(seed.height),levelHeight(seed.levelHeight){
    if(cells.size()>16384||slots.size()!=262144||seed.resident.landMap.size()!=16||seed.resident.wheelSpeeds.size()!=11||
       width<2||height<1||std::int64_t(width)+height>256||levelHeight!=104||
       buffer4.size()!=std::size_t(width+height+1)*std::size_t(width+height+1)*4||buffer10.size()/10!=buffer4.size()/4||buffer10.size()%10)
        throw std::invalid_argument("Mutable Unit map outside verified preparation domain");
    std::copy(seed.resident.landMap.begin(),seed.resident.landMap.end(),landMap_.begin());
    std::copy(seed.resident.wheelSpeeds.begin(),seed.resident.wheelSpeeds.end(),wheelSpeeds_.begin());
    for(auto& c:cells)attributes.push_back(&c.attributes);
    for(std::size_t i=0;i<slots.size();++i){
        const int id=slots[i];if(id==-1)continue;
        if(id<0||std::size_t(id)>=cells.size())throw std::invalid_argument("Mutable Unit map has invalid canonical slot");
        table[i]=&cells[std::size_t(id)].attributes.input;
    }
    resident.world={table,&fallback.input,{},{}};resident.tiles=tiles_;resident.overlays=overlays_;
    resident.resources=resources_;resident.landMap=landMap_;resident.wheelSpeeds=wheelSpeeds_;
}
std::unique_ptr<MutableUnitMap> MutableUnitMap::clone()const{
    return std::make_unique<MutableUnitMap>(UnitMapSeed{cells,slots,fallback,floor,resident,buffer4,buffer10,width,height,levelHeight},keepAlive_);
}
PreparedMembershipMap MutableUnitMap::input(){return {attributes,slots,fallback,floor,resident,buffer4,buffer10,width,height,levelHeight};}
const MapCellAttributes* MutableUnitMap::find(const MapCellInput& c)const{
    const int slot=int(c.position.y)*512+int(c.position.x);
    if(slot<0||slot>=262144)return nullptr;const int id=slots[std::size_t(slot)];
    if(id<0||std::size_t(id)>=cells.size()||&cells[std::size_t(id)].attributes.input!=&c)return nullptr;
    return &cells[std::size_t(id)].attributes;
}
}
