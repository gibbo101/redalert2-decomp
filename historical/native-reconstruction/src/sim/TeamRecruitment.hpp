// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TeamMembership.hpp"
namespace ra2 {
struct TeamRecruitmentServices {
    const void* const& anchor34;
    const Coord& emptyCoordinates;
    const std::uint32_t& emptyCell;
    std::function<Coord(const void*)> coordinates48;
    std::function<std::uint32_t()> waypoint6BFA90;
    std::function<std::int32_t(std::int32_t)> currentCount84,requiredCountA4;
    std::function<std::int32_t()> group6BFA60,requiredKind2C;
    std::function<std::int32_t()> infantryCount;
    std::function<const void*(std::int32_t)> infantrySlot;
    std::function<std::int32_t(const void*)> footGroup1AC;
    std::function<std::uint8_t()> typeA8;
    std::function<std::uint32_t(const void*,std::int32_t&)> admission6B8DC0;
    std::function<void(const void*)> clearTarget370;
    std::function<bool(const void*)> addMember6B8CC0;
};
// Complete5D4E00 with the actual coordinate getter supplied by its owner.
// The distance is signed wrapped XY squared, with no square root or Z term.
inline std::int32_t teamRecruitmentDistance(Coord from,Coord to){
    const auto x=std::uint32_t(from.x)-std::uint32_t(to.x);
    const auto y=std::uint32_t(from.y)-std::uint32_t(to.y);
    return std::bit_cast<std::int32_t>(x*x+y*y);
}
// Complete-to-return6B91C0 path for required kind16 (InfantryType).
// Other registry kinds remain refused until their actual consumers are joined.
inline bool recruitInfantryTeamSlot(std::int32_t slot,const TeamRecruitmentServices& s){
    Coord origin=s.anchor34?requireTeamAdmission(s.coordinates48)(s.anchor34):s.emptyCoordinates;
    const auto point=requireTeamAdmission(s.waypoint6BFA90)();
    if(std::uint16_t(point)!=std::uint16_t(s.emptyCell)||std::uint16_t(point>>16)!=std::uint16_t(s.emptyCell>>16)){
        const auto second=requireTeamAdmission(s.waypoint6BFA90)();
        origin={int(std::bit_cast<std::int16_t>(std::uint16_t(second)))*256+128,
                int(std::bit_cast<std::int16_t>(std::uint16_t(second>>16)))*256+128,0};
    }
    const auto current=requireTeamAdmission(s.currentCount84)(slot);
    const auto required=requireTeamAdmission(s.requiredCountA4)(slot);
    if(required<=current)return false;
    const auto group=requireTeamAdmission(s.group6BFA60)();
    if(requireTeamAdmission(s.requiredKind2C)()!=16)throw std::invalid_argument("Recruitment requires entered InfantryType registry path");
    const void* selected=nullptr;std::int32_t best=-1;
    for(std::int32_t i=0;i<requireTeamAdmission(s.infantryCount)();++i){
        const auto foot=requireTeamAdmission(s.infantrySlot)(i);
        if(!foot)throw std::invalid_argument("Original recruitment would dereference null Infantry registry entry");
        if(group!=-2&&requireTeamAdmission(s.footGroup1AC)(foot)!=group&&!requireTeamAdmission(s.typeA8)())continue;
        auto distance=teamRecruitmentDistance(requireTeamAdmission(s.coordinates48)(foot),origin);
        if(requireTeamAdmission(s.footGroup1AC)(foot)!=group)
            distance=std::bit_cast<std::int32_t>(std::uint32_t(distance)+0x3200u);
        if(distance>=best&&best!=-1)continue;
        if(std::uint8_t(requireTeamAdmission(s.admission6B8DC0)(foot,slot))){selected=foot;best=distance;}
    }
    if(!selected)return false;
    requireTeamAdmission(s.clearTarget370)(selected);
    (void)requireTeamAdmission(s.addMember6B8CC0)(selected);
    return true; // Parent reports selection, independently of AddMember's return.
}
// Complete502470 ->6C9AF0 null-target paths on ordinary E1 records.
// Nonnull targets/special deploy animation require their entered children.
inline void clearInfantryRecruitTarget(const void* alternate228,std::int32_t state5AC,
        std::int32_t& route4D0,std::uint8_t& flag404,std::uint8_t& flag57E,
        const std::function<void(std::int64_t,std::uint32_t)>& store={}){
    if(alternate228||state5AC==27||state5AC==28||state5AC==29||state5AC==30)
        throw std::invalid_argument("Infantry recruitment target/animation branch unjoined");
    route4D0=-1;if(store)store(0x4d0,0xffffffffu);
    flag404=0;if(store)store(0x404,0);
    flag57E=0;if(store)store(0x57e,0);
}
}
