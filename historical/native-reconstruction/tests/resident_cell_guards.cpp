// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/ResidentCellPreparation.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
int main(){try{
    MapCellAttributes c;c.input.position={51,72};c.input.tile=0;c.overlay=0;c.overlayData=97;c.passability=17;
    MapCellInput fallback;std::vector<MapCellInput*> table(262144);table[72*512+51]=&c.input;
    MapTileImageInput image;image.columns=image.rows=1;image.subTiles={MapSubTileInput{0,5,false,0,0}};
    std::array<MapTileAttributes,1> tiles;tiles[0].image=&image;
    std::array<int,16> land{};std::array<float,11> speeds;speeds.fill(1.0f);
    std::array<MapOverlayType,1> overlays;overlays[0].tiberium=255;overlays[0].flag1FD=255;
    std::array<MapResourceType,1> resources;resources[0].numImages=1;
    ResidentCellInputs input;input.world={table,&fallback,{},{}};input.tiles=tiles;input.landMap=land;
    input.overlays=overlays;input.resources=resources;input.wheelSpeeds=speeds;input.lat.fill(-1);input.permission={80,0,0,80,85};
    std::array<std::uint8_t,4> b4{};std::array<std::uint8_t,10> b10{};
    bool cleared=false,zeroed=false,queried=false;
    ResidentCellServices services;
    services.store=[&](MapAttributeField field,unsigned value){
        if(field==MapAttributeField::Overlay){if(value!=0xffffffffu||c.overlay!=-1)throw std::runtime_error("Overlay store is stale");cleared=true;}
        if(field==MapAttributeField::OverlayData){if(!cleared||value||c.overlayData)throw std::runtime_error("Data clear order differs");zeroed=true;}
    };
    services.beforePassability=[&](const auto& state){if(!zeroed||state.overlay!=-1||state.overlayData)throw std::runtime_error("Passability saw stale resource");};
    services.passabilityStore=[&](int value){if(c.passability!=value)throw std::runtime_error("Passability store observer saw stale Cell");};
    input.world.query=[&](auto p){if(p!=c.input.position||table[72*512+51]!=&c.input||c.input.slope!=5)throw std::runtime_error("Lookup did not share current Cell");queried=true;};
    recalculateResidentCell(c,-1,b4,b10,input,services);
    if(!queried||!zeroed||c.passability||b4[0]||c.overlay!=-1)throw std::runtime_error("Shared removal/passability result differs");
    // Clearing the overlay must prevent its old Crushable flag from selecting
    // overlay passability. A missing ordinary lookup binding is a safety refusal.
    c.input.tile=65535;c.overlay=-1;input.world.cells={};bool refused=false;
    try{recalculateResidentCell(c,-1,b4,b10,input);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Missing map lookup accepted");
    std::cout<<"Resident Cell shared mutation and passability boundaries: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
