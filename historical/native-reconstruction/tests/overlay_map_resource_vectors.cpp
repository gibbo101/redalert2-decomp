// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayMapPreparation.hpp"
#include "assets/OverlayMapResources.hpp"
#include "assets/ResourceMapInputs.hpp"
#include "assets/ResidentOverlayPreparation.hpp"
#include "render/Redraw.hpp"
#include <openssl/evp.h>
#include <array>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>
using namespace ra2;
namespace {
using Words=std::vector<std::uint32_t>;
unsigned packed(MapInputPosition p){return std::uint16_t(p.x)|(unsigned(std::uint16_t(p.y))<<16);}
MapInputPosition position(unsigned v){return {std::bit_cast<std::int16_t>(std::uint16_t(v)),std::bit_cast<std::int16_t>(std::uint16_t(v>>16))};}
std::string digest(const Words& words){
    std::vector<unsigned char> bytes;bytes.reserve(words.size()*4);for(auto v:words)for(int i=0;i<4;++i)bytes.push_back(static_cast<unsigned char>(v>>(i*8)));
    unsigned char result[EVP_MAX_MD_SIZE];unsigned size=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),result,&size,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream out;for(unsigned i=0;i<size;++i)out<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(result[i]);return out.str();
}
void state(Words& out,const TransientMapOverlay& a,const OverlayObjectBase& b){
    out.insert(out.end(),{a.identityToken,b.flags14,b.word18,b.word1C,b.byte20,unsigned(b.coord24.x),unsigned(b.coord24.y),unsigned(b.coord24.z)});
    out.insert(out.end(),b.links30.begin(),b.links30.end());
    for(unsigned i=0;i<2;++i){out.insert(out.end(),b.resources[i].begin(),b.resources[i].end());out.push_back(b.resourceTags[i]);}
    out.insert(out.end(),{unsigned(b.word64),b.byte68,unsigned(b.word6C),unsigned(b.word70),a.onMap,a.redraw,a.limbo});
    out.insert(out.end(),b.bytes77.begin(),b.bytes77.end());out.insert(out.end(),{a.active,unsigned(b.lastLayer),b.byte84,b.byte85,unsigned(a.position.x),unsigned(a.position.y),unsigned(a.position.z),b.word94,a.type?1u:0u});
}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;Words events;
        const auto event=[&](std::initializer_list<unsigned> v){events.insert(events.end(),v.begin(),v.end());};
        if(op=='B'){
            unsigned p=0;int w=0,h=0;in>>p>>w>>h;
            std::cout<<overlayMapPositionPermitted(position(p),w,h);
        }else if(op=='N'||op=='J'||op=='R'){
            struct ResourceRow {int key=0,length=0;unsigned base=0;int image=0,value=0;};
            std::vector<ResourceRow> resourceRows;
            if(op=='J'||op=='R'){
                unsigned count=0;in>>count;if(count>8)throw std::invalid_argument("Too many initialized resource rows");
                resourceRows.resize(count);
                for(auto& r:resourceRows)in>>r.key>>r.length>>r.base>>r.image>>r.value;
            }
            unsigned resourceCount=0,flagCount=0;in>>resourceCount;
            if(resourceCount>8)throw std::invalid_argument("Too many resource records");
            std::vector<MapResourceType> resources(resourceCount);
            for(auto& r:resources)in>>r.index>>r.imageIndex>>r.numImages>>r.numSlopes>>r.numFrames>>r.value;
            in>>flagCount;if(flagCount>255)throw std::invalid_argument("Too many resource type flags");
            std::vector<unsigned> flags(flagCount);for(auto& f:flags){in>>f;if(f>255)throw std::invalid_argument("Invalid resource type flag");}
            std::array<std::uint8_t,9> frames;for(auto& f:frames){unsigned n=0;in>>n;if(n>255)throw std::invalid_argument("Invalid resource frame");f=std::uint8_t(n);}

            unsigned seed=0,filter=0,typeLimit=0,dataLimit=0,divisor=0,dataMode=0,typeCount=0;
            int version=0,w=0,h=0,typeResult=0,dataResult=0;
            in>>seed>>version>>w>>h>>filter>>typeResult>>dataResult>>typeLimit>>dataLimit>>divisor>>dataMode>>typeCount;
            if(typeCount>255||typeLimit>262144||dataLimit>262144)throw std::invalid_argument("Overlay reader fixture domain");
            if(typeCount!=flagCount)throw std::invalid_argument("Resource flags differ from type registry");
            std::vector<OverlayTypeInputs> types(typeCount);unsigned typeIndex=0;
            for(auto& type:types){unsigned crate=0,demand=0;in>>type.image>>type.cellAnim>>crate>>demand>>type.land;unsigned wall=0;in>>wall;type.wall=std::uint8_t(wall);type.index=int(typeIndex++);type.crate=std::uint8_t(crate);type.demandLoad=std::uint8_t(demand);}
            for(unsigned i=0;i<typeCount;++i)types[i].tiberium=std::uint8_t(flags[i]);
            if(op=='J'||op=='R'){
                if(resourceCount)throw std::invalid_argument("Initialized resources require an empty diagnostic prefix");
                std::vector<ResourceTypeInputs> objects(resourceRows.size());unsigned allocated=0,selected=0;
                ResourceTypeRegistry primary,secondary;
                primary.slots.resize(resourceRows.size());secondary.slots.resize(resourceRows.size());
                ResourceListServices list;list.construction.currentFrame=seed;
                list.construction.base=[](auto& t,auto name){t.id=name;};
                list.construction.constructDebris=[](auto& d){d={};d.owns=1;};
                list.construction.clearDebris=[](auto& d){d.count=0;d.items.clear();};
                list.entry=[&](int i){selected=unsigned(i);const auto& r=resourceRows[selected];return ResourceListEntry{std::to_string(r.key),"Resource"+std::to_string(i),r.length};};
                list.numericKey=[&](auto){return resourceRows[selected].key;};
                list.allocate=[&](){return &objects.at(allocated++);};
                ResourceIniServices ini;ini.overlays=types;
                ini.base=[&](auto&){return std::uint8_t(resourceRows[selected].base)!=0;};
                ini.integer=[&](auto,auto key,int value){const auto& r=resourceRows[selected];return key=="Image"?r.image:key=="Value"?r.value:value;};
                ini.real=[](auto,auto,double value){return value;};ini.color=[](auto,int value){return value;};
                ini.debrisText=[](auto){return std::pair{0,std::string{}};};
                ini.copyDebris=[](const auto& d){return d;};ini.assignDebris=[](auto& d,const auto& copy){d=copy;};ini.releaseDebris=[](auto&){};
                list.readIni=[&](auto& t){return readResourceTypeIni(t,ini);};
                resources=readMapResourceTypes(int(resourceRows.size()),primary,secondary,list);
                resourceCount=unsigned(resources.size());Words selectedInputs{resourceCount};
                for(const auto& r:resources)selectedInputs.insert(selectedInputs.end(),{unsigned(r.index),unsigned(r.imageIndex),unsigned(r.numImages),unsigned(r.numSlopes),unsigned(r.numFrames),unsigned(r.value)});
                std::cout<<digest(selectedInputs)<<' ';
            }
            for(const auto& r:resources)if(r.index<0||unsigned(r.index)>=resourceCount||r.imageIndex<0||unsigned(r.imageIndex)>=typeCount||r.numFrames<=0)
                throw std::invalid_argument("Resource fixture registry domain");
            unsigned count=0;in>>count;if(count>16384)throw std::invalid_argument("Too many overlay fixture Cells");
            std::vector<OverlayPlacementCell> cells(count);std::unordered_map<unsigned,unsigned> binding;
            for(unsigned i=0;i<count;++i){unsigned index=0;in>>index;if(index>=262144||!binding.emplace(index,i).second)throw std::invalid_argument("Invalid overlay Cell binding");cells[i].position=position((index%512)|((index/512)<<16));cells[i].overlay=-1;cells[i].data=std::uint8_t(seed+i*37);}
            std::array<std::unordered_map<unsigned,std::uint8_t>,2> bytes;
            for(auto& stream:bytes){in>>count;if(count>262144)throw std::invalid_argument("Too many overlay stream overrides");for(unsigned i=0;i<count;++i){unsigned index=0,value=0;in>>index>>value;if(index>=262144||value>255||!stream.emplace(index,std::uint8_t(value)).second)throw std::invalid_argument("Invalid overlay byte override");}}
            OverlayPlacementCell fallback;fallback.position=position(0x12345678);fallback.overlay=-1;fallback.data=std::uint8_t(seed^0xa5);
            std::unordered_map<const MapWallCell*,unsigned> identities;for(unsigned i=0;i<cells.size();++i)identities[&cells[i]]=i;identities[&fallback]=0xffffffffu;
            const auto id=[&](const MapWallCell& c){return identities.at(&c);};
            const auto target=[&](MapInputPosition p)->OverlayPlacementCell&{const auto it=binding.find(unsigned(int(p.y)*512+int(p.x)));return it==binding.end()?fallback:cells[it->second];};
            std::array<unsigned,2> cursors{};unsigned attempts=0;
            unsigned enabled=0,capacity=0,owns=0,growResult=0;int growth=0;in>>enabled>>capacity>>growth>>owns>>growResult;
            if(!in||enabled>255||capacity>1024||growth<0||growth>1024||owns>255)throw std::invalid_argument("Overlay preparation storage domain");
            OverlayMapPreparationState prepared;prepared.identityCounter=seed^0xfedcba98;prepared.placementFlag=std::bit_cast<int>(seed);
            for(auto& r:prepared.registries){r.slots.resize(capacity);r.growth=growth;r.owns=std::uint8_t(owns);}
            OverlayMapPreparationInputs input;input.invalidCell=position(0x7fff7fff);input.invalidWorld={std::bit_cast<int>(seed),17,-19};input.resourceTag=1;input.initialFlags=seed;input.identityProvider=seed!=0;input.enabled=std::uint8_t(enabled);
            OverlayMapPreparationServices services;auto& s=services.reader;
            unsigned current=0,currentCell=0;std::vector<unsigned> freed;
            services.currentObject=[&](unsigned object){current=object;};
            s.section=[&](auto pack,unsigned capacity){const unsigned pass=unsigned(pack);const int result=pass?dataResult:typeResult;event({0,pass,capacity,unsigned(result)});return result;};
            s.read=[&](auto pack)->std::optional<std::uint8_t>{const unsigned pass=unsigned(pack),index=cursors[pass]++,limit=pass?dataLimit:typeLimit;const bool has=index<limit;unsigned value=pass?(dataMode?0:std::uint8_t(seed+index*37)):255;const auto it=bytes[pass].find(index);if(it!=bytes[pass].end())value=it->second;event({1,pass,index,unsigned(has),has?value:0});if(has)return std::uint8_t(value);return {};};
            services.placement.cell=[&](auto p)->OverlayPlacementCell&{event({6,packed(p)});auto& cell=target(p);if(&cell==&fallback){cell.position=p;event({7,packed(p)});}currentCell=id(cell);return cell;};
            s.allocate=[&](){const unsigned attempt=attempts++;const bool ok=!divisor||attempt%divisor;event({8,attempt,unsigned(ok)});return ok;};
            s.store=[&](auto& cell,auto value){event({21,id(cell),0x11e,1,value});};
            s.cleanup=[&](){event({11});};
            // Observe actual resident getter and permission requests without
            // substituting supplied results for their native computations.
            // The kernel itself emits these through the optional callbacks.
            s.imageQuery=[&](unsigned index){event({2,index});event({5,types[index].image});};
            s.permissionQuery=[&](auto p,bool result){event({3,packed(p)});event({4,unsigned(result)});};
            auto& life=services.lifetime;
            life.store=[&](unsigned role,unsigned off,unsigned size,unsigned value){if(!role)event({20,current,off,size,value});else event({22,role,off,size,value});};
            life.grow=[&](unsigned role,int amount){event({50,role,unsigned(amount),growResult});if(std::uint8_t(growResult)){auto& r=prepared.registries.at(role-1);r.slots.resize(unsigned(amount));r.owns=1;}return growResult;};
            life.expired=[&](unsigned object){event({61,object});};life.baseDestroy=[&](unsigned object){event({62,object});};
            life.free=[&](unsigned object){if(freed.size()<object)freed.resize(object);++freed.at(object-1);event({63,object});};
            life.rttiQuery=[&](unsigned object,unsigned kind){event({64,object,kind});};life.detachTag=[&](unsigned tag){event({60,tag});};
            auto& placement=services.placement;
            placement.noAttachedAnimation=[&]{event({32});};placement.redraw=[&]{event({33});};
            placement.store=[&](unsigned role,unsigned off,unsigned size,unsigned value){
                if(!role)event({20,current,off,size,value});else if(role==1)event({21,currentCell,off,size,value});
                else if(role==2)event({22,6,off,size,value});else event({20+role,0,size,value});
            };
            OverlayMapResourceInputs resourceInput{types,resources,frames,{MapInputPosition{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}}};
            OverlayMapResourceServices resourceServices;
            resourceServices.cell=placement.cell;
            resourceServices.classifyQuery=[&](int overlay){event({65,unsigned(overlay)});};
            resourceServices.missing=[&](int overlay){event({67,unsigned(overlay)});};
            resourceServices.store=[&](auto& c,std::uint8_t value){event({21,id(c),0x11e,1,value});};
            placement.resource=[&](auto& c){const auto i=id(c);event({51,i,0});const int amount=updateLoadedMapResource(c,resourceInput,resourceServices);currentCell=i;event({66,i,unsigned(amount)});};
            placement.recalculate=[&](auto& c,int level){currentCell=id(c);event({52,currentCell,unsigned(level)});c.passability=c.overlay!=-1;event({21,currentCell,0x4c,4,unsigned(c.passability)});};
            auto& wall=services.wall;wall.visits={0,2,4,6,-1};
            wall.directions={MapInputPosition{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};
            std::vector<std::uint8_t> wallTypes;for(const auto& t:types)wallTypes.push_back(t.wall);wall.wallTypes=wallTypes;
            wall.bounds=[&](const auto& c,unsigned kind){event({53,id(c),kind});return MapWallBounds{};};
            wall.unite=[](MapWallBounds a,MapWallBounds b){const auto r=unionDirtyBounds({a.x,a.y,a.width,a.height},{b.x,b.y,b.width,b.height});return MapWallBounds{r.x,r.y,r.width,r.height};};
            wall.dirty=[&](auto r){event({54,unsigned(r.x),unsigned(r.y),unsigned(r.width),unsigned(r.height)});};
            wall.notify=[&](auto p){event({55,packed(p)});};wall.expired=[&](auto& c){event({56,id(c)});};wall.zone=[&](unsigned kind,auto p){event({57,kind,packed(p)});};
            wall.store=[&](auto& c,unsigned off,unsigned size,unsigned value){event({21,id(c),off,size,value});};
            wall.recalculate=[&](MapWallCell& c,int level){placement.recalculate(static_cast<OverlayPlacementCell&>(c),level);};
            std::vector<MapCellAttributes> residentCells;
            MapCellAttributes residentFallback;
            std::vector<std::uint8_t> buffer4,buffer10;
            if(op=='R'){
                unsigned profile=0;in>>profile;if(profile>3)throw std::invalid_argument("Resident overlay fixture profile");
                residentCells.resize(cells.size());
                const auto initialize=[&](MapCellAttributes& a,OverlayPlacementCell& c,unsigned i){
                    a.overlay=c.overlay;a.overlayData=c.data;a.passability=c.passability;a.input.position=c.position;
                    a.input.tile=i%2?200:100;a.input.level=std::int8_t(i%7);a.input.slope=std::uint8_t(i%5);c.slope=a.input.slope;
                };
                for(unsigned i=0;i<cells.size();++i)initialize(residentCells[i],cells[i],i);
                initialize(residentFallback,fallback,7);residentFallback.input.tile=777;
                std::vector<MapCellInput*> table(262144);
                for(unsigned i=0;i<cells.size();++i)table[unsigned(int(cells[i].position.y)*512+int(cells[i].position.x))]=&residentCells[i].input;
                MapTileImageInput first,second,alternate;
                first.columns=first.rows=second.columns=second.rows=alternate.columns=alternate.rows=1;
                first.width=second.width=alternate.width=60;first.height=45;second.height=60;alternate.height=77;
                first.subTiles={MapSubTileInput{0,std::uint8_t(profile==1?5:1),false,0,0}};
                second.subTiles={MapSubTileInput{2,0,false,0,0}};alternate.subTiles={MapSubTileInput{6,4,false,0,0}};
                std::vector<MapTileAttributes> tiles(1024);for(auto& t:tiles)t.image=profile==2?nullptr:&alternate;
                tiles[100].image=profile==2?nullptr:&first;tiles[200].image=profile==2?nullptr:&second;
                std::array<int,16> landMap{};for(unsigned i=0;i<landMap.size();++i)landMap[i]=int(i%10);
                std::array<float,11> speeds;speeds.fill(1.0f);speeds[3]=0;
                std::vector<MapOverlayType> overlayTypes;
                for(unsigned i=0;i<types.size();++i){auto& t=types[i];t.noUseTileLandType=std::uint8_t(profile%2);t.crushable=std::uint8_t(i%3==0);
                    overlayTypes.push_back({t.land,t.crushable,t.wall,t.tiberium,t.noUseTileLandType,t.rubble,t.rock});}
                buffer4.resize(65536*4,0xa5);buffer10.resize(65536*10,0xa5);
                ResidentCellInputs resident;resident.world={table,&residentFallback.input,{},{}};
                resident.tiles=tiles;resident.landMap=landMap;resident.overlays=overlayTypes;resident.resources=resources;
                resident.wheelSpeeds=speeds;resident.permission={w,0,0,w,h};resident.directions=wall.directions;
                resident.lat={10,20,100,200,300,400,450,500,550,600,700,90,190,290,390};resident.cliffMode=profile==3?2:0;
                resident.world.query=[&](auto p){event({6,packed(p)});};
                resident.world.fallbackStore=[&](auto p){event({7,packed(p)});};
                ResidentOverlayServices joined;joined.overlay=services;
                joined.attributes=[&](auto& c)->MapCellAttributes&{const auto i=id(c);return i==0xffffffffu?residentFallback:residentCells.at(i);};
                joined.beforeResource=[&](auto& c,int argument){event({51,id(c),unsigned(argument)});};
                joined.afterResource=[&](auto& c,int amount){currentCell=id(c);event({66,currentCell,unsigned(amount)});};
                joined.beforeRecalculation=[&](auto& c,int level){currentCell=id(c);event({52,currentCell,unsigned(level)});};
                joined.classifyQuery=resourceServices.classifyQuery;joined.missingResource=resourceServices.missing;
                joined.attributeStore=[&](auto& c,MapAttributeField field,unsigned value){
                    currentCell=id(c);
                    constexpr std::array<unsigned,10> offsets{0x38,0x11a,0xec,0x11c,0x11b,0x11d,0,0,0x44,0x11e};
                    if(field==MapAttributeField::Buffer4||field==MapAttributeField::Buffer10){
                        const auto& a=joined.attributes(c);const unsigned i=unsigned(mapAttributeBufferIndex(a.input.position,w,h,65536));
                        event({68,unsigned(field==MapAttributeField::Buffer10),i,(value>>8)&255,value&255});
                    }else{const auto off=offsets[unsigned(field)];event({21,currentCell,off,unsigned(field==MapAttributeField::Tile||field==MapAttributeField::Land||field==MapAttributeField::Overlay?4:1),value});}
                };
                joined.passabilityStore=[&](auto& c,int value){currentCell=id(c);event({21,currentCell,0x4c,4,unsigned(value)});};
                prepareResidentMapOverlays(version,w,h,filter!=0,types,prepared,input,fallback,resident,frames,buffer4,buffer10,joined);
            }else prepareDecodedMapOverlays(version,w,h,filter!=0,types,prepared,input,services);
            Words output{cursors[0],cursors[1],attempts,unsigned(prepared.objects.size()),prepared.identityCounter,unsigned(prepared.placementFlag)};
            for(const auto& cell:cells)output.insert(output.end(),{packed(cell.position),unsigned(cell.overlay),unsigned(cell.passability),unsigned(cell.owner),cell.data,cell.neighbors});
            output.insert(output.end(),{packed(fallback.position),unsigned(fallback.overlay),unsigned(fallback.passability),unsigned(fallback.owner),fallback.data,fallback.neighbors});
            for(const auto& object:prepared.objects)state(output,object.actor,object.base);
            for(const auto& r:prepared.registries){output.insert(output.end(),{unsigned(r.count),unsigned(r.slots.size()),r.owns});output.insert(output.end(),r.slots.begin(),r.slots.end());}
            freed.resize(prepared.objects.size());output.insert(output.end(),freed.begin(),freed.end());
            if(op=='R'){
                for(const auto& a:residentCells)output.insert(output.end(),{unsigned(a.input.tile),unsigned(a.input.land),unsigned(std::uint16_t(a.input.tube)),
                    a.input.subTile,unsigned(std::uint8_t(a.input.level)),a.input.slope,a.input.flags,a.extraHeight,a.input.ice});
                const auto& a=residentFallback;output.insert(output.end(),{unsigned(a.input.tile),unsigned(a.input.land),unsigned(std::uint16_t(a.input.tube)),
                    a.input.subTile,unsigned(std::uint8_t(a.input.level)),a.input.slope,a.input.flags,a.extraHeight,a.input.ice});
                for(const auto* bytes:{&buffer4,&buffer10})for(unsigned i=0;i<bytes->size();i+=4)
                    output.push_back(unsigned((*bytes)[i])|(unsigned((*bytes)[i+1])<<8)|(unsigned((*bytes)[i+2])<<16)|(unsigned((*bytes)[i+3])<<24));
            }
            std::cout<<digest(output)<<' '<<digest(events);
        }else throw std::invalid_argument("Unknown overlay loading command");
        if(!in)throw std::invalid_argument("Incomplete overlay loading command");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing overlay loading command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
