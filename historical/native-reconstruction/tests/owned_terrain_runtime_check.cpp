// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/OwnedTerrainRuntime.hpp"
#include "owned_world_snapshot.hpp"
#include "owned_command_validation_checks.hpp"
#include <iostream>
using namespace ra2;
namespace {
void require(bool value,const char* message){if(!value)throw std::runtime_error(message);}
void membership(OwnedTerrainRuntime& rt){
    auto& w=rt.world();const auto& c=w.context();std::array<int,2> counts{};
    for(const auto& [id,cell]:c.unit->membership.cells){
        (void)id;require(cell.alternateHead==-1,"Unexpected alternate Unit list");
        int n=0;for(int actor=cell.head;actor!=-1;actor=c.unit->membership.actors.at(actor).next){
            require(actor>=0&&actor<2&&++n<=2,"Unbound/cyclic owned list");++counts[std::size_t(actor)];
        }
    }
    require(counts==std::array<int,2>{1,1},"An actor is missing or duplicated in shared membership");
    for(int id:{0,1})require(w.actor(id).state.movement.actor.marked74,"Missing actor Mark");
}
void draw(Renderer& view,OwnedTerrainRuntime& rt){
    auto& world=rt.world();const auto& c=world.context();OwnedUnitDrawingMap map(*c.map,*c.unit);
    const std::array<OwnedUnitDrawActor,2> actors{{{0,world.actor(0).state,world.actor(0).turret,&world.movementTargetStorage(0)},{1,world.actor(1).state,world.actor(1).turret,&world.movementTargetStorage(1)}}};
    OwnedUnitDrawScene scene{map,actors,rt.selected()};view.drawOwned(OwnedUnitDrawFrame{rt.tick()},scene);
    require(view.ownedDraws.size()==2&&view.registeredUnits().size()==2,"Owned frame lost a draw/screen identity");
    for(int id:{0,1}){
        const auto& d=view.ownedDraws[std::size_t(id)];auto a=world.actor(id);
        require(d.id==id&&d.location==a.state.movement.actor.position&&d.body==a.state.movement.body.current(rt.tick())&&d.turret==a.turret.current(rt.tick()),"Renderer inferred another actor's pose");
    }
}
}
int main(int argc,char** argv){try{
    if(argc!=2)return 2;
    GameAssets assets(argv[1],"mp03t4.map");prepareTerrainAssets(assets);prepareStaticScenery(assets);
    auto rt=ownedTerrainRuntime(assets);auto& world=rt->world();const auto initial=owned_check::snapshot(world);
    owned_command_check::check(world,assets.driveData->stopScale,assets.speed);
    require(!world.context().admission&&&world.actor(0).state!=&world.actor(1).state,"Owned runtime retained legacy admission/actor alias");
    require(!rt->move(88,101)&&owned_check::snapshot(world)==initial,"Unselected command changed world");
    rt->paused=true;rt->step();require(rt->tick()==0&&owned_check::snapshot(world)==initial,"Paused runtime advanced");rt->paused=false;
    Renderer view(assets,1024,720);view.camera.zoom=2;view.center(world.actor(0).state.movement.actor.position);
    draw(view,*rt);const auto cold=view.pixels;draw(view,*rt);require(view.pixels==cold&&view.voxelHits>0,"Explicit frame lost warm pixel/cache reuse");
    // Initial factory parity against the retained one-mover scenario, using the
    // legacy wrapper only here. It is not part of the new runtime's ownership.
    auto legacy=residentTerrainSimulation(assets);Renderer reference(assets,1024,720);reference.camera=view.camera;
    const auto* c=dynamic_cast<const TerrainUnitContext*>(legacy.groundContext());OwnedUnitDrawingMap map(*c->map,*c->unit);
    const std::array<OwnedUnitDrawActor,2> actors{{{0,c->state,legacy.drive.turret},{1,c->parked->state,c->parked->drawingTurret()}}};
    OwnedUnitDrawScene scene{map,actors,-1};reference.drawOwned(legacy,scene);
    require(reference.pixels==cold,"Explicit runtime factory changed initial bounded presentation");
    rt->select(0);const auto before=owned_check::snapshot(world);const auto pixels=view.pixels;
    auto refused=rt->move(90,101);require(refused&&refused->status!=OwnedUnitMoveStatus::accepted&&owned_check::snapshot(world)==before&&view.pixels==pixels,"Occupied preview changed live world/render");
    const auto initial0=world.actor(0).state.movement.actor.position;
    auto accepted=rt->move(88,101);require(accepted&&accepted->status==OwnedUnitMoveStatus::accepted&&rt->tick()==0&&world.actor(0).state.movement.actor.position==initial0,"Move refused or committed preview time/position");
    rt->select(1);const auto future=owned_check::snapshot(world);
    refused=rt->move(88,101);require(refused&&refused->status!=OwnedUnitMoveStatus::accepted&&owned_check::snapshot(world)==future,"Future occupied destination accepted or changed the other route");
    accepted=rt->move(92,101);require(accepted&&accepted->status==OwnedUnitMoveStatus::accepted,"Actor1 empty move rejected");
    for(int i=0;i<3;++i){rt->step();membership(*rt);draw(view,*rt);}
    require(world.actor(0).state.movement.driving&&world.actor(1).state.movement.driving,"Both distinct actors never moved together");
    const auto targetBody=std::uint16_t(world.actor(0).state.movement.body.desired+8192);
    const auto targetTurret=std::uint16_t(world.actor(0).turret.desired-8192);
    rt->select(0);rt->turnBody(8192);rt->turnTurret(-8192);
    require(world.actor(0).commands.pendingBodyTurn.has_value()&&!world.actor(1).commands.manualTurret,"Moving body turn not deferred or turret aliased");
    rt->select(1);rt->stop();
    for(int i=0;i<160;++i){rt->step();membership(*rt);if(i%8==0)draw(view,*rt);}
    require(!rt->moving(0)&&!rt->moving(1)&&!world.actor(0).commands.pendingBodyTurn&&
        world.actor(0).state.movement.body.current(rt->tick())==targetBody&&world.actor(0).turret.current(rt->tick())==targetTurret,"Independent stop/deferred body/turret did not settle");
    require(world.actor(1).state.movement.actor.position.x<cellCenter(92,101).x,"Actor1 stop discarded its committed-track boundary");
    const auto state=owned_check::snapshot(world);const int oldTick=rt->tick();auto calls=OwnedTerrainRuntime::calls(world);calls[1].notify={};bool fault=false;
    try{rt->step(calls);}catch(const std::invalid_argument&){fault=true;}
    require(fault&&rt->tick()==oldTick&&owned_check::snapshot(world)==state,"Invalid actor1 services entered a live tick");
    std::vector<int> order;bool reentry=false;
    rt->step(OwnedTerrainRuntime::calls(world),[&](int id,bool){order.push_back(id);
        try{rt->step();}catch(const std::logic_error&){reentry=true;}});
    require(order==std::vector<int>{0,1}&&reentry&&rt->tick()==oldTick+1,"Runtime observer/reentry lost scheduled order");
    calls=OwnedTerrainRuntime::calls(world);fault=false;
    try{rt->step(calls,[](int,bool){throw std::runtime_error("runtime observer fault");});}
    catch(const std::runtime_error& e){fault=std::string(e.what())=="runtime observer fault";}
    require(fault&&rt->tick()==oldTick+2,"Live runtime fault hidden or tick rolled back");
    rt->step();require(rt->tick()==oldTick+3,"Fault left runtime guard armed");
    OwnedTerrainRuntime wrap(world.clone(),OwnedUnitClearance(Bytes(262144,1)),
        OwnedUnitMovePolicy{{{assets.speed,assets.speed},{0,0}},4096},assets.driveData->stopScale,2147483647);
    wrap.step();require(wrap.tick()==(-2147483647-1),"Runtime tick did not wrap signed32");
    rt=ownedTerrainRuntime(assets);require(owned_check::snapshot(rt->world())==initial,"Reset retained old world records");draw(view,*rt);
    rt->select(1);rt->turnBody(-8192);rt->turnTurret(8192);const auto other=rt->world().actor(0).state.movement.body.desired;
    for(int i=0;i<40;++i)rt->step();
    require(rt->world().actor(1).state.movement.body.current(rt->tick())==8192&&rt->world().actor(0).state.movement.body.desired==other,"Actor1 body command affected actor0");
    rt->select(1);accepted=rt->move(91,101);require(accepted&&accepted->status==OwnedUnitMoveStatus::accepted,"Actor1 replacement move failed");
    accepted=rt->move(92,101,true);require(accepted&&accepted->status==OwnedUnitMoveStatus::accepted,"Actor1 appended move failed");
    for(int i=0;i<400&&rt->moving(1);++i){rt->step();membership(*rt);if(i%16==0)draw(view,*rt);}
    require(!rt->moving(1)&&rt->world().actor(1).state.movement.actor.position.x==cellCenter(92,101).x,"Actor1 appended route did not arrive");
    draw(view,*rt);
    std::cout<<"Owned runtime: initial legacy parity, no mirror, distinct two-Process movement, shared membership, future occupied refusal, independent stop/body/turret, pause/reset, appended route and explicit-frame warm rendering: PASS (native integration, not original frame proof)\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
