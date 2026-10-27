// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayPlacement.hpp"
#include "render/Redraw.hpp"
#include <openssl/evp.h>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
using Words=std::vector<std::uint32_t>;
std::string digest(const Words& values){
    std::vector<unsigned char> bytes;for(auto n:values)for(unsigned i=0;i<4;++i)bytes.push_back(static_cast<unsigned char>(n>>(8*i)));
    unsigned char hash[EVP_MAX_MD_SIZE];unsigned length=0;if(!EVP_Digest(bytes.data(),bytes.size(),hash,&length,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream out;for(unsigned i=0;i<length;++i)out<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(hash[i]);return out.str();
}
int signedWord(unsigned n){return std::bit_cast<std::int32_t>(n);}
MapInputPosition point(unsigned p){return {std::bit_cast<std::int16_t>(std::uint16_t(p)),std::bit_cast<std::int16_t>(std::uint16_t(p>>16))};}
unsigned packed(MapInputPosition p){return std::uint16_t(p.x)|(unsigned(std::uint16_t(p.y))<<16);}
void append(Words& values,MapWallBounds r){values.insert(values.end(),{unsigned(r.x),unsigned(r.y),unsigned(r.width),unsigned(r.height)});}
void occupants(std::istream& in,std::vector<MapWallOccupant>& out,unsigned n){
    if(n>8)throw std::invalid_argument("Wall occupant count");
    out.resize(n);for(auto& o:out)in>>o.kind>>o.health>>o.type;
}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;Words events;
        const auto event=[&](std::initializer_list<unsigned> v){events.insert(events.end(),v.begin(),v.end());};
        WallConnectionInputs connections;std::vector<OverlayPlacementCell> cells;std::vector<std::vector<MapWallOccupant>> nodes;
        const auto id=[&](const MapWallCell& c){for(unsigned i=0;i<cells.size();++i)if(&c==&cells[i])return i;throw std::runtime_error("Wall Cell identity");};
        connections.connectionQuery=[&](const auto& c,int target,int facing){event({6,id(c),unsigned(target),unsigned(facing)});};
        connections.occupantQuery=[&](const auto& c,unsigned index){event({7,id(c),index,unsigned(c.occupants[index].kind)});};
        unsigned slope=0,enabled=0,limbo=0,onMap=0,redraw=0,active=0,pActor=0,invalid=0,owns=0,growResult=0;
        int index=0,flag=0,incoming=0,owner=0,capacity=0,count=0,growth=0;
        in>>index>>slope>>enabled>>limbo>>onMap>>redraw>>active>>pActor>>invalid>>flag>>incoming>>owner>>capacity>>count>>growth>>owns>>growResult;
        if(!in||(op!='C'&&op!='U')||index<0||index>=256||slope>255||enabled>255||limbo>255||onMap>255||redraw>255||active>255||owns>255||capacity<0||capacity>16||count<0||count>capacity||growth>16)
            throw std::invalid_argument("Wall construction input");
        unsigned seed=0,skip=0,p=0,recalc=0,alias=0,allWalls=0,n=0;MapWallUpdateServices s;
        in>>seed>>skip>>p>>s.screenX>>s.screenY>>recalc>>alias>>allWalls;
        for(auto& t:connections.gates)in>>t;s.connections=connections;
        for(auto& visit:s.visits)in>>visit;
        for(auto& direction:s.directions){unsigned q=0;in>>q;direction=point(q);}in>>n;
        if(!in||skip!=1||recalc>3||alias>2||allWalls>1||!n||n>16||s.visits!=std::array<int,5>{0,2,4,6,-1})throw std::invalid_argument("Wall update input");
        cells.resize(n);nodes.resize(n);const auto base=point(p);
        for(unsigned i=0;i<n;++i){
            auto& c=cells[i];unsigned data=0,neighbors=0,count=0;
            in>>c.overlay>>data>>neighbors>>c.passability>>c.owner>>count;
            if(c.overlay< -1||c.overlay>=256||data>255||neighbors>255)throw std::invalid_argument("Wall Cell input");
            c.data=std::uint8_t(data);c.neighbors=std::uint8_t(neighbors);occupants(in,nodes[i],count);c.occupants=nodes[i];
            c.position=i?point((unsigned(std::uint16_t(base.x))+i-4)&65535u|(((unsigned(std::uint16_t(base.y))+(i*3)%5-2)&65535u)<<16)):base;
        }
        if(!in)throw std::invalid_argument("Wall Cell input truncated");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing wall input");
        for(unsigned i=0;i<n;++i)cells[i].slope=std::uint8_t(slope^i);
        std::array<std::uint8_t,256> flags;for(unsigned i=0;i<flags.size();++i)flags[i]=std::uint8_t(allWalls||(i+seed)%5!=0);flags[unsigned(index)]=1;s.wallTypes=flags;
        s.cell=[&](MapInputPosition q)->MapWallCell&{
            const unsigned x=std::uint16_t(q.x),y=std::uint16_t(q.y);
            const unsigned index=alias==1?0:(alias==2?(x^y)%std::min(n,2u):(x+3*y+seed)%n);
            event({5,packed(q),index});return cells[index];
        };
        s.bounds=[&](const auto& c,unsigned kind){
            const auto index=id(c);MapWallBounds r;
            switch(seed&3){
                case 0:break;
                case 1:r={int(index)*37-100,int(kind)*41-77,17+int(index),13+int(kind)};break;
                case 2:r={signedWord(seed^(index*0x1234567u)),signedWord(seed+kind*0x7654321u),signedWord(seed^(kind*0x40000000u)),signedWord(seed+index*0x11111111u)};break;
                default:r={signedWord(seed-index*53),signedWord(seed+kind*7),kind==0?-1:23,kind==2?0:17};break;
            }
            event({1,index,kind});append(events,r);return r;
        };
        s.unite=[&](MapWallBounds a,MapWallBounds b){
            event({2});append(events,a);append(events,b);const auto r=unionDirtyBounds({a.x,a.y,a.width,a.height},{b.x,b.y,b.width,b.height});return MapWallBounds{r.x,r.y,r.width,r.height};
        };
        s.dirty=[&](auto r){event({3});append(events,r);};s.notify=[&](auto q){event({4,packed(q)});};
        s.expired=[&](auto& c){event({9,id(c)});};s.zone=[&](unsigned kind,auto q){event({10,kind,packed(q)});};
        s.store=[&](auto& c,unsigned offset,unsigned size,unsigned value){event({12,id(c),offset,size,value});};
        s.recalculate=[&](auto& c,int level){
            event({8,id(c),unsigned(level)});unsigned value=unsigned(c.passability);
            if(recalc==1)value^=(unsigned(c.overlay)+1)&7;else if(recalc==2)value^=1;else if(recalc==3)value=c.overlay!=-1;
            c.passability=signedWord(value);s.store(c,0x4c,4,value);
        };
        OverlayTypeInputs type;type.index=index;type.wall=1;
        TransientMapOverlay actor;actor.type=&type;actor.position={signedWord(seed),signedWord(seed^0x12345678),signedWord(seed+17)};
        actor.identityToken=seed^0xaaaaaaaa;actor.limbo=std::uint8_t(limbo);actor.onMap=std::uint8_t(onMap);actor.redraw=std::uint8_t(redraw);actor.active=std::uint8_t(active);
        std::uint32_t counter=seed^0xfedcba98;
        OverlayTransientRegistry registry;registry.count=count;registry.growth=growth;registry.owns=std::uint8_t(owns);
        registry.slots.resize(unsigned(capacity));for(unsigned i=0;i<registry.slots.size();++i)registry.slots[i]=i+2;
        LoadedWallPlacementServices wall;wall.directions=s.directions;wall.currentOwner=owner;wall.livePlacementFlag=&flag;
        unsigned current=0;auto& placement=wall.object;
        placement.base=[&](auto&){event({30});};placement.identityCounter=seed?&counter:nullptr;
        placement.grow=[&](int size){
            event({31,unsigned(size),growResult});
            if(std::uint8_t(growResult)){registry.slots.resize(unsigned(size));registry.owns=1;}
            return bool(std::uint8_t(growResult));
        };
        placement.noAttachedAnimation=[&]{event({32});};placement.redraw=[&]{event({33});};
        placement.cell=[&](MapInputPosition q)->OverlayPlacementCell&{auto& c=s.cell(q);current=id(c);return cells[current];};
        placement.store=[&](unsigned role,unsigned offset,unsigned size,unsigned value){
            if(role==1)event({12,current,offset,size,value});else event({40+role,offset,size,value});
        };
        placement.recalculate=[&](auto& c,int level){current=id(c);s.recalculate(c,level);};
        placement.retire=[&](auto& a){event({34,40,0x7d,1,0});a.active=0;};
        wall.permissionQuery=[&]{event({35,1,0,0});};
        wall.updateWall=[&](auto& c,std::uint8_t argument){const auto saved=id(c);updateMapWall(c,argument,s);current=saved;};
        const auto q=point(pActor);const Coord center{int(q.x)*256+128,int(q.y)*256+128,0};
        bool result=true;
        if(op=='C')constructLoadedMapWall(actor,type,q,point(invalid),incoming,flag,1,registry,std::uint8_t(enabled),wall);
        else result=unlimboLoadedMapWall(actor,center,std::uint8_t(enabled),wall);
        Words output{unsigned(result),actor.identityToken,counter,unsigned(actor.position.x),unsigned(actor.position.y),unsigned(actor.position.z),actor.onMap,actor.redraw,actor.limbo,actor.active,unsigned(flag),unsigned(registry.count),unsigned(registry.slots.size()),registry.owns};
        output.insert(output.end(),registry.slots.begin(),registry.slots.end());
        for(const auto& c:cells)output.insert(output.end(),{packed(c.position),unsigned(c.overlay),unsigned(c.passability),unsigned(c.owner),c.data,c.neighbors,c.slope});
        std::cout<<digest(output)<<' '<<digest(events)<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
