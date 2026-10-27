// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/UnitAdmission.hpp"

namespace ra2 {
struct InfantryAdmissionActor {
    const std::uint8_t& flag32d;
    const std::uint8_t& flag370;
    const int& speedType5a4;
    const int& loadingA40774;
};
struct InfantryAdmissionServices {
    std::function<const int&(int)> overlay;
    // Registry+24 is distinct from the existing registry+28 destination.
    std::function<TerrainCellPoint(int)> registryOrigin;
    std::span<const std::uint32_t> speedBits;
    std::function<bool(int,std::uint8_t)> permission; // Direct Cell55A740, no map lookup.
    // Optional resident continuation on the same logical identities; returns a
    // terminal admission result, or increments the stationary Infantry count.
    std::function<std::optional<int>(int,int,int&)> resident;
    std::function<bool(int)> permissionOverride; // Foot4C8CA0, only after denied permission.
};
// Borrowed ordinary E1 resident path50345B..5038CB. The admitted domain has
// no transport, C10/C11 special missions or C14 demolition; unsupported entered
// branches refuse after preceding queries. Startup values are supplied separately.
struct InfantryResidentServices {
    const void* const& transport588;
    const std::uint8_t& typeC10;
    const std::uint8_t& typeC11;
    const std::uint8_t& typeC14;
    std::function<bool(int,int)> ally4E5580;
    std::function<std::uint8_t(int)> moving10;
};
template<class World>
std::optional<int> ordinaryInfantryResident(int mover,int resident,int& stationary,
        World& w,const InfantryResidentServices& s){
    using namespace unit_admission_policy;
    if(s.transport588)throw std::invalid_argument("Infantry transport resident admission unjoined");
    // Preserve repeated virtual queries, including live results after children.
    const auto unsupported=[] {throw std::invalid_argument("Infantry special mission resident admission unjoined");};
    if(mission(mover,w)==7)unsupported();
    if(mission(mover,w)==8)unsupported();
    if(mission(mover,w)==9)unsupported();
    if(mission(mover,w)==17&&s.typeC10)unsupported();
    const bool special=mission(mover,w)==11||mission(mover,w)==25||mission(mover,w)==5;
    if(special&&s.typeC11)unsupported();
    if(mission(mover,w)==11)throw std::invalid_argument("Infantry mission11 destination resident admission unjoined");
    if(s.typeC14)throw std::invalid_argument("Infantry demolition resident admission unjoined");
    if(kind(resident,w)!=15)throw std::invalid_argument("Infantry non-Infantry resident admission unjoined");
    if(mission(mover,w)==7)unsupported();
    if(!s.ally4E5580||!s.ally4E5580(mover,resident))
        throw std::invalid_argument("Infantry hostile resident admission unjoined");
    // Original switch includes Infantry kind15 ->5038A3. Other kinds are not
    // generalized from it. Is_Moving consumes the raw low byte.
    if(kind(resident,w)!=15)throw std::invalid_argument("Infantry changed resident kind unjoined");
    if(!s.moving10)throw std::invalid_argument("Infantry resident Walk getter unbound");
    if(!s.moving10(resident))++stationary;
    return std::nullopt;
}
// Complete ordinary Infantry503190 paths with explicitly bound selected lists
// and absent overlays. World is the existing admission owner or borrowed view;
// Foot terrain, registry, neighbor, map/fallback and House helpers stay single.
// Unbound permission, other residents, overlays and hostile-owner weapon queries
// refuse. Initial associations/type/speed table remain supplied.
template<class World>
int ordinaryInfantryAdmission(int mover,int target,int direction,int level,int previous,
    int /*consult*/,World& w,InfantryAdmissionActor actor,const InfantryAdmissionServices& services){
    using namespace unit_admission_policy;
    if(!w.cells.contains(target)||!w.gates.cells.contains(target)||!w.gates.objects.contains(mover))
        throw std::invalid_argument("Infantry admission requires bound actor and Cell");
    const auto& t=w.cells.at(target);
    std::uint8_t elevated=std::uint8_t((t.flags&0x100u)&&(level==-1||absolute(sub(level,t.level))>1));
    auto occupation=std::uint8_t(t.occupation);bool bit5=(t.occupation&32u)!=0;int owner=t.owner;
    const int r=registry(target,w);
    if(direction==8){
        if(r==-1)return 7;
        if(!services.registryOrigin)throw std::invalid_argument("Infantry registry origin requires binding");
        return services.registryOrigin(r)!=w.registry[std::size_t(r)]->point?0:7;
    }
    const auto blocked=[&](int id,int d){
        if(id==-1)return false;
        const int n=absolute(sub(d,w.registry[std::size_t(id)]->direction));
        return n>2&&n<6&&direction!=-1;
    };
    if(blocked(r,direction))return 7;
    const int reverse=opposite(direction);
    if(blocked(registry(neighbor(target,reverse,w),w),reverse))return 7;
    // Infantry's own early success precedes the shared Foot terrain call.
    if(sub(level,t.level)>4)return 0;
    if(unitTerrainAdmission(target,direction,level,elevated,previous,w)==7)return 7;
    if(level!=-1&&(t.flags&0x100u)&&level==int(t.level)+4){
        occupation=std::uint8_t(t.elevatedOccupation);bit5=(t.elevatedOccupation&32u)!=0;owner=t.elevatedOwner;
    }
    if(actor.flag32d&&!actor.loadingA40774){
        if(!services.permission)throw std::invalid_argument("Infantry direct permission requires binding");
        if(!services.permission(target,1)){
            if(!services.permissionOverride)throw std::invalid_argument("Infantry permission override requires binding");
            if(!services.permissionOverride(mover))return 7;
        }
    }
    if(!services.overlay)throw std::invalid_argument("Infantry admission requires overlay owner");
    if(services.overlay(target)!=-1)throw std::invalid_argument("Infantry overlay admission requires recovery");
    int resident=elevated?t.elevatedHead:w.gates.cells.at(target).head;
    int count=0;std::size_t visits=0;
    while(resident!=-1){
        if(++visits>w.gates.objects.size())throw std::invalid_argument("Cyclic Infantry admission list");
        if(resident!=mover){
            if(!services.resident)throw std::invalid_argument("Infantry resident admission requires recovery");
            if(auto result=services.resident(mover,resident,count))return *result;
        }
        resident=w.gates.objects.at(resident).next;
    }
    if(!actor.flag370&&!elevated){
        const int index=signed32(std::uint32_t(t.land)*9u+std::uint32_t(actor.speedType5a4));
        if(index<0||std::size_t(index)>=services.speedBits.size())throw std::invalid_argument("Infantry terrain speed index");
        const auto bits=services.speedBits[std::size_t(index)];event(w,'S',index,signed32(bits));
        const auto magnitude=bits&0x7fffffffu;
        if(magnitude==0||magnitude>0x7f800000u)return 7; // equality or unordered, not positivity
    }
    if(bit5)return 2;
    if(owner!=-1){
        if(!indexAlly(w.gates.objects.at(mover).owner,owner,w))
            throw std::invalid_argument("Infantry hostile occupation weapon query requires recovery");
        if((occupation&0x1cu)==0x1cu)return count==3?6:2;
    }else if((occupation&0x1cu)==0x1cu)return 7;
    return 0;
}
}
