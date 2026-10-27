// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/GameAssets.hpp"
#include "assets/PreparedData.hpp"
#include "assets/UnitTypeMetadata.hpp"
#include "assets/UnitModelInputs.hpp"
#include "assets/UnitFireAngle.hpp"
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <limits>

namespace ra2 {
int unitSpeedTypeDefault(int current,bool crusher) {return current==-1?(crusher?1:2):current;}
static std::string packedSection(const Ini& ini,const std::string& name) {
    std::map<int,std::string> rows;for(const auto& [k,v]:ini.section(name)) rows.emplace(std::stoi(k),v);
    std::string all;for(const auto& [k,v]:rows) all+=v;return all;
}
// Bounded Format80 reader, used only to conservatively exclude overlays from routes.
static Bytes lcw(const Data& d,std::size_t wanted) {
    Bytes out;std::size_t p=0;
    auto copy=[&](std::size_t from,std::size_t count) {
        if(from>=out.size()||count>wanted-out.size()) throw std::runtime_error("Invalid LCW copy");
        while(count--) out.push_back(out.at(from++));
    };
    while(p<d.size) {
        auto cmd=d.u8(p++);
        if(!(cmd&0x80)) {auto distance=((cmd&15)<<8)|d.u8(p++);if(std::size_t(distance)>out.size()) throw std::runtime_error("Invalid LCW distance");copy(out.size()-distance,((cmd>>4)&7)+3);}
        else if(!(cmd&0x40)) {auto count=cmd&63;if(!count) break;if(std::size_t(count)>wanted-out.size()) throw std::runtime_error("LCW output overflow");auto v=d.ptr(p,count);out.insert(out.end(),v,v+count);p+=count;}
        else if(cmd==0xfe) {auto count=d.u16(p);p+=2;auto value=d.u8(p++);if(count>wanted-out.size()) throw std::runtime_error("LCW fill overflow");out.insert(out.end(),count,value);}
        else {std::size_t count=(cmd&63)+3;if(cmd==0xff) {count=d.u16(p);p+=2;}auto from=d.u16(p);p+=2;copy(from,count);}
    }
    if(out.size()!=wanted) throw std::runtime_error("LCW output length mismatch");return out;
}
static VehiclePart loadPart(const AssetStore& store,const std::string& name) {
    VehiclePart p{readVxl(store.require(name+".vxl")),readHva(store.require(name+".hva"))};
    if(p.voxels.sections.size()!=p.animation.names.size()) throw std::runtime_error("VXL/HVA section mismatch: "+name);
    for(std::size_t i=0;i<p.voxels.sections.size();++i) if(lower(p.voxels.sections[i].name)!=lower(p.animation.names[i])) throw std::runtime_error("VXL/HVA name mismatch: "+name);
    return p;
}
GameAssets::GameAssets(const std::filesystem::path& root,const std::string& mapFile,const std::filesystem::path& directionFile,const std::filesystem::path& renderFile,const std::filesystem::path& rasterFile):store(root,AssetStore::Registration::InitialTemperate),mapName(mapFile) {
    const auto engine=store.require("game.exe");engineDataSource=verifiedEngineDataSource(engine);
    const auto prepared=[&](const std::filesystem::path& override,const char* name) {
        return readFile(override.empty()?preparedDataPath(engineDataSource,name):override);
    };
    driveData=readDriveData(engine,prepared(directionFile,"direction-data.bin"));
    renderData=readRenderData(prepared(renderFile,"render-data.bin"),engineDataSource);voxelPalette=readVpl(store.require("voxels.vpl"));
    rasterData=readRasterData(prepared(rasterFile,"raster-data.bin"),engineDataSource);
    Ini source(store.require(mapFile).text());map=readMap(source);
    terrainPalette=readPalette(store.require("isotem.pal"));unitPalette=readPalette(store.require("unittem.pal"));
    stagingPalette=readPalette(store.require("temperat.pal"));
    Ini rules(store.require("rules.ini").text());Ini art(store.require("art.ini").text());
    if(rules.get("AudioVisual","ExtraUnitLight").empty())throw std::runtime_error("Explicit ExtraUnitLight required for ordinary unit lighting");
    extraUnitLight=rules.number("AudioVisual","ExtraUnitLight");
    if(!rules.section("INGALITE").empty()) {
        for(const char* key:{"LightVisibility","LightIntensity","LightRedTint","LightGreenTint","LightBlueTint"})
            if(rules.get("INGALITE",key).empty())throw std::runtime_error("INGALITE requires explicit light settings");
        if(lower(rules.get("INGALITE","Image"))!="galite"||lower(rules.get("INGALITE","InvisibleInGame"))!="yes"||art.get("GALITE","Foundation")!="1x1")
            throw std::runtime_error("Unsupported INGALITE image/foundation profile");
        invisibleLight=StaticLightAsset{rules.integer("INGALITE","LightVisibility"),rules.number("INGALITE","LightIntensity"),
            {rules.number("INGALITE","LightRedTint"),rules.number("INGALITE","LightGreenTint"),rules.number("INGALITE","LightBlueTint")}};
    }
    for(const auto& [key,value]:source.section("Structures")) {
        std::istringstream in(value);std::string owner,type;
        std::getline(in,owner,',');std::getline(in,type,',');
        if(rules.number(type,"LightIntensity",0)==0&&source.number(type,"LightIntensity",0)==0)continue;
        hasPlacedLights=true;
        if(lower(type)!="ingalite"||placedLight||!source.section(type).empty())throw std::runtime_error("Only one stock INGALITE emitter is supported; type overrides require recovery");
        // Read only the numeric health/location prefix; later structure fields
        // include names and are not a reconstructed actor initialization path.
        std::string health,x,y;
        if(!std::getline(in,health,',')||!std::getline(in,x,',')||!std::getline(in,y,',')||std::stoi(health)!=256)throw std::runtime_error("Only a healthy static INGALITE is supported");
        placedLight=std::pair{std::stoi(x),std::stoi(y)};
    }
    for(const auto& [name,value]:rules.section("Colors")) {
        const auto hsv=integers(value);
        if(hsv.size()!=3||std::any_of(hsv.begin(),hsv.end(),[](int v){return v<0||v>255;}))throw std::runtime_error("Invalid rules player color: "+name);
        playerColors.emplace(name,HsvColor{std::uint8_t(hsv[0]),std::uint8_t(hsv[1]),std::uint8_t(hsv[2])});
    }
    rot=rules.integer("HTNK","ROT",-1);speed=rules.integer("HTNK","Speed",-1);
    const auto rhinoType=readUnitTypeMetadata(rules,art,"HTNK");
    requireOrdinaryRhinoMetadata(rhinoType);
    passive=rules.boolean("HTNK","Passive")!=0;
    auto yes=[&](const char* key){return rules.boolean("HTNK",key)!=0;};
    noShadow=yes("NoShadow");disableShadowCache=yes("DisableShadowCache");disableVoxelCache=yes("DisableVoxelCache");
    const auto speedType=lower(rules.get("HTNK","SpeedType"));
    if(yes("BalloonHover")||(!speedType.empty()&&speedType!="track")||
       (speedType.empty()&&unitSpeedTypeDefault(-1,yes("Crusher"))!=1))
        throw std::runtime_error("Only ordinary Track HTNK shadow/type profile is recovered");
    if(yes("UseTurretShadow")||art.integer("HTNK","ShadowIndex",0)!=0)throw std::runtime_error("Alternate HTNK shadow selection requires additional recovery");
    if(rot<=0||rot>127||speed<=0) throw std::runtime_error("Unsupported HTNK rules");
    std::string rhinoImage="htnk";
    if(engineDataSource==PatchedEngineSha) {
        unitDrawMetadata=readUnitDrawMetadata(rules,"HTNK");
        if(unitDrawMetadata.zFudgeCliff!=10||unitDrawMetadata.zFudgeColumn!=8||
           unitDrawMetadata.zFudgeTunnel!=13||unitDrawMetadata.zFudgeBridge!=0||
           unitDrawMetadata.tooBigToFitUnderBridge!=1||readUnitFireAngle(rules,"HTNK")!=8)
            throw std::runtime_error("Only stock HTNK drawing metadata/FireAngle are supported");
        const auto modelInputs=readUnitModelInputs(rules,art,"HTNK");
        requireOrdinaryRhinoModelInputs(modelInputs);
        rhinoImage=lower(modelImageString(modelInputs.image));
    } else if(art.integer("HTNK","TurretOffset",0)!=0)
        throw std::runtime_error("Nonzero HTNK TurretOffset requires additional recovery");
    body=loadPart(store,rhinoImage);turret=loadPart(store,rhinoImage+"tur");barrel=loadPart(store,rhinoImage+"barl");
    for(const auto* part:{&body,&turret,&barrel})if(part->animation.frames!=1)throw std::runtime_error("Animated HTNK actor frame/key timing requires additional recovery");
    for(const auto* part:{&body,&turret,&barrel})for(const auto& section:part->voxels.sections) {
        if(section.normalType<1||section.normalType>4)throw std::runtime_error("Unsupported voxel normal type");
        for(const auto& voxel:section.voxels)if(voxel.normal>=renderData.normals[section.normalType].size()&&voxel.normal<253)
            throw std::runtime_error("Voxel normal outside its original table");
    }
    Ini theater(store.require("temperat.ini").text());std::vector<std::string> filenames;
    for(int set=0;set<2048;++set) {
        char section[32];std::snprintf(section,sizeof(section),"TileSet%04d",set);
        if(theater.section(section).empty()) break;
        const int count=theater.integer(section,"TilesInSet",0);const auto prefix=theater.get(section,"FileName");
        if(count<0||count>10000) throw std::runtime_error("Invalid theater tile count");
        for(int t=1;t<=count;++t) {char suffix[32];std::snprintf(suffix,sizeof(suffix),"%02d.tem",t);filenames.push_back(prefix+suffix);}
    }
    for(std::size_t i=0;i<map.cells.size();++i) {
        auto& c=map.cells[i];if(c.tile==0xffff||c.tile==0xffffffffu) {c.tile=0;c.sub=0;}
        if(c.tile>=filenames.size()) throw std::runtime_error("Map tile outside theater table");
        if(!tiles.contains(c.tile)) tiles.emplace(c.tile,readTmp(store.require(filenames[c.tile])));
        if(c.sub>=tiles.at(c.tile).size() || tiles.at(c.tile)[c.sub].pixels.empty()) throw std::runtime_error("Missing map sub-tile");
        cellIndex.emplace(std::pair{c.x,c.y},i);
    }
    // The healthy ordinary scenery profile remains guarded. Other scenery still
    // uses conservative exclusions, without claiming original occupation.
    for(const auto& [key,value]:source.section("Terrain")) {
        const auto id=lower(value);
        const bool tree=id.size()==6&&id.substr(0,4)=="tree"&&id[4]>='0'&&id[4]<='9'&&id[5]>='0'&&id[5]<='9';
        if(tree) {
            const int type=(id[4]-'0')*10+id[5]-'0';
            if(type<1||type>28)throw std::runtime_error("Tree image/type is outside the verified stock TREE01..28 profile");
        } else if(std::find(stockStaticPropTypes().begin(),stockStaticPropTypes().end(),id)==stockStaticPropTypes().end())continue;
        const int n=std::stoi(key),x=n%1000,y=n/1000;
        if(!cell(x,y))throw std::runtime_error("Scenery outside prepared map cells");
        if(!sceneryImages.contains(id)) {
            auto flag=[&](const char* key){const auto v=lower(rules.get(id,key,"no"));return v=="yes"||v=="true"||v=="1";};
            if(rules.section(id).empty()||!source.section(id).empty()||flag("IsAnimated")||flag("SpawnsTiberium")||flag("IsVeinhole")||flag("WaterBound")||
               terrainStrengthDefault(rules.integer(id,"Strength",-1),rules.integer("General","TreeStrength",-1))<2||
               lower(art.get(id,"Theater"))!="yes"||art.get(id,"Foundation")!="1x1"||
               lower(rules.get(id,"Image",id))!=id||!art.get(id,"Image").empty())
                throw std::runtime_error("Only stock healthy static terrain types are recovered: "+id);
            const auto reload=terrainImageReload(id,true,false,0,true,0,-1);
            auto image=readShp(store.require(reload->filename));
            if(image.frames.size()!=2)throw std::runtime_error("Animated/damaged terrain images require additional recovery: "+id);
            sceneryImages.emplace(id,std::move(image));
        }
        scenery.push_back({x,y,id});
    }
    // Original object locations are conservative route exclusions, not simulated actors.
    for(const char* section:{"Terrain","Structures","Units","Infantry"}) for(const auto& [k,v]:source.section(section)) {
        int x=0,y=0;
        if(std::string(section)=="Terrain") {int n=std::stoi(k);x=n%1000;y=n/1000;}
        else {std::istringstream in(v);std::string f;std::vector<std::string> fields;while(std::getline(in,f,',')) fields.push_back(f);if(fields.size()<5) continue;x=std::stoi(fields[3]);y=std::stoi(fields[4]);}
        const int radius=std::string(section)=="Structures"?4:1;
        for(int dx=-radius;dx<=radius;++dx) for(int dy=-radius;dy<=radius;++dy) occupied.emplace(x+dx,y+dy);
    }
    const auto packed=packedSection(source,"OverlayPack");
    if(!packed.empty()) {
        Data d(decodeBase64(packed));Bytes expanded;std::size_t p=0;
        while(p<d.size) {auto in=d.u16(p),out=d.u16(p+2);p+=4;if(!in&&!out) break;if(out==0||out>8192||expanded.size()+out>512*512) throw std::runtime_error("Invalid OverlayPack block");auto block=lcw(d.slice(p,in),out);expanded.insert(expanded.end(),block.begin(),block.end());p+=in;}
        if(expanded.size()!=512*512) throw std::runtime_error("OverlayPack size mismatch");
        for(const auto& c:map.cells) if(c.x<512&&c.y<512&&expanded[std::size_t(c.y)*512+c.x]!=255) occupied.emplace(c.x,c.y);
    }
}
void GameAssets::prepareSceneryLifecycle(const TerrainLifeServices& services) {
    // Native construction/storage and map-load policy. Original Unlimbo/Mark/
    // layer transitions run in the SDL-free model; loading=1 deliberately
    // bypasses placement permission for the supplied map's existing actors.
    sceneryLifecycle={};sceneryLifecycle.loading=1;
    Ini rules(store.require("rules.ini").text());
    auto& world=sceneryLifecycle.occupation;
    for(const auto& c:map.cells)world.cells.try_emplace({std::int16_t(c.x),std::int16_t(c.y)});
    for(std::size_t i=0;i<scenery.size();++i) {
        const auto& placement=scenery[i];
        const TerrainOccupationType type{std::uint32_t(rules.integer(placement.type,"TemperateOccupationBits",7)),
                                         std::uint32_t(rules.integer(placement.type,"SnowOccupationBits",7))};
        const auto position=cellCenter(placement.x,placement.y,cell(placement.x,placement.y)->z*104);
        world.members.emplace(int(i),TerrainMember{position,type,-1,{0,0,1}});
        sceneryLifecycle.actors.emplace(int(i),TerrainLifeState{});
        sceneryLifecycle.objects.actors.emplace(int(i),ObjectLayerActor{position,-1});
        if(!sceneryLifecycle.unlimbo(int(i),position,services))throw std::runtime_error("Prepared scenery placement failed");
    }
    sceneryLifecycle.loading=0;
}
const MapCell* GameAssets::cell(int x,int y) const {auto it=cellIndex.find({x,y});return it==cellIndex.end()?nullptr:&map.cells[it->second];}
const TileImage& GameAssets::tile(const MapCell& c) const {return tiles.at(c.tile).at(c.sub);}
void GameAssets::prepareTerrainMap(int levelHeight,int bridgeHeight){
    if(preparedTerrain)throw std::runtime_error("Terrain already prepared");
    if(engineDataSource!=PatchedEngineSha||mapName!="mp03t4.map"||passive)
        throw std::runtime_error("Terrain mode requires supplied base 1.006, stock non-Passive HTNK and mp03t4.map");
    const Ini rules(store.require("rules.ini").text());
    if(rules.boolean("HTNK","Accelerates")||rules.boolean("HTNK","IsTrain"))throw std::runtime_error("Accelerating/train terrain movement requires recovery");
    auto prepared=std::make_shared<PreparedTerrainMap>(store,Ini(store.require(mapName).text()),
        readMapRuntimeData(readFile(preparedDataPath(engineDataSource,"map-runtime-data.bin"))),levelHeight,bridgeHeight);
    for(auto& c:map.cells){
        const auto* value=prepared->find(c.x,c.y);if(!value)throw std::runtime_error("Prepared Cell missing from display map");
        const auto& v=value->input;c.tile=v.tile==65535?0u:std::uint32_t(v.tile);c.sub=v.tile==65535?0:v.subTile;c.z=std::uint8_t(v.level);
        if(!tiles.contains(c.tile))tiles.emplace(c.tile,readTmp(store.require(prepared->filenames.at(c.tile))));
        if(c.sub>=tiles.at(c.tile).size()||tiles.at(c.tile)[c.sub].pixels.empty())throw std::runtime_error("Prepared display TMP is missing");
    }
    preparedTerrain=std::move(prepared);
}
bool GameAssets::clearTerrainCell(int x,int y) const{
    if(!preparedTerrain||occupied.contains({x,y}))return false;
    const auto* c=preparedTerrain->find(x,y);if(!c||c->overlay!=-1||c->input.tube!=-1||c->input.slope>20||(c->input.flags&0x100u))return false;
    const auto& v=c->input;if(v.land<0||v.land>=12||preparedTerrain->land[std::size_t(v.land)].speed[unsigned(LandSpeed::Track)]<=.01f)return false;
    const double u=(x-y+map.width-1)*.5,w=(x+y-map.width-1)*.5;const auto& b=map.local;
    return u>=b[0]&&w>=b[1]&&u<b[0]+b[2]&&w<b[1]+b[3];
}
bool GameAssets::clearCell(int x,int y,int z) const {
    auto c=cell(x,y);if(!c||c->z!=z||occupied.contains({x,y})) return false;
    const double u=(x-y+map.width-1)*0.5,v=(x+y-map.width-1)*0.5;
    const auto& bounds=map.local;
    if(u<bounds[0]||v<bounds[1]||u>=bounds[0]+bounds[2]||v>=bounds[1]+bounds[3]) return false;
    const auto& image=tile(*c);
    // Temporary whitelist, checked against the supplied road/grass/dirt templates.
    // These are raw TMP tags, NOT a recovered LandType or movement-zone mapping.
    return (image.terrain==11||image.terrain==13||image.terrain==14)&&image.ramp==0;
}
std::pair<int,int> GameAssets::spawn() const {
    auto desired=map.waypoints.contains(0)?map.waypoints.at(0):std::pair{map.width,map.height};
    int best=std::numeric_limits<int>::max();std::pair<int,int> result{-1,-1};
    for(const auto& c:map.cells) {
        const double u=(c.x-c.y+map.width-1)*0.5,v=(c.x+c.y-map.width-1)*0.5;
        const auto& bounds=map.local;
        if(u<bounds[0]+8||v<bounds[1]+6||u>=bounds[0]+bounds[2]-8||v>=bounds[1]+bounds[3]-6) continue;
        bool clear=true;for(int dx=-2;dx<=2;++dx) for(int dy=-2;dy<=2;++dy) clear&=clearCell(c.x+dx,c.y+dy,c.z);
        if(!clear) continue;int distance=(c.x-desired.first)*(c.x-desired.first)+(c.y-desired.second)*(c.y-desired.second);
        if(distance<best) {best=distance;result={c.x,c.y};}
    }
    if(result.first<0) throw std::runtime_error("No bounded clear-ground spawn found on this map");return result;
}
}
