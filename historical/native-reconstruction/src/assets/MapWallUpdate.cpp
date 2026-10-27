// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapWallUpdate.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
namespace {
int sub(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
MapInputPosition add(MapInputPosition a,MapInputPosition b){
    return {std::bit_cast<std::int16_t>(std::uint16_t(unsigned(std::uint16_t(a.x))+unsigned(std::uint16_t(b.x)))),
            std::bit_cast<std::int16_t>(std::uint16_t(unsigned(std::uint16_t(a.y))+unsigned(std::uint16_t(b.y))))};
}
template<class T> void put(MapWallCell& c,T& field,T value,unsigned off,const MapWallUpdateServices& s){
    field=value;if(s.store)s.store(c,off,sizeof(T),std::uint32_t(value));
}
}
bool connectsToMapOverlay(const MapWallCell& c,int overlay,int facing,const WallConnectionInputs& in){
    if(in.connectionQuery)in.connectionQuery(c,overlay,facing);
    if(c.overlay==overlay&&overlay!=-1)return true;
    if(overlay==-1)return c.overlay==2||c.overlay==26;
    if(overlay==0||overlay==2||overlay==26){
        for(unsigned i=0;i<c.occupants.size();++i){
            if(in.occupantQuery)in.occupantQuery(c,i);
            const auto& o=c.occupants[i];if(o.kind!=6||o.health<=0)continue;
            const bool horizontal=facing==2||facing==6,vertical=facing==0||facing==4;
            if(overlay==26){
                if((o.type==in.gates[3]&&horizontal)||(o.type==in.gates[4]&&vertical))return true;
            }else if((o.type==in.gates[0]&&horizontal)||(o.type==in.gates[1]&&vertical)||o.type==in.gates[2])return true;
        }
    }
    return false;
}
void updateMapWall(MapWallCell& center,std::uint8_t skipCenter,const MapWallUpdateServices& s){
    if(!s.cell||!s.bounds||!s.unite||!s.dirty||!s.notify||!s.recalculate||!s.expired||!s.zone)
        throw std::invalid_argument("Missing map wall-update service");
    const auto neighbor=[&](MapWallCell& c,int facing)->MapWallCell&{
        return std::uint32_t(facing)<8?s.cell(add(c.position,s.directions[unsigned(facing)&7])):c;
    };
    for(int facing:s.visits){
        auto& c=neighbor(center,facing);
        if(!skipCenter||facing!=-1){
            // The original performs these old-image queries before recomputing
            // its three-way dirty union; their partial local union is unused.
            s.bounds(c,0);s.bounds(c,1);
        }
        const auto shadow=s.bounds(c,1),overlay=s.bounds(c,0),terrain=s.bounds(c,2);
        const auto first=s.unite(terrain,overlay);auto dirty=s.unite(first,shadow);
        dirty.x=sub(dirty.x,s.screenX);dirty.y=sub(dirty.y,s.screenY);s.dirty(dirty);
        s.notify(c.position);
        if(c.overlay==-1)continue;
        if(c.overlay<0||std::size_t(c.overlay)>=s.wallTypes.size())throw std::invalid_argument("Wall overlay outside supplied registry");
        if(!s.wallTypes[std::size_t(c.overlay)])continue;
        unsigned mask=0;
        for(unsigned i=0;i<4;++i){
            const int direction=s.visits[i];auto& other=neighbor(c,direction);
            if(connectsToMapOverlay(other,c.overlay,direction,s.connections))mask|=1u<<i;
        }
        const int before=c.passability;
        put(c,c.data,std::uint8_t((c.data&0xf0)|mask),0x11e,s);
        bool removed=false;
        const auto remove=[&](bool clearOwner){
            put(c,c.overlay,-1,0x44,s);put(c,c.data,std::uint8_t(0),0x11e,s);
            if(clearOwner)put(c,c.owner,-1,0x50,s);
            s.expired(c);removed=true;
        };
        if((c.overlay==2||c.overlay==26)&&(c.data==0x30||c.data==0x20))remove(false);
        if(c.overlay==0&&(c.data==0x10||c.data==0x20))remove(true);
        if(c.overlay==1&&c.data==0x20)remove(true);
        if(c.overlay==22&&(c.data==0x10||c.data==0x20))remove(true);
        if(c.overlay==3&&c.data==0x10)remove(true);
        s.recalculate(c,-1);
        if(c.passability==before)continue;
        s.zone(removed?0:1,c.position);s.zone(2,c.position);
        if(removed)for(unsigned i=0;i<8;++i){auto& other=neighbor(c,int(i));put(other,other.neighbors,std::uint8_t(unsigned(other.neighbors)-1),0x122,s);}
    }
}
bool damageMapWall(MapWallCell& c,int damage,const MapWallDamageServices& services){
    if(c.overlay==-1)return false;
    if(!services.type)throw std::invalid_argument("Wall damage type service unbound");
    const auto type=services.type(c.overlay);
    if(!type.wall)return false;
    if(damage!=-1&&damage<type.strength274&&!services.forceDamage){
        if(!services.randomRange)throw std::invalid_argument("Wall damage RNG unbound");
        if(services.randomRange(0,type.strength274)>=damage)return false;
    }
    const auto& s=services.update;
    if(!s.bounds||!s.unite||!s.dirty)throw std::invalid_argument("Wall damage bounds services unbound");
    const auto shadow=s.bounds(c,1),overlay=s.bounds(c,0);
    auto dirty=s.unite(overlay,shadow);
    // Unlike updateMapWall, this caller subtracts only the vertical camera word.
    dirty.y=sub(dirty.y,s.screenY);s.dirty(dirty);
    put(c,c.data,std::uint8_t(unsigned(c.data)+16),0x11e,s);
    const auto neighbor=[&](unsigned facing)->MapWallCell&{
        if(!s.cell)throw std::invalid_argument("Wall damage Cell lookup unbound");
        return s.cell(add(c.position,s.directions[facing]));
    };
    if(int(c.data>>4)==sub(type.levels270,1)&&type.levels270>2){
        for(unsigned facing=0;facing<8;facing+=2){
            auto& other=neighbor(facing);
            if(other.overlay==-1)continue;
            const auto otherType=services.type(other.overlay);
            if(otherType.wall&&other.overlay==c.overlay&&other.data<16)
                (void)damageMapWall(other,200,services);
        }
    }
    if(damage!=-1&&int(c.data>>4)<type.levels270){
        if(int(c.data>>4)!=sub(type.levels270,1)||(c.data&15))return false;
    }
    if(!s.recalculate||!s.zone||!s.notify||!s.expired)
        throw std::invalid_argument("Wall damage removal services unbound");
    put(c,c.owner,-1,0x50,s);put(c,c.overlay,-1,0x44,s);
    put(c,c.data,std::uint8_t(0),0x11e,s);
    s.recalculate(c,-1);s.zone(0,c.position);s.zone(2,c.position);s.notify(c.position);
    for(unsigned facing:{0u,6u,4u,2u})updateMapWall(neighbor(facing),0,s);
    s.expired(c);
    for(unsigned facing=0;facing<8;++facing){
        auto& other=neighbor(facing);
        put(other,other.neighbors,std::uint8_t(unsigned(other.neighbors)-1),0x122,s);
    }
    return true;
}
}
