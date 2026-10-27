// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/InfantryPositionEffectsE1.hpp"
#include <bit>
#include <stdexcept>

namespace ra2 {
namespace { void require(bool v,const char* m){if(!v)throw std::invalid_argument(m);} }
void applyInfantryPositionEffectsE1(InfantryPositionEffectsE1Actor a,std::int32_t argument,
        const InfantryPositionEffectsE1Services& s) {
    require(s.alternateQuery&&s.mission&&s.cellPoint&&s.cell&&s.findKind6&&
        s.permission&&s.positionChild3b8&&s.dirty&&s.scratchStore,
        "Infantry E1 position effects require every service");
    require(argument==2,"Infantry E1 position effects support only argument 2");
    a.state59c=0;a.state59a=0;
    require(a.typeFootprint538==0,"Infantry E1 footprint type branch unsupported");
    require(a.footprintX454==0&&a.footprintY456==0,"Infantry E1 footprint transfer unsupported");
    require(a.mode1b8!=2,"Infantry E1 mode-2 effects unsupported");
    (void)s.alternateQuery(a.alternateTarget228);
    const auto m21=s.mission(),m11=s.mission(),m1=s.mission(),m15=s.mission();
    require(m21!=21&&m11!=11&&m1!=1&&m15!=15,
        "Infantry E1 alternate-target mission effects unsupported");
    auto current=s.cell(s.cellPoint());
    require(a.mode1b8!=2,"Infantry E1 secondary mode-2 effects unsupported");
    require((current.flags140&(0x100000u|0x200000u))==0&&current.object3c==nullptr,
        "Infantry E1 Cell object/edge effects unsupported");
    s.scratchStore(0);
    require(s.findKind6(current.identity)==nullptr,
        "Infantry E1 current kind-6 effect unsupported");
    require(a.bridge79==0,"Infantry E1 bridge refresh unsupported");
    if(!a.onMap7d)return;
    const bool permitted=s.permission(s.cellPoint(),true);
    if(!permitted)require(a.active32d==0,"Infantry E1 active placement branch unsupported");
    require(a.flag77==0,"Infantry E1 visible-map refresh unsupported");
    require(a.animation418==-1,"Infantry E1 animation-offset branch unsupported");

    require(a.effect208==nullptr,"Infantry E1 tail effect branch unsupported");
    const auto word=[](std::int32_t value){
        return std::bit_cast<std::int16_t>(std::uint16_t(value/256));
    };
    const TerrainCellPoint rounded{word(a.coordinates88.x),word(a.coordinates88.y)};
    s.positionChild3b8();
    require(a.target34==nullptr,"Infantry E1 tail target event unsupported");
    if(!a.active32d&&s.permission(rounded,true))a.active32d=1;
    if(!a.flag373){
        const auto first=s.cell(rounded);
        if(first.flags12c&0x10u){
            require(bool(s.discover),"Infantry E1 tail discovery service missing");
            s.discover();
        }
    }
    auto second=s.cell(rounded);s.dirty(second.identity);
}
}
