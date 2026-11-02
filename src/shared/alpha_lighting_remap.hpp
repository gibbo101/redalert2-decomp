// AlphaLightingRemapClass: a 65536-entry table of 16-bit alpha-lighting
// values for one light level, shared through AlphaLightingRemapClass::Array
// and reference counted (AlphaLightingRemap unit 0x0041E320-0x0041E600;
// the cache object at 0x008315B8 in shared/alpha_table_cache.hpp finds and
// releases them). The table is the object's first member.
#ifndef RA2_SHARED_ALPHA_LIGHTING_REMAP_HPP
#define RA2_SHARED_ALPHA_LIGHTING_REMAP_HPP

#include "shared/vector_class.hpp"

class AlphaLightingRemapClass {
public:
    // Builds the table for a level: entry i = min(level - 1, (i & 0xFF) * (i >> 8) * (level - 1) / 0x7E02) << 8.
    AlphaLightingRemapClass(int level);                 // 0x0041E590
    // Empty and inline: UnknownAlphaTableCache_008315B8::Release (0x0041E510)
    // null-tests the pointer before operator delete.
    ~AlphaLightingRemapClass() {}

    unsigned short Table[0x10000];                      // +0x00000
    int Level;                                          // +0x20000
    int RefCount;                                       // +0x20004

    static DynamicVectorClass<AlphaLightingRemapClass *> Array;     // 0x0083C5D8
};

#endif
