// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/InfantryAdmission.hpp"
#include "sim/FootPermissionOverride.hpp"
#include "assets/NearbyCellAdmission.hpp"
#include "sim/BorrowedUnitAdmission.hpp"
#include <cfenv>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void event(char k,int a=0,int b=0,int c=0){std::cout<<k<<' '<<a<<' '<<b<<' '<<c<<' ';}
int number(std::istream& in,int lo,int hi){int n=0;in>>n;if(!in||n<lo||n>hi)throw std::invalid_argument("Invalid admission input");return n;}
std::uint32_t bits(std::istream& in){std::uint64_t n=0;in>>n;if(!in||n>0xffffffff)throw std::invalid_argument("Invalid admission bits");return std::uint32_t(n);}
BorrowedUnitAdmissionWorld bindWorld(UnitAdmissionWorld& w){
    AdmissionHouses houses{[&w](int id){const auto& h=w.gates.houses.at(id);return AdmissionHouseView{h.index,h.allies};},
        [&w](int id){return w.gates.houses.contains(id);}};
    BorrowedMovementGateWorld gates{houses,{},{},w.gates.slots,w.gates.fallbackCell,w.gates.tick,w.gates.setPadding,w.gates.commencePadding};
    for(auto& [id,g]:w.gates.objects)gates.objects.emplace(id,AdmissionGateObjectView{g.kind,g.next,g.owner,g.gate,g.animation18,g.animation19,g.mission,g.statusA8,g.lastAC,g.timerStart,g.timerPadding,g.timerRemaining});
    std::map<int,AdmissionCellView> cells;
    for(auto& [id,c]:w.cells){auto& g=w.gates.cells.at(id);
        gates.cells.emplace(id,AdmissionGateCellView{{g.point.x,g.point.y},g.head});
        cells.emplace(id,AdmissionCellView{c.registry,c.level,c.ramp,c.flags,c.occupation,c.elevatedOccupation,c.owner,c.elevatedOwner,c.land,c.elevatedHead});}
    gates.forwardFallback=[&](TerrainCellPoint p){w.gates.storeFallbackPoint(p);};
    return {std::move(gates),std::move(cells),{},w.registry,w.speedBits,w.directions,w.trace};
}
void guards(){
    UnitAdmissionWorld w;std::vector<int> slots(262144,0);w.gates.slots=slots;w.gates.fallbackCell=0;
    w.gates.cells[0]={};w.cells[0]={};w.gates.houses[0]={0,1};w.gates.objects[0].owner=0;w.gates.objects[1].owner=0;
    for(int d=0;d<8;++d){const auto [x,y]=directionOffset(d);w.directions[std::size_t(d)]={std::int16_t(x),std::int16_t(y)};}
    std::array<std::uint32_t,108> speeds;speeds.fill(0x3f800000);int overlay=-1,speedType=1,loading=1,queries=0;
    std::uint8_t flag32d=0,flag370=0;InfantryAdmissionActor actor{flag32d,flag370,speedType,loading};
    InfantryAdmissionServices services{[&](int)->const int&{++queries;return overlay;},{},speeds};
    auto world=bindWorld(w);if(queries)throw std::runtime_error("Borrowing Infantry admission queried world");
    const auto check=[&](int expected){if(ordinaryInfantryAdmission(0,0,2,0,0,1,world,actor,services)!=expected)throw std::runtime_error("Live Infantry fields differ");};
    check(0);w.cells[0].occupation=32;check(2);w.cells[0].occupation=28;check(7);w.cells[0].owner=0;check(2);
    w.cells[0].owner=33;w.gates.houses[0].allies=2;check(2);w.cells[0].occupation=0;w.cells[0].owner=-1;
    speeds[1]=0xbf800000;check(0);speeds[1]=0x80000000;check(7);speeds[1]=0x7f800001;check(7);
    flag370=255;speedType=INT32_MIN;check(0);flag370=0;speedType=1;speeds[1]=0x3f800000;
    const auto refused=[&]{try{check(0);}catch(const std::invalid_argument&){return;}throw std::runtime_error("Unjoined Infantry child accepted");};
    flag32d=1;loading=0;refused();loading=1;check(0);flag32d=0;
    overlay=7;refused();overlay=-1;w.gates.cells[0].head=1;refused();w.gates.cells[0].head=0;check(0);
    w.cells[0].owner=1;w.gates.houses[0].allies=0;refused();w.cells[0].owner=-1;
    auto missing=services;missing.overlay={};
    if(ordinaryInfantryAdmission(0,0,2,5,0,1,world,actor,missing)!=0)throw std::runtime_error("Early level success demanded overlay");
    w.cells[0].registry=0;w.registry.push_back(UnitAdmissionRegistry{{0,0},2});
    missing.registryOrigin=[](int){return TerrainCellPoint{1,0};};
    if(ordinaryInfantryAdmission(0,0,8,0,0,1,world,actor,missing)!=0)throw std::runtime_error("Distinct registry points ignored");
    // Native live-owner/refusal coverage; original matrix separately verifies
    // the supported complete caller path and its repeated child queries.
    const void* transport=nullptr;std::uint8_t c10=0,c11=0,c14=0,moving=0;
    w.gates.objects.at(0).mission.mission98=12;w.gates.objects.at(1).kind=15;
    InfantryResidentServices rs{transport,c10,c11,c14};rs.ally4E5580=[](int,int){return true;};rs.moving10=[&](int){return moving;};
    int stationary=0;
    const auto resident=[&]{return ordinaryInfantryResident(0,1,stationary,world,rs);};
    if(resident()||stationary!=1)throw std::runtime_error("Stationary Infantry not counted");
    moving=255;if(resident()||stationary!=1)throw std::runtime_error("Raw moving byte not preserved");
    const auto reject=[&]{try{resident();}catch(const std::invalid_argument&){return;}throw std::runtime_error("Unsupported resident accepted");};
    transport=&w;reject();transport=nullptr;c14=1;reject();c14=0;
    w.gates.objects.at(0).mission.mission98=5;c11=128;reject();c11=0;
    if(resident())throw std::runtime_error("Ordinary mission5 with zeroC11 refused");
    for(int mission:{7,8,9,11}){w.gates.objects.at(0).mission.mission98=mission;reject();}
    w.gates.objects.at(0).mission.mission98=17;c10=1;reject();c10=0;
    w.gates.objects.at(0).mission.mission98=12;w.gates.objects.at(1).kind=6;reject();w.gates.objects.at(1).kind=15;
    rs.ally4E5580=[](int,int){return false;};reject();rs.ally4E5580={};reject();
    rs.ally4E5580=[](int,int){return true;};rs.moving10={};reject();
    std::cout<<"Infantry borrowed ownership, raw speed and entered child guards PASS\n";
}
}

int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)throw std::invalid_argument("Unexpected Infantry argument");
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;std::array<int,8> residentOptions{};const bool residentJoin=op=='J';
        if(residentJoin){for(auto& v:residentOptions)v=number(in,0,255);in>>op;}
        std::array<int,9> permissionOptions{};const bool permissionJoin=op=='P';
        if(permissionJoin){for(auto& v:permissionOptions)in>>v;if(!in)throw std::invalid_argument("Permission options");
            for(int i=0;i<4;++i)if(permissionOptions[std::size_t(i)]<0||permissionOptions[std::size_t(i)]>255)throw std::invalid_argument("Permission byte");in>>op;}
        if(op!='I')throw std::invalid_argument("Infantry input needs I prefix");
        std::array<int,13> options{};for(auto& x:options)if(!(in>>x))throw std::invalid_argument("Infantry options");
        if(options[0]<0||options[0]>255||options[1]<0||options[1]>255)throw std::invalid_argument("Infantry raw flag");
        for(int i=4;i<10;++i)if(options[std::size_t(i)]<-32768||options[std::size_t(i)]>32767)throw std::invalid_argument("Registry origin word");
        in>>op;
        if(op!='W')throw std::invalid_argument("Invalid admission command");
        UnitAdmissionWorld w;in>>w.gates.tick;int slots[2]{};
        for(int& n:slots)n=number(in,-1,262143);
        if(slots[0]!=-1&&slots[0]==slots[1])throw std::invalid_argument("Aliased admission slots");
        const int count=number(in,0,3);
        for(auto& p:w.directions){p.x=std::int16_t(number(in,-32768,32767));p.y=std::int16_t(number(in,-32768,32767));}
        for(auto& n:w.speedBits)n=bits(in);
        for(int i=0;i<3;++i){in>>w.gates.houses[i].index;w.gates.houses[i].allies=bits(in);}
        for(int i=0;i<3;++i){const int present=number(in,0,1);UnitAdmissionRegistry r;
            r.point.x=std::int16_t(number(in,-32768,32767));r.point.y=std::int16_t(number(in,-32768,32767));in>>r.direction;
            if(i<count)w.registry.push_back(present?std::optional(r):std::nullopt);}
        for(int i=0;i<3;++i){auto& c=w.cells[i];auto& g=w.gates.cells[i];
            g.point.x=std::int16_t(number(in,-32768,32767));g.point.y=std::int16_t(number(in,-32768,32767));
            c.registry=std::int16_t(number(in,-32768,32767));c.level=std::int8_t(number(in,-128,127));c.ramp=std::uint8_t(number(in,0,255));
            c.flags=bits(in);c.occupation=bits(in);c.elevatedOccupation=bits(in);in>>c.owner>>c.elevatedOwner;
            c.land=number(in,0,11);g.head=number(in,-1,4);c.elevatedHead=number(in,-1,4);}
        w.gates.fallbackCell=2;std::vector<int> table(262144,-1);for(int i=0;i<2;++i)if(slots[i]!=-1)table[std::size_t(slots[i])]=i;w.gates.slots=table;
        for(int i=0;i<5;++i){auto& o=w.objects[i];auto& g=w.gates.objects[i];
            g.kind=number(in,1,6);if(g.kind!=1&&g.kind!=6)throw std::invalid_argument("Unsupported admission kind");
            g.next=number(in,-1,4);g.owner=number(in,0,2);g.gate=std::uint8_t(number(in,0,255));in>>g.mission.mission98;g.mission.queuedA0=7;
            g.animation18=std::uint8_t(number(in,0,255));g.animation19=std::uint8_t(number(in,0,255));
            o.flags=std::uint8_t(number(in,0,255));o.crushable=std::uint8_t(number(in,0,255));o.crusher=std::uint8_t(number(in,0,255));
            o.train=std::uint8_t(number(in,0,255));o.building1350=std::uint8_t(number(in,0,255));in>>o.state1b8;
            o.target=number(in,-1,4);o.destination=number(in,-1,4);o.weapon=number(in,0,1);o.projectile275=number(in,0,1);
            if(i&&o.target!=-1)throw std::invalid_argument("Moving admission resident unsupported");
        }
        if(w.gates.objects.at(0).kind!=1)throw std::invalid_argument("Admission mover is not Unit");
        for(int id=0;id<5;++id){int p=id,n=0;while(p!=-1){if(++n>5)throw std::invalid_argument("Cyclic admission fixture");p=w.gates.objects.at(p).next;}}
        w.trace=event;w.gates.trace=[](char k,int id){event(k,id);};
        std::array<std::uint32_t,108> speeds;for(std::size_t i=0;i<108;++i)speeds[i]=w.speedBits[i/9];
        auto flag32d=std::uint8_t(options[0]),flag370=std::uint8_t(options[1]);
        InfantryAdmissionActor actor{flag32d,flag370,options[2],options[3]};
        InfantryAdmissionServices services{[&](int id)->const int&{return options[std::size_t(10+id)];},
            [&](int id){return TerrainCellPoint{std::int16_t(options[std::size_t(4+2*id)]),std::int16_t(options[std::size_t(5+2*id)])};},speeds};
        std::uint8_t overrideFlag=std::uint8_t(permissionOptions[1]);int teamToken=0;
        const void* team=permissionOptions[2]?&teamToken:nullptr;
        if(permissionJoin){
            const MapPermissionShape shape{permissionOptions[4],permissionOptions[5],permissionOptions[6],permissionOptions[7],permissionOptions[8]};
            services.permission=[&,shape](int id,std::uint8_t elevation){
                event('B',id,elevation);const auto& c=w.cells.at(id);const auto& point=w.gates.cells.at(id).point;
                MapCellInput input;input.position={point.x,point.y};input.level=c.level;input.slope=c.ramp;
                return nearbyCellPermitted(input,elevation,shape);
            };
            services.permissionOverride=[&](int id){
                event('b',id);FootPermissionOverrideServices override;
                override.typeTrainAa0=[&]{event('T',id);return std::uint8_t(permissionOptions[0]);};
                override.mission=[&]{event('M',id);return unitDiscoveryMission(w.gates.objects.at(id).mission);};
                override.teamPredicate=[&](const void* p){if(p!=team)throw std::invalid_argument("Foreign Team owner");event('q',id,permissionOptions[3]);return std::uint8_t(permissionOptions[3]);};
                return footPermissionOverride({flag32d,overrideFlag,team},override);
            };
        }
        if(residentJoin)for(auto& [id,g]:w.gates.objects)g.kind=15;
        auto borrowed=bindWorld(w);
        const void* transport=nullptr;
        const auto c10=std::uint8_t(residentOptions[5]),c11=std::uint8_t(residentOptions[6]),c14=std::uint8_t(residentOptions[7]);
        if(residentJoin)services.resident=[&](int mover,int resident,int& count){
            InfantryResidentServices r{transport,c10,c11,c14};
            r.ally4E5580=[&](int left,int right){return unit_admission_policy::house(w.gates.objects.at(left).owner,w.gates.objects.at(right).owner,borrowed);};
            r.moving10=[&](int id){event('v',id,residentOptions[std::size_t(id)]);return std::uint8_t(residentOptions[std::size_t(id)]);};
            return ordinaryInfantryResident(mover,resident,count,borrowed,r);
        };
        const int previousMode=std::fegetround();std::fesetround(w.gates.tick%2?FE_UPWARD:FE_DOWNWARD);
        const int steps=number(in,1,128);
        for(int j=0;j<steps;++j){char k=0;in>>k;const int mover=number(in,0,0),target=number(in,0,2);
            int direction=0,level=0;in>>direction>>level;const int previous=number(in,-1,2),consult=number(in,0,255);auto elevated=std::uint8_t(number(in,0,255));
            int result=0;
            if(k=='U')result=ordinaryInfantryAdmission(mover,target,direction,level,previous,consult,borrowed,actor,services);
            else if(k=='T')result=unit_admission_policy::unitTerrainAdmission(target,direction,level,elevated,previous,borrowed);
            else throw std::invalid_argument("Unknown admission action");
            event('R',result,level,elevated);const auto p=w.gates.cells.at(2).point;event('z',p.x,p.y);
        }
        std::fesetround(previousMode);in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing admission command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
