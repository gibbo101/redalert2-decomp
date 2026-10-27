// BuildingTypes (0x00A35CD8), the list every BuildingTypeClass registers in.
// Split from building_type.hpp for units that look types up by name but must
// not pick up that header's static rectangle initializer (AITriggerTypeClass).
#ifndef RA2_SHARED_BUILDING_TYPE_LIST_HPP
#define RA2_SHARED_BUILDING_TYPE_LIST_HPP

#include "shared/vector_class.hpp"

class BuildingTypeClass;
extern DynamicVectorClass<BuildingTypeClass *> BuildingTypes;   // 0x00A35CD8

#endif
