// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/PositionCloakEffect.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Position cloak-effect fixture outside domain");}
void run(std::istream& in){
    char op=0;long long mask=0;int x=0,y=0,owner=0,predicate=0;
    require(bool(in>>op>>x>>y>>owner>>mask>>predicate)&&op=='C'&&
        mask>=0&&mask<=0xffffffffLL&&predicate>=0&&predicate<=1);
    std::string extra;require(!(in>>extra));int calls=0;TerrainCellPoint queried{};
    PositionCloakEffectServices services;
    services.cell=[&](TerrainCellPoint point){queried=point;return PositionCloakEffectCell{1,point,std::uint32_t(mask)};};
    services.actorPredicate280=[&]{++calls;return predicate!=0;};
    const auto result=applyPositionCloakEffectPrefix({{x,y,0},owner},services);
    std::cout<<"R "<<unsigned(result)<<' '<<queried.x<<' '<<queried.y<<' '<<calls<<'\n';
}
void guards(){
    PositionCloakEffectServices services;
    services.cell=[](TerrainCellPoint p){return PositionCloakEffectCell{1,p,1};};
    services.actorPredicate280=[](){return true;};
    bool refused=false;try{(void)applyPositionCloakEffectPrefix({{},0},services);}
    catch(const std::invalid_argument&){refused=true;}require(refused);
    std::cout<<"Position cloak-effect guards PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);
    std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
