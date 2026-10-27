// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/CrossingScenario.hpp"
#include "assets/PreparedData.hpp"
#include <algorithm>
#include <iostream>

namespace ra2 {
namespace {
GameAssets withoutScenery(const GameAssets& a){
    auto bare=a;bare.scenery.clear();bare.sceneryImages.clear();prepareStaticScenery(bare);return bare;
}
void require(bool condition,const char* message){if(!condition)throw std::runtime_error(message);}
}
CrossingScenario::CrossingScenario(const GameAssets& a){
    require(a.engineDataSource==PatchedEngineSha&&a.mapName=="mp03t4.map",
            "Crossing scenario requires supplied 1.006 data and mp03t4.map");
    const auto it=std::find_if(a.scenery.begin(),a.scenery.end(),[](const auto& p){
        return p.type=="trff03"&&p.x==89&&p.y==103;
    });
    require(it!=a.scenery.end(),"Crossing scenario traffic light is missing");
    scenery=std::size_t(it-a.scenery.begin());
    const auto* start=a.cell(86,101);const auto* end=a.cell(92,101);
    require(start&&end&&start->z==4&&end->z==4&&a.clearCell(86,101,4)&&a.clearCell(92,101,4),
            "Crossing scenario requires its clear level-ground endpoints");
}
Simulation CrossingScenario::initial(const GameAssets& a) const {
    return Simulation(entry,4,a.rot,a.speed,a.driveData,a.passive);
}
void CrossingScenario::center(Renderer& view) const {view.camera.zoom=2;view.centerScenery(scenery);}
CrossingRegression::CrossingRegression(const GameAssets& a,const Renderer& view,const std::filesystem::path& output)
    :assets_(a),bare_(withoutScenery(a)),baseline_(bare_,view.width,view.height,view.playerColor()),output_(output),lightDemo_(view.hasLight()){
    if(lightDemo_)baseline_.addLightDemo(CrossingScenario::lightX,CrossingScenario::lightY);
    if(!output.empty()){
        std::filesystem::create_directories(output);
        csv_.open(output/"frames.csv");require(bool(csv_),"Cannot create crossing CSV");
        csv_<<"sample,tick,x,y,visible_pixels,without_scenery,hidden_pixels,clears,foot_queries,draws,extras,caller_calls,light_lookups,brightness\n";
    }
}
void CrossingRegression::sample(const Simulation& sim,const Renderer& view){
    require(view.dynamicClears==assets_.scenery.size()+1&&view.footQueries==2&&view.unitDrawCalls==1&&
            view.extrasCalls==1&&view.unitVisible,"Crossing did not use ordinary dynamic traversal and Unit gate");
    require(view.unitCallerCalls==1&&view.unitLightLookups==2,"Crossing did not use complete Unit DrawIt and both light lookups");
    const auto p=unitLightCell(sim.drive.position.x,sim.drive.position.y);const auto* cell=assets_.cell(p.x,p.y);
    require(cell&&view.lastUnitBrightness==view.unitBrightnessAt(*cell),"Caller brightness did not follow current Drive cell");
    minimumBrightness_=std::min(minimumBrightness_,view.lastUnitBrightness);maximumBrightness_=std::max(maximumBrightness_,view.lastUnitBrightness);
    // Only the diagnostic renderer loses scenery. Orders always use the full
    // original map's conservative clearance, including its scenery occupation.
    baseline_.camera=view.camera;baseline_.draw(sim);
    const int hidden=int(baseline_.vehiclePixels)-int(view.vehiclePixels);
    require(baseline_.vehiclePixels>0&&view.vehiclePixels>0&&hidden>=0,"Crossing coverage is invalid");
    if(first_<0){first_=hidden;if(!output_.empty())view.writePpm(output_/"entry.ppm");}
    if(hidden>maximum_){maximum_=hidden;if(!output_.empty())view.writePpm(output_/"occluded.ppm");}
    occluded_+=hidden>0;emerged_|=occluded_>0&&hidden==0;last_=hidden;
    if(csv_)csv_<<samples_<<','<<sim.tick<<','<<sim.drive.position.x<<','<<sim.drive.position.y<<','
        <<view.vehiclePixels<<','<<baseline_.vehiclePixels<<','<<hidden<<','<<view.dynamicClears<<','
        <<view.footQueries<<','<<view.unitDrawCalls<<','<<view.extrasCalls<<','<<view.unitCallerCalls<<','<<view.unitLightLookups<<','<<view.lastUnitBrightness<<'\n';
    ++samples_;
}
void CrossingRegression::finish(const Simulation& sim,Renderer& view){
    require(samples_>=79&&!sim.moving&&sim.drive.position==Coord{23680,25984,sim.groundState()?416:0}&&sim.tick==78,
            "Crossing did not arrive in the retained 78-update native scenario");
    require(first_==0&&last_==0&&maximum_>=30&&occluded_>=3&&emerged_,
            "Crossing did not enter, become occluded and emerge");
    const auto final=view.pixels;const auto camera=view.camera;
    if(!output_.empty())view.writePpm(output_/"exit.ppm");
    Renderer fresh(assets_,view.width,view.height,view.playerColor());fresh.camera=camera;fresh.draw(sim);
    if(lightDemo_){fresh.addLightDemo(CrossingScenario::lightX,CrossingScenario::lightY);fresh.draw(sim);}
    require(fresh.pixels==final,"Moving renderer left a trail compared with fresh final rendering");
    view.draw(sim,true,true,false,false);
    require(view.pixels==final,"Crossing final frame changed with lit/shadow cache bypass");
    const auto builds=view.voxelBuilds,shadows=view.shadowBuilds;
    for(const auto offset:std::array<Point,4>{{{1600,0},{-1600,0},{0,1600},{0,-1600}}}){
        view.camera={camera.x+offset.x,camera.y+offset.y,camera.zoom};view.draw(sim);
        require(!view.unitVisible&&!view.footQueries&&!view.unitDrawCalls&&!view.extrasCalls&&
                !view.vehiclePixels&&!view.shadowPixels&&view.dynamicClears==assets_.scenery.size()+1&&
                view.voxelBuilds==builds&&view.shadowBuilds==shadows,
                "Offscreen traversal drew the Unit or built voxel/shadow images");
    }
    for(double edge:{0.0,double(view.width)}){
        view.camera=camera;
        const auto point=view.project(sim.position.x,sim.position.y,sim.drawElevation());
        view.camera.x+=(point.x-edge)/camera.zoom;view.draw(sim);
        require(view.unitVisible&&view.unitDrawCalls==1&&view.footQueries==2&&view.vehiclePixels>0&&
                view.vehiclePixels<baseline_.vehiclePixels,"Partly clipped Unit did not reach the drawing gate");
        fresh.camera=view.camera;fresh.draw(sim);
        require(fresh.pixels==view.pixels,"Partly clipped Unit differs from a fresh render");
    }
    view.camera=camera;view.draw(sim);require(view.pixels==final,"Pan-away/return did not restore the final scene");
    if(lightDemo_){
        require(maximumBrightness_>minimumBrightness_,"Moving caller did not traverse different current-cell light values");
        const auto lit=view.pixels;const auto brightness=view.lastUnitBrightness;
        const auto litBuilds=view.voxelBuilds,shadowBuilds=view.shadowBuilds;const auto* converter=&view.unitConverter();
        view.setLightActive(false);view.draw(sim);
        require(view.lastUnitBrightness<brightness&&view.pixels!=lit&&view.voxelBuilds==litBuilds&&view.shadowBuilds==shadowBuilds&& &view.unitConverter()==converter,
                "Light toggle failed to change caller brightness while retaining indexed images and house converter");
        view.setLightActive(true);view.draw(sim);
        require(view.pixels==lit&&view.lastUnitBrightness==brightness&&view.voxelBuilds==litBuilds&&view.shadowBuilds==shadowBuilds,
                "Light toggle failed to restore complete drawing without rebuilding indexed images");
    }
    if(!output_.empty()){
        csv_.close();require(!csv_.fail(),"Crossing CSV write failed");
        std::ofstream report(output_/"summary.json");
        report<<"{\n  \"evidence\": \"native integration only\",\n  \"engine_sha256\": \""<<assets_.engineDataSource
              <<"\",\n  \"map\": \"mp03t4.map\",\n  \"scenery\": \"trff03 at 89,103\",\n  \"updates\": "<<sim.tick
              <<",\n  \"samples\": "<<samples_<<",\n  \"maximum_hidden_pixels\": "<<maximum_
              <<",\n  \"occluded_samples\": "<<occluded_<<",\n  \"complete_unit_caller\": true,\n  \"light_lookups_per_draw\": 2,\n  \"light_demo\": "<<(lightDemo_?"true":"false")
              <<",\n  \"minimum_brightness\": "<<minimumBrightness_<<",\n  \"maximum_brightness\": "<<maximumBrightness_
              <<",\n  \"fresh_final_equal\": true,\n  \"offscreen_checks\": 4,\n  \"partial_clip_checks\": 2,\n  \"cache_bypass_equal\": true,\n  \"pan_return_equal\": true\n}\n";
        require(bool(report),"Crossing report write failed");
    }
    std::cout<<"Native crossing: "<<samples_<<" samples / "<<sim.tick<<" updates, "<<maximum_
             <<" maximum hidden pixels / "<<occluded_<<" occluded samples; complete Unit caller, two light lookups, brightness "<<minimumBrightness_<<".."<<maximumBrightness_
             <<"; fresh final, cache bypass, offscreen culling, partial clipping and pan return: PASS\n";
}
}
