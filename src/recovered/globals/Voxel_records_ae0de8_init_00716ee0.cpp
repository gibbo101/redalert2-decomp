// Dynamic initializer of the global array 0x00AE0DE8 (0x00716EE0): 64
// records of 0x88 bytes, each holding eight Vector3s at +0x28, constructed
// by the eh vector constructor iterator with Vector3's empty constructor
// (0x00717CD0). The record's other fields and the names are not known.
#include "shared/vector3.hpp"
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??0Vector3@@QAE@XZ=00717cd0
// @ref ?unknown_records_ae0de8@@3PAUUnknownVoxelRecord88@@A=00ae0de8

struct UnknownVoxelRecord88 {
    int unknown_00[10];         // +0x00
    Vector3 Points[8];          // +0x28
};
// (0x88 bytes: no fields after Points)

UnknownVoxelRecord88 unknown_records_ae0de8[64];
