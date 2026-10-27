// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/TerrainUnitContext.hpp"
#include "sim/Simulation.hpp"
namespace ra2 {
const Facing& TerrainUnitContext::ParkedUnit::drawingTurret()const{
    if(!turret)throw std::invalid_argument("Parked drawing requires an explicit turret Facing");
    return *turret;
}
TerrainUnitContext::TerrainUnitContext(std::shared_ptr<MutableUnitMap> owned,GroundDriveProcessServices supplied,
    const GroundDriveProcessState& initial,const GroundStateStore& actorStore,
    const PreparedMembershipStore& store,const PreparedUnitMembership::Query& query)
    :supplied_(std::move(supplied)),map(std::move(owned)){
    if(!map)throw std::invalid_argument("Terrain Unit requires owned mutable Cells");
    state=initial;unit=std::make_unique<PreparedUnitMembership>(map->input(),store,query);
    unit->visibility={104,1,0,0};unit->houses.currentHouse=0;unit->houses.mode=1;unit->houses.loading=1;
    unit->houses.houses[0].human134=1;unit->discovery.owner=0;unit->discovery.mission98=2;
    unit->discovery.queuedA0=-1;unit->discovery.queuedA4=255;
    for(auto& c:unit->visibilityCells)c.flags12c=8;
    unit->redrawMap=[this,store]{requestMapRedraw(redraw,0,[&](auto e){if(store)store('t',0,0,e.value);});};
    const auto check=[this](const MapCellInput& c,bool neighbor)->std::uint8_t{
        const auto* a=map->find(c);
        const bool overlay=a&&a->overlay!=-1;
        const bool ordinaryOverlay=overlay&&neighbor&&a->overlay>=0&&
            std::size_t(a->overlay)<map->resident.overlays.size();
        if(!a||(overlay&&!ordinaryOverlay)||c.tube!=-1||c.slope>20||(c.flags&0x100u))
            throw UnsupportedGroundRoute("Terrain movement refuses Cell ("+std::to_string(c.position.x)+","+
                std::to_string(c.position.y)+"): missing="+std::to_string(!a)+
                " overlay="+(a?std::to_string(a->overlay):"unknown")+" tube="+std::to_string(c.tube)+
                " slope="+std::to_string(c.slope)+" flags="+std::to_string(c.flags)+
                " query="+(neighbor?"ordinary-neighbor":"movement"));
        return ordinaryOverlay?map->resident.overlays[std::size_t(a->overlay)].flag1FD:0;
    };
    terrain_=std::make_unique<PreparedDriveTerrain>(map->floor,map->levelHeight,unit->world(),
        [check](const auto& c){(void)check(c,false);},query,[check](const auto& c){return check(c,true);});
    services=unit->bind(terrain_->bind(supplied_),state,actorStore);
}
std::unique_ptr<GroundDriveContext> TerrainUnitContext::clone()const{
    // Keep warm floor/fallback, logical memberships and actor state, with no
    // pointers/callbacks into the source context and no live observation hooks.
    auto copy=std::make_unique<TerrainUnitContext>(std::shared_ptr<MutableUnitMap>(map->clone()),supplied_,state);
    if(parked)copy->bindParked(parked->state,parked->marking,parked->discovery,{},parked->turret);
    copy->redraw=redraw;copy->unit->copyStateFrom(*unit);
    if(admission)copy->enableAdmission(admission->inputs());
    return copy;
}
void TerrainUnitContext::bindParked(const GroundDriveProcessState& state,const UnitMarkState& mark,
    const UnitDiscoveryActor& discovery,const GroundStateStore& actorStore,std::optional<Facing> turret){
    if(parked||admission)throw std::invalid_argument("Parked Unit must bind once before admission");
    parked=std::make_unique<ParkedUnit>();parked->state=state;parked->marking=mark;parked->discovery=discovery;
    parked->turret=turret;
    parked->services=unit->bindParked(terrain_->bind(supplied_),parked->state,parked->marking,parked->discovery,actorStore);
}
void TerrainUnitContext::enableAdmission(PreparedUnitAdmissionInputs inputs,
    const PreparedUnitMembership::Query& query,const PreparedUnitAdmission::Decision& decision,
    const GroundStateStore& driveStore){
    if(admission)throw std::invalid_argument("Terrain Unit admission is already bound");
    admission=std::make_unique<PreparedUnitAdmission>(map->input(),*unit,state,services,inputs,query,decision);
    admissionDriveStore_=driveStore;
    services=admission->bind(services);
}
bool TerrainUnitContext::process(const DriveData& data,int speed,int tick,int padding,
    const GroundStateStore& actorStore,const GroundStateStore& rampStore){
    if(admission)return admission->process(data,speed,tick,padding,services,actorStore,rampStore,admissionDriveStore_);
    return GroundDriveContext::process(data,speed,tick,padding,actorStore,rampStore);
}
}
