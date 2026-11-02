// The AbstractClass kind name table (0x007CD978): 71 {name, kind} pairs,
// <none>, Unit, Aircraft, AircraftType, Anim, ... read by Name_From_RTTI
// 0x0040DB60 and RTTI_From_Name 0x0040DB90 (shared/ccini_extra.hpp).
// Names follow Westwood's RTTI vocabulary; the struct name is a hypothesis.
#ifndef RA2_SHARED_RTTI_NAME_TABLE_HPP
#define RA2_SHARED_RTTI_NAME_TABLE_HPP

#include "shared/ccini_extra.hpp"

struct RTTINameStruct {
    char const *Name;       // +0x00
    RTTIType Type;          // +0x04
};

extern RTTINameStruct RTTINames[71];        // 0x007CD978

#endif
