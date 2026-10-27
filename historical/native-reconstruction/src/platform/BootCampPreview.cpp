// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/BootCampPreview.hpp"
#include "platform/BootCampWalkWorld.hpp"
#include "render/OwnedMessagePresentation.hpp"
#include "render/MessageFrame.hpp"
#include "render/GiSpriteDirection.hpp"
#include <fstream>
#include "assets/MissionDefinition.hpp"
#include "assets/StringTable.hpp"
#include "render/Renderer.hpp"
#include "sim/MissionEvent.hpp"
#include <SDL3/SDL.h>
#include <iostream>
#include <cmath>
#include <map>

namespace ra2 {
namespace {
void check(bool ok){if(!ok)throw std::runtime_error(SDL_GetError());}
struct Quit {~Quit(){SDL_Quit();}};
struct WindowDelete {void operator()(SDL_Window* p)const{SDL_DestroyWindow(p);}};
struct RendererDelete {void operator()(SDL_Renderer* p)const{SDL_DestroyRenderer(p);}};
struct TextureDelete {void operator()(SDL_Texture* p)const{SDL_DestroyTexture(p);}};
struct PreviewSprite {std::size_t actor;ShpImage image;Palette palette;int ready,readyStride,walkStart,walkCount,walkStride;};
// Temporary unlit sprite presentation. Walking borrows actual actor placement;
// frame orientation/phase, depth, palette and shadows are not recovered drawing.
void sprite(Renderer& view,const PreviewSprite& sp,const MissionActorDefinition& actor,const GameAssets& assets,const BootCampWalkWorld* world=nullptr,const Palette* currentPalette=nullptr) {
    const auto* cell=assets.cell(actor.x,actor.y);if(!cell)throw std::invalid_argument("Mission infantry outside map");
    Coord position{actor.x*256+128,actor.y*256+128,cell->z*104};
    auto facing=giSpriteDirection(std::uint16_t(std::uint32_t(actor.facing)<<8));
    int index=sp.ready+int(facing)*sp.readyStride;
    if(world){const auto& a=world->actor(int(sp.actor));position=a.ground.position;
        facing=giSpriteDirection(a.body.current(world->tick()));
        index=sp.ready+int(facing)*sp.readyStride;
        if(a.walk.reallyMoving36&&a.walk.head!=Coord{})index=sp.walkStart+facing*sp.walkStride+(world->tick()/2)%sp.walkCount;
    }
    const auto at=view.project(position.x/256.,position.y/256.,position.z/104.);const auto& image=sp.image;const auto& frame=image.frames.at(std::size_t(index));
    const auto left=int(std::lround(at.x+(frame.x-image.width/2)*view.camera.zoom));
    const auto top=int(std::lround(at.y+(frame.y-image.height/2)*view.camera.zoom));
    const int w=int(std::ceil(frame.width*view.camera.zoom)),h=int(std::ceil(frame.height*view.camera.zoom));
    for(int y=std::max(0,top);y<std::min(view.height,top+h);++y)for(int x=std::max(0,left);x<std::min(view.width,left+w);++x) {
        const int sx=std::min(frame.width-1,int((x-left)/view.camera.zoom)),sy=std::min(frame.height-1,int((y-top)/view.camera.zoom));
        const auto index=frame.pixels[std::size_t(sy)*frame.width+sx];if(!index)continue;
        const auto color=(currentPalette?*currentPalette:sp.palette)[index];view.pixels[std::size_t(y)*view.width+x]=0xff000000u|(std::uint32_t(color.r)<<16)|(std::uint32_t(color.g)<<8)|color.b;
    }
}
void text(SDL_Renderer* target,float x,float y,const std::string& value,int columns=105) {
    std::string line;int row=0;
    for(char ch:value) {
        if(ch=='\r')continue;
        if(ch=='\n'||int(line.size())==columns){check(SDL_RenderDebugText(target,x,y+row*10,line.c_str()));line.clear();++row;if(ch=='\n')continue;}
        line+=ch;
    }
    if(!line.empty())check(SDL_RenderDebugText(target,x,y+row*10,line.c_str()));
}
}
int runBootCampPreview(const GameAssets& assets,const std::string& renderPath,bool walking,const std::filesystem::path& smokeOutput) {
    const Ini source(assets.store.require(assets.mapName).text());const auto mission=readMissionDefinition(source);
    const auto strings=readStringTable(assets.store.require("ra2.csf"));const Ini rules(assets.store.require("rules.ini").text()),art(assets.store.require("art.ini").text());
    std::unique_ptr<BootCampWalkWorld> world;if(walking)world=std::make_unique<BootCampWalkWorld>(assets,mission,source,rules,art);
    Renderer view(assets,1024,720,"Gold");view.camera.zoom=2;
    auto home=assets.map.waypoints.find(mission.homeWaypoint);if(home==assets.map.waypoints.end())throw std::invalid_argument("Missing mission HomeCell waypoint");
    auto center=[&]{const auto [x,y]=home->second;const auto* cell=assets.cell(x,y);if(!cell)throw std::invalid_argument("Mission home outside map");view.center({x*256+128,y*256+128,cell->z*104});};center();
    std::vector<PreviewSprite> sprites;
    for(std::size_t i=0;i<mission.actors.size();++i) {
        const auto& actor=mission.actors[i];if(actor.kind!=MissionActorKind::Infantry||lower(actor.type)!="e1")continue;
        const auto image=rules.get(actor.type,"Image",actor.type),sequence=art.get(image,"Sequence");
        const auto ready=integers(art.get(sequence,"Ready"));if(ready.size()<3||ready[0]<0)throw std::invalid_argument("Missing infantry Ready sequence");
        auto shp=readShp(assets.store.require(image+".shp"));if(std::size_t(ready[0])>=shp.frames.size())throw std::invalid_argument("Infantry Ready frame outside image");
        const auto color=source.get(actor.house,"Color");auto palette=assets.unitPalette;
        if(!color.empty())palette=playerPalette(assets.rasterData,palette,assets.playerColors.at(lower(color)));
        const auto walk=integers(art.get(sequence,"Walk"));
        if(ready.size()!=3||ready[1]!=1||ready[2]<=0||walk.size()!=3||walk[0]<0||walk[1]<=0||walk[2]<walk[1]||
           std::size_t(ready[0]+7*ready[2])>=shp.frames.size()||std::size_t(walk[0]+7*walk[2]+walk[1]-1)>=shp.frames.size())
            throw std::invalid_argument("Unsupported GI Ready/Walk frame layout");
        sprites.push_back({i,std::move(shp),std::move(palette),ready[0],ready[2],walk[0],walk[1],walk[2]});
    }
    // Temporary palette presentation still uses original supplied Color inputs,
    // but current-owner lookup must not retain the pre-transfer sprite's House.
    std::map<int,Palette> housePalettes;
    if(world)for(const auto& [id,name]:mission.houses){
        auto palette=assets.unitPalette;const auto color=source.get(name,"Color");
        if(!color.empty())palette=playerPalette(assets.rasterData,palette,assets.playerColors.at(lower(color)));
        housePalettes.emplace(id,std::move(palette));
    }
    int selected=-1;std::string status=walking?"Select the player GI, then RMB for a direct flat route. S stops; Space pauses. Objectives remain pending.":
        "Select the player GI to inspect its original selection event. Movement and objectives are not available yet.";
    const auto position=[&](std::size_t id){const auto& a=mission.actors[id];
        if(world)return world->actor(int(id)).ground.position;
        return Coord{a.x*256+128,a.y*256+128,assets.cell(a.x,a.y)->z*104};};
    const auto project=[&](std::size_t id){const auto p=position(id);return view.project(p.x/256.,p.y/256.,p.z/104.);};
    std::uint32_t messageMilliseconds=0;
    auto draw=[&](OwnedMessagePresentation* diagnostic=nullptr){
        view.drawMap();for(const auto& sp:sprites)sprite(view,sp,mission.actors[sp.actor],assets,world.get(),world?&housePalettes.at(world->actor(int(sp.actor)).object.mission.owner):nullptr);
        if(diagnostic)return composeMessageFrame(*diagnostic,view.pixels,view.width,view.height,4000);
        if(world)return composeMessageFrame(world->missionWorld().messages(),view.pixels,view.width,view.height,messageMilliseconds);
        return MessageFrameResult{};
    };
    draw();
    std::cout<<"Boot Camp content preview: "<<assets.mapName<<"; "<<mission.triggers.size()<<" original triggers, "<<sprites.size()<<(walking?" walking GI records (supplied startup/route/presentation)":" static GI sprites")<<". No mission actions execute.\n";
    if(!renderPath.empty()){view.writePpm(renderPath);return 0;}
    check(SDL_Init(SDL_INIT_VIDEO));Quit quit;
    std::unique_ptr<SDL_Window,WindowDelete> window(SDL_CreateWindow(walking?"Red Alert 2 - Boot Camp walking checkpoint":"Red Alert 2 - Boot Camp content preview",view.width,view.height,0));check(bool(window));
    std::unique_ptr<SDL_Renderer,RendererDelete> target(SDL_CreateRenderer(window.get(),nullptr));check(bool(target));
    std::unique_ptr<SDL_Texture,TextureDelete> texture(SDL_CreateTexture(target.get(),SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,view.width,view.height));check(bool(texture));
    bool running=true,paused=false;auto lastStep=SDL_GetTicks();int smokeStage=0,frames=0,player=-1,pausedTick=0;Coord start{},pausedAt{},savedDestination{},arrival{},stopped{};
    std::unique_ptr<BootCampWalkWorld> diagnosticMessageWorld;
    bool diagnosticMessagePresented=false;MessageFrameResult diagnosticFrame;
    bool eastFacingDrawn=false,westFacingDrawn=false;
    std::array<int,24> savedQueue{};int previewSourceTick=-1,previewProcessCalls=-1,previewDiscoveryCalls=-1;
    for(const auto& sp:sprites)if(world?world->player(int(sp.actor)):lower(mission.actors[sp.actor].house)==lower(mission.player)){player=int(sp.actor);break;}
    if(!smokeOutput.empty()){
        if(!world||player<0)throw std::invalid_argument("Walking SDL check needs a player GI");
        const auto out=std::filesystem::weakly_canonical(smokeOutput),base=std::filesystem::canonical(std::filesystem::current_path());
        const auto relative=out.lexically_relative(base);if(relative.empty()||(*relative.begin()!="private"&&*relative.begin()!="build"))throw std::invalid_argument("SDL receipts must remain private");
        if(std::filesystem::exists(out))throw std::invalid_argument("Use a new private walking SDL output");
        std::filesystem::create_directories(out);start=position(std::size_t(player));view.writePpm((out/"initial.ppm").string());
    }
    const auto pushMouse=[&](Uint8 button,Point p){SDL_Event e{};e.type=SDL_EVENT_MOUSE_BUTTON_DOWN;e.button.button=button;e.button.x=float(p.x);e.button.y=float(p.y);check(SDL_PushEvent(&e));};
    const auto pushKey=[&](SDL_Keycode key){SDL_Event e{};e.type=SDL_EVENT_KEY_DOWN;e.key.key=key;check(SDL_PushEvent(&e));};
    const auto clickCell=[&](int x,int y){const auto* c=assets.cell(x,y);if(!c)throw std::logic_error("SDL smoke Cell missing");pushMouse(SDL_BUTTON_RIGHT,view.project(x+.5,y+.5,c->z));};
    while(running) {
        if(!smokeOutput.empty()){
            if(smokeStage==0){pushMouse(SDL_BUTTON_LEFT,project(std::size_t(player)));smokeStage=1;}
            else if(smokeStage==1&&selected==player){clickCell(start.x/256+2,start.y/256);smokeStage=2;}
            else if(smokeStage==2&&world->actor(player).walk.head!=Coord{}){
                pausedAt=position(std::size_t(player));pausedTick=world->tick();savedDestination=world->actor(player).walk.destination;savedQueue=world->actor(player).route;
                pushKey(SDLK_SPACE);smokeStage=3;
            }else if(smokeStage==3){
                if(!paused||world->tick()!=pausedTick||position(std::size_t(player))!=pausedAt)throw std::runtime_error("SDL pause advanced GI");
                clickCell(start.x/256,start.y/256-2);smokeStage=4;
            }else if(smokeStage==4){
                if(world->tick()!=pausedTick||position(std::size_t(player))!=pausedAt||world->actor(player).walk.destination!=savedDestination||world->actor(player).route!=savedQueue)
                    throw std::runtime_error("SDL refused moving retarget changed GI");
                // Exercise the discarded warm snapshot while ordinary SDL
                // input has paused a real committed head. Live scheduling is
                // deliberately unchanged; only this smoke path invokes it.
                const auto pixels=view.pixels;const auto* backing=view.pixels.data();const auto camera=view.camera;
                const auto visibility=world->visibilityWorld().state();const auto missionState=world->missionWorld().state();
                const auto& messages=world->missionWorld().messages();
                const std::vector<std::uint16_t> messagePixels(messages.pixels().begin(),messages.pixels().end());
                const auto* messageBacking=messages.pixels().data();const auto messageSlots=messages.list().text;const auto messageAvailable=messages.list().available;
                const auto* messageHead=messages.list().head;const auto messageNodes=messages.allocatedNodes();
                const auto messageFont=std::tuple{messages.font().color,messages.font().pitch,messages.font().origin,messages.font().clip,messages.font().clipping};
                const auto messageRequests=std::tuple{messages.sounds().size(),messages.fills().size(),messages.lines().size()};
                previewSourceTick=world->tick();const auto discarded=world->composeUpdatePositionPreview(player);
                previewProcessCalls=discarded.arrivalProcessCalls;previewDiscoveryCalls=discarded.discoveryCalls;
                if(world->tick()!=previewSourceTick||position(std::size_t(player))!=pausedAt||
                   world->actor(player).walk.destination!=savedDestination||world->actor(player).route!=savedQueue||
                   view.pixels!=pixels||view.pixels.data()!=backing||view.camera!=camera||
                   world->visibilityWorld().state().mapQueries!=visibility.mapQueries||
                   world->missionWorld().state().textRequests!=missionState.textRequests||
                   messages.pixels().data()!=messageBacking||!std::equal(messagePixels.begin(),messagePixels.end(),messages.pixels().begin())||
                   messages.list().text!=messageSlots||messages.list().available!=messageAvailable||messages.list().head!=messageHead||messages.allocatedNodes()!=messageNodes||
                   std::tuple{messages.font().color,messages.font().pitch,messages.font().origin,messages.font().clip,messages.font().clipping}!=messageFont||
                   std::tuple{messages.sounds().size(),messages.fills().size(),messages.lines().size()}!=messageRequests||
                   !discarded.arrivalNotifications||discarded.arrivalProcessCalls<1)
                    throw std::runtime_error("Discarded warm SDL arrival preview changed live world or renderer");
                // Explicit presentation diagnostic only. Discovery is injected
                // into an isolated mission clone, never ordinary live gameplay.
                diagnosticMessageWorld=world->clone();auto& diagnostic=diagnosticMessageWorld->missionWorld();
                diagnostic.messages().setMilliseconds(0);
                if(!diagnostic.discoverStructure(1019675)||!diagnostic.messages().list().head||diagnostic.state().textPayload.empty())
                    throw std::runtime_error("Diagnostic mission clone did not produce actual objective text");
                composeMessageFrame(diagnostic.messages(),view.pixels,view.width,view.height,0);
                smokeStage=40;
            }else if(smokeStage==40){
                if(!diagnosticMessagePresented||!diagnosticFrame.glyphStores||!diagnosticFrame.fillStores||
                   world->tick()!=pausedTick||position(std::size_t(player))!=pausedAt||
                   world->missionWorld().state().textRequests||world->missionWorld().messages().list().head)
                    throw std::runtime_error("SDL diagnostic message presentation changed live mission/Walk state");
                diagnosticMessageWorld.reset();pushKey(SDLK_SPACE);smokeStage=5;
            }else if(smokeStage==5&&!world->actor(player).walk.moving34){
                const auto p=position(std::size_t(player));if(p.x/256!=start.x/256+2||p.y/256!=start.y/256)throw std::runtime_error("SDL GI did not reach clicked Cell");
                arrival=p;view.writePpm((smokeOutput/"arrival.ppm").string());clickCell(start.x/256,start.y/256);smokeStage=6;
            }else if(smokeStage==6&&world->actor(player).walk.head!=Coord{}){pushKey(SDLK_S);smokeStage=7;}
            else if(smokeStage==7&&!world->actor(player).walk.moving34){
                stopped=position(std::size_t(player));if(stopped.x/256==start.x/256)throw std::runtime_error("SDL Stop failed to shorten route");
                view.writePpm((smokeOutput/"stopped.ppm").string());clickCell(start.x/256,start.y/256);smokeStage=8;
            }else if(smokeStage==8&&!world->actor(player).walk.moving34){
                const auto p=position(std::size_t(player));if(p.x/256!=start.x/256||p.y/256!=start.y/256)throw std::runtime_error("SDL repeated command missed Cell");
                pushMouse(SDL_BUTTON_LEFT,{20,500});smokeStage=9;
            }else if(smokeStage==9){
                if(selected!=-1)throw std::runtime_error("SDL blank selection retained GI");
                pushMouse(SDL_BUTTON_LEFT,project(std::size_t(player)));smokeStage=10;
            }else if(smokeStage==10&&selected==player){
                clickCell(start.x/256+2,start.y/256-2);smokeStage=11;
            }else if(smokeStage==11&&!world->actor(player).walk.moving34){
                const auto p=position(std::size_t(player));
                if(p.x/256!=start.x/256+2||p.y/256!=start.y/256-2||!eastFacingDrawn)
                    throw std::runtime_error("SDL horizontal rightward movement/drawing missing");
                clickCell(start.x/256,start.y/256);smokeStage=12;
            }else if(smokeStage==12&&!world->actor(player).walk.moving34){
                const auto p=position(std::size_t(player));
                if(p.x/256!=start.x/256||p.y/256!=start.y/256||!westFacingDrawn)
                    throw std::runtime_error("SDL horizontal leftward movement/drawing missing");
                pushMouse(SDL_BUTTON_LEFT,{20,500});smokeStage=13;
            }else if(smokeStage==13){
                if(selected!=-1)throw std::runtime_error("SDL final deselection retained GI");
                std::ofstream receipt(smokeOutput/"report.json");receipt<<"{\n  \"actual_sdl_selection_and_move\": true,\n  \"pause_and_retained_moving_retarget_refusal\": true,\n  \"committed_head_Stop_and_repeated_orders\": true,\n  \"blank_click_deselection\": true,\n  \"horizontal_right_frame6_and_left_frame2_drawn\": true,\n  \"ticks\": "<<world->tick()<<",\n  \"start\": ["<<start.x<<','<<start.y<<','<<start.z<<"],\n  \"arrival\": ["<<arrival.x<<','<<arrival.y<<','<<arrival.z<<"],\n  \"stopped\": ["<<stopped.x<<','<<stopped.y<<','<<stopped.z<<"],\n  \"original_fidelity_from_this_smoke\": false,\n  \"startup_route_presentation_and_schedule_supplied\": true,\n  \"discarded_warm_arrival_preview\": true,\n  \"preview_source_tick\": "<<previewSourceTick<<",\n  \"preview_remaining_process_calls\": "<<previewProcessCalls<<",\n  \"preview_discovery_calls\": "<<previewDiscoveryCalls<<",\n  \"owned_message_preview_isolation\": true,\n  \"visible_objective_text\": false,\n  \"objectives_enabled\": false\n}\n";
                receipt.close();
                // Keep the baseline receipt's visible_objective_text:false as
                // its LIVE-gameplay scope; this separate receipt names exactly
                // what the isolated diagnostic displayed.
                std::ofstream diagnosticReceipt(smokeOutput/"message-presentation.json");
                diagnosticReceipt<<"{\n  \"isolated_mission_clone\": true,\n  \"discovery_injected\": true,\n  \"clock_milliseconds_supplied\": 4000,\n  \"actual_sdl_texture_presented\": "<<std::boolalpha<<diagnosticMessagePresented
                    <<",\n  \"glyph_stores\": "<<diagnosticFrame.glyphStores<<",\n  \"fill_stores\": "<<diagnosticFrame.fillStores
                    <<",\n  \"pixel_stores\": "<<diagnosticFrame.pixelStores<<",\n  \"live_objective_progression\": false,\n  \"original_frame_fidelity\": false\n}\n";
                if(!receipt||!diagnosticReceipt)throw std::runtime_error("Could not write walking SDL receipt");
                std::cout<<"Boot Camp SDL selection/move/drawing/pause/refusal/Stop/repeated order/deselection PASS\n";running=false;
            }
            if(++frames>512)throw std::runtime_error("SDL walking check exceeded frame bound");
        }
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type==SDL_EVENT_QUIT)running=false;
            if(event.type==SDL_EVENT_KEY_DOWN)switch(event.key.key) {
                case SDLK_ESCAPE:running=false;break;
                case SDLK_LEFT:view.camera.x-=40;break;case SDLK_RIGHT:view.camera.x+=40;break;
                case SDLK_UP:view.camera.y-=40;break;case SDLK_DOWN:view.camera.y+=40;break;
                case SDLK_H:center();break;
                case SDLK_SPACE:if(world){paused=!paused;status=paused?"Paused (host schedule).":"Resumed (host schedule).";}break;
                case SDLK_S:if(world&&selected>=0)world->stop(selected,status);break;default:break;
            }
            if(event.type==SDL_EVENT_MOUSE_WHEEL)view.camera.zoom=std::clamp(view.camera.zoom+event.wheel.y*.25,0.5,3.0);
            if(event.type==SDL_EVENT_MOUSE_BUTTON_DOWN&&event.button.button==SDL_BUTTON_RIGHT){
                if(!world)status="Infantry walking is the next integration dependency; this preview issues no move or objective command.";
                else if(selected<0)status="Select the player GI first.";
                else {
                    double nearest=30*view.camera.zoom;const MapCell* chosen=nullptr;
                    for(const auto& c:assets.map.cells){const auto p=view.project(c.x+.5,c.y+.5,c.z);
                        const double distance=std::abs(p.x-event.button.x)+2*std::abs(p.y-event.button.y);
                        if(distance<nearest){nearest=distance;chosen=&c;}}
                    if(chosen)world->move(selected,chosen->x,chosen->y,status);else status="No map Cell under pointer.";
                }
                std::cout<<status<<'\n'<<std::flush;
            }
            if(event.type==SDL_EVENT_MOUSE_BUTTON_DOWN&&event.button.button==SDL_BUTTON_LEFT) {
                selected=-1;
                for(const auto& sp:sprites) {
                    const auto& actor=mission.actors[sp.actor];if(world?!world->player(int(sp.actor)):lower(actor.house)!=lower(mission.player))continue;
                    const auto p=project(sp.actor);
                    if(std::abs(p.x-event.button.x)>14*view.camera.zoom||std::abs(p.y-event.button.y)>18*view.camera.zoom)continue;
                    selected=int(sp.actor);status="Selected "+localizedText(strings,rules.get(actor.type,"UIName"))+". ";
                    if(!mission.tags.contains(actor.tag)){status+="No mission tag.";break;}
                    const auto& trigger=mission.triggers.at(mission.tags.at(actor.tag).trigger);
                    for(const auto& definition:trigger.events)if(definition.kind==33) {
                        const auto result=missionEventOccurred(33,std::stoi(definition.argument),33,0,0,nullptr,{[](auto){}});
                        status+="Selection event "+std::to_string(definition.kind)+(result?" eligible: ":" false: ")+trigger.name+". Actions are pending recovery.";
                    }
                    std::cout<<status<<'\n'<<std::flush;break;
                }
                if(selected<0)status="Select the player GI. Arrows pan, wheel zooms, H returns home, Esc closes.";
            }
        }
        if(world&&!paused&&(!smokeOutput.empty()||SDL_GetTicks()-lastStep>=67)){world->step();lastStep=SDL_GetTicks();}
        messageMilliseconds=std::uint32_t(SDL_GetTicks());
        const auto messageFrame=draw(diagnosticMessageWorld?&diagnosticMessageWorld->missionWorld().messages():nullptr);
        if(!smokeOutput.empty()&&(smokeStage==11||smokeStage==12)&&world->actor(player).walk.reallyMoving36){
            const auto direction=giSpriteDirection(world->actor(player).body.current(world->tick()));
            if(smokeStage==11&&direction==6&&!eastFacingDrawn){view.writePpm((smokeOutput/"walking-right.ppm").string());eastFacingDrawn=true;}
            if(smokeStage==12&&direction==2&&!westFacingDrawn){view.writePpm((smokeOutput/"walking-left.ppm").string());westFacingDrawn=true;}
        }
        if(diagnosticMessageWorld){diagnosticFrame=messageFrame;view.writePpm((smokeOutput/"diagnostic-objective.ppm").string());}
        check(SDL_UpdateTexture(texture.get(),nullptr,view.pixels.data(),view.width*4));check(SDL_RenderTexture(target.get(),texture.get(),nullptr,nullptr));
        // Building/UI stand-ins are not actors, discovery producers or actions.
        check(SDL_SetRenderDrawColor(target.get(),80,150,210,255));
        for(const auto& actor:mission.actors)if(actor.kind==MissionActorKind::Structure) {
            const auto* cell=assets.cell(actor.x,actor.y);if(!cell)continue;
            const auto p=view.project(actor.x+.5,actor.y+.5,cell->z);SDL_FRect box{float(p.x-10),float(p.y-7),20,14};
            check(SDL_RenderRect(target.get(),&box));if(p.x>0&&p.x<view.width-60&&p.y>100&&p.y<view.height-110)text(target.get(),float(p.x+12),float(p.y),actor.type);
        }
        if(selected>=0) {
            const auto p=project(std::size_t(selected));
            check(SDL_SetRenderDrawColor(target.get(),100,255,100,255));SDL_FRect box{float(p.x-18),float(p.y-32),36,44};check(SDL_RenderRect(target.get(),&box));
        }
        check(SDL_SetRenderDrawColor(target.get(),12,18,24,255));SDL_FRect top{0,0,1024,92},bottom{0,642,1024,78};check(SDL_RenderFillRect(target.get(),&top));check(SDL_RenderFillRect(target.get(),&bottom));
        check(SDL_SetRenderDrawColor(target.get(),235,240,245,255));text(target.get(),12,10,diagnosticMessageWorld?"DIAGNOSTIC MISSION CLONE - injected discovery; live objectives remain disabled":walking?"BOOT CAMP WALKING CHECKPOINT - direct routes; objective transitions are pending":"BOOT CAMP CONTENT PREVIEW - tutorial movement and objectives are not available yet");
        text(target.get(),12,28,localizedText(strings,mission.briefing));text(target.get(),12,650,status);
        text(target.get(),12,686,walking?"Supplied startup/route/15Hz schedule; approximate animation/palette/layering. No fog, audio or mission actions.":"Static GI frames and building markers; approximate placement/palette/layering. No fog, audio or mission actions.");
        check(SDL_RenderPresent(target.get()));if(diagnosticMessageWorld)diagnosticMessagePresented=true;SDL_Delay(16);
    }
    return 0;
}
}
