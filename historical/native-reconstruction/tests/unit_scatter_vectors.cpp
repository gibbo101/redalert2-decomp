// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/UnitScatter.hpp"
#include "assets/MovementData.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
using namespace ra2;
template<class T>T take(std::istream& in){T v{};if(!(in>>v))throw std::invalid_argument("Missing Unit Scatter input");return v;}
int number(std::istream& in,int low,int high){auto v=take<int>(in);if(v<low||v>high)throw std::invalid_argument("Unit Scatter field domain");return v;}
void guards(){
    DirectionData directions;OriginalRandomState random;UnitScatterDriveLifetime lifetime;
    UnitScatterInputs w{directions,random,lifetime,{}};UnitScatterActor actor;UnitScatterServices services;
    actor.mission.mission98=0;lifetime.references=0;scatterUnit(actor,{},0,0,w,services);
    actor.mission.mission98=7;bool refused=false;
    try{scatterUnit(actor,{},0,0,w,services);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Missing retained Drive accepted");
    lifetime.references=3;lifetime.globalReferences=0xffffffffu;refused=false;
    try{scatterUnit(actor,{},0,0,w,services);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||lifetime.references!=3||lifetime.globalReferences!=0xffffffffu)throw std::runtime_error("Missing control ownership not released");
    services.missionControl=[](int,int){return std::uint8_t(1);};refused=false;
    try{scatterUnit(actor,{},0,0,w,services);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||lifetime.references!=3||lifetime.globalReferences!=0xffffffffu)throw std::runtime_error("Missing pathfinder not refused/released");
    std::cout<<"4 native guard checks PASS\n";
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=2)throw std::invalid_argument("Expected private prepared direction data");
    std::ifstream prepared(argv[1],std::ios::binary);Bytes bytes(16464);
    if(!prepared.read(reinterpret_cast<char*>(bytes.data()),std::streamsize(bytes.size()))||prepared.peek()!=std::char_traits<char>::eof())throw std::invalid_argument("Private direction data size");
    const auto directions=readDirectionData(Data(std::move(bytes)),PatchedEngineSha);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);if(take<char>(in)!='U')return 2;
        const auto byte=[&](){return std::uint8_t(number(in,0,255));};
        UnitScatterActor a;a.mission.mission98=number(in,-1,31);a.mission.queuedA0=number(in,-1,31);a.mission.queuedA4=byte();a.isTrain=byte();
        const auto control9=byte(),control7=byte(),ignoreMission=byte(),ignoreDestination=byte();
        a.field5c8=byte();a.field5b9=byte();a.field599=byte();a.destination494=number(in,0,1);a.target228=number(in,0,1);a.bridge79=byte();a.type5a4=take<int>(in);
        const auto currentLevel=std::int8_t(number(in,-128,127));const auto layer=byte();const auto level=take<int>(in),height=take<int>(in),tick=take<int>(in);
        a.body.desired=std::uint16_t(number(in,0,65535));a.body.start=std::uint16_t(number(in,0,65535));a.body.timerStart=take<int>(in);a.body.duration=take<int>(in);a.body.rate=std::uint16_t(number(in,0,65535));
        UnitScatterDriveLifetime lifetime;lifetime.references=take<std::uint32_t>(in);lifetime.globalReferences=take<std::uint32_t>(in);
        OriginalRandomState random;random.disabled=byte();random.next1=number(in,0,249);random.next2=number(in,0,249);const bool mutatePoint=number(in,0,1);const int repeats=number(in,1,512);
        const auto coord=[&](){const auto x=take<int>(in),y=take<int>(in),z=take<int>(in);return Coord{x,y,z};};
        const auto cell=[&](){const auto x=number(in,-32768,32767),y=number(in,-32768,32767);return ScatterCellPoint{std::int16_t(x),std::int16_t(y)};};
        a.position=coord();const auto coordinates=coord();auto away=coord();const auto emptyCell=cell(),pathResult=cell();
        std::array<ScatterCellPoint,8> neighbors;for(auto& p:neighbors)p=cell();
        std::array<int,8> bounds{},admissions{},projections{};std::array<std::uint32_t,8> flags{};
        for(auto& v:bounds)v=number(in,0,1);for(auto& v:admissions)v=number(in,0,7);for(auto& v:projections)v=number(in,0,1);for(auto& v:flags)v=take<std::uint32_t>(in);
        for(auto& v:random.table)v=take<std::uint32_t>(in);
        std::string extra;if(in>>extra)throw std::invalid_argument("Extra Unit Scatter input");
        if(lifetime.references==0||lifetime.references>=0x7fffffffu)throw std::invalid_argument("Unsupported Scatter retained reference count");
        const auto center=ScatterCellPoint{std::int16_t(coordinates.x/256),std::int16_t(coordinates.y/256)};
        const auto event=[](auto... v){((std::cout<<v<<' '),...);};
        const auto dir=[&](ScatterCellPoint p){for(int i=0;i<8;++i)if(p==ScatterCellPoint{std::int16_t(std::uint16_t(center.x)+std::uint16_t(neighbors[std::size_t(i)].x)),std::int16_t(std::uint16_t(center.y)+std::uint16_t(neighbors[std::size_t(i)].y))})return i;return -1;};
        std::map<std::pair<int,int>,UnitScatterCell> cells;UnitScatterServices s;
        s.trace=event;
        s.missionControl=[&](int raw,int off){const auto v=off==9?control9:control7;event('H',raw,off,int(v));if(off==7&&mutatePoint){away={};event('m',0,0,0);}return v;};
        s.coordinates=[&](){event('Q',coordinates.x,coordinates.y,coordinates.z);return coordinates;};
        s.lookup=[&](ScatterCellPoint p)->UnitScatterCell&{event('L',p.x,p.y,0);const auto d=dir(p);return cells.try_emplace({p.x,p.y},UnitScatterCell{p,currentLevel,d<0?0:flags[std::size_t(d)]}).first->second;};
        s.layer=[&](){event('Y',int(layer),0,0);return layer;};
        s.inBounds=[&](ScatterCellPoint p){const int d=dir(p);if(d<0)throw std::runtime_error("Missing supplied bounds association");event('N',p.x,p.y,bounds[std::size_t(d)]);return bool(bounds[std::size_t(d)]);};
        s.admissionLevel=[&](){event('V',level,0,0);return level;};
        s.admission=[&](UnitScatterCell&,int d,int value){event('A',d,value,admissions[std::size_t(d)]);return admissions[std::size_t(d)];};
        s.project=[&](Coord point){event('P',point.x,point.y,point.z);ScatterCellPoint p{std::int16_t((point.x-128)/256),std::int16_t((point.y-128)/256)};const auto d=dir(p);if(d<0)throw std::runtime_error("Missing supplied projection");if(!projections[std::size_t(d)])p.x=std::int16_t(std::uint16_t(p.x)+17u);return p;};
        s.pathfinder=[&](ScatterCellPoint p,ScatterCellPoint zero,int type,std::uint32_t bridge){if(zero!=ScatterCellPoint{})throw std::runtime_error("Pathfinder zero input lost");event('p',p.x,p.y,type,bridge);return pathResult;};
        s.destination=[&](UnitScatterCell& c,std::uint8_t flag){event('S',c.point.x,c.point.y,int(flag));};
        UnitScatterInputs w{directions,random,lifetime,neighbors,{},emptyCell,height,tick};
        for(int call=0;call<repeats;++call)scatterUnit(a,away,ignoreMission,ignoreDestination,w,s);
        event("state",a.mission.queuedA0,int(a.mission.queuedA4),lifetime.globalReferences,lifetime.references,random.next1,random.next2,away.x,away.y,away.z);
        for(auto v:random.table)event(v);std::cout<<'\n';
    }return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
