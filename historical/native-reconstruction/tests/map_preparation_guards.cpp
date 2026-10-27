// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapPreparation.hpp"
#include <iostream>
using namespace ra2;
template<class F>void refused(F f){try{f();}catch(const std::exception&){return;}throw std::runtime_error("Expected safety refusal");}
int main(){try{
    std::vector<int> slots(512*512,-1);std::vector<MapPreparationCell> cells(1);unsigned called=0;
    MapPreparationServices services;refused([&]{prepareMapCells(2,slots,cells,services);});
    services.initializeLighting=[&](int){++called;};services.recalculate=[&](int,int){++called;};
    for(int profile:{0,1}){cells[0].attachedTag=profile==0;cells[0].attributes.overlay=profile==1?0:-1;refused([&]{prepareMapCells(2,slots,cells,services);});}
    if(called)throw std::runtime_error("Unsupported profile invoked a child");
    cells[0].attachedTag=false;cells[0].attributes.overlay=-1;
    refused([&]{prepareMapCells(1,slots,cells,services);});slots[1025]=1;refused([&]{prepareMapCells(2,slots,cells,services);});
    refused([&]{prepareMapCells(2,std::span<const int>(slots).first(4),cells,services);});
    slots.assign(512*512,-1);slots[1025]=0;
    cells[0].attributes.input.position={1,2};
    ResidentMapPreparationInputs input;input.width=2;input.height=2;input.slots=slots;input.permission={2,0,0,2,2};
    MapCellInput fallback;std::vector<std::uint8_t> b4(100),b10(250);
    ResidentMapPreparationServices joined;
    refused([&]{prepareResidentMapCells(input,cells,fallback,b4,b10,joined);});
    joined.initializeLighting=[&](int){++called;};
    refused([&]{prepareResidentMapCells(input,cells,fallback,std::span(b4).first(99),b10,joined);});
    slots[1025]=7;refused([&]{prepareResidentMapCells(input,cells,fallback,b4,b10,joined);});
    slots[1025]=0;cells[0].attributes.input.position={2,2};
    refused([&]{prepareResidentMapCells(input,cells,fallback,b4,b10,joined);});
    cells[0].attributes.input.position={1,2};
    refused([&]{prepareResidentMapCells(input,cells,cells[0].attributes.input,b4,b10,joined);});
    input.cliffMode=3;refused([&]{prepareResidentMapCells(input,cells,fallback,b4,b10,joined);});
    input.cliffMode=0;input.height=2147483647;
    refused([&]{prepareResidentMapCells(input,cells,fallback,b4,b10,joined);});input.height=2;
    if(called)throw std::runtime_error("Invalid resident binding invoked lighting");
    input.cliffMode=0;
    prepareResidentMapCells(input,cells,fallback,b4,b10,joined);
    if(called!=1)throw std::runtime_error("Valid resident binding did not reach lighting");
    std::cout<<"Map preparation native domain guards: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
