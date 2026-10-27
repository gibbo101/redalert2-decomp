// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/BuildingTypeBounds.hpp"
#include <string>
namespace ra2 {
struct BuildingImageState {
    const void* primaryA4=nullptr;
    std::uint8_t ownedA8=0,demand13e0=0,demand13e1=0,flag1351=0;
    std::int32_t count137c=0,startC8c=0,countC90=0,durationC94=0;
    std::string primary13eb,secondaryBf4;
};
struct BuildingImageServices {
    std::function<void(int,const std::string&)> construct;
    std::function<void(int,int)> cache;
    std::function<const void*(int)> load;
    std::function<void(int,int)> finish;
    std::function<std::int16_t(const void*)> frameCount;
    std::function<double()> timing1178;
    // Read-only diagnostic stores; pointer identities are supplied as opaque
    // values, separate from numeric fields and host allocation addresses.
    std::function<void(int,const void*)> pointerStore;
    std::function<void(int,int,int)> store;
};
// Complete458CE0 /45E790 policy on bounded filenames; file construction/read/
// cache/cleanup services are explicit. Existing Type bounds fields are borrowed.
const void* ensureBuildingPrimaryImage(BuildingImageState&,const BuildingImageServices&);
const void* ensureBuildingSecondaryImage(BuildingImageState&,BuildingTypeBoundsState&,
    const std::int32_t& theater,const BuildingImageServices&);
}
