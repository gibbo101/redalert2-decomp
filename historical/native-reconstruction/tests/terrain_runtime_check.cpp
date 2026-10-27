// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/TerrainRegression.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <fstream>
using namespace ra2;
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){
        for(const std::size_t size:{std::size_t(0),std::size_t(939),std::size_t(940),std::size_t(941)}){
            bool rejected=false;try{(void)readMapRuntimeData(Data(Bytes(size,0)));}catch(const std::exception&){rejected=true;}
            if(!rejected)throw std::runtime_error("Unverified terrain data accepted");
        }
        std::cout<<"Terrain prepared-data size/hash/source refusals: PASS\n";return 0;
    }
    if(argc<2||argc>4)return 2;GameAssets assets(argv[1],"mp03t4.map");prepareTerrainAssets(assets);prepareStaticScenery(assets);
    if(argc==3&&std::string(argv[2])=="--inputs"){
        for(const auto& name:{std::string("rules.ini"),std::string("art.ini"),std::string("temperat.ini"),assets.mapName})std::cout<<name<<' '<<assetSha256(assets.store.require(name))<<'\n';
        const auto& map=*assets.preparedTerrain;for(std::size_t i=0;i<map.tiles.size();++i)if(map.tiles[i].image)std::cout<<lower(map.filenames[i])<<' '<<assetSha256(assets.store.require(map.filenames[i]))<<'\n';return 0;
    }
    if(argc>=3&&std::string(argv[2])=="--projection"){
        Bytes bytes;const auto append=[&](std::uint32_t n){for(unsigned i=0;i<4;++i)bytes.push_back(std::uint8_t(n>>(i*8)));};
        const auto settings=mapLightSettings(assets.map.ambient,assets.map.tint,assets.map.ground,assets.map.level);
        for(const auto& c:assets.map.cells){const auto id=assets.preparedTerrain->slots[std::size_t(c.y)*512+c.x];const auto& record=assets.preparedTerrain->cells.at(std::size_t(id));const auto& cell=record.attributes;const auto& a=cell;const auto& v=a.input;
            for(unsigned n:{std::uint32_t(std::uint16_t(v.position.x))|(std::uint32_t(std::uint16_t(v.position.y))<<16),unsigned(v.tile),unsigned(v.land),unsigned(std::uint16_t(v.tube)),unsigned(v.subTile),unsigned(std::uint8_t(v.level)),unsigned(v.slope),v.flags,unsigned(a.extraHeight),unsigned(a.overlayData),unsigned(v.ice),unsigned(a.passability),record.field30})append(n);
            const auto light=cellLight(assets.renderData,settings,v.position.x,v.position.y,assets.preparedTerrain->lightingLevels.at(std::size_t(id)));
            for(unsigned n:{0u,unsigned(light.scale),unsigned(std::uint16_t(light.sourceIntensity)),unsigned(std::uint16_t(light.ambient)),unsigned(std::uint16_t(light.terrain)),unsigned(std::uint16_t(light.bridge)),unsigned(std::uint16_t(light.tint[0])),unsigned(std::uint16_t(light.tint[1])),unsigned(std::uint16_t(light.tint[2])),unsigned(a.overlay),unsigned(record.wallOwner)})append(n);
        }
        if(argc==4){std::ofstream dump(argv[3],std::ios::binary);dump.write(reinterpret_cast<const char*>(bytes.data()),std::streamsize(bytes.size()));}
        std::cout<<assetSha256(Data(std::move(bytes)))<<'\n';return 0;
    }
    const auto require=[](bool b,const char* m){if(!b)throw std::runtime_error(m);};
    require(assets.preparedTerrain->cells.size()==13515,"Owned prepared map count differs");
    auto sim=terrainSimulation(assets,{86.5,101.5});Renderer view(assets,1024,720);view.center(sim);view.draw(sim);
    require(sim.coordinates().z==416&&view.vehiclePixels>0,"Derived entry height/drawing failed");
    const auto clear=[&](int x,int y,int){return terrainCommandCell(assets,x,y);};
    const auto before=sim.coordinates();const auto beforeRamp=sim.groundState()->ramps.current;
    require(!sim.move({92.5,101.5},[](int,int,int){return false;}),"Blocked route accepted");
    require(!sim.move({-1,0},clear),"Invalid coordinate accepted");
    require(sim.move({92.5,101.5},clear),"Owned crossing order rejected");
    require(sim.coordinates()==before&&sim.tick==0&&sim.groundState()->ramps.current==beforeRamp,"Preview changed the live actor");
    for(int i=0;i<1024&&sim.moving;++i)sim.step();view.draw(sim);
    require(!sim.moving&&sim.tick==78&&sim.coordinates()==Coord{23680,25984,416},"Prepared crossing arrival differs");
    auto blocked=terrainSimulation(assets,{73.5,41.5},16384);const auto blockedBefore=blocked.coordinates();
    const auto* target=assets.preparedTerrain->find(74,41);
    require(target&&assets.preparedTerrain->land[std::size_t(target->input.land)].speed[unsigned(LandSpeed::Track)]==0.f,"Stock blocked target Track speed is not zero");
    require(terrainCommandCell(assets,74,41)&&!assets.clearTerrainCell(74,41),"Stock zero-speed target/domain differs");
    require(!blocked.move({74.5,41.5},clear)&&blocked.status=="MOVEMENT REJECTED / NO DETOUR SEARCH","Stock terrain admission rejection was not exercised");
    require(blocked.coordinates()==blockedBefore&&blocked.tick==0&&!blocked.moving,"Admission rejection changed live actor");
    std::cout<<"Actual terrain admission blocks 73,41 -> 74,41 with host domain guard accepting the target: PASS\n";
    sim.turnBody(8192);for(int i=0;i<32;++i)sim.step();require(!sim.moving&&sim.drive.body.current(sim.tick)==sim.drive.body.desired,"Prepared manual turn did not settle");
    TerrainRegression regression(assets);auto ramp=terrainSimulation(assets,TerrainRegression::rampEntry,16384);view.center(ramp);view.draw(ramp);regression.ramp(ramp,view);
    require(ramp.move(TerrainRegression::rampExit,clear),"Fixed ramp order rejected");
    for(int i=0;i<512&&ramp.moving;++i){ramp.step();view.draw(ramp);regression.ramp(ramp,view);}regression.finishRamp(ramp,view);
    auto stopped=terrainSimulation(assets,TerrainRegression::rampEntry,16384);require(stopped.move(TerrainRegression::rampExit,clear),"Stop test order failed");
    for(int i=0;i<8;++i)stopped.step();stopped.stop();for(int i=0;i<100&&stopped.moving;++i)stopped.step();require(!stopped.moving&&!stopped.drive.navigationTarget,"Terrain stop failed");
    bool refused=false;for(const auto& record:assets.preparedTerrain->cells){const auto& c=record.attributes;if(c.overlay==-1||std::abs(c.input.position.x-86)>10||std::abs(c.input.position.y-101)>10)continue;
        auto unsupported=terrainSimulation(assets,{86.5,101.5});const auto at=unsupported.coordinates();refused=!unsupported.move({c.input.position.x+.5,c.input.position.y+.5},[](int,int,int){return true;});
        require(unsupported.coordinates()==at&&unsupported.tick==0,"Rejected unsupported route mutated actor");if(refused)break;}
    require(refused,"Unsupported terrain route was not rejected safely");
    auto cliff=terrainSimulation(assets,TerrainRegression::cliffEntry,49152);view.center(cliff);view.draw(cliff);regression.cliff(cliff,view);
    const auto screen=view.project(cliff.position.x,cliff.position.y,cliff.drawElevation());const auto picked=terrainPick(assets,view,screen.x,screen.y);
    require(picked&&picked->x==cliff.position.x&&picked->y==cliff.position.y,"Terrain center picking differs");
    std::cout<<"Owned terrain preparation, preview isolation/refusal, crossing/turn/stop, ramp/height/cache and parked cliff: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
