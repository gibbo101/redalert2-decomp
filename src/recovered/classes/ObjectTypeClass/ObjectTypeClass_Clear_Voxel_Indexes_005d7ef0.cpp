// void ObjectTypeClass::Clear_Voxel_Indexes() (0x005D7EF0)
// Releases the four cached buffers of every object type, then resets
// unknown_839aa8 from unknown_839aa4 (name and meaning hypotheses).
#include "shared/object_type.hpp"
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?ObjectTypes@@3V?$DynamicVectorClass@PAVObjectTypeClass@@@@A=00a72f90
// @ref ?unknown_839aa4@@3HA=00839aa4
// @ref ?unknown_839aa8@@3HA=00839aa8

extern int unknown_839aa4;
extern int unknown_839aa8;

void ObjectTypeClass::Clear_Voxel_Indexes()
{
    for (int index = 0; index < ObjectTypes.Count(); index++) {
        ObjectTypeClass *type = ObjectTypes[index];
        type->unknown_214.~UnknownBuffer();
        type->unknown_228.~UnknownBuffer();
        type->unknown_23c.~UnknownBuffer();
        type->unknown_250.~UnknownBuffer();
    }
    unknown_839aa8 = unknown_839aa4;
}
