// The object index (0x00ABFF58): every AbstractClass object that joins it, keyed
// by its ID (Fetch_ID). TargetClass (Target.cpp) resolves its references through
// it; the techno and terrain constructors, destructors and Loads add and remove
// themselves. Defined in Target.cpp (initializer 0x006B5440).
#ifndef RA2_SHARED_OBJECT_INDEX_HPP
#define RA2_SHARED_OBJECT_INDEX_HPP

#include "shared/ini_class.hpp"     // IndexClass

class AbstractClass;

extern IndexClass<long, AbstractClass *> unknown_object_index_abff58;

#endif
