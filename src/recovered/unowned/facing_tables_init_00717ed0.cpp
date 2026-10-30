// The facing tables of the voxel draw (0x00717ED0-0x00719033): matrices and
// quaternions per facing and per ramp, built by Unknown_00718060 (0x00718060).
// The 8 class-type statics below are this unit's dynamic initializers
// 0x00717ED0-0x00717F80 in definition order (Matrix3D and Vector3 arrays
// have empty inline constructors: one-ret initializers).
#include "shared/quaternion.hpp"
#include "shared/object_type.hpp"
#include "shared/facing.hpp"
#include "shared/fast_math.hpp"
// @ref ??0Quaternion@@QAE@MMMM@Z=00622160
// @ref ?Slerp@@YI?AVQuaternion@@ABV1@0M@Z=00622ac0
// @ref ?Build_Matrix3D@@YI?AVMatrix3D@@ABVQuaternion@@@Z=00622eb0
// @ref ??0Matrix3D@@QAE@ABUVector3@@M@Z=0058ff50
// @ref ?Make_Identity@Matrix3D@@QAEXXZ=00590060
// @ref ?Rotate_Y@Matrix3D@@QAEXM@Z=00590880
// @ref ?Translate@Matrix3D@@QAEXMMM@Z=00590090
// @ref ?Translate@Matrix3D@@QAEXABUVector3@@@Z=005900f0
// @ref ??D@YI?AVMatrix3D@@ABV0@0@Z=00591180
// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380
// @ref ?Axis_To_Quat@@YI?AVQuaternion@@ABUVector3@@M@Z=006229b0
// @ref ??0Matrix3D@@QAE@MM@Z=0058fef0
// @ref ?Set@Quaternion@@QAEXMMMM@Z=00622180
// @ref ??4Quaternion@@QAE?AV0@ABV0@@Z=00622250
// @ref ?Rotate_X@Matrix3D@@QAEXM@Z=00590760
// @ref ?Rotate_Z@Matrix3D@@QAEXM@Z=005909a0
// @ref __real@4@00000000000000000000=0079a738
// @ref __real@4@3ff9c90e560000000000=007aea34
// @ref ?Clear_Voxel_Indexes@ObjectTypeClass@@SAXXZ=005d7ef0
// @ref ?unknown_matrices_af73a0@@3PAVMatrix3D@@A=00af73a0
// @ref ?unknown_matrices_af8608@@3PAVMatrix3D@@A=00af8608
// @ref ?unknown_quaternions_af77d8@@3PAVQuaternion@@A=00af77d8
// @ref ?unknown_quaternions_af6618@@3PAVQuaternion@@A=00af6618
// @ref ?unknown_matrix_af77a8@@3VMatrix3D@@A=00af77a8
// @ref ?unknown_matrices_af8538@@3PAVMatrix3D@@A=00af8538
// @ref ?unknown_vectors_af7930@@3PAUVector3@@A=00af7930
// @ref ?unknown_vectors_af6768@@3PAUVector3@@A=00af6768
// @ref ?unknown_839aac@@3MA=00839aac
// @ref ?unknown_839ab0@@3UVector3@@A=00839ab0
// @ref ?unknown_839a60@@3UVector3@@A=00839a60
// @ref ?unknown_angles_7f9d84@@3PAMA=007f9d84
// @ref __real@4@c001c000000000000000=007aea30
// @ref __real@4@c000c000000000000000=007aea38

Matrix3D unknown_matrices_af73a0[21];
