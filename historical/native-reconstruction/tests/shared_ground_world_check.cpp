// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/SharedGroundUnitVoxelWorld.hpp"
#include <iostream>
using namespace ra2;
int main(){try{
    RasterData raster;RenderData light;VoxelPalette palette;VoxelModel model;model.sections.emplace_back();
    Animation hva;hva.frames=1;UnitVoxelDrawInputs input;IndexRemap remap{};
    SharedUnitVoxelStage global;UnitVoxelWorldTypeIndexes type;UnitVoxelActorStage first,second;
    UnitVoxelWorldServices services;services.actor.originalTypeVisible=[]{};
    GroundUnitBodyServices body;body.pose=[](std::int32_t*){return voxelIdentity();};
    GroundUnitShadowServices shadow;shadow.pose=body.pose;shadow.relativeHeight=[]{return 0;};shadow.point=[]{return PixelPoint{};};
    std::vector<std::uint16_t> colors(4),depth(4),alpha(4);std::vector<Palette16> palettes(53);
    const auto draw=[&](const UnitVoxelStore& store={}){
        drawSharedPosedGroundUnitVoxelToWorld(raster,light,{&model,nullptr,nullptr},{&hva,&hva,&hva},palette,input,false,
            false,false,global,type,first,services,body,shadow,remap,{2,2,colors,depth,alpha,palettes},store);};
    const auto require=[](bool value){if(!value)throw std::runtime_error("Shared ground ownership guard failed");};
    for(int mode=0;mode<5;++mode){
        global={};first={};body.pose=[](std::int32_t*){return voxelIdentity();};input={};
        if(mode==0)first.staging=true;if(mode==1)global.stagingSurface=true;
        if(mode==2)body.pose={};if(mode==3)input.clip={0,0,3,2};if(mode==4)global.image.pixels.clear();
        int stores=0;bool refused=false;try{draw([&](char,int){++stores;});}catch(const std::invalid_argument&){refused=true;}
        require(refused&&stores==0&&!second.staging&&type.shadow.size()==0&&type.lit.parts[0].size()==0);
    }
    for(char stop:{'s','f'}){
        global={};first={};input={};body.pose=[](std::int32_t*){return voxelIdentity();};
        bool caught=false;try{draw([&](char k,int){if(k==stop)throw std::runtime_error("diagnostic observer");});}
        catch(const std::runtime_error&){caught=true;}
        require(caught&&global.stagingSurface&&first.staging==(stop=='f')&&!second.staging);
    }
    std::cout<<"Shared posed world domain, actor isolation and immediate partial writes: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
