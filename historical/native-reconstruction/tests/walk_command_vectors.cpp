// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/WalkCommands.hpp"
#include <array>
#include <bit>
#include <cfenv>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace ra2;
void guards(){
    int frozen=1;std::uint8_t a=0,b=0,flag=0;WalkMovementState w{{17,23,31},{0,0,1},173,197,255};
    WalkCommandServices s;int resets=0;s.resetMovement=[&]{++resets;};
    moveWalkTo(w,{frozen,a,b},{128,256,17},s);
    if(w.destination!=Coord{17,23,31})throw std::logic_error("Guard mutated Walk destination");
    frozen=0;a=128;moveWalkTo(w,{frozen,a,b},{1,2,3},s);a=0;b=255;moveWalkTo(w,{frozen,a,b},{1,2,3},s);
    if(w.destination!=Coord{17,23,31})throw std::logic_error("Live raw actor guards ignored");
    b=0;stopWalkMovement(w,s);
    if(w.destination!=Coord{}||w.head!=Coord{0,0,1}||w.moving34!=173||w.reallyMoving36!=255||resets)
        throw std::logic_error("Stop cancelled a committed Z-only head");
    setWalkHeadImmediate(w,{},s);
    if(w.moving34||w.reallyMoving36!=255||w.inProcessing35!=197||resets!=1)throw std::logic_error("Immediate head reset differs");
    stopWalkMovement(w,s);stopWalkMovement(w,s);
    if(resets!=3||w.reallyMoving36)throw std::logic_error("Empty-head Stop reset must be unconditional");
    s.cellFlags=[&](Coord p){if(w.destination!=p)throw std::logic_error("Map query precedes command stores");w.destination.z=INT32_MAX;return 0x100u;};
    double scale=1;s.projectionScale=[&]()->const double&{return scale;};
    moveWalkTo(w,{frozen,a,b},{1,2,3},s);
    if(w.destination.z!=-2147483590||w.moving34!=1)throw std::logic_error("Late wrapped destination Z differs");
    bool refused=false;s.projectionScale={};
    try{moveWalkTo(w,{frozen,a,b},{1,2,3},s);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::logic_error("Entered bridge scale accepted without owner");
    resetInfantryWalkMovement(flag,{});flag=128;
    resetInfantryWalkMovement(flag,[&](int k,int x,int y){if(flag||k!=27||x||y)throw std::logic_error("Reset store/effect order differs");});
    if(flag)throw std::logic_error("Reset flag not cleared");
    std::cout<<"Walk command live-owner, retained-head, late-Z and reset guards PASS\n";
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)throw std::invalid_argument("Unexpected Walk command argument");
    std::string line;int sequence=0;const int saved=std::fegetround();
    while(std::getline(std::cin,line)){
        char c=0;std::array<std::uint64_t,19> v{};std::istringstream in(line);in>>c;
        for(auto& x:v)if(!(in>>x))throw std::invalid_argument("Missing Walk command field");
        if(c!='C')throw std::invalid_argument("Walk command prefix");
        for(int i=0;i<19;++i)if(i!=14&&v[std::size_t(i)]>UINT32_MAX)throw std::invalid_argument("Walk command dword");
        for(int i:{6,7,8,10,11,12})if(v[std::size_t(i)]>255)throw std::invalid_argument("Walk command byte");
        if(v[18]>31)throw std::invalid_argument("Walk command mutation");
        const auto integer=[](std::uint64_t n){return signed32(std::uint32_t(n));};
        const auto point=[&](int i){return Coord{integer(v[std::size_t(i)]),integer(v[std::size_t(i+1)]),integer(v[std::size_t(i+2)])};};
        WalkMovementState w{point(0),point(3),std::uint8_t(v[6]),std::uint8_t(v[7]),std::uint8_t(v[8])};
        int frozen=integer(v[9]);auto disabled=std::uint8_t(v[10]),disabled2=std::uint8_t(v[11]),resetFlag=std::uint8_t(v[12]);
        std::uint32_t flags=std::uint32_t(v[13]);double scale=std::bit_cast<double>(v[14]);const auto empty=point(15);const auto mask=v[18];
        const auto trace=[](char k,std::int64_t x,std::int64_t y,std::int64_t z){std::cout<<k<<' '<<x<<' '<<y<<' '<<z<<' ';};
        WalkCommandServices s;s.trace=trace;
        s.cellFlags=[&](Coord p){trace('B',p.x,p.y,p.z);
            if(mask&1){w.destination.x=signed32(std::uint32_t(w.destination.x)+257u);w.destination.z=signed32(std::uint32_t(w.destination.z)+7u);}
            if(mask&2)flags^=256;
            if(mask&4)scale=1.25;
            if(mask&8){w.moving34=173;w.reallyMoving36=197;}
            return flags;
        };
        s.projectionScale=[&]()->const double&{return scale;};
        s.resetMovement=[&]{trace('X',0,0,0);resetInfantryWalkMovement(resetFlag,[&](int k,int x,int y){trace('N',k,x,y);
            if(mask&16){w.head={7,9,11};w.moving34=255;w.reallyMoving36=17;resetFlag=128;}
        },trace);};
        int count=0;if(!(in>>count)||count<1||count>16)throw std::invalid_argument("Walk command count");
        const auto mode=std::array{FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO,FE_TONEAREST}[std::size_t(sequence++%4)];std::fesetround(mode);
        for(int i=0;i<count;++i){int op=0;std::array<std::uint64_t,3> raw{};
            if(!(in>>op>>raw[0]>>raw[1]>>raw[2])||op<0||op>2||raw[0]>UINT32_MAX||raw[1]>UINT32_MAX||raw[2]>UINT32_MAX)
                throw std::invalid_argument("Walk command operation");
            const Coord request{integer(raw[0]),integer(raw[1]),integer(raw[2])};
            if(op==0)moveWalkTo(w,{frozen,disabled,disabled2},request,s,empty);
            else if(op==1)stopWalkMovement(w,s,empty);
            else setWalkHeadImmediate(w,request,s,empty);
            trace('R',op,0,0);if(std::fegetround()!=mode)throw std::logic_error("Walk command leaked FP mode");
        }
        std::string extra;if(in>>extra)throw std::invalid_argument("Extra Walk command field");
        std::cout<<"Z "<<w.destination.x<<' '<<w.destination.y<<' '<<w.destination.z<<' '<<w.head.x<<' '<<w.head.y<<' '<<w.head.z<<' '
            <<int(w.moving34)<<' '<<int(w.inProcessing35)<<' '<<int(w.reallyMoving36)<<' '<<frozen<<' '<<int(disabled)<<' '<<int(disabled2)<<' '
            <<int(resetFlag)<<' '<<flags<<' '<<std::bit_cast<std::uint64_t>(scale)<<'\n';std::fesetround(saved);
    }
    return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
