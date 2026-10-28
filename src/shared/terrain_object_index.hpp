// The object index keyed by Fetch_ID (0x00ABFF58; buildings and terrain
// objects join it) as the Terrain unit sees it: an IndexClass. The Building
// headers (shared/techno_index.hpp) declare the same object with their own
// index template (UnknownIndexClass); kept out of terrain.hpp so that a unit
// may include terrain.hpp and building_class.hpp together (Scenario.cpp).
#ifndef RA2_SHARED_TERRAIN_OBJECT_INDEX_HPP
#define RA2_SHARED_TERRAIN_OBJECT_INDEX_HPP

#include "shared/terrain.hpp"

extern IndexClass<long, ObjectClass *> unknown_object_index_abff58;

#endif
