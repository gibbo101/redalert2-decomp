// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/UnitMovementRestriction.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace ra2;
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op;in>>op;
        if(op=='M'){
            int mode,neighbor;in>>mode>>neighbor;
            if(mode<0||mode>1||neighbor<0||neighbor>255)throw std::invalid_argument("Restriction command outside domain");
            std::cout<<readUnitMovementRestriction(Ini(mode?"[HTNK]\nMovementZone=Destroyer\n":""),"HTNK");
        }else if(op=='O'){
            std::string path;in>>path;std::cout<<readUnitMovementRestriction(Ini(readFile(path).text()),"HTNK");
        }else throw std::invalid_argument("Unknown restriction command");
        if(!in)throw std::invalid_argument("Missing restriction input");in>>std::ws;
        if(!in.eof())throw std::invalid_argument("Trailing restriction input");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
