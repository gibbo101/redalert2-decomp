// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/ResidentOverlayPreparation.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
int main(){try{
    OverlayPlacementCell cell,fallback;cell.position={2,2};cell.data=17;
    MapCellAttributes a,f;a.input.position=cell.position;a.input.tile=0;a.overlayData=17;
    std::vector<MapCellInput*> table(262144);table[1026]=&a.input;
    std::array<OverlayTypeInputs,1> types;types[0].index=0;types[0].land=5;
    types[0].noUseTileLandType=0;types[0].tiberium=1;types[0].image=1;
    std::array<MapOverlayType,1> overlayTypes;overlayTypes[0].land=5;overlayTypes[0].tiberium=1;
    std::array<MapResourceType,1> resources;resources[0].numImages=1;
    std::array<std::uint8_t,9> frames{};
    MapTileImageInput image;image.columns=image.rows=1;image.height=45;
    image.subTiles={MapSubTileInput{0,5,false,0,0}};
    std::array<MapTileAttributes,1> tiles;tiles[0].image=&image;
    std::array<int,16> land{};std::array<float,11> speeds;speeds.fill(1);
    ResidentCellInputs input;input.world={table,&f.input,{},{}};input.tiles=tiles;input.landMap=land;
    input.overlays=overlayTypes;input.resources=resources;input.wheelSpeeds=speeds;
    input.permission={3,0,0,3,3};input.lat.fill(-1);
    std::array<std::uint8_t,128> b4{};std::array<std::uint8_t,320> b10{};
    ResidentOverlayServices services;services.attributes=[&](auto& c)->MapCellAttributes&{return &c==&cell?a:f;};
    auto& s=services.overlay;
    unsigned cursor=0,observed=0;
    s.reader.section=[](auto pack,unsigned){return pack==OverlayMapPack::Types?1:0;};
    s.reader.read=[&](auto)->std::optional<std::uint8_t>{return cursor++==1026?0:255;};
    s.reader.allocate=[](){return true;};
    s.placement.cell=[&](auto p)->OverlayPlacementCell&{if(p==cell.position)return cell;fallback.position=p;return fallback;};
    s.placement.noAttachedAnimation=[](){};s.placement.redraw=[](){};
    s.lifetime.expired=[](unsigned){};s.lifetime.baseDestroy=[](unsigned){};s.lifetime.free=[](unsigned){};
    const auto check=[&](){if(cell.overlay!=a.overlay||cell.data!=a.overlayData||cell.slope!=a.input.slope||cell.passability!=a.passability)
        throw std::runtime_error("Store observer saw stale shared Cell");++observed;};
    s.placement.store=[&](unsigned role,unsigned,unsigned,unsigned){if(role==1)check();};
    s.reader.store=[&](auto&,auto){check();};services.attributeStore=[&](auto&,auto,auto){check();};
    services.passabilityStore=[&](auto&,int){check();};
    OverlayMapPreparationState state;for(auto& r:state.registries)r.slots.resize(2);
    OverlayMapPreparationInputs preparation;
    prepareResidentMapOverlays(2,3,3,false,types,state,preparation,fallback,input,frames,b4,b10,services);
    if(cell.overlay!=-1||cell.data||cell.slope!=5||!observed||state.objects.size()!=1)
        throw std::runtime_error("Actual resource clear did not reach shared placement records");
    bool refused=false;overlayTypes[0].land=0;
    try{prepareResidentMapOverlays(1,3,3,false,types,state,preparation,fallback,input,frames,b4,b10,services);}
    catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Mismatched type projection accepted");
    overlayTypes[0].land=5;
    for(unsigned bad=0;bad<3;++bad){
        auto invalid=input;auto shortBuffer=std::span<std::uint8_t>(b10);
        if(bad==0)invalid.permission.dimension0=4;
        if(bad==1)invalid.directions[0]={1,1};
        if(bad==2)shortBuffer=shortBuffer.first(319);
        OverlayMapPreparationState empty;refused=false;
        try{prepareResidentMapOverlays(1,3,3,false,types,empty,preparation,fallback,invalid,frames,b4,shortBuffer,services);}
        catch(const std::invalid_argument&){refused=true;}
        if(!refused)throw std::runtime_error("Inconsistent resident map/table/buffer inputs accepted");
    }
    std::cout<<"Resident overlay immediate shared-store observers and type guards: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
