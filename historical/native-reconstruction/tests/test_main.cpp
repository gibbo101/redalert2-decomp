// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/Archive.hpp"
#include "assets/ArchiveSequence.hpp"
#include "assets/Formats.hpp"
#include "assets/UnitTypeMetadata.hpp"
#include "assets/GameAssets.hpp"
#include "assets/MovementData.hpp"
#include "assets/RampGeometryData.hpp"
#include "render/Lighting.hpp"
#include "render/MapLighting.hpp"
#include "render/StaticLight.hpp"
#include "render/UnitLighting.hpp"
#include "render/VoxelRaster.hpp"
#include "render/Composition.hpp"
#include "render/PlayerColor.hpp"
#include "render/VoxelShadow.hpp"
#include "render/UnitStaging.hpp"
#include "render/ShadowCache.hpp"
#include "render/VoxelCache.hpp"
#include "render/ShadowKeys.hpp"
#include "render/Scenery.hpp"
#include "sim/Simulation.hpp"
#include "platform/FramePacer.hpp"
#include <bit>
#include <cmath>
#include <cfenv>
#include <iostream>
#include <stdexcept>
using namespace ra2;
static int checks=0;
static void require(bool ok,const char* what) {++checks;if(!ok)throw std::runtime_error(what);}
template<class F> static void rejects(F f,const char* what) {bool failed=false;try{f();}catch(const std::exception&){failed=true;}require(failed,what);}
static void put16(Bytes& b,std::size_t p,unsigned v){b.at(p)=v&255;b.at(p+1)=(v>>8)&255;}
static void put32(Bytes& b,std::size_t p,std::uint32_t v){for(int i=0;i<4;++i)b.at(p+i)=std::uint8_t(v>>(i*8));}
static void putFloat(Bytes& b,std::size_t p,float f){put32(b,p,std::bit_cast<std::uint32_t>(f));}
int main() {
 try {
    const UnitTypeMetadata ordinary{0,1,1,0,0};
    requireOrdinaryRhinoMetadata(ordinary);
    for(int field=0;field<5;++field) {
        auto unsupported=ordinary;
        std::uint8_t* flags[]={&unsupported.harvester,&unsupported.voxel,&unsupported.turret,
                               &unsupported.hunterSeeker,&unsupported.balloonHover};
        *flags[field]=(field==1||field==2)?0:255;
        rejects([&]{requireOrdinaryRhinoMetadata(unsupported);},"Unsupported drawing type metadata is refused");
    }
    const auto type=readUnitTypeMetadata(Ini("[HTNK]\nTurret=Totally\nHarvester=Nonsense\n"),Ini("[HTNK]\nVoxel=Yarbitrary\n"),"HTNK");
    require(type.harvester==0&&type.voxel==1&&type.turret==1,"Rhino metadata uses recovered first-byte boolean decisions");
    const auto defaults=readUnitTypeMetadata(Ini("[HTNK]\nTurret=unknown\n"),Ini(""),"HTNK",{0,255,127,0,0});
    require(defaults.voxel==255&&defaults.turret==127,"Missing or unknown metadata preserves its default byte");
    const auto point=terrainCellPoint({-255,-257,2147483647});
    require(point.x==0&&point.y==-1,"Terrain cell conversion divides signed coordinates toward zero before word truncation");
    require(terrainCellPoint({8388608,-8388864,0})==TerrainCellPoint{-32768,32767},"Terrain cell coordinates wrap at sixteen bits");
    auto occupied=terrainOccupation({0,0,0},0,{0xfffffff7u,2},0xa573c900,true);
    require(occupied.flags==0xa573c91c&&occupied.writes==std::vector<std::uint8_t>({4,12,28}),"Terrain occupation preserves high bytes and ordered low-mask stores");
    require(terrainOccupation({},0,{7,0},occupied.flags,true).writes==std::vector<std::uint8_t>({28,28,28}),"Repeated occupation still writes every selected bit");
    require(terrainOccupation({},1,{7,2},0xffffffffu,false).flags==0xfffffff7u,"Snow alone selects snow occupation mask");
    require(terrainOccupation({},-1,{0,7},0xffffffffu,false).writes.empty(),"Zero temperate mask ignores snow and has no stores");
    TerrainMarkState markState{0,2,0};
    auto markDecision=terrainMark(markState,3);
    require(markDecision.accepted&&markDecision.coordinates&&markDecision.action==TerrainMapAction::Insert&&markState.onMap==1&&markState.needsRedraw==2,"Mark mode three preserves existing noncanonical redraw byte");
    require(!terrainMark(markState,1).accepted&&!terrainMark(markState,2).accepted,"Already marked or already dirty actor rejects duplicate mark/redraw");
    require(terrainMark(markState,0).accepted&&markState.onMap==0&&markState.needsRedraw==2,"Removal leaves redraw state unchanged");
    markState={2,0,0};markDecision=terrainMark(markState,2);
    require(markDecision.accepted&&markDecision.action==TerrainMapAction::None&&markState.onMap==2&&markState.needsRedraw==1,"Redraw accepts nonzero onMap without insertion");
    markState={0,0,255};require(!terrainMark(markState,1).accepted&&markState.onMap==0,"Limbo rejects insertion before changing fields");
    TerrainOccupationWorld world;const TerrainCellPoint origin{0,0};world.cells[origin]={0xa573c900};
    world.members.emplace(0,TerrainMember{{128,128,0},{7,7}});
    world.members.emplace(1,TerrainMember{{128,128,0},{2,2}});
    std::vector<TerrainOccupationEvent> occupationEvents;auto trace=[&](auto e){occupationEvents.push_back(e);};
    require(world.mark(0,1,trace)&&world.cells.at(origin).head==0&&world.cells.at(origin).flags==0xa573c91c,"Mark inserts ordinary terrain and occupies its coordinate cell");
    std::string sequence;for(const auto& e:occupationEvents)sequence+=e.kind;
    require(sequence=="MBRCNHVLWWWD","Terrain mark preserves actor, redraw, coordinate, list and cell-event order");
    require(world.mark(1,1)&&world.cells.at(origin).head==1&&world.members.at(1).next==0,"Terrain insertion prepends to ground membership");
    world.cellInsert(0,origin,false);
    require(world.cells.at(origin).head==1&&world.members.at(0).next==-1,"Terrain insertion preserves unusual head-next duplicate guard");
    require(world.mark(0,0)&&world.cells.at(origin).head==1&&world.members.at(1).next==-1&&world.cells.at(origin).flags==0xa573c900,"Overlapping terrain removal clears bits without reference counting");
    world.members.at(0).next=1;occupationEvents.clear();world.cellRemove(0,origin,false,trace);
    sequence.clear();for(const auto& e:occupationEvents)sequence+=e.kind;
    require(world.members.at(0).next==1&&sequence=="LWWW","Missing-member removal leaves Next but still unmarks occupation");
    world.members.at(0).next=-1;world.cellInsert(0,origin,true);
    require(world.cells.at(origin).alternateHead==0&&world.cells.at(origin).head==1,"Alternate cell head is independent from ground head");
    world.cellRemove(0,origin,true);
    require(world.cells.at(origin).alternateHead==-1&&world.members.at(0).next==-1,"Alternate removal clears only selected head and removed Next");
    require(terrainStrengthDefault(-1,200)==200&&terrainStrengthDefault(0,200)==0,"Terrain strength sentinel defaults to TreeStrength only for -1");
    const auto reload=terrainImageReload("TREE28",true,true,7,false,0,1);
    require(reload&&reload->filename=="TREE28.TEM"&&reload->releasePrevious,"Terrain theater reload uses type ID and releases owned nonnull image");
    require(!terrainImageReload("TREE01",true,true,7,false,0,0)&&!terrainImageReload("TREE01",false,true,7,true,0,1),"Same-theater and nontheater terrain skip reload");
    require(terrainImageReload("TREE01",true,false,7,true,1,1)->filename=="TREE01.SNO"&&!terrainImageReload("TREE01",true,true,0,true,2,0)->releasePrevious,"Forced reload, extension and null ownership behavior");
    rejects([]{terrainImageReload("../TREE01",true,false,0,true,0,1);},"Bounded terrain filenames refuse paths");
    Bytes shp(39);put16(shp,2,7);put16(shp,4,7);put16(shp,6,1);
    put16(shp,8,2);put16(shp,10,3);put16(shp,12,3);put16(shp,14,1);put32(shp,16,3);put32(shp,28,32);
    put16(shp,32,7);shp[34]=9;shp[35]=0;shp[36]=2;shp[37]=0;shp[38]=1;
    const auto decoded=readShp(Data(shp));
    require(decoded.width==7&&decoded.frames[0].x==2&&decoded.frames[0].y==3&&decoded.frames[0].pixels==Bytes({9,0,0}),"SHP exact odd crop and terminal transparent padding");
    auto bad=shp;bad.pop_back();rejects([&]{readShp(Data(bad));},"SHP truncated run rejected");
    bad=shp;put32(bad,28,12);rejects([&]{readShp(Data(bad));},"SHP header-overlapping pixels rejected");
    bad=shp;bad[37]=8;rejects([&]{readShp(Data(bad));},"SHP literal beyond crop rejected");
    bad=shp;bad[38]=2;rejects([&]{readShp(Data(bad));},"SHP excessive row padding rejected");
    bad=shp;bad[36]=0;rejects([&]{readShp(Data(bad));},"SHP zero-length run rejected");
    bad=shp;put32(bad,16,2);rejects([&]{readShp(Data(bad));},"Unrecovered SHP format refused");
    bad=shp;put32(bad,28,0);require(readShp(Data(bad)).frames[0].pixels==Bytes(3),"Missing SHP pixel offset stays transparent");
    auto rawShp=shp;rawShp.resize(35);put32(rawShp,16,1);rawShp[32]=0;rawShp[33]=17;rawShp[34]=9;
    const auto rawImage=readShp(Data(rawShp));
    require(rawImage.frames[0].format==1&&rawImage.frames[0].pixels==Bytes({0,17,9}),"Raw SHP preserves exact contiguous pixels and format");
    rawShp.pop_back();rejects([&]{readShp(Data(rawShp));},"Truncated raw SHP pixels refused");
    const auto treeInput=staticTerrainDrawInputs(2,60,1234);
    require(treeInput[0].zAdjust==-72&&treeInput[0].brightness==1234&&treeInput[1].zAdjust==-63&&treeInput[1].gradient==0,"Tree body and shadow use distinct original inputs");
    rejects([]{staticTerrainDrawInputs(4,0,1000);},"Animated tree profile refused");
    ShpImage tinyTree{5,5,{{1,1,3,3,Bytes(9,1)},{1,1,3,3,Bytes(9,1)}}};
    std::vector<std::uint16_t> treeColors(25,0xffff),treeDepth(25,32751),treeAlpha(25,127);
    std::vector<Palette16> treeRows(53);for(auto& row:treeRows)row[1]=123;
    const auto flatTree=staticTerrainDrawInputs(2,0,1000);
    blitTerrainFrame(tinyTree,flatTree[0],{2,2},{0,0,5,5},treeRows,5,5,treeColors,treeDepth,treeAlpha);
    require(treeColors[6]==0xffff&&treeDepth[6]==32751,"Tree body rejects depth ties");
    treeDepth.assign(25,65535);blitTerrainFrame(tinyTree,flatTree[0],{2,2},{0,0,5,5},treeRows,5,5,treeColors,treeDepth,treeAlpha);
    require(treeColors[6]==123&&treeDepth[6]==32751&&treeDepth[0]==65535,"Tree body writes color and depth only under nonzero source");
    treeColors.assign(25,0xffff);treeDepth.assign(25,65535);
    blitTerrainFrame(tinyTree,flatTree[1],{2,2},{0,0,5,5},{},5,5,treeColors,treeDepth,treeAlpha);
    require(treeColors[6]==0x7bef&&treeDepth[6]==32764&&treeDepth[11]==32763,"SHP shadow halves RGB565 and writes descending depth");
    auto rawTerrain=tinyTree;rawTerrain.frames[0].format=1;treeColors.assign(25,0xffff);treeDepth.assign(25,65535);
    blitTerrainFrame(rawTerrain,flatTree[0],{2,2},{0,0,5,3},treeRows,5,5,treeColors,treeDepth,treeAlpha);
    require(treeDepth[6]==32754,"Raw terrain body uses bottom-clipped height for gradient phase");
    Facing f;f.setRate(5);f.setDesired(8193,0);
    require(f.duration==6,"facing duration");require(f.current(0)==3,"preserve divide-before-multiply remainder");require(f.current(6)==8193,"facing completion");
    f.setCurrent(65500,20);f.setDesired(1000,20);require(f.duration==0&&f.current(20)==1000,"sub-rate wrap snap");
    f.setCurrent(0,0);f.setDesired(32768,0);require(f.difference()==-32768,"half turn signed tie");
    f.setRate(300);require(f.rate==32512,"ROT cap");f.setRate(-1);require(f.rate==65280,"ROT low byte behavior");
    Facing turn;turn.setRate(5);turn.setDesired(16384,0);auto middle=turn.current(4);turn.setDesired(40000,4);require(turn.start==middle,"interrupted turn starts at recovered current");
    const auto duration=turn.duration;require(!turn.setDesired(40000,5)&&turn.duration==duration,"repeat target does not restart");
    // Deliberately synthetic four-lepton tracks, not extracted original tables.
    auto driveData=std::make_shared<DriveData>();driveData->stopScale=0.3;
    // Synthetic angle data; original lookup bytes remain user-supplied only.
    auto& aim=driveData->directionsToTargets;aim.slopeStep=0.125f;
    aim.pi=std::acos(-1.0);aim.halfPi=aim.pi/2;aim.angleScale=-65536/(2*aim.pi);
    aim.positiveHalfPi=float(aim.halfPi);aim.negativeHalfPi=-aim.positiveHalfPi;
    for(std::size_t i=0;i<aim.atan.size();++i)aim.atan[i]=float(std::atan(i*double(aim.slopeStep)));
    for(int i=1;i<=64;++i) {int q=256-4*i;driveData->tracks[0].points.push_back({0,q,0});driveData->tracks[1].points.push_back({-q,q,32});}
    const int flags[8]={0,0,3,4,4,1,1,2};
    for(int d=0;d<8;++d)driveData->transitions[d*9]={d%2+1,flags[d],d*32,0};
    require(internalSpeed(6)==15&&internalSpeed(100)==255&&internalSpeed(-1,33)==33,"original INI speed scaling");
    const int hostRounding=std::fegetround();
    require(currentSpeed(15,0.3)==4&&std::fegetround()==hostRounding,"speed truncation restores host rounding");
    Simulation sim({10.5,10.5},0,5,6,driveData);auto clear=[](int x,int y,int z){return x>=10&&x<=14&&y>=10&&y<=14&&z==0;};
    require(sim.move({12.5,10.5},clear),"clear move accepted");const auto before=sim.position;sim.step();require(sim.position.x==before.x&&sim.position.y==before.y,"adapter waits for turn");
    for(int i=0;i<200;++i)sim.step();require(!sim.moving&&sim.position.x==12.5&&sim.position.y==10.5,"arrival exact");
    require(std::fegetround()==hostRounding,"movement restores host rounding");
    require(!sim.drive.navigationTarget,"arrival clears coordinate target adapter");
    sim.aim({11.5,9.5});require(sim.drive.manualTurret&&std::fegetround()==hostRounding,"manual aim preserves host rounding");
    rejects([&]{destinationDirection(aim,{0,0,0},{2000000,0,0});},"bearing domain check");
    FramePacer pacer(3);require(pacer.ready(7),"first frame immediately eligible");pacer.begin(7);
    require(!pacer.ready(47)&&pacer.ready(48),"original 16ms clock phase");
    pacer.setSpeed(5);require(!pacer.ready(47),"speed change retains active wait");pacer.begin(48);
    require(!pacer.ready(63)&&pacer.ready(64),"new speed applies next frame");
    pacer.begin(1000);require(!pacer.ready(1000)&&pacer.ready(1008),"late frame resets origin without catch-up");
    pacer.pause(true);require(!pacer.ready(5000),"pause blocks updates");pacer.pause(false);
    require(pacer.ready(5000),"resume rebases without backlog");pacer.setSpeed(6);pacer.begin(5000);
    require(pacer.ready(5000)&&pacer.sleepHint(5000)==0,"fastest is uncapped");
    rejects([]{FramePacer invalid(7);},"speed range validation");
    rejects([]{readDirectionData(Data(Bytes(32)));},"truncated derived angle data rejected");
    rejects([]{readDirectionData(Data(Bytes(16464)));},"derived angle hash mismatch rejected");
    rejects([]{readRampGeometryData(Data(Bytes(32)));},"truncated ramp geometry data rejected");
    rejects([]{readRampGeometryData(Data(Bytes(16432)));},"ramp geometry hash mismatch rejected");
    rejects([]{readRenderData(Data(Bytes(32)));},"truncated derived render data rejected");
    rejects([]{readRenderData(Data(Bytes(69944)));},"derived render hash mismatch rejected");
    RenderData syntheticLight;syntheticLight.normals[1]={{0,0,1},{0,0,-1}};syntheticLight.shadeScale=16;
    const auto normalShades=voxelShades(syntheticLight,1,{0,0,1},{0,0,1},3,true);
    require(normalShades[0]==16&&normalShades[1]==0&&normalShades[253]==16,"normal signs and special slots");
    require(std::fegetround()==hostRounding,"lighting restores host rounding");
    rejects([&]{voxelShades(syntheticLight,0,{},{},3,true);},"normal encoding bound");
    rejects([&]{voxelShades(syntheticLight,1,{NAN,0,0},{},3,true);},"nonfinite lighting rejected");
    Palette16 testPalette{};testPalette[1]=42;testPalette[2]=84;
    std::uint16_t output=7,zbuffer=100;
    depthPixel(1,100,42,output,zbuffer);require(output==7&&zbuffer==100,"equal-depth pixel preserves first writer");
    depthPixel(0,90,42,output,zbuffer);require(output==7&&zbuffer==100,"transparent pixel preserves color and depth");
    depthPixel(1,99,42,output,zbuffer);require(output==42&&zbuffer==99,"nearer nonzero pixel writes both planes");
    std::array<std::uint8_t,3> span{1,0,2};std::array<std::uint16_t,3> dest{7,7,7};std::array<std::uint16_t,2> depths{100,100};
    depthSpan(span,50,testPalette,dest,depths,1);
    require(dest==std::array<std::uint16_t,3>{42,7,7}&&depths==std::array<std::uint16_t,2>{100,50},"wrapped span preserves transparency and equal-depth first write");
    Bytes vpl(784+512);put32(vpl,0,16);put32(vpl,4,31);put32(vpl,8,2);vpl[19]=255;vpl[784+256+9]=77;
    auto voxelPalette=readVpl(Data(vpl));require(voxelPalette.palette[1].r==255&&voxelPalette.lookup(9,1)==77,"VPL eight-bit palette and shade-major lookup");
    rejects([&]{voxelPalette.lookup(9,2);},"VPL shade bound");
    vpl.pop_back();rejects([&]{readVpl(Data(vpl));},"VPL truncated section rejected");
    syntheticLight.paletteCoefficient=0.0625;Palette syntheticPalette{};syntheticPalette[1]={128,64,32};std::array<std::uint8_t,256> allAffected;allAffected.fill(1);
    const auto lit=lightPalette(syntheticLight,syntheticPalette,{1000,1000,1000},53,allAffected);
    require(lit.front()[1]==0&&lit[26][1]!=0&&lit.back()[1]!=lit[26][1],"synthetic palette dark/middle/bright rows");
    require(std::fegetround()==hostRounding,"palette builder restores host rounding");
    const auto mapSettings=mapLightSettings(0.6,{1,1,0.87},0,0.028);
    require(mapSettings.ambient==59&&mapSettings.level==28&&mapSettings.tint[2]==86,"map INI original decimal truncation");
    require(std::fegetround()==hostRounding,"map light conversion restores FP state");
    auto neutral=cellLight(syntheticLight,{100,{100,100,100},0,32},33,86,4);
    require(neutral.terrain==1128&&neutral.bridge==1256&&neutral.tint==std::array<int,3>{1000,1000,1000},"height lighting remains distinct from visibility");
    int lightScale=0,brightness=1200;std::array<int,3> tintZero{};normalizeLight(lightScale,brightness,tintZero);
    require(lightScale==65536&&brightness==0&&tintZero==std::array<int,3>{1000,1000,1000},"near-zero tint clears brightness and restores neutral converter");
    require(VisibleAlpha==127&&alphaShadeRow(VisibleAlpha,1000,53)==26,"original visible alpha and neutral row");
    require(extraUnitLight(-1)==-1000&&extraUnitLight(0.2)==200,"rules unit light has no static-type bias");
    require(std::fegetround()==hostRounding,"unit light conversion restores FP state");
    require(ordinaryUnitBrightness(1112,200)==1312,"unit uses unnormalized signed ambient plus extra");
    require(ordinaryUnitBrightness(1112,200,0x10000,false)==812&&ordinaryUnitBrightness(1112,200,0x10000,true)==1312,"unnamed cell flag/predicate branch");
    require(ordinaryUnitBrightness(32767,2147483647)==-2147450882,"unit brightness preserves wrapped addition");
    require(unitBrightnessEffect(1500,2)==2000&&unitBrightnessEffect(1501,2)==500&&unitBrightnessEffect(2200,0)==2200,"actor brightness effect threshold");
    require(unitLightCell(-255,257)==UnitLightCell{0,1},"unit lighting coordinate division truncates toward zero");
    rejects([]{unitLightCell(1048577,0);},"unit light coordinate bound");
    rejects([]{extraUnitLight(NAN);},"nonfinite unit light refused");
    rejects([]{houseUnitConverter({},0);},"missing house converter refused");
    require(cellLight(syntheticLight,{0,{0,0,0},0,0},0,0,0).terrain==1000,"invalid-cell lighting sentinel ignores scenario");
    rejects([&]{mapLightSettings(NAN,{1,1,1},0,0);},"nonfinite map settings refused");
    rejects([&]{cellLight(syntheticLight,{},33,86,32);},"unsupported map light elevation refused");
    const std::array<LightSource,1> invalidRadius{{{0,0,0,0}}};
    rejects([&]{cellLight(syntheticLight,{},33,86,4,invalidRadius);},"zero light radius refused");
    require(std::fegetround()==hostRounding,"map lighting restores FP mode after exceptions");
    const auto lamp=lightTypeInputs(5000,-0.15,{0.05,0.05,0.01});
    require(lamp.intensity==-149&&lamp.tint==std::array<int,3>{50,50,10},"type-light original bias before truncation");
    auto source=makeStaticLight(lamp,256,512,104);
    require(!source.active&&source.minimumDetail==2&&source.x==256&&source.z==104,"source starts inactive at graphics detail threshold 2");
    require(changeLightActive(source,true)&&!changeLightActive(source,true)&&changeLightActive(source,false),"source activation/deactivation are idempotent");
    require(affectedLightCells(syntheticLight,source,{},1).empty(),"stock source is gated at low graphics detail");
    require(affectedLightCells(syntheticLight,source,{},2,false).empty(),"disabled lighting has no map updates");
    require(terrainConverterInputs({1000,1000,860},2).tint==std::array<int,3>{992,992,832},"detail-2 terrain tint mask");
    require(terrainConverterInputs({1000,1000,1000},0).tint==std::array<int,3>{1000,1000,1000},"neutral converter fast path precedes mask");
    require(terrainConverterInputs({1000,1000,0},2).shades==27&&terrainConverterInputs({1000,1000,32},2).shades==53,"terrain shade count uses quantized-channel sum");
    rejects([&]{lightTypeInputs(0,0.2,{1,1,1});},"unsupported emitter radius rejected");
    rejects([&]{lightTypeInputs(5000,NAN,{1,1,1});},"nonfinite emitter setting rejected");
    rejects([&]{terrainConverterInputs({1000,1000,860},3);},"unsupported graphics detail rejected");
    require(std::fegetround()==hostRounding,"static source arithmetic restores host FP state");
    rejects([&]{lightPalette(syntheticLight,syntheticPalette,{1000,1000,1000},2,allAffected);},"unsupported low shade count rejected safely");
    require(!sim.move({16.5,10.5},clear),"blocked route rejected");require(!sim.move({11.5,NAN},clear),"NaN command rejected");
    sim.paused=true;auto tick=sim.tick;sim.step();require(sim.tick==tick,"pause");
    sim.paused=false;sim.move({11.5,10.5},clear);sim.stop();auto pos=sim.position;sim.step();require(!sim.moving&&sim.position.x==pos.x,"stationary stop");
    Simulation direct({10.5,10.5},0,5,6,driveData);
    require(direct.move({12.8,11.2},clear),"off-axis direct route accepted");
    require(direct.drive.destination==cellCenter(12,11)&&direct.drive.route==std::deque<int>({3,2}),"direct route snaps the requested cell, not a ray");
    require(direct.move({12.5,13.5},clear,true)&&direct.drive.route.size()==4,"waypoint appends queued cells");
    auto queued=direct.drive.route;
    require(!direct.move({100.5,100.5},clear,true)&&direct.drive.route==queued,"oversized append preserves existing order");
    rejects([&]{direct.drive.order(cellCenter(30,30),std::vector<int>(24,2));},"bounded original queue capacity");
    auto curveData=std::make_shared<DriveData>(*driveData);
    curveData->tracks[2].points={{-256,224,0},{-128,128,32},{-16,0,64},{0,0,64}};
    curveData->transitions[2]={3,8,64,0}; // Synthetic curve touches an off-route corner.
    Simulation corner({10.5,10.5},0,5,6,curveData);
    auto blockedCorner=[](int x,int y,int z){return x>=8&&x<=15&&y>=8&&y<=15&&z==0&&!(x==11&&y==10);};
    require(corner.move({10.5,9.5},blockedCorner),"first waypoint clear");
    require(!corner.move({11.5,9.5},blockedCorner,true),"curve footprint checks cells beyond the route centerline");
    require(corner.drive.destination==cellCenter(10,9)&&corner.drive.route==std::deque<int>({0}),"rejected curve preview has no command side effects");
    Ini ini(" [Test] ; comment\n K = first\nk=last ; suffix\nFloat=1.25\n");require(ini.get("TEST","K")=="last","INI comments/case/last value");require(ini.number("test","float")==1.25,"INI decimal");
    require(decodeBase64("YWJjZA==")==Bytes({'a','b','c','d'}),"base64");rejects([]{decodeBase64("ab$!");},"base64 reject");
    require(mixHash("HTNK.VXL")==mixHash("htnk.vxl"),"MIX case folding");
    Bytes archive(25);put32(archive,0,0);put16(archive,4,1);put32(archive,6,3);put32(archive,10,mixHash("test"));put32(archive,14,0);put32(archive,18,3);archive[22]='a';archive[23]='b';archive[24]='c';
    Mix mix{Data(archive)};require(mix.find("TEST")->text()=="abc"&&!mix.find("absent"),"MIX entry lookup");archive.pop_back();rejects([&]{Mix bad{Data(archive)};},"MIX truncation");
    const std::array<MixEntry,7> signedIndex{{{0x80000000,0,1},{0xffffffff,1,1},{0,2,1},{0,3,1},{0,4,1},{1,5,1},{0x7fffffff,6,1}}};
    require(findMixEntry(signedIndex,0)==&signedIndex[3],"MIX duplicate chooses original midpoint");
    require(findMixEntry(signedIndex,0x80000000)==&signedIndex[0]&&findMixEntry(signedIndex,0x7fffffff)==&signedIndex[6],"MIX signed extremes");
    require(!findMixEntry(signedIndex,0xfffffffe)&&!findMixEntry({},0),"MIX signed miss and empty index");
    Bytes duplicates(75);put32(duplicates,0,0x10000);put16(duplicates,4,5);put32(duplicates,6,5);
    for(unsigned i=0;i<5;++i){put32(duplicates,10+12*i,mixHash("test"));put32(duplicates,14+12*i,i);put32(duplicates,18+12*i,1);duplicates[70+i]=std::uint8_t('a'+i);}
    Mix duplicateMix{Data(duplicates)};
    require(duplicateMix.count()==5&&duplicateMix.find("test")->text()=="c","MIX parser retains duplicate index order");
    require(duplicateMix.hasChecksum()&&!duplicateMix.isEncrypted()&&duplicateMix.bodyOffset()==70&&duplicateMix.bodySize()==5,"MIX plaintext header metadata");
    put32(duplicates,10,0);put32(duplicates,22,0xffffffff);
    rejects([&]{Mix bad{Data(duplicates)};},"MIX unsorted signed index safety guard");
    Bytes negativeCount(10);put16(negativeCount,4,0x8000);
    rejects([&]{Mix bad{Data(negativeCount)};},"MIX negative signed count safety guard");
    std::array<bool,100> expansions{};expansions[0]=expansions[4]=expansions[99]=true;
    require(baseMixBootstrapNames(expansions)==std::vector<std::string>({"expand99.mix","expand04.mix","expand00.mix","ra2.mix","cache.mix","local.mix"}),"MIX descending bootstrap requests");
    require(theaterMixRequests(0,-1)==std::vector<std::string>({"generic.mix","temperat.mix","tem.mix","isotemp.mix","isogen.mix"}),"MIX first temperate requests");
    require(theaterMixRequests(0,0).empty(),"MIX same theater skips reload");
    require(theaterMixRequests(1,0)==std::vector<std::string>({"snow.mix","sno.mix","isosnow.mix","isogen.mix"}),"MIX snow requests omit generic reload");
    rejects([]{theaterMixRequests(3,-1);},"MIX unsupported theater request guard");
    auto allExist=[](const std::string&){return true;};
    auto requests=startupMixRequests(true,0,{"maps02.mix","maps01.mix"},{"movies02.mix","movies01.mix"},allExist);
    require(requests.success&&requests.names==std::vector<std::string>({"conquer.mix","cameo.mix","maps02.mix","maps01.mix","multi.mix","theme.mix","movies02.mix","movies01.mix"}),"MIX supplied enumeration order retained");
    require(!startupMixRequests(true,0,{}, {},allExist).success,"MIX missing enumerated map family stops startup");
    rejects([&]{startupMixRequests(false,2,{}, {},allExist);},"MIX unverified media index guard");
    Bytes pal(768,63);auto p=readPalette(Data(pal));require(p[1].r==252&&p[0].a==0,"palette expansion");pal[0]=64;rejects([&]{readPalette(Data(pal));},"palette range");
    Bytes raw(11);put16(raw,0,1);put16(raw,2,1);Bytes lzo{28};lzo.insert(lzo.end(),raw.begin(),raw.end());lzo.insert(lzo.end(),{17,0,0});Bytes pack(4);put16(pack,0,unsigned(lzo.size()));put16(pack,2,11);pack.insert(pack.end(),lzo.begin(),lzo.end());require(unpackMap(pack)==raw,"LZO chunk framing");pack.pop_back();rejects([&]{unpackMap(pack);},"LZO truncated");
    Bytes tmp(1872);put32(tmp,0,1);put32(tmp,4,1);put32(tmp,8,60);put32(tmp,12,30);put32(tmp,16,20);std::fill(tmp.begin()+72,tmp.begin()+972,7);
    auto tile=readTmp(Data(tmp));require(tile.size()==1&&tile[0].pixels[28]==7&&tile[0].pixels[0]==0,"TMP diamond geometry");tmp.resize(500);rejects([&]{readTmp(Data(tmp));},"TMP truncated");
    Bytes hva(88);put32(hva,16,1);put32(hva,20,1);hva[24]='x';putFloat(hva,40,1);putFloat(hva,40+20,1);putFloat(hva,40+40,1);putFloat(hva,52,3);
    auto animation=readHva(Data(hva));require(animation.frames==1&&animation.names[0]=="x"&&animation.at(0,0)[3]==3,"HVA row-major translation");rejects([&]{animation.at(1,0);},"HVA frame bounds");hva.resize(60);rejects([&]{readHva(Data(hva));},"HVA truncated");
    Bytes vxl(802+28+13+92);const std::string magic="Voxel Animation";std::copy(magic.begin(),magic.end(),vxl.begin());put32(vxl,20,1);put32(vxl,24,1);put32(vxl,28,13);vxl[802]='x';const int b=830,foot=b+13;put32(vxl,b,0);put32(vxl,b+4,4);vxl[b+8]=0;vxl[b+9]=1;vxl[b+10]=7;vxl[b+11]=3;vxl[b+12]=1;
    put32(vxl,foot,0);put32(vxl,foot+4,4);put32(vxl,foot+8,8);putFloat(vxl,foot+12,1);putFloat(vxl,foot+76,1);putFloat(vxl,foot+80,1);putFloat(vxl,foot+84,1);vxl[foot+88]=vxl[foot+89]=vxl[foot+90]=1;vxl[foot+91]=4;
    auto model=readVxl(Data(vxl));require(model.sections.size()==1&&model.sections[0].voxels.size()==1&&model.sections[0].voxels[0].color==7&&model.sections[0].voxels[0].normal==3,"VXL span decoding");
    require(model.sections[0].spans[0]==Bytes({0,1,7,3,1}),"retain validated original span sequence");
    vxl[b+12]=2;rejects([&]{readVxl(Data(vxl));},"VXL corrupt duplicate count");
    require(voxelHeading(1023)==0&&voxelHeading(1024)==1&&voxelHeading(65535)==0,"32-bin raster heading ties and wrap");
    rejects([]{readRasterData(Data(Bytes(41312)));},"raster data hash mismatch rejected");
    RasterData syntheticRaster;std::array<std::uint8_t,256> flatShade;flatShade.fill(1);voxelPalette.sections[1][7]=77;
    // Deliberately degenerate one-column synthetic traversal; no extracted table.
    auto raster=rasterVoxel(syntheticRaster,model.sections[0],voxelIdentity(),flatShade,voxelPalette);
    require(raster.pixels[127*256+128]==77&&std::count(raster.pixels.begin(),raster.pixels.end(),77)==1,"indexed single-voxel coverage");
    require(raster.rectangle==std::array<int,6>{-4,-4,124,124,9,9},"original scratch crop truncation");
    require(std::fegetround()==hostRounding,"raster restores host rounding");
    auto oversized=voxelIdentity();oversized[0]=300;
    rejects([&]{rasterVoxel(syntheticRaster,model.sections[0],oversized,flatShade,voxelPalette);},"scratch extent bound");
    require(worldPixels(0.125,{256,0,0})==PixelPoint{30,15},"integer world projection");
    require(heightPixels(0.125,727)==91&&heightPixels(0.125,728)==92,"original height correction threshold");
    require(std::fegetround()==hostRounding,"world projection restores FP mode");
    require(!barrelAfterTurret(8191)&&barrelAfterTurret(8192)&&!barrelAfterTurret(49152),"directional barrel/turret order");
    require(alphaShadeRow(127,1000,53)==26&&alphaShadeRow(254,1000,53)==52,"original alpha-map integer divisor");
    require(alphaShadeRow(127,2200,53)==52&&alphaShadeRow(255,65535,53)==52,"original unit brightness saturates lookup bin above 2000");
    std::uint16_t groundColor=0,groundZ=10;terrainPixel(0,10,0,42,groundColor,groundZ);
    require(groundColor==42&&groundZ==10,"terrain accepts depth ties and opaque palette zero");
    std::vector<Palette16> composePalette(53);for(int row=0;row<53;++row)for(int i=0;i<256;++i)composePalette[row][i]=std::uint16_t(row*256+i);
    std::vector<std::uint16_t> ccolors(2,5),cdepth{32766,65535},calpha(2,128);const auto depthBefore=cdepth;
    blitUnit(Bytes{7,0},2,1,{0,0,2,1},{0,0},{0,0,2,1},-1,1000,composePalette,2,1,ccolors,cdepth,calpha);
    require(ccolors==std::vector<std::uint16_t>({5,5})&&cdepth==depthBefore,"unit depth ties and transparency preserve planes");
    cdepth[0]=32767;blitUnit(Bytes{7,0},2,1,{0,0,2,1},{0,0},{0,0,2,1},-1,1000,composePalette,2,1,ccolors,cdepth,calpha);
    require(ccolors[0]==6663&&cdepth[0]==32767,"unit reads depth without writing it");
    std::vector<std::uint16_t> offsetColors(8),offsetDepth(8,65535),offsetAlpha(8,128);
    blitUnit(Bytes{7,0},2,1,{0,0,2,1},{0,0},{2,1,2,1},-1,1000,composePalette,4,2,offsetColors,offsetDepth,offsetAlpha);
    require(offsetColors[6]==6663&&offsetColors[0]==0,"blit placement is relative to clip origin");
    require(std::count(tile[0].coverage.begin(),tile[0].coverage.end(),1)==900,"TMP opaque base coverage retained");
    const auto red=originalHsvToRgb({0,255,255}),wrapRed=originalHsvToRgb({255,255,255}),yellow=originalHsvToRgb({42,255,255});
    require(red.r==255&&red.g==0&&red.b==0&&wrapRed.r==red.r&&wrapRed.g==red.g&&wrapRed.b==red.b,"HSV hue endpoint wraps");
    require(yellow.r==255&&yellow.g==252&&yellow.b==0,"HSV retains integer fraction below sector boundary");
    const auto grey=originalHsvToRgb({137,0,151});require(grey.r==151&&grey.g==151&&grey.b==151,"zero-saturation hue independence");
    const auto remapped=playerPalette(syntheticRaster,syntheticPalette,{90,0,0});
    require(remapped[1].r==128&&remapped[1].g==64&&remapped[1].b==32&&remapped[16].r==0&&remapped[31].b==0,"remap only replaces its sixteen slots");
    require(std::fegetround()==hostRounding,"player remap restores host rounding");
    auto shadow=rasterVoxelShadow(model.sections[0],voxelIdentity(),voxelIdentity(),{});
    require(shadow.pixels[128*256+127]==1&&shadow.pixels[128*256+128]==1&&std::count(shadow.pixels.begin(),shadow.pixels.end(),1)==2,"one occupied shadow column writes two pixels");
    Bytes solidStencil(65536,7);auto masked=rasterVoxelShadow(model.sections[0],voxelIdentity(),voxelIdentity(),{},{solidStencil,256,256,{0,0}});
    require(std::count(masked.pixels.begin(),masked.pixels.end(),1)==0,"nonzero staging pixels suppress shadow");
    require(std::fegetround()==hostRounding,"shadow projection restores host rounding");
    rejects([&]{rasterVoxelShadow(model.sections[0],voxelIdentity(),voxelIdentity(),{NAN,0,0});},"nonfinite shadow offset rejected");
    rejects([&]{rasterVoxelShadow(model.sections[0],voxelIdentity(),voxelIdentity(),{},{solidStencil,2,2,{}});},"shadow stencil plane mismatch rejected");
    rejects([&]{rasterVoxelShadow(model.sections[0],oversized,voxelIdentity(),{});},"shadow scratch bounds enforced");
    std::vector<std::uint16_t> shadowColors{65535,65535},shadowDepth{32766,65535};const auto untouchedDepth=shadowDepth;
    blitShadow(Bytes{1,0},2,1,{0,0,2,1},{0,0},{0,0,2,1},-1,2,1,shadowColors,shadowDepth);
    require(shadowColors==std::vector<std::uint16_t>({65535,65535})&&shadowDepth==untouchedDepth,"shadow tie/transparency preserves both planes");
    shadowDepth[0]=32767;blitShadow(Bytes{1,0},2,1,{0,0,2,1},{0,0},{0,0,2,1},-1,2,1,shadowColors,shadowDepth);
    require(shadowColors[0]==0x7bef&&shadowDepth[0]==32767,"shadow RGB565 half mask and depth read only");
    Palette duplicatePalette{};duplicatePalette[4]={2,1,1};duplicatePalette[9]=duplicatePalette[4];
    auto indexMap=stagingRemap(duplicatePalette,duplicatePalette);
    require(indexMap[0]==0&&indexMap[9]==4&&indexMap[7]==0,"staging maps duplicate colors to first palette entry");
    auto grown=stagingUnion({128,128,10,10},{138,138,1,1});
    require(grown.x==128&&grown.y==128&&grown.width==12&&grown.height==12,"dirty union extra right and bottom pixel");
    auto leftUnion=stagingUnion({128,128,10,10},{126,126,10,10});
    require(leftUnion.width==12&&leftUnion.height==12,"left and top extension has no extra pixel");
    auto unchanged=stagingUnion(grown,{0,0,0,1});require(unchanged.width==grown.width&&unchanged.x==grown.x,"empty part preserves dirty bounds");
    Bytes indexed{91,92};indexMap[1]=0;
    blitIndexed(Bytes{1,0},2,1,{0,0,2,1},{0,0},{0,0,2,1},indexMap,2,1,indexed);
    require(indexed==Bytes({0,92}),"nonzero remapped to zero erases earlier staging pixel; source zero transparent");
    rejects([&]{blitIndexed(Bytes{1},2,1,{},{},{},indexMap,2,1,indexed);},"invalid staging source rejected");
    rejects([&]{stagingUnion({2147483647,0,1,1},{});},"staging union bounds reject overflow");
    UnitStaging staged;RasterFrame part;part.rectangle={0,0,128,128,1,1};part.pixels[128*256+128]=4;
    staged.add(part,indexMap);require(staged.pixels[128*256+128]==4&&staged.dirty.x==128&&staged.dirty.width==1,"staging original center anchor");
    staged.clear();require(staged.dirty.width==0&&std::count(staged.pixels.begin(),staged.pixels.end(),0)==65536,"staging reset prevents prior frame trails");
    ShadowCache cache;int builds=0;
    auto buildShadow=[&]{RasterFrame f;f.traversal=++builds;return f;};
    auto result=cache.draw({2},buildShadow);
    require(result.built&&!result.bypass&&result.frame->traversal==1&&cache.size()==1&&cache.capacity()==10,"shadow miss builds then inserts and draws");
    result=cache.draw({2,false,false,false,true,false,false},buildShadow);
    require(!result.built&&result.frame&&builds==1,"cache hit allowed when rebuild is disabled");
    result=cache.draw({1,false,false,false,true,false,false},buildShadow);
    require(!result.frame&&cache.size()==1&&builds==1,"cacheable miss with build disabled does not draw");
    result=cache.draw({-1,false,false,false,true,false,false},buildShadow);
    require(result.built&&result.bypass&&cache.size()==1,"minus one bypass ignores build guard and preserves cache");
    result=cache.draw({3,false,false,false,true,true,false},buildShadow);
    require(result.bypass&&cache.size()==1,"DisableShadowCache forces direct render");
    result=cache.draw({3,false,false,false,false,false,false},buildShadow);
    require(result.bypass&&cache.size()==1,"absent cache forces direct render");
    const auto beforeBuilds=builds;
    require(!cache.draw({3,true},buildShadow).frame&&!cache.draw({3,false,true},buildShadow).frame&&!cache.draw({3,false,false,true},buildShadow).frame&&builds==beforeBuilds,"all three original shadow suppression guards precede cache lookup");
    cache.draw({-2147483647-1},buildShadow);cache.draw({2147483647},buildShadow);
    require(cache.keys()==std::vector<std::int32_t>({-2147483647-1,2,2147483647}),"shadow cache uses signed key ordering");
    for(int i=0;i<20;++i)cache.draw({i},buildShadow);
    require(cache.size()==22&&cache.capacity()==40&&cache.hotKey()==19,"shadow cache growth and hot key survive sorting");
    require(bodyVoxelKey(-1,3)==-1&&turretVoxelKey(-1,8192,0)==-1,"invalid locomotor key propagates to both lit keys");
    require(bodyVoxelKey(31,32)==992&&bodyVoxelKey(31,-1)==1023,"body key packs five low animation bits");
    require(bodyVoxelKey(2147483647,0)==-32&&bodyVoxelKey(-2147483647-1,1)==1,"body key shift wraps without signed overflow");
    require(turretVoxelKey(992,8192,0)==4&&turretVoxelKey(992,8192,1)==996,"zero turret offset removes body-heading bits");
    require(turretVoxelKey(992,1023,0)==0&&turretVoxelKey(992,1024,0)==1,"turret key preserves render heading ties");
    VoxelCache litCache;int litBuilds=0;
    auto buildLit=[&]{RasterFrame frame;frame.traversal=++litBuilds;return frame;};
    auto litResult=litCache.draw({2},buildLit);
    require(litResult.built&&!litResult.bypass&&litResult.frame->traversal==1&&litCache.size()==1&&litCache.capacity()==10&&!litCache.sorted()&&!litCache.hotKey(),"lit miss draws before snapshot insertion without recursive hit");
    litResult=litCache.draw({2,true,false,false},buildLit);
    require(!litResult.built&&litResult.frame->traversal==1&&litCache.sorted()&&litCache.hotKey()==2&&litBuilds==1,"lit warm lookup precedes model validation");
    require(!litCache.draw({9,true,false,false},buildLit).frame&&litBuilds==1&&litCache.hotKey()==2,"invalid model miss preserves hot cache and skips render");
    litCache.draw({1},buildLit);
    require(!litCache.sorted()&&litCache.hotKey()==2&&litCache.keys()==std::vector<std::int32_t>({2,1}),"lit append preserves existing hot entry and marks unsorted");
    litCache.draw({2},buildLit);
    require(!litCache.sorted()&&litBuilds==2,"hot hit skips sorting a dirty index");
    litCache.draw({1},buildLit);
    require(litCache.sorted()&&litCache.hotKey()==1&&litCache.keys()==std::vector<std::int32_t>({1,2}),"nonhot lookup sorts and selects the signed key");
    litCache.draw({-2147483647-1},buildLit);litCache.draw({2147483647},buildLit);litCache.draw({2},buildLit);
    require(litCache.keys()==std::vector<std::int32_t>({-2147483647-1,1,2,2147483647}),"lit index sorts signed endpoint keys");
    litResult=litCache.draw({-1},buildLit);
    require(litResult.bypass&&litResult.built&&litCache.size()==4,"minus one lit bypass renders without snapshot insertion");
    require(litCache.draw({2,false},buildLit).bypass&&litCache.draw({2,true,true},buildLit).bypass&&litCache.size()==4,"absent and disabled lit caches bypass warm entries");
    require(!litCache.draw({2,true,true,false},buildLit).frame,"invalid model bypass does not render");
    for(int key=10;key<16;++key)litCache.draw({key},buildLit);
    litCache.draw({2},buildLit);require(litCache.capacity()==10&&litCache.hotKey()==2,"lit capacity ten retains hot selection");
    litCache.draw({16},buildLit);
    require(litCache.capacity()==20&&litCache.size()==11&&!litCache.hotKey()&&!litCache.sorted(),"lit successful growth doubles capacity and clears hot entry");
    require(flatUnitShadowKey(0,0)==0&&flatUnitShadowKey(992,63488)==63519,"Track flat shadow identity differs from lit keys");
    require(flatUnitShadowKey(992,63488)==flatUnitShadowKey(1023,63488),"shadow seed drops body animation frame bits");
    require(flatUnitShadowKey(0,0,16,0)==0&&flatUnitShadowKey(0,0,-16,0)==0,"general shadow point packs five wrapped bits after subtracting sixteen");
    require(flatUnitShadowKey(-1,0)==2095104,"shadow key recovers actual ten-bit body seed rather than propagating lit invalidation");
    require(flatUnitShadowKey(0,1023)==0&&flatUnitShadowKey(0,1024)==1,"shadow matrix preserves visual heading ties");
    require(flatUnitShadowKey(32,2048,15,2)==2049&&flatUnitShadowKey(32,2048,15,0,true)==2049,"Wheel and BalloonHover take direct shadow seed branch");
    require(unitSpeedTypeDefault(-1,true)==1&&unitSpeedTypeDefault(-1,false)==2&&unitSpeedTypeDefault(3,true)==3,"Unit default selects Track for Crusher or Wheel otherwise, preserving explicit type");
    auto placement=footShadowPlacement({10,-10},{-3,4},true,1);
    require(placement&&placement->x==7&&placement->y==-6,"Foot adds the locomotor shadow screen offset");
    placement=footShadowPlacement({2147483647,-2147483647-1},{1,-1},true,1);
    require(placement&&placement->x==-2147483647-1&&placement->y==2147483647,"Foot screen location wraps at thirty-two bits");
    require(!footShadowPlacement({},{},false,1)&&!footShadowPlacement({},{},true,0)&&!footShadowPlacement({},{},true,2),"Foot requires locomotor and exact predicate byte one");
    TerrainLifecycle terrainLife;
    for(int x=49;x<=51;++x)for(int y=49;y<=51;++y)terrainLife.occupation.cells[{std::int16_t(x),std::int16_t(y)}]={};
    terrainLife.occupation.members[0]={{12928,12928,0},{7,7},-1,{0,0,1}};
    terrainLife.objects.actors[0]={{12928,12928,0},-1};terrainLife.actors[0]={};
    TerrainLifeServices services;
    services.groundHeight=[](auto){return 104;};services.placementAllowed=[](auto){return true;};
    services.projectWorld=[](auto){return std::array<std::int32_t,2>{0,1499};};services.screenOrigin={2147483647,-2147483647-1};
    bool refused=false;
    try{terrainLife.unlimbo(0,{12928,12928,105},services);}catch(const std::invalid_argument&){refused=true;}
    require(refused&&terrainLife.occupation.members.at(0).state.limbo==1&&terrainLife.objects.layers[2].count==0,
            "elevated Terrain profile guard precedes lifecycle mutation");
    require(terrainLife.unlimbo(0,{12928,12928,0},services)&&terrainLife.occupation.members.at(0).position.z==104,
            "native lifecycle prepares grounded placement");
    require(terrainLife.actors.at(0).screenX==0&&terrainLife.actors.at(0).screenY==1499,
            "native projection service survives wrapped tactical origin stores");
    terrainLife.occupation.members.at(0).position.z=105;
    refused=false;
    try{terrainLife.limbo(0,services);}catch(const std::invalid_argument&){refused=true;}
    require(refused&&terrainLife.occupation.members.at(0).state.onMap==1&&terrainLife.objects.layers[2].count==1,
            "nonground removal profile guard preserves prior registration");
    terrainLife.occupation.members.at(0).position.z=104;
    require(terrainLife.limbo(0,services)&&!terrainLife.limbo(0,services)&&terrainLife.objects.layers[2].count==0,
            "native lifecycle unregisters without rebuilding layer storage");
    std::cout<<checks<<" synthetic regression checks: PASS\n";
 } catch(const std::exception& e) {std::cerr<<"FAIL: "<<e.what()<<"\n";return 1;}
}
