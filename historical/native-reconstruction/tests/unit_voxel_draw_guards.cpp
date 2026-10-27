// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitVoxelDraw.hpp"
#include <cfenv>
#include <iostream>
#include <stdexcept>
using namespace ra2;
int main(){try {
    RasterData data;UnitVoxelDrawInputs in;UnitVoxelDrawState state;UnitVoxelDrawServices services;
    int calls=0;services.originalTypeVisible=[&]{++calls;throw std::runtime_error("service failure");};
    for(int n:{0,-1,-2147483647}) {
        in.bodyFrames=n;
        try{drawHealthyUnitVoxel(data,in,state,services);throw std::runtime_error("Invalid HVA count accepted");}
        catch(const std::invalid_argument&){}
    }
    in.bodyFrames=1;
    for(int n:{0,1}) {
        state.staging=n==0;state.stagingSurface=n==1;
        try{drawHealthyUnitVoxel(data,in,state,services);throw std::runtime_error("Reentrant surface accepted");}
        catch(const std::invalid_argument&){}
    }
    if(calls)throw std::runtime_error("Rejected domain called services");
    state={};const int original=std::fegetround();
    for(int mode:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO}) {
        if(std::fesetround(mode))throw std::runtime_error("FP mode unavailable");
        try{drawHealthyUnitVoxel(data,in,state,services);}
        catch(const std::runtime_error& e){if(std::string(e.what())!="service failure")throw;}
        if(std::fegetround()!=mode)throw std::runtime_error("Unit voxel FP state leaked on exception");
        if(state.staging||state.stagingSurface)throw std::runtime_error("Pre-draw exception changed surface");
    }
    std::fesetround(original);
    if(calls!=4)throw std::runtime_error("Missing exception cases");
    std::cout<<"Unit voxel HVA/surface guards and FP restoration: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
