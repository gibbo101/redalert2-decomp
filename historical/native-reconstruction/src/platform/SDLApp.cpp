// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/Renderer.hpp"
#include "platform/FramePacer.hpp"
#include "platform/CrossingScenario.hpp"
#include "platform/TerrainRegression.hpp"
#include "platform/TerrainUnitContext.hpp"
#include "platform/OwnedSdlApp.hpp"
#include "platform/BootCampPreview.hpp"
#include <SDL3/SDL.h>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace {
constexpr int Width=1024,Height=720;
struct SdlQuit { ~SdlQuit(){SDL_Quit();} };
void check(bool ok) {if(!ok) throw std::runtime_error(SDL_GetError());}
struct Options {std::filesystem::path data,directionData,renderData,rasterData,crossingOutput;std::string map="mp03t4.map",render,playerColor="DarkRed";bool smoke=false,timingSmoke=false,lightDemo=false,crossingDemo=false,crossingSmoke=false,crossingLight=false,terrain=false,terrainSmoke=false,parked=false,resident=false,residentSmoke=false,owned=false,ownedSmoke=false,ownedScatterSmoke=false;bool boot=false,bootWalk=false;std::filesystem::path bootOutput;int speed=3,detail=2;};
Options options(int argc,char** argv) {
    Options o;bool mapSet=false;if(const auto* p=std::getenv("RA2_DATA_DIR")) o.data=p;
    for(int i=1;i<argc;++i) {
        const std::string arg=argv[i];
        auto value=[&](){if(++i>=argc) throw std::runtime_error("Missing value for "+arg);return std::string(argv[i]);};
        if(arg=="--raster-data") o.rasterData=value();else if(arg=="--render-data") o.renderData=value();else if(arg=="--direction-data") o.directionData=value();else if(arg=="--data-dir") o.data=value();else if(arg=="--map"){o.map=value();mapSet=true;}else if(arg=="--render") o.render=value();else if(arg=="--smoke-test") o.smoke=true;else if(arg=="--timing-smoke-test") o.timingSmoke=true;
        else if(arg=="--boot-camp-preview")o.boot=true;
        else if(arg=="--boot-camp-walk")o.boot=o.bootWalk=true;
        else if(arg=="--boot-camp-walk-smoke-test"){o.boot=o.bootWalk=true;o.bootOutput=value();}
        else if(arg=="--player-color") o.playerColor=value();
        else if(arg=="--light-demo") o.lightDemo=true;
        else if(arg=="--crossing-demo") o.crossingDemo=true;
        else if(arg=="--crossing-light-demo") o.crossingDemo=o.crossingLight=true;
        else if(arg=="--crossing-light-smoke-test") {o.crossingDemo=o.crossingSmoke=o.crossingLight=true;o.crossingOutput=value();}
        else if(arg=="--crossing-smoke-test") {o.crossingDemo=o.crossingSmoke=true;o.crossingOutput=value();}
        else if(arg=="--terrain-demo")o.terrain=true;
        else if(arg=="--owned-demo")o.terrain=o.owned=true;
        else if(arg=="--owned-smoke-test"){o.terrain=o.owned=o.ownedSmoke=true;o.crossingOutput=value();}
        else if(arg=="--owned-scatter-smoke-test"){o.terrain=o.owned=o.ownedSmoke=o.ownedScatterSmoke=true;o.crossingOutput=value();}
        else if(arg=="--resident-demo")o.terrain=o.resident=true;
        else if(arg=="--resident-smoke-test"){o.terrain=o.resident=o.residentSmoke=true;o.crossingOutput=value();}
        else if(arg=="--parked-cliff-demo")o.terrain=o.parked=true;
        else if(arg=="--terrain-smoke-test"){o.terrain=o.terrainSmoke=o.crossingDemo=o.crossingSmoke=true;o.crossingOutput=value();}
        else if(arg=="--detail") {
            const auto raw=value();std::size_t used=0;o.detail=std::stoi(raw,&used);
            if(used!=raw.size()||o.detail<0||o.detail>2)throw std::runtime_error("Graphics detail must be 0..2");
        }
        else if(arg=="--speed") {
            const auto raw=value();std::size_t used=0;o.speed=std::stoi(raw,&used);
            if(used!=raw.size()) throw std::runtime_error("Game speed must be an integer 0..6");
            (void)ra2::frameDelay(o.speed);
        } else if(arg=="--help") {
            std::cout<<"Red Alert 2 native reconstruction / bounded prototype\n"
              <<"Usage: redalert2-native --data-dir OWNED_INSTALL [--map mp03t4.map]\n"
              <<"       [--speed 0..6] [--render OUTPUT.ppm | --smoke-test | --timing-smoke-test]\n"
              <<"--direction-data / --render-data / --raster-data PATH override prepared files.\n"
              <<"Defaults follow verified GAME.EXE: private/derived (disc), private/derived/ra2-1006 (patch).\n"
              <<"Every prepared file must match that source profile.\n"
              <<"--player-color NAME selects a rules.ini [Colors] scheme (default DarkRed).\n"
              <<"--light-demo places one stock invisible INGALITE near the tank; L toggles it (host demo).\n"
              <<"--crossing-demo stages the supplied 1.006 Rhino/traffic-light crossing; select, then G to move.\n"
              <<"--crossing-smoke-test PRIVATE_OUTPUT_DIR tests actual SDL selection/move and saves native diagnostics.\n"
              <<"--crossing-light-demo adds one stock invisible light; L toggles it (host placement).\n"
              <<"--crossing-light-smoke-test PRIVATE_OUTPUT_DIR also checks moving cell light and reversible toggles.\n"
              <<"--terrain-demo enables prepared terrain, height/tilt/depth and a fixed ramp route; select then G.\n"
              <<"--parked-cliff-demo stages the prepared-height Rhino behind the original cliff.\n"
              <<"--terrain-smoke-test PRIVATE_OUTPUT_DIR tests SDL crossing, ramp and parked cliff.\n"
              <<"--resident-demo stages a mover and an allied inspection-only parked Rhino; select mover then G.\n"
              <<"--resident-smoke-test PRIVATE_OUTPUT_DIR checks two actors, selection isolation, blocked orders and empty movement.\n"
              <<"--owned-demo enables two commandable Rhinos and bounded resident displacement; G moves selected tank +2 cells.\n"
              <<"--owned-smoke-test PRIVATE_OUTPUT_DIR retains the ordinary two-tank movement/drawing regression.\n"
              <<"--owned-scatter-smoke-test PRIVATE_OUTPUT_DIR checks actual SDL resident displacement and Advance6.\n"
              <<"--boot-camp-preview loads original Day 1 terrain/briefing and static GIs; no movement/objective actions yet.\n"
              <<"--boot-camp-walk enables bounded GI walking; startup/route/animation/schedule supplied; objectives pending.\n"
              <<"--boot-camp-walk-smoke-test PRIVATE_DIR tests SDL selection/movement/drawing/arrival.\n"
              <<"--detail 0..2 selects graphics detail, default 2; stock lights require 2.\n"
              <<"RA2_DATA_DIR supplies the data folder when --data-dir is omitted.\n"
              <<"Left click: select. Right click: direct route (up to 23 cells). Ctrl-right click: append waypoint.\n"
              <<"Shift-right click: aim turret. Q/E: body turn. A/D: turret turn. S: stop. Space: pause. H: tank. T: scenery. P: props.\n"
              <<"Arrows: pan. Mouse wheel or +/-: zoom. [ / ]: slower / faster. C: cycle colors. R: reset. Esc: quit.\n"
              <<"Speed defaults to 3; 0 is slowest and 6 is uncapped (original skirmish policy).\n"
              <<"Original assets and recovered drive, timing and destination-bearing routines.\n"
              <<"Rendering, controls and route clearance remain approximate. No audio, combat or pathfinding.\n";std::exit(0);
        } else throw std::runtime_error("Unknown option: "+arg);
    }
    if(o.boot) {
        if(!mapSet)o.map="trn01t.map";
        if(o.terrain||o.lightDemo||o.crossingDemo||o.smoke||o.timingSmoke)throw std::runtime_error("Run Boot Camp preview separately from other modes");
        if(o.map!="trn01t.map"&&o.map!="trn02t.map")throw std::runtime_error("Boot Camp preview requires trn01t.map or trn02t.map");
    }
    if(int(o.smoke)+int(o.timingSmoke)+int(o.crossingSmoke)>1) throw std::runtime_error("Choose one smoke-test mode");
    if(o.crossingDemo&&(o.lightDemo||o.smoke||o.timingSmoke))throw std::runtime_error("Run the crossing scenario separately from other demos/tests");
    if(o.terrain&&(o.smoke||o.timingSmoke||o.lightDemo||o.crossingLight||(o.parked&&o.crossingDemo)))throw std::runtime_error("Run terrain scenarios separately from light/legacy smoke modes");
    if(o.resident&&(o.parked||o.crossingDemo||o.terrainSmoke||o.map!="mp03t4.map"))throw std::runtime_error("Resident scenario requires the stock mp03t4 map and a separate run");
    if(o.owned&&(o.resident||o.parked||o.crossingDemo||o.terrainSmoke||o.smoke||o.timingSmoke||o.lightDemo||o.map!="mp03t4.map"))throw std::runtime_error("Owned scenario requires stock mp03t4 and a separate run");
    if(o.data.empty()) throw std::runtime_error("Supply --data-dir or RA2_DATA_DIR; see README.md for disc import");return o;
}
void mouse(Uint8 button,float x,float y) {SDL_Event e{};e.type=SDL_EVENT_MOUSE_BUTTON_DOWN;e.button.button=button;e.button.x=x;e.button.y=y;check(SDL_PushEvent(&e));}
void key(SDL_Keycode code) {SDL_Event e{};e.type=SDL_EVENT_KEY_DOWN;e.key.key=code;check(SDL_PushEvent(&e));}
void terrainMembership(const ra2::Simulation& sim) {
    const auto* context=dynamic_cast<const ra2::TerrainUnitContext*>(sim.groundContext());
    if(!context||!context->admission||context->services.admit||context->services.reserve)
        throw std::runtime_error("SDL terrain lost its actual owned admission/membership binding");
    int count=0;for(const auto& [id,cell]:context->unit->membership.cells){
        count+=cell.head==0;if(cell.alternateHead!=-1)throw std::runtime_error("SDL terrain entered unsupported alternate list");
    }
    const auto at=sim.coordinates();const int x=at.x/256,y=at.y/256;
    if(count!=1||x<0||x>=512||y<0||y>=512||!context->state.movement.actor.marked74)
        throw std::runtime_error("SDL terrain lost or duplicated the Unit membership");
    const auto slot=std::size_t(y)*512+x;const auto id=context->map->slots.at(slot);
    if(id<0||context->unit->membership.cells.at(1000+id).head!=0)
        throw std::runtime_error("SDL terrain Unit is linked to a different Cell");
}
}
int main(int argc,char** argv) {
    try {
        const auto o=options(argc,argv);ra2::GameAssets assets(o.data,o.map,o.directionData,o.renderData,o.rasterData);if(o.terrain)ra2::prepareTerrainAssets(assets);ra2::prepareStaticScenery(assets);
        if(o.boot)return ra2::runBootCampPreview(assets,o.render,o.bootWalk,o.bootOutput);
        if(o.owned)return ra2::runOwnedSdl(assets,{o.speed,o.detail,o.playerColor,o.render,o.ownedSmoke,o.crossingOutput,o.ownedScatterSmoke});
        std::optional<ra2::CrossingScenario> crossing;if(o.crossingDemo)crossing.emplace(assets);
        const auto spawn=crossing?std::pair{86,101}:o.terrain?(o.parked?std::pair{51,72}:std::pair{65,26}):assets.spawn();
        std::cout<<"Verified engine data: "<<assets.engineDataSource<<"; initial temperate archive registration\n";
        auto initial=[&](){if(o.resident)return ra2::residentTerrainSimulation(assets);if(o.terrain)return ra2::terrainSimulation(assets,{spawn.first+.5,spawn.second+.5},o.parked?49152:crossing?0:16384);return ra2::Simulation({spawn.first+0.5,spawn.second+0.5},assets.cell(spawn.first,spawn.second)->z,assets.rot,assets.speed,assets.driveData,assets.passive);};
        auto sim=initial();ra2::Renderer view(assets,Width,Height,o.playerColor,o.detail);view.center(sim);std::size_t treeCamera=0,propCamera=0;
        int residentSelection=-1;
        const auto withOwnedScene=[&](auto&& fn){
            const auto* c=dynamic_cast<const ra2::TerrainUnitContext*>(sim.groundContext());
            if(!c||!c->parked)throw std::runtime_error("Resident drawing requires its owned actor group");
            ra2::OwnedUnitDrawingMap map(*c->map,*c->unit);
            const std::array<ra2::OwnedUnitDrawActor,2> actors{{{0,c->state,sim.drive.turret},{1,c->parked->state,c->parked->drawingTurret()}}};
            ra2::OwnedUnitDrawScene scene{map,actors,residentSelection};return fn(scene);
        };
        const auto draw=[&]{if(o.resident)withOwnedScene([&](auto& scene){view.drawOwned(sim,scene);});else view.draw(sim);};
        if(crossing)crossing->center(view);else if(o.terrain){view.camera.zoom=2;view.center(sim);}
        if(o.crossingLight)view.addLightDemo(ra2::CrossingScenario::lightX,ra2::CrossingScenario::lightY);
        std::unique_ptr<ra2::CrossingRegression> crossingCheck;
        if(o.crossingSmoke)crossingCheck=std::make_unique<ra2::CrossingRegression>(assets,view,o.crossingOutput);
        std::unique_ptr<ra2::TerrainRegression> terrainCheck;if(o.terrainSmoke)terrainCheck=std::make_unique<ra2::TerrainRegression>(assets,o.crossingOutput);
        int terrainStage=0,stageFrame=0;std::uint16_t terrainBody=0,terrainTurret=0;
        if(o.lightDemo)view.addLightDemo(spawn.first+2,spawn.second);
        if(!o.render.empty()) {sim.selected=true;if(o.resident)residentSelection=0;draw();view.writePpm(o.render);std::cout<<"Saved original-asset preview: "<<o.render<<"\n";return 0;}
        check(SDL_Init(SDL_INIT_VIDEO));SdlQuit cleanup;
        std::unique_ptr<SDL_Window,decltype(&SDL_DestroyWindow)> window(SDL_CreateWindow("Red Alert 2 Native | bounded terrain and Rhino prototype",Width,Height,SDL_WINDOW_RESIZABLE|((o.smoke||o.timingSmoke||o.crossingSmoke||o.residentSmoke)?SDL_WINDOW_HIDDEN:0)),SDL_DestroyWindow);
        check(bool(window));
        std::unique_ptr<SDL_Renderer,decltype(&SDL_DestroyRenderer)> renderer(SDL_CreateRenderer(window.get(),nullptr),SDL_DestroyRenderer);check(bool(renderer));
        check(SDL_SetRenderLogicalPresentation(renderer.get(),Width,Height,SDL_LOGICAL_PRESENTATION_LETTERBOX));
        std::unique_ptr<SDL_Texture,decltype(&SDL_DestroyTexture)> texture(SDL_CreateTexture(renderer.get(),SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,Width,Height),SDL_DestroyTexture);check(bool(texture));
        check(SDL_SetTextureScaleMode(texture.get(),SDL_SCALEMODE_NEAREST));
        auto clear=[&](int x,int y,int z){return o.terrain?ra2::terrainCommandCell(assets,x,y):assets.clearCell(x,y,z);};
        bool running=true;auto last=SDL_GetTicksNS();Uint64 lastRender=0;int frame=0;
        ra2::FramePacer pacer(o.speed);const auto timingStart=last;
        bool selectedViaEvent=false,bodyViaEvent=false,turretViaEvent=false,moveViaEvent=false;
        std::uint16_t expectedTurret=0;bool speedViaEvent=false,pauseViaEvent=false,colorViaEvent=false;
        bool lightViaEvent=!o.lightDemo;
        bool treeViaEvent=assets.scenery.empty(),propViaEvent=false;
        bool legacyPassed=false,waypointViaEvent=false,curveSeen=false,retargetViaEvent=false,heldCommittedCurve=false;
        int residentStage=0,residentFrame=0;std::uint16_t residentBody=0,residentTurret=0;
        std::optional<ra2::Coord> parkedPosition;
        if(o.resident){const auto* c=dynamic_cast<const ra2::TerrainUnitContext*>(sim.groundContext());
            parkedPosition=c->parked->state.movement.actor.position;
            if(o.residentSmoke)std::filesystem::create_directories(o.crossingOutput);
        }
        while(running) {
            if(o.residentSmoke){
                const auto click=[&](ra2::Coord p,Uint8 button){const auto at=view.project(p.x/256.0,p.y/256.0,p.z/104.0);mouse(button,float(at.x),float(at.y));};
                if(residentStage==0){
                    if(residentFrame==0)click(*parkedPosition,SDL_BUTTON_LEFT);
                    if(residentFrame==1){for(auto k:{SDLK_G,SDLK_Q,SDLK_E,SDLK_A,SDLK_D,SDLK_S})key(k);
                        click(ra2::cellCenter(88,101),SDL_BUTTON_RIGHT);}
                    if(residentFrame==2)click(sim.coordinates(),SDL_BUTTON_LEFT);
                    if(residentFrame==3)click(*parkedPosition,SDL_BUTTON_RIGHT);
                    if(residentFrame==4)key(SDLK_G);
                    if(residentFrame==6)key(SDLK_S);
                }else if(residentStage==1&&residentFrame==0){
                    residentBody=std::uint16_t(sim.drive.body.desired-8192);residentTurret=std::uint16_t(sim.drive.turret.desired+8192);
                    key(SDLK_Q);key(SDLK_D);
                }else if(residentStage==2&&residentFrame==0)key(SDLK_G);
            }
            if(o.crossingSmoke&&terrainStage==0){
                if(frame==0){auto p=view.project(sim.position.x,sim.position.y,sim.drawElevation());mouse(SDL_BUTTON_LEFT,float(p.x),float(p.y));}
                if(frame==1){auto p=view.project(crossing->destination.x,crossing->destination.y,sim.drawElevation());mouse(SDL_BUTTON_RIGHT,float(p.x),float(p.y));}
            }
            if(o.terrainSmoke&&terrainStage==1){
                if(stageFrame==0){const auto p=view.project(sim.position.x,sim.position.y,sim.drawElevation());mouse(SDL_BUTTON_LEFT,float(p.x),float(p.y));}
                if(stageFrame==1){ra2::TerrainMapView map(assets.preparedTerrain);const auto to=ra2::TerrainRegression::rampExit;
                    const auto p=view.project(to.x,to.y,map.floor(ra2::cellCenter(69,26))/104.0);mouse(SDL_BUTTON_RIGHT,float(p.x),float(p.y));}
            }
            if(o.terrainSmoke&&terrainStage==3){
                if(stageFrame==0){const auto p=view.project(sim.position.x,sim.position.y,sim.drawElevation());mouse(SDL_BUTTON_LEFT,float(p.x),float(p.y));}
                if(stageFrame==1)key(SDLK_G);
                if(stageFrame==9)key(SDLK_S);
            }
            if(o.terrainSmoke&&terrainStage==4){
                if(stageFrame==0){terrainBody=std::uint16_t(sim.drive.body.desired-8192);key(SDLK_Q);}
                if(stageFrame==1){terrainTurret=std::uint16_t(sim.drive.turret.desired+8192);key(SDLK_D);}
            }
            if(o.terrainSmoke&&terrainStage==5){
                if(stageFrame==0){const auto p=view.project(sim.position.x,sim.position.y,sim.drawElevation());mouse(SDL_BUTTON_LEFT,float(p.x),float(p.y));}
                if(stageFrame==1){ra2::TerrainMapView map(assets.preparedTerrain);const auto to=ra2::TerrainRegression::blockedExit;
                    const auto p=view.project(to.x,to.y,map.floor(ra2::cellCenter(74,41))/104.0);mouse(SDL_BUTTON_RIGHT,float(p.x),float(p.y));}
            }
            if(o.smoke) {
                if(frame==0) {auto p=view.project(sim.position.x,sim.position.y,sim.drawElevation());mouse(SDL_BUTTON_LEFT,float(p.x),float(p.y));}
                if(frame==1) key(SDLK_E);
                if(frame==2) {expectedTurret=std::uint16_t(sim.drive.turret.desired-8192);key(SDLK_A);}
                if(frame==10) key(SDLK_LEFTBRACKET);
                if(frame==5) key(SDLK_C);
                if(o.lightDemo&&(frame==6||frame==7))key(SDLK_L);
                if(frame==11) key(SDLK_RIGHTBRACKET);
                if(frame==12||frame==13) key(SDLK_SPACE);
                if(frame==14)key(SDLK_T);
                if(frame==15)key(SDLK_H);
                if(frame==16)key(SDLK_P);
                if(frame==17)key(SDLK_H);
                if(frame==20) {auto p=view.project(spawn.first+1.5,spawn.second+0.5,sim.elevation);mouse(SDL_BUTTON_RIGHT,float(p.x),float(p.y));}
            }
            if(o.smoke) {
                if(frame==90) key(SDLK_R);
                if(frame==91) {auto p=view.project(sim.position.x,sim.position.y,sim.drawElevation());mouse(SDL_BUTTON_LEFT,float(p.x),float(p.y));}
                if(frame==92) {
                    SDL_SetModState(SDL_KMOD_CTRL);
                    auto first=view.project(spawn.first+0.5,spawn.second-0.5,sim.elevation);
                    auto second=view.project(spawn.first+1.5,spawn.second-0.5,sim.elevation);
                    mouse(SDL_BUTTON_RIGHT,float(first.x),float(first.y));
                    mouse(SDL_BUTTON_RIGHT,float(second.x),float(second.y));
                }
                if(frame==100) {
                    auto target=view.project(spawn.first+1.5,spawn.second-1.5,sim.elevation);
                    mouse(SDL_BUTTON_RIGHT,float(target.x),float(target.y));
                }
            }
            SDL_Event e{};
            while(SDL_PollEvent(&e)) {
                check(SDL_ConvertEventToRenderCoordinates(renderer.get(),&e));
                if(e.type==SDL_EVENT_QUIT) running=false;
                else if(e.type==SDL_EVENT_MOUSE_BUTTON_DOWN) {
                    if(e.button.button==SDL_BUTTON_LEFT){
                        if(o.resident){residentSelection=withOwnedScene([&](auto& scene){return view.hitOwnedActor(scene,e.button.x,e.button.y);});
                            sim.selected=residentSelection==0;
                            sim.status=residentSelection==1?"PARKED ALLIED RHINO / INSPECTION ONLY":residentSelection==0?"MOVER RHINO SELECTED":"NO UNIT SELECTED";
                        }else sim.selected=view.hitTank(sim,e.button.x,e.button.y);
                    }
                    if(sim.selected&&e.button.button==SDL_BUTTON_RIGHT) {
                        auto p=view.unproject(e.button.x,e.button.y,sim.drawElevation());
                        if(o.terrain){const auto picked=ra2::terrainPick(assets,view,e.button.x,e.button.y);if(!picked){sim.status="NO PREPARED CELL AT CURSOR";continue;}p=*picked;}
                        if(SDL_GetModState()&SDL_KMOD_SHIFT) sim.aim(p);
                        else sim.move(p,clear,(SDL_GetModState()&SDL_KMOD_CTRL)!=0);
                    }
                } else if(e.type==SDL_EVENT_MOUSE_WHEEL) view.camera.zoom=std::clamp(view.camera.zoom*std::pow(1.15,e.wheel.y),0.5,4.0);
                else if(e.type==SDL_EVENT_KEY_DOWN&&!e.key.repeat) {
                    const auto k=e.key.key;
                    if(k==SDLK_ESCAPE) running=false;
                    else if(k==SDLK_SPACE) sim.paused=!sim.paused;
                    else if(k==SDLK_LEFTBRACKET) pacer.setSpeed(std::max(0,pacer.speed()-1));
                    else if(k==SDLK_RIGHTBRACKET) pacer.setSpeed(std::min(6,pacer.speed()+1));
                    else if(k==SDLK_H) view.center(sim);
                    else if(k==SDLK_T) view.centerScenery(treeCamera++);
                    else if(k==SDLK_P) {const bool found=view.centerProp(propCamera++);if(o.smoke&&!found)propViaEvent=true;}
                    else if(k==SDLK_L)view.setLightActive(!view.lightActive());
                    else if(k==SDLK_C) {
                        auto color=assets.playerColors.find(view.playerColor());++color;
                        if(color==assets.playerColors.end())color=assets.playerColors.begin();view.setPlayerColor(color->first);
                    }
                    else if(k==SDLK_R) {sim=initial();residentSelection=-1;if(crossing)crossing->center(view);else view.center(sim);pacer.reset();}
                    else if(k==SDLK_EQUALS||k==SDLK_PLUS) view.camera.zoom=std::min(4.0,view.camera.zoom*1.15);
                    else if(k==SDLK_MINUS) view.camera.zoom=std::max(0.5,view.camera.zoom/1.15);
                    else if(sim.selected) {
                        if(k==SDLK_G&&o.resident)sim.move({88.5,101.5},clear);
                        else if(k==SDLK_G&&o.terrain&&(!crossing||terrainStage>0)&&!o.parked)sim.move(ra2::TerrainRegression::rampExit,clear);
                        else if(k==SDLK_G&&crossing)sim.move(crossing->destination,clear);
                        else if(k==SDLK_Q||k==SDLK_E) sim.turnBody(k==SDLK_Q?-8192:8192);
                        else if(k==SDLK_A||k==SDLK_D) sim.turnTurret(k==SDLK_A?-8192:8192);
                        else if(k==SDLK_S) sim.stop();
                    }
                }
            }
            if(o.residentSmoke&&residentStage==0){
                if(residentFrame<=1&&(residentSelection!=1||sim.selected||sim.moving||sim.coordinates().x!=22144||
                    sim.drive.body.desired!=16384||sim.drive.turret.desired!=16384||!sim.drive.route.empty()))
                    throw std::runtime_error("Parked SDL selection silently commanded the mover");
                if(residentFrame==2&&(residentSelection!=0||!sim.selected))throw std::runtime_error("Mover SDL selection failed");
                if(residentFrame==3&&(sim.moving||sim.status!="MOVEMENT REJECTED / NO DETOUR SEARCH"))throw std::runtime_error("SDL occupied-target refusal failed: "+sim.status);
                if(residentFrame==4&&!sim.moving)throw std::runtime_error("SDL resident empty move failed: "+sim.status);
            }
            if(o.crossingSmoke&&terrainStage==0){
                if(frame==0&&!sim.selected)throw std::runtime_error("SDL crossing selection event failed");
                if(frame==1&&(!sim.moving||sim.drive.destination!=ra2::Coord{23680,25984,o.terrain?416:0}))
                    throw std::runtime_error("SDL crossing right-click order failed");
            }
            if(o.terrainSmoke&&terrainStage==1){
                if(stageFrame==0&&!sim.selected)throw std::runtime_error("SDL ramp selection failed");
                if(stageFrame==1&&!sim.moving)throw std::runtime_error("SDL ramp right-click failed: "+sim.status);
            }
            if(o.terrainSmoke&&terrainStage==3){
                if(stageFrame==0&&!sim.selected)throw std::runtime_error("SDL membership selection failed");
                if(stageFrame==1&&!sim.moving)throw std::runtime_error("SDL membership move key failed");
                if(stageFrame==9&&(!sim.drive.route.empty()||sim.drive.navigationTarget))throw std::runtime_error("SDL membership stop key failed");
            }
            if(o.terrainSmoke&&terrainStage==4){
                if(stageFrame==0&&sim.drive.body.desired!=terrainBody)throw std::runtime_error("SDL membership body turn key failed");
                if(stageFrame==1&&(sim.drive.turret.desired!=terrainTurret||!sim.drive.manualTurret))throw std::runtime_error("SDL membership turret key failed");
            }
            if(o.terrainSmoke&&terrainStage==5&&stageFrame==1){
                if(!sim.selected||sim.moving||sim.status!="MOVEMENT REJECTED / NO DETOUR SEARCH"||!sim.drive.route.empty())
                    throw std::runtime_error("SDL actual admission did not reject stock zero-speed terrain: "+sim.status);
            }
            if(o.smoke&&frame==92) SDL_SetModState(SDL_KMOD_NONE);
            if(o.smoke) {
                if(frame==92) waypointViaEvent=sim.drive.route.size()==2&&sim.drive.route[0]==0&&sim.drive.route[1]==2;
                if(frame==100) retargetViaEvent=sim.drive.destination==ra2::cellCenter(spawn.first+1,spawn.second-2);
                if(frame==0) selectedViaEvent=sim.selected;
                if(frame==1) bodyViaEvent=sim.drive.body.desired==8192;
                if(frame==2) turretViaEvent=sim.drive.turret.desired==expectedTurret&&sim.drive.manualTurret;
                if(frame==10) speedViaEvent=pacer.speed()==std::max(0,o.speed-1);
                if(frame==5) colorViaEvent=view.playerColor()!=ra2::lower(o.playerColor);
                if(o.lightDemo&&frame==6)lightViaEvent=!view.lightActive();
                if(o.lightDemo&&frame==7)lightViaEvent&=view.lightActive();
                if(frame==11) speedViaEvent&=pacer.speed()==std::min(6,std::max(0,o.speed-1)+1);
                if(frame==20) moveViaEvent=sim.moving&&sim.drive.navigationTarget.has_value()&&!sim.drive.manualTurret;
            }
            const auto now=SDL_GetTicksNS();
            const double elapsed=std::min(0.1,double(now-last)/1e9);last=now;
            const auto* keys=SDL_GetKeyboardState(nullptr);const double pan=360*elapsed/view.camera.zoom;
            view.camera.x+=(keys[SDL_SCANCODE_RIGHT]-keys[SDL_SCANCODE_LEFT])*pan;
            view.camera.y+=(keys[SDL_SCANCODE_DOWN]-keys[SDL_SCANCODE_UP])*pan;
            // Smoke drives the real scheduler with a deterministic late-host clock.
            const auto milliseconds=(o.smoke||o.crossingSmoke||o.residentSmoke)?std::uint32_t(frame*96):std::uint32_t(now/1000000);
            const auto oldTick=sim.tick;pacer.pause(sim.paused);
            const bool advanced=pacer.ready(milliseconds)&&!(o.crossingSmoke&&(frame==0||(o.terrainSmoke&&terrainStage>0&&stageFrame==0)))&&!(o.residentSmoke&&frame==0);
            if(advanced) {pacer.begin(milliseconds);sim.step();}
            if(o.terrainSmoke)terrainMembership(sim);
            if(o.smoke&&frame==12) pauseViaEvent=sim.paused&&sim.tick==oldTick;
            if(o.smoke&&frame==13) pauseViaEvent&=!sim.paused&&sim.tick==oldTick+1;
            if(o.smoke && frame>=92) {
                curveSeen|=sim.drive.driving&&sim.drive.track>=0&&sim.drive.track/8!=sim.drive.track%8;
                if(frame==105) heldCommittedCurve=sim.drive.track==2&&sim.drive.head==ra2::cellCenter(spawn.first+1,spawn.second-1);
            }
            // Present every update, including uncapped mode. While waiting,
            // refresh the camera/UI at ~16 ms intervals as a host adaptation.
            if(advanced||o.smoke||o.crossingSmoke||o.residentSmoke||frame==0||now-lastRender>=16000000) {
                lastRender=now;
                draw();if(crossingCheck&&terrainStage==0)crossingCheck->sample(sim,view);
                if(o.residentSmoke){
                    const auto* c=dynamic_cast<const ra2::TerrainUnitContext*>(sim.groundContext());
                    if(view.ownedDraws.size()!=2||view.registeredUnits().size()!=2||view.registeredUnits()[0].actor!=0||view.registeredUnits()[1].actor!=1||
                       c->parked->state.movement.actor.position!=*parkedPosition||c->parked->drawingTurret().desired!=32768)
                        throw std::runtime_error("SDL resident drawing lost identity, pose or stationary actor");
                    if(residentStage==0&&residentFrame==1)view.writePpm(o.crossingOutput/"parked-inspection.ppm");
                    if(residentStage==0&&residentFrame==3)view.writePpm(o.crossingOutput/"occupied-refusal.ppm");
                }
                if(terrainCheck&&terrainStage==1)terrainCheck->ramp(sim,view);
                if(terrainCheck&&terrainStage==2)terrainCheck->cliff(sim,view);
                check(SDL_UpdateTexture(texture.get(),nullptr,view.pixels.data(),Width*4));
                check(SDL_SetRenderDrawColor(renderer.get(),0,0,0,255));check(SDL_RenderClear(renderer.get()));check(SDL_RenderTexture(renderer.get(),texture.get(),nullptr,nullptr));
                check(SDL_SetRenderDrawColor(renderer.get(),14,19,23,255));SDL_FRect top{0,0,Width,69},bottom{0,Height-46,Width,46};check(SDL_RenderFillRect(renderer.get(),&top));check(SDL_RenderFillRect(renderer.get(),&bottom));
                check(SDL_SetRenderDrawColor(renderer.get(),226,233,228,255));
                if(o.smoke&&frame==14)treeViaEvent|=view.sceneryPixels>0&&view.sceneryShadowPixels>0;
                if(o.smoke&&frame==16)propViaEvent|=view.propPixels>0&&view.propShadowPixels>0;
                check(SDL_RenderDebugText(renderer.get(),14,12,o.terrain?"RED ALERT 2 NATIVE / PREPARED TERRAIN, LIVE HEIGHT AND RAMP POSE":"RED ALERT 2 NATIVE / RHINO AND SCENERY TRAVERSAL"));
                check(SDL_RenderDebugText(renderer.get(),14,29,o.resident?
                    "Two Rhinos: mover commands / parked inspection only | G moves mover | Routes, picking, camera are host policies":o.terrain?
                    "Terrain demo: select, G crosses ramp, R resets | Direct routes, clearance, picking and camera are host policies":crossing?
                    "CROSSING: select Rhino, G to cross past traffic light, R to reset | Camera, controls and full redraw are host policies":
                    "Recovered ordinary Unit/Terrain traversal | Full actor lifetime, frame scheduling, visibility and UI remain open"));
                check(SDL_RenderDebugText(renderer.get(),14,46,"LMB select | RMB direct move | Ctrl-RMB waypoint | Shift-RMB aim | Q/E body | A/D turret"));
                check(SDL_RenderDebugText(renderer.get(),14,Height-34,sim.status.c_str()));
                std::string info="Speed "+std::to_string(pacer.speed())+"/6"+(pacer.speed()==6?" UNCAPPED":"")+" | C color: "+view.playerColor()+" | [ ] speed | H tank | T scenery | P props | R reset | S stop | Space pause"+(sim.paused?std::string(" [PAUSED]"):std::string());
                info+=" | Detail "+std::to_string(o.detail);
                if(view.hasLight())info+=" | L light: "+std::string(view.lightActive()?"ON":"OFF")+(o.detail<2?" [detail gated]":"");
                check(SDL_RenderDebugText(renderer.get(),14,Height-17,info.c_str()));
                check(SDL_RenderPresent(renderer.get()));++frame;
            }
            if(o.residentSmoke){
                if(residentStage==0&&residentFrame>6&&!sim.moving){
                    if(sim.position.x==88.5)throw std::runtime_error("SDL resident active-track stop did not shorten the route");
                    residentStage=1;residentFrame=-1;
                }else if(residentStage==1&&residentFrame>=40){
                    if(sim.moving||sim.drive.body.current(sim.tick)!=residentBody||sim.drive.turret.current(sim.tick)!=residentTurret)
                        throw std::runtime_error("SDL resident body/turret turns did not settle");
                    residentStage=2;residentFrame=-1;
                }else if(residentStage==2&&residentFrame>1&&!sim.moving){
                    if(sim.position.x!=88.5||sim.position.y!=101.5)throw std::runtime_error("SDL resident empty route did not arrive");
                    view.writePpm(o.crossingOutput/"empty-arrival.ppm");
                    std::ofstream report(o.crossingOutput/"resident-summary.json");
                    report<<"{\n  \"evidence\": \"native SDL injected events; not original gameplay observations\",\n  \"two_distinct_actor_draws_and_registry_ids\": true,\n  \"parked_selection_commands_mover\": false,\n  \"occupied_order_rejected\": true,\n  \"active_track_stop_and_body_turret_turns\": true,\n  \"empty_arrival\": [88.5, 101.5],\n  \"parked_inspection_only\": true\n}\n";
                    if(!report)throw std::runtime_error("Cannot write resident SDL report");
                    std::cout<<"SDL resident two-actor drawing/registry, parked inspection/input isolation, occupied-target refusal, active-track stop, body/turret turns and empty movement: PASS\n";running=false;
                }
                ++residentFrame;if(frame>220)throw std::runtime_error("SDL resident scenario did not finish");
            }
            if(o.crossingSmoke&&terrainStage==0&&frame>1&&!sim.moving){
                crossingCheck->finish(sim,view);std::cout<<"SDL crossing selection, right-click order and presentation: PASS\n";
                if(o.terrainSmoke){terrainStage=1;stageFrame=-1;sim=ra2::terrainSimulation(assets,ra2::TerrainRegression::rampEntry,16384);view.center(sim);pacer.reset();}
                else running=false;
            }else if(o.terrainSmoke&&terrainStage==1&&stageFrame>1&&!sim.moving){
                terrainCheck->finishRamp(sim,view);terrainStage=2;stageFrame=-1;sim=ra2::terrainSimulation(assets,ra2::TerrainRegression::cliffEntry,49152);view.center(sim);pacer.reset();
            }else if(o.terrainSmoke&&terrainStage==2&&stageFrame==0){
                terrainStage=3;stageFrame=-1;sim=ra2::terrainSimulation(assets,ra2::TerrainRegression::rampEntry,16384);view.center(sim);pacer.reset();
            }else if(o.terrainSmoke&&terrainStage==3&&stageFrame>9&&!sim.moving){
                if(sim.position.x==ra2::TerrainRegression::rampExit.x&&sim.position.y==ra2::TerrainRegression::rampExit.y)
                    throw std::runtime_error("SDL stop failed to shorten the route");
                terrainStage=4;stageFrame=-1;
            }else if(o.terrainSmoke&&terrainStage==4&&stageFrame>=40){
                if(sim.moving||sim.drive.body.current(sim.tick)!=terrainBody||sim.drive.turret.current(sim.tick)!=terrainTurret)
                    throw std::runtime_error("SDL membership turns did not settle");
                terrainStage=5;stageFrame=-1;sim=ra2::terrainSimulation(assets,ra2::TerrainRegression::blockedEntry,16384);view.center(sim);pacer.reset();
            }else if(o.terrainSmoke&&terrainStage==5&&stageFrame>=2){
                if(sim.coordinates()!=ra2::Coord{18816,10624,832}||sim.moving)
                    throw std::runtime_error("SDL rejected terrain order moved the actor");
                view.writePpm(o.crossingOutput/"blocked-terrain.ppm");
                std::ofstream report(o.crossingOutput/"admission-summary.json");
                report<<"{\n  \"evidence\": \"native SDL integration only\",\n  \"actual_admission_enabled\": true,\n  \"source\": [73, 41],\n  \"target\": [74, 41],\n  \"order_rejected\": true,\n  \"actor_unchanged\": true\n}\n";
                if(!report)throw std::runtime_error("Cannot write terrain admission report");
                std::cout<<"SDL terrain selection/right-click/G, actual zero-speed admission refusal, active-track stop, body/turret turns, live membership, crossing/ramp and parked cliff: PASS\n";running=false;
            }
            if(o.terrainSmoke)++stageFrame;
            if(o.crossingSmoke&&frame>(o.terrainSmoke?300:200))throw std::runtime_error("SDL crossing did not finish");
            if(o.smoke&&frame==90) {
                if(!selectedViaEvent||!bodyViaEvent||!turretViaEvent||!moveViaEvent||!speedViaEvent||!pauseViaEvent||!colorViaEvent||!lightViaEvent||!treeViaEvent||!propViaEvent||sim.moving||std::abs(sim.position.x-(spawn.first+1.5))>0.001||std::abs(sim.position.y-(spawn.second+0.5))>0.001) throw std::runtime_error("SDL input/movement/light/scenery smoke failed");
                legacyPassed=true;
            }
            if(o.smoke&&frame>=170) {
                if(!legacyPassed||!waypointViaEvent||!curveSeen||!retargetViaEvent||!heldCommittedCurve||sim.moving||
                    std::abs(sim.position.x-(spawn.first+1.5))>0.001||std::abs(sim.position.y-(spawn.second-1.5))>0.001)
                    throw std::runtime_error("SDL curve/waypoint/retarget smoke failed");
                std::cout<<"SDL movement, turret, speed, pause, player color, static light toggle, scenery/prop inspection, curved waypoints and mid-curve retarget: PASS (170 frames)\n";running=false;
            }
            if(o.timingSmoke && now-timingStart>=1000000000) {
                const auto elapsed=(now-timingStart)/1000000;
                const auto quanta=ra2::originalClock(std::uint32_t(now/1000000))-ra2::originalClock(std::uint32_t(timingStart/1000000));
                const int delay=ra2::frameDelay(pacer.speed());
                if(sim.tick<=0||(delay>0&&std::uint32_t(sim.tick)>1+quanta/std::uint32_t(delay)))
                    throw std::runtime_error("Real-clock pacing violated its quantum bound");
                std::cout<<"SDL real-clock speed "<<pacer.speed()<<": "<<sim.tick<<" updates in "<<elapsed<<" ms: PASS\n";
                running=false;
            }
            if(!o.smoke&&!o.crossingSmoke) SDL_Delay(std::min(8u,pacer.sleepHint(std::uint32_t(SDL_GetTicks()))));
        }
    } catch(const std::exception& e) {std::cerr<<"Error: "<<e.what()<<"\n";return 1;}
}
