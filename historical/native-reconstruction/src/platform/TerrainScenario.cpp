// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/TerrainScenario.hpp"
#include "platform/TerrainUnitContext.hpp"
#include "assets/PreparedData.hpp"
#include "assets/UnitMovementRestriction.hpp"
#include "render/RampGeometry.hpp"
#include <cmath>
namespace ra2 {
void prepareTerrainAssets(GameAssets& assets){
    const auto geometry=stockRampGeometry(assets.renderData,assets.rasterData,assets.driveData->directionsToTargets,
        readRampGeometryData(readFile(preparedDataPath(assets.engineDataSource,"ramp-geometry-data.bin")),assets.engineDataSource));
    assets.prepareTerrainMap(geometry.levelHeight,geometry.quadrupleHeight);
}
bool terrainCommandCell(const GameAssets& assets,int x,int y){
    if(!assets.preparedTerrain||assets.occupied.contains({x,y}))return false;
    const auto* c=assets.preparedTerrain->find(x,y);
    if(!c||c->overlay!=-1||c->input.tube!=-1||c->input.slope>20||(c->input.flags&0x100u)||c->input.land<0||c->input.land>=12)return false;
    const double u=(x-y+assets.map.width-1)*.5,v=(x+y-assets.map.width-1)*.5;const auto& b=assets.map.local;
    return u>=b[0]&&v>=b[1]&&u<b[0]+b[2]&&v<b[1]+b[3];
}
std::optional<Position> terrainPick(const GameAssets& assets,const Renderer& renderer,double x,double y){
    if(!assets.preparedTerrain)throw std::invalid_argument("Terrain picking requires prepared Cells");
    TerrainMapView terrain(assets.preparedTerrain);double nearest=30*renderer.camera.zoom;std::optional<Position> result;
    // Host input policy: nearest projected Cell center at its actual center floor.
    // This is not the original tactical picking or an occlusion/selection model.
    for(const auto& c:assets.map.cells){const auto at=cellCenter(c.x,c.y);const auto point=renderer.project(c.x+.5,c.y+.5,terrain.floor(at)/104.0);
        const double distance=std::abs(point.x-x)+2*std::abs(point.y-y);
        if(distance<nearest){nearest=distance;result=Position{c.x+.5,c.y+.5};}}
    return result;
}
static Simulation terrainSimulationImpl(const GameAssets& assets,Position at,int heading,bool resident){
    if(!assets.preparedTerrain)throw std::invalid_argument("Prepare terrain before creating its Unit");
    const auto* cell=assets.cell(int(at.x),int(at.y));if(!cell)throw std::invalid_argument("Terrain Unit outside prepared map");
    Simulation sim(at,cell->z,assets.rot,assets.speed,assets.driveData,assets.passive);sim.drive.body.setCurrent(std::uint16_t(heading),0);
    sim.drive.turret.setCurrent(std::uint16_t(heading),0);
    const auto map=assets.preparedTerrain;
    auto owned=std::make_shared<MutableUnitMap>(map->unitSeed(),map);
    GroundDriveProcessServices services;
    services.advance.notify=[](int){};services.advance.postCell=[]{};
    services.reserve=services.markNext=[](auto,auto){};services.admit=[](const auto&,int,int){};services.noRoute=[]{};
    services.uphill=map->uphill;services.downhill=map->downhill;
    for(unsigned i=0;i<12;++i)services.trackSpeed[i]=map->land[i].speed[unsigned(LandSpeed::Track)];
    services.squareRoot=[&assets](double n){return tableSqrt(assets.renderData,n);};
    GroundDriveProcessState initial;initial.movement.reached5a0=1;
    const Ini rules(assets.store.require("rules.ini").text());
    (void)readUnitMovementRestriction(rules,"HTNK");
    if(!rules.section("HTNK").contains("crusher"))throw std::invalid_argument("Terrain admission requires explicit HTNK Crusher input");
    auto context=std::make_unique<TerrainUnitContext>(std::move(owned),std::move(services),initial);
    if(resident){
        GroundDriveProcessState parked;parked.movement.actor.position=cellCenter(90,101);
        parked.movement.reached5a0=1;parked.movement.body.setRate(assets.rot);
        parked.movement.body.setCurrent(16384,0);
        UnitDiscoveryActor discovery;discovery.owner=0;discovery.mission98=2;
        discovery.queuedA0=-1;discovery.queuedA4=255;
        Facing turret;turret.setRate(assets.rot);turret.setCurrent(32768,0);
        context->bindParked(parked,{},discovery,{},turret);
        auto& p=*context->parked;const auto& services=p.services;
        setActorRelativeHeight(p.state.movement.actor,0,416,services.advance.ground);
        unlimboDriveRamp(p.state.ramps,[&]{(void)services.cell(p.state.movement.actor.position);
            return services.cell(p.state.movement.actor.position).ramp;},0,0);
        services.advance.ground.mark(1);
    }
    context->enableAdmission({rules.boolean("HTNK","Crusher"),0,0,resident});
    sim.enableGround(std::move(context));
    return sim;
}
Simulation terrainSimulation(const GameAssets& assets,Position at,int heading){return terrainSimulationImpl(assets,at,heading,false);}
Simulation residentTerrainSimulation(const GameAssets& assets){return terrainSimulationImpl(assets,{86.5,101.5},16384,true);}
}
