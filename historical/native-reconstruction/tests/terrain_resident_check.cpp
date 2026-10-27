// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/TerrainScenario.hpp"
#include "platform/TerrainUnitContext.hpp"
#include "assets/MapCoordinateCell.hpp"
#include "assets/OwnedUnitDrawingMap.hpp"
#include <bit>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void require(bool v,const char* message){if(!v)throw std::runtime_error(message);}
const TerrainUnitContext& context(const Simulation& s){return dynamic_cast<const TerrainUnitContext&>(*s.groundContext());}
std::string snapshot(const TerrainUnitContext& c){
    std::ostringstream out;const auto put=[&](auto... v){((out<<+v<<' '),...);};
    const auto point=[&](Coord p){put(p.x,p.y,p.z);};
    const auto state=[&](const GroundDriveProcessState& s,const UnitMarkState& mark,const UnitDiscoveryActor& d){
        const auto& m=s.movement;point(m.actor.position);point(m.head);put(m.actor.marked74,m.actor.bridge79,m.reached5a0,m.reached5a1,
            m.track,m.index,m.accumulator,m.driving,m.body.desired,m.body.start,m.body.timerStart,m.body.duration,m.body.rate);
        const auto& r=s.ramps;put(r.current,r.previous,r.start,r.padding,r.remaining,r.duration);point(s.destination);
        for(int n:s.route)put(n);put(std::bit_cast<std::uint64_t>(s.percentage),std::bit_cast<std::uint64_t>(s.instancePercentage),
            s.wasRotating,s.crossing57b,s.preparation57a,s.nextX,s.nextY,s.retryStart,s.retryPadding,s.retryRemaining);
        put(mark.onMap,mark.needsRedraw,mark.limbo,mark.special,d.field372,d.current373,d.other374,d.queuedA4,d.owner,d.mission98,d.queuedA0,d.hasTag);
    };
    const auto cell=[&](const MapCellAttributes& a){const auto& v=a.input;
        put(v.position.x,v.position.y,v.tile,v.land,v.tube,v.subTile,v.ice,v.slope,v.level,v.flags,a.overlay,a.passability,a.overlayData,a.extraHeight);};
    const auto& map=*c.map;for(const auto& v:map.cells){cell(v.attributes);put(v.field30,v.wallOwner);}cell(map.fallback);
    put(map.floor.flags,std::bit_cast<std::uint64_t>(map.floor.height),std::bit_cast<std::uint64_t>(map.floor.scale));
    for(const auto& p:map.floor.planes)for(double n:{p.x,p.y,p.offset,p.limit,p.add})put(std::bit_cast<std::uint64_t>(n));
    for(auto n:map.buffer4)put(n);for(auto n:map.buffer10)put(n);
    const auto& u=*c.unit;const auto& f=u.membership.foundation;
    put(f.objectFlag,f.unitFlag,f.fallback.x,f.fallback.y);for(auto p:f.unit)put(p.x,p.y);
    for(const auto& [id,a]:u.membership.actors){put(id);point(a.position);put(a.next,a.alternate,a.eligible,a.typeMapFlag);}
    for(const auto& [id,v]:u.membership.cells)put(id,v.point.x,v.point.y,v.head,v.alternateHead);
    for(const auto& o:u.occupation)put(o.flags,o.ground,o.elevated);
    for(const auto& v:u.visibilityCells)put(v.point.x,v.point.y,v.flags12c,v.flags140);
    put(u.visibility.heightDivisor,u.visibility.mode,u.visibility.overrideValue,u.visibility.currentHouse13d,u.occupationThreshold,
        u.houses.currentHouse,u.houses.mode,u.houses.loading,u.houses.tagContext,u.membership.services.visibilityGate,u.membership.services.notificationArgument);
    for(const auto& [id,h]:u.houses.houses)put(id,h.human134,h.control135,h.discovered13c,h.field13d,h.field5668,h.field5669);
    put(c.redraw.mapMode,c.redraw.counter,c.redraw.tactical,c.redraw.tacticalPresent);
    state(c.state,u.marking,u.discovery);
    if(c.parked){state(c.parked->state,c.parked->marking,c.parked->discovery);
        put(c.parked->turret.has_value());if(c.parked->turret){const auto& t=*c.parked->turret;
            put(t.desired,t.start,t.timerStart,t.duration,t.rate);}}
    return out.str();
}
void distinct(const TerrainUnitContext& a,const TerrainUnitContext& b){
    require(a.map.get()!=b.map.get()&&a.unit.get()!=b.unit.get()&&a.parked.get()!=b.parked.get(),"Resident clone shares owners");
    require(&a.unit->actorState(0)!=&b.unit->actorState(0)&&&a.unit->actorState(1)!=&b.unit->actorState(1),"Resident clone shares actor bindings");
    require(&b.unit->actorState(0)==&b.state&&&b.unit->actorState(1)==&b.parked->state,"Clone retained foreign actor binding");
    require(a.map->buffer4.data()!=b.map->buffer4.data()&&a.map->buffer10.data()!=b.map->buffer10.data(),"Resident clone shares buffers");
    for(std::size_t i=0;i<a.map->cells.size();++i){const auto p=a.map->cells[i].attributes.input.position;const auto slot=std::size_t(p.y)*512+p.x;
        require(b.map->table[slot]==&b.map->cells[i].attributes.input&&a.map->table[slot]!=b.map->table[slot],"Resident clone retains foreign Cells");}
}
UnitDiscoveryActor discovery(){UnitDiscoveryActor a;a.owner=0;a.mission98=2;a.queuedA4=255;return a;}
void guards(){
    std::vector<MapFinalizationCell> cells(1);cells[0].attributes.input.position={1,1};std::vector<int> slots(262144,-1);slots[513]=0;
    MapCellAttributes fallback;MapFloorHeightState floor;std::array<int,16> land{};std::array<float,11> speeds{};
    ResidentCellInputs resident;resident.landMap=land;resident.wheelSpeeds=speeds;Bytes b4(64),b10(160);
    UnitMapSeed seed{cells,slots,fallback,floor,resident,b4,b10,2,1,104};
    std::vector<int> actors;bool fail=false;int decisions=0;
    TerrainUnitContext source(std::make_shared<MutableUnitMap>(seed),{}, {},{},[&](char k,int id,int off,std::uint32_t){
        if(k=='a'&&off==0x373){actors.push_back(id);if(fail)throw std::runtime_error("diagnostic observer");}
    });
    source.bindParked({}, {},discovery());
    bool missingTurret=false;try{(void)source.parked->drawingTurret();}catch(const std::invalid_argument&){missingTurret=true;}
    require(missingTurret,"Parked drawing inferred a missing turret from the body");
    Facing turret;turret.setRate(7);turret.setCurrent(30000,0);turret.setDesired(17000,19);
    source.parked->turret=turret;
    bool legacyRefused=false;try{source.enableAdmission();}catch(const std::invalid_argument&){legacyRefused=true;}
    require(legacyRefused&&!source.admission,"Legacy one-Unit admission accepted resident silently");
    source.enableAdmission({1,0,0,true,{19,-23}}, {},[&](char,int,int,int){++decisions;});
    fail=true;bool caught=false;try{source.unit->membership.services.notify(1,0);}catch(const std::runtime_error&){caught=true;}
    require(caught&&actors==std::vector<int>{1},"Parked discovery observer did not select Unit1");
    fail=false;source.unit->membership.services.notify(0,0);
    require(actors==std::vector<int>({1,0}),"Throwing parked observer leaked its actor identity");
    source.parked->discovery.current373=0;source.unit->membership.services.notify(1,0);
    require(actors==std::vector<int>({1,0,1})&&source.unit->houses.houses.at(0).discovered13c,"Shared House/discovery state differs");
    auto copy=source.clone();auto& clone=dynamic_cast<TerrainUnitContext&>(*copy);distinct(source,clone);
    require(snapshot(source)==snapshot(clone),"Resident clone changed logical state");
    require(clone.parked->drawingTurret().current(21)==turret.current(21),"Clone lost logical parked turret Facing");
    const auto before=snapshot(source);const int count=decisions,notifications=int(actors.size());
    clone.unit->discovery.current373=0;clone.unit->membership.services.notify(0,0);
    clone.parked->discovery.current373=0;clone.unit->membership.services.notify(1,0);clone.services.markNext(-1,-2);
    require(snapshot(source)==before&&decisions==count&&int(actors.size())==notifications,"Resident clone retained live state or observers");
    require(clone.map->fallback.input.position==MapInputPosition{-1,-2}&&clone.unit->visibilityCells.back().point.y==-2,"Resident fallback forwarding differs");
    auto again=clone.clone();auto& twice=dynamic_cast<TerrainUnitContext&>(*again);distinct(clone,twice);
    require(snapshot(clone)==snapshot(twice),"Resident reclone changed state");
    for(int test=0;test<5;++test){auto bad=source.clone();auto& c=dynamic_cast<TerrainUnitContext&>(*bad);
        if(test==0)c.parked->state.movement.driving=true;
        if(test==1)c.parked->state.movement.head={1,2,3};
        if(test==2)c.parked->discovery.owner=1;
        if(test==3)c.unit->membership.actors.at(1).next=99;
        if(test==4)c.unit->membership.cells.at(1000).head=99;
        bool refused=false;try{c.services.markNext(1,1);}catch(const std::invalid_argument&){refused=true;}
        require(refused,"Unsupported resident association accepted");}
    bool duplicate=false;try{source.bindParked({}, {},discovery());}catch(const std::invalid_argument&){duplicate=true;}
    require(duplicate,"Parked Unit rebound over stable callbacks");
    std::cout<<"Shared resident ownership, per-actor discovery/exception restoration, clone/reclone observers/Cells/House/fallback and admission guards: PASS\n";
}
void drawingMap(){
    std::vector<MapFinalizationCell> cells(1);cells[0].attributes.input.position={1,1};
    std::vector<int> slots(262144,-1);slots[513]=0;MapCellAttributes fallback;MapFloorHeightState floor;
    std::array<int,16> land{};std::array<float,11> speeds{};ResidentCellInputs resident;resident.landMap=land;resident.wheelSpeeds=speeds;
    Bytes b4(64),b10(160);UnitMapSeed seed{cells,slots,fallback,floor,resident,b4,b10,2,1,104};
    int stores=0;TerrainUnitContext source(std::make_shared<MutableUnitMap>(seed),{}, {},{},[&](char k,int,int off,std::uint32_t){if(k=='c'&&off==0x24)++stores;});
    OwnedUnitDrawingMap view(*source.map,*source.unit);
    require(stores==0&&source.map->floor.flags==0,"Drawing bind performed a map query");
    auto& live=source.map->cells[0].attributes;
    require(&view.cell({1,1})==&live&&&view.coordinate({513*256,0,0})==&live.input&&&view.cell({513,0})==&live,
        "Drawing lost canonical combined-index aliases");
    live.input.flags=0x1234;live.input.tile=17;live.input.level=3;
    require(view.cell({1,1}).input.flags==0x1234&&view.cell({1,1}).input.tile==17,"Drawing reads stale prepared attributes");
    require(view.floor({384,384,0})==312&&view.relative({384,384,416})==104&&source.map->floor.flags==7,"Drawing did not share owned lazy floor");
    require(cells[0].attributes.input.level==0&&floor.flags==0,"Drawing mutated immutable preparation");
    require(&view.cell({-1,1})==&source.map->fallback&&stores==1,"Drawing fallback write missing");
    const int fallbackId=source.unit->membership.fallbackCell;
    require(source.unit->membership.cells.at(fallbackId).point.x==-1&&source.unit->visibilityCells.back().point.y==1,"Drawing fallback did not update membership/visibility");
    require(&view.coordinate({-1,-1,0})==&source.map->fallback.input&&stores==2&&source.map->fallback.input.position==MapInputPosition{0,0},"Drawing negative division changed");
    auto cloned=source.clone();auto& clone=dynamic_cast<TerrainUnitContext&>(*cloned);OwnedUnitDrawingMap copied(*clone.map,*clone.unit);
    bool refused=false;try{OwnedUnitDrawingMap wrong(*clone.map,*source.unit);}catch(const std::invalid_argument&){refused=true;}
    require(refused,"Drawing accepted mismatched map/membership owners");
    clone.map->cells[0].attributes.input.level=5;
    require(copied.floor({384,384,0})==520&&view.floor({384,384,0})==312,"Drawing clone shares live Cells");
    copied.cell({-4,-5});require(stores==2&&source.map->fallback.input.position==MapInputPosition{0,0}&&clone.unit->visibilityCells.back().point.y==-5,"Drawing clone shares fallback/observers");
    auto twice=clone.clone();auto& again=dynamic_cast<TerrainUnitContext&>(*twice);OwnedUnitDrawingMap rebound(*again.map,*again.unit);
    rebound.cell({-7,-8});require(clone.map->fallback.input.position==MapInputPosition{-4,-5}&&again.unit->visibilityCells.back().point.y==-8,"Drawing reclone retained foreign callbacks");
    std::cout<<"Owned drawing live Cells/floor, canonical aliases, fallback forwarding, mismatched-owner refusal and clone isolation: PASS\n";
}
Simulation scenario(const GameAssets& assets){
    const auto prepared=assets.preparedTerrain;GroundDriveProcessServices s;
    s.advance.notify=[](int){};s.advance.postCell=[]{ };s.noRoute=[]{ };
    s.squareRoot=[&assets](double n){return tableSqrt(assets.renderData,n);};s.uphill=prepared->uphill;s.downhill=prepared->downhill;
    for(unsigned i=0;i<12;++i)s.trackSpeed[i]=prepared->land[i].speed[unsigned(LandSpeed::Track)];
    GroundDriveProcessState initial;initial.movement.reached5a0=1;
    auto c=std::make_unique<TerrainUnitContext>(std::make_shared<MutableUnitMap>(prepared->unitSeed(),prepared),std::move(s),initial);
    GroundDriveProcessState p;p.movement.actor.position={23168,25984,0};p.movement.reached5a0=1;
    Facing turret;turret.setRate(7);turret.setCurrent(32768,0);
    c->bindParked(p,{},discovery(),{},turret);auto& parked=*c->parked;const auto& ps=parked.services;
    setActorRelativeHeight(parked.state.movement.actor,0,416,ps.advance.ground);
    unlimboDriveRamp(parked.state.ramps,[&]{return ps.cell(parked.state.movement.actor.position).ramp;},0,0);ps.advance.ground.mark(1);
    c->enableAdmission({1,0,0,true,{}});
    Simulation sim({86.5,101.5},0,assets.rot,assets.speed,assets.driveData,assets.passive);sim.drive.body.setCurrent(16384,0);sim.enableGround(std::move(c));return sim;
}
}
int main(int argc,char** argv){try{
    if(argc!=2)return 2;if(std::string(argv[1])=="--guards"){guards();drawingMap();return 0;}
    GameAssets assets(argv[1],"mp03t4.map");prepareTerrainAssets(assets);prepareStaticScenery(assets);
    auto sim=scenario(assets);const auto& c=context(sim);const auto initial=snapshot(c);
    const auto clear=[&](int x,int y,int){return terrainCommandCell(assets,x,y);};
    require(!sim.move({90.5,101.5},clear)&&snapshot(c)==initial,"Occupied-target preview changed live resident group");
    require(sim.move({88.5,101.5},clear),"Empty-Cell movement refused with parked resident");
    for(int i=0;i<256&&sim.moving;++i)sim.step();require(!sim.moving&&sim.drive.position.x==22656,"Empty-Cell movement failed");
    const auto warm=snapshot(c);Simulation copy(sim);const auto& copied=context(copy);distinct(c,copied);
    require(snapshot(copied)==warm,"Warm resident Simulation copy changed state");
    require(!copy.move({90.5,101.5},clear)&&snapshot(copied)==warm&&snapshot(c)==warm,"Copied occupied preview changed either group");
    copied.parked->services.advance.ground.mark(0);require(snapshot(c)==warm,"Cloned parked Mark changed live group");
    copied.parked->services.advance.ground.mark(1);require(snapshot(copied)==warm,"Cloned parked unmark/mark failed to restore group");
    auto assigned=scenario(assets);assigned=sim;distinct(c,context(assigned));require(snapshot(context(assigned))==warm,"Resident assignment changed state");
    auto moved=std::move(assigned);moved.turnBody(8192);for(int i=0;i<32;++i)moved.step();moved.stop();moved.turnTurret(4096);moved.step();
    require(snapshot(c)==warm,"Moved resident callbacks changed source group");
    auto pristine=scenario(assets);require(snapshot(context(pristine))==initial,"Resident operations changed immutable renderer preparation");
    Renderer renderer(assets,1024,720);renderer.camera.zoom=2;renderer.center(sim);
    const auto draw=[&](const Simulation& s){const auto& owner=context(s);OwnedUnitDrawingMap map(*owner.map,*owner.unit);
        const std::array<OwnedUnitDrawActor,2> actors{{{0,owner.state,s.drive.turret},{1,owner.parked->state,owner.parked->drawingTurret()}}};
        OwnedUnitDrawScene scene{map,actors,1};renderer.drawOwned(s,scene);
        const auto at=renderer.project(90.5,101.5,owner.parked->state.movement.actor.position.z/104.0);
        require(renderer.hitOwnedActor(scene,at.x,at.y)==1,"Parked selection resolved to the mover");
        const auto& other=context(copy);const std::array<OwnedUnitDrawActor,2> foreign{{{0,other.state,s.drive.turret},{1,owner.parked->state,owner.parked->drawingTurret()}}};
        OwnedUnitDrawScene wrong{map,foreign,-1};bool refused=false;
        try{renderer.drawOwned(s,wrong);}catch(const std::invalid_argument&){refused=true;}
        require(refused,"Drawing accepted an actor from a different simulation map");
    };
    const auto untouchedClone=snapshot(copied);draw(sim);
    require(snapshot(copied)==untouchedClone,"Live draw mutated a preview clone");
    require(renderer.ownedDraws.size()==2&&renderer.unitDrawCalls==2&&renderer.registeredUnits().size()==2,
        "Owned rendering omitted an actor or screen identity");
    require(renderer.registeredUnits()[0].actor==0&&renderer.registeredUnits()[1].actor==1,"Owned screen registry aliased actor identities");
    require(renderer.ownedDraws[1].id==1&&renderer.ownedDraws[1].location==c.parked->state.movement.actor.position&&
        renderer.ownedDraws[1].turret==32768&&renderer.ownedDraws[1].body==0,"Parked rendering inferred pose from mover/body");
    const auto cold=renderer.pixels;const auto hits=renderer.voxelHits;draw(sim);
    require(renderer.pixels==cold&&renderer.voxelHits>hits,"Interleaved warm owned drawing changed final pixels or lost cache reuse");
    auto afterDrawing=scenario(assets);require(snapshot(context(afterDrawing))==initial,"Owned drawing mutated renderer preparation");
    auto production=residentTerrainSimulation(assets);const auto& p=context(production);
    require(production.position.x==86.5&&production.position.y==101.5&&p.parked&&p.admission&&
        p.parked->state.movement.actor.position.x==90*256+128&&p.parked->drawingTurret().desired==32768,
        "Production resident factory lost explicit actors, turret or admission");
    require(p.state.movement.actor.marked74&&p.parked->state.movement.actor.marked74,
        "Production resident factory omitted initial Mark");
    const auto saved=snapshot(p);require(!production.move({90.5,101.5},clear),"Production occupied target accepted");
    require(snapshot(p)==saved,"Production rejected preview changed live state");
    require(production.move({88.5,101.5},clear),"Production empty route refused");
    for(int i=0;i<200&&production.moving;++i)production.step();
    require(!production.moving&&production.position.x==88.5&&production.position.y==101.5,"Production resident mover did not arrive");
    std::cout<<"Owned-data parked-Unit rejection, empty movement, warm Simulation copy/assignment/move/turn, shared membership and independent renderer preparation: PASS\n";
    std::cout<<"Native owned two-actor resources/registry/picking, explicit turret, cold/warm pixels and preview isolation: PASS (not original proof)\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
