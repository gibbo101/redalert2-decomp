// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/UnitAdmission.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void event(char k,int a=0,int b=0,int c=0){std::cout<<k<<' '<<a<<' '<<b<<' '<<c<<' ';}
int number(std::istream& in,int lo,int hi){int n=0;in>>n;if(!in||n<lo||n>hi)throw std::invalid_argument("Invalid admission input");return n;}
std::uint32_t bits(std::istream& in){std::uint64_t n=0;in>>n;if(!in||n>0xffffffff)throw std::invalid_argument("Invalid admission bits");return std::uint32_t(n);}
void guards(){
    UnitAdmissionWorld w;bool refused=false;
    try{ordinaryUnitAdmission(0,0,0,0,-1,1,w);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Missing admission world accepted");
    std::cout<<"Missing Unit admission ownership refused: PASS\n";
}
void overlayGuards(){
    UnitAdmissionWorld w;
    std::vector<int> slots(262144,0);w.gates.slots=slots;w.gates.fallbackCell=0;
    w.gates.cells[0]={};w.cells[0]={};w.gates.houses[0]={0,1};
    w.gates.objects[0].owner=0;w.objects[0].weapon=true;w.speedBits.fill(0x3f800000);
    std::uint8_t flag=0,wall=0,crushable=0,human=0,control=0,weapon144=0,weapon146=0;
    int armor=0,owner=-1,overrideValue=0,cellQueries=0,houseQueries=0,weaponQueries=0;
    bool present=false;
    UnitAdmissionOverlayServices services{
        [&](int id)->std::optional<UnitAdmissionOverlayView>{
            if(id!=0)throw std::runtime_error("Overlay Cell identity changed");++cellQueries;
            if(!present)return {};
            return {{flag,wall,crushable,armor,owner}};
        },[&](int id){
            if(id!=0)throw std::runtime_error("Overlay House identity changed");++houseQueries;
            return UnitAdmissionOverlayHouseView{human,control};
        },[&](int id){
            if(id!=0)throw std::runtime_error("Overlay weapon identity changed");++weaponQueries;
            return UnitAdmissionOverlayWeaponView{weapon144,weapon146};
        },overrideValue};
    const auto check=[&](int expected){
        if(overlayUnitAdmission(0,0,2,0,0,1,w,services)!=expected)
            throw std::runtime_error("Live overlay fields were not consumed");
    };
    if(cellQueries||houseQueries||weaponQueries)throw std::runtime_error("Overlay binding made queries");
    check(0);present=true;flag=255;check(7);
    control=255;check(0);control=0;overrideValue=-1;check(0);
    overrideValue=0;human=255;check(0);
    flag=0;wall=255;crushable=255;w.objects[0].crusher=255;owner=1;check(0);
    owner=32;check(4);w.objects[0].crusher=0;weapon144=255;check(4);
    owner=1;check(5);weapon144=0;weapon146=255;armor=6;check(5);armor=5;check(7);
    w.objects[0].weapon=false;check(7);w.objects[0].weapon=true;
    const auto refused=[&](const UnitAdmissionOverlayServices& s){
        try{(void)overlayUnitAdmission(0,0,2,0,0,1,w,s);}
        catch(const std::invalid_argument&){return;}
        throw std::runtime_error("Missing entered overlay association accepted");
    };
    auto missing=services;missing.cell={};refused(missing);
    // Early returns must not demand or query skipped overlay associations.
    const int before=cellQueries;
    if(overlayUnitAdmission(0,0,8,0,0,1,w,missing)!=7||cellQueries!=before)
        throw std::runtime_error("Early registry return consulted overlay");
    flag=1;auto missingHouse=services;missingHouse.house={};refused(missingHouse);
    flag=0;auto missingWeapon=services;missingWeapon.weapon={};refused(missingWeapon);
    present=false;missingWeapon.house={};check(0);
    if(overlayUnitAdmission(0,0,2,0,0,1,w,missingWeapon)!=0)
        throw std::runtime_error("Absent overlay demanded unused associations");
    std::cout<<"Live overlay owners and entered association refusals: PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc==2&&std::string(argv[1])=="--overlay-guards"){overlayGuards();return 0;}
    const bool overlayMode=argc==2&&std::string(argv[1])=="--overlay";
    if(argc!=1&&!overlayMode)throw std::invalid_argument("Unexpected admission argument");
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;
        struct OverlayType {std::uint8_t flag27a,wall,crushable;int armor;};
        int overrideValue=0;std::array<std::array<std::uint8_t,2>,3> houses{};
        std::array<std::uint8_t,2> weapon{};std::array<std::array<int,2>,3> overlays{};
        std::array<OverlayType,3> types{};
        if(overlayMode){
            if(op!='V')throw std::invalid_argument("Overlay mode requires explicit overlay input");
            in>>overrideValue;
            for(auto& h:houses)for(auto& b:h)b=std::uint8_t(number(in,0,255));
            for(auto& b:weapon)b=std::uint8_t(number(in,0,255));
            for(auto& c:overlays){c[0]=number(in,-1,2);in>>c[1];}
            for(auto& t:types){t.flag27a=std::uint8_t(number(in,0,255));t.wall=std::uint8_t(number(in,0,255));
                t.crushable=std::uint8_t(number(in,0,255));in>>t.armor;}
            in>>op;
        }
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
        UnitAdmissionOverlayServices overlayServices{
            [&](int id)->std::optional<UnitAdmissionOverlayView>{
                const auto& c=overlays.at(std::size_t(id));event('o',id,c[0]);
                if(c[0]==-1)return {};
                const auto& t=types.at(std::size_t(c[0]));return {{t.flag27a,t.wall,t.crushable,t.armor,c[1]}};
            },[&](int id){const auto& h=houses.at(std::size_t(id));return UnitAdmissionOverlayHouseView{h[0],h[1]};},
            [&](int){return UnitAdmissionOverlayWeaponView{weapon[0],weapon[1]};},overrideValue};
        const int steps=number(in,1,128);
        for(int j=0;j<steps;++j){char k=0;in>>k;const int mover=number(in,0,0),target=number(in,0,2);
            int direction=0,level=0;in>>direction>>level;const int previous=number(in,-1,2),consult=number(in,0,255);auto elevated=std::uint8_t(number(in,0,255));
            int result=0;
            if(k=='U')result=overlayMode?overlayUnitAdmission(mover,target,direction,level,previous,std::uint8_t(consult),w,overlayServices):
                ordinaryUnitAdmission(mover,target,direction,level,previous,std::uint8_t(consult),w);
            else if(k=='T')result=unitTerrainAdmission(target,direction,level,elevated,previous,w);
            else throw std::invalid_argument("Unknown admission action");
            event('R',result,level,elevated);const auto p=w.gates.cells.at(2).point;event('z',p.x,p.y);
        }
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing admission command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
