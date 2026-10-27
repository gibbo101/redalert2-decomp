// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/ResourceTypeInputs.hpp"

namespace ra2 {
// Read the numeric-key list, then project registry order into the immutable
// records consumed by shared overlay preparation. This native phase binding is
// not a recovered original startup caller or full type/parser initialization.
std::vector<MapResourceType> readMapResourceTypes(int,ResourceTypeRegistry&,
    ResourceTypeRegistry&,const ResourceListServices&);
}
