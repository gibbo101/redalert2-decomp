// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TechnoPlacement.hpp"
#include "sim/UnitDrawingState.hpp"
#include "assets/UnitFireAngle.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace ra2;
namespace {
void facing(const Facing& f){std::cout<<f.desired<<' '<<f.start<<' '<<f.timerStart<<' '<<f.duration<<' '<<f.rate<<' ';}
template<class... T> void event(T... args){((std::cout<<args<<' '),...);}
Facing readFacing(std::istream& in) {
    Facing f;unsigned d,s,r;in>>d>>s>>f.timerStart>>f.duration>>r;f.desired=d;f.start=s;f.rate=r;return f;
}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)) {
        std::istringstream in(line);char op;in>>op;
        if(op=='M') {
            int fallback,present,value;in>>fallback>>present>>value;
            Ini rules(present?"[HTNK]\nFireAngle="+std::to_string(value)+"\n":"[HTNK]\n");
            std::cout<<InitialUnitFireAngle<<' '<<readUnitFireAngle(rules,"HTNK",fallback);
        } else if(op=='O') {
            std::string path;in>>path;std::cout<<InitialUnitFireAngle<<' '<<readUnitFireAngle(Ini(readFile(path).text()),"HTNK");
        } else if(op=='P'||op=='C') {
            UnitPlacementState a;UnitPlacementInputs input;
            int accept,onMap,b0,b1,predicate,effect,cell,flag373,flag190,cellValue,cellKind,ownerDefault;
            std::array<int,2> location;
            in>>input.currentFrame>>input.direction>>input.fireAngle>>accept>>onMap>>b0>>b1>>predicate>>effect>>cell>>input.heightDivisor;
            in>>input.requested.x>>input.requested.y>>input.requested.z>>a.position.x>>a.position.y>>a.position.z;
            in>>a.field1F4>>a.field114>>flag373>>flag190>>a.field400>>a.field3EC>>a.field3F0
              >>location[0]>>location[1]>>cellValue>>cellKind>>ownerDefault;
            a.body=readFacing(in);a.barrel=readFacing(in);a.onMap=std::uint8_t(onMap);a.field373=std::uint8_t(flag373);
            if(op=='C') {
                const auto initial=initialUnitDrawingFields(input.currentFrame);a.body=initial.body;a.barrel=initial.barrel;
                input.fireAngle=readUnitFireAngle(Ini("[HTNK]\n"),"HTNK");
            }
            a.flag190=std::uint8_t(flag190);a.bridge32D=0xa7;a.height378=0xa7;
            a.field1A0.fill(signed32(0xa7a7a7a7u));input.typeEffect=effect!=0;
            UnitPlacementServices s;int bridgeCalls=0;
            s.bridge=[&](TerrainCellPoint p){event("bridge",p.x,p.y);return std::uint8_t(bridgeCalls++?b1:b0);};
            s.objectUnlimbo=[&](Coord p,int d){event("object",p.x,p.y,p.z,d);return std::uint8_t(accept);};
            s.reset418=[](){event("reset");};s.typeQuery=[](){event("type");};
            s.mapUpdate=[](Coord p,int distance){event("map",p.x,p.y,p.z,distance);};
            s.registerEffect=[](){event("effect");};s.ownerPlacement=[](){event("owner");};
            s.unitKind=[](){event("kind");};s.notify414=[](){event("notify414");};
            s.predicate1E8=[&](){event("predicate");return std::uint8_t(predicate);};
            s.notify1D4=[](){event("notify1d4");};s.cell1A4=[&](){event("cell");return cell!=0;};
            s.value2A0=[&](){event("value");return cellValue;};s.kind38=[&](int v){event("cellkind",v);return cellKind;};
            s.associateCell=[](int k){event("associate",k);};
            s.locate=[&](Coord p){event("locate",p.x,p.y,p.z);return location;};s.ownerDefault=[&](){return ownerDefault;};
            const bool result=placeOrdinaryUnit(a,input,s,[](int o,int n,int v){event("w",o,n,v);});
            event("state",result);facing(a.body);facing(a.barrel);
            event(int(a.onMap),int(a.bridge32D),int(a.flag190),int(a.field373),int(a.height378),
                  a.field3EC,a.field3F0,a.field400,a.field114,a.field1A0[0],a.field1A0[1]);
            event("pitch");for(unsigned delta:{0,1,2,3,10})event(a.barrel.current(signed32(std::uint32_t(input.currentFrame)+delta)));
        } else throw std::invalid_argument("Unknown placement command");
        if(!in)throw std::invalid_argument("Missing placement input");in>>std::ws;
        if(!in.eof())throw std::invalid_argument("Trailing placement input");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
