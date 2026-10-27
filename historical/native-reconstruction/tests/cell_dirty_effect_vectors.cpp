// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/CellDirtyEffect.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Cell dirty-effect fixture outside domain");}
void run(std::istream& in){
    char op=0;long long flags=0;int data=0,slope=0,resident=0;CellDirtyEffectInput c;
    require(bool(in>>op>>c.overlay44>>data>>slope>>flags>>resident)&&op=='D'&&data>=0&&data<=255&&
        slope>=0&&slope<=255&&flags>=0&&flags<=0xffffffffLL&&resident>=0&&resident<=1);
    std::string extra;require(!(in>>extra));c.overlayData11e=std::uint8_t(data);c.slope11c=std::uint8_t(slope);
    c.flags140=std::uint32_t(flags);c.hasPrimaryResident=resident!=0;
    std::cout<<"R "<<unsigned(applyCellDirtyEffectPrefix(c))<<'\n';
}
void guards(){
    bool refused=false;try{(void)applyCellDirtyEffectPrefix({0x7e,0x30,0,0,true});}
    catch(const std::invalid_argument&){refused=true;}require(refused);
    std::cout<<"Cell dirty-effect guards PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);
    std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
