// The object index keyed by Fetch_ID (0x00ABFF58; buildings and terrain
// objects join it) as the Terrain unit sees it: an IndexClass. The Building
// headers (shared/techno_index.hpp) declare the same object with their own
// index template (UnknownIndexClass); kept out of terrain.hpp so that a unit
// may include terrain.hpp and building_class.hpp together (Scenario.cpp).
#ifndef RA2_SHARED_TERRAIN_OBJECT_INDEX_HPP
#define RA2_SHARED_TERRAIN_OBJECT_INDEX_HPP

#include "shared/terrain.hpp"

extern IndexClass<long, ObjectClass *> unknown_object_index_abff58;

// Adds an object to the index (TerrainClass::Load 0x006E4570). The extra
// inline expansion over Add_Index is what keeps Increase_Table_Size out of
// line there (VC6_MATCHING_NOTES.md, Swizzle_Pointer).
inline bool Add_Object_Index(long id, ObjectClass *object)
{
    return unknown_object_index_abff58.Add_Index(id, object);
}

#endif
