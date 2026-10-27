// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/NearbyLocationPolicy.hpp"
namespace ra2 {
NearbyLocationPoint nearbyLocation(const NearbyLocationPoint& source,
    const NearbyLocationPoint& closeTo,const NearbyLocationOptions& options,
    const NearbyLocationWorld& world,const NearbyLocationServices& services){
    return nearbyLocationPolicy(source,closeTo,options,world,services);
}
}
