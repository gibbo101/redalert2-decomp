// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/Renderer.hpp"
#include <iostream>
#include <set>
std::uint64_t frameHash(const std::vector<std::uint32_t>& pixels) {
    std::uint64_t h=14695981039346656037ull;for(auto c:pixels){h^=c;h*=1099511628211ull;}return h;
}
int main(int argc,char** argv) {
 try {
    if(argc<2||argc>3){std::cerr<<"Usage: presentation-check OWNED_INSTALL [PREVIEW_PREFIX]\n";return 2;}
    ra2::GameAssets a(argv[1],"mp03t4.map");ra2::prepareStaticScenery(a);auto spawn=a.spawn();
    ra2::Simulation sim({spawn.first+0.5,spawn.second+0.5},a.cell(spawn.first,spawn.second)->z,a.rot,a.speed,a.driveData,a.passive);
    ra2::Renderer r(a,512,360);r.camera.zoom=3;r.center(sim);
    const auto& spawnLight=r.lightingAt(*a.cell(spawn.first,spawn.second));
    if(spawnLight.terrain!=1112||spawnLight.tint!=std::array<int,3>{1000,1000,860})throw std::runtime_error("Supplied map original light inputs regression");
    if(r.unitBrightnessAt(*a.cell(spawn.first,spawn.second))!=1312)throw std::runtime_error("Unit ambient plus ExtraUnitLight regression");
    auto tinted=a;tinted.map.tint={2,0.5,0.2};ra2::Renderer tintTest(tinted,512,360);
    if(tintTest.unitConverter().shades!=r.unitConverter().shades||tintTest.unitBrightnessAt(*a.cell(spawn.first,spawn.second))!=1312)
        throw std::runtime_error("Local map tint entered ordinary house converter or unit brightness");
    r.draw(sim);const auto normalLightFrame=r.pixels;const auto lightTick=sim.tick;const auto lightPosition=sim.drive.position;
    if(r.voxelBuilds!=3||r.voxelHits!=0)throw std::runtime_error("Cold lit part cache did not build three parts");
    r.draw(sim);
    if(r.pixels!=normalLightFrame||r.voxelBuilds!=3||r.voxelHits!=3)throw std::runtime_error("Warm lit part cache did not reuse three parts");
    ra2::Renderer keys(a,512,360);keys.camera=r.camera;keys.draw(sim,true,false);
    const auto startFrame=keys.pixels;
    auto turned=sim;turned.drive.body.setCurrent(8192,turned.tick);
    keys.draw(turned,true,false);
    if(keys.voxelBuilds!=4||keys.voxelHits!=2||keys.pixels==startFrame)throw std::runtime_error("Fixed zero-offset turret/barrel did not reuse across body turn");
    keys.draw(sim,true,false);
    if(keys.voxelBuilds!=4||keys.voxelHits!=5||keys.pixels!=startFrame)throw std::runtime_error("Returning to previous lit key did not restore cached frame");
    keys.draw(sim,true,false,true,false);
    if(keys.voxelBuilds!=7||keys.pixels!=startFrame)throw std::runtime_error("Diagnostic lit cache bypass changed ordinary cold-key output");
    auto disabled=a;disabled.disableVoxelCache=true;ra2::Renderer noCache(disabled,512,360);noCache.camera=r.camera;
    noCache.draw(sim,true,false);noCache.draw(sim,true,false);
    if(noCache.voxelBuilds!=6||noCache.voxelHits||noCache.pixels!=startFrame)throw std::runtime_error("Type DisableVoxelCache did not bypass all three parts");
    std::cout<<"Lit voxel keys: warm repeat, cross-body zero-offset turret reuse, return and disable/bypass: PASS\n";
    auto darker=a;darker.map.ambient=0.35;darker.map.ground=0.2;
    ra2::Renderer dim(darker,512,360);dim.camera=r.camera;dim.draw(sim);
    if(dim.pixels==normalLightFrame||dim.vehiclePixels!=r.vehiclePixels||sim.tick!=lightTick||sim.drive.position!=lightPosition)throw std::runtime_error("Map light rendering or simulation isolation regression");
    if(argc==3)dim.writePpm(std::string(argv[2])+"-dim.ppm");
    bool emittersRejected=false;auto unsupported=a;unsupported.hasPlacedLights=true;
    try{ra2::Renderer rejected(unsupported,512,360);}catch(const std::exception&){emittersRejected=true;}
    if(!emittersRejected)throw std::runtime_error("Unrecovered placed light-source creation accepted");
    std::cout<<"Recovered map light: brightness="<<spawnLight.terrain<<" tint="<<spawnLight.tint[0]<<','<<spawnLight.tint[1]<<','<<spawnLight.tint[2]<<"; darker scene changes colors without changing coverage/simulation: PASS\n";
    ra2::Renderer lamp(a,512,360);lamp.camera=r.camera;lamp.draw(sim);
    const auto unlit=lamp.pixels;const auto coverage=lamp.vehiclePixels;const auto shadowBuilds=lamp.shadowBuilds;
    const auto litBuilds=lamp.voxelBuilds;
    const auto* converter=&lamp.unitConverter();
    lamp.addLightDemo(spawn.first+2,spawn.second);lamp.draw(sim);
    const auto lit=lamp.pixels;const auto updates=lamp.lightUpdates();
    if(&lamp.unitConverter()!=converter||lamp.unitBrightnessAt(*a.cell(spawn.first,spawn.second))!=1491)
        throw std::runtime_error("Light intensity/house converter separation regression");
    bool inside=false,outside=false;
    for(int dx=-27;dx<=26;++dx)if(const auto* c=a.cell(spawn.first+2+dx,spawn.second)) {
        const int brightness=lamp.unitBrightnessAt(*c);const auto& inputs=lamp.lightingAt(*c);
        if(brightness!=inputs.ambient+200||&lamp.unitConverter()!=converter)throw std::runtime_error("Crossing source radius changed converter identity");
        inside|=inputs.sourceIntensity>0;outside|=inputs.sourceIntensity==0;
    }
    if(!inside||!outside)throw std::runtime_error("Unit source-radius crossing integration did not exercise both sides");
    if(lit==unlit||!updates||lamp.vehiclePixels!=coverage||lamp.shadowBuilds!=shadowBuilds||lamp.voxelBuilds!=litBuilds||sim.tick!=lightTick||sim.drive.position!=lightPosition)
        throw std::runtime_error("Static emitter color/coverage/cache/simulation isolation regression");
    if(argc==3)lamp.writePpm(std::string(argv[2])+"-light-on.ppm");
    if(lamp.setLightActive(true)!=0||lamp.setLightActive(false)!=updates)throw std::runtime_error("Static emitter immediate/idempotent update regression");
    lamp.draw(sim);if(lamp.pixels!=unlit)throw std::runtime_error("Deactivated light did not restore complete frame");
    if(&lamp.unitConverter()!=converter||lamp.unitBrightnessAt(*a.cell(spawn.first,spawn.second))!=1312)throw std::runtime_error("Deactivated unit light did not restore brightness and palette identity");
    if(argc==3)lamp.writePpm(std::string(argv[2])+"-light-off.ppm");
    auto placed=a;placed.hasPlacedLights=true;placed.placedLight=std::pair{spawn.first+2,spawn.second};
    ra2::Renderer placedLamp(placed,512,360);placedLamp.camera=r.camera;placedLamp.draw(sim);
    if(placedLamp.pixels!=lit)throw std::runtime_error("Placed stock light differs from bounded demonstration");
    ra2::Renderer low(a,512,360,"DarkRed",1);low.camera=r.camera;low.draw(sim);const auto lowFrame=low.pixels;
    low.addLightDemo(spawn.first+2,spawn.second);low.draw(sim);
    if(low.pixels!=lowFrame||low.lightUpdates()!=0||!low.lightActive())throw std::runtime_error("Graphics-detail source eligibility regression");
    auto zero=a;zero.invisibleLight->intensity=0.0001;
    ra2::Renderer absent(zero,512,360);absent.camera=r.camera;absent.addLightDemo(spawn.first+2,spawn.second);absent.draw(sim);
    if(absent.hasLight()||absent.lightUpdates()!=0||absent.pixels!=unlit)throw std::runtime_error("Zero integer intensity created a source");
    std::cout<<"Stock INGALITE immediate cell updates="<<updates<<"; reversible pixels, stable coverage/shadow cache/simulation, low-detail gate: PASS\n";
    std::cout<<"Ordinary unit brightness=1312, near active INGALITE=1491; stable house converter across map tint, source radius and toggles: PASS\n";
    std::set<std::uint64_t> body,turret;
    for(int heading=0;heading<8;++heading) {
        sim.drive.body.setCurrent(std::uint16_t(heading*8192),sim.tick);r.draw(sim);body.insert(frameHash(r.pixels));
    }
    sim.drive.body.setCurrent(0,sim.tick);
    for(int heading=0;heading<8;++heading) {
        sim.drive.turret.setCurrent(std::uint16_t(heading*8192),sim.tick);r.draw(sim);turret.insert(frameHash(r.pixels));
        if(heading==2&&argc==3)r.writePpm(std::string(argv[2])+"-tank.ppm");
    }
    sim.drive.turret.setCurrent(0,sim.tick);r.draw(sim,true,false);const auto withoutShadow=r.pixels;
    r.draw(sim);std::size_t shadowChanges=0;for(std::size_t i=0;i<r.pixels.size();++i)shadowChanges+=r.pixels[i]!=withoutShadow[i];
    if(!r.shadowPixels||!shadowChanges)throw std::runtime_error("Original-column shadow integration regression");
    const auto warmFrame=r.pixels;const auto buildCount=r.shadowBuilds,hitCount=r.shadowHits;
    r.draw(sim);
    if(r.pixels!=warmFrame||r.shadowBuilds!=buildCount||r.shadowHits!=hitCount+1)throw std::runtime_error("Warm shadow cache repeat regression");
    // Fresh cache and bypass compare the same staged input; cross-heading pool
    // eviction or original full-actor invalidation is not established here.
    ra2::Renderer fresh(a,512,360);fresh.camera=r.camera;fresh.draw(sim);
    const auto cached=fresh.pixels;fresh.draw(sim,true,true,false);
    if(fresh.pixels!=cached||fresh.shadowBuilds!=2)throw std::runtime_error("Shadow miss/hit/bypass buffer integration regression");
    auto disabledShadow=a;disabledShadow.disableShadowCache=true;
    ra2::Renderer directShadow(disabledShadow,512,360);directShadow.camera=r.camera;
    directShadow.draw(sim);directShadow.draw(sim);
    if(directShadow.pixels!=cached||directShadow.shadowBuilds!=2||directShadow.shadowHits)throw std::runtime_error("Type DisableShadowCache bypass integration regression");
    auto suppressedShadow=a;suppressedShadow.noShadow=true;
    ra2::Renderer absentShadow(suppressedShadow,512,360);absentShadow.camera=r.camera;absentShadow.draw(sim);
    if(absentShadow.pixels!=withoutShadow||absentShadow.shadowPixels||absentShadow.shadowBuilds)throw std::runtime_error("Type NoShadow suppression integration regression");
    std::cout<<"Recovered flat shadow identity: warm/bypass pixels, type disabling and suppression: PASS\n";
    const auto redFrame=r.pixels;const auto simPosition=sim.drive.position;const auto tick=sim.tick;
    const auto colorBuilds=r.voxelBuilds;
    r.setPlayerColor("Gold");r.draw(sim);const auto goldFrame=r.pixels;
    r.setPlayerColor("DarkBlue");r.draw(sim);const auto blueFrame=r.pixels;
    if(redFrame==goldFrame||goldFrame==blueFrame||redFrame==blueFrame||r.voxelBuilds!=colorBuilds||sim.drive.position!=simPosition||sim.tick!=tick)throw std::runtime_error("Player color integration or simulation isolation regression");
    std::size_t colorChanges=0;for(std::size_t i=0;i<goldFrame.size();++i)colorChanges+=goldFrame[i]!=blueFrame[i];
    if(colorChanges>r.vehiclePixels*9)throw std::runtime_error("Player color changed pixels outside the zoomed vehicle footprint");
    if(argc==3)r.writePpm(std::string(argv[2])+"-blue.ppm");
    bool unknownRejected=false;try{r.setPlayerColor("missing-scheme");}catch(const std::invalid_argument&){unknownRejected=true;}
    if(!unknownRejected||r.playerColor()!="darkblue")throw std::runtime_error("Invalid player color changed the current scheme");
    r.setPlayerColor("DarkRed");
    std::cout<<"Shadow pixels="<<r.shadowPixels<<" displayed changes="<<shadowChanges<<"; three distinct player schemes, simulation unchanged: PASS\n";
    if(body.size()!=8||turret.size()!=8)throw std::runtime_error("Independent heading render regression");
    // Static diagnostic pose near an original cliff; not a navigable route or
    // original-game screenshot. Find one low flat cell with higher ground in front.
    bool covered=false;int attempts=0;
    for(const auto& cell:a.map.cells) {
        if(a.tile(cell).ramp||!a.clearCell(cell.x,cell.y,cell.z))continue;
        bool cliff=false;
        for(const auto [dx,dy]:{std::pair{1,0},std::pair{0,1},std::pair{1,1},std::pair{2,1},std::pair{1,2},std::pair{2,2}}) {
            const auto* front=a.cell(cell.x+dx,cell.y+dy);cliff|=front&&front->z>=cell.z+2;
        }
        if(!cliff)continue;
        ra2::Simulation pose({cell.x+0.1,cell.y+0.1},cell.z,a.rot,a.speed,a.driveData,a.passive);
        r.center(pose);r.draw(pose,false);auto without=r.pixels;const auto unobscured=r.vehiclePixels;
        r.draw(pose);std::size_t changed=0;for(std::size_t i=0;i<without.size();++i)changed+=without[i]!=r.pixels[i];
        if(changed>100&&r.terrainRejections>20&&r.vehiclePixels>unobscured/10&&r.vehiclePixels<unobscured*9/10) {
            const auto visible=r.vehiclePixels;
            if(argc==3){r.writePpm(std::string(argv[2])+"-cliff.ppm");r.draw(pose,false);r.writePpm(std::string(argv[2])+"-cliff-without-depth.ppm");}
            std::cout<<"Cliff fixture cell="<<cell.x<<','<<cell.y<<" elevation="<<unsigned(cell.z)<<" visible tank pixels="<<visible<<'/'<<unobscured<<" changed pixels="<<changed<<"\n";
            covered=true;break;
        }
        if(++attempts>=180)break;
    }
    if(!covered)throw std::runtime_error("No original-map cliff occlusion fixture exercised");
    if(a.sceneryImages.size()!=30||a.scenery.size()!=565||a.sceneryImages.at("tree01").width!=155||a.sceneryImages.at("tree01").height!=155)throw std::runtime_error("Stock static terrain assets/map regression");
    if(a.sceneryLifecycle.occupation.members.size()!=565||a.sceneryLifecycle.occupation.cells.size()!=a.map.cells.size())
        throw std::runtime_error("Prepared ordinary scenery occupation count regression");
    for(std::size_t i=0;i<a.scenery.size();++i) {
        const auto& placement=a.scenery[i];const auto& actor=a.sceneryLifecycle.occupation.members.at(int(i));
        const auto& cell=a.sceneryLifecycle.occupation.cells.at({std::int16_t(placement.x),std::int16_t(placement.y)});
        if(actor.state.onMap!=1||actor.state.needsRedraw!=1||actor.state.limbo||actor.next!=-1||cell.head!=int(i)||
           cell.flags!=((actor.type.temperate&7)<<2)||cell.alternateHead!=-1)
            throw std::runtime_error("Prepared scenery membership/occupation regression");
        if(!a.occupied.contains({placement.x,placement.y}))throw std::runtime_error("Conservative scenery clearance disappeared");
    }
    auto lifecycle=a.sceneryLifecycle;const auto initialCells=lifecycle.occupation.cells;
    const auto services=ra2::staticSceneryServices(a);
    const auto layer=lifecycle.objects.layers[2];
    if(layer.count!=565||layer.slots.size()!=570)throw std::runtime_error("Prepared scenery layer registration/growth regression");
    std::map<ra2::TerrainCellPoint,unsigned> expectedNeighbors;
    std::int32_t previousKey=-2147483647-1;
    for(int slot=0;slot<layer.count;++slot) {
        const auto id=layer.slots.at(std::size_t(slot));const auto& actor=lifecycle.occupation.members.at(id);
        const auto key=ra2::terrainSortKey(actor.position);
        if(key<previousKey||lifecycle.objects.actors.at(id).lastLayer!=2)throw std::runtime_error("Scenery layer order/identity regression");
        previousKey=key;
        const auto screen=services.projectWorld(actor.position);const auto& life=lifecycle.actors.at(id);
        if(life.screenX!=screen[0]||life.screenY!=screen[1])throw std::runtime_error("Scenery projection stores regression");
        const auto point=ra2::terrainCellPoint(actor.position);
        for(int d=0;d<8;++d){const auto [dx,dy]=ra2::directionOffset(d);++expectedNeighbors[{std::int16_t(point.x+dx),std::int16_t(point.y+dy)}];}
    }
    for(const auto& [point,cell]:initialCells)if(cell.neighbors!=std::uint8_t(expectedNeighbors[point]))
        throw std::runtime_error("Scenery neighbor counter regression");
    for(std::size_t i=0;i<a.scenery.size();++i)if(!lifecycle.limbo(int(i),services)||lifecycle.limbo(int(i),services))
        throw std::runtime_error("Native scenery remove/idempotence regression");
    if(lifecycle.objects.layers[2].count)throw std::runtime_error("Scenery removal left layer registrations");
    for(const auto& [point,cell]:lifecycle.occupation.cells)if(cell.flags||cell.head!=-1||cell.alternateHead!=-1||cell.neighbors)
        throw std::runtime_error("Native scenery removal left cell state");
    for(std::size_t i=0;i<a.scenery.size();++i) {
        const auto id=int(i);const auto position=lifecycle.occupation.members.at(id).position;
        if(!lifecycle.unlimbo(id,position,services)||lifecycle.unlimbo(id,position,services))
            throw std::runtime_error("Native scenery restore/idempotence regression");
    }
    for(const auto& [point,cell]:lifecycle.occupation.cells) {
        const auto& old=initialCells.at(point);
        if(cell.flags!=old.flags||cell.head!=old.head||cell.alternateHead!=old.alternateHead||cell.neighbors!=old.neighbors)
            throw std::runtime_error("Native scenery restore changed cell state");
    }
    if(lifecycle.objects.layers[2].count!=565||lifecycle.objects.layers[2].slots!=layer.slots)
        throw std::runtime_error("Scenery restoration changed layer order/tail");
    std::cout<<"Prepared 565 scenery actors: occupation, 4520 neighbor contributions, projection, sorted registration and removal/restoration PASS (native integration)\n";
    auto noTrees=a;noTrees.sceneryImages.clear();noTrees.scenery.clear();ra2::prepareStaticScenery(noTrees);
    ra2::Renderer scenery(a,512,360),emptyScenery(noTrees,512,360);scenery.camera.zoom=emptyScenery.camera.zoom=2;
    if(!scenery.centerScenery(0)||emptyScenery.centerScenery(0))throw std::runtime_error("Scenery camera inspection regression");
    emptyScenery.camera=scenery.camera;scenery.draw(sim);emptyScenery.draw(sim);
    const auto treesFrame=scenery.pixels;const auto sceneryTick=sim.tick;
    if(!scenery.sceneryPixels||!scenery.sceneryShadowPixels||treesFrame==emptyScenery.pixels)throw std::runtime_error("Tree image/shadow integration regression");
    scenery.draw(sim);scenery.setPlayerColor("Gold");scenery.draw(sim);
    if(scenery.pixels!=treesFrame||sim.tick!=sceneryTick)throw std::runtime_error("Static scenery cache/house separation regression");
    if(argc==3)scenery.writePpm(std::string(argv[2])+"-trees.ppm");
    const auto tx=a.scenery.front().x,ty=a.scenery.front().y;const auto treeCoverage=scenery.sceneryPixels;
    scenery.addLightDemo(tx,ty);scenery.draw(sim);
    if(scenery.pixels==treesFrame||scenery.sceneryPixels!=treeCoverage)throw std::runtime_error("Tree local light integration regression");
    if(argc==3)scenery.writePpm(std::string(argv[2])+"-trees-lit.ppm");
    scenery.setLightActive(false);scenery.draw(sim);
    if(scenery.pixels!=treesFrame)throw std::runtime_error("Tree light deactivation did not restore static layer");
    bool treeOcclusion=false;
    for(int dx=-1;dx<=1&&!treeOcclusion;++dx)for(int dy=-1;dy<=1&&!treeOcclusion;++dy) {
        // Diagnostic poses bypass routing; occupation/pathfinding is not claimed.
        const auto* cell=a.cell(tx+dx,ty+dy);if(!cell)continue;
        ra2::Simulation pose({tx+dx+0.5,ty+dy+0.5},cell->z,a.rot,a.speed,a.driveData,a.passive);
        scenery.draw(pose);emptyScenery.draw(pose);
        treeOcclusion=scenery.vehiclePixels>0&&scenery.vehiclePixels<emptyScenery.vehiclePixels;
        if(treeOcclusion&&argc==3)scenery.writePpm(std::string(argv[2])+"-tree-occlusion.ppm");
    }
    if(!treeOcclusion)throw std::runtime_error("Scenery depth did not exercise a bounded tank overlap");
    // Every supplied map type gets a native inspection frame; original pixel
    // comparisons are separately performed by compare_terrain_types.py.
    std::set<std::string> checkedTypes;
    for(std::size_t i=0;i<a.scenery.size();++i)if(checkedTypes.insert(a.scenery[i].type).second) {
        scenery.centerScenery(i);scenery.draw(sim);
        if(!scenery.sceneryPixels||!scenery.sceneryShadowPixels)throw std::runtime_error("Tree type inspection frame missing body/shadow");
    }
    if(!scenery.centerProp(0)||emptyScenery.centerProp(0))throw std::runtime_error("Prop-only camera inspection regression");
    scenery.draw(sim);
    if(!scenery.propPixels||!scenery.propShadowPixels)throw std::runtime_error("Prop inspection frame lacks body/shadow");
    if(argc==3)scenery.writePpm(std::string(argv[2])+"-props.ppm");
    // Isolate every owned ordinary prop, including raw signs absent from this
    // map. This is native pipeline QA; compare_props.py checks original pixels.
    for(const auto& id:ra2::stockStaticPropTypes()) {
        auto prop=noTrees;
        auto image=ra2::readShp(a.store.require(id+".tem"));
        if(id>="sign03"&&id<="sign06"&&(image.frames[0].format!=1||image.frames[1].format!=3))
            throw std::runtime_error("Owned raw sign profile regression");
        prop.sceneryImages.emplace(id,std::move(image));prop.scenery.push_back({tx,ty,id});ra2::prepareStaticScenery(prop);
        ra2::Renderer inspect(prop,512,360);inspect.camera.zoom=2;inspect.centerProp(0);inspect.draw(sim);
        if(!inspect.propPixels||!inspect.propShadowPixels)throw std::runtime_error("Isolated prop lacks body/shadow: "+id);
        const auto frame=inspect.pixels;inspect.draw(sim);
        if(inspect.pixels!=frame)throw std::runtime_error("Isolated static prop repeat changed: "+id);
        if(argc==3&&id=="sign03")inspect.writePpm(std::string(argv[2])+"-sign03.ppm");
    }
    std::cout<<"Static scenery: 565 owned map placements / 30 types; 34 props, body/shadow, cache repeat, house separation, reversible local light and diagnostic unit occlusion: PASS (native integration only)\n";
    std::cout<<"All 23 owned ordinary props, including four raw-body/RLE-shadow signs: isolated native rendering PASS\n";
    std::cout<<"Owned-data normal/VPL/RGB565, independent headings, shadows, player colors and terrain occlusion integration: PASS\n";
 } catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
