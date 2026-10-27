// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/PreparedTerrainMap.hpp"
#include "assets/PreparedData.hpp"
#include "assets/MapGeometry.hpp"
#include "assets/MapCoordinateCell.hpp"
#include "assets/TileImagePreparation.hpp"
#include "assets/ResourceMapInputs.hpp"
#include <algorithm>
#include <bit>
#include <cmath>
#include <cstdio>
#include <sstream>
#include <set>
namespace ra2 {
namespace {
std::string packed(const Ini& ini,const char* section){
    std::map<int,std::string> rows;for(const auto& [key,value]:ini.section(section))rows.emplace(std::stoi(key),value);
    std::string out;for(const auto& [key,value]:rows)out+=value;return out;
}
Bytes overlayStream(const Ini& source,const char* section,std::uint8_t fill){
    const auto text=packed(source,section);if(text.empty())return Bytes(262144,fill);
    Data data(decodeBase64(text));Bytes out;std::size_t at=0;
    while(at<data.size){
        const auto size=data.u16(at),wanted=data.u16(at+2);at+=4;if(!size&&!wanted)break;
        if(!wanted||wanted>8192||out.size()+wanted>262144)throw std::runtime_error("Invalid overlay block");
        const auto d=data.slice(at,size);at+=size;Bytes block;std::size_t p=0;
        const auto copy=[&](std::size_t from,std::size_t count){
            if(from>=block.size()||count>wanted-block.size())throw std::runtime_error("Invalid overlay copy");
            while(count--)block.push_back(block.at(from++));
        };
        while(p<d.size){
            const auto op=d.u8(p++);
            if(!(op&128)){const auto distance=((op&15)<<8)|d.u8(p++);if(std::size_t(distance)>block.size())throw std::runtime_error("Invalid overlay distance");copy(block.size()-distance,((op>>4)&7)+3);}
            else if(!(op&64)){const auto n=op&63;if(!n)break;if(std::size_t(n)>wanted-block.size())throw std::runtime_error("Overlay literal overflow");const auto* v=d.ptr(p,n);block.insert(block.end(),v,v+n);p+=n;}
            else if(op==254){const auto n=d.u16(p);p+=2;const auto v=d.u8(p++);if(n>wanted-block.size())throw std::runtime_error("Overlay fill overflow");block.insert(block.end(),n,v);}
            else{std::size_t n=(op&63)+3;if(op==255){n=d.u16(p);p+=2;}const auto from=d.u16(p);p+=2;copy(from,n);}
        }
        if(block.size()!=wanted)throw std::runtime_error("Overlay block length differs");out.insert(out.end(),block.begin(),block.end());
    }
    if(out.size()!=262144)throw std::runtime_error("Overlay stream length differs");return out;
}
int landValue(const std::string& text){
    const auto id=lower(text);for(unsigned i=0;i<landSections.size();++i)if(lower(landSections[i])==id)return int(i);
    throw std::runtime_error("Unknown overlay Land value: "+text);
}
std::vector<std::pair<std::string,std::string>> declaredList(const Ini& rules,const std::string& text,const char* section){
    // Ini's value map is sorted; registry order must instead follow source key
    // enumeration. Gaps in OverlayTypes keys do not create registry slots.
    std::vector<std::pair<std::string,std::string>> out;std::set<std::string> seen;std::istringstream in(text);std::string line;bool active=false;
    const auto trim=[](std::string v){const auto a=v.find_first_not_of(" \t\r");return a==std::string::npos?std::string{}:v.substr(a,v.find_last_not_of(" \t\r")-a+1);};
    while(std::getline(in,line)){line=trim(line.substr(0,line.find(';')));if(line.empty())continue;
        if(line.front()=='['){active=lower(line)=="["+lower(section)+"]";continue;}
        if(!active)continue;const auto end=line.find('=');if(end==std::string::npos)continue;const auto key=trim(line.substr(0,end));
        if(!seen.insert(key).second)throw std::runtime_error("Repeated type-list keys require further parser association");
        out.emplace_back(key,rules.get(section,key));
    }
    if(out.size()!=rules.section(section).size())throw std::runtime_error("Type-list source enumeration differs");
    return out;
}
}
MapRuntimeData readMapRuntimeData(const Data& data){
    validatePreparedData(data,940,"","78b9bebc9ee7f9078619e05503fbce387b72e3ac20df84af3537e3462aee39f2",PatchedEngineSha);
    MapRuntimeData out;for(unsigned i=0;i<16;++i)out.landMap[i]=data.i32(40+i*4);
    for(unsigned i=0;i<9;++i)out.frames[i]=data.u8(104+i*4);
    std::size_t at=140;for(auto& plane:out.floor.planes)for(double* v:{&plane.x,&plane.y,&plane.offset,&plane.limit,&plane.add}){
        *v=std::bit_cast<double>(std::uint64_t(data.u32(at))|(std::uint64_t(data.u32(at+4))<<32));at+=8;
    }
    return out;
}
PreparedTerrainMap::PreparedTerrainMap(const AssetStore& store,const Ini& source,const MapRuntimeData& data,int stockHeight,int bridge,PreparedTerrainMapPolicy policy)
    :initialFloor(data.floor),levelHeight(stockHeight),bridgeHeight(bridge){
    if(stockHeight!=104||bridge!=416)throw std::runtime_error("Prepared terrain requires verified stock geometry");
    cellTagsDeferred=policy.deferCellTags&&!source.section("CellTags").empty();
    const auto decoded=readMap(source);const auto rulesText=store.require("rules.ini").text();const Ini rules(rulesText),art(store.require("art.ini").text());
    if(!source.section("Tubes").empty()||(!policy.deferCellTags&&!source.section("CellTags").empty()))throw std::runtime_error("Tubes/attached Cell tags require further map recovery");
    uphill=rules.number("General","TrackedUphill",1);downhill=rules.number("General","TrackedDownhill",1.2);
    if(!std::isfinite(uphill)||!std::isfinite(downhill)||uphill<0||downhill<0)throw std::runtime_error("Unsupported tracked slope factors");
    const Ini ini(store.require("temperat.ini").text());std::vector<TheaterTileSetInput> sets;std::array<int,16> numbers;
    for(unsigned i=0;i<numbers.size();++i)numbers[i]=ini.integer("General",theaterDepthKeys[i],-1);
    for(int i=0;i<1024;++i){
        char name[32];std::snprintf(name,sizeof(name),"TileSet%04d",i);TheaterTileSetInput s;
        s.count=ini.integer(name,"TilesInSet",-1);s.lastCount=ini.integer(name,"LastTilesInSet",-1);
        s.shadowCaster=ini.boolean(name,"ShadowCaster")!=0;s.shadowTiles=ini.integer(name,"ShadowTiles");
        if(s.count!=-1&&(s.count<0||s.count>10000||s.shadowCaster||!ini.get(name,"TileAnimation").empty()||(s.lastCount!=-1&&s.lastCount!=s.count)))
            throw std::runtime_error("Tile animation/shadow/shift requires further runtime association");
        if(s.count!=-1){const auto prefix=ini.get(name,"FileName");if(prefix.empty())throw std::runtime_error("Missing theater prefix");
            for(int j=1;j<=s.count;++j){char suffix[32];std::snprintf(suffix,sizeof(suffix),"%02d.tem",j);filenames.push_back(prefix+suffix);}}
        sets.push_back(s);if(s.count==-1)break;
    }
    theater=prepareTheaterTileInputs(numbers,sets);tileImages.resize(theater.types.size());tiles.resize(tileImages.size());
    for(std::size_t i=0;i<tileImages.size();++i)tileImages[i].filename=filenames.at(i);
    // Primary-image selection remains supplied. Only source-referenced images
    // and the original default tile are resident; no RNG/alternate substitution.
    const auto load=[&](unsigned n){if(n>=tileImages.size())throw std::runtime_error("Map tile outside prepared theater");
        if(!tiles[n].image){auto& type=tileImages[n];type.image=store.require(type.filename);type.prepared=prepareTileImage(*type.image);tiles[n].image=&type.prepared->image;}};
    load(0);for(const auto& c:decoded.cells)if(c.tile!=65535&&c.tile!=0xffffffffu)load(c.tile);
    LandCharacteristicServices landServices;
    landServices.hasSection=[&](unsigned i){if(rules.section(landSections[i]).empty())throw std::runtime_error("Missing stock land section");return true;};
    landServices.readSpeed=[&](unsigned i,LandSpeed s,double fallback){return rules.number(landSections[i],landSpeedKeys[unsigned(s)],fallback);};
    landServices.readBuildable=[&](unsigned i,std::uint8_t fallback){return rules.boolean(landSections[i],"Buildable",fallback);};
    loadLandCharacteristics(land,landServices);
    const auto rows=declaredList(rules,rulesText,"OverlayTypes");overlayInputs.resize(rows.size());overlayImages.resize(rows.size());overlayImageOwned.resize(rows.size());
    OverlayTypeRegistry registry;registry.slots.resize(rows.size());OverlayConstructionServices construction;
    construction.base=[](auto& t,std::string_view name){t.id=name;t.imageName=name;};
    for(std::size_t i=0;i<rows.size();++i){
        const auto& name=rows[i].second;if(name.empty())throw std::runtime_error("Empty stock overlay ID");
        if(!source.section(name).empty())throw std::runtime_error("Map overlay type overrides require further association");
        auto& t=overlayInputs[i];constructOverlayType(t,name,registry,construction);
        OverlayIniServices read;
        read.base=[&](auto& v){v.crushable=rules.boolean(v.id,"Crushable");v.imageName=rules.get(v.id,"Image",v.id);v.theater=art.boolean(v.imageName,"Theater");v.newTheater=art.boolean(v.imageName,"NewTheater");return true;};
        read.integer=[&](bool a,std::string_view name,std::string_view key,int fallback){
            if(key=="Land"){const auto value=rules.get(std::string(name),"Land");return value.empty()?fallback:landValue(value);}
            return (a?art:rules).integer(std::string(name),std::string(key),fallback);
        };
        read.boolean=[&](bool a,std::string_view name,std::string_view key,std::uint8_t fallback){return (a?art:rules).boolean(std::string(name),std::string(key),fallback);};
        read.cellAnimation=[&](std::string_view name){const auto value=rules.get(std::string(name),"CellAnim");if(!value.empty())throw std::runtime_error("Overlay animation requires further association");return std::pair{0,std::string{}};};
        read.loadImage=[](std::string_view){return 0u;}; // Presence irrelevant to this prepared-cell-only profile.
        readOverlayTypeIni(t,read);overlays.push_back({t.land,t.crushable,t.wall,t.tiberium,t.noUseTileLandType,t.rubble,t.rock});
    }
    const auto resourceRows=declaredList(rules,rulesText,"Tiberiums");std::vector<ResourceTypeInputs> resourceInputs(resourceRows.size());
    ResourceTypeRegistry resources,secondary;resources.slots.resize(resourceInputs.size());secondary.slots.resize(resourceInputs.size());
    ResourceListServices list;std::size_t allocated=0;
    list.entry=[&](int i){const auto& [key,name]=resourceRows.at(std::size_t(i));return ResourceListEntry{key,name,int(name.size())};};
    list.numericKey=[](std::string_view key){return std::stoi(std::string(key));};list.allocate=[&]{return &resourceInputs.at(allocated++);};
    list.construction.base=[](auto& t,std::string_view name){t.id=name;};list.construction.constructDebris=[](auto&){};list.construction.clearDebris=[](auto&){};
    list.readIni=[&](ResourceTypeInputs& t){
        const auto& override=source.section(t.id);
        if(!override.empty()&&(!policy.resourceValueOverrides||override.size()!=1||!override.contains("value")))
            throw std::runtime_error("Map resource overrides require further association");
        ResourceIniServices s;s.base=[](auto&){return true;};s.overlays=overlayInputs;
        s.integer=[&](std::string_view name,std::string_view key,int fallback){
            const auto section=std::string(name),field=std::string(key);
            const int value=rules.integer(section,field,fallback);
            return policy.resourceValueOverrides&&key=="Value"?source.integer(section,field,value):value;
        };
        s.real=[&](std::string_view name,std::string_view key,double fallback){return rules.number(std::string(name),std::string(key),fallback);};
        s.color=[](std::string_view,int fallback){return fallback;}; // Unused by map amount/depth.
        s.debrisText=[](std::string_view){return std::pair{0,std::string{}};};s.copyDebris=[](const auto& v){return v;};
        s.assignDebris=[](auto& a,const auto& b){a=b;};s.releaseDebris=[](auto&){};return readResourceTypeIni(t,s);
    };
    resourceTypes=readMapResourceTypes(int(resourceRows.size()),resources,secondary,list);
    const auto geometry=initialMapGeometry({0,0,decoded.width,decoded.height});cells.resize(geometry.positions.size());table.assign(262144,nullptr);slots.assign(262144,-1);
    for(std::size_t i=0;i<cells.size();++i){auto& v=cells[i].attributes.input;resetMapCellInput(v,{-1,-1});v.position=geometry.positions[i];
        const auto slot=std::size_t(v.position.y)*512+std::size_t(v.position.x);table[slot]=&v;slots[slot]=int(i);}
    resetMapCellInput(initialFallback.input,{-1,-1});
    auto raw=unpackMap(decodeBase64(packed(source,"IsoMapPack5")));const auto count=decoded.cells.size();
    if(raw.size()==count*11)raw.insert(raw.end(),4,255);
    const Data stream(raw);const auto term=stream.u32(count*11);
    loadIsoMapCellInputs(raw,table,initialFallback.input,{std::bit_cast<std::int16_t>(std::uint16_t(term)),std::bit_cast<std::int16_t>(std::uint16_t(term>>16))},{-1,-1},theater.shifts);
    // The recovered map reader applies theater shifts to the stored tile index.
    // Resident metadata and radar must resolve that final index, not only the
    // raw IsoMap references loaded above. This is still explicit host startup;
    // it does not reproduce the original type/usage/alternate loading schedule.
    for(const auto& c:cells)if(c.attributes.input.tile!=65535)load(c.attributes.input.tile);
    const auto indexes=overlayStream(source,"OverlayPack",255),values=overlayStream(source,"OverlayDataPack",0);
    for(auto& c:cells){const auto& p=c.attributes.input.position;const auto slot=std::size_t(p.y)*512+std::size_t(p.x);
        const auto index=indexes[slot];if(index!=255){if(index>=overlays.size())throw std::runtime_error("Overlay index outside stock registry");c.attributes.overlay=index;}
        c.attributes.overlayData=values[slot];}
    landMap=data.landMap;
    ResidentCellInputs resident;resident.world={table,&initialFallback.input,{},{}};resident.tiles=tiles;resident.landMap=landMap;resident.overlays=overlays;resident.resources=resourceTypes;
    for(unsigned i=0;i<11;++i)wheelSpeeds[i]=land[i].speed[unsigned(LandSpeed::Wheel)];resident.wheelSpeeds=wheelSpeeds;
    std::copy_n(theater.depthBases.begin(),15,resident.lat.begin());
    for(int i=0;i<8;++i){const auto [x,y]=directionOffset(i);resident.directions[std::size_t(i)]={std::int16_t(x),std::int16_t(y)};}
    resident.permission={decoded.width,decoded.local[0],decoded.local[1],decoded.local[2],decoded.local[3]};
    const auto cliff=rules.integer("General","CliffBackImpassability",2);if(cliff<0||cliff>2)throw std::runtime_error("Unsupported cliff mode");resident.cliffMode=std::uint8_t(cliff);
    width=decoded.width;height=decoded.height;membershipResident=resident;
    MapFinalizationInputs input{width,height,slots,resident,data.frames,{}};
    const auto allocation=mapGeometryAllocation(width,height);buffer4.resize(allocation.attributeBytes);buffer10.resize(allocation.secondaryBytes);initializeMapGeometryBuffer(buffer4);
    lightingLevels.resize(cells.size());
    MapFinalizationServices services;services.initializeLighting=[&](int id){lightingLevels[std::size_t(id)]=cells[std::size_t(id)].attributes.input.level;}; // Renderer owns light/converter records.
    finalizeResidentMap(input,cells,initialFallback,buffer4,buffer10,services);
    // LAT may select a different tile during finalization (Day1 selects
    // Rmpfx10.tem). Preserve the recovered saved-old-type recalculation order;
    // install the final references for subsequent consumers without recalculating
    // the Cells or replaying startup. The host residency schedule is supplied.
    for(const auto& c:cells)if(c.attributes.input.tile!=65535)load(c.attributes.input.tile);
}
OverlayImageResult PreparedTerrainMap::demandOverlayImage(const AssetStore& store,int id,int requestedTheater){
    if(id<0||std::size_t(id)>=overlayInputs.size())throw std::invalid_argument("Overlay image type outside registry");
    OverlayImageServices services;
    services.load=[&](const std::string& filename){auto data=store.find(filename);return OverlayImageResult{data?std::uint32_t(id+1):0u,std::move(data)};};
    services.finish=[]{}; // Host immutable Data/RAII replaces temporary original file objects.
    return ensureOverlayImage(overlayInputs[std::size_t(id)],overlayImages[std::size_t(id)],overlayImageOwned[std::size_t(id)],requestedTheater,services);
}
void PreparedTerrainMap::initializeOverlayImage(const AssetStore& store,int id,int requestedTheater){
    if(id<0||std::size_t(id)>=overlayInputs.size())throw std::invalid_argument("Overlay startup type outside registry");
    OverlayStartupServices services;
    services.release=[](std::uint32_t){}; // Immutable Data is released by native shared ownership below.
    services.cachedImage=[&](const std::string& filename){auto data=store.find(filename);return OverlayImageResult{data?std::uint32_t(id+1):0u,std::move(data)};};
    ra2::initializeOverlayImage(overlayInputs[std::size_t(id)],overlayImages[std::size_t(id)],overlayImageOwned[std::size_t(id)],requestedTheater,services);
}
UnitMapSeed PreparedTerrainMap::unitSeed()const{return {cells,slots,initialFallback,initialFloor,membershipResident,buffer4,buffer10,width,height,levelHeight};}
const MapCellAttributes* PreparedTerrainMap::find(int x,int y) const{
    if(x<0||y<0||x>=512||y>=512)return nullptr;const auto i=slots[std::size_t(y)*512+std::size_t(x)];
    return i<0?nullptr:&cells[std::size_t(i)].attributes;
}
TerrainMapView::TerrainMapView(std::shared_ptr<const PreparedTerrainMap> map):map_(std::move(map)),floorState(map_->initialFloor),fallback(map_->initialFallback){}
MapFloorHeightWorld TerrainMapView::world(){return {map_->table,&fallback.input,{}};}
const MapCellInput& TerrainMapView::coordinate(Coord p){return mapCoordinateCell(p,world(),262144);}
const MapCellAttributes& TerrainMapView::cell(MapInputPosition p){
    const auto& found=mapAttributeCell(p,{map_->table,&fallback.input,{},{}});if(&found==&fallback.input)return fallback;
    return *map_->find(found.position.x,found.position.y);
}
int TerrainMapView::floor(Coord p){return mapFloorHeight(floorState,map_->levelHeight,p,world());}
int TerrainMapView::relative(Coord p){return relativeMapHeight(floorState,map_->levelHeight,p,0,map_->bridgeHeight,world());}
GroundDriveProcessServices TerrainMapView::movementServices(const std::function<void(const MapCellInput&)>& check){
    // The returned callbacks retain their terrain binding; callers also retain
    // this view. Mark/admission/occupation/mission effects are preserving adapters.
    auto binding=std::make_shared<PreparedDriveTerrain>(floorState,map_->levelHeight,world(),check);
    GroundDriveProcessServices s;s.advance.ground.mark=[](int){};s.advance.unmarkOccupation=[](Coord){};
    s.advance.notify=[](int){};s.advance.postCell=[]{};s.reserve=s.markNext=[](auto,auto){};
    s.markOccupation=[](Coord){};s.admit=[](const auto&,int,int){};s.noRoute=[]{};
    s.uphill=map_->uphill;s.downhill=map_->downhill;for(unsigned i=0;i<12;++i)s.trackSpeed[i]=map_->land[i].speed[unsigned(LandSpeed::Track)];
    auto out=binding->bind(s);auto retain=out.cell;out.cell=[binding,retain](Coord p){return retain(p);};return out;
}
}
