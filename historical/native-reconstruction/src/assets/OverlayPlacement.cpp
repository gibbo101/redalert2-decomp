// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayPlacement.hpp"
#include <bit>
#include <climits>
#include <stdexcept>

namespace ra2 {
namespace {
void check(const OverlayTypeInputs* type){
    if(!type)throw std::invalid_argument("Missing temporary overlay type");
    const int i=type->index;
    if(type->wall||type->land==9||type->cellAnim||i==0x18||i==0x19||i==0xed||i==0xee||
       i==0x7e||i==0xa7||(i>=0x7a&&i<=0x7d)||(i>=0xe9&&i<=0xec))
        throw std::invalid_argument("Alternate overlay placement requires recovery");
}
void emit(const OverlayPlacementServices& s,unsigned role,unsigned offset,unsigned size,std::uint32_t value){
    if(s.store)s.store(role,offset,size,value);
}
template<class T> void put(T& field,T value,const OverlayPlacementServices& s,unsigned role,unsigned offset){
    field=value;emit(s,role,offset,sizeof(T),std::uint32_t(value));
}
MapInputPosition cellPoint(Coord p){
    return {std::bit_cast<std::int16_t>(std::uint16_t(p.x/256)),
            std::bit_cast<std::int16_t>(std::uint16_t(p.y/256))};
}
bool baseMark(TransientMapOverlay& actor,int mode,const OverlayPlacementServices& s){
    if(actor.limbo)return false;
    const auto redraw=[&]{
        if(!actor.redraw){
            if(!s.redraw)throw std::invalid_argument("Missing overlay redraw queue");
            put(actor.redraw,std::uint8_t(1),s,0,0x75);s.redraw();
        }
    };
    if(mode==2){if(actor.redraw||!actor.onMap)return false;redraw();return true;}
    if(!s.noAttachedAnimation)throw std::invalid_argument("Missing overlay animation association service");
    s.noAttachedAnimation();
    if((mode==1||mode==3)&&!actor.onMap){put(actor.onMap,std::uint8_t(1),s,0,0x74);redraw();return true;}
    if(mode==0&&actor.onMap){put(actor.onMap,std::uint8_t(0),s,0,0x74);return true;}
    return false;
}
}
bool markLoadedMapOverlay(TransientMapOverlay& actor,int mode,const OverlayPlacementServices& s){
    check(actor.type);
    if(!baseMark(actor,mode,s)||(mode!=1&&mode!=3))return false;
    if(!s.cell)throw std::invalid_argument("Missing overlay placement Cell lookup");
    auto& cell=s.cell(cellPoint(actor.position));const auto& type=*actor.type;
    if(cell.slope>4&&type.index!=0xb2)return false;
    put(cell.overlay,type.index,s,1,0x44);put(cell.data,std::uint8_t(0),s,1,0x11e);
    if(type.land==5){
        if(!s.resource)throw std::invalid_argument("Missing overlay resource update");
        put(cell.data,std::uint8_t(1),s,1,0x11e);s.resource(cell);
    }
    if(type.crate)put(cell.data,std::uint8_t(255),s,1,0x11e);
    if(!s.recalculate||!s.retire)throw std::invalid_argument("Missing overlay recalculation/retirement services");
    s.recalculate(cell,-1);
    put(actor.onMap,std::uint8_t(0),s,0,0x74);put(actor.limbo,std::uint8_t(1),s,0,0x76);
    s.retire(actor);
    return true;
}
namespace {
template<class Mark>
bool unlimbo(TransientMapOverlay& actor,Coord position,std::uint8_t enabled,
             const OverlayPlacementServices& s,Mark mark){
    if(!enabled||!actor.limbo||actor.onMap)return false;
    put(actor.limbo,std::uint8_t(0),s,0,0x76);put(actor.redraw,std::uint8_t(0),s,0,0x75);
    // The actual OverlayType adjustment copies all three coordinates unchanged.
    put(actor.position.x,position.x,s,0,0x88);put(actor.position.y,position.y,s,0,0x8c);
    put(actor.position.z,position.z,s,0,0x90);
    if(!mark(actor)){put(actor.limbo,std::uint8_t(1),s,0,0x76);return false;}
    if(actor.active)throw std::invalid_argument("Overlay retirement service retained active actor");
    return true;
}
template<class Place>
void construct(TransientMapOverlay& actor,const OverlayTypeInputs& type,
    MapInputPosition point,MapInputPosition invalid,int flag,int& placementFlag,
    std::uint32_t identity,OverlayTransientRegistry& registry,std::uint8_t enabled,
    const OverlayPlacementServices& s,Place place){
    if(registry.count<0||registry.slots.size()>INT_MAX||std::size_t(registry.count)>registry.slots.size())
        throw std::invalid_argument("Invalid transient overlay registry");
    if(!s.base)throw std::invalid_argument("Missing temporary Object constructor");
    s.base(actor);actor.type=&type;emit(s,0,0x98,4,1);
    // Identity provider association is separate from the map-loading global.
    std::uint32_t token=0;
    if(s.identityCounter){token=++*s.identityCounter;emit(s,4,0,4,token);}
    put(actor.identityToken,token,s,0,0x10);
    bool append=registry.count<int(registry.slots.size());
    if(!append&&(registry.owns||registry.slots.empty())&&registry.growth>0){
        const int capacity=std::bit_cast<std::int32_t>(std::uint32_t(registry.slots.size())+std::uint32_t(registry.growth));
        if(capacity<0)throw std::invalid_argument("Unsupported transient capacity wrap");
        append=s.grow&&s.grow(capacity);
    }
    if(append){
        if(std::size_t(registry.count)>=registry.slots.size())throw std::invalid_argument("Transient growth supplied no capacity");
        const unsigned index=unsigned(registry.count++);
        emit(s,2,0,4,std::uint32_t(registry.count));registry.slots[index]=identity;emit(s,2,index+1,4,identity);
    }
    if(point==invalid)return;
    placementFlag=flag;emit(s,3,0,4,std::uint32_t(placementFlag));
    const Coord center{int(point.x)*256+128,int(point.y)*256+128,0};
    place(actor,center,enabled);
    placementFlag=-1;emit(s,3,0,4,std::uint32_t(placementFlag));
}
void checkWall(const OverlayTypeInputs* type,const LoadedWallPlacementServices& wall){
    if(!type||!type->wall||type->cellAnim||type->land==9||!wall.loading)
        throw std::invalid_argument("Only loaded ordinary walls are supported");
    const int index=type->index;
    if(index==0x18||index==0x19||index==0xed||index==0xee||index==0x7e||index==0xa7)
        throw std::invalid_argument("Special wall placement requires recovery");
}
}
bool unlimboLoadedMapOverlay(TransientMapOverlay& actor,Coord position,std::uint8_t enabled,
                            const OverlayPlacementServices& s){
    check(actor.type);
    return unlimbo(actor,position,enabled,s,[&](auto& a){return markLoadedMapOverlay(a,1,s);});
}
void constructLoadedMapOverlay(TransientMapOverlay& actor,const OverlayTypeInputs& type,
    MapInputPosition point,MapInputPosition invalid,int flag,int& placementFlag,
    std::uint32_t identity,OverlayTransientRegistry& registry,std::uint8_t enabled,
    const OverlayPlacementServices& s){
    check(&type);
    construct(actor,type,point,invalid,flag,placementFlag,identity,registry,enabled,s,
        [&](auto& a,Coord p,std::uint8_t e){return unlimboLoadedMapOverlay(a,p,e,s);});
}
bool markLoadedMapWall(TransientMapOverlay& actor,int mode,const LoadedWallPlacementServices& wall){
    checkWall(actor.type,wall);
    const int index=actor.type->index;
    const auto& s=wall.object;
    if(!s.cell||!wall.updateWall||!s.recalculate||!s.retire)
        throw std::invalid_argument("Missing loaded wall placement services");
    if(!baseMark(actor,mode,s)||(mode!=1&&mode!=3))return false;
    auto& cell=s.cell(cellPoint(actor.position));
    if(cell.slope>4&&index!=0xb2)return false;
    if(wall.permissionQuery)wall.permissionQuery();
    // Actual CanThisExistHere returns one before reading the Cell when loading
    // is nonzero; alternate occupancy/placement decisions are outside this API.
    put(cell.data,std::uint8_t(0),s,1,0x11e);put(cell.overlay,index,s,1,0x44);
    wall.updateWall(cell,1);
    if((wall.livePlacementFlag?*wall.livePlacementFlag:wall.placementFlag)!=-1)
        put(cell.owner,wall.currentOwner,s,1,0x50);
    for(const auto& direction:wall.directions){
        const MapInputPosition next{
            std::bit_cast<std::int16_t>(std::uint16_t(unsigned(std::uint16_t(cell.position.x))+unsigned(std::uint16_t(direction.x)))),
            std::bit_cast<std::int16_t>(std::uint16_t(unsigned(std::uint16_t(cell.position.y))+unsigned(std::uint16_t(direction.y))))};
        auto& neighbor=s.cell(next);
        put(neighbor.neighbors,std::uint8_t(unsigned(neighbor.neighbors)+1),s,1,0x122);
    }
    s.recalculate(cell,-1);
    put(actor.onMap,std::uint8_t(0),s,0,0x74);put(actor.limbo,std::uint8_t(1),s,0,0x76);
    s.retire(actor);
    return true;
}
bool unlimboLoadedMapWall(TransientMapOverlay& actor,Coord position,std::uint8_t enabled,
                         const LoadedWallPlacementServices& wall){
    checkWall(actor.type,wall);
    return unlimbo(actor,position,enabled,wall.object,[&](auto& a){return markLoadedMapWall(a,1,wall);});
}
void constructLoadedMapWall(TransientMapOverlay& actor,const OverlayTypeInputs& type,
    MapInputPosition point,MapInputPosition invalid,int flag,int& placementFlag,
    std::uint32_t identity,OverlayTransientRegistry& registry,std::uint8_t enabled,
    const LoadedWallPlacementServices& wall){
    checkWall(&type,wall);
    construct(actor,type,point,invalid,flag,placementFlag,identity,registry,enabled,wall.object,
        [&](auto& a,Coord p,std::uint8_t e){
            // Mark observes the flag just stored by the actual constructor.
            auto live=wall;live.livePlacementFlag=&placementFlag;
            return unlimboLoadedMapWall(a,p,e,live);
        });
}
}
