// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/SharedUnitVoxelStaging.hpp"
#include <iostream>
using namespace ra2;
int main(){try{
    RasterData raster;RenderData render;VoxelPalette vpl;IndexRemap remap{};Animation hva;hva.frames=1;
    UnitVoxelDrawInputs in;SharedUnitVoxelStage stage;UnitVoxelTypeIndexes type;UnitVoxelActorStage first,second;
    UnitVoxelStagingServices s;s.originalTypeVisible=[]{};int observed=0;
    const auto draw=[&](const SharedUnitVoxelObservers& observer={}){
        drawSharedUnitVoxelIntoStaging(raster,render,{nullptr,nullptr,nullptr},{&hva,&hva,&hva},vpl,in,false,stage,type,first,s,remap,observer);};
    const auto require=[](bool v){if(!v)throw std::runtime_error("Shared staging ownership guard failed");};
    for(int mode=0;mode<4;++mode){
        stage={};first={};in={};hva.frames=1;
        if(mode==0)first.staging=true;if(mode==1)stage.stagingSurface=true;
        if(mode==2)hva.frames=2;if(mode==3)in.emptyDirty.x=1048577;
        bool refused=false;try{draw({[&](char,int){++observed;},{}});}catch(const std::invalid_argument&){refused=true;}
        require(refused&&observed==0&&!second.staging&&type.parts[0].size()==0);
    }
    for(char stop:{'s','f'}){
        stage={};first={};in={};hva.frames=1;
        bool caught=false;try{draw({[&](char k,int){if(k==stop)throw std::runtime_error("diagnostic observer");},{}});}
        catch(const std::runtime_error&){caught=true;}
        require(caught&&stage.stagingSurface&&first.staging==(stop=='f')&&!second.staging);
    }
    std::cout<<"Shared staging domain, per-actor flag isolation and immediate partial-write observation: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
