// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/InfantryUpdatePositionE1.hpp"
#include <stdexcept>

namespace ra2 {
namespace {
void require(bool value,const char* message){if(!value)throw std::invalid_argument(message);}
}
void updateInfantryPositionE1(InfantryUpdatePositionE1Actor actor,std::int32_t argument,
        const InfantryUpdatePositionE1Services& services) {
    require(services.mission&&services.cell&&services.currentCell&&services.cellValue&&services.findKind6&&
        services.findKind2&&services.findKind1&&services.targetKind&&
        services.targetCoordinates&&services.locomotorPredicate&&services.postUpdate,
        "Infantry E1 update-position requires every parent service");

    const auto initialCell=services.cell(actor.coordinates88);
    (void)initialCell;
    require(argument==2,"Infantry E1 update-position supports only argument 2");
    require(services.mission()!=8,"Infantry E1 update-position mission-8 branch unsupported");
    require(services.mission()!=9,"Infantry E1 update-position mission-9 branch unsupported");
    const auto mission8=services.mission();
    const auto mission11=services.mission();
    const auto mission25=services.mission();
    require(mission8!=8&&mission11!=11&&mission25!=25,
        "Infantry E1 update-position special mission branch unsupported");
    require(actor.typeSpecialC14==0,"Infantry E1 update-position special type branch unsupported");

    require(services.findKind6(services.currentCell())==nullptr,
        "Infantry E1 update-position current kind-6 resident unsupported");
    require(services.findKind2(services.currentCell(),actor.bridgeLayer79!=0)==nullptr,
        "Infantry E1 update-position current kind-2 resident unsupported");
    require(services.findKind1(services.currentCell(),actor.bridgeLayer79!=0)==nullptr,
        "Infantry E1 update-position current kind-1 resident unsupported");

    require(actor.target494!=nullptr&&services.targetKind(actor.target494)==11,
        "Infantry E1 update-position requires the ordinary Cell target");
    const auto targetCell=services.cell(services.targetCoordinates(actor.target494));
    require(services.findKind6(targetCell)==nullptr,
        "Infantry E1 update-position target kind-6 resident unsupported");
    require(services.findKind2(targetCell,true)==nullptr,
        "Infantry E1 update-position target kind-2 resident unsupported");
    require(services.findKind1(targetCell,true)==nullptr,
        "Infantry E1 update-position target kind-1 resident unsupported");
    require(services.mission()!=7&&services.mission()!=17,
        "Infantry E1 update-position resident mission branch unsupported");
    require(actor.special370==0,"Infantry E1 update-position special actor branch unsupported");
    require(actor.queuedMissionA0!=-1||actor.target494||actor.alternateTarget228,
        "Infantry E1 update-position no-target transition branch unsupported");

    scheduleInfantryArrivalSight({actor.coordinates88,actor.lastSightRange1f4},services.sight);
    const auto postCell=services.cell(actor.coordinates88);
    (void)services.cellValue(postCell);
    require(actor.locomotor564&&services.locomotorPredicate(actor.locomotor564),
        "Infantry E1 update-position locomotor tail branch unsupported");
    if(actor.onMap7d)services.postUpdate(2);
}

void updateInfantryPositionE1WithEffects(InfantryUpdatePositionE1Actor actor,
        InfantryPositionEffectsE1Actor effects,std::int32_t argument,
        InfantryUpdatePositionE1Services services,
        const InfantryPositionEffectsE1Services& effectServices) {
    require(&actor.coordinates88==&effects.coordinates88&&
        &actor.alternateTarget228==&effects.alternateTarget228&&
        &actor.onMap7d==&effects.onMap7d,
        "Infantry E1 parent/effects composition requires shared actor fields");
    services.postUpdate=[effects,&effectServices](std::int32_t childArgument) mutable {
        applyInfantryPositionEffectsE1(effects,childArgument,effectServices);
    };
    updateInfantryPositionE1(actor,argument,services);
}
}
