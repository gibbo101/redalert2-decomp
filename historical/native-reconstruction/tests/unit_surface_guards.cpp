// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitSurfaceDraw.hpp"
#include <stdexcept>
int main(){
    ra2::UnitSurfaceInputs in;in.typeBAE=1;ra2::UnitSurfaceServices s;
    bool queried=false;s.layer=[&]{queried=true;return 0;};
    try{ra2::drawOrdinaryUnitSurface(in,s);return 1;}catch(const std::invalid_argument&){}
    if(queried)return 2;
    for(auto flags:{0u,0x2000u,0x2801u,0x2810u,0xffffffffu}){
        try{ra2::unitSurfaceBlitterSlot(flags);return 3;}catch(const std::invalid_argument&){}
    }
    return 0;
}
