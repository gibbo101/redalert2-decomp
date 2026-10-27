// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapGeometry.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
template<class F> void refused(F f){try{f();}catch(const std::invalid_argument&){return;}throw std::runtime_error("Expected native safety refusal");}
int main(){try{
    for(auto r:{MapGeometryRect{0,0,0,1},{0,0,1,0},{0,0,-1,80},{0,0,128,129},{0,0,2147483647,1}})refused([&]{initialMapGeometry(r);});
    auto g=initialMapGeometry({1,1,1,1});std::vector<MapCellInput> cells(1);std::vector<MapCellInput*> table(262144);MapCellInput fallback;
    table[0]=&fallback;refused([&]{initializeMapGeometryCells(g,cells,table,fallback,{},0);});table[0]=nullptr;
    auto forged=g;forged.positions[0]={-1,0};refused([&]{initializeMapGeometryCells(forged,cells,table,fallback,{},0);});
    refused([&]{initializeMapGeometryCells(g,{},table,fallback,{},0);});
    refused([&]{initializeMapGeometryCells(g,cells,table,cells[0],{},0);});
    std::array<std::uint8_t,3> incomplete{};refused([&]{initializeMapGeometryBuffer(incomplete);});
    std::cout<<"Map geometry native domain guards: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
