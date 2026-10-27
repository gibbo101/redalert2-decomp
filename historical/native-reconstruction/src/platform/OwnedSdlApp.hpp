// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "platform/OwnedTerrainRuntime.hpp"
#include "platform/FramePacer.hpp"
#include <SDL3/SDL.h>
#include <fstream>
#include <iostream>
namespace ra2 {
struct OwnedSdlOptions {
    int speed=3,detail=2;
    std::string playerColor="DarkRed",render;
    bool smoke=false;
    std::filesystem::path output;
    bool scatterSmoke=false;
};
inline int runOwnedSdl(GameAssets& assets,const OwnedSdlOptions& options){
    constexpr int width=1024,height=720;
    // Normal play and its Scatter acceptance share this explicit bounded policy.
    // Retain the earlier ordinary-only smoke as a separate regression profile;
    // low-level construction defaults remain guarded.
    const auto makeRuntime=[&]{return ownedTerrainRuntime(assets,options.smoke&&!options.scatterSmoke?
        OwnedUnitAdvancePolicy::ordinaryAdmission:OwnedUnitAdvancePolicy::ordinaryScatter);};
    auto runtime=makeRuntime();
    Renderer view(assets,width,height,options.playerColor,options.detail);
    view.camera.zoom=2;view.center(runtime->world().actor(0).state.movement.actor.position);
    const auto withScene=[&](auto&& f){
        auto& world=runtime->world();const auto& c=world.context();OwnedUnitDrawingMap map(*c.map,*c.unit);
        const std::array<OwnedUnitDrawActor,2> actors{{{0,world.actor(0).state,world.actor(0).turret,&world.movementTargetStorage(0)},{1,world.actor(1).state,world.actor(1).turret,&world.movementTargetStorage(1)}}};
        OwnedUnitDrawScene scene{map,actors,runtime->selected()};return f(scene);
    };
    const auto draw=[&]{withScene([&](auto& scene){view.drawOwned(OwnedUnitDrawFrame{runtime->tick()},scene);});};
    if(!options.render.empty()){draw();view.writePpm(options.render);return 0;}
    const auto check=[](bool value){if(!value)throw std::runtime_error(SDL_GetError());};
    const auto require=[](bool value,const char* message){if(!value)throw std::runtime_error(message);};
    check(SDL_Init(SDL_INIT_VIDEO));struct Quit{~Quit(){SDL_Quit();}} quit;
    std::unique_ptr<SDL_Window,decltype(&SDL_DestroyWindow)> window(SDL_CreateWindow(
        "Red Alert 2 Native | two owned Rhinos",width,height,SDL_WINDOW_RESIZABLE|(options.smoke?SDL_WINDOW_HIDDEN:0)),SDL_DestroyWindow);check(bool(window));
    std::unique_ptr<SDL_Renderer,decltype(&SDL_DestroyRenderer)> renderer(SDL_CreateRenderer(window.get(),nullptr),SDL_DestroyRenderer);check(bool(renderer));
    check(SDL_SetRenderLogicalPresentation(renderer.get(),width,height,SDL_LOGICAL_PRESENTATION_LETTERBOX));
    std::unique_ptr<SDL_Texture,decltype(&SDL_DestroyTexture)> texture(SDL_CreateTexture(renderer.get(),SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,width,height),SDL_DestroyTexture);check(bool(texture));
    check(SDL_SetTextureScaleMode(texture.get(),SDL_SCALEMODE_NEAREST));
    FramePacer pacer(options.speed);std::size_t scenery=0,prop=0;
    bool running=true;auto last=SDL_GetTicksNS();Uint64 lastRender=0;int frame=0;
    // Scripted checks inject real SDL events into this same loop. They are native
    // integration evidence, not observations of the original UI or frame loop.
    struct Action{std::string label;std::function<void()> inject,verify;bool advance=false;};
    std::vector<Action> actions;
    const auto key=[&](SDL_Keycode code){SDL_Event e{};e.type=SDL_EVENT_KEY_DOWN;e.key.key=code;check(SDL_PushEvent(&e));};
    const auto click=[&](Coord p,Uint8 button){const auto at=view.project(p.x/256.0,p.y/256.0,p.z/104.0);
        SDL_Event e{};e.type=SDL_EVENT_MOUSE_BUTTON_DOWN;e.button.button=button;e.button.x=float(at.x);e.button.y=float(at.y);check(SDL_PushEvent(&e));};
    const auto position=[&](int id){return runtime->world().actor(id).state.movement.actor.position;};
    const auto target=[&](int x,int y){TerrainMapView map(assets.preparedTerrain);auto at=cellCenter(x,y);at.z=map.floor(at);return at;};
    const auto selected=[&](int id){return [&,id]{require(runtime->selected()==id,"SDL selected the wrong owned actor");};};
    const auto add=[&](std::string label,std::function<void()> inject={},std::function<void()> verify={},bool advance=false){actions.push_back({std::move(label),std::move(inject),std::move(verify),advance});};
    const auto wait=[&](int n){for(int i=0;i<n;++i)add("advance",{},{},true);};
    std::uint16_t wantedBody=0,wantedTurret=0;Coord stopped{},initial0{},initial1{};
    int pauseTick=0,curveSeven=0;bool curveChecking=false;std::array<Coord,2> sevenPositions{};std::ofstream trace;
    bool residentChecking=false,selfChecking=false,alternatePassed=false,crushableChecking=false,crushablePassed=false;
    int crushableStores=0;
    int residentDispatches=0,counterStores=0,residentPendingDraws=0,residentTargetFrames=0,selfSix=0,selfDispatches=0,selfPendingDraws=0;
    Coord residentStart{},residentDestination{},selfResident{},selfDestination{};
    std::array<Coord,2> refusedPositions{},refusedDestinations{};
    std::array<std::array<int,24>,2> refusedQueues{};
    std::array<OwnedUnitCommands,2> refusedCommands{};
    std::array<const void*,2> refusedTargets{};int refusalTick=0;
    if(options.smoke){
        std::filesystem::create_directories(options.output);trace.open(options.output/"native-sdl.jsonl");require(bool(trace),"Cannot open SDL trace");
        initial0=position(0);initial1=position(1);
    }
    if(options.smoke&&!options.scatterSmoke){
        add("select1",[&]{click(position(1),SDL_BUTTON_LEFT);},selected(1));
        add("turn1",[&]{key(SDLK_Q);key(SDLK_D);},[&]{auto& w=runtime->world();
            require(w.actor(1).state.movement.body.desired==8192&&w.actor(1).turret.desired==40960&&w.actor(0).state.movement.body.desired==16384&&w.actor(0).turret.desired==16384,"SDL actor1 turns aliased actor0");});
        wait(40);
        add("reset",[&]{key(SDLK_R);},[&]{require(runtime->tick()==0&&runtime->selected()==-1&&position(0)==initial0&&position(1)==initial1,"SDL reset kept old world");});
        add("unselected",[&]{for(auto k:{SDLK_G,SDLK_Q,SDLK_E,SDLK_A,SDLK_D,SDLK_S})key(k);click(target(88,101),SDL_BUTTON_RIGHT);},[&]{require(!runtime->moving(0)&&!runtime->moving(1)&&position(0)==initial0,"Unselected SDL commands moved a Unit");});
        add("select0",[&]{click(position(0),SDL_BUTTON_LEFT);},selected(0));
        add("occupied-refusal",[&]{click(position(1),SDL_BUTTON_RIGHT);},[&]{require(!runtime->moving(0)&&position(0)==initial0&&runtime->status!="DIRECT ROUTE ACCEPTED","SDL occupied target accepted");});
        add("move0",[&]{key(SDLK_G);},[&]{require(runtime->moving(0)&&!runtime->moving(1)&&position(0)==initial0,"SDL move0 failed/committed preview state");});
        add("select1",[&]{click(position(1),SDL_BUTTON_LEFT);},selected(1));
        add("future-refusal",[&]{click(target(88,101),SDL_BUTTON_RIGHT);},[&]{require(!runtime->moving(1)&&runtime->moving(0)&&position(1)==initial1,"SDL future occupied order accepted");});
        add("move1",[&]{click(target(92,101),SDL_BUTTON_RIGHT);},[&]{require(runtime->moving(0)&&runtime->moving(1)&&position(1)==initial1,"SDL move1 failed/advanced preview");});
        wait(3);
        add("both-moving",{},[&]{require(runtime->world().actor(0).state.movement.driving&&runtime->world().actor(1).state.movement.driving&&position(0)!=initial0&&position(1)!=initial1,"Both SDL actors did not move concurrently");});
        add("select0",[&]{click(position(0),SDL_BUTTON_LEFT);},selected(0));
        add("deferred-body",[&]{auto a=runtime->world().actor(0);wantedBody=std::uint16_t(a.state.movement.body.desired+8192);wantedTurret=std::uint16_t(a.turret.desired-8192);key(SDLK_E);key(SDLK_A);},[&]{require(runtime->world().actor(0).commands.pendingBodyTurn.has_value(),"SDL moving body turn was not deferred");});
        add("select1",[&]{click(position(1),SDL_BUTTON_LEFT);},selected(1));
        add("stop1",[&]{stopped=position(1);key(SDLK_S);},[&]{require(runtime->world().actor(1).state.movement.driving&&runtime->world().actor(1).state.route.front()==-1&&!runtime->world().actor(1).commands.navigationTarget,"SDL stop discarded committed track");});
        wait(160);
        add("settled",{},[&]{auto& w=runtime->world();require(!runtime->moving(0)&&!runtime->moving(1)&&!w.actor(0).commands.pendingBodyTurn&&w.actor(0).state.movement.body.current(runtime->tick())==wantedBody&&w.actor(0).turret.current(runtime->tick())==wantedTurret&&position(1)!=stopped&&position(1).x<cellCenter(92,101).x,"SDL stop/deferred turns did not settle independently");});
        add("pause",[&]{pauseTick=runtime->tick();key(SDLK_SPACE);},{},true);wait(2);
        add("paused",{},[&]{require(runtime->paused&&runtime->tick()==pauseTick,"SDL pause advanced time");});
        add("resume",[&]{key(SDLK_SPACE);},{},true);
        add("resumed",{},[&]{require(!runtime->paused&&runtime->tick()==pauseTick+1,"SDL resume lost scheduler tick");});
        add("reset",[&]{key(SDLK_R);});
        add("select1",[&]{click(position(1),SDL_BUTTON_LEFT);},selected(1));
        add("replace1",[&]{click(target(91,101),SDL_BUTTON_RIGHT);});
        add("append1",[&]{SDL_SetModState(SDL_KMOD_CTRL);click(target(92,101),SDL_BUTTON_RIGHT);},[&]{auto a=runtime->world().actor(1);require(a.state.route[0]==2&&a.state.route[1]==2&&a.state.destination.x==cellCenter(92,101).x,"SDL append lost actor1 queue");});
        wait(240);
        add("arrived1",{},[&]{require(!runtime->moving(1)&&position(1).x==cellCenter(92,101).x&&position(0)==initial0,"SDL actor1 waypoint arrival failed");});
        add("replace1",[&]{click(target(91,101),SDL_BUTTON_RIGHT);});
        add("retarget1",[&]{click(target(93,101),SDL_BUTTON_RIGHT);},[&]{require(runtime->world().actor(1).state.destination.x==cellCenter(93,101).x,"SDL replacement retained old target");});
        wait(240);
        add("retarget-arrived1",{},[&]{require(!runtime->moving(1)&&position(1).x==cellCenter(93,101).x&&position(0)==initial0,"SDL retarget arrival failed");});
        add("aim1",[&]{SDL_SetModState(SDL_KMOD_SHIFT);click(target(93,103),SDL_BUTTON_RIGHT);},[&]{require(runtime->world().actor(1).commands.manualTurret&&!runtime->moving(1)&&!runtime->world().actor(0).commands.manualTurret,"SDL manual aim selected wrong actor");});
        wait(40);
        add("final-reset",[&]{key(SDLK_R);},[&]{require(runtime->tick()==0&&position(0)==initial0&&position(1)==initial1,"Final SDL reset failed");});
        // Reach the curve from ordinary input: no seeded Drive/head/index or
        // actor/Cell-list edits. These routes/timings remain supplied policies.
        const auto setupMove=[&](int id,int x,int y,int ticks){
            add("curve-select"+std::to_string(id),[&,id]{click(position(id),SDL_BUTTON_LEFT);},selected(id));
            add("curve-setup-move",[&,id,x,y]{stopped=position(id);click(target(x,y),SDL_BUTTON_RIGHT);},[&,id,x,y]{
                require(runtime->status=="DIRECT ROUTE ACCEPTED"&&position(id)==stopped&&runtime->world().actor(id).commands.navigationTarget==target(x,y),"SDL curve setup command refused/advanced preview");});
            wait(ticks);
            add("curve-setup-arrival",{},[&,id,x,y]{require(!runtime->moving(id)&&position(id)==target(x,y),"SDL curve setup arrival failed");});
        };
        setupMove(1,94,101,110);setupMove(0,91,101,137);setupMove(0,91,102,41);
        setupMove(1,93,101,54);setupMove(1,93,105,122);setupMove(1,94,105,41);
        add("curve-body0",[&]{click(position(0),SDL_BUTTON_LEFT);key(SDLK_Q);key(SDLK_Q);},selected(0));
        add("curve-body1",[&]{click(position(1),SDL_BUTTON_LEFT);key(SDLK_Q);key(SDLK_Q);key(SDLK_Q);},selected(1));
        wait(80);
        add("curve-ready",[&]{key(SDLK_H);},[&]{require(runtime->tick()==585&&runtime->world().actor(0).state.movement.body.current(585)==16384&&runtime->world().actor(1).state.movement.body.current(585)==57344,"SDL curve body preparation failed");});
        add("curve-order0",[&]{curveChecking=true;click(position(0),SDL_BUTTON_LEFT);click(target(92,102),SDL_BUTTON_RIGHT);},[&]{require(runtime->selected()==0&&runtime->status=="DIRECT ROUTE ACCEPTED","SDL curve first order refused");});
        add("curve-waypoint0",[&]{SDL_SetModState(SDL_KMOD_CTRL);click(target(93,103),SDL_BUTTON_RIGHT);},[&]{require(runtime->status=="WAYPOINT APPENDED","SDL curve diagonal waypoint refused");});
        add("curve-tail0",[&]{SDL_SetModState(SDL_KMOD_CTRL);click(target(93,105),SDL_BUTTON_RIGHT);},[&]{auto a=runtime->world().actor(0);
            require(runtime->status=="WAYPOINT APPENDED"&&a.state.route[0]==2&&a.state.route[1]==3&&a.state.route[2]==4&&a.state.route[3]==4&&runtime->tick()==585,"SDL curve tail/command-only acceptance failed");});
        wait(14);
        add("curve-order1",[&]{click(position(1),SDL_BUTTON_LEFT);click(target(92,103),SDL_BUTTON_RIGHT);},[&]{require(runtime->selected()==1&&runtime->status=="DIRECT ROUTE ACCEPTED","SDL curve resident order refused");});
        wait(31);
        add("curve-result7",{},[&]{require(curveSeven==1&&runtime->tick()==630,"SDL never reached actual moving-resident Advance7");});
        wait(160);
        add("curve-arrived",{},[&]{require(!runtime->moving(0)&&!runtime->moving(1)&&position(0)==target(93,105)&&position(1)==target(92,103)&&position(0)!=sevenPositions[0]&&position(1)!=sevenPositions[1],"SDL result7 lost later independent movement/arrival");});
        add("curve-reset",[&]{key(SDLK_R);},[&]{require(runtime->tick()==0&&runtime->selected()==-1&&position(0)==initial0&&position(1)==initial1,"SDL curve reset kept state");});
    }
    if(options.scatterSmoke){
        // All setup and later commands use this loop's real input handler. No
        // K/Drive/pose/target/list edits or future-tick command previews.
        const auto setupMove=[&](int id,int x,int y,int ticks){
            add("scatter-select"+std::to_string(id),[&,id]{click(position(id),SDL_BUTTON_LEFT);key(SDLK_H);},selected(id));
            add("scatter-setup-order",[&,id,x,y]{stopped=position(id);click(target(x,y),SDL_BUTTON_RIGHT);},[&,id,x,y]{
                require(runtime->status=="DIRECT ROUTE ACCEPTED"&&position(id)==stopped&&runtime->world().actor(id).commands.navigationTarget==target(x,y),"SDL Scatter setup command refused/advanced time");});
            wait(ticks);
            add("scatter-setup-arrival",{},[&,id,x,y]{require(!runtime->moving(id)&&position(id)==target(x,y),"SDL Scatter setup did not arrive");});
        };
        add("scatter-initial",{},[&]{require(runtime->world().hasScatter(),"SDL Scatter policy missing");});
        setupMove(1,94,101,110);setupMove(0,91,101,137);setupMove(0,91,104,95);setupMove(1,93,104,114);
        add("resident-select0",[&]{click(position(0),SDL_BUTTON_LEFT);key(SDLK_H);},selected(0));
        add("scatter-mask-refusal",[&]{
            refusalTick=runtime->tick();
            for(int id:{0,1}){auto a=runtime->world().actor(id);refusedPositions[id]=position(id);refusedDestinations[id]=a.state.destination;
                refusedQueues[id]=a.state.route;refusedCommands[id]=a.commands;refusedTargets[id]=runtime->world().movementTarget(id);}
            for(int y=99;y<=109;++y)for(int x=87;x<=98;++x){
                if(!assets.preparedTerrain->find(x,y)||terrainCommandCell(assets,x,y))continue;
                const auto p=target(x,y);const auto screen=view.project(p.x/256.,p.y/256.,p.z/104.);
                if(screen.x<0||screen.x>=width||screen.y<69||screen.y>=height-46)continue;
                const auto picked=terrainPick(assets,view,screen.x,screen.y);
                if(picked&&int(picked->x)==x&&int(picked->y)==y){click(p,SDL_BUTTON_RIGHT);return;}
            }
            throw std::runtime_error("SDL Scatter masked-Cell input coverage missing");
        },[&]{require(runtime->status!="DIRECT ROUTE ACCEPTED"&&runtime->tick()==refusalTick,"SDL Scatter mask refused too late");
            for(int id:{0,1}){auto a=runtime->world().actor(id);require(position(id)==refusedPositions[id]&&a.state.destination==refusedDestinations[id]&&
                a.state.route==refusedQueues[id]&&a.commands==refusedCommands[id]&&runtime->world().movementTarget(id)==refusedTargets[id],"SDL refused Scatter command changed either actor");}
        });
        add("resident-order",[&]{residentStart=position(1);stopped=position(0);residentChecking=true;click(target(94,104),SDL_BUTTON_RIGHT);},[&]{
            require(runtime->status=="DIRECT ROUTE ACCEPTED"&&position(0)==stopped&&position(1)==residentStart&&!runtime->moving(1),"SDL occupied-area command refused or moved either actor");});
        wait(320);
        add("resident-arrival",{},[&]{
            require(residentDispatches==1&&counterStores==2&&residentPendingDraws==1&&residentTargetFrames>0,
                "SDL resident dispatch/counter/target-drawing coverage missing");
            require(!runtime->moving(0)&&!runtime->moving(1)&&position(1)==residentDestination&&position(1)!=residentStart&&
                !runtime->world().movementTarget(1),"SDL assigned resident destination without actual arrival/clear");
            residentChecking=false;
        });
        setupMove(0,93,104,120);
        add("vacated-cell",{},[&]{require(position(0)==residentStart&&position(1)==residentDestination,"SDL mover did not enter vacated resident Cell independently");});
        setupMove(1,92,104,120);
        add("displaced-command",{},[&]{require(position(0)==residentStart&&position(1)==target(92,104),"SDL displaced actor lost independent commands");});
        add("scatter-turn",[&]{auto a=runtime->world().actor(1);wantedBody=std::uint16_t(a.state.movement.body.desired-8192);wantedTurret=std::uint16_t(a.turret.desired+8192);key(SDLK_Q);key(SDLK_D);});
        wait(40);
        add("scatter-turn-arrival",{},[&]{auto a=runtime->world().actor(1);require(a.state.movement.body.current(runtime->tick())==wantedBody&&a.turret.current(runtime->tick())==wantedTurret&&position(0)==residentStart,"SDL displaced body/turret command aliased other actor");});
        add("scatter-pause",[&]{pauseTick=runtime->tick();key(SDLK_SPACE);},{},true);wait(2);
        add("scatter-paused",{},[&]{require(runtime->paused&&runtime->tick()==pauseTick,"SDL Scatter pause advanced time");});
        add("scatter-resume",[&]{key(SDLK_SPACE);},{},true);
        add("scatter-reset",[&]{key(SDLK_R);},[&]{require(runtime->world().hasScatter()&&runtime->tick()==0&&runtime->selected()==-1&&position(0)==initial0&&position(1)==initial1,"SDL reset lost Scatter policy or retained actors");});
        // Also reach actual Advance6 through ordinary curved movement. Its
        // late head Cell contains the mover itself, not the candidate's resident.
        setupMove(1,94,101,110);setupMove(0,91,101,137);setupMove(0,91,102,41);setupMove(1,93,104,114);
        add("self-body",[&]{click(position(0),SDL_BUTTON_LEFT);key(SDLK_H);key(SDLK_Q);key(SDLK_Q);},selected(0));
        wait(80);
        add("self-ready",{},[&]{require(runtime->world().actor(0).state.movement.body.current(runtime->tick())==16384,"SDL self-Scatter body setup failed");});
        add("self-order",[&]{selfChecking=true;selfResident=position(1);click(target(92,102),SDL_BUTTON_RIGHT);},[&]{require(runtime->status=="DIRECT ROUTE ACCEPTED","SDL self-Scatter order refused");});
        add("self-waypoint",[&]{SDL_SetModState(SDL_KMOD_CTRL);click(target(92,103),SDL_BUTTON_RIGHT);},[&]{require(runtime->status=="WAYPOINT APPENDED","SDL self-Scatter waypoint refused");});
        add("self-tail",[&]{SDL_SetModState(SDL_KMOD_CTRL);click(target(93,104),SDL_BUTTON_RIGHT);},[&]{const auto& q=runtime->world().actor(0).state.route;
            require(runtime->status=="WAYPOINT APPENDED"&&q[0]==2&&q[1]==4&&q[2]==3&&q[3]==-1,"SDL self-Scatter supplied route differs");});
        wait(320);
        add("self-arrival",{},[&]{require(selfSix==1&&selfDispatches==1&&selfPendingDraws==1&&!runtime->moving(0)&&!runtime->moving(1)&&position(0)==selfDestination&&position(1)==selfResident&&!runtime->world().movementTarget(0),"SDL actual Advance6 self-Scatter/drawing/arrival failed");selfChecking=false;});
        setupMove(1,94,104,120);
        add("self-independent",{},[&]{require(position(0)==selfDestination&&position(1)==target(94,104),"SDL self-Scatter lost later independent commands");});
        add("scatter-final-reset",[&]{key(SDLK_R);},[&]{require(runtime->world().hasScatter()&&runtime->tick()==0&&runtime->selected()==-1&&position(0)==initial0&&position(1)==initial1&&!runtime->world().movementTarget(0)&&!runtime->world().movementTarget(1),"SDL final Scatter reset retained targets/state");});
        // Retain the failed control's four200-tick waits and actual nearby
        // choice. Preparation queries91,106 beyond destination92,105; that
        // noncrushable overlay is a look-ahead, never a traversed Cell.
        setupMove(1,94,101,200);setupMove(0,91,101,200);setupMove(0,91,104,200);setupMove(1,93,104,200);
        add("alternate-select0",[&]{click(position(0),SDL_BUTTON_LEFT);key(SDLK_H);},selected(0));
        add("alternate-order",[&]{residentStart=position(1);residentChecking=true;click(target(94,104),SDL_BUTTON_RIGHT);},[&]{
            require(runtime->tick()==800&&runtime->status=="DIRECT ROUTE ACCEPTED"&&position(1)==residentStart,
                "SDL alternate timing command/setup changed");});
        wait(320);
        add("alternate-arrival",{},[&]{
            require(residentDispatches==2&&counterStores==3&&residentPendingDraws==2&&residentDestination==Coord{23680,27008,416},
                "SDL alternate timing changed original nearby choice or dispatch/counter coverage");
            require(!runtime->moving(0)&&!runtime->moving(1)&&position(1)==residentDestination&&!runtime->world().movementTarget(1),
                "SDL alternate destination failed actual movement/arrival/target clear");
            alternatePassed=true;residentChecking=false;
        });
        setupMove(0,93,104,120);
        add("alternate-vacated",{},[&]{require(position(0)==residentStart&&position(1)==residentDestination,
            "SDL alternate mover failed vacated Cell entry");});
        setupMove(1,92,104,120);
        add("alternate-independent",{},[&]{require(position(0)==residentStart&&position(1)==target(92,104),
            "SDL alternate displaced actor lost independent commands");});
        add("alternate-reset",[&]{key(SDLK_R);},[&]{require(runtime->tick()==0&&runtime->selected()==-1&&position(0)==initial0&&position(1)==initial1,
            "SDL alternate reset retained movement");});
        // The original map has a Crushable overlay at85,103. Approach it from
        //87,101 to86,102 using ordinary input; never traverse the overlay Cell.
        setupMove(0,87,101,120);
        add("crushable-order",[&]{crushableChecking=true;stopped=position(0);click(target(86,102),SDL_BUTTON_RIGHT);},[&]{
            require(runtime->status=="DIRECT ROUTE ACCEPTED"&&runtime->tick()==120&&position(0)==stopped&&position(1)==initial1,
                "SDL Crushable approach command refused or predicted movement");});
        wait(120);
        add("crushable-arrival",{},[&]{
            require(crushableStores==1&&!runtime->moving(0)&&!runtime->moving(1)&&position(0)==target(86,102)&&
                position(1)==initial1&&!runtime->world().movementTarget(0),"SDL positive curve64 approach/arrival/independence failed");
            crushablePassed=true;crushableChecking=false;
        });
        add("crushable-traversal-refusal",[&]{
            refusalTick=runtime->tick();
            for(int id:{0,1}){auto a=runtime->world().actor(id);refusedPositions[id]=position(id);refusedDestinations[id]=a.state.destination;
                refusedQueues[id]=a.state.route;refusedCommands[id]=a.commands;refusedTargets[id]=runtime->world().movementTarget(id);}
            click(target(85,103),SDL_BUTTON_RIGHT);
        },[&]{
            require(runtime->status!="DIRECT ROUTE ACCEPTED"&&runtime->tick()==refusalTick,"SDL accepted overlay traversal or changed time");
            for(int id:{0,1}){auto a=runtime->world().actor(id);require(position(id)==refusedPositions[id]&&a.state.destination==refusedDestinations[id]&&
                a.state.route==refusedQueues[id]&&a.commands==refusedCommands[id]&&runtime->world().movementTarget(id)==refusedTargets[id],
                "SDL overlay traversal refusal changed actor orders/targets/pose");}
        });
        add("crushable-reset",[&]{key(SDLK_R);},[&]{require(runtime->tick()==0&&runtime->selected()==-1&&position(0)==initial0&&position(1)==initial1,
            "SDL Crushable reset retained movement");});
    }
    while(running){
        Action* action=options.smoke?&actions.at(std::size_t(frame)):nullptr;
        if(action&&action->inject)action->inject();
        SDL_Event e{};while(SDL_PollEvent(&e)){
            check(SDL_ConvertEventToRenderCoordinates(renderer.get(),&e));
            if(e.type==SDL_EVENT_QUIT)running=false;
            else if(e.type==SDL_EVENT_MOUSE_BUTTON_DOWN){
                if(e.button.button==SDL_BUTTON_LEFT)runtime->select(withScene([&](auto& scene){return view.hitOwnedActor(scene,e.button.x,e.button.y);}));
                else if(e.button.button==SDL_BUTTON_RIGHT&&runtime->selected()>=0){
                    const auto picked=terrainPick(assets,view,e.button.x,e.button.y);
                    if(!picked){runtime->status="NO PREPARED CELL AT CURSOR";continue;}
                    const int x=int(picked->x),y=int(picked->y);
                    if(SDL_GetModState()&SDL_KMOD_SHIFT)runtime->aim(cellCenter(x,y),*assets.driveData);
                    else (void)runtime->move(x,y,(SDL_GetModState()&SDL_KMOD_CTRL)!=0);
                }
            }else if(e.type==SDL_EVENT_MOUSE_WHEEL)view.camera.zoom=std::clamp(view.camera.zoom*std::pow(1.15,e.wheel.y),.5,4.);
            else if(e.type==SDL_EVENT_KEY_DOWN&&!e.key.repeat){
                const auto k=e.key.key;
                if(k==SDLK_ESCAPE)running=false;
                else if(k==SDLK_R){runtime=makeRuntime();pacer.reset();view.center(position(0));}
                else if(k==SDLK_SPACE)runtime->paused=!runtime->paused;
                else if(k==SDLK_LEFTBRACKET)pacer.setSpeed(std::max(0,pacer.speed()-1));
                else if(k==SDLK_RIGHTBRACKET)pacer.setSpeed(std::min(6,pacer.speed()+1));
                else if(k==SDLK_H)view.center(position(runtime->selected()<0?0:runtime->selected()));
                else if(k==SDLK_T)view.centerScenery(scenery++);
                else if(k==SDLK_P)view.centerProp(prop++);
                else if(k==SDLK_EQUALS||k==SDLK_PLUS)view.camera.zoom=std::min(4.,view.camera.zoom*1.15);
                else if(k==SDLK_MINUS)view.camera.zoom=std::max(.5,view.camera.zoom/1.15);
                else if(k==SDLK_C){auto it=assets.playerColors.find(view.playerColor());if(++it==assets.playerColors.end())it=assets.playerColors.begin();view.setPlayerColor(it->first);}
                else if(k==SDLK_S)runtime->stop();
                else if(k==SDLK_Q||k==SDLK_E)runtime->turnBody(k==SDLK_Q?-8192:8192);
                else if(k==SDLK_A||k==SDLK_D)runtime->turnTurret(k==SDLK_A?-8192:8192);
                else if(k==SDLK_G&&runtime->selected()>=0){const auto at=position(runtime->selected());(void)runtime->move(at.x/256+2,at.y/256);}
            }
        }
        if(action&&action->verify)action->verify();
        if(options.smoke)SDL_SetModState(SDL_KMOD_NONE);
        const auto now=SDL_GetTicksNS();const double elapsed=std::min(.1,double(now-last)/1e9);last=now;
        const auto* keys=SDL_GetKeyboardState(nullptr);const double pan=360*elapsed/view.camera.zoom;
        view.camera.x+=(keys[SDL_SCANCODE_RIGHT]-keys[SDL_SCANCODE_LEFT])*pan;view.camera.y+=(keys[SDL_SCANCODE_DOWN]-keys[SDL_SCANCODE_UP])*pan;
        const auto milliseconds=options.smoke?std::uint32_t(frame*96):std::uint32_t(now/1000000);pacer.pause(runtime->paused);
        const bool advanced=pacer.ready(milliseconds)&&(!action||action->advance);
        if(advanced){
            pacer.begin(milliseconds);
            if(!options.smoke)runtime->step();
            else{
                auto calls=OwnedTerrainRuntime::calls(runtime->world());
                if(options.scatterSmoke)for(int id:{0,1}){
                    calls[std::size_t(id)].driveStore=[&,id](int off,int value){
                        if(!crushableChecking||off!=0x64||value!=1)return;
                        require(id==0,"SDL Crushable curve store changed the wrong actor");++crushableStores;
                        trace<<"{\"event\":\"actual-curve64\",\"tick\":"<<runtime->tick()<<",\"actor\":"<<id<<",\"value\":1}\n";
                    };
                    calls[std::size_t(id)].actorStore=[&,id](int off,int value){
                        if(!residentChecking||off!=0x53c)return;
                        require(id==0&&value==10,"SDL preparation counter changed the wrong owner/value");++counterStores;
                    };
                    calls[std::size_t(id)].scatter=[&,id](char group,char kind,auto actor,auto,auto){
                        if(group!='c'||kind!='S'||(!residentChecking&&!selfChecking))return;
                        require(id==0&&actor==(residentChecking?1:0),"SDL Scatter dispatched outside actual expected Cell membership");
                        if(residentChecking){require(!runtime->moving(1)&&position(1)==residentStart,"SDL resident moved before actual dispatch");++residentDispatches;}
                        else ++selfDispatches;
                        trace<<"{\"event\":\"actual-Cell-Unit-Scatter\",\"tick\":"<<runtime->tick()<<",\"callerActor\":"<<id<<",\"dispatchedActor\":"<<actor<<"}\n";
                    };
                }
                for(int id:{0,1})calls[std::size_t(id)].decision=[&,id](char kind,int result){
                    if(kind=='D'&&result==6&&selfChecking){require(id==0,"SDL Advance6 changed actor identity");++selfSix;
                        trace<<"{\"event\":\"actual-Advance6\",\"tick\":"<<runtime->tick()<<",\"actor\":"<<id<<"}\n";}
                    if(kind!='D'||result!=7||!curveChecking)return;
                    // Read actual consumer-time membership without map/floor
                    // queries or warming fallback/lazy state for telemetry.
                    auto& w=runtime->world();const auto& c=w.context();auto a=w.actor(id);
                    require(a.state.route[0]>=0&&a.state.route[0]<=7,"SDL result7 missing queued target");
                    const auto [dx,dy]=directionOffset(a.state.route[0]);
                    const int x=a.state.movement.head.x/256+dx,y=a.state.movement.head.y/256+dy;
                    require(x>=0&&x<512&&y>=0&&y<512,"SDL result7 target outside map");
                    const int slot=c.map->slots[std::size_t(y)*512+std::size_t(x)];require(slot>=0,"SDL result7 target was fallback");
                    bool resident=false;int count=0;
                    for(int member=c.unit->cellMembership(std::size_t(slot)).head;member!=-1;member=c.unit->membership.actors.at(member).next){
                        require(member>=0&&member<2&&++count<=2,"SDL result7 target list unbound/cyclic");
                        const auto p=position(member);require(p.x/256==x&&p.y/256==y,"SDL result7 resident location/list mismatch");
                        resident|=member==1-id;
                    }
                    require(id==0&&x==93&&y==104&&resident&&w.actor(0).state.movement.driving&&w.actor(1).state.movement.driving,"SDL result7 missing genuine moving target resident");
                    ++curveSeven;sevenPositions={position(0),position(1)};
                    trace<<"{\"event\":\"actual-Advance7\",\"tick\":"<<runtime->tick()<<",\"actor\":"<<id<<",\"targetX\":"<<x<<",\"targetY\":"<<y<<",\"resident\":"<<1-id<<"}\n";
                };
                runtime->step(calls,[&](int actor,bool){
                    if(actor!=0||(!residentChecking&&!selfChecking))return;
                    const int displaced=residentChecking?1:0;
                    const auto* target=runtime->world().pendingScatterRoute(displaced);if(!target)return;
                    require(runtime->world().movementTarget(displaced)==target&&runtime->world().actor(displaced).wait.remaining==8&&runtime->world().actor(displaced).state.retryRemaining==0,
                        "SDL Scatter target/timer owner differs from original-backed setup");
                    const auto destination=runtime->world().actor(displaced).state.destination;
                    // Complete real drawing during the actual target-bearing
                    // Process return, before the supplied route follower runs.
                    draw();require(view.ownedDraws[std::size_t(displaced)].target494&&runtime->world().movementTarget(displaced)==target,
                        "SDL drawing cleared/substituted actual Scatter target");
                    if(residentChecking){++residentPendingDraws;residentDestination=destination;}
                    else{++selfPendingDraws;selfDestination=destination;}
                    const std::string label=residentChecking?"resident-target":"self-target";
                    view.writePpm(options.output/(std::to_string(frame)+"-"+label+".ppm"));
                    trace<<"{\"event\":\""<<label<<"\",\"tick\":"<<runtime->tick()<<",\"actor\":"<<displaced
                         <<",\"x\":"<<destination.x<<",\"y\":"<<destination.y<<",\"z\":"<<destination.z<<"}\n";
                });
            }
        }
        if(advanced||action||frame==0||now-lastRender>=16000000){
            lastRender=now;draw();
            if(action){
                auto& w=runtime->world();const auto& c=w.context();std::array<int,2> counts{};
                for(const auto& [id,cell]:c.unit->membership.cells){(void)id;int n=0;for(int a=cell.head;a!=-1;a=c.unit->membership.actors.at(a).next){require(a>=0&&a<2&&++n<=2,"SDL list unbound/cyclic");++counts[std::size_t(a)];}}
                require(counts==std::array<int,2>{1,1}&&!c.admission,"SDL shared membership missing/duplicated or legacy admission enabled");
                require(view.ownedDraws.size()==2&&view.registeredUnits().size()==2&&view.registeredUnits()[0].actor==0&&view.registeredUnits()[1].actor==1,"SDL draw lost distinct resources/registry");
                for(int id:{0,1}){const auto& d=view.ownedDraws[std::size_t(id)];auto a=w.actor(id);require(d.id==id&&d.location==position(id)&&d.body==a.state.movement.body.current(runtime->tick())&&d.turret==a.turret.current(runtime->tick())&&d.target494==bool(w.movementTarget(id)),"SDL draw used another actor's pose/target");}
                if(residentChecking&&view.ownedDraws[1].target494)++residentTargetFrames;
                trace<<"{\"frame\":"<<frame<<",\"tick\":"<<runtime->tick()<<",\"label\":\""<<action->label<<"\",\"selected\":"<<runtime->selected()<<",\"x0\":"<<position(0).x<<",\"x1\":"<<position(1).x<<",\"draws\":"<<view.ownedDraws.size();
                if(options.scatterSmoke)trace<<",\"y0\":"<<position(0).y<<",\"z0\":"<<position(0).z<<",\"y1\":"<<position(1).y<<",\"z1\":"<<position(1).z<<",\"target0\":"<<bool(w.movementTarget(0))<<",\"target1\":"<<bool(w.movementTarget(1));
                trace<<"}\n";
                if(action->label!="advance")view.writePpm(options.output/(std::to_string(frame)+"-"+action->label+".ppm"));
            }
            check(SDL_UpdateTexture(texture.get(),nullptr,view.pixels.data(),width*4));check(SDL_RenderClear(renderer.get()));check(SDL_RenderTexture(renderer.get(),texture.get(),nullptr,nullptr));
            check(SDL_SetRenderDrawColor(renderer.get(),14,19,23,255));SDL_FRect top{0,0,width,69},bottom{0,height-46,width,46};check(SDL_RenderFillRect(renderer.get(),&top));check(SDL_RenderFillRect(renderer.get(),&bottom));
            check(SDL_SetRenderDrawColor(renderer.get(),226,233,228,255));
            check(SDL_RenderDebugText(renderer.get(),14,12,"RED ALERT 2 NATIVE / TWO OWNED RHINOS / BOUNDED MOVEMENT PROTOTYPE"));
            check(SDL_RenderDebugText(renderer.get(),14,29,"Select either tank | Direct routes, sampled clearance, picking, camera and scheduling are supplied policies"));
            check(SDL_RenderDebugText(renderer.get(),14,46,"LMB select | RMB move | Ctrl-RMB waypoint | Shift-RMB aim | Q/E body | A/D turret | S stop | G +2 cells"));
            check(SDL_RenderDebugText(renderer.get(),14,height-34,runtime->status.c_str()));
            const auto info="tick "+std::to_string(runtime->tick())+" | selected "+std::to_string(runtime->selected())+" | Space pause | R reset | H center | Arrows pan | +/- zoom";
            check(SDL_RenderDebugText(renderer.get(),14,height-17,info.c_str()));check(SDL_RenderPresent(renderer.get()));
        }
        ++frame;
        if(options.smoke&&std::size_t(frame)==actions.size()){
            if(options.scatterSmoke)require(alternatePassed&&crushablePassed&&crushableStores==1&&residentDispatches==2&&residentPendingDraws==2&&selfSix==1&&selfDispatches==1&&selfPendingDraws==1,"SDL Scatter acceptance missing");
            else require(curveSeven==1,"SDL result7 acceptance missing");
            require(view.voxelHits>0&&view.shadowHits>0,"SDL shared warm caches never reused");
            if(options.scatterSmoke){std::cout<<"Owned Scatter SDL: "<<frame<<" frames; both resident timing cases and actual arrival, vacated Cell entry, independent later commands, actual Advance6 self-Scatter, positive Crushable approach and overlay traversal refusal, target-preserving complete drawing, pause/reset and warm caches: PASS (native integration only)\n";return 0;}
            std::cout<<"Owned SDL: "<<frame<<" frames; both selected actors, concurrent movement, stop/deferred body/turret, occupied/future refusal, append/replacement/aim, pause/reset, shared membership/drawing, actual Advance7 curve and later arrival: PASS (native integration only)\n";return 0;
        }
        if(!options.smoke)SDL_Delay(std::min(8u,std::max(1u,pacer.sleepHint(milliseconds))));
    }
    if(options.smoke)throw std::runtime_error("Owned SDL acceptance interrupted before completion");
    return 0;
}
}
