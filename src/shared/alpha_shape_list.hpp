// The list of alpha shapes (0x0083C648; defined with the AlphaShape unit's
// header statics, 0x0041E970). Held apart from shared/alpha_shape.hpp so that
// the AlphaShape unit is unchanged.
#ifndef RA2_SHARED_ALPHA_SHAPE_LIST_HPP
#define RA2_SHARED_ALPHA_SHAPE_LIST_HPP

#include "shared/vector_class_decl.hpp"

class AlphaShapeClass;

extern DynamicVectorClass<AlphaShapeClass *> unknown_AlphaShapeClass_list_0083c648;   // 0x0083C648

#endif
