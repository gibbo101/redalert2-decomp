// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/OwnedTerrainRuntime.hpp"
#include "owned_world_snapshot.hpp"
#include <iostream>
using namespace ra2;
namespace {
void require(bool value,const char* why){if(!value)throw std::runtime_error(why);}
void draw(Renderer& view,OwnedTerrainRuntime& rt){
    const std::array<const void*,2> targets{rt.world().movementTarget(0),rt.world().movementTarget(1)};
    auto& w=rt.world();const auto& c=w.context();OwnedUnitDrawingMap map(*c.map,*c.unit);
    const std::array<OwnedUnitDrawActor,2> actors{{{0,w.actor(0).state,w.actor(0).turret,&w.movementTargetStorage(0)},{1,w.actor(1).state,w.actor(1).turret,&w.movementTargetStorage(1)}}};
    OwnedUnitDrawScene scene{map,actors,rt.selected()};view.drawOwned(OwnedUnitDrawFrame{rt.tick()},scene);
    require(view.ownedDraws.size()==2,"Scatter drawing lost an actor");
    for(int i:{0,1})require(view.ownedDraws[i].id==i&&view.ownedDraws[i].location==w.actor(i).state.movement.actor.position,
        "Scatter drawing inferred another actor position");
    for(int i:{0,1})require(view.ownedDraws[i].target494==bool(targets[i])&&w.movementTarget(i)==targets[i],
        "Scatter drawing lost, changed or substituted an actual target");
}
void preparationEncounter(const GameAssets& assets,int stagingTicks=0){
    auto rt=ownedTerrainRuntime(assets,OwnedUnitAdvancePolicy::ordinaryScatter);
    auto& w=rt->world();
    Renderer view(assets,1024,720);view.camera.zoom=2;view.center(w.actor(1).state.movement.actor.position);
    const auto stage=[&](int id,int x,int y){
        const int start=rt->tick();
        rt->select(id);const auto result=rt->move(x,y);
        require(result&&result->status==OwnedUnitMoveStatus::accepted,"Preparation staging command refused");
        int n=0;try{while(rt->moving(id)&&++n<=1024)rt->step();}
        catch(...){std::cerr<<"preparation staging fault actor "<<id<<" target "<<x<<','<<y<<" tick "<<rt->tick()<<'\n';throw;}
        require(n<=1024&&!rt->moving(id),"Preparation staging failed to settle");
        if(stagingTicks){
            require(rt->tick()-start<=stagingTicks,"Preparation staging exceeded fixed timing");
            while(rt->tick()-start<stagingTicks)rt->step();
        }
        std::cout<<"Preparation stage actor "<<id<<" -> "<<x<<','<<y<<": "<<rt->tick()-start<<" ticks; tick "<<rt->tick()<<'\n';
    };
    stage(1,94,101);stage(0,91,101);stage(0,91,104);stage(1,93,104);
    draw(view,*rt);
    rt->select(0);
    const auto refusedState=owned_check::snapshot(w);const auto refusedPixels=view.pixels;const int refusedTick=rt->tick();
    int refusals=0;
    for(const auto [x,y]:{std::pair{-1,104},std::pair{500,500}}){
        const auto result=rt->move(x,y);
        require(result&&result->status!=OwnedUnitMoveStatus::accepted&&rt->tick()==refusedTick&&
            owned_check::snapshot(w)==refusedState&&view.pixels==refusedPixels,
            "Scatter command-domain refusal changed source owners/time/warm pixels");++refusals;
    }
    bool masked=false;
    for(int y=99;y<=109&&!masked;++y)for(int x=87;x<=98&&!masked;++x){
        if(!assets.preparedTerrain->find(x,y)||terrainCommandCell(assets,x,y))continue;
        const auto result=rt->move(x,y);
        require(result&&result->status!=OwnedUnitMoveStatus::accepted&&rt->tick()==refusedTick&&
            owned_check::snapshot(w)==refusedState&&view.pixels==refusedPixels,
            "Scatter command accepted a masked Cell or changed refused state");masked=true;++refusals;
    }
    require(masked&&refusals==3,"Scatter command refusal coverage missing");
    const auto resident=w.actor(1).state.movement.actor.position;
    rt->select(0);const auto order=rt->move(94,104);
    require(order&&order->status==OwnedUnitMoveStatus::accepted&&order->ticks==0,
        "Preparation occupied-area order refused or predicted movement");
    int dispatch=0,counters=0,clones=0,faults=0;Coord destination{};
    auto calls=OwnedTerrainRuntime::calls(w);
    calls[0].actorStore=[&](int off,int value){if(off==0x53c){require(value==10,"Preparation counter value");++counters;}};
    calls[0].scatter=[&](char group,char kind,auto actor,auto,auto){if(group=='c'&&kind=='S'){
        require(actor==1,"Preparation dispatched an actor outside actual candidate membership");++dispatch;}};
    for(int n=0;n<512&&(rt->moving(0)||rt->moving(1));++n){
        rt->step(calls,[&](int actor,bool){
            if(actor!=0||!w.pendingScatterRoute(1))return;
            destination=w.actor(1).state.destination;
            require(w.actor(1).wait.remaining==8&&w.actor(1).state.retryRemaining==0,
                "Scatter factory lost separate original-backed wait/retry timer inputs");
            draw(view,*rt); // Draw during the target-bearing dispatch, before routing.
            require(view.ownedDraws[1].target494,"Resident target was not passed to the surface consumer");
            const auto before=owned_check::snapshot(w);const auto pixels=view.pixels;
            const auto* target=w.movementTarget(1);auto copy=w.clone();
            require(copy->preparationCounter(0)==w.preparationCounter(0)&&copy->movementTarget(1)!=target,
                "Preparation clone lost counter or retained source Cell identity");
            OwnedUnitOrders(*copy,assets.driveData->stopScale).followScatter(1);
            // Force the supplied callback at its actual empty-queue consumer on
            // this discarded diagnostic clone, without modifying the live pose.
            copy->actor(1).state.route[0]=-1;
            auto effects=OwnedTerrainRuntime::calls(*copy);
            copy->process(1,assets.speed,rt->tick(),0,effects[1]);
            require(copy->preparationCounter(1)==10&&w.preparationCounter(1)==0,
                "Preparation callback/counter remained bound to source actor");
            bool fault=false;
            try{w.preview([&](OwnedUnitWorld& preview){
                OwnedUnitOrders(preview,assets.driveData->stopScale).followScatter(1);
                preview.actor(1).state.route[0]=-1;
                auto bound=OwnedTerrainRuntime::calls(preview);
                bound[1].actorStore=[](int off,int){if(off==0x53c)throw std::runtime_error("preparation observer fault");};
                preview.process(1,assets.speed,rt->tick(),0,bound[1]);return true;
            });}catch(const std::runtime_error& e){fault=std::string(e.what())=="preparation observer fault";}
            require(fault,"Preparation preview hid an unrelated observer fault");++faults;
            require(owned_check::snapshot(w)==before&&w.movementTarget(1)==target&&view.pixels==pixels,
                "Discarded preparation changed source world or warm drawing");++clones;
        });
        if(n%8==0)draw(view,*rt);
    }
    const bool counterCoverage=counters==(stagingTicks==200?1:2);
    if(!(dispatch==1&&counterCoverage&&clones==1&&faults==1))std::cerr<<"Preparation coverage at tick "<<rt->tick()
        <<": dispatch="<<dispatch<<" counters="<<counters<<" clones="<<clones<<" faults="<<faults<<'\n';
    require(dispatch==1&&counterCoverage&&clones==1&&faults==1&&w.preparationCounter(0)==10,
        "Preparation did not retain expected resident dispatch/counter/clone/fault coverage");
    if(stagingTicks==200)require(destination==Coord{23680,27008,416},
        "Alternate timing changed the actual nearby-selected destination");
    require(!rt->moving(0)&&!rt->moving(1)&&w.actor(1).state.movement.actor.position!=resident&&
        w.actor(1).state.movement.actor.position==destination&&!w.movementTarget(1),
        "Preparation assigned a target without actual resident arrival");
    stage(0,93,104);const auto arrived0=w.actor(0).state.movement.actor.position;
    require(arrived0.x==resident.x&&arrived0.y==resident.y,"Mover could not enter vacated resident Cell");
    stage(1,92,104);
    require(w.actor(0).state.movement.actor.position==arrived0&&w.actor(1).state.movement.actor.position!=destination,
        "Displaced actor's later command changed the mover");
    draw(view,*rt);const auto pixels=view.pixels;draw(view,*rt);
    require(view.pixels==pixels,"Preparation warm draw changed pixels");
    std::cout<<"Owned preparation: "<<dispatch<<" actual resident dispatch, "<<counters<<" counter stores, "
        <<clones<<" discarded callback/target/counter clones, "<<faults
        <<" propagated preview faults; resident arrived "<<destination.x/256<<','<<destination.y/256
        <<", mover entered vacated Cell, independent later commands and warm drawing PASS"
        <<" (native integration; no distinct-original interaction or SDL proof)\n";
}
void crushableApproach(const GameAssets& assets){
    auto rt=ownedTerrainRuntime(assets,OwnedUnitAdvancePolicy::ordinaryScatter);auto& w=rt->world();
    Renderer view(assets,1024,720);view.camera.zoom=2;view.center(w.actor(0).state.movement.actor.position);
    rt->select(0);auto order=rt->move(87,101);
    require(order&&order->status==OwnedUnitMoveStatus::accepted&&order->ticks==0,"Crushable approach staging refused or predicted ticks");
    for(int n=0;n<128&&rt->moving(0);++n)rt->step();
    require(!rt->moving(0)&&w.actor(0).state.movement.actor.position.x/256==87,"Crushable approach staging failed");
    const auto& map=*w.context().map;const auto* neighbor=map.table[103*512+85];
    require(neighbor,"Missing original Crushable neighbor");const auto* attributes=map.find(*neighbor);
    require(attributes&&attributes->overlay>=0&&std::size_t(attributes->overlay)<map.resident.overlays.size()&&
        map.resident.overlays[attributes->overlay].flag1FD,"Original approach neighbor is not Crushable");
    const auto other=w.actor(1);const auto resident=other.state.movement.actor.position;
    const auto otherQueue=other.state.route;const auto otherDestination=other.state.destination;const auto otherCommands=other.commands;
    const auto otherTurret=other.turret.desired;
    order=rt->move(86,102);
    require(order&&order->status==OwnedUnitMoveStatus::accepted&&order->ticks==0,"Crushable approach command refused or predicted ticks");
    draw(view,*rt);const auto before=owned_check::snapshot(w);const auto pixels=view.pixels;const int start=rt->tick();
    int previewPositive=0,previewTicks=0;
    const auto preview=w.preview([&](OwnedUnitWorld& copy){
        auto calls=OwnedTerrainRuntime::calls(copy);
        calls[0].driveStore=[&](int off,int value){if(off==0x64&&value==1)++previewPositive;};
        OwnedUnitSchedule schedule(copy,assets.driveData->stopScale);
        while(copy.actor(0).state.destination!=Coord{}&&previewTicks<128)
            schedule.step(start+(++previewTicks),{{assets.speed,assets.speed},{0,0}},calls);
        return copy.actor(0).state.destination==Coord{}&&previewPositive==1;
    });
    require(preview.status==OwnedUnitPreviewStatus::accepted&&previewPositive==1,"Discarded approach did not execute positive curve64");
    bool fault=false;
    try{w.preview([&](OwnedUnitWorld& copy){
        auto calls=OwnedTerrainRuntime::calls(copy);
        calls[0].driveStore=[](int off,int value){if(off==0x64&&value==1)throw std::runtime_error("curve64 observer fault");};
        OwnedUnitSchedule schedule(copy,assets.driveData->stopScale);
        for(int n=1;n<=128;++n)schedule.step(start+n,{{assets.speed,assets.speed},{0,0}},calls);
        return false;
    });}catch(const std::runtime_error& e){fault=std::string(e.what())=="curve64 observer fault";}
    require(fault&&owned_check::snapshot(w)==before&&view.pixels==pixels&&rt->tick()==start,
        "Discarded curve64 preview hid a fault or changed selected source state/time/warm pixels");
    draw(view,*rt);require(view.pixels==pixels,"Discarded curve64 preview changed later warm drawing");
    int positive=0;auto calls=OwnedTerrainRuntime::calls(w);
    calls[0].driveStore=[&](int off,int value){if(off==0x64&&value==1)++positive;};
    for(int n=0;n<128&&rt->moving(0);++n){rt->step(calls);if(n%8==0)draw(view,*rt);}
    require(positive==1&&!rt->moving(0)&&rt->tick()-start==previewTicks&&
        w.actor(0).state.movement.actor.position==Coord{86*256+128,102*256+128,416}&&!w.movementTarget(0),
        "Positive curve64 approach did not arrive exactly and clear its target");
    require(w.actor(1).state.movement.actor.position==resident&&w.actor(1).state.route==otherQueue&&
        w.actor(1).state.destination==otherDestination&&w.actor(1).commands==otherCommands&&w.actor(1).turret.desired==otherTurret,
        "Positive curve64 approach changed the other actor's pose/orders/turret");
    draw(view,*rt);const auto refused=owned_check::snapshot(w);const auto warm=view.pixels;const int tick=rt->tick();
    order=rt->move(85,103);
    require(order&&order->status!=OwnedUnitMoveStatus::accepted&&owned_check::snapshot(w)==refused&&rt->tick()==tick,
        "Approach enabled overlay traversal or mutated refused command state");
    bool strict=false;try{(void)w.context().services.wordCell(85,103);}catch(const UnsupportedGroundRoute&){strict=true;}
    draw(view,*rt);require(strict&&view.pixels==warm,"Approach widened strict traversal or changed refused warm drawing");
    std::cout<<"Crushable approach: one curve64=1, exact86,102 arrival in "<<previewTicks
        <<" ticks, independent actor1, discarded clone/fault isolation, warm drawing and overlay traversal refusal PASS (native integration)\n";
}
void neighborGuards(const GameAssets& assets){
    auto rt=ownedTerrainRuntime(assets,OwnedUnitAdvancePolicy::ordinaryScatter);auto& w=rt->world();
    auto& context=w.context();auto& map=*context.map;const auto& svc=context.services;
    const auto* input=map.table[106*512+91];require(input,"Missing retained terrain-refusal Cell");
    auto& cell=map.cells.at(std::size_t(map.slots[106*512+91])).attributes;
    require(cell.overlay==27&&map.resident.overlays.size()>27&&!map.resident.overlays[27].flag1FD,"Changed source overlay fixture");
    const auto before=owned_check::snapshot(w);
    require(bool(svc.ordinaryNeighbor),"Terrain has no distinct preparation-neighbor binding");
    require(svc.ordinaryNeighbor(91,106)==0,"Noncrushable neighbor returned a positive byte");
    require(owned_check::snapshot(w)==before,"Ordinary neighbor query mutated the live world");
    bool refused=false;
    try{(void)svc.wordCell(91,106);}catch(const UnsupportedGroundRoute& e){
        refused=std::string(e.what()).find("Cell (91,106):")!=std::string::npos&&
            std::string(e.what()).find("query=movement")!=std::string::npos;
    }
    require(refused&&owned_check::snapshot(w)==before,"Look-ahead support widened traversal or lost refusal identity");
    // Diagnostic setup only: entered unsupported children keep their guards.
    const int original=cell.overlay;int crushable=-1;
    for(std::size_t i=0;i<map.resident.overlays.size();++i)if(map.resident.overlays[i].flag1FD){crushable=int(i);break;}
    require(crushable>=0,"No crushable guard fixture");
    cell.overlay=crushable;
    require(svc.ordinaryNeighbor(91,106)==map.resident.overlays[crushable].flag1FD,
        "Crushable neighbor did not return the actual overlay byte");
    auto copy=w.clone();cell.overlay=original;
    require(svc.ordinaryNeighbor(91,106)==0&&copy->context().services.ordinaryNeighbor(91,106)!=0,
        "Cloned neighbor callback retained the source map/overlay association");
    for(int overlay:{int(map.resident.overlays.size()),-2}){
        cell.overlay=overlay;refused=false;
        try{svc.ordinaryNeighbor(91,106);}catch(const UnsupportedGroundRoute&){refused=true;}
        require(refused,"Preparation neighbor accepted an invalid overlay");
    }
    cell.overlay=original;
    for(int kind=0;kind<3;++kind){
        const auto tube=cell.input.tube;const auto flags=cell.input.flags;const auto slope=cell.input.slope;
        if(kind==0)cell.input.tube=0;else if(kind==1)cell.input.flags|=0x100u;else cell.input.slope=21;
        refused=false;try{svc.ordinaryNeighbor(91,106);}catch(const UnsupportedGroundRoute&){refused=true;}
        cell.input.tube=tube;cell.input.flags=flags;cell.input.slope=slope;
        require(refused,"Preparation neighbor widened tube/bridge/ramp domain");
    }
    require(owned_check::snapshot(w)==before,"Neighbor guard diagnostics retained setup or gameplay effects");
    std::cout<<"Preparation neighbor: actual Crushable byte and clone-local binding, unchanged strict traversal and invalid/tube/bridge/ramp refusals PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc!=2)return 2;
    GameAssets assets(argv[1],"mp03t4.map");prepareTerrainAssets(assets);prepareStaticScenery(assets);
    neighborGuards(assets);
    crushableApproach(assets);
    preparationEncounter(assets);
    preparationEncounter(assets,200);
    auto rt=ownedTerrainRuntime(assets,OwnedUnitAdvancePolicy::ordinaryScatter);
    auto& w=rt->world();require(w.hasScatter(),"Missing explicit Scatter policy");
    Renderer view(assets,1024,720);view.camera.zoom=2;view.center(w.actor(0).state.movement.actor.position);
    const auto order=[&](int id,int x,int y,bool append=false){
        rt->select(id);const auto at=w.actor(id).state.movement.actor.position;const int tick=rt->tick();
        const auto result=rt->move(x,y,append);
        require(result&&result->status==OwnedUnitMoveStatus::accepted&&result->ticks==0&&
            rt->tick()==tick&&w.actor(id).state.movement.actor.position==at,"Scatter scenario command refused or predicted movement");
    };
    const auto settle=[&](int id){int n=0;while(rt->moving(id)&&++n<=1024){rt->step();if(n%8==0)draw(view,*rt);}
        require(n<=1024&&!rt->moving(id),"Scatter setup failed to arrive");};
    order(1,94,101);settle(1);order(0,91,101);settle(0);order(0,91,102);settle(0);
    order(1,93,104);settle(1);rt->select(0);rt->turnBody(-16384);
    for(int n=0;n<80;++n)rt->step();
    require(w.actor(0).state.movement.body.current(rt->tick())==16384,"Scatter scenario body preparation failed");
    const auto resident=w.actor(1).state.movement.actor.position;
    Coord recoveredDestination{};
    order(0,92,102);order(0,92,103,true);order(0,93,104,true);
    require(w.actor(0).state.route[0]==2&&w.actor(0).state.route[1]==4&&w.actor(0).state.route[2]==3&&
        w.actor(0).state.route[3]==-1,"Scatter scenario lost supplied curve");
    int six=0,dispatch=0,clones=0;
    auto calls=OwnedTerrainRuntime::calls(w);
    calls[0].decision=[&](char kind,int value){if(kind=='D'&&value==6)++six;};
    calls[0].scatter=[&](char group,char kind,auto actor,auto,auto){if(group=='c'&&kind=='S'){
        require(actor==0,"Curve dispatched an actor outside its actual head Cell");++dispatch;}};
    for(int n=0;n<512&&(rt->moving(0)||rt->moving(1));++n){
        rt->step(calls,[&](int actor,bool){
            if(actor!=0||!w.pendingScatterRoute(0))return;
            const auto* target=w.movementTarget(0);require(target,"Scatter route has no Cell target");
            recoveredDestination=w.actor(0).state.destination;
            const auto snapshot=owned_check::snapshot(w);
            auto copy=w.clone();const auto* rebound=copy->movementTarget(0);
            require(rebound&&rebound!=target&&rebound->position==target->position&&
                rebound==copy->context().map->table[std::size_t(rebound->position.y)*512+std::size_t(rebound->position.x)],
                "Scatter clone retained source target identity");
            OwnedUnitOrders(*copy,assets.driveData->stopScale).followScatter(0);
            const auto bound=OwnedTerrainRuntime::calls(*copy);
            copy->process(0,assets.speed,rt->tick(),0,bound[0]);
            require(owned_check::snapshot(w)==snapshot&&w.movementTarget(0)==target&&w.pendingScatterRoute(0)==target,
                "Discarded Scatter clone changed live owners or targets");++clones;
        });
        if(n%8==0)draw(view,*rt);
    }
    if(!six||!dispatch||!clones)std::cerr<<"encounter counts "<<six<<' '<<dispatch<<' '<<clones<<" at "
        <<w.actor(0).state.movement.actor.position.x<<','<<w.actor(0).state.movement.actor.position.y<<" resident "
        <<w.actor(1).state.movement.actor.position.x<<','<<w.actor(1).state.movement.actor.position.y<<'\n';
    require(six&&dispatch&&clones,"No actual native Advance6/Cell Scatter/target clone encountered");
    require(six==1&&dispatch==1&&clones==1,"Queue consumption spuriously requested a new Scatter route");
    require(!rt->moving(0)&&!rt->moving(1)&&w.actor(0).state.movement.actor.position==recoveredDestination&&
        w.actor(1).state.movement.actor.position==resident,"Self-Scatter failed to arrive or displaced the stationary blocker");
    require(!w.movementTarget(0)&&!w.movementTarget(1),"Arrived Scatter retained its original target");
    const auto moved=w.actor(1).state.movement.actor.position;
    order(1,94,104);settle(1);
    require(w.actor(1).state.movement.actor.position!=moved&&w.actor(0).state.movement.actor.position==recoveredDestination,
        "Scatter actors lost independent commands");
    draw(view,*rt);const auto pixels=view.pixels;draw(view,*rt);require(view.pixels==pixels,"Scatter warm draw changed pixels");
    std::cout<<"Owned self-Scatter: "<<six<<" Advance6, "<<dispatch<<" actual member dispatches, "<<clones
        <<" discarded target-rebound clones; mover arrival, unchanged blocker, later independent command, warm drawing PASS"
        <<" (native diagnostic integration; no original interaction or SDL displacement proof)\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
