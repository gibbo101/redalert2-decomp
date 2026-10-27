// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MovingUnitAdmission.hpp"
#include "borrowed_admission_fixture.hpp"
#include "assets/MovementData.hpp"
#include "assets/PreparedData.hpp"
#include "render/Lighting.hpp"
#include <cfenv>
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
    UnitAdmissionMotionWorld motion;refused=false;
    try{movingUnitAdmission(0,0,0,0,-1,1,w,motion);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Missing moving ownership accepted");
    DriveData data;UnitAdmissionMotionActor actor;actor.track=64;actor.queueHead=-2;
    if(admission_detail::switchPending(actor,data))throw std::runtime_error("Out-of-range queue did not return before transition access");
    actor.queueHead=2;refused=false;
    try{(void)admission_detail::switchPending(actor,data);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Missing ordinary transition accepted");
    std::cout<<"Missing Unit admission ownership refused: PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=4)throw std::invalid_argument("Expected private engine, direction and render data");
    const auto data=readDriveData(readFile(argv[1]),readFile(argv[2]));
    const auto render=readRenderData(readFile(argv[3]),PatchedEngineSha);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;if(op!='V')throw std::invalid_argument("Invalid admission command");
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

        }
        char separator=0;in>>separator;if(separator!='M')throw std::invalid_argument("Missing moving records");
        UnitAdmissionMotionWorld motion;motion.data=data.get();motion.squareRoot=[&](double n){return tableSqrt(render,n);};
        for(int i=0;i<5;++i){auto& a=motion.actors[i];
            in>>a.position.x>>a.position.y>>a.position.z>>a.destination.x>>a.destination.y>>a.destination.z>>a.head.x>>a.head.y>>a.head.z;
            a.body.desired=std::uint16_t(number(in,0,65535));a.body.start=std::uint16_t(number(in,0,65535));
            in>>a.body.timerStart>>a.body.duration;a.body.rate=std::uint16_t(number(in,0,65535));
            a.eligibility5a0=std::uint8_t(number(in,0,255));in>>a.queueHead;a.track=number(in,0,63);in>>a.index;
            a.shortTrack=std::uint8_t(number(in,0,255));
        }
        const int mode=number(in,0,3),prior=std::fegetround();
        const int rounding[]={FE_TONEAREST,FE_TOWARDZERO,FE_UPWARD,FE_DOWNWARD};std::fesetround(rounding[mode]);
        if(w.gates.objects.at(0).kind!=1)throw std::invalid_argument("Admission mover is not Unit");
        for(int id=0;id<5;++id){int p=id,n=0;while(p!=-1){if(++n>5)throw std::invalid_argument("Cyclic admission fixture");p=w.gates.objects.at(p).next;}}
        test::BorrowedAdmissionFixture fixture(w,motion);
        auto& borrowed=fixture.admission->world();
        borrowed.trace=event;borrowed.gates.trace=[](char k,int id){event(k,id);};
        const int steps=number(in,1,128);
        for(int j=0;j<steps;++j){char k=0;in>>k;const int mover=number(in,0,0),target=number(in,0,2);
            int direction=0,level=0;in>>direction>>level;const int previous=number(in,-1,2),consult=number(in,0,255);auto elevated=std::uint8_t(number(in,0,255));
            int result=0;
            if(k=='U')result=fixture.admission->admit(mover,target,direction,level,previous,std::uint8_t(consult));
            else if(k=='T')result=fixture.admission->terrain(target,direction,level,elevated,previous);
            else throw std::invalid_argument("Unknown admission action");
            if(std::fegetround()!=rounding[mode])throw std::runtime_error("Moving admission leaked FP rounding");
            event('R',result,level,elevated);const auto p=fixture.attributes[2].input.position;event('z',p.x,p.y);
        }
        std::fesetround(prior);
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing admission command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
