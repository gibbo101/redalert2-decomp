// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/TerrainRegression.hpp"
#include <algorithm>
#include <iostream>
namespace ra2 {
namespace {void require(bool b,const char* message){if(!b)throw std::runtime_error(message);}}
TerrainRegression::TerrainRegression(const GameAssets& assets,const std::filesystem::path& output):assets_(assets),output_(output){
    if(!output.empty()){std::filesystem::create_directories(output);csv_.open(output/"ramp.csv");require(bool(csv_),"Cannot write ramp CSV");
        csv_<<"tick,x,y,z,relative_height,stored_ramp,cell_ramp,depth,gradient,visible_pixels\n";}
}
void TerrainRegression::stable(const Simulation& sim,Renderer& view){
    const auto pixels=view.pixels;const auto camera=view.camera;
    view.draw(sim,true,true,false,false);require(view.pixels==pixels,"Terrain cache bypass changed the frame");
    Renderer fresh(assets_,view.width,view.height,view.playerColor());fresh.camera=camera;fresh.draw(sim);
    require(fresh.pixels==pixels,"Terrain fresh frame differs");
    view.camera.x+=1600;view.draw(sim);require(!view.unitVisible&&!view.vehiclePixels,"Terrain offscreen gate drew the Unit");
    view.camera=camera;view.draw(sim);require(view.pixels==pixels,"Terrain pan return changed the frame");
}
void TerrainRegression::ramp(const Simulation& sim,Renderer& view){
    require(sim.groundState()&&view.unitDrawCalls==1&&view.unitCallerCalls==1&&view.vehiclePixels>0,"Terrain ramp did not draw the live Unit");
    tilted_+=view.lastUnitStoredRamp!=0;lag_+=view.lastUnitStoredRamp!=view.lastUnitCellRamp;
    positive_+=view.lastUnitRelativeHeight>0;negative_+=view.lastUnitRelativeHeight<0;
    minimum_=std::min(minimum_,view.lastUnitAbsoluteZ);maximum_=std::max(maximum_,view.lastUnitAbsoluteZ);
    if(csv_)csv_<<sim.tick<<','<<sim.coordinates().x<<','<<sim.coordinates().y<<','<<view.lastUnitAbsoluteZ<<','<<view.lastUnitRelativeHeight<<','<<view.lastUnitStoredRamp<<','<<view.lastUnitCellRamp<<','<<view.lastUnitDepth<<','<<view.lastUnitGradient<<','<<view.vehiclePixels<<'\n';
    if(!output_.empty()&&view.lastUnitStoredRamp!=view.lastUnitCellRamp)view.writePpm(output_/"ramp.ppm");
    // Every live pose is compared, including interpolation and warm-cache frames.
    const auto pixels=view.pixels;view.draw(sim,true,true,false,false);require(view.pixels==pixels,"Moving terrain cache bypass changed pixels");
}
void TerrainRegression::finishRamp(const Simulation& sim,Renderer& view){
    require(!sim.moving&&sim.tick==44&&sim.coordinates().x==17792&&sim.coordinates().y==6784,"Fixed terrain ramp route did not arrive in 44 updates");
    require(tilted_>0&&lag_>0&&positive_>0&&maximum_-minimum_>104,"Fixed ramp route lacks height/tilt/lag coverage");
    stable(sim,view);
    if(csv_){csv_.close();require(!csv_.fail(),"Ramp CSV write failed");}
    if(!output_.empty()){std::ofstream report(output_/"terrain-summary.json");report<<"{\n  \"evidence\": \"native integration only\",\n  \"updates\": "<<sim.tick<<",\n  \"tilted_samples\": "<<tilted_<<",\n  \"ramp_lag_samples\": "<<lag_<<",\n  \"positive_height_samples\": "<<positive_<<",\n  \"negative_height_samples\": "<<negative_<<",\n  \"minimum_z\": "<<minimum_<<",\n  \"maximum_z\": "<<maximum_<<"\n}\n";require(bool(report),"Terrain report write failed");}
    std::cout<<"Native terrain ramp: "<<sim.tick<<" updates, "<<tilted_<<" tilted / "<<lag_<<" ramp-lag / "<<positive_<<" positive-height samples, Z "<<minimum_<<".."<<maximum_<<"; cache bypass/fresh/pan: PASS\n";
}
void TerrainRegression::cliff(const Simulation& sim,Renderer& view){
    require(sim.coordinates().z==416&&view.lastUnitDepth==-52&&view.lastUnitGradient==2&&view.vehiclePixels>0&&view.vehiclePixels<500&&view.terrainRejections>200,"Prepared parked cliff height/depth/occlusion differs");
    if(!output_.empty())view.writePpm(output_/"parked-cliff.ppm");
    stable(sim,view);std::cout<<"Native terrain parked cliff: Z416 / depth -52 / gradient2 / "<<view.vehiclePixels<<" visible / "<<view.terrainRejections<<" rejected; cache bypass/fresh/pan: PASS\n";
}
}
