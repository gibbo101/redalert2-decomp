// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapWallUpdate.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
int main(){try{
    MapWallCell c;c.overlay=203;c.data=71;MapWallUpdateServices s;
    try{updateMapWall(c,1,s);throw std::runtime_error("Missing wall services accepted");}catch(const std::invalid_argument&){}
    if(c.overlay!=203||c.data!=71)throw std::runtime_error("Missing service mutated Cell");
    s.cell=[&](auto)->MapWallCell&{return c;};s.bounds=[](const auto&,unsigned){return MapWallBounds{};};
    s.unite=[](auto a,auto){return a;};s.dirty=[](auto){};s.notify=[](auto){};s.recalculate=[](auto&,int){};s.expired=[](auto&){};s.zone=[](unsigned,auto){};
    try{updateMapWall(c,1,s);throw std::runtime_error("Missing overlay registry accepted");}catch(const std::invalid_argument&){}
    std::cout<<"Map wall service and registry boundaries: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
