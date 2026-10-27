// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/ResourceMapInputs.hpp"

namespace ra2 {
std::vector<MapResourceType> readMapResourceTypes(int count,ResourceTypeRegistry& types,
    ResourceTypeRegistry& secondary,const ResourceListServices& services) {
    readResourceTypeList(count,types,secondary,services);
    std::vector<MapResourceType> result;
    result.reserve(std::size_t(types.count));
    for(int i=0;i<types.count;++i)result.push_back(mapResourceInputs(*types.slots[std::size_t(i)]));
    return result;
}
}
