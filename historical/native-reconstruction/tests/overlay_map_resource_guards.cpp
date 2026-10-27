// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayMapResources.hpp"
#include <stdexcept>
#include <iostream>
using namespace ra2;
template<class F>void refuses(F f){bool caught=false;try{f();}catch(const std::invalid_argument&){caught=true;}if(!caught)throw std::runtime_error("Invalid resource binding accepted");}
int main(){try{
    OverlayPlacementCell origin,neighbor;origin.position={12,13};origin.data=71;
    OverlayMapResourceInputs input;OverlayMapResourceServices services;
    // Absent overlays must not consult missing registries or lookups.
    if(updateLoadedMapResource(origin,input,services)||origin.data!=71)throw std::runtime_error("Absent resource changed");
    origin.overlay=0;refuses([&]{updateLoadedMapResource(origin,input,services);});
    std::array<OverlayTypeInputs,1> overlays;input.overlays=overlays;
    if(updateLoadedMapResource(origin,input,services)||origin.data!=71)throw std::runtime_error("Nonresource changed");
    overlays[0].tiberium=255;
    refuses([&]{updateLoadedMapResource(origin,input,services);});
    std::array<MapResourceType,1> records;records[0].numImages=1;records[0].numFrames=3;records[0].value=-7;input.resources=records;
    refuses([&]{updateLoadedMapResource(origin,input,services);});
    unsigned lookups=0,stores=0;neighbor.overlay=0;
    services.cell=[&](MapInputPosition p)->OverlayPlacementCell&{if(p!=origin.position)throw std::runtime_error("Unexpected alias query");++lookups;return neighbor;};
    refuses([&]{updateLoadedMapResource(origin,input,services);});
    if(origin.data!=71||stores)throw std::runtime_error("Refusal stored data");
    const std::array<std::uint8_t,3> frames{17,3,255};input.frames=frames;
    services.store=[&](auto& c,std::uint8_t value){if(&c!=&origin||c.data!=value)throw std::runtime_error("Resource store identity/order");++stores;};
    lookups=0;
    if(updateLoadedMapResource(origin,input,services)!=-1792||origin.data!=255||stores!=1||lookups!=8)
        throw std::runtime_error("Aliased shared resource update failed");
    // The next call must observe changed shared neighbor state and store only
    // in the origin; no cached overlay classification or copied neighbor record.
    neighbor.overlay=-1;
    if(updateLoadedMapResource(origin,input,services)!=-126||origin.data!=17||neighbor.data||stores!=2||lookups!=16)
        throw std::runtime_error("Shared neighbor mutation was lost");
    origin.overlay=-2;refuses([&]{updateLoadedMapResource(origin,input,services);});
    std::cout<<"Loaded resource bindings, mutation visibility and store identity: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
