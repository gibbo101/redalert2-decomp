// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/UnitTypeMetadata.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace ra2;
namespace {
const char* keys[]={"Harvester","Voxel","Turret","HunterSeeker","BalloonHover"};
std::string decode(const std::string& hex) {
    if(hex=="-")return {};
    if(hex.size()%2)throw std::invalid_argument("Invalid hex input");
    std::string result;
    for(std::size_t i=0;i<hex.size();i+=2)result+=char(std::stoul(hex.substr(i,2),nullptr,16));
    return result;
}
void print(UnitTypeMetadata type) {
    std::cout<<int(type.harvester)<<' '<<int(type.voxel)<<' '<<int(type.turret)<<' '
             <<int(type.hunterSeeker)<<' '<<int(type.balloonHover)<<'\n';
}
}
int main() {
    try {
        std::string line;
        while(std::getline(std::cin,line)) {
            std::istringstream in(line);char op;in>>op;
            if(op=='B') {
                int mode,fallback;std::string hex;in>>mode>>fallback>>hex;
                std::cout<<int(iniBooleanValue(mode==5?decode(hex):"",std::uint8_t(fallback)))<<'\n';
            } else if(op=='M') {
                int field,mode,fallback;std::string hex;in>>field>>mode>>fallback>>hex;
                if(field<0||field>=5)throw std::invalid_argument("Invalid field");
                UnitTypeMetadata type{23,41,67,97,123};
                std::uint8_t* fields[]={&type.harvester,&type.voxel,&type.turret,&type.hunterSeeker,&type.balloonHover};
                *fields[field]=std::uint8_t(fallback);
                const auto text=std::string("[HTNK]\n")+(mode==5?std::string(keys[field])+"="+decode(hex)+"\n":"");
                const Ini empty(""),values(text);
                print(readUnitTypeMetadata(field==1?empty:values,field==1?values:empty,"HTNK",type));
            } else if(op=='C')print({});
            else if(op=='O') {
                std::string rules,art;in>>rules>>art;
                print(readUnitTypeMetadata(Ini(readFile(rules).text()),Ini(readFile(art).text()),"HTNK"));
            } else throw std::invalid_argument("Unknown metadata command");
            if(!in)throw std::invalid_argument("Missing metadata input");
        }
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 1;}
}
