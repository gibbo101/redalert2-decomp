// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/NearbyLocation.hpp"
#include "render/Lighting.hpp"
#include "assets/PreparedData.hpp"
#include <bit>
#include <cfenv>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
template<class T>T take(std::istream& in){T v{};if(!(in>>v))throw std::invalid_argument("Missing nearby-location input");return v;}
int number(std::istream& in,int lo,int hi){const auto n=take<int>(in);if(n<lo||n>hi)throw std::invalid_argument("Nearby-location field domain");return n;}
void guards(){
    int checks=0;const auto check=[&](bool ok){++checks;if(!ok)throw std::runtime_error("Nearby-location guard "+std::to_string(checks));};
    NearbyLocationWorld world;NearbyLocationOptions options;NearbyLocationServices services;NearbyLocationPoint close{},source{10,10};NearbyLocationCell cell;
    bool refused=false;try{nearbyLocation(source,close,options,world,services);}catch(const std::invalid_argument&){refused=true;}check(refused);
    int queries=0;services.lookup=[&](auto)->auto&{++queries;return cell;};
    check(nearbyLocation(source,close,options,world,services)==NearbyLocationPoint{}&&queries==1);
    world.dimension0=1;refused=false;try{nearbyLocation(source,close,options,world,services);}catch(const std::invalid_argument&){refused=true;}check(refused);
    services.permission=[](auto&,int){return true;};services.rectangle=[](auto,int,int,int,int,int,int,std::uint32_t,std::uint8_t){return true;};services.projectCenter=[](auto p){return p;};
    int projections=0;services.projectCenter=[&](auto p){++projections;return p;};
    check(nearbyLocation(source,close,options,world,services)==source&&projections==4); // two radius-zero duplicates, two final queries
    world.frame=-1;refused=false;try{nearbyLocation(source,close,options,world,services);}catch(const std::invalid_argument&){refused=true;}check(refused);
    world.frame=1;options.zone=65535;bool zoneSeen=false;services.rectangle=[&](auto,int,int,int,int zone,int,int,std::uint32_t,std::uint8_t){zoneSeen=zone==-1;return true;};
    check(nearbyLocation(source,close,options,world,services)==source&&zoneSeen);
    close={-32768,-32768};source={32767,32767};int negativeInputs=0;
    services.squareRoot=[&](double n){if(n==-262142.)++negativeInputs;return 1.;};
    // The original signed squared sum wraps before its sqrt helper, which
    // accepts negatives. Do not widen, clamp, or reject this original input.
    check(nearbyLocation(source,close,options,world,services)==source&&negativeInputs==2);
    source={10,10};close={12,12};int calls=0;services.squareRoot=[&](double){++calls;throw std::runtime_error("diagnostic");return 0.;};
    const int old=std::fegetround();std::fesetround(FE_UPWARD);refused=false;
    try{nearbyLocation(source,close,options,world,services);}catch(const std::runtime_error&){refused=true;}
    check(refused&&calls==1&&std::fegetround()==FE_UPWARD);std::fesetround(old);
    std::cout<<checks<<" native nearby-location guard checks PASS\n";
}
struct Cell {NearbyLocationCell value;NearbyLocationPoint point;bool permitted=false,rectangle=false,burrowable=false,projection=false;};
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=2)throw std::invalid_argument("Expected private render data");
    std::ifstream input(argv[1],std::ios::binary);Bytes raw(69944);
    if(!input.read(reinterpret_cast<char*>(raw.data()),std::streamsize(raw.size()))||input.peek()!=std::char_traits<char>::eof())throw std::invalid_argument("Render data extent");
    const auto render=readRenderData(Data(std::move(raw)),PatchedEngineSha);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);if(take<char>(in)!='N')return 2;
        const int mode=number(in,0,3);const int modes[]{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(modes[mode]);
        const auto point=[&](){const int x=number(in,-32768,32767),y=number(in,-32768,32767);return NearbyLocationPoint{std::int16_t(x),std::int16_t(y)};};
        const auto source=point();auto close=point();NearbyLocationWorld world;world.emptyCell=point();world.dimension0=take<int>(in);world.dimension1=take<int>(in);world.frame=take<int>(in);
        NearbyLocationOptions options;options.speedType=take<int>(in);options.zone=take<int>(in);options.movementZone=take<int>(in);options.alternate=take<std::uint32_t>(in);options.width=take<int>(in);options.height=take<int>(in);
        const auto byte=[&](){return std::uint8_t(number(in,0,255));};options.disallowOverlay=byte();options.matchLevel=byte();options.requireBurrowable=byte();options.allowBridge=byte();options.skipNorthWest=byte();
        const int flipAt=number(in,0,100000),mutation=number(in,0,2),mutationFrame=take<int>(in);const auto mutationClose=point();
        const int count=number(in,1,128);std::vector<Cell> cells(std::size_t(count),Cell{});std::vector<int> slots(262144,-1);
        for(int i=0;i<count;++i){
            const int slot=number(in,-1,262143);auto& c=cells[std::size_t(i)];c.point=point();c.value.level=std::int8_t(number(in,-128,127));c.value.flags=take<std::uint32_t>(in);
            c.permitted=number(in,0,1);c.rectangle=number(in,0,1);c.burrowable=number(in,0,1);c.projection=number(in,0,1);
            if(slot!=-1){if(i==count-1||slots[std::size_t(slot)]!=-1)throw std::invalid_argument("Nearby slot alias");slots[std::size_t(slot)]=i;}
            else if(i!=count-1)throw std::invalid_argument("Only final Cell is fallback");
        }
        std::string tail;if(in>>tail)throw std::invalid_argument("Extra nearby-location input");
        const auto event=[](auto... v){((std::cout<<v<<' '),...);};
        int projections=0;const auto id=[&](const NearbyLocationCell& c){for(int i=0;i<count;++i)if(&cells[std::size_t(i)].value==&c)return i;throw std::logic_error("Unowned Cell");};
        const auto lookup=[&](NearbyLocationPoint p,bool log)->Cell&{
            const auto index=std::bit_cast<std::int32_t>((std::uint32_t(std::int32_t(p.y))<<9)+std::uint32_t(std::int32_t(p.x)));
            const int found=index>=0&&index<262144?slots[std::size_t(index)]:-1;const int n=found<0?count-1:found;auto& c=cells[std::size_t(n)];
            if(found<0&&log){c.point=p;event('W',p.x,p.y);}
            if(log)event('L',p.x,p.y,n);return c;
        };
        NearbyLocationServices services;services.lookup=[&](auto p)->auto&{return lookup(p,true).value;};
        services.permission=[&](auto& value,int flag){const auto n=id(value);auto& c=cells[std::size_t(n)];event('B',n,c.point.x,c.point.y,flag,int(c.permitted));return c.permitted;};
        services.rectangle=[&](auto p,int width,int height,int speed,int zone,int movement,int unknown,std::uint32_t alternate,std::uint8_t overlay){
            auto& c=lookup(p,false);event('C',p.x,p.y,width,height,speed,zone,movement,unknown,alternate,int(overlay),int(c.rectangle));return c.rectangle;};
        services.burrowable=[&](auto& value){const auto n=id(value);event('b',n,int(cells[std::size_t(n)].burrowable));return cells[std::size_t(n)].burrowable;};
        services.projectCenter=[&](auto p){
            auto& c=lookup(p,false);++projections;const bool good=c.projection^(flipAt&&projections>=flipAt);event('P',p.x,p.y,int(good));
            if(projections==1&&mutation){world.frame=mutationFrame;event('X',world.frame);if(mutation==2){close=mutationClose;event('T',close.x,close.y);}}
            if(!good)p.x=std::bit_cast<std::int16_t>(std::uint16_t(std::uint16_t(p.x)+17u));return p;};
        services.squareRoot=[&](double squared){const auto result=tableSqrt(render,std::abs(squared));event('D',int(squared),std::bit_cast<std::uint64_t>(result));return result;};
        const auto result=nearbyLocation(source,close,options,world,services);event('R',result.x,result.y);
        if(std::fegetround()!=modes[mode])throw std::runtime_error("Nearby caller FP mode changed");
        event("state",cells.back().point.x,cells.back().point.y,world.frame,close.x,close.y,projections);std::cout<<'\n';
    }return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
