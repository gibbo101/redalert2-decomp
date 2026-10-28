// The Terrain unit's helper over the object index (0x00ABFF58,
// shared/object_index.hpp).
#ifndef RA2_SHARED_TERRAIN_OBJECT_INDEX_HPP
#define RA2_SHARED_TERRAIN_OBJECT_INDEX_HPP

#include "shared/terrain.hpp"

#include "shared/object_index.hpp"

// Adds an object to the index (TerrainClass::Load 0x006E4570). The extra
// inline expansion over Add_Index is what keeps Increase_Table_Size out of
// line there (VC6_MATCHING_NOTES.md, Swizzle_Pointer).
inline bool Add_Object_Index(long id, AbstractClass *object)
{
    return unknown_object_index_abff58.Add_Index(id, object);
}

#endif
