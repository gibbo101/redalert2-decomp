// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapOverlayLoading.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
namespace {
template<class F> void refuses(F call){try{call();}catch(const std::invalid_argument&){return;}throw std::runtime_error("Unsupported overlay load accepted");}
}
int main(){try{
    OverlayMapLoadServices s;std::vector<OverlayTypeInputs> types;
    refuses([&]{loadDecodedMapOverlays(2,1,1,false,types,s);});
    int cleanup=0;s.cleanup=[&]{++cleanup;};
    loadDecodedMapOverlays(1,1,1,false,types,s);
    if(cleanup!=1)throw std::runtime_error("Old-version cleanup missing");
    refuses([&]{loadDecodedMapOverlays(2,1,1,false,types,s);});
    s.section=[](auto,unsigned){return 0;};loadDecodedMapOverlays(2,1,1,false,types,s);
    s.section=[](auto pack,unsigned){return pack==OverlayMapPack::Types?1:0;};
    refuses([&]{loadDecodedMapOverlays(2,1,1,false,types,s);});
    OverlayLoadCell cell;
    s.cell=[&](auto)->OverlayLoadCell&{return cell;};
    unsigned cursor=0;s.read=[&](auto)->std::optional<std::uint8_t>{return cursor++==513?0:255;};
    refuses([&]{loadDecodedMapOverlays(2,1,1,false,types,s);});
    types.resize(1);types[0].demandLoad=1;cursor=0;
    refuses([&]{loadDecodedMapOverlays(2,1,1,false,types,s);});
    types[0].image=1;cursor=0;
    refuses([&]{loadDecodedMapOverlays(2,1,1,false,types,s);});
    s.allocate=[](){return true;};cursor=0;
    refuses([&]{loadDecodedMapOverlays(2,1,1,false,types,s);});
    std::cout<<"Overlay map stream/registry/service boundaries: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
