// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/InfantryDestination.hpp"
#include <iostream>
#include <sstream>
#include <bit>
using namespace ra2;
template<class... T>void output(T... x){((std::cout<<x<<' '),...);}
void guards(){
    int f=17,tick=100,delay=8,state=0,session=0;const void* target=nullptr;const void* effect=nullptr;
    std::uint8_t suspended=0,reached=173,flag=0,jump=0,c0d=0,c00=0,human=1,human2=0,disabled=0;
    std::uint32_t refs=3,global=7;int frozen=0;std::array<int,3> retry{},wait{};std::array<int,24> route;route.fill(91);
    FootDestinationView foot{f,target,suspended,reached,{retry[0],retry[1],retry[2]},{wait[0],wait[1],wait[2]},{global,refs}};
    UnitDiscoveryActor mission;mission.mission98=2;
    InfantryDestinationActor actor{foot,route,mission,state,flag,jump,c0d,c00,effect};WalkMovementState walk{{17,23,31},{},0,197,255};
    InfantryDestinationServices s;s.house=[&](){return InfantryDestinationHouse{session,human,human2};};
    s.foot.tick=[&](){return tick;};s.foot.delay=[&](){return delay;};s.foot.targetId=[](const void*){return 1;};
    int cell=0;s.foot.coordinates=[&](const void* p){if(p!=&cell)throw std::logic_error("Wrong late target");return Coord{1,-31,7};};
    s.foot.trace=[&](char k,int off,int,int64_t){if(k=='a'&&off==0x558){tick=101;delay=99;}};
    WalkCommandServices ws;ws.cellFlags=[](Coord){return 0u;};ws.resetMovement=[]{};
    setOrdinaryInfantryDestination(actor,walk,{frozen,disabled,disabled},&cell,1,23,s,ws);
    if(target!=&cell||retry!=std::array{101,-31,0}||wait!=std::array{100,-31,8}||refs!=3||global!=7||route[0]!=-1||route[23]!=91)
        throw std::logic_error("Borrowed Foot timers/references/tails differ");
    bool refused=false;try{setOrdinaryInfantryDestination(actor,walk,{frozen,disabled,disabled},&cell,0,0,s,ws);}catch(const UnsupportedFootDestination&){refused=true;}
    if(!refused)throw std::logic_error("Moving retarget silently admitted");
    walk.moving34=0;jump=1;refused=false;
    try{setOrdinaryInfantryDestination(actor,walk,{frozen,disabled,disabled},&cell,0,0,s,ws);}catch(const UnsupportedFootDestination&){refused=true;}
    if(!refused)throw std::logic_error("JumpJet silently admitted");
    state=27;setOrdinaryInfantryDestination(actor,walk,{frozen,disabled,disabled},&cell,0,0,s,ws);
    state=0;jump=0;mission.mission98=7;refused=false;
    try{setOrdinaryInfantryDestination(actor,walk,{frozen,disabled,disabled},nullptr,0,0,s,ws);}catch(const UnsupportedFootDestination&){refused=true;}
    if(!refused)throw std::logic_error("Transport silently admitted");
    refs=0;refused=false;try{setInfantryFootDestination(actor,walk,{frozen,disabled,disabled},&cell,0,s,ws);}catch(const UnsupportedFootDestination&){refused=true;}
    if(!refused||global!=7)throw std::logic_error("Unretained interface admitted");
    std::cout<<"Infantry destination borrowed-owner and entered-child guards PASS\n";
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)throw std::invalid_argument("Unexpected Infantry destination argument");
    std::string line;
    while(std::getline(std::cin,line)){
        std::istringstream in(line);char prefix=0;in>>prefix;
        const auto word=[&](){std::int64_t n=0;if(!(in>>n)||n<INT32_MIN||n>UINT32_MAX)throw std::invalid_argument("Destination word");return signed32(std::uint32_t(n));};
        const auto byte=[&](){int n=word();if(n<0||n>255)throw std::invalid_argument("Destination byte");return std::uint8_t(n);};
        const auto point=[&](){const int x=word(),y=word(),z=word();return Coord{x,y,z};};
        UnitDiscoveryActor mission;mission.mission98=word();mission.queuedA0=word();int session=word();
        auto human=byte(),human2=byte();int state=word();auto flag=byte(),jump=byte(),c0d=byte(),c00=byte();
        int field=word(),initial=word();auto suspended=byte(),reached=byte();std::uint32_t refs=std::uint32_t(word()),global=std::uint32_t(word());
        auto moving=byte(),processing=byte(),really=byte(),resetFlag=byte();int frozen=word();auto disabled=byte(),disabled2=byte();
        int tick=word(),delay=word(),mask=word();std::uint32_t flags=std::uint32_t(word());
        WalkMovementState walk{point(),point(),moving,processing,really};const std::array points{point(),point()};
        std::array<int,24> route;for(auto& x:route)x=word();std::array<int,3> retry,wait;for(auto& x:retry)x=word();for(auto& x:wait)x=word();
        std::uint64_t scaleBits=0;if(!(in>>scaleBits)||prefix!='F'||initial<0||initial>2||mask<0||mask>63||!refs||refs>=0x7fffffff)
            throw std::invalid_argument("Infantry destination profile");
        double scale=std::bit_cast<double>(scaleBits);std::array<int,2> identities{};
        const auto targetFor=[&](int id)->const void*{if(id<0||id>2)throw std::invalid_argument("Destination target");return id?&identities[std::size_t(id-1)]:nullptr;};
        const auto idFor=[&](const void* p){if(!p)return 0;for(int i=1;i<=2;++i)if(p==targetFor(i))return i;throw std::invalid_argument("Unknown target identity");};
        const void* target=targetFor(initial);const void* effect=nullptr;
        const auto add=[](int a,int b){return signed32(std::uint32_t(a)+std::uint32_t(b));};
        const auto animation=[&](int k,int x,int y){output('N',k,x,y);if(mask&32){flag^=128;c00^=255;}};
        const auto trace=[&](char k,int x,int y,std::int64_t z){output(k,x,y,z);
            if(k=='G'){if(mask&1)target=targetFor(2);if(mask&2)suspended^=128;}
            if(k=='a'&&x==0x558&&(mask&8)){tick=add(tick,13);delay=add(delay,17);}
        };
        FootDestinationView foot{field,target,suspended,reached,{retry[0],retry[1],retry[2]},{wait[0],wait[1],wait[2]},{global,refs}};
        InfantryDestinationActor actor{foot,route,mission,state,flag,jump,c0d,c00,effect};
        InfantryDestinationServices s;s.house=[&](){return InfantryDestinationHouse{session,human,human2};};s.animation=animation;
        s.foot.trace=trace;s.foot.targetId=idFor;s.foot.tick=[&](){return tick;};s.foot.delay=[&](){return delay;};
        s.foot.coordinates=[&](const void* p){const auto value=points[std::size_t(idFor(p)-1)];output('Q',value.x,value.y,value.z);
            if(mask&4){tick=add(tick,7);delay=add(delay,9);}return value;};
        WalkCommandServices ws;ws.trace=[](char k,std::int64_t x,std::int64_t y,std::int64_t z){output(k,x,y,z);};
        ws.cellFlags=[&](Coord p){output('B',p.x,p.y,p.z);if(mask&16)walk.destination.z=add(walk.destination.z,7);return flags;};
        ws.projectionScale=[&]()->const double&{return scale;};
        ws.resetMovement=[&](){output('X',0,0,0);resetInfantryWalkMovement(resetFlag,animation,ws.trace);};
        int count=word();if(count<1||count>32)throw std::invalid_argument("Destination operation count");
        for(int i=0;i<count;++i){int mode=word(),id=word();auto control=byte();int padding=word();
            if(mode==1)setOrdinaryInfantryDestination(actor,walk,{frozen,disabled,disabled2},targetFor(id),control,padding,s,ws);
            else if(mode==0)setInfantryFootDestination(actor,walk,{frozen,disabled,disabled2},targetFor(id),padding,s,ws);
            else throw std::invalid_argument("Destination root");output('R',mode,0,0);
        }
        std::string tail;if(in>>tail)throw std::invalid_argument("Destination extra field");
        output('Z',field,idFor(target),int(suspended),int(reached),global,refs,int(flag),int(c00),int(resetFlag),tick,delay);
        for(int x:route)output(x);for(int x:retry)output(x);for(int x:wait)output(x);
        output(walk.destination.x,walk.destination.y,walk.destination.z,walk.head.x,walk.head.y,walk.head.z,int(walk.moving34),int(walk.inProcessing35),int(walk.reallyMoving36),flags,std::bit_cast<std::uint64_t>(scale));std::cout<<'\n';
    }
    return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
