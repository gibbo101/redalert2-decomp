// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingImage.hpp"
#include "assets/OverlayImage.hpp"
#include "sim/OriginalMath.hpp"
#include <bit>
#include <cmath>
#include <stdexcept>
namespace ra2 {
namespace {
void nameDomain(const std::string& s){
    if(s.size()>24||s.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_.")!=std::string::npos)
        throw std::invalid_argument("Building image filename outside bounded profile");
}
std::string genericName(std::string name){
    if(name.size()<2)name.resize(2,'\0');name[1]='G';return name;
}
void fileServices(const BuildingImageServices& s){
    if(!s.construct||!s.load||!s.finish)throw std::invalid_argument("Building image file/lifetime services unbound");
}
void finish(const BuildingImageServices& s,int id){s.finish(id,1);s.finish(id,2);}
int increment(int v){return std::bit_cast<std::int32_t>(std::uint32_t(v)+1u);}
int ftol(double v){return !std::isfinite(v)||v<-0x1p63||v>=0x1p63?0:std::bit_cast<std::int32_t>(std::uint32_t(std::int64_t(v)));}
}
const void* ensureBuildingPrimaryImage(BuildingImageState& a,const BuildingImageServices& s){
    const auto resident=a.primaryA4;if(resident||!a.demand13e0)return resident;
    if(a.primary13eb.empty())return a.primaryA4;
    nameDomain(a.primary13eb);fileServices(s);if(!s.cache)throw std::invalid_argument("Building image cache service unbound");
    s.construct(0,a.primary13eb);s.cache(0,0);const auto first=s.load(0);
    a.primaryA4=first;if(s.pointerStore)s.pointerStore(0xa4,first);
    if(first){a.ownedA8=1;if(s.store)s.store(0xa8,1,1);}
    else{
        // Original strncpy(...,19) need not terminate a long name. Refuse that
        // uninitialized-stack suffix rather than inventing replacement bytes.
        if(a.primary13eb.size()>=19)throw std::invalid_argument("Unterminated original Building fallback filename");
        s.construct(1,genericName(a.primary13eb));const auto second=s.load(1);
        a.primaryA4=second;if(s.pointerStore)s.pointerStore(0xa4,second);
        if(second){a.ownedA8=1;if(s.store)s.store(0xa8,1,1);}
        finish(s,1);
    }
    finish(s,0);return a.primaryA4;
}
const void* ensureBuildingSecondaryImage(BuildingImageState& a,BuildingTypeBoundsState& bounds,
        const std::int32_t& theater,const BuildingImageServices& s){
    const auto resident=bounds.secondaryB98;if(resident||!a.demand13e1)return resident;
    if(a.secondaryBf4.empty())return bounds.secondaryB98;
    nameDomain(a.secondaryBf4);fileServices(s);
    auto name=a.secondaryBf4+".SHP";applyObjectNewTheater(name,theater);
    s.construct(0,name);auto image=s.load(0);
    if(!image){s.construct(1,genericName(name));image=s.load(1);finish(s,1);}
    bounds.secondaryB98=image;if(s.pointerStore)s.pointerStore(0xb98,image);
    if(image){
        bounds.flagB9c=1;if(s.store)s.store(0xb9c,1,1);
        if(!s.frameCount)throw std::invalid_argument("Building animation SHP count unbound");
        int count=int(s.frameCount(image))/2;if(a.flag1351)count=increment(a.count137c);
        int duration=1;
        if(count>0){
            if(!s.timing1178)throw std::invalid_argument("Building animation rules timing unbound");
            const double timing=s.timing1178();OriginalRounding rounding;duration=ftol((timing*900.0)/double(count));
        }
        a.startC8c=0;if(s.store)s.store(0xc8c,4,0);
        a.countC90=count;if(s.store)s.store(0xc90,4,count);
        a.durationC94=duration;if(s.store)s.store(0xc94,4,duration);
    }
    finish(s,0);return bounds.secondaryB98;
}
}
