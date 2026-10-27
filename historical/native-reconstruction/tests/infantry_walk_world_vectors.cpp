// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/PreparedInfantryWalk.hpp"
#include "assets/PreparedData.hpp"
#include "assets/MovementData.hpp"
#include "assets/InfantrySubcellData.hpp"
#include "assets/PreparedTerrainMap.hpp"
#include "render/Lighting.hpp"
#include "render/VoxelRaster.hpp"
#include <openssl/evp.h>
#include <bit>
#include <cfenv>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
template<class... T>void event(const T&... v){((std::cout<<v<<' '),...);}
std::string digest(const MapFloorHeightState& s,MapInputPosition p){
    Bytes b{s.flags};const auto word=[&](std::uint64_t v,int n){for(int i=0;i<n;++i)b.push_back(std::uint8_t(v>>(8*i)));};
    word(std::bit_cast<std::uint64_t>(s.height),8);word(std::bit_cast<std::uint64_t>(s.scale),8);
    for(const auto& q:s.planes)for(double v:{q.x,q.y,q.offset,q.limit,q.add})word(std::bit_cast<std::uint64_t>(v),8);
    word(std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16),4);
    unsigned char hash[32];unsigned n=0;if(!EVP_Digest(b.data(),b.size(),hash,&n,EVP_sha256(),nullptr)||n!=32)throw std::runtime_error("Walk world digest");
    std::ostringstream out;for(auto v:hash)out<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(v);return out.str();
}
}
int main(int argc,char** argv){try{
    if(argc!=6)throw std::invalid_argument("Infantry Walk world requires render/raster/direction/subcell/map data");
    const auto render=readRenderData(readFile(argv[1]),PatchedEngineSha);
    const auto raster=readRasterData(readFile(argv[2]),PatchedEngineSha);
    const auto direction=readDirectionData(readFile(argv[3]),PatchedEngineSha);
    const auto subcells=readInfantrySubcellData(readFile(argv[4]),PatchedEngineSha);
    const auto mapData=readMapRuntimeData(readFile(argv[5]));
    std::fesetround(FE_TONEAREST);const double radians=direction.pi/-32767.;
    const WalkMovementNumerics numbers{direction,radians,[&](double v){return tableSqrt(render,v);},
        [&](double v){return tableSine(raster,v);},[&](double v){return tableCosine(raster,v);}};
    std::string line;int sequence=0;
    while(std::getline(std::cin,line)){
        std::istringstream in(line);char code=0;std::array<int,10> v{};in>>code;
        for(auto& x:v)if(!(in>>x))throw std::invalid_argument("Missing Infantry Walk world input");
        in>>std::ws;
        if(!in.eof()||code!='J'||v[0]<0||v[0]>7||v[1]<1||v[1]>64||v[2]<1||v[2]>2||v[3]<1||v[3]>96||
           v[4]<-128||v[4]>127||(v[5]!=0&&v[5]!=768)||v[6]<1||v[6]>255||v[7]<1||v[7]>255||v[8]<0||v[8]>3||v[9]<-1||v[9]>=v[3])
            throw std::invalid_argument("Infantry Walk world scenario");
        std::array<MapFinalizationCell,25> prepared{};
        std::vector<int> slots(262144,-1);
        for(int i=0;i<25;++i){auto& c=prepared[std::size_t(i)].attributes.input;
            c.position={std::int16_t(49+i%5),std::int16_t(70+i/5)};c.level=std::int8_t(v[4]);c.flags=std::uint32_t(v[5]);
            slots[std::size_t(c.position.y*512+c.position.x)]=i;
        }
        MapCellAttributes fallback;fallback.input.position={-7,5};MapFloorHeightState floor;
        // Existing private map preparation retains the100 plane doubles.
        floor.planes=mapData.floor.planes;
        std::array<int,16> land{};std::array<float,11> wheels{};ResidentCellInputs resident;
        resident.landMap=land;resident.wheelSpeeds=wheels;Bytes b4(166*166*4),b10(166*166*10);
        MutableUnitMap map({prepared,slots,fallback,floor,resident,b4,b10,80,85,104});
        std::array<InfantryMembershipCell,26> cells;
        for(auto& c:cells){c.ground=0xaabbcc00;c.elevated=0x11223300;}
        InfantryWalkState actor;actor.ground.position={51*256+v[6],72*256+v[7],104*v[4]+(v[5]?416:0)};
        actor.ground.bridge79=std::uint8_t(v[5]!=0);
        actor.object.mission.owner=0;actor.object.mission.mission98=2;
        actor.body={0x1234,0x2345,-1,7,256};
        actor.percentage468=.375;actor.field57a=173;actor.field5a1=255;actor.transition57b=197;
        actor.cell450={0x5678,0x1234};for(int i=1;i<24;++i)actor.route[std::size_t(i)]=100+i;
        actor.counter53c=19;actor.field490=19;actor.wait558={31,37,41};
        InfantryWalkType type;type.speed5a0=v[1];type.image598=17;
        InfantryWalkGlobals globals;globals.session=0;globals.routePadding=0x12345678;globals.orderPadding=0x12345689;
        UnitDiscoveryHouse house;house.indexAlliance={0,0,1};house.human134=1;float country=1;
        AdmissionHouses houses{[&house](int id){if(id!=0)throw std::invalid_argument("Foreign Walk House");
                return AdmissionHouseView{house.indexAlliance.countryIndex,house.indexAlliance.allianceMask};},
            [](int id){return id==0;}};
        std::vector<std::optional<UnitAdmissionRegistry>> registry;std::array<std::uint32_t,108> speeds;speeds.fill(std::bit_cast<std::uint32_t>(1.f));
        OriginalRandomState random{0,0,103,{}};std::uint32_t seed=0x71e220;
        for(auto& x:random.table){seed=seed*1664525u+1013904223u;x=seed;}
        UnitFoundationState foundation;
        PreparedInfantryWalk world(map,cells,{{0,{actor,type,house.indexAlliance.countryIndex,country,house.human134,house.control135}}},foundation,houses,registry,globals,subcells,random,numbers,speeds);
        if(map.floor.flags||cells[12].head!=-1||actor.ground.marked74)throw std::logic_error("Walk binding warmed source owners");
        world.store=[](char k,int id,int off,int width,std::uint64_t value){event('W',k,id,off,width,value);};
        auto& membership=world.membership();auto& m=membership.world();
        m.services.visible=[](const Coord&){return 1;};m.services.visibleSecondary=[](const Coord&)->int{throw std::logic_error("Unexpected secondary visibility");};
        m.services.notify=[](int,int){throw std::logic_error("Unexpected membership notification");};
        m.services.recalculate=[](int id,int arg){event('r',id,arg);};
        int tactical=0;membership.redrawMap=[&]{tactical=1;world.store('G',2,0,1,1);};
        membership.specialEvent=[](int,int){throw std::logic_error("Unexpected special event");};
        world.dirty=[](int id){event('d',id);};
        world.animation=[](int,int,int,int){throw std::logic_error("Unexpected animation service");};
        world.arrivalNotification=[&](int id,int kind){event('n',id,kind);
            if(v[8]==1)actor.flag7a=1;else if(v[8]==2)actor.onMap7d=0;else if(v[8]==3)actor.flag76=1;
        };
        const auto [dx,dy]=directionOffset(v[0]);const Coord destination{actor.ground.position.x+dx*256*v[2],actor.ground.position.y+dy*256*v[2],actor.ground.position.z};
        int target=1;world.targetIdentity=[&](const void* p){if(p!=&target)throw std::invalid_argument("Walk target association");return 1;};
        world.targetCoordinates=[&](const void* p){if(p!=&target)throw std::invalid_argument("Walk target coordinates");return destination;};
        world.route=[&](int id,TerrainCellPoint p,int x,int y){event('f',id,p.x,p.y,x,y);
            for(int i=0;i<v[2];++i){actor.route[std::size_t(i)]=v[0];world.store('A',id,0x4d0+4*i,4,std::uint32_t(v[0]));}
            actor.route[std::size_t(v[2])]=-1;world.store('A',id,0x4d0+4*v[2],4,UINT32_MAX);return std::uint8_t(1);
        };
        const auto rounding=std::array{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}[std::size_t(sequence++%4)];std::fesetround(rounding);
        world.mark(0,1);membership.occupy(0,actor.ground.position);world.order(0,&target);
        for(int tick=0;tick<v[3];++tick){globals.tick=tick;if(tick==v[9])world.order(0,nullptr);
            const auto result=world.process(0);if(std::fegetround()!=rounding)throw std::logic_error("Walk world leaked rounding mode");
            event('P',unsigned(result),actor.ground.position.x,actor.ground.position.y,actor.ground.position.z,
                actor.walk.destination.x,actor.walk.destination.y,actor.walk.destination.z,actor.walk.head.x,actor.walk.head.y,actor.walk.head.z,
                unsigned(actor.walk.moving34),unsigned(actor.walk.inProcessing35),unsigned(actor.walk.reallyMoving36),unsigned(actor.ground.marked74),unsigned(actor.redraw75),
                unsigned(actor.ground.bridge79),unsigned(actor.onMap7d),unsigned(actor.flag76),unsigned(actor.flag7a),unsigned(actor.field57a),unsigned(actor.transition57b),unsigned(actor.field5a1),
                std::bit_cast<std::uint64_t>(actor.percentage468),actor.body.desired,actor.body.start,actor.body.timerStart,actor.body.duration,actor.object.next+1);
        }
        event('Z',actor.field490,int(actor.target494!=nullptr),unsigned(actor.suspended598),unsigned(actor.reset5cc),actor.references,globals.references,actor.counter53c,actor.state5ac,
            int(actor.cell450.x),int(actor.cell450.y),tactical);
        for(int x:actor.retry530)event(x);for(int x:actor.wait558)event(x);for(int x:actor.route)event(x);
        for(const auto& c:cells)event(c.head+1,c.alternateHead+1,c.ground,c.elevated,c.groundHouse,c.elevatedHouse);
        event(unsigned(foundation.objectFlag),unsigned(foundation.unitFlag),int(foundation.fallback.x),int(foundation.fallback.y),
            int(foundation.unit[0].x),int(foundation.unit[0].y),int(foundation.unit[1].x),int(foundation.unit[1].y),digest(map.floor,map.fallback.input.position));
        event("rng",random.next1,random.next2);for(auto x:random.table)event(x);std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
