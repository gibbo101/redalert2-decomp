// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayMapPreparation.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
int main(){try{
    OverlayMapPreparationState state;OverlayMapPreparationInputs input;OverlayMapPreparationServices services;
    const auto refuses=[&]{bool rejected=false;try{prepareDecodedMapOverlays(1,2,3,false,{},state,input,services);}catch(const std::invalid_argument&){rejected=true;}if(!rejected)throw std::runtime_error("Overlay preparation guard accepted");};
    refuses();state.objects.emplace_back();refuses();state.objects.clear();state.registries[0].count=1;refuses();state.registries[0].count=0;
    OverlayPlacementCell cell;services.placement.cell=[&](auto)->OverlayPlacementCell&{return cell;};
    unsigned cleanups=0;services.reader.cleanup=[&]{++cleanups;};
    services.lifetime.expired=[](unsigned){};services.lifetime.baseDestroy=[](unsigned){};services.lifetime.free=[](unsigned){};
    prepareDecodedMapOverlays(1,2,3,false,{},state,input,services);
    if(cleanups!=1||!state.objects.empty()||cell.overlay!=-1)throw std::runtime_error("Old-version cleanup join failed");
    std::cout<<"Overlay preparation storage and empty cleanup boundaries: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
