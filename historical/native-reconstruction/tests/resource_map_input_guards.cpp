// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/ResourceMapInputs.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
int main(){try{
    OverlayTypeInputs first,second;first.index=102;second.index=27;
    ResourceTypeInputs a,b;a.image=&first;a.index=1;a.numImages=12;a.numSlopes=8;a.numFrames=12;a.value=25;
    b.image=&second;b.index=0;b.numImages=12;b.numFrames=12;b.value=50;
    ResourceTypeRegistry primary,secondary;primary.slots={&a,&b,nullptr};primary.count=2;
    ResourceListServices services;
    const auto inputs=readMapResourceTypes(0,primary,secondary,services);
    if(inputs.size()!=2||inputs[0].index!=1||inputs[0].imageIndex!=102||inputs[1].index!=0||inputs[1].numSlopes!=0)
        throw std::runtime_error("Resource projection lost order/stored indices/default slopes");
    a.image=nullptr;bool refused=false;
    try{readMapResourceTypes(0,primary,secondary,services);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Unassociated resource accepted");
    std::cout<<"Initialized resource registry order/image boundaries: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
