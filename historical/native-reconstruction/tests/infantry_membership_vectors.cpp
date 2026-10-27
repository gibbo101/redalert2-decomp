// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/PreparedInfantryMembership.hpp"
#include "assets/MovementData.hpp"
#include "assets/PreparedData.hpp"
#include "render/Lighting.hpp"
#include "render/Redraw.hpp"
#include "sim/UnitDiscovery.hpp"
#include "sim/MapVisibility.hpp"
#include <openssl/evp.h>
#include <bit>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
template<class... T>void event(const T&... v){((std::cout<<v<<' '),...);}
std::string digest(const MapFloorHeightState& s,MapInputPosition p){
    std::vector<unsigned char> bytes{s.flags};
    const auto word=[&](std::uint64_t v,int n){for(int i=0;i<n;++i)bytes.push_back(std::uint8_t(v>>(i*8)));};
    word(std::bit_cast<std::uint64_t>(s.height),8);word(std::bit_cast<std::uint64_t>(s.scale),8);
    for(const auto& q:s.planes)for(double v:{q.x,q.y,q.offset,q.limit,q.add})word(std::bit_cast<std::uint64_t>(v),8);
    word(std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16),4);
    unsigned char hash[32];unsigned n=0;if(!EVP_Digest(bytes.data(),bytes.size(),hash,&n,EVP_sha256(),nullptr)||n!=32)throw std::runtime_error("Infantry membership digest");
    std::ostringstream out;for(auto v:hash)out<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(v);return out.str();
}
struct Actor {
    ActorGroundState ground;WalkMovementState walk;int next=-1,house=0,owner=0,image=17;
    std::uint8_t eligible=1,typeMap=1,redraw=0,limbo=0,special=0;
    InfantryMembershipActor view(){return {ground,walk,next,eligible,typeMap,{ground.marked74,redraw,limbo,special},house,owner,image};}
};
}
int main(int argc,char** argv){try{
    if(argc!=2)throw std::invalid_argument("Infantry membership requires prepared render data");
    const auto render=readRenderData(readFile(argv[1]),PatchedEngineSha);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;std::array<int,9> h;in>>op;const bool joined=op=='D';
        std::array<std::uint32_t,4> visibilityFlags{};UnitDiscoveryWorld discovery;UnitDiscoveryActor discovered;MapVisibilityState visibilityState;
        if(joined){
            for(auto& flags:visibilityFlags){std::uint64_t v=0;in>>v;if(!in||v>UINT32_MAX)throw std::invalid_argument("Infantry visibility flags");flags=std::uint32_t(v);}
            for(int i=0;i<2;++i){int human=0,control=0;in>>human>>control;if(!in||human<0||human>255||control<0||control>255)throw std::invalid_argument("Infantry discovery House");discovery.houses[i].human134=std::uint8_t(human);discovery.houses[i].control135=std::uint8_t(control);}
            int h13d=0,b372=0,b373=0,b374=0;in>>h13d>>visibilityState.overrideValue>>discovered.owner>>discovered.mission98>>discovered.queuedA0>>b372>>b373>>b374;
            for(int v:{h13d,b372,b373,b374})if(v<0||v>255)throw std::invalid_argument("Infantry discovery byte");
            if(!in||discovered.owner<0||discovered.owner>1)throw std::invalid_argument("Infantry discovery owner");
            visibilityState.heightDivisor=104;visibilityState.currentHouse13d=std::uint8_t(h13d);
            discovered.field372=std::uint8_t(b372);discovered.current373=std::uint8_t(b373);discovered.other374=std::uint8_t(b374);discovered.queuedA4=255;discovery.loading=1;
        }
        for(auto& n:h)in>>n;
        const auto byte=[](int v){return v>=0&&v<=255;};const auto id=[](int v){return v>=-1&&v<=3;};
        if(!in||(op!='U'&&!joined)||!byte(h[0])||!byte(h[1])||!byte(h[2])||h[8]<0||h[8]>7)throw std::invalid_argument("Infantry membership header");
        if(joined&&(h[6]<0||h[6]>1||h[8]))throw std::invalid_argument("Infantry joined current House/mutation");
        discovery.currentHouse=h[6];discovery.mode=h[3];visibilityState.mode=h[3];
        std::array<MapFinalizationCell,3> prepared{};MapCellAttributes fallback;
        std::array<InfantryMembershipCell,4> extra;
        for(int i=0;i<4;++i){int level=0,ramp=0,head=0,alt=0;std::uint64_t flags=0,g=0,e=0;
            in>>level>>ramp>>flags>>g>>e>>head>>alt;
            if(!in||level<-128||level>127||ramp<0||ramp>20||flags>UINT32_MAX||g>UINT32_MAX||e>UINT32_MAX||!id(head)||!id(alt))throw std::invalid_argument("Infantry membership Cell");
            auto& c=i==3?fallback:prepared[std::size_t(i)].attributes;
            c.input.position={std::int16_t(i<3?51+i:-7),std::int16_t(i<3?72:5)};
            c.input.level=std::int8_t(level);c.input.slope=std::uint8_t(ramp);c.input.flags=std::uint32_t(flags);
            extra[std::size_t(i)]={head,alt,std::uint32_t(g),std::uint32_t(e),-1,-1};
        }
        std::array<Actor,4> actors;
        for(auto& a:actors){in>>a.next;if(!in||!id(a.next))throw std::invalid_argument("Infantry Next");a.typeMap=std::uint8_t(h[2]);}
        MapFloorHeightState floor;
        for(auto& p:floor.planes)for(auto* v:{&p.x,&p.y,&p.offset,&p.limit,&p.add}){
            std::uint64_t bits=0;in>>bits;*v=std::bit_cast<double>(bits);if(!in||!std::isfinite(*v))throw std::invalid_argument("Infantry floor planes");
        }
        int count=0;in>>count;if(!in||count<1||count>128)throw std::invalid_argument("Infantry membership count");
        std::vector<int> slots(262144,-1);for(int i=0;i<3;++i)slots[72*512+51+i]=i;
        std::array<int,16> land{};std::array<float,11> speeds{};ResidentCellInputs resident;resident.landMap=land;resident.wheelSpeeds=speeds;
        Bytes b4(166*166*4),b10(166*166*10);MutableUnitMap map({prepared,slots,fallback,floor,resident,b4,b10,80,85,104});
        UnitFoundationState foundation;foundation.objectFlag=std::uint8_t(h[0]);foundation.unitFlag=std::uint8_t(h[1]);
        if(!(h[0]&1))foundation.fallback={-23131,-23131};
        if(!(h[1]&1))foundation.unit={{{-23131,-23131},{-23131,-23131}}};
        PreparedInfantryMembership member(map,extra,{{0,actors[0].view()},{1,actors[1].view()},{2,actors[2].view()},{3,actors[3].view()}},foundation,h[7],
            [&render](double v){return tableSqrt(render,v);});
        if(map.floor.flags||map.fallback.input.position!=fallback.input.position)throw std::logic_error("Infantry binding warmed map");
        auto& w=member.world();w.services.visibilityGate=h[3];w.services.notificationArgument=h[6];
        w.trace=[](char k,int a,int b){event(k,a,b);};
        const auto store=[](int subject,int off,int width,std::uint32_t value){
            const bool logical=subject<100||(subject>=100&&subject<104&&(off==0xe4||off==0xe8));
            event('W',subject,off,width,logical?std::int64_t(signed32(value)):std::int64_t(value));
        };
        w.store=[&](int subject,int off,std::uint32_t value){store(subject,off,subject==200&&(off==0||off==8)?1:4,value);};
        w.services.visible=[&](const Coord& p){event('V',0,p.x,p.y,p.z);return h[4];};
        w.services.visibleSecondary=[&](const Coord& p){event('V',1,p.x,p.y,p.z);return h[5];};
        w.services.notify=[&](int actor,int arg){event('N',actor,arg);
            if(h[8]){event('Z',h[8]);auto& a=actors[0];
                if(h[8]&1){a.ground.position.x=signed32(std::uint32_t(a.ground.position.x)+512);a.ground.position.z=signed32(std::uint32_t(a.ground.position.z)+37);a.eligible=a.eligible?0:255;}
                if(h[8]&6){const int slot=72*512+51;map.slots[slot]=(h[8]&4)?-1:2;map.table[slot]=(h[8]&4)?nullptr:&map.cells[2].attributes.input;}
            }
        };
        MapVisibilityWorld visibility;
        visibility.direction3={1,1};visibility.query=[](char k,TerrainCellPoint p){event(k,int(p.x),int(p.y));};
        visibility.borrowedCell=[&](TerrainCellPoint p){
            auto& input=mapAttributeCell({p.x,p.y},{map.table,&map.fallback.input,{},[&](MapInputPosition q){event('W',103,0x24,4,std::uint16_t(q.x)|(std::uint32_t(std::uint16_t(q.y))<<16));}});
            const int id=member.cellId(&input);
            return MapVisibilityCell{{input.position.x,input.position.y},visibilityFlags[std::size_t(id)],input.flags};
        };
        visibility.neighbor=[&](const MapVisibilityCell& c,int d){int id=3;for(int i=0;i<3;++i)if(c.point==TerrainCellPoint{std::int16_t(51+i),72})id=i;event('n',id,d);};
        if(joined){
            w.services.liveVisibilityGate=[&]{return discovery.mode;};
            w.services.liveNotificationArgument=[&]{return discovery.currentHouse;};
            w.services.visible=[&](const Coord& p){event('V',0,p.x,p.y,p.z);return int(mapPrimaryVisibility(p,visibilityState,visibility));};
            w.services.visibleSecondary=[&](const Coord& p){event('V',1,p.x,p.y,p.z);return int(mapSecondaryVisibility(p,visibilityState,visibility));};
            discovery.trace=[](char k,int v){event(k,v);};discovery.store=[](int subject,int offset,std::uint32_t value){event('w',subject,offset,value);};
            w.services.notify=[&](int actor,int arg){event('N',actor,arg);if(actor!=0)throw std::invalid_argument("Unsupported Infantry discovery actor");discoverUnit(discovered,arg,discovery);};
        }
        w.services.recalculate=[](int cell,int arg){event('R',cell,arg);};
        member.occupationStore=[&](InfantryOccupationCell c,int off,int width,std::uint32_t v){
            for(int i=0;i<4;++i)if(&c.ground==&extra[std::size_t(i)].ground){store(100+i,off,width,v);return;}
            throw std::logic_error("Foreign Infantry occupation owner");
        };
        RedrawState redraw{2,255,0,true};member.redrawMap=[&]{requestMapRedraw(redraw,0,[&](auto e){if(e.kind!='t')throw std::logic_error("Unexpected redraw field");store(201,0,1,e.value);});};
        for(int n=0;n<count;++n){int root=0,mode=0,actor=0,cell=0,alt=0,eligible=0;Coord p;
            in>>root>>mode>>actor>>cell>>p.x>>p.y>>p.z>>alt>>eligible;
            if(!in||root<0||root>4||(actor!=-1&&actor!=0)||cell<0||cell>3||!byte(alt)||!byte(eligible)||(root==4&&actor!=0))throw std::invalid_argument("Infantry membership row");
            actors[0].ground.position=p;actors[0].ground.bridge79=std::uint8_t(alt);actors[0].eligible=std::uint8_t(eligible);int accepted=-1;
            if(root==0)w.cellInsert(actor,cell);else if(root==1)w.cellRemove(actor,cell);
            else if(root==2)w.mapInsert(actor,terrainCellPoint(p));else if(root==3)w.mapRemove(actor,terrainCellPoint(p));
            else accepted=member.mark(0,mode,[&](int off,std::uint8_t v){store(0,off,1,v);});
            event('S',accepted,unsigned(actors[0].ground.marked74),unsigned(actors[0].redraw),unsigned(redraw.tactical));
            for(const auto& c:extra)event(c.head,c.alternateHead,c.ground,c.elevated,c.groundHouse,c.elevatedHouse);
            for(const auto& a:actors)event(a.next);event(digest(map.floor,map.fallback.input.position));
            if(joined){event('X',unsigned(discovered.current373),unsigned(discovered.other374),discovered.queuedA0,unsigned(discovered.queuedA4));for(int i=0;i<2;++i){const auto& house=discovery.houses.at(i);event(unsigned(house.discovered13c),unsigned(house.field5668),unsigned(house.field5669));}}

        }
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing Infantry membership fixture");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
