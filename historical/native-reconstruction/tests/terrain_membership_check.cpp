// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/TerrainScenario.hpp"
#include "platform/TerrainUnitContext.hpp"
#include "assets/MapCoordinateCell.hpp"
#include <bit>
#include <iostream>
#include <sstream>
#include <type_traits>
using namespace ra2;
static_assert(!std::is_copy_constructible_v<PreparedUnitAdmission> &&
    !std::is_move_constructible_v<PreparedUnitAdmission>);
static_assert(!std::is_copy_constructible_v<TerrainUnitContext> &&
    !std::is_move_constructible_v<TerrainUnitContext> &&
    !std::is_move_assignable_v<TerrainUnitContext>);
namespace {
void require(bool b,const char* message){if(!b)throw std::runtime_error(message);}
const TerrainUnitContext& context(const Simulation& s){
    const auto* c=dynamic_cast<const TerrainUnitContext*>(s.groundContext());
    require(c,"Missing production terrain context");return *c;
}
// Serialize logical values, never object padding or host pointer addresses.
std::string snapshot(const TerrainUnitContext& c){
    std::ostringstream out;const auto put=[&](auto... n){((out<<+n<<' '),...);};
    const auto coord=[&](Coord p){put(p.x,p.y,p.z);};
    const auto cell=[&](const MapCellAttributes& a){const auto& v=a.input;
        put(v.position.x,v.position.y,v.tile,v.land,v.tube,v.subTile,v.ice,v.slope,v.level,v.flags,
            a.overlay,a.passability,a.overlayData,a.extraHeight);};
    const auto& map=*c.map;
    for(const auto& v:map.cells){cell(v.attributes);put(v.field30,v.wallOwner);}
    cell(map.fallback);put(map.floor.flags,std::bit_cast<std::uint64_t>(map.floor.height),std::bit_cast<std::uint64_t>(map.floor.scale));
    for(const auto& p:map.floor.planes)for(double n:{p.x,p.y,p.offset,p.limit,p.add})put(std::bit_cast<std::uint64_t>(n));
    for(auto n:map.buffer4)put(n);for(auto n:map.buffer10)put(n);
    const auto& u=*c.unit;const auto& f=u.membership.foundation;
    put(f.objectFlag,f.unitFlag,f.fallback.x,f.fallback.y);for(auto p:f.unit)put(p.x,p.y);
    put(u.membership.fallbackCell,u.membership.services.visibilityGate,u.membership.services.notificationArgument);
    for(const auto& [id,a]:u.membership.actors){put(id);coord(a.position);put(a.next,a.alternate,a.eligible,a.typeMapFlag);}
    for(const auto& [id,v]:u.membership.cells)put(id,v.point.x,v.point.y,v.head,v.alternateHead);
    for(const auto& o:u.occupation)put(o.flags,o.ground,o.elevated);
    for(const auto& v:u.visibilityCells)put(v.point.x,v.point.y,v.flags12c,v.flags140);
    put(u.visibility.heightDivisor,u.visibility.mode,u.visibility.overrideValue,u.visibility.currentHouse13d,u.occupationThreshold);
    put(u.marking.onMap,u.marking.needsRedraw,u.marking.limbo,u.marking.special);
    const auto& d=u.discovery;put(d.field372,d.current373,d.other374,d.queuedA4,d.owner,d.mission98,d.queuedA0,d.hasTag);
    put(u.houses.currentHouse,u.houses.mode,u.houses.loading,u.houses.tagContext);
    for(const auto& [id,h]:u.houses.houses)put(id,h.human134,h.control135,h.discovered13c,h.field13d,h.field5668,h.field5669);
    put(c.redraw.mapMode,c.redraw.counter,c.redraw.tactical,c.redraw.tacticalPresent);
    const auto& s=c.state;const auto& m=s.movement;coord(m.actor.position);put(m.actor.marked74,m.actor.bridge79);coord(m.head);
    put(m.body.desired,m.body.start,m.body.timerStart,m.body.duration,m.body.rate,m.track,m.index,m.accumulator,m.driving,m.reached5a0,m.reached5a1);
    const auto& r=s.ramps;put(r.current,r.previous,r.start,r.padding,r.remaining,r.duration);coord(s.destination);
    for(auto n:s.route)put(n);put(std::bit_cast<std::uint64_t>(s.percentage),std::bit_cast<std::uint64_t>(s.instancePercentage),s.wasRotating,
        s.crossing57b,s.preparation57a,s.nextX,s.nextY,s.retryStart,s.retryPadding,s.retryRemaining);
    return out.str();
}
void linked(const Simulation& sim){
    const auto& c=context(sim);int primary=0,alternate=0;
    for(const auto& [id,cell]:c.unit->membership.cells){primary+=cell.head==0;alternate+=cell.alternateHead==0;}
    require(primary==1&&alternate==0&&c.state.movement.actor.marked74==1,"Unit membership lost or duplicated");
    const auto& member=c.unit->membership.actors.at(0);
    const int x=sim.drive.position.x/256,y=sim.drive.position.y/256;
    const int id=c.map->slots.at(std::size_t(y)*512+x);
    require(id>=0&&c.unit->membership.cells.at(1000+id).head==0,"Unit linked to wrong current Cell");
    // The member's stored point is refreshed at Mark, not residual interpolation.
    require(member.next==-1&&member.alternate==0,"Unit list links differ");
}
void distinct(const TerrainUnitContext& a,const TerrainUnitContext& b){
    require(a.map.get()!=b.map.get()&&a.unit.get()!=b.unit.get(),"Clone shares mutable owner");
    require(a.map->cells.data()!=b.map->cells.data()&&a.map->buffer4.data()!=b.map->buffer4.data()&&
        a.map->buffer10.data()!=b.map->buffer10.data(),"Clone shares Cell/buffer storage");
    for(std::size_t i=0;i<a.map->cells.size();++i){const auto p=a.map->cells[i].attributes.input.position;
        const auto slot=std::size_t(p.y)*512+p.x;
        require(b.map->table[slot]==&b.map->cells[i].attributes.input&&a.map->table[slot]!=b.map->table[slot],"Clone has stale canonical pointers");}
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){
        std::vector<MapFinalizationCell> cells(1);cells[0].attributes.input.position={1,1};
        std::vector<int> slots(262144,-1);slots[513]=0;MapCellAttributes fallback;MapFloorHeightState floor;
        std::array<int,16> land{};std::array<float,11> speeds{};ResidentCellInputs resident;resident.landMap=land;resident.wheelSpeeds=speeds;
        Bytes b4(64),b10(160);UnitMapSeed seed{cells,slots,fallback,floor,resident,b4,b10,2,1,104};
        auto owned=std::make_shared<MutableUnitMap>(seed);TerrainUnitContext source(owned,{});auto copy=source.clone();
        auto& clone=dynamic_cast<TerrainUnitContext&>(*copy);distinct(source,clone);
        require(snapshot(source)==snapshot(clone),"Valid empty clone changed values");
        clone.unit->membership.actors.at(0).eligible=9;clone.map->buffer4[0]=7;clone.map->cells[0].attributes.passability=6;
        require(source.unit->membership.actors.at(0).eligible!=9&&source.map->buffer4[0]==0&&source.map->cells[0].attributes.passability==0,"Clone aliases source");
        int refused=0;
        for(int test=0;test<6;++test){auto bad=seed;
            if(test==0)bad.width=1;if(test==1)bad.levelHeight=105;if(test==2)bad.buffer10={};if(test==3)bad.slots={};
            if(test==4)bad.resident.landMap={};if(test==5)slots[513]=2;
            try{MutableUnitMap invalid(bad);}catch(const std::invalid_argument&){++refused;}}
        require(refused==6,"Invalid mutable map seed accepted");
        int queries=0,decisions=0;
        source.enableAdmission({},[&](char,Coord){++queries;},[&](char,int,int,int){++decisions;});
        require(!source.services.reserve&&!source.services.admit&&source.admission,"Legacy admission services retained");
        source.services.markNext(1,1);
        require(queries==1&&decisions==1,"Actual next-Cell decision was not observed");
        // Every decision must refresh the canonical occupation and lists. These
        // are native safety checks, not evidence of original warning delivery.
        source.unit->occupation[0].ground=1;bool warningRefused=false;
        try{source.services.markNext(1,1);}catch(const std::invalid_argument&){warningRefused=true;}
        require(warningRefused,"Admission used stale occupation");source.unit->occupation[0].ground=0;
        source.services.markNext(1,1);
        auto admittedCopy=source.clone();auto& admitted=dynamic_cast<TerrainUnitContext&>(*admittedCopy);
        require(admitted.admission&&admitted.admission.get()!=source.admission.get(),"Clone shares admission owner");
        const auto sourceBefore=snapshot(source);const int beforeQueries=queries,beforeDecisions=decisions;
        admitted.services.markNext(-1,-2);
        require(admitted.map->fallback.input.position==MapInputPosition{-1,-2}&&
            admitted.unit->visibilityCells.back().point.y==-2&&
            admitted.unit->cellMembership(admitted.map->cells.size()).point.x==-1,"Admission fallback forwarding differs");
        require(snapshot(source)==sourceBefore&&queries==beforeQueries&&decisions==beforeDecisions,"Cloned admission retained source state or observer");
        admitted.unit->membership.cells.at(1000).head=99;bool residentRefused=false;
        try{admitted.services.markNext(1,1);}catch(const std::invalid_argument&){residentRefused=true;}
        require(residentRefused,"Unsupported stationary resident accepted");
        bool rebound=false;try{source.enableAdmission();}catch(const std::invalid_argument&){rebound=true;}
        require(rebound,"Admission rebound over live callbacks");
        source.unit->discovery.hasTag=true;bool tagRefused=false;
        try{(void)source.clone();}catch(const std::invalid_argument&){tagRefused=true;}
        require(tagRefused,"Unsupported tagged preview accepted");
        std::cout<<"Mutable map ownership, admission live occupation/list refusal, fallback/clone observer isolation and Tag guards: PASS\n";return 0;
    }
    if(argc!=2)return 2;GameAssets assets(argv[1],"mp03t4.map");prepareTerrainAssets(assets);prepareStaticScenery(assets);
    // The immutable prepared map is independently copied, so no test callback can mutate it.
    auto source=std::make_shared<MutableUnitMap>(assets.preparedTerrain->unitSeed(),assets.preparedTerrain);
    TerrainUnitContext staticCopy(source,{});const auto initialSource=snapshot(staticCopy);
    auto sim=terrainSimulation(assets,{86.5,101.5});linked(sim);
    const auto& c=context(sim);const auto initial=snapshot(c);
    require(c.unit->discovery.current373==1&&c.unit->houses.houses.at(0).discovered13c==1,"Initial recovered discovery did not run");
    const int start=c.map->slots.at(101*512+86);
    require((c.unit->occupation.at(std::size_t(start)).ground&0x20)!=0,"Initial occupation missing");
    const auto clear=[&](int x,int y,int){return terrainCommandCell(assets,x,y);};
    require(!sim.move({92.5,101.5},[](int x,int,int){return x<90;}),"Partially blocked preview accepted");
    require(snapshot(c)==initial,"Rejected preview mutated live map/lists/buffers/House/actor");
    auto commandExpected=c.clone();
    require(sim.move({92.5,101.5},clear),"Crossing order refused");
    require(c.admission!=nullptr,"Terrain scenario retained supplied admission");
    commandExpected->state.route=c.state.route;
    require(snapshot(c)==snapshot(dynamic_cast<const TerrainUnitContext&>(*commandExpected)),"Successful preview mutated state beyond command queue");
    auto blocked=terrainSimulation(assets,{73.5,41.5},16384);const auto blockedBefore=snapshot(context(blocked));
    require(!blocked.move({74.5,41.5},clear)&&blocked.status=="MOVEMENT REJECTED / NO DETOUR SEARCH","Actual admission rejection did not reach command adapter");
    require(snapshot(context(blocked))==blockedBefore,"Admission-refused preview mutated live owned state");
    for(int i=0;i<19;++i)sim.step();linked(sim);const auto warm=snapshot(c);
    Simulation copied(sim);require(snapshot(context(copied))==warm,"Warm copy changed logical state");distinct(c,context(copied));
    copied.stop();for(int i=0;i<100&&copied.moving;++i)copied.step();linked(copied);
    require(snapshot(c)==warm,"Stopping a copied Unit changed source state");
    // Copy assignment destroys its prior context; callbacks must bind to the new one.
    auto assigned=terrainSimulation(assets,{86.5,101.5});assigned=sim;distinct(c,context(assigned));
    require(snapshot(context(assigned))==warm,"Copy assignment changed warm state");
    auto moved=std::move(assigned);moved.turnBody(8192);for(int i=0;i<100;++i)moved.step();linked(moved);
    auto moveAssigned=terrainSimulation(assets,{86.5,101.5});moveAssigned=std::move(moved);moveAssigned.turnTurret(4096);moveAssigned.step();linked(moveAssigned);
    require(snapshot(c)==warm,"Move/turn callbacks changed the source context");
    // Invalid-coordinate fallback writes and lazy plane caches belong to each clone.
    auto clone=c.clone();auto& warmClone=dynamic_cast<TerrainUnitContext&>(*clone);
    const auto fallbackBefore=c.map->fallback.input.position;
    (void)mapCoordinateCell({-257,-513,0},warmClone.unit->world(),262144);
    (void)cellFloorHeight(warmClone.map->floor,104,4,13,127,129);
    require(c.map->fallback.input.position==fallbackBefore&&snapshot(c)==warm,"Clone fallback/lazy state leaked");
    require(warmClone.map->fallback.input.position==MapInputPosition{-1,-2},"Clone fallback was not forwarded");
    require(warmClone.unit->visibilityCells.back().point.x==-1&&warmClone.unit->membership.cells.at(warmClone.unit->membership.fallbackCell).point.y==-2,"Fallback logical views diverged");
    auto reclone=warmClone.clone();auto& twice=dynamic_cast<TerrainUnitContext&>(*reclone);
    require(snapshot(twice)==snapshot(warmClone),"Warm fallback/lazy snapshot changed");distinct(warmClone,twice);
    (void)mapCoordinateCell({-1025,-769,0},twice.unit->world(),262144);
    require(warmClone.map->fallback.input.position==MapInputPosition{-1,-2},"Reclone callback targets parent");
    for(int i=0;i<1024&&sim.moving;++i){sim.step();linked(sim);}
    require(!sim.moving&&sim.tick==78,"Live crossing arrival differs");
    require(c.unit->membership.cells.at(1000+start).head==-1&&(c.unit->occupation.at(std::size_t(start)).ground&0x20)==0,"Old Cell list/occupation retained");
    sim.turnBody(8192);for(int i=0;i<32;++i)sim.step();linked(sim);
    require(sim.drive.body.current(sim.tick)==sim.drive.body.desired,"Body turn did not settle");
    auto fresh=std::make_shared<MutableUnitMap>(assets.preparedTerrain->unitSeed(),assets.preparedTerrain);TerrainUnitContext finalSource(fresh,{});
    require(snapshot(finalSource)==initialSource,"Simulation or preview modified shared renderer preparation");
    std::cout<<"Production Unit membership, successful/rejected preview isolation, warm clone/copy/move/assignment, fallback/lazy/House/buffer independence and crossing/stop/turn: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
