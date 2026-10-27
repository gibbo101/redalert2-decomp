// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/WalkHead.hpp"
#include "sim/InfantryAdmission.hpp"
#include "sim/InfantrySpeed.hpp"
#include "sim/WalkCommands.hpp"
#include "sim/WalkRoute.hpp"
#include "sim/InfantryDestination.hpp"
#include "sim/BorrowedUnitAdmission.hpp"
#include "assets/InfantrySubcellData.hpp"
#include "assets/WalkCellView.hpp"
#include "assets/MovementData.hpp"
#include "assets/PreparedData.hpp"
#include "render/Lighting.hpp"
#include "render/VoxelRaster.hpp"
#include <bit>
#include <cfenv>
#include <cmath>
#include <iostream>
#include <sstream>
using namespace ra2;
template<class... T>void event(T... args){((std::cout<<args<<' '),...);}
struct Cell {
    MapCellInput movement;std::uint32_t ground,elevated;int house,elevatedHouse,overlay=-1;
    TerrainCellPoint point;std::int16_t registry=-1;std::uint8_t ramp=0;int land=0,head=-1,elevatedHead=-1;
    WalkHeadCell view(){return {{ground,elevated,movement.flags,house,elevatedHouse},overlay};}
};
int add(int a,int b){return signed32(std::uint32_t(a)+std::uint32_t(b));}
int identity(Coord p){return (p.x/256 ^ p.y/256)&1;}
void routeGuards(){
    ActorGroundState ground{{128,128,0}};Facing body;int frozen=0;double percentage=.375;
    std::uint8_t a=173,b=197,on=1,z=0,transition=0,jump=0;std::int8_t secondary=-1;
    const void* target=nullptr;WalkMovementState walk{{384,128,0},{},173,0,255};
    std::array<int,24> route;route.fill(99);route[0]=-1;TerrainCellPoint point;
    WalkArrivalContext arrival{{route,point,on,z,z,secondary},{}};
    UnitDiscoveryActor mission;DirectionData direction;InfantrySubcellData subcells;OriginalRandomState random;
    int house=3,height=104;WalkHeadInputs inputs{subcells,random,house,height,height,height};WalkHeadServices head;
    WalkQueuedContext queued{{ground.position,mission,target},inputs,head,transition,{},{}};
    int start=-1,padding=17,remaining=5,counter=23,state=3;double interval=0;
    WalkRouteContext refill{{start,padding,remaining},counter,state,target,jump,interval,31,
        []()->int{throw std::logic_error("Disabled timer read the clock");},{}};
    queued.route=&refill;WalkMovementNumerics n{direction};WalkMovementServices services;
    WalkMovementActor actor{ground,body,frozen,percentage,a,b};
    for(int value:{3,6,17,2}){
        state=value;
        if(processQueuedWalk(walk,actor,n,services,arrival,queued,0)!=173||walk.inProcessing35||
            state!=(value==2?2:-1)||walk.reallyMoving36!=255||b!=197||percentage!=.375||counter!=23||route[23]!=99)
            throw std::logic_error("Retry wait changed unrelated live owners");
    }
    refill.clock=[](){return 0;};remaining=-1;start=0;interval=std::numeric_limits<double>::quiet_NaN();
    refill.findRoute=[](TerrainCellPoint p,int a,int b){if(p!=TerrainCellPoint{1,0}||a||b)throw std::logic_error("Route arguments changed");return std::uint8_t(0);};
    bool refused=false;try{processQueuedWalk(walk,actor,n,services,arrival,queued,0);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||remaining||padding!=31||walk.reallyMoving36||counter!=23||route[0]!=-1)
        throw std::logic_error("Failed route became movement or lost preceding stores");
    const void* other=nullptr;WalkRouteContext wrong{{start,padding,remaining},counter,state,other,jump,interval,31,refill.clock,refill.findRoute};
    queued.route=&wrong;start=17;refused=false;
    try{processQueuedWalk(walk,actor,n,services,arrival,queued,0);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||start!=17)throw std::logic_error("Different route target owner accepted");
    std::cout<<"Walk route wait/borrowed-owner/failed-child guards PASS\n";
}
void guards(){
    ActorGroundState ground{{192,192,0}};Facing body;int frozen=0;double percent=.375;
    std::uint8_t a=17,b=23,transition=197,on=0,z=0;std::int8_t secondary=-1;
    WalkMovementState w{{448,192,0},{},173,197,255};std::array<std::int32_t,24> route;route.fill(-1);route[0]=2;
    TerrainCellPoint cellPoint{};WalkArrivalContext arrival{{route,cellPoint,on,z,z,secondary},{}};
    DirectionData direction;WalkMovementNumerics n{direction,0,[](double x){return std::sqrt(x);}};WalkMovementServices s;
    Cell cell{{},0,0,3,7};UnitDiscoveryActor mission;mission.mission98=2;const void* target=nullptr;
    InfantrySubcellData data;OriginalRandomState random;int house=3,height=104;
    WalkHeadInputs inputs{data,random,house,height,height,height};WalkHeadServices hs;
    hs.cell=[&](const Coord&){return cell.view();};hs.floor=[](const Coord&){return 0;};hs.squareRoot=n.squareRoot;
    WalkQueuedContext q{{ground.position,mission,target},inputs,hs,transition,{}, {}};
    WalkMovementActor actor{ground,body,frozen,percent,a,b};
    bool refused=false;try{processCommittedWalk(w,actor,n,s,0,104);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||w.inProcessing35!=1)throw std::logic_error("Legacy empty-head guard changed");
    int queries=0;q.coordinateCell=[&](const Coord&)->WalkMovementCellView{++queries;return borrowWalkCell(cell.movement);};
    s.lookup=[&](TerrainCellPoint)->WalkMovementCellView{return borrowWalkCell(cell.movement);};
    q.admission=[](WalkMovementCellView,int,int,int,int){return 7;};
    refused=false;try{processQueuedWalk(w,actor,n,s,arrival,q,0);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||queries!=3||w.head!=Coord{}||percent!=.375||transition!=197)
        throw std::logic_error("Nonzero Infantry admission must not become success");
    q.admission=[](WalkMovementCellView,int,int,int,int){return 0;};
    if(processQueuedWalk(w,actor,n,s,arrival,q,0)!=173||ground.position!=Coord{192,192,0}||w.head!=Coord{448,192,0}||w.inProcessing35||w.reallyMoving36!=1||b!=23||percent!=.375)
        throw std::logic_error("Off-map preparation must skip interpolation, percentage and57A clear");
    for(int dir:{-1,8}) {
        w.head={};route[0]=dir;queries=0;refused=false;
        try{processQueuedWalk(w,actor,n,s,arrival,q,0);}catch(const std::invalid_argument&){refused=true;}
        if(!refused||queries)throw std::logic_error("Unjoined route/special child made queries");
    }
    auto other=ground.position; // ownership is checked before mutation
    WalkQueuedContext wrong{{other,mission,target},inputs,hs,transition,q.coordinateCell,q.admission};
    w.inProcessing35=197;refused=false;
    try{processQueuedWalk(w,actor,n,s,arrival,wrong,0);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||w.inProcessing35!=197)throw std::logic_error("Different head/movement actor accepted");
    std::cout<<"6 queued Walk guards PASS\n";
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();routeGuards();return 0;}
    const bool routeMode=argc==6&&std::string(argv[5])=="--route";
    const bool commandMode=argc==6&&std::string(argv[5])=="--commands";
    const bool speedMode=routeMode||commandMode||(argc==6&&std::string(argv[5])=="--speed");
    const bool admissionMode=speedMode||(argc==6&&std::string(argv[5])=="--admission");
    if(argc!=5&&!admissionMode)throw std::invalid_argument("Queued Walk requires render/raster/direction/subcell data [--admission|--speed]");
    const auto render=readRenderData(readFile(argv[1]),PatchedEngineSha);
    const auto raster=readRasterData(readFile(argv[2]),PatchedEngineSha);
    const auto direction=readDirectionData(readFile(argv[3]),PatchedEngineSha);
    const auto subcells=readInfantrySubcellData(readFile(argv[4]),PatchedEngineSha);
    const auto saved=std::fegetround();std::fesetround(FE_TONEAREST);const double radians=direction.pi/-32767.;std::fesetround(saved);
    const WalkMovementNumerics n{direction,radians,[&](double v){event('Q',std::int64_t(v));return tableSqrt(render,v);},
        [&](double v){return tableSine(raster,v);},[&](double v){return tableCosine(raster,v);}};
    std::string line;std::size_t sequence=0;
    while(std::getline(std::cin,line)){
        std::istringstream in(line);char cmd=0;std::array<std::int64_t,35> v{};in>>cmd;
        for(auto& x:v)if(!(in>>x))throw std::invalid_argument("Missing queued Walk field");
        // Explicit diagnostic composition. Legacy Q inputs/outputs keep their
        // supplied admission service and existing immutable original receipts.
        std::array<std::int64_t,11> options{};
        if(admissionMode)for(auto& x:options)if(!(in>>x))throw std::invalid_argument("Missing joined admission field");
        std::array<std::uint64_t,8> speedOptions{};
        if(speedMode)for(auto& x:speedOptions)if(!(in>>x))throw std::invalid_argument("Missing joined speed field");
        if(speedMode){
            if(speedOptions[0]>UINT32_MAX)throw std::invalid_argument("Country speed float bits");
            for(std::size_t i=4;i<8;++i)if(speedOptions[i]>255)throw std::invalid_argument("Infantry speed flag");
        }
        int stopAt=-1;
        if(commandMode&&(!(in>>stopAt)||stopAt<-1||stopAt>=v[7]))throw std::invalid_argument("Queued Walk Stop tick");
        std::array<std::int64_t,12> f{};std::uint64_t intervalBits=0;
        if(routeMode){
            if(!(in>>f[0]>>intervalBits))throw std::invalid_argument("Walk route options");
            for(std::size_t i=1;i<f.size();++i)if(!(in>>f[i])||f[i]<INT32_MIN||f[i]>INT32_MAX)throw std::invalid_argument("Walk route word");
            if(f[0]<0||f[0]>1||f[7]<1||f[7]>24||f[8]<1||f[8]>255||f[10]<0||f[10]>1||f[11]<0||f[11]>3)
                throw std::invalid_argument("Walk route supplied-service profile");
        }
        std::string extra;if(cmd!=(routeMode?'F':commandMode?'W':speedMode?'V':admissionMode?'A':'Q')||in>>extra)throw std::invalid_argument("Queued Walk command");
        if(admissionMode){
            for(auto i:{0,1})if(options[std::size_t(i)]<0||options[std::size_t(i)]>255)throw std::invalid_argument("Admission flag");
            if(options[2]<0||options[2]>8||options[3]<INT32_MIN||options[3]>INT32_MAX||options[4]<0||options[4]>UINT32_MAX)
                throw std::invalid_argument("Admission type/loading/speed");
            for(auto i:{5,6})if(options[std::size_t(i)]<0||options[std::size_t(i)]>11)throw std::invalid_argument("Admission land");
            for(auto i:{7,8})if(options[std::size_t(i)]<-1||options[std::size_t(i)]>0)throw std::invalid_argument("Admission self head");
            for(auto i:{9,10})if(options[std::size_t(i)]<0||options[std::size_t(i)]>255)throw std::invalid_argument("Admission ramp");
        }
        for(std::size_t i=0;i<v.size();++i){const bool word=i==21||i==22||i==23||i==26||i==27||i==28;
            if(v[i]<(word?0:std::int64_t(INT32_MIN))||v[i]>(word?std::int64_t(UINT32_MAX):std::int64_t(INT32_MAX)))throw std::invalid_argument("Queued Walk integer");}
        if(v[7]<1||v[7]>128||v[8]<0||v[8]>256||v[17]<0||v[17]>511||v[18]<0||v[18]>32||v[19]<-128||v[19]>127||v[20]<-128||v[20]>127)
            throw std::invalid_argument("Queued Walk fixture domain");
        for(auto i:{13,14,15})if(v[std::size_t(i)]<0||v[std::size_t(i)]>255)throw std::invalid_argument("Queued Walk byte");
        ActorGroundState ground{{int(v[0]),int(v[1]),int(v[2])},128,std::uint8_t(v[13])};
        Facing body{0x1234,0x2345,-1,7,256};int frozen=int(v[16]);double percentage=double(v[34]);
        std::uint8_t a1=255,a2=173,transition=197,on=std::uint8_t(v[14]),flag76=0,flag7a=0;
        WalkMovementState w{{int(v[3]),int(v[4]),int(v[5])},{},std::uint8_t(v[15]),173,197};
        std::array<std::int32_t,24> route;route[0]=int(v[6]);for(int i=1;i<24;++i)route[std::size_t(i)]=100+i;
        TerrainCellPoint cellPoint{0x5678,0x1234};std::int8_t secondary=-1;
        WalkArrivalContext arrival{{route,cellPoint,on,flag76,flag7a,secondary},{}};
        std::array<Cell,2> cells{};for(int i=0;i<2;++i){const auto j=std::size_t(21+5*i);auto& c=cells[std::size_t(i)];
            c.movement.level=std::int8_t(v[std::size_t(19+i)]);c.movement.flags=std::uint32_t(v[j+2]);
            c.ground=std::uint32_t(v[j]);c.elevated=std::uint32_t(v[j+1]);c.house=int(v[j+3]);c.elevatedHouse=int(v[j+4]);}
        UnitDiscoveryActor mission;mission.mission98=int(v[32]);mission.queuedA0=int(v[33]);const void* target=nullptr;
        std::map<int,MovementGateHouse> houses{{0,{int(v[31]),0}}};int& house=houses.at(0).index;
        int height=int(v[10]),level=int(v[11]),threshold=int(v[12]);
        OriginalRandomState random{0,0,103,{}};std::uint32_t seed=0x71e220;for(auto& word:random.table){seed=seed*1664525u+1013904223u;word=seed;}
        int lookups=0;const auto mutation=v[17];
        const auto mutate=[&]{
            if(mutation&1){ground.position.x=add(ground.position.x,257);ground.position.y=add(ground.position.y,-513);ground.position.z=add(ground.position.z,7);}
            if(mutation&2)ground.bridge79^=128;
            if(mutation&4)for(auto& c:cells)c.movement.level=std::bit_cast<std::int8_t>(std::uint8_t(std::uint8_t(c.movement.level)+1));
            if(mutation&8)for(auto& c:cells)c.movement.flags^=256;
            if(mutation&16)route[0]=7;if(mutation&32)on=0;
            if(mutation&64)for(auto& c:cells){c.ground^=0x1c;c.elevated^=0x1c;}
            if(mutation&128){mission.mission98=-1;mission.queuedA0=8;}
            if(mutation&256)w.destination={};
        };
        const auto tag=[&](const Coord& p){return &p==&w.head?'h':&p==&ground.position?'a':'s';};
        const auto lookup=[&](const Coord& p)->Cell&{
            const auto id=identity(p);event('N',id,tag(p),p.x,p.y,p.z);
            if(++lookups==v[18])mutate();return cells[std::size_t(id)];
        };
        WalkHeadServices hs;hs.squareRoot=n.squareRoot;hs.cell=[&](const Coord& p){return lookup(p).view();};
        hs.floor=[&](const Coord& p){event('F',tag(p),p.x,p.y,p.z);return int(v[9]);};
        hs.houseQuery=[&]{event('H',house);};hs.missionQuery=[](int m){event('M',m);};
        hs.headStore=[](int off,int value){event('L',off,std::uint32_t(value),0);};
        hs.cellStore=[&](InfantryOccupationCell c,int off,int width,std::uint32_t value){event('C',&c.ground==&cells[0].ground?0:1,off,width,value);};
        hs.cellEffect=[&](WalkHeadCell c){event('E',&c.occupation.ground==&cells[0].ground?0:1);};
        hs.randomDraw=[](std::uint32_t value,const OriginalRandomState& state){event('D',value,state.next1,state.next2);};
        WalkHeadInputs inputs{subcells,random,house,threshold,height,level};
        WalkQueuedContext q{{ground.position,mission,target},inputs,hs,transition,{}, {}};
        q.coordinateCell=[&](const Coord& p)->WalkMovementCellView{return borrowWalkCell(lookup(p).movement);};
        q.admission=[&](WalkMovementCellView c,int dir,int l,int zero,int one){event('I',c.identity==&cells[0].movement?0:1,dir,l,zero,one);return 0;};
        // New metadata has its own diagnostic owners; all existing level,
        // flags, occupation and House fields are borrowed, never refreshed.
        std::vector<int> slots;std::vector<std::optional<UnitAdmissionRegistry>> registries;
        std::array<TerrainCellPoint,8> offsets{};std::array<std::uint32_t,12> unusedSpeeds{};
        std::array<std::uint32_t,108> admissionSpeeds{};MovementGateObject gateActor;gateActor.owner=0;
        int tickOwner=0,padding=0,speedType=int(options[2]),loading=int(options[3]);
        auto flag32d=std::uint8_t(options[0]),flag370=std::uint8_t(options[1]);
        std::optional<BorrowedUnitAdmissionWorld> admissionWorld;
        InfantryAdmissionServices admissionServices;
        if(admissionMode){
            slots.resize(262144);for(int y=0;y<512;++y)for(int x=0;x<512;++x)slots[std::size_t(y*512+x)]=(x^y)&1;
            for(int d=0;d<8;++d){auto [x,y]=directionOffset(d);offsets[std::size_t(d)]={std::int16_t(x),std::int16_t(y)};}
            BorrowedMovementGateWorld gates{houses,{},{},slots,0,tickOwner,padding,padding};
            gates.objects.emplace(0,AdmissionGateObjectView{gateActor.kind,gateActor.next,gateActor.owner,gateActor.gate,gateActor.animation18,gateActor.animation19,
                mission,gateActor.statusA8,gateActor.lastAC,gateActor.timerStart,gateActor.timerPadding,gateActor.timerRemaining});
            gates.forwardFallback=[](TerrainCellPoint){throw std::invalid_argument("Joined diagnostic admission map must stay in range");};
            std::map<int,AdmissionCellView> borrowedCells;
            for(int id=0;id<2;++id){auto& c=cells[std::size_t(id)];c.point={std::int16_t(100+id),100};
                c.land=int(options[std::size_t(5+id)]);c.head=int(options[std::size_t(7+id)]);c.elevatedHead=c.head;c.ramp=std::uint8_t(options[std::size_t(9+id)]);
                gates.cells.emplace(id,AdmissionGateCellView{{c.point.x,c.point.y},c.head});
                borrowedCells.emplace(id,AdmissionCellView{c.registry,c.movement.level,c.ramp,c.movement.flags,c.ground,c.elevated,c.house,c.elevatedHouse,c.land,c.elevatedHead});
            }
            admissionWorld.emplace(BorrowedUnitAdmissionWorld{std::move(gates),std::move(borrowedCells),{},registries,unusedSpeeds,offsets,
                [](char k,int id,int a,int b){event(k,id,a,b);}});
            admissionSpeeds.fill(std::uint32_t(options[4]));
            admissionServices={ [&](int id)->const int&{return cells.at(std::size_t(id)).overlay;},{},admissionSpeeds};
            q.admission=[&](WalkMovementCellView c,int dir,int l,int zero,int one){
                const int id=c.identity==&cells[0].movement?0:1;event('I',id,dir,l,zero,one);
                if(zero!=0||one!=1)throw std::invalid_argument("Queued admission argument association");
                const int result=ordinaryInfantryAdmission(0,id,dir,l,-1,one,*admissionWorld,{flag32d,flag370,speedType,loading},admissionServices);
                event('a',result,0,0);return result;
            };
        }
        WalkMovementServices services;services.trace=[](auto c,auto x,auto y,auto z){event(c,x,y,z);};services.speed=[&]{return int(v[8]);};
        const int baseSpeed=int(v[8]);const float countrySpeed=std::bit_cast<float>(std::uint32_t(speedOptions[0]));
        const double speedMultiplier=std::bit_cast<double>(speedOptions[1]),veterancy=std::bit_cast<double>(speedOptions[2]),veteranBonus=std::bit_cast<double>(speedOptions[3]);
        const auto speedFlag=std::uint8_t(speedOptions[4]),speedTypeFlag=std::uint8_t(speedOptions[5]),veteranSpeed=std::uint8_t(speedOptions[6]),eliteSpeed=std::uint8_t(speedOptions[7]);
        InfantrySpeedServices speedServices{
            [&]{return InfantrySpeedType{baseSpeed,veteranSpeed,eliteSpeed,speedTypeFlag};},
            [&]()->const float&{return countrySpeed;},[&]()->const double&{return veteranBonus;},
            [](char k,int x){event(k,x);}};
        if(speedMode)services.speed=[&]{return infantrySpeed({veterancy,percentage,speedMultiplier,speedFlag},speedServices);};
        services.placement.mark=[](int kind){event('K',kind);};services.placement.floor=[&](Coord p){event('F','s',p.x,p.y,p.z);return int(v[9]);};
        services.lookup=[&](TerrainCellPoint p)->WalkMovementCellView{event('B',p.x,p.y);return borrowWalkCell(cells[std::size_t((p.x^p.y)&1)].movement);};
        services.currentCell=[&](Coord p)->WalkMovementCellView{return borrowWalkCell(lookup(p).movement);};
        services.dirty=[&](WalkMovementCellView c){event("Dirt",c.identity==&cells[0].movement?0:1);};
        arrival.services.notify=[](int k){event('J',k);};arrival.services.destination=[](int a,int b){event('G',a,b);};arrival.services.resetMovement=[](){event('X');};
        std::uint8_t disabled204=0,disabled205=0,resetFlag=0;double projectionScale=1;
        WalkCommandServices commands;commands.trace=services.trace;
        commands.cellFlags=[&](Coord p){event('B',p.x,p.y,p.z);return cells[std::size_t(identity(p))].movement.flags;};
        commands.projectionScale=[&]()->const double&{return projectionScale;};
        commands.resetMovement=[&]{event('X',0,0,0);resetInfantryWalkMovement(resetFlag,[](int k,int a,int b){event('N',k,a,b);},services.trace);};
        // Explicit proof composition, using the same actor/Walk/route/House and
        // occupation/admission/speed as every Process below. Nothing is reseeded
        // after the Infantry command clears route[0].4C3000 stays supplied.
        std::array<int,3> retry{int(f[1]),int(f[2]),int(f[3])},wait{31,37,41};
        int counter=int(f[4]),infantryState=int(f[5]),field490=19,session=1,targetIdentity=1;
        int liveTick=int(f[9]),orderDelay=8;std::uint8_t suspended=0,jumpJet=0,c0d=0,c00=0,human=1,human2=0;
        std::uint32_t references=3,globalReferences=7;const void* effect=nullptr;
        double interval=std::bit_cast<double>(intervalBits);
        WalkRouteContext refill{{retry[0],retry[1],retry[2]},counter,infantryState,target,jumpJet,interval,int(f[6]),
            [&]{return liveTick;},[&](TerrainCellPoint p,int a,int b){
                event('f',p.x,p.y,a,b,int(f[8]));
                for(int i=0;i<f[7];++i){route[std::size_t(i)]=int(v[6]);event('A',0x4d0+4*i,std::uint32_t(v[6]),0);}
                if(f[7]<24){route[std::size_t(f[7])]=-1;event('A',0x4d0+4*f[7],UINT32_MAX,0);}
                if(f[11]&2)w.destination={add(int(v[3]),257),add(int(v[4]),-513),add(int(v[5]),7)};
                return std::uint8_t(f[8]);}};
        FootDestinationView foot{field490,target,suspended,a1,{retry[0],retry[1],retry[2]},{wait[0],wait[1],wait[2]},{globalReferences,references}};
        InfantryDestinationActor infantry{foot,route,mission,infantryState,speedFlag,jumpJet,c0d,c00,effect};
        InfantryDestinationServices destination;
        destination.house=[&]{return InfantryDestinationHouse{session,human,human2};};
        destination.foot.trace=[](char k,int a,int b,std::int64_t c){event('d',k,a,b,c);};
        destination.foot.tick=[&]{return liveTick;};destination.foot.delay=[&]{return orderDelay;};
        destination.foot.targetId=[&](const void* p){if(p!=&targetIdentity)throw std::invalid_argument("Route target identity");return 1;};
        destination.foot.coordinates=[&](const void* p){if(p!=&targetIdentity)throw std::invalid_argument("Route coordinate target");
            event('d','Q',int(v[3]),int(v[4]),int(v[5]));return Coord{int(v[3]),int(v[4]),int(v[5])};};
        WalkCommandServices destinationCommands=commands;
        destinationCommands.trace=[](char k,std::int64_t x,std::int64_t y,std::int64_t z){event('d',k,x,y,z);};
        destinationCommands.cellFlags=[&](Coord p){event('d','B',p.x,p.y,p.z);return cells[std::size_t(identity(p))].movement.flags;};
        destinationCommands.resetMovement=[&]{event('d','X',0,0,0);resetInfantryWalkMovement(resetFlag,{},destinationCommands.trace);};
        const auto order=[&](const void* p,int flag){setOrdinaryInfantryDestination(infantry,w,{frozen,disabled204,disabled205},p,std::uint8_t(flag),add(int(f[6]),17),destination,destinationCommands);};
        if(routeMode){
            route[0]=-1;q.route=&refill;target=f[10]?&targetIdentity:nullptr;
            services.trace=[&](auto k,auto x,auto y,auto z){event(k,x,y,z);if(k=='A'&&x==0x530&&(f[11]&1)){liveTick=add(liveTick,13);interval=2.5;}};
            arrival.services.destination=[&](int a,int b){if(a)throw std::logic_error("Arrival destination must be null");order(nullptr,b);};
            arrival.services.resetMovement=[&]{event('X',0,0,0);resetInfantryWalkMovement(resetFlag,{},services.trace);};
            if(f[0]){w.destination={};w.moving34=0;order(&targetIdentity,1);event('O',1,0,0);}
        }
        const auto mode=std::array{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}[sequence++%4];std::fesetround(mode);
        if(commandMode){
            // This mode supplies a route as before but issues an actual Walk
            // interface command instead of seeding the final destination/byte.
            w.destination={};w.moving34=0;
            moveWalkTo(w,{frozen,disabled204,disabled205},{int(v[3]),int(v[4]),int(v[5])},commands);
            event('R',0,0,0);
        }
        for(int tick=0;tick<v[7];++tick){
            if(commandMode&&tick==stopAt){stopWalkMovement(w,commands);event('R',1,0,0);}
            if(routeMode)liveTick=add(int(f[9]),tick);
            lookups=0;const auto result=processQueuedWalk(w,{ground,body,frozen,percentage,a1,a2},n,services,arrival,q,routeMode?liveTick:tick);
            if(std::fegetround()!=mode)throw std::logic_error("Queued Walk leaked host FP mode");
            event('R',int(result),'P',ground.position.x,ground.position.y,ground.position.z,w.destination.x,w.destination.y,w.destination.z,w.head.x,w.head.y,w.head.z,
                int(w.moving34),int(w.inProcessing35),int(w.reallyMoving36),int(ground.marked74),int(ground.bridge79),int(on),int(a2),int(transition),int(a1),std::bit_cast<std::uint64_t>(percentage),
                body.desired,body.start,body.timerStart,body.duration);
            for(auto x:route)event(x);
        }
        event('Z');for(const auto& c:cells)event(c.ground,c.elevated,c.movement.flags,c.house,c.elevatedHouse,int(c.movement.level));
        event("rng",random.next1,random.next2);for(auto word:random.table)event(word);
        if(routeMode)event("owners",counter,infantryState,field490,int(target!=nullptr),int(suspended),int(resetFlag),references,globalReferences,
            retry[0],retry[1],retry[2],wait[0],wait[1],wait[2],liveTick,std::bit_cast<std::uint64_t>(interval));
        std::cout<<'\n';std::fesetround(saved);
    }
    return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
