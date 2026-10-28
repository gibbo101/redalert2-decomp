// The list of live spawn managers (0x00ABD028; defined with the SpawnManager
// unit's header statics, 0x006894A0). Held apart from shared/spawn_manager.hpp so
// that the SpawnManager unit, which defines the list before it sees the class,
// is unchanged.
#ifndef RA2_SHARED_SPAWN_MANAGER_LIST_HPP
#define RA2_SHARED_SPAWN_MANAGER_LIST_HPP

#include "shared/vector_class_decl.hpp"

class SpawnManagerClass;

extern DynamicVectorClass<SpawnManagerClass *> unknown_SpawnManagerClass_list_00abd028;   // 0x00ABD028

#endif
