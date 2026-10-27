// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayMapPreparation.hpp"
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
        }else if(op=='M'){
            unsigned seed=0,filter=0,typeLimit=0,dataLimit=0,divisor=0,dataMode=0,typeCount=0;
            int version=0,w=0,h=0,typeResult=0,dataResult=0;
            in>>seed>>version>>w>>h>>filter>>typeResult>>dataResult>>typeLimit>>dataLimit>>divisor>>dataMode>>typeCount;
            if(typeCount>255||typeLimit>262144||dataLimit>262144)throw std::invalid_argument("Overlay reader fixture domain");
            std::vector<OverlayTypeInputs> types(typeCount);unsigned typeIndex=0;
            for(auto& type:types){unsigned crate=0,demand=0;in>>type.image>>type.cellAnim>>crate>>demand>>type.land;unsigned wall=0;in>>wall;type.wall=std::uint8_t(wall);type.index=int(typeIndex++);type.crate=std::uint8_t(crate);type.demandLoad=std::uint8_t(demand);}
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
            placement.resource=[&](auto& c){const auto i=id(c);event({51,i,0});c.data=std::uint8_t(unsigned(c.overlay)*3+seed);event({21,i,0x11e,1,c.data});};
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
            prepareDecodedMapOverlays(version,w,h,filter!=0,types,prepared,input,services);
            Words output{cursors[0],cursors[1],attempts,unsigned(prepared.objects.size()),prepared.identityCounter,unsigned(prepared.placementFlag)};
            for(const auto& cell:cells)output.insert(output.end(),{packed(cell.position),unsigned(cell.overlay),unsigned(cell.passability),unsigned(cell.owner),cell.data,cell.neighbors});
            output.insert(output.end(),{packed(fallback.position),unsigned(fallback.overlay),unsigned(fallback.passability),unsigned(fallback.owner),fallback.data,fallback.neighbors});
            for(const auto& object:prepared.objects)state(output,object.actor,object.base);
            for(const auto& r:prepared.registries){output.insert(output.end(),{unsigned(r.count),unsigned(r.slots.size()),r.owns});output.insert(output.end(),r.slots.begin(),r.slots.end());}
            freed.resize(prepared.objects.size());output.insert(output.end(),freed.begin(),freed.end());
            std::cout<<digest(output)<<' '<<digest(events);
        }else throw std::invalid_argument("Unknown overlay loading command");
        if(!in)throw std::invalid_argument("Incomplete overlay loading command");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing overlay loading command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
