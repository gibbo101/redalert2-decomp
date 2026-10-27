// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayTypeInputs.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
namespace {
template<class F> void refuses(F call){
    try{call();}catch(const std::invalid_argument&){return;}
    throw std::runtime_error("Unsupported overlay input accepted");
}
}
int main(){try{
    OverlayTypeInputs t;OverlayTypeRegistry r;OverlayConstructionServices s;
    refuses([&]{constructOverlayType(t,"T",r,s);});
    s.base=[](auto&,auto){};r.count=-1;
    refuses([&]{constructOverlayType(t,"T",r,s);});
    r.count=1;r.slots.resize(1);
    refuses([&]{constructOverlayType(t,"T",r,s);});
    r.count=0;r.slots.clear();s.grow=[](int){return true;};
    refuses([&]{constructOverlayType(t,"T",r,s);});
    refuses([&]{resolveOverlayType("T",r,s);});
    refuses([&]{readOverlayTypeList(1,{},r,s);});
    OverlayIniServices ini;
    refuses([&]{readOverlayTypeIni(t,ini);});
    ini.base=[](auto&){return false;};
    if(readOverlayTypeIni(t,ini))throw std::runtime_error("Rejected base INI accepted");
    ini.base=[](auto&){return true;};
    refuses([&]{readOverlayTypeIni(t,ini);});
    std::cout<<"Overlay input storage/service guards: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
