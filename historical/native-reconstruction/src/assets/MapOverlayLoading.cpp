// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapOverlayLoading.hpp"
#include <bit>
#include <stdexcept>

namespace ra2 {
bool overlayMapPositionPermitted(MapInputPosition p,int width,int height){
    const int sum=int(p.x)+int(p.y);
    const int end=std::bit_cast<std::int32_t>(std::uint32_t(width)+std::uint32_t(height)*2u);
    return sum>width&&int(p.x)-int(p.y)<width&&int(p.y)-int(p.x)<width&&sum<=end;
}
void loadDecodedMapOverlays(int version,int width,int height,bool filterCrates,
    std::span<const OverlayTypeInputs> types,const OverlayMapLoadServices& s){
    if(!s.cleanup)throw std::invalid_argument("Missing overlay transient cleanup");
    const auto write=[&](OverlayLoadCell& cell,std::uint8_t value){cell.data=value;if(s.store)s.store(cell,value);};
    const auto permitted=[&](MapInputPosition p){const bool value=overlayMapPositionPermitted(p,width,height);if(s.permissionQuery)s.permissionQuery(p,value);return value;};
    if(version>1){
        if(!s.section)throw std::invalid_argument("Missing overlay map section reader");
        for(auto pack:{OverlayMapPack::Types,OverlayMapPack::Data}){
            const unsigned capacity=pack==OverlayMapPack::Types?512000:256000;
            if(s.section(pack,capacity)<=0)continue;
            if(!s.read||!s.cell)throw std::invalid_argument("Missing overlay decoded stream or Cell lookup");
            for(int y=0;y<512;++y)for(int x=0;x<512;++x){
                const MapInputPosition p{std::int16_t(x),std::int16_t(y)};
                const auto value=s.read(pack);
                if(pack==OverlayMapPack::Types){
                    const unsigned index=value.value_or(255);if(index==255)continue;
                    if(index>=types.size())throw std::invalid_argument("Overlay byte outside supplied registry");
                    const auto& type=types[index];
                    if(!type.image&&type.demandLoad)throw std::invalid_argument("Lazy overlay image outside resident boundary");
                    if(s.imageQuery)s.imageQuery(index);
                    if(!type.image&&!type.cellAnim)continue;
                    if(filterCrates&&type.crate)continue;
                    if(!permitted(p))continue;
                    const auto previous=s.cell(p).data;
                    if(!s.allocate)throw std::invalid_argument("Missing temporary overlay allocator");
                    if(s.allocate()){
                        if(!s.construct)throw std::invalid_argument("Missing temporary overlay constructor");
                        s.construct(index,p,-1);
                    }
                    if(index==0x18||index==0x19||index==0xed||index==0xee)write(s.cell(p),previous);
                }else if(permitted(p))write(s.cell(p),value.value_or(0));
            }
        }
    }
    s.cleanup();
}
}
