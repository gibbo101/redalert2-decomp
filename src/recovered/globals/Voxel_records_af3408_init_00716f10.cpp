// Dynamic initializer of the global array 0x00AF3408 (0x00716F10): 64
// records of 0x48 bytes, each holding four Vector3s at +0x0C, constructed
// like 0x00716EE0. The record's other fields and the names are not known.
#include "shared/vector3.hpp"
// @ref ?unknown_records_af3408@@3PAUUnknownVoxelRecord48@@A=00af3408

struct UnknownVoxelRecord48 {
    int unknown_00[3];          // +0x00
    Vector3 Points[4];          // +0x0C
    int unknown_3c[3];          // +0x3C
};

UnknownVoxelRecord48 unknown_records_af3408[64];
