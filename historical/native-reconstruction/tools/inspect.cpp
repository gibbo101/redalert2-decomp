// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/Renderer.hpp"
#include <iostream>
#include <stdexcept>
int main(int argc,char** argv) {
    try {
        if(argc<2) {std::cerr<<"Usage: ra2-inspect DATA_DIR [MAP] [OUTPUT.ppm]\n";return 2;}
        ra2::GameAssets a(argv[1],argc>2?argv[2]:"mp03t4.map");
        std::cout<<"Verified engine data: "<<a.engineDataSource<<"; initial temperate archive registration\n";
        ra2::prepareStaticScenery(a);
        auto spawn=a.spawn();ra2::Simulation sim({spawn.first+0.5,spawn.second+0.5},a.cell(spawn.first,spawn.second)->z,a.rot,a.speed,a.driveData,a.passive);
        auto vox=[](const ra2::VehiclePart& p){std::size_t n=0;for(const auto& s:p.voxels.sections)n+=s.voxels.size();return n;};
        std::cout<<"map="<<a.mapName<<" dimensions="<<a.map.width<<"x"<<a.map.height<<" cells="<<a.map.cells.size()<<" templates="<<a.tiles.size()<<"\n"
          <<"Rhino: body="<<vox(a.body)<<" turret="<<vox(a.turret)<<" barrel="<<vox(a.barrel)<<" voxels; HVA frames="<<a.body.animation.frames<<","<<a.turret.animation.frames<<","<<a.barrel.animation.frames<<"\n"
          <<"Rules: ROT="<<a.rot<<" Speed="<<a.speed<<" (recovered internal Speed="<<ra2::internalSpeed(a.speed)<<")\n"
          <<"spawn="<<spawn.first<<","<<spawn.second<<" elevation="<<sim.elevation<<"\n";
        std::cout<<"Static terrain scenery: "<<a.scenery.size()<<" map placements / "<<a.sceneryImages.size()<<" types (other object types omitted)\n";
        std::size_t marked=0,neighbors=0;for(const auto& [point,c]:a.sceneryLifecycle.occupation.cells){marked+=bool(c.flags&0x1c);neighbors+=c.neighbors;}
        std::cout<<"Recovered scenery lifecycle: "<<a.sceneryLifecycle.occupation.members.size()<<" placed members / "<<marked<<" marked cells / "
                 <<a.sceneryLifecycle.objects.layers[2].count<<" layer registrations / "<<neighbors<<" neighbor contributions; route clearance remains conservative\n";
        if(argc>3) {ra2::Renderer r(a,1024,720);r.center(sim);sim.selected=true;r.draw(sim);r.writePpm(argv[3]);}
        // Native integration: a nearby guaranteed-clear route must reach its exact endpoint.
        auto clear=[&](int x,int y,int z){return a.clearCell(x,y,z);};auto target=sim.position;target.x+=1;
        if(!sim.move(target,clear)) throw std::runtime_error("Integration route rejected");
        for(int i=0;i<200;++i)sim.step();
        if(sim.moving||sim.position.x!=target.x||sim.position.y!=target.y) throw std::runtime_error("Integration movement failed");
        ra2::Simulation curve({spawn.first+0.5,spawn.second+0.5},sim.elevation,a.rot,a.speed,a.driveData,a.passive);
        if(!curve.move({spawn.first+0.5,spawn.second-0.5},clear)||
           !curve.move({spawn.first+1.5,spawn.second-0.5},clear,true)) throw std::runtime_error("Curve waypoint rejected");
        bool sawCurve=false;
        for(int i=0;i<150;++i) {
            curve.step();sawCurve|=curve.drive.track>=0&&curve.drive.track/8!=curve.drive.track%8;
            if(i==8&&argc>3) {ra2::Renderer r(a,1024,720);r.camera.zoom=2.5;r.center(curve);curve.selected=true;r.draw(curve);r.writePpm(std::string(argv[3])+".curve.ppm");}
        }
        if(!sawCurve||curve.moving||curve.drive.position!=ra2::cellCenter(spawn.first+1,spawn.second-1))
            throw std::runtime_error("Curve integration failed");
        std::cout<<"Owned-data load/render, movement and curved-waypoint integration: PASS\n";
    } catch(const std::exception& e) {std::cerr<<"Error: "<<e.what()<<"\n";return 1;}
}
